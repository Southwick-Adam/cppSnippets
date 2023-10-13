#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string str);

int main(){
    string input;
    cout<<"Please enter a word: ";
    cin>>input;

    if (isPalindrome(input)){
        cout<<input<<" is a palindrome\n";
    }else{
        cout<<input<<" is not a palindrome\n";
    }
    return 0;
}

bool isPalindrome(string str){
    string reverseWord = "";
    for (int k = 0; k<str.length(); k++){
        reverseWord = str[k] + reverseWord;
    }
    if (reverseWord == str)
        return true;
    return false;
}