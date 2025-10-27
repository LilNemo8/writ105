#include "helper/functions.h"
#include "visuals/visuals.h"
#include "games/games.h"
#include "ciphers/ciphers.h"
#include "deepseek/deepseek.h"

// Just a little touch

void intro(int input){
    std::cout << "--------------------------------------------------\n";
    std::cout << "   Welcome to My Interactive Environment Project\n";
    std::cout << "--------------------------------------------------\n\n"; sleep(1);

    type_chars("1. Get Started\n2. More info\n");


    
    while(true){
        std::cout<< "Input: "; std::cin >> input;

        if(input != 1 && input != 2){continue;}

        if(input == 2){
            type_chars("This project brings together a collection of demos:\n"); sleep(1);
            type_chars("  * Console-based visual effects and animations"); sleep(1);
            type_chars("  * Retro-inspired games and puzzles"); sleep(1);
            type_chars("  * Cipher tools that showcase basic encryption logic\n"); sleep(1);
            type_chars("It's designed as a modular environment to explore and uses different programming concepts through play.\n"); sleep(3);
        }
        type_chars("\nGreat, Let us begin\n"); sleep(1);

        break;
    }
}

void main_menu(int input){
    while(true){    
        type_chars("Here are the following options you can explore :D\n "); sleep(1);
    
    
        while(true){
            type_chars("1. Visuals\n2. Games\n3. Ciphers\n4. DeepSeek\n");
    
            type_chars("Enter -1 to exit\n");
    
            std::cout << "Input: "; std::cin >> input;
    
            if(input == 1){  visuals(); }
            else if(input == 2){ games(); }
            else if(input == 3){ ciphers(); }
            else if(input == 4){ deepseek(); }
            else if(input == -1){ return; }
            else {type_chars("That isn't an option\n\n"); continue;}
    
            std::cout << "MAIN MENU\n\n";
        }
        
    }

}


int main() {
    clear_terminal();

    int input = 0;

    intro(input);
    main_menu(input);

    type_chars("Alright then, thanks for checking out my project :D");
    type_chars("Hope to see you again!");
    return 0;
}
