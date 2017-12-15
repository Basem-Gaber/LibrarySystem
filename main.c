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
char ISBN[18]; // International Standard Book Number ..Example: 978-3-16-148410-0
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


int read_books_file (){
    FILE* f;
    int i=0;
    f=fopen("books.txt","r");
    if(f==NULL)
    {
        printf("Books text file doesn't exist!\n");
        exit(1);
    }
    while(!feof(f))
    {
        fscanf(f,"%[^,],%[^,],%[^,],%[^,],%d/%d/%d,%d,%d,%[^,],%d",books[i].Book_Title,books[i].Author,books[i].publisher,books[i].ISBN
                        ,&books[i].DateOfPuplication.day,&books[i].DateOfPuplication.month,&books[i].DateOfPuplication.year
                        ,&books[i].number_of_copies,&books[i].current_available_number_of_copies,books[i].category,&books[i].borrows);
        fscanf(f,"\n");
        i++;
    }
    fclose(f);
    return i;
}

int read_members_file(){
    FILE* f;
    int i=0;
    f=fopen("members.txt","r");
    if(f==NULL)
    {
        printf("Members text file doesn't exist!\n");
        exit(2);
    }
    while(!feof(f))
    {
        fscanf(f,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d",members[i].last_name,members[i].first_name,members[i].ID,members[i].member_address.building,members[i].member_address.street,members[i].member_address.city
                          ,members[i].member_Phone_Number,members[i].member_age,members[i].member_Email,&members[i].borrows);
        fscanf(f,"\n");
        i++;
    }
    fclose(f);
    return i;
}

int read_borrows_file(){
    FILE* f;
    int i=0;

    f=fopen("borrows.txt","r");

    if(f==NULL)
    {
        printf("Borrows file doesn't exist!\n");
        exit(3);
    }

    while(!feof(f))
    {
        fscanf(f,"%[^,],%[^,],%d/%d/%d,%d/%d/%d,%d/%d/%d",borrows[i].borrowed_ISBN,borrows[i].user_i,&borrows[i].date_borrowed.day,&borrows[i].date_borrowed.month
                    ,&borrows[i].date_borrowed.year,&borrows[i].date_due_to_return.day,&borrows[i].date_due_to_return.month
                    ,&borrows[i].date_due_to_return.year,&borrows[i].date_returned.day,&borrows[i].date_returned.month,&borrows[i].date_returned.year);
        fscanf(f,"\n");
        i++;

    }
    fclose(f);

    return i;
}
int date_compare(Date d1,Date d2){
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
    date_current.month=tm.tm_mon+1;
    date_current.year=tm.tm_year+1900;
}
void overdue_books(){
int i=0,x,y,overcount=0;
acquire_date_current();

for(i=0;i<borrowarraysize;i++)
{
    x=date_compare(borrows[i].date_due_to_return,date_current);
    y=date_compare(borrows[i].date_due_to_return,borrows[i].date_returned);

    if(x==2&&y!=2)
    {
        overdue[overcount]=borrows[i];
        overcount++;
    }
}

display_overdue(overcount);
}

void display_overdue(int n){
    int i;
    printf("List of Overdue books: \n");
    for(i=0;i<n;i++)
    {
    printf("%d)%s,%s,%d-%d-%d,%d/%d/%d,%d/%d/%d\n",i+1,overdue[i].borrowed_ISBN,overdue[i].user_i,overdue[i].date_borrowed.day,overdue[i].date_borrowed.month
                    ,overdue[i].date_borrowed.year,overdue[i].date_due_to_return.day,overdue[i].date_due_to_return.month
                    ,overdue[i].date_due_to_return.year,overdue[i].date_returned.day,overdue[i].date_returned.month,overdue[i].date_returned.year);

}
wait_for_it(4);
}

book*popular;

void most_popular_books(){
    int i,j,max=0,popularcount=0;
    popular=(book*)malloc(5*sizeof(book));
    for(i=0;i<bookarraysize;i++)
    {
        if(books[i].borrows>max)
            max=books[i].borrows;
    }
    while(popularcount!=5)
    {
        for(i=0;i<bookarraysize;i++)
        {
            if(books[i].borrows==max){
                popular[popularcount]=books[i];
                popularcount++;
                }
            if(popularcount==5)
                break;

        }
        max--;
    }
printf("Most Popular 5 books: \n");
for(j=0;j<popularcount;j++)
{
    printf("%d)%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d",popular[j].Book_Title,popular[j].Author,popular[j].publisher,popular[j].ISBN,
           popular[j].DateOfPuplication.day,popular[j].DateOfPuplication.month,popular[j].DateOfPuplication.year,popular[j].number_of_copies,
           popular[j].current_available_number_of_copies,popular[j].category,popular[j].borrows);
}
wait_for_it(4);
}


void edit_book(){
    int i,x=0,y=0,bookindex=0;
    char ISBN[15],newdata[50];
    printf("Please enter the ISBN if the book you wish to modify: \n");
    scanf("%s",ISBN);
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(ISBN,books[i].ISBN);
        if(x==0)
        {
            bookindex=i;
            break;
        }

    }
    printf("Please select which data would you like to configure:\n1)Title\n2)Author\n3)Category\n4)Publisher\n");
    scanf("%d",y);
    printf("Please enter the new data you wish to insert:\n");
    scanf("%s",newdata);
    switch (y){
case 1:
    strcpy(newdata,books[bookindex].Book_Title);
    break;
case 2:
    strcpy(newdata,books[bookindex].Author);
    break;
case 3:
    strcpy(newdata,books[bookindex].category);
    break;
case 4:
    strcpy(newdata,books[bookindex].publisher);
    break;
    }
    wait_for_it(1);
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

int check_ISBN_in_borrows(char ISBN[])
{
    int i=0,duplicate=0,x;
    for(i=0;i<borrowarraysize;i++)
    {
        x=strcmp(ISBN,borrows[i].borrowed_ISBN);
        if(x==0)
        {
            duplicate=1;
            break;
        }
    }
    if(duplicate==1)
    {
        return i;
    }
    else{
    //printf("ISBN doesn't belong to a borrowed book!!\n");
    return -1;
    }
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
        printf("Same ID already exists for another member!!");
        return i;
    }
    return -1;
}


void return_book(){
    int x,y,z;
    char ISBN[15];
    char ID[10];
    printf("Please enter the ID of the user returning the book:\n");
    scanf("%s",ID);
    printf("Please enter the ISBN of the returned book: \n");
    scanf("%s",ISBN);
    x=check_ISBN_in_borrows(ISBN);
    acquire_date_current();
    borrows[x].date_returned=date_current;
    y=check_ISBN_in_books(ISBN);
    books[y].current_available_number_of_copies++;
    z=check_ID(ID);
    members[z].borrows--;
    printf("Book returned!");
    wait_for_it(3);


}


book *found;//global found books array...will be malloced in main


void display_found(int n){
    int i;
    char c;
    printf("Search Results:\n");
    for(i=0;i<n;i++)
    {
        printf("%d)%s,%s,%s,%s,%d/%d/%d,%d,%d,%s\n",i+1,found[i].Book_Title,found[i].Author,found[i].publisher,found[i].ISBN
               ,found[i].DateOfPuplication.day,found[i].DateOfPuplication.month,found[i].DateOfPuplication.year
               ,found[i].number_of_copies,found[i].current_available_number_of_copies,found[i].category);
    }
}

void book_struct_copy(int x,int y){
    strcpy(found[x].Author,books[y].Author);
    strcpy(found[x].Book_Title,books[y].Book_Title);
    strcpy(found[x].category,books[y].category);
    found[x].current_available_number_of_copies=books[y].current_available_number_of_copies;
    found[x].DateOfPuplication=books[y].DateOfPuplication;
    strcpy(found[x].ISBN,books[y].ISBN);
    found[x].number_of_copies=books[y].number_of_copies;
    strcpy(found[x].publisher,books[y].publisher);


}

void capitalization(char*string,int n){
    int i;
    char c;
    c=toupper(string[0]);
    string[0]=c;
    for(i=1;i<n;i++)
    {
        if(string[i]==' '&&!(string[i+1]=='t' && string[i+2]=='o'))
        {
            c=toupper(string[i+1]);
            string[i+1]=c;
        }
    }

}
int search_by_title(){
    char key[50];
    char title[50];
    int foundcount=0,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    printf("Please enter the title of the book: \n");
    getchar();
    scanf("%[^\n]",key);
    int i,j,k,l,x=0,titlelen=0,keylen=0,found=0,not_duplicate=1;
    keylen=strlen(key);
    capitalization(key,keylen);
    printf("%s\n\n",key);
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].Book_Title,key);
        if(x==0){
            book_struct_copy(foundcount,i);
            foundcount++;
            book_index[foundcount]=i;//stores the index of the book in main array to allow for future editing on book after search
        }

    }
    for(i=0;i<bookarraysize;i++)
    {
        int titlelen=strlen(books[i].Book_Title);
        strcpy(books[i].Book_Title,title);
        for(j=0;j<titlelen;j++)
        {
            if(title[j]==key[0])
            {
                for(k=1;k<keylen;k++)
                {
                    if(title[j+k]!=key[k])
                        break;
                    if(k==keylen-1)
                        found=1;
                }

            }
        }
        for(l=0;l<foundcount;l++)
        {
            if(book_index[foundcount]==i)
                not_duplicate=0;
        }
        if(found==1&&not_duplicate==1)
        {
            book_struct_copy(foundcount,i);
            foundcount++;
            book_index[foundcount]=i;
        }
        found=0;
        not_duplicate=1;
    }

    char c;
    if(foundcount==0)
    {
        printf("Book Title wasn't found!\n");
    }
    //if(c=='Y'||'y')
        //search_for_a_book();
    //else
        //main_menu();
    if(foundcount>0)
        display_found(foundcount);

        return foundcount;
}


int search_by_author(){
    char key[50];
    int foundcount=0,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    printf("Please enter the name of the author: \n");
    getchar();
    scanf("%[^\n]",key);
    toupper(key);
    int i,x=0;
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].Author,key);
        if(x==0){
            found[foundcount]=books[i];
            foundcount++;
            book_index[foundcount]=i;//stores the index of the book in main array to allow for future editing on book after search
        }

    }
    char c;
    if(foundcount==0)
    {
        printf("Author wasn't found!\n");
    }
    //if(c=='Y'||'y')
        //search_for_a_book();
    //else
        //main_menu();
    if(foundcount>0)
        display_found(foundcount);

        return foundcount;
}


int search_by_ISBN(){
    char key[50];
    int foundcount=0,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    printf("Please enter the ISBN: \n");
    scanf("%s",key);
    int i,x=0;
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].ISBN,key);
        if(x==0){
            found[foundcount]=books[i];
            foundcount++;
            book_index[foundcount]=i;//stores the index of the book in main array to allow for future editing on book after search
        }

    }
    char c;
    if(foundcount==0)
    {
        printf("ISBN wasn't found!\n");
    }
    //if(c=='Y'||'y')
        //search_for_a_book();
    //else
        //main_menu();
    if(foundcount>0)
        display_found(foundcount);

        return foundcount;
}


int search_by_category(){
    char key[50];
    int foundcount=0,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    printf("Please enter the category: \n");
    scanf("%s",key);
    toupper(key);
    int i,x=0;
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].category,key);
        if(x==0){
            found[foundcount]=books[i];
            foundcount++;
            book_index[foundcount]=i;//stores the index of the book in main array to allow for future editing on book after search
        }

    }
    char c;
    if(foundcount==0)
    {
        printf("Category wasn't found!\n");
    }
    //if(c=='Y'||'y')
      //  search_for_a_book();
    //else
       // main_menu();
    if(foundcount>0)
        display_found(foundcount);
        return foundcount;
}

void search_for_a_book(int way){
    printf("Please enter the desired method of searching:\n1)Search by book title\n2)Search by author name\n3)Search by ISBN\n4)Search by book category\nChoice(1-2-3-4)?\n");
    int x,y;
    char c='n';
    scanf("%d",&x);
    switch (x){
case 1:
    y=search_by_title();
    break;
case 2:
    y=search_by_author();
    break;
case 3:
    y=search_by_ISBN();
    break;
case 4:
    y=search_by_category();
    break;
    }
if(y==0){
    {printf("Do you wish to retry the search(Y/N)?\n");
        scanf("%c",&c);}
        toupper(c);
    if(c=='Y'){
        search_for_a_book(way);}
    }
    if (way==1)
    wait_for_it(1);
}

void insert(){
    char ISBN[15];
    int x;
    bookarraysize++;

     printf("Enter information of the new book\n");
     printf("Please enter book's title: ");
     scanf("%s",books[bookarraysize].Book_Title);
     printf("Please enter the author of the book: ");
     scanf("%s",books[bookarraysize].Author);
     printf("Please enter publisher of the book: ");
     scanf("%s",books[bookarraysize].publisher);
     printf("Please enter ISBN of book: ");
     scanf("%s",ISBN);
     check_ISBN_in_books(ISBN);
     if(x==-1)
        strcpy(books[bookarraysize].ISBN,ISBN);
     else
        printf("Same ISBN already exists for another registered book!!");
     printf("Please enter date of publication: ");
     scanf("%s",books[bookarraysize].DateOfPuplication);
     printf("Please enter category of book: ");
     scanf("%s",books[bookarraysize].category);
     printf("Please enter number of copies: ");
     scanf("%d",&books[bookarraysize].number_of_copies);
     bookarraysize++;
    /* printf("to save press 6");
      scanf("%d",&s);
     if (s==6)
     {
         save_insert();
     }*/
wait_for_it(1);
 }
 /*void save_insert()
 {
     FILE* bookPtr;
     bookPtr=fopen ("program1.txt" ,"a");
     if(bookPtr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   fprintf(bookPtr,"%s,%s,%s,%s,%s,%s,%d,%d\n",books->Book_Title,books->Auther,books->publisher ,books->ISBN,books->DateOfPuplication,books->category,books->number_of_copies,books->number_of_copies );
 }*/
 void add_new_copy(){
    char ISBN[18];
    int copies;
    int i,r;
    printf("enter ISBN of the book as (978-3-16-148410-0):\n");
    scanf("%s",ISBN);
    printf("enter number of copies of the book: ");
    do {scanf("%d",&copies);} while (copies<0); // "no negative values" check
    for (i=0;i<bookarraysize;i++){
            r= strcmp(books[i].ISBN,ISBN);// if ISBN found increment the no. of copies by the value entered
        if(r==0)
           {
             books[i].number_of_copies+=copies;
             books[i].current_available_number_of_copies+=copies;
            }

   } /*printf("%d\n",r);*/
   wait_for_it(1);
   }

void delete_book(){
    char ISBN[18];
    int found=0,pos,i;
    printf("enter ISBN of the book as (978-3-16-148410-0):\n");
    scanf("%s",ISBN);
     for (i=0;i<bookarraysize;i++){
        if((strcmp(books[i].ISBN,ISBN))==0) // search for ISBN
        {
            found = 1;
            pos = i;
            break;
        }}

    if (found == 1)
    {
        for (i = pos; i <bookarraysize-1; i++)
        {
           strcpy( books[i].Book_Title , books[i + 1].Book_Title);
           strcpy( books[i].Author  , books[i + 1].Author );
           strcpy( books[i].publisher  , books[i + 1].publisher );
           strcpy( books[i].ISBN , books[i + 1].ISBN );
           books[i].DateOfPuplication=books[i + 1].DateOfPuplication;
           strcpy( books[i].category  , books[i + 1].category );
           books[i].number_of_copies=books[i+1].number_of_copies;
            books[i].current_available_number_of_copies  = books[i + 1].current_available_number_of_copies;
        }

 /*strcpy( books[i].Book_Title , "\0");
           strcpy( books[i].Auther  , "\0" );
           strcpy( books[i].publisher  ,"\0");
           strcpy( books[i].ISBN ,"\0" );
           strcpy( books[i].DateOfPuplication  ,"\0" );
           strcpy( books[i].category  , "\0" );*/
           printf("Book deleted successfully!!");
           bookarraysize--; // decrease size of the book array by 1

}
else printf("BOOK NOT FOUND\n");
wait_for_it(1);
}

void register_(){
    int n;
    char ID[10];
    int x;
    n=memberarraysize++;
    printf("Please enter member's first name: ");
    scanf("%s",members[n].first_name);
    printf("Please enter member's last name: ");
    scanf("%s",members[n].member_Phone_Number);
    printf("Please enter member's ID: ");
    scanf("%s",ID);
    x=check_ID(ID);
    if(x==-1)
        strcpy(members[n].ID,ID);
    else
        printf("Same ID already exits for another registered member!!");
    printf("Please enter member's address:\n");
    printf("building: ");
    scanf("%s",members[n].member_address.building);
    printf("\nstreet: ");
    scanf("%s",members[n].member_address.street);
    printf("\ncity: ");
    scanf("%s",members[n].member_address.city);
    printf("Please enter member's phone number: ");
    scanf("%d",members[n].member_Phone_Number);
    printf("Please enter member's age: ");
    scanf("%d",members[n].member_age);
    printf("Please enter member's e-mail: ");
    scanf("%s",members[n].member_Email);
    wait_for_it(2);
}
void remove_member (){
int n=memberarraysize;
int i;
int flag=0;
int k;
char*ID;
ID=(char*)malloc(15*sizeof(char));
printf("Please enter member's ID: ");
scanf("%s",ID);
for(i=0;i<n;i++){
    if(strcmp(members[i].ID,ID)==1){
            flag=1;
        for (k=i;k<n;k++){
            members[i]=members[i+1];
        }


    }
}
if(flag==1)
{
    printf("Member removed successfully!!");
}
else if(flag==0)
    printf("Member wasn't found!!");


wait_for_it(2);

}

void savebook()
{
    FILE *fbook;
    int i;
    fbook=fopen("books.txt","w");
    if (fbook!=NULL)
    {
        for (i=0;i< bookarraysize ; i++ )
        {
            fprintf(fbook,"%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d",books[i].Book_Title,books[i].Author,books[i].publisher,books[i].ISBN
                        ,books[i].DateOfPuplication.day,books[i].DateOfPuplication.month,books[i].DateOfPuplication.year
                        ,books[i].number_of_copies,books[i].current_available_number_of_copies,books[i].category,books[i].borrows);
        }

    }
    fclose(fbook);

}
void savemember()
{
    FILE *fmember;
    int i;
    fmember=fopen("members.txt","w");
    if (fmember!=NULL)
    {
        for (i=0;i< memberarraysize ; i++ )
        {
            fprintf(fmember,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%d",members[i].last_name,members[i].first_name,members[i].ID,members[i].member_address.building,members[i].member_address.street,members[i].member_address.city
                          ,members[i].member_Phone_Number,members[i].member_age,members[i].member_Email,members[i].borrows);
        }

    }
    fclose(fmember);

}
void saveborrow()
{
    FILE *fborrow;
    int i;
    fborrow=fopen("borrows.txt","w");
    if (fborrow!=NULL)
    {
        for (i=0;i< borrowarraysize ; i++ )
        {
            fprintf(fborrow, "%s,%s,%d/%d/%d,%d/%d/%d,%d/%d/%d",borrows[i].borrowed_ISBN,borrows[i].user_i,borrows[i].date_borrowed.day,borrows[i].date_borrowed.month
                    ,borrows[i].date_borrowed.year,borrows[i].date_due_to_return.day,borrows[i].date_due_to_return.month
                    ,borrows[i].date_due_to_return.year,borrows[i].date_returned.day,borrows[i].date_returned.month,borrows[i].date_returned.year);
        }

    }
    fclose(fborrow);

}
void print_books(){
    int n=bookarraysize;
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d)%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d",books[i].Book_Title,books[i].Author,books[i].publisher,books[i].ISBN,
           books[i].DateOfPuplication.day,books[i].DateOfPuplication.month,books[i].DateOfPuplication.year,books[i].number_of_copies,
           books[i].current_available_number_of_copies,books[i].category,books[i].borrows);
    }
    wait_for_it(5);
}

void print_members(){
    int n=memberarraysize;
    int i;
    for(i=0;i<n;i++)
    {
        printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d",members[i].first_name,members[i].last_name,members[i].ID,members[i].member_address.building
               ,members[i].member_address.street,members[i].member_address.city,members[i].member_Phone_Number,members[i].member_age,members[i].member_Email
               ,members[i].borrows);
    }
    wait_for_it(5);
}

void print_borrows(){
    int n=borrowarraysize;
    int i;
    for(i=0;i<n;i++)
    {
        printf("%s,%s,%d/%d/%d,%d/%d/%d,%d/%d/%d",borrows[i].borrowed_ISBN,borrows[i].user_i,borrows[i].date_borrowed.day,borrows[i].date_borrowed.month
               ,borrows[i].date_borrowed.year,borrows[i].date_due_to_return.day,borrows[i].date_due_to_return.month,borrows[i].date_due_to_return.year
               ,borrows[i].date_returned.day,borrows[i].date_returned.month,borrows[i].date_returned.year);
    }
    wait_for_it(5);
}



void print_all(){
    int x;

    printf("((1)print all books\n2)print all members\n3)print all borrows\n4)back to main menu\n))");
    printf("Enter your choice");
    scanf("%d",&x);
    switch (x){
    case 1:
        sleep(0.5);
        system("cls");
        print_books();
        break;
    case 2:
        sleep(0.5);
        system("cls");
        print_members();
        break;
    case 3:
        sleep(0.5);
        system("cls");
        print_borrows();
        break;
    case 4:
        sleep(0.5);
        system("cls");
        main_menu();
        break;
    }

}

void borrow_book(char *ID){
    borrowarraysize++;
    int k;
    search_for_a_book(2);
    printf("Which of the books in the list do you wish to borrow?(Enter its list number)");
    scanf("%d",&k);
    if (found[k].current_available_number_of_copies>0){
    strcpy(borrows[borrowarraysize].borrowed_ISBN,found[k].ISBN);
    strcpy(borrows[borrowarraysize].user_i,ID);
    printf("Please enter Dates as following\n Day/Month/Year");
printf("Date issued: ");
      scanf("%d%d%d",borrows[borrowarraysize].date_borrowed.day,borrows[borrowarraysize].date_borrowed.month,borrows[borrowarraysize].date_borrowed.year);
printf("Date due return: ");
      scanf("%d%d%d",borrows[borrowarraysize].date_due_to_return.day,borrows[borrowarraysize].date_due_to_return.month,borrows[borrowarraysize].date_due_to_return.year);
borrows[borrowarraysize].date_returned.day=0;
borrows[borrowarraysize].date_returned.month=0;
borrows[borrowarraysize].date_returned.year=0;
int z;
char ISBN[20];
strcpy(ISBN,found[k].ISBN);
z=check_ISBN_in_books(ISBN);
books[z].current_available_number_of_copies--;
}
}
void check_member_books(){
    char ID[9];
    int flag=0;
    int index;
    int i;
printf("please enter user ID:");
scanf("%s",ID);
for(i=0;i<memberarraysize;i++){
    if(strcmp(ID,members[i].ID)==1)
        { flag=1;
        index=i;
        break;
        }
}
if (flag==1)
    printf("User ID is Valid.");
    else{
            printf("Wrong ID");}


    if(members[index].borrows<3){
        borrow_book(ID);}
    else
        printf("Sorry, you can't borrow more books");
}

void savetotal()
{
    savebook();
    saveborrow();
    savemember();
    printf("Saved successfully!!");
    sleep(1.5);
    system("cls");
    main_menu();
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
     scanf("%c",&c);
     }
     if (c=='y'|| c=='Y')
     {
       savetotal();
     }
else
    exit(0);

     }



void bookmanagement(){
    int x,y;
printf("1)insert a new book\n2)search for a book\n3)add a new copy\n4)delete a book\n5)return to main menu\n");
do{
printf("Please enter your choice: ");
scanf("%d",&x);}while(x<=0|x>4);
switch(x){
case 1:
    sleep(0.5);
    system("cls");
    insert();
    break;
case 2:
    sleep(0.5);
    system("cls");
    search_for_a_book(1);
    break;
case 3:
    sleep(0.5);
    system("cls");
    add_new_copy();
    break;
case 4:
    sleep(0.5);
    system("cls");
    delete_book();
    break;
case 5:
    sleep(0.5);
    system("cls");
    main_menu();
    break;}
}
void administrative(){
    int x;
    printf("1)most popular books\n2)overdue books\n");
    do{
printf("Enter your choice: ");
scanf("%d",&x);}while(x<=-0|x>3);
switch(x){
case 1:
    sleep(0.5);
    system("cls");
    most_popular_books();
    break;
case 2:
    sleep(0.5);
    system("cls");
    overdue_books();
    break;
case 3:
    sleep(0.5);
    system("cls");
    main_menu();
    break;
}
}

void main_menu(){
    int x;
printf("1)book management\n2)member management\n3)borrow management\n4)administrative actions\n5)print all data\n6) save changes\n7) exit\n");
do{
printf("Enter your choice: ");
scanf("%d",&x);}while(x<=-0|x>7);
switch(x){
case 1:
    sleep(0.5);
    system("cls");
    bookmanagement();
    break;
case 2:
    sleep(0.5);
    system("cls");
    member_management();
    break;
case 3:
    sleep(0.5);
    system("cls");
    borrow_management();
    break;
case 4:
    sleep(0.5);
    system("cls");
    administrative();
    break;
case 5:
    sleep(0.5);
    system("cls");
    print_all();
    break;
case 6:
    sleep(0.5);
    system("cls");
    savetotal();
    break;
case 7:
    sleep(0.5);
    system("cls");
    my_exit();
    break;
}
}

void member_management(){
int x;
printf("1)Register\n2)Remove\n3)Return back to main menu\n");
printf("Please enter your choice: ");
scanf("%d",&x);
switch(x){
case 1:
    sleep(0.5);
    system("cls");
    register_();
    break;
case 2:
    sleep(0.5);
    system("cls");
    remove_member();
    break;
case 3:
    sleep(0.5);
    system("cls");
    main_menu();
    break;
    }

}
void borrow_management (){
int x;
printf("1)Borrow\n2)Return book\n3)Return to main menu\n");
printf("Please enter your choice: ");
scanf("%d",&x);
switch(x){
case 1:
    sleep(0.5);
    system("cls");
    check_member_books();
    break;
case 2:
    sleep(0.5);
    system("cls");
    return_book();
    break;
case 3:
    sleep(0.5);
    system("cls");
    main_menu();
    break;
}
}

void wait_for_it(int x){
    printf("((\nPress any key to return back\npress 'M' to return to main menu\n))");
    char c;
    scanf("%c",&c);
    sleep(0.5);
    system("cls");
    if(c=='M'||c=='m')
        main_menu;
    switch(x){
case 1:
    bookmanagement();
case 2:
    member_management();
case 3:
    borrow_management();
case 4:
    administrative();
case 5:
    print_all();
    }
}

int main()
{
    books=(book*)malloc(50*sizeof(book));
    overdue=(borrow*)malloc(50*sizeof(borrow));
    found=(book*)malloc(50*sizeof(book));
    members=(member*)malloc(50*sizeof(member));
    borrows=(borrow*)malloc(50*sizeof(member));
    int i,borrowsize=0,membersize=0,booksize=0;
    borrowarraysize=read_borrows_file();
    memberarraysize=read_members_file();
    bookarraysize=read_books_file();
    main_menu();
    return 0;
}
