// EE569 Homework Assignment #1
// Date: 2018.1.29
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>  // used for max and min algorithm

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int Size = 256;
    int BytesPerPixel = 3;

    // Allocate image data array
    unsigned char Imagedata[Size][Size][BytesPerPixel];
    unsigned char result1[Size][Size][1];
    unsigned char result2[Size][Size][1];
    unsigned char result3[Size][Size][1];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //cout << "size of picture = " << Size << endl;

    for (int i = 0; i < Size; i++) 
    {
        for (int j = 0; j < Size; j++) 
        {
            // for first way: lightness method
            int newVal1 = (min((int)Imagedata[i][j][0], min((int)Imagedata[i][j][1], (int)Imagedata[i][j][2]) ) + max( (int)Imagedata[i][j][0], max((int)Imagedata[i][j][1], (int)Imagedata[i][j][2]) ) ) / 2;
            // for second way: average method
            int newVal2 = ((int)Imagedata[i][j][0] + (int)Imagedata[i][j][1] + (int)Imagedata[i][j][2] ) / 3;
            // for third way: luminosity method
            int newVal3 = 0.21 * (int)Imagedata[i][j][0] + 0.72 * (int)Imagedata[i][j][1] + 0.07 * (int)Imagedata[i][j][2];
            // apply the calculated values to the result for output
            result1[i][j][0] = (char) newVal1;
            result2[i][j][0] = (char) newVal2;
            result3[i][j][0] = (char) newVal3;
        }
    }

    char out1[] = "Q1_part1_1.raw", out2[] = "Q1_part1_2.raw", out3[] = "Q1_part1_3.raw";
    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out1,"wb"))) {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result1, sizeof(unsigned char), Size*Size, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out2,"wb"))) {
        cout << "Cannot open file2: " << out2 << endl;
        exit(1);
    }
    fwrite(result2, sizeof(unsigned char), Size*Size, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out3,"wb"))) {
        cout << "Cannot open file3: " << out3 << endl;
        exit(1);
    }
    fwrite(result3, sizeof(unsigned char), Size*Size, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    return 0;
}
