#include <stdio.h>
#include <stdlib.h>
typedef struct {
char Book_Title[100];
char Auther[50];
char publisher[50];
char ISBN[18]; // International Standard Book Number ..Example: 978-3-16-148410-0
char DateOfPuplication[11]; // Example 30/11/2017
int number_of_copies ;
int current_available_number_of_copies;
char category[30];
}book;

 typedef struct {
     char building[4];
     char street[20];
     char city[20];
 }address;
typedef struct{
char member_1st_name[50];
char member_last_name[50];
char member_ID[9];
address member_address;
char member_Phone_Number[12];
char member_age[4];
char    member_Email[30];
}member;
typedef struct {
    int day, month, year;
} Date;
typedef struct{
    char borrowed_ISBN[18];
    char user_i[9];
    Date date_borrowed;
    Date date_due_to_return;
    Date date_returned;


}Borrow;

int main()
{

    return 0;
}
