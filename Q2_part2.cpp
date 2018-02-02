// EE569 Homework Assignment #1
// Date: 2018.1.29
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>  // use max and min algorithm
#include <cmath> // use for pow function
#include <sstream>
#include <string>
using namespace std;


const int Size1 = 275, Size2 = 380;
const int BytesPerPixel = 3, byteRange = 256;
// Allocate image data array
unsigned char Imagedata[Size1][Size2][BytesPerPixel];
unsigned char result1[Size1][Size2][BytesPerPixel];
unsigned char result2[Size1][Size2][BytesPerPixel];
unsigned int hist[byteRange][BytesPerPixel];

// the function to transfer number to string
string num2str(double i)
{
    stringstream ss;
    ss<<i;
    return ss.str();
}
// define a linkedlist structure
struct Node {
  int xaxis;
  int yaxis;
  Node *next;

  Node(int xValue, int yValue);
  Node(int xValue, int yValue, Node *n);
};
// add new elements first time
Node::Node(int xValue, int yValue)
{
    xaxis = xValue;
    yaxis = yValue;
    next = NULL;
}
// add the new elements at the first position of the linkedlist
Node::Node(int xValue, int yValue, Node *n)
{
    xaxis = xValue;
    yaxis = yValue;
    next = n;
}
// get the amount of pixels stored in the bucket
int size(Node *list) {
    int amount = 0;
    Node *p = list;
    while (p != NULL)
    {
        amount++;
        // Go to next
        p = p->next;
    }
    return amount;
}
// add the new pixel position to the memory
void addAtHead(Node *&list,const int xValue, int yValue) 
{
    list = new Node(xValue, yValue, list);

}

typedef Node * ListType;
// define the structure to store the pixel information
class Table {
    public:
        Table();
        void insert(int xValue, int yValue, int insertPos);
        void printAll();
        void getColorMap(int colorAmount, int * colorMap, int * colorRange);
    private:
        ListType * histInfo; // the place to store the hashed buckets

};
// initialize function
Table::Table(){
    histInfo = new ListType[byteRange];
    for (int i = 0; i < byteRange; i++) 
    {
        histInfo[i] = NULL;
    }
}

// add the new pixel position to the memory
void Table::insert(int xValue, int yValue, int insertPos)
{
    addAtHead(histInfo[insertPos],xValue,yValue);
}
// check the histogram detail, just use for test purpose
void Table::printAll()  
{
    int i = 0, temp = 0, summ = 0;
    for (i = 0; i < byteRange; i++)
    {
        temp = size(histInfo[i]);
        summ = summ + temp;
        cout << i <<": " << temp << endl;
    }
    cout << "sum = " << summ << endl;
}
void Table::getColorMap(int colorAmount, int * colorMap, int * colorRange)
{
    
    int totalPixel = Size1 * Size2;
    int threshold = totalPixel / colorAmount / 2;
    int totalCount = 0;
    int tempCount1 = 0, tempCount2 = -threshold;
    int i = 0, j = 0, k = 0;
    Node *p = histInfo[0];
    //cout << "threshold = " << threshold << endl;
    // repeat until all points are reallocated
    while (totalCount < totalPixel)
    {

        if (tempCount1 == threshold)
        {
            colorMap[j] = i;
            tempCount1 = -threshold ;
            j++;
            //cout << j << "->" << i << endl;
        }
        if (tempCount2 == threshold)
        {
            colorRange[k] = i;
            tempCount2 = -threshold ;
            k++;
            //cout << "!"<< k << "->" << i << endl;
        }
        if (p->next == NULL)
        {
            i++;
            p = histInfo[i];
        }
        else
        {
            p = p->next;
        }
        tempCount1++;
        tempCount2++;
        totalCount++;
    }
    colorRange[colorAmount - 1] = 255;
}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file;
    Table * result_R;
    Table * result_G;
    Table * result_B;
    // initialize the structure
    result_R = new Table();
    result_G = new Table();
    result_B = new Table();
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);
    string name = argv[1];
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
/*
 //step 1 : Quantize – for method 1
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {   
                double temp = (double) (int)Imagedata[i][j][k] / 32;
                if (temp < 1)
                {
                    result1[i][j][k] = 16;
                }
                else if (temp < 2)
                {
                    result1[i][j][k] = 48;
                }
                else if (temp < 3)
                {
                    result1[i][j][k] = 80;
                }
                else if (temp < 4)
                {
                    result1[i][j][k] = 112;
                }
                else if (temp < 5)
                {
                    result1[i][j][k] = 144;
                }
                else if (temp < 6)
                {
                    result1[i][j][k] = 176;
                }
                else if (temp < 7)
                {
                    result1[i][j][k] = 208;
                }
                else
                {
                    result1[i][j][k] = 240;
                }

            }
        }
    }

*/

    //step 1 : Quantize - for method 2
    //Histogram(Size1,Size2,&Imagedata[0][0][0],&hist[0][0],name);
    int colorAmount = atoi(argv[2]);
    int sumCurrent = 0, sumLast = 0, currentColorLoc = 0;
    //int tempTreshold = Size1 * Size2 / colorAmount;
    int colorMap_R[colorAmount];
    int colorMap_G[colorAmount];
    int colorMap_B[colorAmount];
    int colorRange_R[colorAmount];
    int colorRange_G[colorAmount];
    int colorRange_B[colorAmount];
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++) 
            {
                int temp = ((int)Imagedata[i][j][k]);
                // generate the histogram information
                if (k == 0)
                    result_R->insert(i,j,temp);
                if (k == 1)
                    result_G->insert(i,j,temp);
                if (k == 2)
                    result_B->insert(i,j,temp);
            }
        }
    }
    result_R->getColorMap(colorAmount,&colorMap_R[0],&colorRange_R[0]);
    result_G->getColorMap(colorAmount,&colorMap_G[0],&colorRange_G[0]);
    result_B->getColorMap(colorAmount,&colorMap_B[0],&colorRange_B[0]);

    for (int i = 0; i < colorAmount; i++)
    {
        cout << "R: if R < " << colorRange_R[i] << ", ->" << colorMap_R[i] << endl; 
        cout << "G: if G < " << colorRange_G[i] << ", ->" << colorMap_G[i] << endl; 
        cout << "B: if B < " << colorRange_B[i] << ", ->" << colorMap_B[i] << endl; 
    }
    for (int i = 0; i < Size1; i++)
    {
        for (int j = 0; j < Size2; j++)
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {
                int temp = (int) Imagedata[i][j][k];
                for (int m = 0; m < colorAmount; m++)
                {
                    if (k == 0)
                    {
                        if (temp <= colorRange_R[m])
                        {
                            result1[i][j][k] = (char) colorMap_R[m];
                            break;
                        }
                    }
                    else if (k == 1)
                    {
                        if (temp <= colorRange_G[m])
                        {
                            result1[i][j][k] = (char) colorMap_G[m];
                            break;
                        }
                    }
                    else if (k == 2)
                    {
                        if (temp <= colorRange_B[m])
                        {
                            result1[i][j][k] = (char) colorMap_B[m];
                            break;
                        }
                    }
                }
            }
        }
    }

    //step 2 : neighborhood filter
    int filterSize = atoi(argv[3]), tempLocX = 0, tempLocY = 0;
    cout << "filter size = " << filterSize << endl;
    int matrixSize = filterSize * filterSize;
    int filterMidToEdge = (filterSize - 1) / 2;
    //int repeat1 = floor((double) Size1 / filterSize);
    //int repeat2 = floor((double) Size2 / filterSize);
    unsigned char filterArea[filterSize][filterSize];
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            //for (int k = 0; k < BytesPerPixel; k++)
            //{   
                int appearTimes[matrixSize];
                int appearvalue[matrixSize][3];
                int blankLoc = 1;
                // initialize the matrix
                for (int m1 = 0; m1 < matrixSize; m1++)
                {
                    appearTimes[m1] = 0;
                    for (int k = 0; k < BytesPerPixel; k++)
                    {
                        appearvalue[m1][k] = -1;
                    }
                    
                }
                //cout << "--------DEBUG: point " << i<<","<<j << "-----------" << endl;
                // set the most frequent color in its NxN neighbour
                for (int m2 = -filterMidToEdge; m2 <= filterMidToEdge; m2++)
                {   
                    for (int n = -filterMidToEdge; n <= filterMidToEdge; n++)
                    {
                        int valueOfTempLoc[3];
                        tempLocX = i + m2;
                        tempLocY = j + n;
                        valueOfTempLoc[0] = result1[tempLocX][tempLocY][0];
                        valueOfTempLoc[1] = result1[tempLocX][tempLocY][1];
                        valueOfTempLoc[2] = result1[tempLocX][tempLocY][2];
                        //cout << m2 << "," << n << endl;
                        if ((m2 == -filterMidToEdge) & (n == -filterMidToEdge)) 
                        {
                            appearvalue[0][0] = valueOfTempLoc[0];
                            appearvalue[0][1] = valueOfTempLoc[1];
                            appearvalue[0][2] = valueOfTempLoc[2];
                            appearTimes[0] = 1;
                            //cout << tempLocX <<"," << tempLocY << "->" << valueOfTempLoc << endl;
                        }
                        else 
                        {   
                            bool checkPoint = false;
                            if ((tempLocY < Size2) & (tempLocX < Size1))
                            {
                                //cout << tempLocX <<"," << tempLocY << "->" << valueOfTempLoc << endl;
                                for (int r = 0; r < matrixSize; r++)
                                {
                                    if ((appearvalue[r][0] == valueOfTempLoc[0]) & (appearvalue[r][1] == valueOfTempLoc[1]) & (appearvalue[r][2] == valueOfTempLoc[2]))
                                    {
                                        appearTimes[r]++;
                                        checkPoint = true;
                                    }
                                }
                                if (checkPoint == false)
                                {
                                    appearvalue[blankLoc][0] = valueOfTempLoc[0];
                                    appearvalue[blankLoc][1] = valueOfTempLoc[1];
                                    appearvalue[blankLoc][2] = valueOfTempLoc[2];
                                    appearTimes[blankLoc] = 1;
                                    blankLoc++;
                                }
                            }
                        } 
                    }           
                }
                // find the most frequent value's location
                int mostFrequentLoc = 0;  // initialize at first location
                int mostFrequentAmount = appearTimes[mostFrequentLoc];
                for (int m = 1; m < matrixSize; m++)
                {
                    if (appearTimes[m] > mostFrequentAmount)
                    {
                        mostFrequentLoc = m;
                        mostFrequentAmount = appearTimes[m];
                    }
                }
                result2[i][j][0] = (char) appearvalue[mostFrequentLoc][0];
                result2[i][j][1] = (char) appearvalue[mostFrequentLoc][1];
                result2[i][j][2] = (char) appearvalue[mostFrequentLoc][2];
                //cout << "final result = " << appearvalue[mostFrequentLoc] << endl;
            //}
        }
    }

    char out1[] = "Q2_part2_1.raw";
    string nValue = num2str(atoi(argv[3]));
    string out_str= "Q2_part2_N=" + nValue + "Color="+ num2str(colorAmount)+".raw";
    const char* out2 = out_str.c_str();
    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out1,"wb"))) {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result1, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(out2,"wb"))) {
        cout << "Cannot open file2: " << out2 << endl;
        exit(1);
    }
    fwrite(result2, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    return 0;
}
