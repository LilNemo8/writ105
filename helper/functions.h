#ifndef TYPE_CHAR_H
#define TYPE_CHAR_H

#include <iostream>
#include <sys/wait.h>  // wait()
#include <signal.h>     // kill(), SIGTERM
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>


void type_chars(const std::string& text = "", std::chrono::milliseconds per_char = std::chrono::milliseconds(50), bool newline_at_end = true);

void loading(const std::string& msg, int time);

int play_again(std::string category);

void clear_terminal();

#endif