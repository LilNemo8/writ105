#include "visuals.h"

int  load_timer = 2 + rand() % 6;
int  input = 0;



void parent_v(pid_t& pid){
    // int status = 0;
    while (true) {
        char key = getch();
        if (key == 'q' || key == 'Q') {
            kill(pid, SIGTERM);  // or SIGKILL for force
            waitpid(pid, nullptr, 0);
            break;
        }
    }      
}

void child_v(){
    make_stdio_blocking();

    switch (input) {
        case 1: loading("CMATRIX", load_timer);             execlp("cmatrix", "cmatrix", (char*)NULL);            break;
        case 2: loading("AQUARIUM", load_timer);            execlp("asciiquarium", "asciiquarium", (char*)NULL);  break;
        case 3: loading("HOLLYWOOD", load_timer);           execlp("hollywood", "hollywood", (char*)NULL);        break;
        case 4: loading("DONUT", load_timer);               execlp("visuals/donut/donut", "donut", (char*)NULL);  break;
        case 5: loading("CUBE", load_timer);                execlp("visuals/cube/cube", "cube", (char*)NULL);     break;
        case 6:  loading("STEAM LOCOMOTIVE", load_timer);   execlp("sl", "sl", (char*)NULL);                      break;
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
    
    if(mathew->exists()){
        mathew->visuals_dialogue(1);
    }else{
        type_chars("Here are some choices that you can see\n");
    }
}

void visuals(){
    visuals_intro();

    while(true){
        input = 0;

        std::cout << "Enter -1 to go back to main menu\n\n";
        std::cout << "1. CMATRIX\n2. AQUARIUM\n3. HOLLYWOOD\n4. DONUT\n5. CUBE\n6. STEAM LOCOMOTIVE\n\n\n";
        std::cout << "Input: "; std::cin >> input;

        if(input == -1){
            if(mathew->exists()) mathew->visuals_dialogue(3);

            std::cout << "Leaving Visuals\n\n";
            sleep(1); 
            break;
        }else if(input == 0 && mathew->exists()){
            mathew->visuals_dialogue(2);
            continue;
        }
        
        pid_t pid = fork();

        if (pid == -1) {
            std::perror("fork");
            exit(1);

        } else if (pid == 0) {
            child_v();

        } else {
            parent_v(pid);
            wait(NULL);
            clear_terminal();
        }
        
    }

    clear_terminal();
}


