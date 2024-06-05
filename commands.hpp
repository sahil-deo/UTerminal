#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdio>

// Function declarations
void line(int n);
void read(int args, char* commands[]);
void write(int args, char* commands[]);
void search(int args, char* commands[]);
void Delete(int args, char* commands[]);
void append(int args, char* commands[]);
void list(int args, char* commands[]);
void create(int args, char* commands[]);
void curl_get(int args, char* commands[]);
void pwd(int args, char* commands[]);
void random(int args, char* commands[]);
void encrypt(int args, char* commands[]);
void decrypt(int args, char* commands[]);
void help();

#endif // FUNCTIONS_HPP
