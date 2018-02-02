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

const int byteRange = 256;
const int BytesPerPixel = 3;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file2;
    int BytesPerPixel = 3, Size1 = 750, Size2 = 1000, byteRange = 256;
    
    // Allocate image data array
    unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
    unsigned int hist_org[byteRange][BytesPerPixel];

    unsigned char Imagedata_film[Size1][Size2][BytesPerPixel];
    unsigned int hist_film[byteRange][BytesPerPixel];

    for (int i = 0; i < byteRange; i++) 
    {
        for (int k = 0; k < BytesPerPixel; k++) 
        {
            hist_org[i][k] = 0;
            hist_film[i][k] = 0;
        }
    } 
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    if (!(file2=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[2] <<endl;
        exit(1);
    }
    fread(Imagedata_film, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file2);
    fclose(file2);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int temp;
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++) 
            {
                temp = ((int) Imagedata_org[i][j][k]);
                // generate the histogram information
                hist_org[temp][k]++;

                temp = ((int) Imagedata_film[i][j][k]);
                hist_film[temp][k]++;

            }
        }
    }


    char out1[] = "Q2_part5_hist_org.txt", out2[] = "Q2_part5_hist_film.txt";
    fstream f1,f2;
    f1.open(out1,fstream::out);
    if (f1.is_open())
    {
        for (int j = 0; j < BytesPerPixel; j++) 
        {
            f1 << j << endl;
            for (int i = 0; i < byteRange; i++) 
            {
                f1 << i << "," << hist_org[i][j]<< endl;
            } 
        }
    }
    f1.close();

    f2.open(out2,fstream::out);
    if (f2.is_open())
    {
        for (int j = 0; j < BytesPerPixel; j++) 
        {
            f2 << j << endl;
            for (int i = 0; i < byteRange; i++) 
            {
                f2 << i << "," << hist_film[i][j]<< endl;
            } 
        }
    }
    f2.close();

    // Write image data (filename specified by second argument) from image data matrix
/*

*/
    return 0;
}
