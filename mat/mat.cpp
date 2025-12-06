#include "mat.h"
#include "../helper/functions.h"

mat::mat(){
    exist = false;
    color = "cyan";
}

void mat::manager_dialogue(int dialogue){
    std::cout << setColor(color);
    switch(dialogue){
        case 1:
            type_chars("\nAye what's up, my name is Mat and I will guide you through the environment :D\n");
            type_chars("Also a heads up, if things get buggy are dont work just press CRTL + Z to terminate the program and start again\n");
            type_chars("Yea sorry if you have to do :|\n");sleep(2);
            break;
        case 2:
            type_chars("\nHere are the options and as you can see there are 4. \n");
            type_chars("To be honest with you bro, only the first two, Visuals and Games, are fully complete :D\n");
            type_chars("The creator of this environment got a little lazy with Ciphers and hasn't finished it :|\n");
            type_chars("The fourth option might not work for you since you have to download the AI in the first place :(\n");
            type_chars("Anyways, lets get at it :)\n");
            break;
        case 3:
            type_chars("\nthanks for playing this interactive simulation :D\n");
            type_chars("the creator sends his regards and will continue to work on this project during the winter :}\n");
            type_chars("GoodBye\n");
            break;
    }
    std::cout << setColor("white");
}

void mat::visuals_dialogue(int dialogue){
    std::cout << setColor(color);

    switch(dialogue){
        case 1:
            type_chars("\nNice Choice bro, Welcome to visuals. Ima show you the options and then if you want more information input 0\n");
            break;
        case 2:
            type_chars("\n1. Shows a Matrix style display, its like from the movie: The Matrix");
            type_chars("2. It is an aquarium/sea animation in ASCII art created using perl");
            type_chars("3. Creates a visually engaging, hacker-movie-like terminal interface with multiple windows and animated text");
            type_chars("4. Displays 3 rotating donut animated in ASCII art");
            type_chars("5. Displays 3 rotating cubes animated in ASCII art");
            type_chars("6. shows you an animated steam train\n"); 
            break;
        case 3:
            std::vector<std::string> visuals = {"CMATRIX", "AQUARIUM", "HOLLYWOOD", "DONUT", "CUBE", "STEAM LOCOMOTIVE"};
            int randomNum = rand() % 6;
            type_chars("\nWell I hope you had fun, me personally my favorite game to play was " + visuals[randomNum]); std::cout << '\n';
            break;
    }
    std::cout << setColor("white");
}

void mat::games_dialogue(int dialogue){
    std::cout << setColor(color);

    switch(dialogue){
        case 1:
            type_chars("Now we are at the games. these are honestly pretty fun. :D\n");
            type_chars("A little side not as well, the creator of this environment did not create these games. :O\n");
            type_chars("If he did, he would not only fail but it would take too long yk. XD\n");
            type_chars("last note, the games are pretty self explanatory and some of them have descriptions within the game :)\n");
            break;
        case 2:
            std::vector<std::string> games = {"PONG", "TETRIS", "SNAKE", "DOOM", "SPACE INVADERS", "PACMAN", "GREED", "2048", "SUDOKU", "HANGMAN"};
            int randomNum = rand() % 10;
            type_chars("Well I hope you had fun, me personally my favorite game to play was " + games[randomNum]); std::cout << '\n';

            break;
    }
    std::cout << setColor("white");
}



void mat::update_existence(){ exist = true; };

bool mat::exists(){ return exist; }

