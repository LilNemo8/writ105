#include "games.h"

void child_games(int input){
    int loading_timer = 2 + rand() % 6;
        
    switch (input) {
        case 1:
            loading("PONG", loading_timer); 
            execlp("pong/build/pong", "pong", (char*)NULL);
            break;
        case 2:
            loading("TETRIS", loading_timer); 
            execlp("tetris/tetris", "tetris", (char*)NULL);
            break;
        case 3:
            loading("SNAKE", loading_timer); 
            execlp("nsnake", "nsnake", (char*)NULL);
            break;
        case 4:
            loading("DOOM", loading_timer); 
            execlp("chocolate-doom", "chocolate-doom", (char*)NULL);
            break;
        case 5:
            loading("SPACE INVADERS", loading_timer); 
            execlp("ninvaders", "ninvaders", (char*)NULL);
            break;
        case 6:
            loading("PACMAN", loading_timer); 
            execlp("pacman4console", "pacman4console", (char*)NULL);
            break;
        case 7:
            loading("GREED", loading_timer); 
            execlp("greed", "greed", (char*)NULL);
            break;
        case 8:
            loading("2048", loading_timer); 
            execlp("2048", "2048", (char*)NULL);
            break;
        case 9:
            loading("SUDOKU", loading_timer); 
            execlp("nudoku", "nudoku", (char*)NULL);
            break;
        case 10:
            loading("HANGMAN", loading_timer); 
            execlp("hangman", "hangman", (char*)NULL);
            break;
        default:
            std::cerr << "Invalid choice.\n";
            _exit(1);
    }
    
    
    // If execlp returns, it failed:
    std::perror("exec error");
    _exit(1);
    
}

void games_intro(){
    type_chars("Alright, here are some of the games that you can play\n\n");
    type_chars("A sidenote, these games are not mine, you can find their original creators if you look at the readme of each game's folder. :D\n\n");

}

void games(){
    games_intro();

    
    int input = 0;

    while(true){

        std::cout << "Enter -1 to go back to main menu\n\n";

        std::cout << "1. PONG\n2. TETRIS\n3. SNAKE\n4. DOOM\n5. SPACE INVADERS\n6. PACMAN\n7. GREED\n8. 2048\n9. SUDOKU\n10. HANGMAN\n\n";
        std::cout << "Input: "; std::cin >> input;


        if(input == -1){ std::cout << "Leaving Games\n\n"; return;}        
    
        pid_t pid = fork();
        if (pid == -1) {
            std::perror("fork");
            return;
        } else if (pid == 0) {
            child_games(input);
        } else {
            wait(NULL);
            if(play_again("GAMES")){ continue; }
            else{ break; }

        }
    }

}
