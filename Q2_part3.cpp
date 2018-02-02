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
using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file;
    int BytesPerPixel = 3, Size1 = 256, Size2 = 256, byteRange = 256;
    
    // Allocate image data array
    unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
    unsigned char result[Size1][Size2][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int temp;
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            result[i][j][0] = (char)(int)((double)(255 - (int) Imagedata_org[i][Size2 - j][0] * 0.6750));
            result[i][j][1] = (char)(int)((double)(196 - (int) Imagedata_org[i][Size2 - j][1] *0.6452));
            result[i][j][2] = (char)(int)((double)(175 - (int) Imagedata_org[i][Size2 - j][2] *0.5949));
        }
    }


    char out1[] = "Q2_film_filter.raw";
        if (!(file = fopen(out1,"wb"))) {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    cout << "Finished!" << endl;
    return 0;
}
