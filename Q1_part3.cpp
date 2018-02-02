// EE569 Homework Assignment #1
// Date: 2018.1.29
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath> // use for round function
#include <algorithm>  // use max and min algorithm

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel = 3;
    int Size = 512;
    int SizeEnlarged = 650;
    
    // Allocate image data array
    unsigned char Imagedata[Size][Size][BytesPerPixel];
    unsigned char result1[SizeEnlarged][SizeEnlarged][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    double positionPerPix = (double) (Size - 1) / (SizeEnlarged - 1);
    double positionX = 0, positionY = 0, deltaX = 0, deltaY = 0;
    int positionP = 0, positionQ = 0, fpq = 0, fpq1 = 0, fp1q1 = 0, fp1q = 0;
    cout << "size of original picture = " << Size << endl;
    cout << "size of enlarged picture = " << SizeEnlarged << endl;
    for (int i = 0; i < SizeEnlarged; i++) 
    {
        for (int j = 0; j < SizeEnlarged; j++) 
        {
            positionX = positionPerPix * i;
            positionY = positionPerPix * j;
            //cout << positionX << "," << positionY << endl;
            // if the new position is just at the original pixel's position, we can use it directly
            if ((abs(round(positionX) - positionX) < 0.00001)  && (abs(round(positionY) - positionY) < 0.00001)) 
            {
                //cout << "remain org: (" << positionX << ", " << positionY << ") , ("<< i<< ", " << j << ")"<<endl;
                for (int k = 0; k < BytesPerPixel; k++) 
                {
                    result1[i][j][k] = Imagedata[(int)positionX][(int)positionY][k];
                }
                
            }
            // otherwise we need to udr bilinear interpolation to calculate the result
            else
            {
                positionP = floor(positionX);
                positionQ = floor(positionY);

                for (int k = 0; k < BytesPerPixel; k++) 
                {
                    fpq = (int) Imagedata[positionP][positionQ][k];
                    fpq1 = (int) Imagedata[positionP + 1][positionQ][k];
                    fp1q = (int) Imagedata[positionP][positionQ + 1][k];
                    fp1q1 = (int) Imagedata[positionP + 1][positionQ + 1][k];
                    deltaX = positionX - positionP;
                    deltaY = positionY - positionQ;
                    double temp = fpq*(1 - deltaX)*(1 - deltaY) + fpq1*(deltaX)*(1 - deltaY) + fp1q*(1 - deltaX)*(deltaY) + fp1q1*(deltaX)*(deltaY);
                    result1[i][j][k] = (char) ((int) temp);
                }
            }
        }
    }

    char out1[] = "Q1_part3_1.raw";
    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out1,"wb"))) {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result1, sizeof(unsigned char), SizeEnlarged*SizeEnlarged*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    cout << "Finished!" << endl;
    // Write image data (filename specified by second argument) from image data matrix
    return 0;
}
