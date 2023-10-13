#include <iostream>
using namespace std;

int findPath(int arr[], int arrSize);

int main(){
    const int size = 6;
    int arr[size] = {0, 3, 80, 6, 57, 10};

    cout<<"the shortest path is ";
    cout<<findPath(arr, size)<<endl;

    return 0;
}

int findPath(int arr[], int arrSize){
    int size = arrSize - 1;
    if (size <= 1){
        return arr[size];
    }else{
        int minus1 = arr[size - 1];
        int minus2 = arr[size - 2];
        if (minus1 < minus2){
            return arr[size] + findPath(arr, size);
        }
        return arr[size] + findPath(arr, size-1);
    }
}