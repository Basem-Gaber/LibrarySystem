#ifndef MEMBERS_H_INCLUDED
#define MEMBERS_H_INCLUDED

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


int read_members_file();//f1)read members from file and store them in array
void register_(); //f27) registration of new member
void remove_member ();//f34)
void savemember();//f36) saving the changes in members array into file
void print_members();//f39) print all members data in the members array
void bookmanagement();//f46) managing the operations of books array


#endif // MEMBERS_H_INCLUDED
