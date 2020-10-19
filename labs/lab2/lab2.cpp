/******************************************************************************
                              Lab Assignment 2
    Divide and Conquer, Sorting and Searching, and Randomized Algorithms
                                Coursera
October 19, 2020
Hauk Gu
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unsigned long long sortArray(int*, int, int);
void mergeArray(int*, int, int);
unsigned long long countInvert(int*, int, int);
void printArray(int*);

int main(void) {

    int fileSize = 100000;
    int data[fileSize];
    string infileName = "../IntegerArray.txt";
    string outfileName = "../sorted.txt";

    ifstream inFile;
    inFile.open(infileName);

    //read elements into array
    if (inFile.is_open()) {

        for (int i = 0; i < fileSize; i++)
            inFile >> data[i];

        inFile.close();
    }

    else
        cout << "Error: Failed to open file " << infileName << "!" << endl;

    //sort and count inversion with merge sort
    unsigned long long cnt = sortArray(data, 0, fileSize-1);
    //printArray(data);

    //2407905288
    cout << "Total number of inversions: " << cnt << endl;

    //output sorted array to file
    ofstream outFile(outfileName);
    if (outFile.is_open()) {

        for (int i=0; i<fileSize; i++)
            outFile << data[i] << endl;

        outFile.close();
    }
    else
        cout << "Error: Failed to open file " << outfileName << "!" << endl;

    return 0;
}

//merge sort
unsigned long long sortArray(int* data, int startInd, int endInd) {

    unsigned long long cnt = 0;

    //base case
    if (startInd == endInd)
        return cnt;

    int pivotR = (startInd + endInd + 1) / 2;
    int pivotL = pivotR - 1;

    //count inversions on left subarray
    unsigned long long cntL = sortArray(data, startInd, pivotL);

    //count inversions on right subarray
    unsigned long long cntR = sortArray(data, pivotR, endInd);

    //merge
    //mergeArray(data, startInd, endInd);

    //merge and count split inversions
    unsigned long long cntS = countInvert(data, startInd, endInd);

    cnt = cntL + cntR + cntS;
    return cnt;
}

//merge sort
//merge left and right subarray
void mergeArray(int* data, int startInd, int endInd) {

    int length = endInd - startInd + 1;

    int pivotR = (startInd + endInd + 1) / 2;
    int pivotL = pivotR - 1;

    //auxiliary array to store sorted elements
    int c[length];

    //start index of left subarray
    int i=startInd;

    //start index of right subarray
    int j=pivotR;

    for (int k=0; k<length; k++) {

        //end cases
        if (i == pivotL + 1) {
            if (j < endInd + 1) {

                //remaining elements of right subarray
                c[k] = data[j];
                j++;
            }
        }
        else if (j == endInd + 1) {
            if (i < pivotL + 1) {

                //remaining elements of left subarray
                c[k] = data[i];
                i++;
            }
        }

        //normal cases
        else if (data[i] < data[j]) {
            c[k] = data[i];
            i++;
        }
        else if (data[j] < data[i]) {
            c[k] = data[j];
            j++;
        }
    }

    //copy sorted elements back to input array
    for (int m=0; m<length; m++) {

        data[startInd + m] = c[m];
    }

    return;
}

//modified version of mergeArray
//merge and count split inversions
unsigned long long countInvert(int* data, int startInd, int endInd) {

    unsigned long long cnt = 0;
    int length = endInd - startInd + 1;

    int pivotR = (startInd + endInd + 1) / 2;
    int pivotL = pivotR - 1;

    //auxiliary array to store sorted elements
    int c[length];

    //start index of left subarray
    int i=startInd;

    //start index of right subarray
    int j=pivotR;

    for (int k=0; k<length; k++) {

        //end cases
        if (i == pivotL + 1) {
            if (j < endInd + 1) {

                //remaining elements of right subarray
                c[k] = data[j];
                j++;
            }
        }
        else if (j == endInd + 1) {
            if (i < pivotL + 1) {

                //remaining elements of left subarray
                c[k] = data[i];
                i++;
            }
        }

        //normal cases
        else if (data[i] < data[j]) {
            c[k] = data[i];
            i++;
        }
        else if (data[j] < data[i]) {
            c[k] = data[j];
            j++;

            //the split inversions involving an element of the right subarray
            //are precisely the number left in the left subarray
            //when the element is copied to the output array
            cnt += pivotL + 1 - i;
        }
    }

    //copy result back to input array
    for (int m=0; m<length; m++) {

        data[startInd + m] = c[m];
    }

    return cnt;
}

void printArray(int* data) {

    cout << data[0] << " " << data[1] << " " << data[99999] << endl;
    return;
}

//end of file
