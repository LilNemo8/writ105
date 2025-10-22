#include "visuals.h"

int  load_timer = 2 + rand() % 6;
int  input = 0;

static void make_stdio_blocking() {
    for (int fd = 0; fd <= 2; ++fd) {
        int fl = fcntl(fd, F_GETFL);
        if (fl != -1 && (fl & O_NONBLOCK)) fcntl(fd, F_SETFL, fl & ~O_NONBLOCK);
    }
}

char getch() {
    static bool inited = false;
    static struct termios saved;     // original settings
    struct termios raw;

    if (!inited) {
        if (tcgetattr(STDIN_FILENO, &saved) < 0) perror("tcgetattr(saved)");
        inited = true;
    }

    // Ensure blocking reads on STDIN
    int fl = fcntl(STDIN_FILENO, F_GETFL);
    if (fl != -1 && (fl & O_NONBLOCK)) fcntl(STDIN_FILENO, F_SETFL, fl & ~O_NONBLOCK);

    raw = saved;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 1;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0) perror("tcsetattr(raw)");

    char ch;
    for (;;) {
        ssize_t n = read(STDIN_FILENO, &ch, 1);
        if (n == 1) break;
        if (n < 0 && (errno == EINTR || errno == EAGAIN)) continue;
        perror("read"); break;
    }

    // Restore original terminal settings
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &saved) < 0) perror("tcsetattr(saved)");
    return ch;
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
}

void child(){
    make_stdio_blocking();

    switch (input) {
        case 1: loading("CMATRIX", load_timer);          execlp("cmatrix", "cmatrix", (char*)NULL);            break;
        case 2: loading("AQUARIUM", load_timer);         execlp("asciiquarium", "asciiquarium", (char*)NULL);  break;
        case 3: loading("HOLLYWOOD", load_timer);        execlp("hollywood", "hollywood", (char*)NULL);        break;
        case 4: loading("DONUT", load_timer);            execlp("visuals/donut/donut", "donut", (char*)NULL);  break;
        case 5: loading("CUBE", load_timer);             execlp("visuals/cube/cube", "cube", (char*)NULL);     break;
        case 6:loading("STEAM LOCOMOTIVE", load_timer);  execlp("sl", "sl", (char*)NULL);                      break;
        default: std::cerr << "Invalid choice.\n"; _exit(1);
    }
    // If we got here, exec failed.
    std::perror("exec error");
    _exit(1);
}

void visuals_intro(){
    clear_terminal();
    
    std::cout << "--------------------------------------------------\n";
    std::cout << "              WELCOME TO VISUALS\n";
    std::cout << "--------------------------------------------------\n\n"; 
    sleep(1);
    
    type_chars("Here are some choices that you can see (input 0 for more info)\n");
}

void visuals(){
    visuals_intro();

    while(true){
        input = 0;

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
        
        pid_t pid = fork();

        if (pid == -1) {
            std::perror("fork");
            exit(1);

        } else if (pid == 0) {
            child();

        } else {
            parent(pid);
            wait(NULL);
            clear_terminal();
            if(play_again("VISUALS")){ sleep(1); continue; }
            else{ break; }
        }
        
    }

    clear_terminal();
}


