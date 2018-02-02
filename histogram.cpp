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
//const int BytesPerPixel = 1;

// The function to read the image and store the histogram
void Histogram(const int Size1, const int Size2, unsigned char * Imagedata, unsigned int * hist, string name, int BytesPerPixel)
{
    //unsigned int hist[byteRange][BytesPerPixel];
    for (int i = 0; i < byteRange; i++) 
    {
        for (int k = 0; k < BytesPerPixel; k++) 
        {
            hist[i * BytesPerPixel + k] = 0;
        }
    } 
    int temp;
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++) 
            {
                temp = ((int) Imagedata[(i * Size2 + j) * BytesPerPixel+ k]);

                // generate the histogram information
                hist[temp * BytesPerPixel + k]++;
            }

        }
    }
    string out1 = name + "_histogram.txt";
    fstream f;
    f.open(out1,fstream::out);
    if (f.is_open())
    {
        for (int j = 0; j < BytesPerPixel; j++) 
        {
            f << j << endl;
            for (int i = 0; i < byteRange; i++) 
            {
                f << i << "," << hist[i * BytesPerPixel + j]<< endl;
            } 
        }
    }
    f.close();
    cout << "The histogram is stored at " << out1 << endl;
}