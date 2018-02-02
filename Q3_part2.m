% EE569 Homework Assignment #1
% Date: 2018.1.29
% Name: Jun Liu
% ID  : 4871562115
% email:liu494@usc.edu
%% Initialization
clear all
close all
ima = double(readraw("House.raw",256,256,1));
ima_nse = double(readraw("House_noisy.raw",256,256,1));

% WP        : the size of the patch
% factor_thr: use to control the thresholding function
% sigma     : parameter of the gaussian noise
% hW        : half size of the searching zone
% delta     : shift parameter, controls the overlap of searching windows
%% Searching for the best results: it takes a lot of time to finished!
psnr_all = [];
psnr_best = 0;
for WP_loop = 8:10
    for factor_loop = 290 : 5 : 350
        for hW_loop = 20 : 20
            for sigma_loop = 20 : 29
                WP = WP_loop;
                factor_thr = factor_loop / 100;
                hW = hW_loop;
                sigma = sigma_loop;
                threshold = factor_thr * sigma;
                % Shift/Redudancy  parameter for the searching zone.
                delta = hW; %< 2*hW+WP;
                func_thresholding = @(ima_ppca) ...
                    hardthresholding(ima_ppca, threshold, sigma);
                %% Patchization step 
                ima_patchs = spatial_patchization(ima_nse, WP);
                %% Local PCA denoising step
                ima_patchs_fil = PLPCA_denoising(ima_patchs, func_thresholding, hW, delta);
                %% Uniform reprojection step
                ima_fil_PLPCA = reprojection_UWA(ima_patchs_fil);
                psnr_temp = psnr(ima, ima_fil_PLPCA);
                %disp("当前PSNR = " + psnr_temp);
                psnr_all = [psnr_all psnr_temp];
                if (psnr_temp > psnr_best)
                    psnr_best = psnr_temp;
                    para_best = [WP, factor_thr, hW, sigma];
                end
            end
        end
    end
end
%% Display

figure();
subplot(1,3,1);
plotimage(ima_nse);
title(sprintf('Noisy:PSNR %.2f', psnr(ima, ima_nse)));
set(get(gca,'Title'),'FontSize',15);
subplot(1,3,2);
plotimage(ima);
title(sprintf('Original'));
set(get(gca,'Title'),'FontSize',15);
WP = 10;
factor_thr = 3.4;
hW = 20;
sigma = 21;
threshold = factor_thr * sigma;
% Shift/Redudancy  parameter for the searching zone.
delta = hW; %< 2*hW+WP;
func_thresholding = @(ima_ppca) ...
    hardthresholding(ima_ppca, threshold, sigma);
local_time=tic;
% Patchization step 
ima_patchs = spatial_patchization(ima_nse, WP);
% Local PCA denoising step
ima_patchs_fil = PLPCA_denoising(ima_patchs, func_thresholding, hW, delta);
% Uniform reprojection step
ima_fil_PLPCA = reprojection_UWA(ima_patchs_fil);
subplot(1,3,3);
plotimage(ima_fil_PLPCA);
title(sprintf('PLPCA:PSNR %.2f', psnr(ima, ima_fil_PLPCA)));
set(get(gca,'Title'),'FontSize',12);

