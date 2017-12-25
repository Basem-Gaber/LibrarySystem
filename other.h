#ifndef OTHER_H_INCLUDED
#define OTHER_H_INCLUDED
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

typedef struct {
    int day, month, year;
} Date;

typedef struct{
char Book_Title[100];
char Author[50];
char publisher[50];
char ISBN[20]; // International Standard Book Number ..Example: 978-3-16-148410-0
Date DateOfPuplication; // Example 30/11/2017
int number_of_copies ;
int current_available_number_of_copies;
char category[30];
int borrows;
}book;

 typedef struct {
     char building[4];
     char street[20];
     char city[20];
 }address;

typedef struct{
char first_name[50];
char last_name[50];
char ID[9];
address member_address;
char member_Phone_Number[12];
char member_age[4];
char    member_Email[30];
int borrows;
}member;

typedef struct{
    char borrowed_ISBN[18];
    char user_i[9];
    Date date_borrowed;
    Date date_due_to_return;
    Date date_returned;
}borrow;

book *books;
member *members;
borrow *borrows;
borrow* overdue;
int borrowarraysize;
int bookarraysize;
int memberarraysize;
Date date_current;
book *foundbks;
book*popular;

int date_compare(Date d1, Date d2);
void acquire_date_current();
int check_ISBN_in_borrows(char ISBN[],char ID[]);
int check_ISBN_in_books(char ISBN[]);
void print_all();
int check_ID(char ID[]);
void savetotal(int way);
void my_exit();
void main_menu(int way);
void wait_for_it(int x);


#endif // OTHER_H_INCLUDED
