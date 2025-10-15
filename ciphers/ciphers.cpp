#include "ciphers.h"


void ciphers(){
    int input;


    type_chars("Alright, here are some of ciphers that you can play\n\n");


    while(true){

        std::cout << "Enter -1 to go back to main menu\n\n";

        std::cout << "1. CAESAR\n2. SCYTALE\n\n";
        std::cout << "Input: "; std::cin >> input;


        if(input == -1){ std::cout << "Leaving CIPHERS\n\n"; return;}

        int loading_timer = 2 + rand() % 5;
        
        switch (input) {
            case 1:
                loading("CAESAR", loading_timer); 
                caesar();
                break;
            case 2:
                loading("SCYTALE", loading_timer); 
                scytale();
                break;
            default:
                std::cerr << "Invalid choice.\n";
                break;
        }

        char answer;
        while(true){
            std::cout << "Would you like to look at the other than CIPHERS? [Y/n]:";
            std::cin >> answer;
            if(answer == 'Y' || answer == 'n'){break;}
        }
        
        if(answer == 'Y'){ 
            std::cout<< "\nAlright let's look at some more CIPHERS :D \n\n";
            continue; 
        }else{
            break; 
        }

    }

};

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


void caesar(){
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


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


void scytale(){
    int input;

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
        for(int i = 0; i < row; i++){ std::cout<<grid[i][index]; }
        index++;
    }
    std::cout<<std::endl;
}

void decryption(std::string str, int row, int column, char operation){
    //creates a grid
    char** grid = createGrid(str, row, column, operation);
    
    //prints out the grid
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){ std::cout<<grid[i][j]; }
    }
    std::cout<<std::endl;

}