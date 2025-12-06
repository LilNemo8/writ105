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
        
        break;
    }

    type_chars("\nQuick question before we begin, would you like Mat to guide you through the Interactive Environment?\n");
    mathew = new mat();
    
    while(true){
        std::cout << "1. Yes\n2. No\n3. Who's Mat?\n\n";
        std::cout<< "Input: "; std::cin >> input;
        
        if(input == 1){
            type_chars("Alright then mat will be accompanying you throughout the interactive environment\n"); sleep(2);
            mathew->update_existence();
            mathew->manager_dialogue(1);
            return;
        }else if(input == 2){
            break;
        }else if(input == 3){
            type_chars("\nMathew is a character that will guide you througout the interactive enviroment.\n"); sleep(2);
        }else{type_chars("\nThat is not an option. Please try again.\n"); sleep(2);}
    }

    type_chars("Alright then, Let's get started\n");


    
}

void main_menu(int input){
    while(true){    
        if(mathew->exists()){ mathew->manager_dialogue(2); }
        else{ type_chars("Here are the following options you can explore :D\n "); sleep(1); }
        
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

    if(mathew->exists()){
        mathew->manager_dialogue(3);
    }else{
        type_chars("Alright then, thanks for checking out my project :D");
        type_chars("Hope to see you again!");
    }

    delete mathew;


    return 0;
}
