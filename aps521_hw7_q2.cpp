#include <iostream>
#include <string>
using namespace std;

void buildArray(string input, int arr[], int &count);

int main(){
    string input1, input2;
    int arr1[26], arr2[26];
    int arrCount1 = 0, arrCount2 = 0;

    for (int n = 0; n<26; n++){
        arr1[n] = 0;
        arr2[n] = 0;
    }

    cout<<"Please enter the first sentence:\n";
    getline(cin, input1);
    cout<<"Please enter the second sentence:\n";
    getline(cin, input2);

    buildArray(input1, arr1, arrCount1);
    buildArray(input2, arr2, arrCount2);

    if (arrCount1 != arrCount2){
        cout<<"They are not Anagrams\n";
        return 0;
    }

    for (int n = 0; n < 26; n++){
        if (arr1[n] != arr2[n]){
            cout<<"They are not Anagrams\n";
            return 0;
        }
    }

    cout<<"They are Anagrams\n";

    return 0;
}

void buildArray(string input, int arr[], int &count){
    for (int k = 0; k < input.length(); k++){
        int ASCII = int(input[k]);
        //if the character is a letter
        if (ASCII > 64 && ASCII < 91){//capital
            arr[ASCII - 65]++;
            count++;
        } else if (ASCII > 96 && ASCII < 123){//lowercase
            arr[ASCII - 97]++;
            count++;
        }
    }
}