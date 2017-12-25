#ifndef VALIDATIONS_H_INCLUDED
#define VALIDATIONS_H_INCLUDED

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// functions prototypes///////////////////////////////////////
char wise_scan(int way);//f1)wise scan function makes sure the user inputs an integer
int number_validation(char number[]);//f2)
int word_validation(char word[]);//f3)
int ISBN_validation(char ISBN[]);//f4)
int email_validation(char email[]);//f)35) email validation
void Name_validation(char*name);//f6) last and first name validation
void phone_validation(char phone[]);//f7) phone number validation

#endif // VALIDATIONS_H_INCLUDED
