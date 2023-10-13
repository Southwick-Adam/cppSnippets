#include <iostream>
#include <string>
using namespace std;

int ASCIItoArray(char letter);
bool isLetter(char ch);

int main(){
    string input;
    int charArray[26];
    int words = 1; //every sentence has at least one word

    for (int n = 0; n<26; n++){
        charArray[n] = 0;
    }

    cout<<"Please enter a line of text:\n";
    getline(cin, input);

//handles empty input
    if (input == ""){
        cout<<"ERROR: PLEASE ENTER TEXT\n";
        return 0;
    }
//handles text input
    for (int k = 0; k < input.length(); k++){
        if (isLetter(input[k])){
            charArray[ASCIItoArray(input[k])]++;
        }else{
            if (k == input.length() - 1){ //if it end the sentence dont had a whole new word.
                break;
            }
            words++;
        }
    }

    cout<<words<<"\twords\n";

    for (int n = 0; n < 26; n++){
        if (charArray[n] != 0){
            cout<<charArray[n]<<"\t"<<char(n+97)<<endl;
        }
    }

    return 0;
}

int ASCIItoArray(char letter){
    int num;
    int ASCII = int(letter);
    if (ASCII < 91){
        num = ASCII - 65; //capitals
    }else{
        num = ASCII - 97; //lowercase
    }
    return num;
}

bool isLetter(char ch){
    if (ch ==' '||ch ==','||ch =='.'){
        return false;
    }
    return true;
}