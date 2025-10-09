#include <iostream>
#include <unistd.h>     // fork(), execlp(), sleep()
#include <sys/wait.h>   // waitpid()
#include <signal.h>     // kill(), SIGTERM
#include <string>
#include <chrono>
#include <thread>
#include <sstream>

void type_chars(const std::string& text,
                std::chrono::milliseconds per_char = std::chrono::milliseconds(40),
                bool newline_at_end = true) {
    for (char c : text) {
        std::cout << c << std::flush;
        using namespace std::chrono_literals;
        if (c == ' ' || c == '\n') std::this_thread::sleep_for(per_char / 2);
        else if (c == '.' || c == '!' || c == '?' || c == ',') std::this_thread::sleep_for(per_char * 6);
        else std::this_thread::sleep_for(per_char);
    }
    if (newline_at_end) std::cout << '\n';
}


void loading(const std::string& msg, int time) {
    const int maxDots = 3;
    int d = 1; // show 1,2,3 dots, then reset to none (0), repeat
    int x  = time;
    while (x!=0) {
        std::cout << "\rDISPLAYING " << msg
                  << std::string(d, '.')
                  << std::string(maxDots - d, ' ')   // overwrite old dots
                  << std::flush;

        sleep(1);
        d = (d + 1) % (maxDots + 1); // cycles: 1→2→3→0→1→...
        x--;
    }
}

void visuals() {
    int input;
    std::cout << "\n\nGREAT! Here are some choices that you can see (INPUT 0 FOR MORE INFORMATION)\n\n";

    while(true){

        std::cout << "1. CMATRIX\n2. AQUARIUM\n3. STEAM LOCOMOTIVE\n\n";
        std::cin >> input;
        int loading_timer = 2 + rand() % 7;
        
        if(input == 0){
            std::cout << "1. Gives a 'Matrix'-style display, where a rain of green characters streams down the screen\n";
            std::cout << "2. It is an aquarium/sea animation in ASCII art created using perl\n";
            std::cout << "3. shows you an animated steam train\n"; 
            std::cin >> input;
        }
        
        // Decide timing *before* fork so the parent sees it.
        bool timed = (input == 1 || input == 2);
        
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
                    loading("STEAM LOCOMOTIVE", loading_timer);
                    execlp("sl", "sl", (char*)NULL);
                    break;
                default:
                    std::cerr << "Invalid choice.\n";
                    _exit(1);
            }
            // If we got here, exec failed.
            std::perror("exec failed");
            _exit(127);

        } else {
            // --- Parent: optionally time-limit the child ---
            int status = 0;

            if (timed) {
                sleep((loading_timer+6));
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
            
         
            char answer;
            std::cout << "Would you like to look at the other than visuals? [Y/n]:";
            std::cin >> answer;

            if(answer == 'Y'){ 
                std::cout<< "\nAlright lets look at some more visuals :D \n\n";
                continue; 
            }else{
                break; 
            }
        }
        
    }
}

void manager(){

}

int main() {
	char answer;

    // type_chars("I am not the best when it comes to story telling, so I want to do something different\n"); sleep(1);
    // type_chars("I've been learning how to use 'fork()' | 'exec()' | 'wait()'\n"); sleep(1);
    // type_chars("I wanted to put these skills to the test here\n"); sleep(1);
    // type_chars("So here is what we are going to do. I am going to give you some cool things to work with :D\n"); sleep(1);

    // std::cout << "\nWould you like to know what I mean when refering to 'fork()' | 'exec()' | 'wait()' [Y/n]: ";
    // std::cin >> answer; std::cout << '\n';

	// if(answer == 'Y'){ std::cout << "Well bascially..."; }
    // else{ type_chars("\tYea I was guessing that you wouldn't be interested but that's alright :(\n\n");}
    
    
    while(true){

        type_chars("Great, Let us begin\n\n");
        
        while(true){
            std::cout << "Would you like to see something cool? [Y/n]: ";
            std::cin >> answer;
            if(answer == 'Y' || answer == 'n'){break;}
        }
        
        if(answer == 'n'){ 
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

        int input;
        type_chars("Great, here are the following options you can explore :D\n ");
        while(true){
            std::cout << "1. Visuals\n2. Games\n3. Ciphers\n\nInput:";
            std::cin >> input;
            switch(input){
                case 1: 
                    visuals();
                    break;
                // case 2:
                //     games();
                //     break;
                // case 3:
                //     ciphers()
                //     break;
            }
            while(true){
                std::cout << "Would you like to look at other options? [Y/n]:";
                std::cin >> answer;
                if(answer == 'Y'){ break; }
                if(answer == 'n'){ goto exit_point; }

            }
        }
        
    }

    exit_point:
    std::cout << "Here is the exit point\n";

    
	// std::string line;
    
    // pid_t pid = fork();
    // if (pid == -1) {
    //     std::perror("fork");
    //     return 1;
    // } else if (pid == 0) {
    //     std::cout << "Child: launching terminal-pong...\n";
    //     // If launcher and pong are in the same directory at runtime:
    //     execlp("/home/nemismagana/code/random/terminal-pong/build/pong", "pong", (char*)NULL);

    //     // If execlp returns, it failed:
    //     std::perror("exec pong");
    //     _exit(1);
    // } else {
    //     int status;
    //     waitpid(pid, &status, 0);
    //     std::cout << "Parent: child exited (status " << status << ")\n";
    // }

    return 0;
}
