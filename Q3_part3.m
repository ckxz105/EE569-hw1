% EE569 Homework Assignment #1
% Date: 2018.1.29
% Name: Jun Liu
% ID  : 4871562115
% email:liu494@usc.edu

% y is the original image
y = im2double(readraw('House.raw',256,256,1));
% z is the noisy image
z = im2double(readraw('House_noisy.raw',256,256,1));
sigma = 25;
[PSNR, y_est] = BM3D(y, z, sigma);
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
ima_patchs = spatial_patchization(z, WP);
% Local PCA denoising step
ima_patchs_fil = PLPCA_denoising(ima_patchs, func_thresholding, hW, delta);
% Uniform reprojection step
ima_fil_PLPCA = reprojection_UWA(ima_patchs_fil);

%%
figure();
subplot(2,2,1);
imshow(y);
title("Original image");
set(gca,'FontSize',15);

subplot(2,2,2);
imshow(z);
title("Noisy image");
set(gca,'FontSize',15);

subplot(2,2,3);
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
plotimage(ima_fil_PLPCA);
title("PLPCA image, PSNR = 31.36");
set(gca,'FontSize',15);

subplot(2,2,4);
imshow(y_est);
title(["BM3D image, PSNR = " + PSNR]);
set(gca,'FontSize',15);