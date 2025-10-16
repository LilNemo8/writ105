#include "functions.h"



// Gives the illusion of typing each character
void type_chars(const std::string& text, std::chrono::milliseconds per_char, bool newline_at_end) {
    for (char c : text) {
        std::cout << c << std::flush;
        using namespace std::chrono_literals;
        if (c == ' ' || c == '\n') std::this_thread::sleep_for(per_char / 3);
        else if (c == '.' || c == '!' || c == '?' || c == ',') std::this_thread::sleep_for(per_char * 6);
        else std::this_thread::sleep_for(per_char);
    }
    if (newline_at_end) std::cout << '\n';
}


// This is the 'loading' that happens when choosing a specific application (CHAT WROTE THIS)
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
    std::cout<<'\n';
}

int play_again(std::string category){
    char answer;
    while(true){
        std::cout << "\nWould you like to look at the other than " << category << "? [Y/n]:";
        std::cin >> answer;
        if(answer == 'Y' || answer == 'n'){break;}
    }

    if(answer == 'Y'){ 
        std::cout<< "\nAlright lets look at some more " << category << " :D \n\n";
        return 1; //continue
    }else{
        return 0; //break
    }
}


void clear_terminal(){
    std::cout << "\033[2J\033[1;1H"; 
};
