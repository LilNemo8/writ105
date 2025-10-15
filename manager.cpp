#include "helper/functions.h"
#include "visuals/visuals.h"
#include "ciphers/ciphers.h"

#include <iostream>
#include <unistd.h>     // fork(), exec(), sleep()
#include <sys/wait.h>   // waitpid()
#include <signal.h>     // kill(), SIGTERM
#include <string>
#include <chrono>
#include <thread>
#include <sstream>

// Just a little touch
void sad_Goodbye(){
    std::cout << '\n';
    
    const int maxDots = 3;
    int d = 1; 
    int x = 3;
    while (x!=0) {
        std::cout << "\rOh" << std::string(d, '.') << std::string(maxDots - d, ' ')  << std::flush;
        sleep(1);
        d = (d + 1) % (maxDots + 1); 
        x--;
    } sleep(1);

    type_chars("okay then\n"); sleep(1);
    type_chars("goodbye :( \n"); sleep(1);
    
    exit(1); 
}


/*
// COOL visuals or some
void visuals() {


    int input;
    std::cout << "\n\nGREAT! Here are some choices that you can see (INPUT 0 FOR MORE INFORMATION)\n\n";

    while(true){
        int process_timer = 8;

        std::cout << "Enter -1 to go back to main menu\n\n";
        std::cout << "1. CMATRIX\n2. AQUARIUM\n3. HOLLYWOOD\n4. STEAM LOCOMOTIVE\n\n";
        std::cout << "Input: "; std::cin >> input;

        if(input == -1){
            std::cout << "Leaving Visuals\n\n";
            return;
        }else if(input == 0){
            std::cout << "1. Gives a 'Matrix'-style display, where a rain of green characters streams down the screen\n";
            std::cout << "2. It is an aquarium/sea animation in ASCII art created using perl\n";
            std::cout << "3. Creates a visually engaging, hacker-movie-like terminal interface with multiple windows and animated text\n";
            std::cout << "4. shows you an animated steam train\n\n"; 
            std::cout << "Input: "; std::cin >> input;
        }
        
        // Decide timing *before* fork so the parent sees it.
        bool timed = (input == 1 || input == 2 || input == 3);

        if(timed){
            std::cout << "How long would you like to display #" << input << " for in seconds? (defualt = 8s): ";
            std::cin >> process_timer;
        }
        
        int loading_timer = 2 + rand() % 7;
        
        pid_t pid = fork();

        if (pid == -1) {
            std::perror("fork");
            return;

        } else if (pid == 0) {
            switch (input) {
                case 1:
                    loading("CMATRIX", loading_timer); 
                    execlp("cmatrix", "cmatrix", (char*)NULL);
                    break;
                case 2:
                    loading("AQUARIUM", loading_timer); 
                    execlp("asciiquarium", "asciiquarium", (char*)NULL);
                    break;
                case 3:
                    loading("HOLLYWOOD", loading_timer); 
                    execlp("hollywood", "hollywood", (char*)NULL);
                    break;
                case 4:
                    loading("STEAM LOCOMOTIVE", loading_timer); 
                    execlp("sl", "sl", (char*)NULL);
                    break;
                default:
                    std::cerr << "Invalid choice.\n";
                    _exit(1);
            }
            // If we got here, exec failed.
            std::perror("exec error");
            _exit(1);

        } else {
            // --- Parent: optionally time-limit the child ---
            int status = 0;

            if (timed) {
                sleep((loading_timer + process_timer));
                if (kill(pid, SIGTERM) == -1) {
                    std::perror("kill(SIGTERM)");
                }

                // Give it a moment to die gracefully
                for (int i = 0; i < 20; ++i) { // ~2 seconds in 100ms steps
                    pid_t r = waitpid(pid, &status, WNOHANG);
                    if (r == pid) break;
                    usleep(100000);
                }

                // If still alive, force-kill
                if (waitpid(pid, &status, WNOHANG) == 0) {
                    kill(pid, SIGKILL);
                }
            }
            
            wait(NULL);
            char answer;
            while(true){
                std::cout << "Would you like to look at the other than VISUALS? [Y/n]:";
                std::cin >> answer;
                if(answer == 'Y' || answer == 'n'){break;}
            }

            if(answer == 'Y'){ 
                std::cout<< "\nAlright lets look at some more VISUALS :D \n\n";
                continue; 
            }else{
                break; 
            }
        }
        
    }
}
*/

//Some games that you can play, these are not mine
void games(){
    int input;


    type_chars("Alright, here are some of the games that you can play\n\n");
    type_chars("A sidenote, these games are not mine, you can find their original creators if you look at the readme of each game's folder. :D\n\n");

    while(true){

        std::cout << "Enter -1 to go back to main menu\n\n";

        std::cout << "1. Pong\n2. Tetris\n3. Snake\n\n";
        std::cout << "Input: "; std::cin >> input;


        if(input == -1){ std::cout << "Leaving Games\n\n"; return;}

        int loading_timer = 2 + rand() % 6;
        
    
        pid_t pid = fork();
        if (pid == -1) {
            std::perror("fork");
            return;
        } else if (pid == 0) {
            switch (input) {
                    case 1:
                        loading("PONG", loading_timer); 
                        execlp("games/pong/build/pong", "pong", (char*)NULL);
                        break;
                    case 2:
                        loading("TETRIS", loading_timer); 
                        execlp("games/tetris/tetris", "tetris", (char*)NULL);
                        break;
                    case 3:
                    loading("SNAKE", loading_timer); 
                    execlp("games/snake/sgt", "sgt", (char*)NULL);
                    break;
                    // case 3:
                    //     loading("", loading_timer); 
                    //     execlp("", "", (char*)NULL);
                    //     break;
                    default:
                        std::cerr << "Invalid choice.\n";
                        _exit(1);
                }


            // If execlp returns, it failed:
            std::perror("exec error");
            _exit(1);
        } else {

            
            wait(NULL);
            char answer;
            while(true){
                std::cout << "Would you like to look at the other than GAMES? [Y/n]:";
                std::cin >> answer;
                if(answer == 'Y' || answer == 'n'){break;}
            }
            
            if(answer == 'Y'){ 
                std::cout<< "\nAlright lets look at some more GAMES :D \n\n";
                continue; 
            }else{
                break; 
            }

        }
    }

}

/*
// Ciphers that I made
void ciphers(){
    int input;


    type_chars("Alright, here are some of ciphers that you can play\n\n");


    while(true){

        std::cout << "Enter -1 to go back to main menu\n\n";

        std::cout << "1. CAESAR\n2. SCYTALE\n\n";
        std::cout << "Input: "; std::cin >> input;


        if(input == -1){ std::cout << "Leaving CIPHERS\n\n"; return;}

        int loading_timer = 2 + rand() % 5;
        
    
        pid_t pid = fork();
        if (pid == -1) {
            std::perror("fork");
            return;
        } else if (pid == 0) {
            switch (input) {
                    case 1:
                        loading("CAESAR", loading_timer); 
                        execlp("ciphers/caesar", "caesar", (char*)NULL);
                        break;
                    case 2:
                        loading("SCYTALE", loading_timer); 
                        execlp("ciphers/syctale", "syctale", (char*)NULL);
                        break;
                    default:
                        std::cerr << "Invalid choice.\n";
                        break;
                }


            // If execlp returns, it failed:
            // std::perror("exec error");
            _exit(1);
        } else {

            
            wait(NULL);
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
    }

}
*/
//Intro that explains what i am doing, is skippable 
void intro(){
    char answer;
    
    type_chars("I am not the best when it comes to story telling, so I want to do something different\n"); sleep(1);
    type_chars("I've been learning how to use 'fork()' | 'exec()' | 'wait()'\n"); sleep(1);
    type_chars("I wanted to put these skills to the test here\n"); sleep(1);
    type_chars("So here is what we are going to do. I am going to give you some cool things to work with :D\n"); sleep(1);
    
    std::cout << "\nWould you like to know what I mean when refering to 'fork()' and 'exec()'? [Y/n]: ";
    std::cin >> answer; std::cout << '\n';
    
    if(answer == 'Y'){ std::cout << ""; } // DO THIS 
    else{ type_chars("\tYea I was guessing that you wouldn't be interested but that's alright :(\n\n");}

}

void manager(){
    char answer;
    std::cout << "Y = yes\nn = No\n";
    std::cout << "Skip Intro [Y/n]:"; std::cin >> answer;

    if(answer =='n'){ intro(); }
    
    
    while(true){
    
        type_chars("Great, Let us begin\n\n");
        
        while(true){
            std::cout << "Would you like to see something cool? [Y/n]: ";
            std::cin >> answer;
            std::cout << '\n';
    
            if(answer == 'Y' || answer == 'n'){break;}
        }
        
        if(answer == 'n'){ sad_Goodbye(); }
    
        int input;
    
        type_chars("Great, here are the following options you can explore :D\n ");
    
        while(true){
            std::cout << "1. Visuals\n2. Games\n3. Ciphers\n\n";
            std::cout << "Input: "; std::cin >> input;
            switch(input){
                case 1: 
                    visuals();
                    break;
                case 2:
                    games();
                    break;
                case 3:
                    ciphers();
                    break;
            }
    
            while(true){
                std::cout << "Would you like to look at MAIN MENU again? [Y/n]:"; std::cin >> answer;
                std::cout << '\n';
    
                if(answer == 'Y'){ break; }
                if(answer == 'n'){ goto exit_point; }
    
            }
        }
        
    }
    
    exit_point:
    std::cout << "Alright. Thanks for using my program :D\n";

    
}    

int main() {
    manager();
    
    return 0;
}
