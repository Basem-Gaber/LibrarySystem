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
#ifndef BOOKHEADER_H_INCLUDED
#define BOOKHEADER_H_INCLUDED
int read_books_file ();//f2)reading books from the file and storing them in the array
void edit_book(); //f10) editing the information of existing book
void display_found(int n);//f15) prints the target search information
void capitalization(char*string,int n);//f17)Uppers the case of the first letter in each word in a string
int search_by_title(int way);//f18) search by Book title or part of it function
int search_by_author(int way,int prev);//f19)
int search_by_ISBN(int way,int prev);//f20)
int search_by_category(int way,int prev);//f21)
int multi_search();//f22)
int search_for_a_book(int way);//f23)
void insert(); //f24) insert a new book
void add_new_copy();//f25) adding new book copy
void delete_book(); //f26) deleting a book from the list
void print_books(); //f38) print all books data in the books array
void savebook();//f35) saving the changes in books array into file
int book_struct_copy(int x,int y);//f16)struct copy function
void bookmanagement();//f46) managing the operations of books array
#endif // BOOKHEADER_H_INCLUDED
