#include "visuals.h"

// bool timed = false;
// int  process_timer = 0;
int  loading_timer = 2 + rand() % 6;
int  input = 0;

char getch() {
    char buf = 0;
    struct termios old = {};
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;  // disable buffering
    old.c_lflag &= ~ECHO;    // no echo
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
}

void parent(pid_t& pid){
    // int status = 0;
    
    while (true) {
        char key = getch();
        if (key == 'q' || key == 'Q') {
            // std::cout << "\nKilling child process...\n";
            kill(pid, SIGTERM);  // or SIGKILL for force
            waitpid(pid, nullptr, 0);
            // std::cout << "Child terminated.\n";
            break;
        }
    }
    // if (timed) {
    //     sleep((loading_timer + process_timer));
    //     if (kill(pid, SIGTERM) == -1) {
    //         std::perror("kill(SIGTERM)");
    //     }

    //     // Give it a moment to die gracefully
    //     for (int i = 0; i < 20; ++i) { // ~2 seconds in 100ms steps
    //         pid_t r = waitpid(pid, &status, WNOHANG);
    //         if (r == pid) break;
    //         usleep(100000);
    //     }
        
    //     // If still alive, force-kill
    //     if (waitpid(pid, &status, WNOHANG) == 0) {
    //         kill(pid, SIGKILL);
    //     }
    // }
    
    // wait(NULL);
}

void child(){
    // int size;
    // std::string colorInput;
    // std::string size_str;

    // if(input == 4){
    //     std::cout << "Enter size (1-10): ";
    //     std::cin >> size;
    //     std::cout << "Enter color (e.g., red, green, blue): ";
    //     std::cin >> colorInput;
    //     size_str = std::to_string(size);
    // }

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
            loading("DONUT", loading_timer);
            execlp("visuals/donut/donut", "donut", (char*)NULL);
            break;
        case 5:
            loading("CUBE", loading_timer); 
            execlp("visuals/cube/cube", "cube", (char*)NULL);
            fflush(stdout);
            break;
        case 6:
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
}



void visuals(){
    // int input;
    clear_terminal();

    std::cout << "--------------------------------------------------\n";
    std::cout << "              WELCOME TO VISUALS\n";
    std::cout << "--------------------------------------------------\n\n"; 
    sleep(1);

    type_chars("Here are some choices that you can see (input 0 for more info)\n");

    while(true){
        // process_timer = 8;

        std::cout << "Enter -1 to go back to main menu\n\n";
        std::cout << "1. CMATRIX\n2. AQUARIUM\n3. HOLLYWOOD\n4. DONUT\n5. CUBE\n6. STEAM LOCOMOTIVE\n\n\n";
        std::cout << "Input: "; std::cin >> input;

        if(input == -1){
            std::cout << "Leaving Visuals\n\n";
            break;
        }else if(input == 0){
            std::cout << "1. Gives a 'Matrix'-style display, where a rain of green characters streams down the screen\n";
            std::cout << "2. It is an aquarium/sea animation in ASCII art created using perl\n";
            std::cout << "3. Creates a visually engaging, hacker-movie-like terminal interface with multiple windows and animated text\n";
            std::cout << "4. shows you an animated steam train\n\n"; 
            std::cout << "Input: "; std::cin >> input;
        }
        
        // Decide timing *before* fork so the parent sees it.
        // timed = (input == 1 || input == 2 || input == 3 || input == 4 || input == 5);

        // if(timed){
        //     std::cout << "How long would you like to display #" << input << " for in seconds? (defualt = 8s): ";
        //     std::cin >> process_timer;
        // }
        
        pid_t pid = fork();

        if (pid == -1) {
            std::perror("fork");
            exit(1);

        } else if (pid == 0) {
            child();

        } else {
            parent(pid);
            clear_terminal();
            if(play_again("VISUALS")){ continue; }
            else{ break; }
        }
        
    }

    clear_terminal();
}


