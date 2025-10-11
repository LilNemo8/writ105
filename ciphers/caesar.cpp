#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <thread>
#include <unistd.h>



void type_chars(const std::string& text, std::chrono::milliseconds per_char = std::chrono::milliseconds(40), bool newline_at_end = true) {
    for (char c : text) {
        std::cout << c << std::flush;
        using namespace std::chrono_literals;
        if (c == ' ' || c == '\n') std::this_thread::sleep_for(per_char / 3);
        else if (c == '.' || c == '!' || c == '?' || c == ',') std::this_thread::sleep_for(per_char * 6);
        else std::this_thread::sleep_for(per_char);
    }
    if (newline_at_end) std::cout << '\n';
}


void invalid_argument(){
    std::cout << "USAGE: caesar [-ed] [key]\n";
    exit(1);
}

std::map<char, char> alphabet_rotation(char procedure, unsigned int displacement){
    int direction = (procedure == 'e') ? 1 : -1;
    int end_point = (procedure == 'e') ? 0 : 25;
    char cut_off =  (procedure == 'e') ? 'z' : 'a';
    int displaced_index = (procedure == 'e') ? displacement % 26 : 26-displacement % 26; 

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    char* regular = &alphabet[0];
    char* displaced = &alphabet[displaced_index];

    std::map<char, char> rotated;
    for(size_t i = 0; i < 26; i++){
        rotated[*regular] = *displaced;
        
        if(*regular == cut_off){regular = &alphabet[end_point];} else{regular+=direction;}
        if(*displaced == cut_off){displaced = &alphabet[end_point];} else{displaced+=direction;}
    }

    return rotated;
}

std::string cipher(char procedure, unsigned int displacement, std::string& input){
    std::map<char, char> alphabet = alphabet_rotation(procedure, displacement);

    std::string result;
    char chr;
    
    for(char& s : input){
        bool upper = false;

        if(islower(s)){ chr = s; }
        else{ chr = tolower(s); upper = true; }

        auto it = alphabet.find(chr);

        if(it != alphabet.end()){ // this means that we have found an alphabetic character
            if(upper){ result += toupper(alphabet[chr]); }
            else{ result += alphabet[chr]; }
        }else{
            result += chr;
        }
    }

    return result;
}


int main(){
    int input, displacement;
    char procedure;
    

    type_chars("\nWelcome to the Caesar cipher!!");

    std::cout << "\n1. START using Caesar Cipher\n2. How to use Caesar Cipher\n\n";
    std::cout << "Input: "; std::cin >> input;

    if(input == 2){
        type_chars("The way this cipher works is by shifiting each letter in the alphabet by a fixed number of positions");
        type_chars("This program will first as for 2 inputs.\n1.Encrypting or Decrypting.\n2. Shift Amount");
        type_chars("Encryption will shift the alphabet to the left and Decryption will shift the alphabet to the right\nHere is an example:\n");

        std::cout << "First Input: Encryption\nSecond Input: 3\nabcdefghijklmnopqrstuvwxyz\ndefghijklmnopqrstuvwxyzabc\nVeni, vidi, vici.\nYhql, ylgl, ylfl.\n\n";
        sleep(3);
    }

    type_chars("Alright let's get started\n\n");

    while(true){

        std::cout << "1. Encryption\n2. Decyption\n\n";
        
        std::cout << "Input: "; std::cin >> input;
        
        if(input == 1){ procedure = 'e'; }
        else if(input == 2){ procedure ='d'; }
        else{ std::cout << "Invalid Input. Please try again \n\n"; continue;}

        break;
    }
    while(true){

        std::cout << "\nEnter shift amount: "; std::cin >> input;
        
        if(input < 0){ std::cout << "Invalid Input. Enter non-negative number. Please try again\n\n"; continue; }
        
        displacement = input;
        
        break;
    }    
        
    std::string sentence;
    std::cout << "\nEnter sentence to cipher (type 'quit' to leave)\n";
    while(std::getline(std::cin, sentence)){
        if(sentence == "quit"){ break; }
        std::cout << cipher(procedure, displacement, sentence)<< "\n\n";
    }


    return 0;
}

