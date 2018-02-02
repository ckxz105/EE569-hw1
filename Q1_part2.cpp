// EE569 Homework Assignment #1
// Date: 2018.1.29
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>  // use max and min algorithm

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file;
    int BytesPerPixel = 3, Size1 = 480, Size2 = 854;
    
    // Allocate image data array
    unsigned char Imagedata[Size1][Size2][BytesPerPixel];
    unsigned char result1[Size1][Size2][1];
    unsigned char result2[Size1][Size2][1];
    unsigned char result3[Size1][Size2][1];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

for (int i = 0; i < Size1; i++) 
{
    for (int j = 0; j < Size2; j++) 
    {
        //cout << (int)Imagedata[i][j][0] << "," <<(int)Imagedata[i][j][1] << ","<< (int)Imagedata[i][j][2] << endl;
        int newVal1 = 255 - (int)Imagedata[i][j][0];
        int newVal2 = 255 - (int)Imagedata[i][j][1];
        int newVal3 = 255 - (int)Imagedata[i][j][2];
        //cout << "i = "<< i << ": "<< (int)Imagedata[0][i][0] << "," << endl;
        result1[i][j][0] = (char) newVal1;
        result2[i][j][0] = (char) newVal2;
        result3[i][j][0] = (char) newVal3;

        //cout << "result = " << newVal << endl;
        
    }
}

    char out1[] = "Q1_part2_1.raw", out2[] = "Q1_part2_2.raw", out3[] = "Q1_part2_3.raw";
    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out1,"wb"))) {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result1, sizeof(unsigned char), Size1*Size2, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out2,"wb"))) {
        cout << "Cannot open file2: " << out2 << endl;
        exit(1);
    }
    fwrite(result2, sizeof(unsigned char), Size1*Size2, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out3,"wb"))) {
        cout << "Cannot open file3: " << out3 << endl;
        exit(1);
    }
    fwrite(result3, sizeof(unsigned char), Size1*Size2, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    cout << "Finished!" << endl;
    return 0;
}
