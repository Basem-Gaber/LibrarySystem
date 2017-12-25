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
#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

//f7)checks for books whose due to return date has passed and wasn't returned using my date compare function
void overdue_books();
void display_overdue(int n);//f8) display overdue books list
//f9)most popular books .. searches until popular count reaches 5
void most_popular_books(int way);
void administrative();//f47)

#endif // ADMIN_H_INCLUDED
