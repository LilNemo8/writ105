#ifndef CIPHERS_H
#define CIPHERS_H

#include "../helper/functions.h"

#include <map>

void ciphers();

// CAESAR
void caesar();
std::string cipher(char procedure, unsigned int displacement, std::string& input);
std::map<char, char> alphabet_rotation(char procedure, unsigned int displacement);


// SCYTALE
void scytale();
void encryption(std::string str, int row, int column, char operation);
void decryption(std::string str, int row, int column, char operation);
char** createGrid(std::string str, int rows, int columns, char operation);


#endif