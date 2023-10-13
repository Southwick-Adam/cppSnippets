#include <iostream>
using namespace std;

int* findMissing(int arr[], int n, int& resArrSize);

int main(){
    int arrSize;
    cout<<"Please enter the size of your array: ";
    cin>>arrSize;

    int inputArr[arrSize];
    cout<<"Please enter integers from 0 to "<<arrSize<< " sperated by new lines:\n";
    for (int k = 0; k<arrSize; k++){
        int input;
        cin>>input;
        inputArr[k] = input;
    }

    int resArrSize = 0;
    int *ptr = findMissing(inputArr, arrSize, resArrSize);

    cout<<"Missing numbers: [ ";
    for (int m = 0; m < resArrSize; m++){
        int num = ptr[m];
        cout<<num<<" ";
    }
    cout<<"]\n";
    delete [] ptr;
    return 0;
}

int* findMissing(int arr[], int n, int &resArrSize){
    bool missing[n+1];
    for (int m = 0; m <= n; m++){
        missing[m] = true;
    }
    resArrSize = n+1;
    for (int k = 0; k < n; k++){
        int num = arr[k];
        if (missing[num]){
            missing[num] = false;
            resArrSize--;
        }
    }
    int *missArr = new int [resArrSize];
    int missCount = 0;
    for (int l = 0; l <= n; l++){
        if (missing[l]){
            missArr[missCount] = l;
            missCount++;
        }
    }
    return missArr;
}