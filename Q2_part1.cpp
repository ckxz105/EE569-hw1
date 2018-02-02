// EE569 Homework Assignment #1
// Date: 2018.1.29
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath> // use for pow function
#include <algorithm>  // use max and min algorithm
#include <fstream>  
using namespace std;

// define some const values
const int BytesPerPixel = 3, Size1 = 400, Size2 = 300, colorByte = 8;
int byteRange = pow(2, colorByte);
unsigned char result3[400][300][3];
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
        void translate(int layer);
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
void Table::translate(int layer)
{
    
    int totalPixel = Size1 * Size2;
    int totalCount = 0;
    int tempCount = 0;
    int threshold = (totalPixel / byteRange) + 1;
    int tempVal = 0;
    int i = 0;
    Node *p = histInfo[0];
    //cout << "threshold = " << threshold << endl;
    // repeat until all points are reallocated
    while (totalCount < totalPixel)
    {
        if (i >= byteRange)
        {
            break;
        }
        if (tempCount < threshold)
        {
            int tempX = p->xaxis;
            int tempY = p->yaxis;
            // debug purpose
            //cout << tempX << "," << tempY << "->" << tempVal << endl;
            //cout << "total pixel used = " << totalCount << "||| temp cound = " <<tempCount<< endl;
            result3[tempX][tempY][layer] = (char) tempVal;
            tempCount++;
            totalCount++;
            
            // go to next position
            if (p->next == NULL)
            {
                i++;
                p = histInfo[i];
            }
            else
            {
                p = p->next;
            }
        }
        // if one pixel value's target amount is enough, go to next one
        else
        {
            tempCount = 0;
            tempVal++; 
        }
        
    }



}

// main function
int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file;
    class Node;
    typedef Node * ListType;
    ListType * histInfo;

    // Allocate image data array
    unsigned char Imagedata[Size1][Size2][BytesPerPixel];
    unsigned char result1[Size1][Size2][BytesPerPixel];
    unsigned int histogram[byteRange][BytesPerPixel];
    unsigned int histogram_a[byteRange][BytesPerPixel];
    unsigned int histogram_b[byteRange][BytesPerPixel];
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

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    // initialize the histogram matrix
    for (int i = 0; i < byteRange; i++) 
    {
        for (int k = 0; k < BytesPerPixel; k++) 
        {
            histogram[i][k] = 0;

        }

    } 

    // start traverse the whole image
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++) 
            {
                int temp = ((int)Imagedata[i][j][k]);
                // generate the histogram information
                histogram[temp][k]++;
                
                // apply the transfer-function-based histogram equalization method
                // for Red
                if (k == 0) 
                {
                    result_R->insert(i,j,temp);
                    if (temp < 23)
                    {
                        result1[i][j][k] = (char) ((int) temp * 8.5);
                    }
                    else if (temp > 250)
                    {
                        result1[i][j][k] = Imagedata[i][j][k];
                    }

                    else
                    {
                        double temp2 = (double) 62 / 227 * temp + 181.7180617;
                        result1[i][j][k] = (char) ((int) temp2);
                    }
                }
                // for green
                else if (k == 1)
                {   
                    result_G->insert(i,j,temp);
                    if (temp < 22)
                    {
                        result1[i][j][k] = (char) (temp * 9);
                    }
                    else if (temp > 250)
                    {
                        result1[i][j][k] = Imagedata[i][j][k];
                    }

                    else
                    {
                        double temp2 = (double) 61 / 228 * temp + 183.1140351;
                        result1[i][j][k] = (char) ((int) temp2);
                    }
                }
                // for blue
                else 
                {
                    result_B->insert(i,j,temp);
                    if (temp < 17)
                    {
                        result1[i][j][k] = (char) (temp * 11);
                    }
                    else if (temp > 250)
                    {
                        result1[i][j][k] = Imagedata[i][j][k];
                    }

                    else
                    {
                        double temp2 = (double) 62 / 232 * temp + 183.1896552;
                        result1[i][j][k] = (char) ((int) temp2);
                    }
                }

            }
        }
    }
    unsigned char aa[Size1][Size2];
    //result_R->printAll();
    result_R->translate(0);
    result_G->translate(1);
    result_B->translate(2);

    int temp = 0;
    // get the histogram of translated image of method (a)
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++) 
            {
                temp = ((int)result1[i][j][k]);
                // generate the histogram information
                histogram_a[temp][k]++;

                temp = ((int)result3[i][j][k]);
                // generate the histogram information
                histogram_b[temp][k]++;
            }
        }
    }

    char out1[] = "Q2_Histogram_of_Org.txt", out2[] = "Q2_result_method_A.raw", out3[] = "Q2_result_method_B.raw", out4[] = "Q2_Histogram_method_A.txt", out5[] = "Q2_Histogram_method_B.txt";

    // Write image data (filename specified by second argument) from image data matrix
    fstream f1,f2,f3;
    f1.open(out1,fstream::out);
    if (f1.is_open())
    {
        for (int j = 0; j < BytesPerPixel; j++) 
        {
            f1 << j << endl;
            for (int i = 0; i < byteRange; i++) 
            {
                f1 << i << "," << histogram[i][j]<< endl;
            } 
        }
    }
    f1.close();

    f2.open(out4,fstream::out);
    if (f2.is_open())
    {
        for (int j = 0; j < BytesPerPixel; j++) 
        {
            f2 << j << endl;
            for (int i = 0; i < byteRange; i++) 
            {
                f2 << i << "," << histogram_a[i][j]<< endl;
            } 
        }
    }
    f2.close();

    f3.open(out5,fstream::out);
    if (f3.is_open())
    {
        for (int j = 0; j < BytesPerPixel; j++) 
        {
            f3 << j << endl;
            for (int i = 0; i < byteRange; i++) 
            {
                f3 << i << "," << histogram_b[i][j]<< endl;
            } 
        }
    }
    f3.close();
  
    if (!(file = fopen(out2,"wb"))) {
        cout << "Cannot open file2: " << out2 << endl;
        exit(1);
    }
    fwrite(result1, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    // Write image data (filename specified by second argument) from image data matrix
    
    if (!(file = fopen(out3,"wb"))) {
        cout << "Cannot open file3: " << out3 << endl;
        exit(1);
    }
    fwrite(result3, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    //fwrite(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    cout << "Finished!" << endl;
    return 0;
}
