#include <iostream>
#include <vector>
using namespace std;

int main1();
int main2();
void resize(int *&arr, int size, int newSize);

int main(){
    cout<<"\nVERSION 1:\n";
    main1();
    cout<<"\nVERSION 2:\n";
    main2();
    return 0;
}

int main1(){
    int arrSize = 1;
    int *ptr = new int [arrSize];
    int search;

    cout<<"Please enter a sequence of positive integers, each in a separate line.\n";
    cout<<"End your input by typing -1.\n";
    int test = 0;
    int count = 0;
    while (test != -1){
        int num;
        cin>>num;
        ptr[count] = num;
        test = num;
        count++;
        if (count >= arrSize){
            int newSize = arrSize * 2;
            resize(ptr, arrSize, newSize);
            arrSize = newSize;
        }
    }
    cout<<"Please enter a number you want to search:\n";
    cin>>search;

    int searchCount = 0;
    for (int k = 0; k < arrSize; k++){
        if (ptr[k] == search){
            searchCount++;
        }
    }

    int lines[searchCount];
    int n = 0;
    for (int l = 0; l < arrSize; l++){
        if (ptr[l] == search){
            lines[n] = (l+1);
            n++;
        }
    }
    
    if (searchCount <= 0){
        cout<<search<<" is not in any lines.\n";
    }else{
        cout<<search<<" shows in lines ";
        for (int n = 0; n < searchCount; n++){
            cout<<lines[n];
            if (n == searchCount-1){
                cout<<"."<<endl;
            }else{
            cout<<", ";
            }
        }
    }

    delete [] ptr;
    return 0;
}

void resize(int *&arr, int size, int newSize){
    int *tempPtr = new int [newSize];
    for (int k = 0; k < size; k++){
        tempPtr[k] = arr[k];
    }
    delete [] arr;
    arr = tempPtr;
}

int main2(){
    vector<int> input;
    vector<int> lines;
    int search;

    cout<<"Please enter a sequence of positive integers, each in a separate line.\n";
    cout<<"End your input by typing -1.\n";
    int test = 0;
    while (test != -1){
        int num;
        cin>>num;
        input.push_back(num);
        test = num;
    }
    cout<<"Please enter a number you want to search:\n";
    cin>>search;

    for (int k = 0; k < input.size(); k++){
        if (input[k] == search){
            lines.push_back(k+1);
        }
    }

    if (lines.size() <= 0){
        cout<<search<<" is not in any lines.\n";
    }else{
        cout<<search<<" shows in lines ";
        for (int n = 0; n < lines.size(); n++){
            cout<<lines[n];
            if (n == lines.size()-1){
                cout<<"."<<endl;
            }else{
            cout<<", ";
            }
        }
    }

    return 0;
}