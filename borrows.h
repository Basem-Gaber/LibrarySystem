#ifndef BORROWS_H_INCLUDED
#define BORROWS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

int read_borrows_file();
void return_book();
void borrow_book(char *ID);
void saveborrow();
void check_member_books();
void borrow_management ();
void print_borrows();
#endif // BORROWS_H_INCLUDED
