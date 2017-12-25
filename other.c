#include "Validations.h"
#include "Members.h"
#include "bookheader.h"
#include "borrows.h"
#include "other.h"
#include "admin.h"

void wait_for_it(int x){
    printf("((\nPress any key to return back\npress 'M' to return to main menu\n))");
    char c;
    fflush(stdin);
    scanf("%c",&c);
    sleep(0.5);
    system("cls");
    if(c=='M'||c=='m'){
        main_menu(1);}
        else{
    switch(x){
case 1:
    bookmanagement();
    break;
case 2:
    member_management();
    break;
case 3:
    borrow_management();
    break;
case 4:
    administrative();
    break;
case 5:
    print_all();
    break;
    }
    }
}

int date_compare(Date d1, Date d2){
    if(d1.year==0||d2.year==0)
        return -1;
    if(d1.year>d2.year)
        return 1;
    else if(d2.year>d1.year)
        return 2;
    else{
        if(d2.month>d1.month)
            return 2;
        else if(d1.month>d2.month)
            return 1;
        else
        {
            if(d2.day>d1.day)
                return 2;
            else if(d1.day>d2.day)
                return 1;
            else
                return 0;
        }
    }
}
void acquire_date_current(){
    time_t date_current1=time(NULL);
    struct tm tm=*localtime(&date_current1);
    date_current.day=tm.tm_mday;
    date_current.month=tm.tm_mon+1;//month numbered from 1 to 11 .. must add 1
    date_current.year=tm.tm_year+1900;//function gets years since 1900 .. must add 1900 to get current year
}
int check_ISBN_in_borrows(char ISBN[],char ID[])
{
    int i=0,duplicate=0,x,y;
    for(i=0;i<borrowarraysize;i++)
    {
        x=strcmp(ISBN,borrows[i].borrowed_ISBN);
        if(x==0)
        {
            y=strcmp(ID,borrows[i].user_i);
            if(y==0){
                duplicate=1;
                break;}
        }
    }
        if(duplicate==1)
        return i;
        else
            return -1;
}
int check_ISBN_in_books(char ISBN[])
{
    int i=0,duplicate=0,x;
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(ISBN,books[i].ISBN);
        if(x==0)
        {
            duplicate=1;
            break;
        }
    }
    if(duplicate==1)
    {
        //printf("Same ISBN already exists for another book!!");
        return i;
    }
    return -1;
}
int check_ID(char ID[])
{
    int i=0,duplicate=0,x;
    for(i=0;i<memberarraysize;i++)
    {
        x=strcmp(ID,members[i].ID);
        if(x==0)
        {
            duplicate=1;
            break;
        }
    }
    if(duplicate==1)
    {
        //printf("Same ID already exists for another member!!");
        return i;
    }
    return -1;
}

     void main_menu(int way){
    int x;
    char c;
    printf("=============== Welcome to Library System ========================\n");
    red();
    background();
    if(way==2){
    most_popular_books(1);}
    //goto(10,10);
    printf("\n\n^^^^System Management^^^^\n");
printf("1)Book management\n2)Member management\n3)Borrow management\n4)Administrative actions\n5)Print all data\n6)Save changes\n7)Exit\n");
printf("Enter your choice: ");
c=wise_scan(way);
sleep(0.5);
    system("cls");
switch(c){
case '1':
    bookmanagement();
    break;
case '2':
    member_management();
    break;
case '3':
    borrow_management();
    break;
case '4':
    administrative();
    break;
case '5':
    print_all();
    break;
case '6':
    savetotal(1);
    break;
case '7':
    my_exit();
    break;
}
}
void savetotal(int way)
{
    savebook();
    saveborrow();
    savemember();
    printf("Saved successfully!!");
    if(way==1){
    sleep(1.5);
    system("cls");
    main_menu(1);}
    if(way==2){
        sleep(1.5);
        exit(45);
    }
}
 void my_exit()
 { char c='y' ;
    printf("do you want to save the changes\n");
     printf("Y/N\n");
     getchar();
     scanf("%c",&c);

     while (c!='y' && c!='Y' && c!='n' && c!='N')
     {
        printf("do you want to save the changes\n");
     printf("Y/N\n");
     fflush(stdin);
     scanf("%c",&c);
     }
     if (c=='y'|| c=='Y')
     {
       savetotal(2);
     }
else
    exit(0);

     }
     void print_all(){
    int x;
//red();
    printf("((1)Print all books\n2)Print all members\n3)Print all borrows\n4)Save changes\n5)Back to main menu\n))");
    printf("Enter your choice");
    char c;
    c=wise_scan(1);
    sleep(0.5);//sleep function pauses for an inputed period of time before continuing into the following line of code
        system("cls");
    switch (c){
    case '1':
        print_books();
        break;
    case '2':
        print_members();
        break;
    case '3':
        print_borrows();
        break;
    case '4':
    savetotal(1);
    break;
    case '5':
        main_menu(1);
        break;
    }

}
