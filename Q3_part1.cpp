// EE569 Homework Assignment #1
// Date: 2018.1.29
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>  // use max and min algorithm
#include <fstream>  
#include <cmath>
#include "histogram.cpp" // the function to write the histogram
using namespace std;

const int Size1 = 512, Size2 = 512;
const int BytesPerPixel = 3;
// The function to calculate PSNR
// input1 and input2: the pointer of first pixel of image, example: image[0][0][0]
// input3: the pointer of the first position of PSNR array, exmpale: PSNR[0]
void PSNR_Calculate(unsigned char * image1,unsigned char * image2, double * PSNR_array)
{
    double PSNR = 0, MSE = 0, maxValue = 255;
    for (int k = 0; k < BytesPerPixel; k++)
    {
        PSNR = 0;
        MSE = 0;
        for (int i = 0; i < Size1; i++)
        {
            for (int j = 0; j < Size2; j++)
            {
                MSE += pow( ((int)(image1[(i * Size2 + j) * BytesPerPixel+ k])) - ((int)(image2[(i * Size2 + j) * BytesPerPixel+ k])), 2);
            }
        }
        MSE = MSE / Size1 / Size2;
        PSNR = 10 * log10(maxValue * maxValue / MSE);
        PSNR_array[k] = PSNR;
    }
}

void Outlier_removal_filter(unsigned char * image,unsigned char * image_new, int filterSize, int threshold)
{
    double avgValue;
    int range = (filterSize - 1) / 2;
    int count,locX,locY;
    int midValue;
    for (int k = 0; k < BytesPerPixel; k++)
    {
        for (int i = 0; i < Size1; i++)
        {
            for (int j = 0; j < Size2; j++)
            {
                avgValue = 0;
                count = 0;
                for (int m = -range; m <=range; m++)
                {
                    for (int n = -range; n <=range; n++)
                    {
                        locX = i + m;
                        locY = j + n;
                        if ((m == 0) & (n == 0))
                        {
                            midValue = (int)image[(i * Size2 + j) * BytesPerPixel+ k];
                        }
                        else if ((locX >= 0) & (locX < Size1) & (locY >= 0) & (locY < Size2))
                        {   
                            avgValue += (int)image[(locX * Size2 + locY) * BytesPerPixel+ k];
                            count++;
                        }
                    }
                }
                avgValue = (double) avgValue / count;
                //cout << "compare :" << abs(avgValue - midValue) << endl;
                if (abs(avgValue - midValue) > threshold)
                {
                    image_new[(i * Size2 + j) * BytesPerPixel+ k] = (char) ((int)avgValue);
                }
                else
                {
                    image_new[(i * Size2 + j) * BytesPerPixel+ k] = (char)midValue;
                }
            }
        }
    }
}
void Mean_filter(unsigned char * image,unsigned char * image_new, int filterSize)
{
    double avgValue;
    int range = (filterSize - 1) / 2;
    int count,locX,locY;
    int filter[filterSize][filterSize];
    for (int k = 0; k < BytesPerPixel; k++)
    {
        for (int i = 0; i < Size1; i++)
        {
            for (int j = 0; j < Size2; j++)
            {
                avgValue = 0;
                count = 0;
                for (int m = -range; m <=range; m++)
                {
                    for (int n = -range; n <=range; n++)
                    {
                        locX = i + m;
                        locY = j + n;
                        if ((locX >= 0) & (locX < Size1) & (locY >= 0) & (locY < Size2))
                        {   
                            avgValue += (int)image[(locX * Size2 + locY) * BytesPerPixel+ k];
                            count++;
                        }
                    }
                }
                avgValue = (double) avgValue / count;
                image_new[(i * Size2 + j) * BytesPerPixel+ k] = (char) ((int)avgValue);
            }
        }
    }
}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file;
    // Allocate image data array
    unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
    unsigned char Imagedata_noisy[Size1][Size2][BytesPerPixel];
    unsigned int hist_noisy[256][BytesPerPixel];
    unsigned char result1[Size1][Size2][BytesPerPixel];
    unsigned char result2[Size1][Size2][BytesPerPixel];
    double PSNR[BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);
    // Read image (filename specified by second argument) into image data matrix
    if (!(file=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_noisy, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    Histogram(Size1,Size2,&Imagedata_noisy[0][0][0],&hist_noisy[0][0],"Q3_1",BytesPerPixel);

    PSNR_Calculate(&Imagedata_org[0][0][0],&Imagedata_noisy[0][0][0],&PSNR[0]);
    cout << "Noise image's PSNR:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i<<" = " << PSNR[i] << endl;
    }


    int filterSize = atoi(argv[2]);
    cout << "window size = " << filterSize << endl;
    int bestCon = 0, best = 0;
    for (int i = 0; i < 100;i++)
    {
        double sum = 0;
        Outlier_removal_filter(&Imagedata_noisy[0][0][0],&result1[0][0][0],filterSize,i);
        Mean_filter(&result1[0][0][0],&result2[0][0][0],filterSize);
        PSNR_Calculate(&Imagedata_org[0][0][0],&result2[0][0][0],&PSNR[0]);
        for (int j = 0; j < 3; j++)
        {
            sum += PSNR[j];
        }
        if (sum > best)
        {
            best = sum;
            bestCon = i;
        }
    }
    cout << "best = " << bestCon << endl;



    Outlier_removal_filter(&Imagedata_noisy[0][0][0],&result1[0][0][0],filterSize,bestCon);

    PSNR_Calculate(&Imagedata_org[0][0][0],&result1[0][0][0],&PSNR[0]);
    cout << "PSNR after the outlier removal filter:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i<<" = " << PSNR[i] << endl;
    }
    Mean_filter(&result1[0][0][0],&result2[0][0][0],filterSize);
    // check the filtered result
    PSNR_Calculate(&Imagedata_org[0][0][0],&result2[0][0][0],&PSNR[0]);
    cout << "PSNR after mean filter:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i<<" = " << PSNR[i] << endl;
    }




    char out1[] = "Q3_outlier_filtered.raw";
        if (!(file = fopen(out1,"wb"))) {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result1, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    char out2[] = "Q3_1_final.raw";
        if (!(file = fopen(out2,"wb"))) {
        cout << "Cannot open file1: " << out2 << endl;
        exit(1);
    }
    fwrite(result2, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    return 0;
}
