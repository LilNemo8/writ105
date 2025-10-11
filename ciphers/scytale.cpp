#include <iostream>
#include <string>
#include <cstring>
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



char** createGrid(std::string str, int rows, int columns, char operation){
    //creates 2d array
    char** grid = new char*[rows];
    for(int i = 0 ; i < rows; i++){
        grid[i] = new char[columns];
    }

    //if the operation is -e
    if(operation == 'e'){
        int index = 0;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(index >= (int)str.length()){
                    grid[i][j] = ' ';
                }else{
                    grid[i][j] = str[index];
                }
                index++;
            }
        }
    //if the operation is -d
    }else if(operation == 'd'){
        int index_str = 0;
        int index_chr = 0;
        //will go up to down, left to right
        while(index_chr <= columns){
            for(int i = 0; i < rows; i++){
                //adds space if necessary
                if(index_str >= (int)str.length()){
                    grid[i][index_chr] = ' ';
                }else{
                    grid[i][index_chr] = str[index_str]; 
                }
                index_str++;
            }
            index_chr++;
        }
    }
    //returns the grid
    return grid;


}

void encryption(std::string str, int row, int column, char operation){
    //creates a grid
    char** grid = createGrid(str, row, column, operation);


    //prints out the grid
    int index = 0;
    while(index < column){
        for(int i = 0; i < row; i++){
            std::cout<<grid[i][index]; 
        }
        index++;
    }

    std::cout<<std::endl;



}

void decryption(std::string str, int row, int column, char operation){
    //creates a grid
    char** grid = createGrid(str, row, column, operation);
    
    //prints out the grid
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            std::cout<<grid[i][j];
        }
    }
    std::cout<<std::endl;

}


int main(){
    int input, displacement;

    type_chars("\nWelcome to the Scytale cipher!!");

    std::cout << "\n1. START using Scytale Cipher\n2. HOW to use Scytale Cipher\n\n";
    std::cout << "Input: "; std::cin >> input;

    if(input == 2){
        type_chars("The way this cipher works is by wrapping a sentence around a rod, writes the message along the rod, then unwraps it so letters are scrambled—only a rod of the same diameter rewraps it to reveal the text.");
        type_chars("This program will first as for 2 inputs.\n\n1. Encrypting or Decrypting.\n2. Height of Grid.\n\n");
        sleep(1);

        type_chars("------Encryption example------\n");
        type_chars("First Input: Encryption\nSecond Input: 3\n");
        type_chars("If the following sentence is inputted: ''Twas brillig, and the slithy toves' then syctale would make the following grid:\n");
        type_chars("'Twas brilli\ng, and the s\nlithy toves\n\n");
        type_chars("And the output would be ''glT,iw taahsny d b trtoihvleel sis·'\n");
        type_chars("Encryption works by going top to bottom, left to right\n\n");

        sleep (1);

        type_chars("------Decryption example------\n");
        type_chars("First Input: Decryption\nSecond Input: 7\n");
        type_chars("If the following sentence is inputted: 'Aiwtov lmehre lsreos  ye g, m  bo' then syctale would make the following grid:\n");
        type_chars("All m\nimsy·\nwere·\nthe b\norogo\nves,\n     \n");
        type_chars("And the output will be 'All mimsy were the borogoves      ' (notice the spaces at the end)\n");
        type_chars("Decrypted works by going left to right, top to bottom\n\n");

        std::cout <<"(Note that when the key is one, or when it is greater than or equal to the length of the message, the input will be unchanged)\n"; 
        std::cout << "To learn more go to Scytale Cipher Wikipedia\n\n";

        sleep(3);
    }

    type_chars("Alright let's get started\n\n");
    char procedure;

    while(true){

        std::cout << "1. Encryption\n2. Decyption\n\n";
        
        std::cout << "Input: "; std::cin >> input;
        
        if(input == 1){ procedure = 'e'; }
        else if(input == 2){ procedure ='d'; }
        else{ std::cout << "Invalid Input. Please try again \n\n"; continue;}

        break;
    }
    while(true){

        std::cout << "\nEnter Grid Height amount: "; std::cin >> input;
        
        if(input < 0){ std::cout << "Invalid Input. Enter non-negative number. Please try again\n\n"; continue; }
        
        displacement = input;
        
        break;
    }    

    std::string sentence;
    std::cout << "\nEnter sentence to cipher (type 'quit' to leave):";

    while(std::getline(std::cin, sentence)){
        if(sentence == "quit"){ break; }
        
        int str_columns = (int) (( (double) ((int)sentence.length()) / input) +.5);

        if(procedure == 'e'){encryption(sentence, input, str_columns, procedure);}
        else if(procedure == 'd'){decryption(sentence, input, str_columns ,procedure);}
    }
    return 0;

}