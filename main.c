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

void red(){
 system("COLOR 4"); // change font color
}
void background(){
system("COLOR FC");// change background color
}
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// functions prototypes///////////////////////////////////////
char wise_scan(int way);//f1)wise scan function makes sure the user inputs an integer
int read_books_file ();//f2)reading books from the file and storing them in the array
int read_members_file();//f3)read members from file and store them in array
int read_borrows_file();//f4)read borrows from file and store them in array
//f5)date_comparison...compares year first .. then month .. then day
int date_compare(Date d1, Date d2);
//f6)gets time programmatically
void acquire_date_current();
//f7)checks for books whose due to return date has passed and wasn't returned using my date compare function
void overdue_books();
void display_overdue(int n);//f8) display overdue books list
//f9)most popular books .. searches until popular count reaches 5
void most_popular_books(int way);
void edit_book(); //f10) editing the information of existing book
//f11)searches for a particular ISBN of a book in the books array and returns its index
int check_ISBN_in_books(char ISBN[]);
//f12)searches for a particular ISBN of a book in the borrows array and returns its index
int check_ISBN_in_borrows(char ISBN[],char ID[]);
//f13)searches for a particular ID of a user in the members array and returns its index
int check_ID(char ID[]);
void return_book();//f14)return book after borrowing function
void display_found(int n);//f15) prints the target search information
int book_struct_copy(int x,int y);//f16)struct copy function
//f17)Uppers the case of the first letter in each word in a string
void capitalization(char*string,int n);
int search_by_title(int way);//f18) search by Book title or part of it function
int search_by_author(int way,int prev);//f19)
int search_by_ISBN(int way,int prev);//f20)
int search_by_category(int way,int prev);//f21)
int multi_search();//f22)
int search_for_a_book(int way);//f23)
void insert(); //f24) insert a new book
void add_new_copy();//f25) adding new book copy
void delete_book(); //f26) deleting a book from the list
void register_(); //f27) registration of new member
int number_validation(char number[]);//f28)
int word_validation(char word[]);//f29)
int ISBN_validation(char ISBN[]);//f30)
int email_validation(char email[]);//f)31 email validation
void Name_validation(char*name);//f32) last and first name validation
void phone_validation(char phone[]);//f33) phone number validation
void remove_member ();//f34)
void savebook();//f35) saving the changes in books array into file
void savemember();//f36) saving the changes in members array into file
void saveborrow();//f37) saving the changes in Borrows array into file
void print_books(); //f38) print all books data in the books array
void print_members();//f39) print all members data in the members array
void print_borrows();//f40) print all members data in the members array
void print_all();//f41) printing administration function
void borrow_book(char *ID);//f42)
void check_member_books();//f43)checking the number of borrowed books for that member to make sure that he has the right to borrow another book or not
void savetotal(int way);//f44) saves all the data in the 3 arrays into files
void my_exit();//f45) exiting function
void bookmanagement();//f46) managing the operations of books array
void administrative();//f47)
void main_menu(int way);// f48)program's main menu
void member_management();//f49)
void borrow_management ();//f50)
//f51) function that waits for an input from the user to direct him either back into the previous sub-menu
//or directly to the main menu upon getting special character 'm'
void wait_for_it(int x);


int main()

{
    books=(book*)malloc(50*sizeof(book));
    overdue=(borrow*)malloc(50*sizeof(borrow));
    foundbks=(book*)malloc(50*sizeof(book));
    members=(member*)malloc(50*sizeof(member));
    borrows=(borrow*)malloc(50*sizeof(member));
    int i,borrowsize=0,membersize=0,booksize=0;
    borrowarraysize=read_borrows_file();
    memberarraysize=read_members_file();
    bookarraysize=read_books_file();
    main_menu(2);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////books functions////////////////////////////////////////////////////////////////
//reading books from the file and storing them in the array
int read_books_file (){
    FILE* f;
    int i=0;
    f=fopen("books.txt","r");
    if(f==NULL) // checking the existence of the file
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
void edit_book(){
    int i,x=0,bookindex=0;
    char ISBN[18],newdata[50];
    do{
    printf("Please enter the ISBN of the book you wish to modify: \n");
    scanf("%s",ISBN);
    }while(ISBN_validation(ISBN)==0);
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(ISBN,books[i].ISBN);
       // printf("%d\n",x);
        if(x==0)
        {
            bookindex=i;
             break;
        }


}
 if (x!=0)
 {
      printf("THIS ISBN DOES NOT EXIST!");
     bookindex=-1;
     wait_for_it(1);
 }

    char c;
    if (bookindex!=-1)
    {printf("Please select which data would you like to configure:\n1)Title\n2)Author\n3)Category\n4)Publisher\n");
    char y;
    y=wise_scan(2);
    do{
    printf("Please enter the new data you wish to insert:\n");
    getchar();
    scanf("%[^\n]",newdata);
    }while(word_validation(newdata)==0);
    switch (y){
case '1':
    strcpy(books[bookindex].Book_Title,newdata);
    break;
case '2':
    strcpy(books[bookindex].Author,newdata);
    break;
case '3':
    strcpy(books[bookindex].category,newdata);
    break;
case '4':
    strcpy(books[bookindex].publisher,newdata);
    break;
    }
    wait_for_it(1);}
}
//searches for a particular ISBN of a book in the books array and returns its index
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
//Uppers the case of the first letter in each word in a string .. char cc resembles capital case
void capitalization(char*string,int n)// takes array and its size
{
    int i;
    char cc;
    cc=toupper(string[0]);
    string[0]=cc;
    for(i=1;i<n;i++)
    {
        if(string[i]==' '&&!(string[i+1]=='t' && string[i+2]=='o'))
        {
            cc=toupper(string[i+1]);
            string[i+1]=cc;
        }
    }

}
int search_for_a_book(int way){
    printf("Please enter the desired method of searching:\n1)Search by book title\n2)Search by author name\n3)Search by ISBN\n4)Search by book category\n5)Multi Search\nChoice(1-2-3-4-5)?\n");
    int y;
    char c='n';
    char x;
    x=wise_scan(2);
    switch (x){
case '1':
    Sleep(0.5);
    system("cls");
    y=search_by_title(1);
    break;
case '2':
    Sleep(0.5);
    system("cls");
    y=search_by_author(1,0);
    break;
case '3':
    Sleep(0.5);
    system("cls");
    y=search_by_ISBN(1,0);
    break;
case '4':
    Sleep(0.5);
    system("cls");
    y=search_by_category(1,0);
    break;
case '5':
    Sleep(0.5);
    system("cls");
    y=multi_search();
    break;
    }
    if (way==1)
    wait_for_it(1);
    if (way==2)
        return y;
}

int multi_search()
{
    int x,y,z,l,all;
    x=search_by_title(2);
    y=search_by_author(2,x);
    z=search_by_ISBN(2,y);
    l=search_by_category(2,z);
    all=x+y+z+l;
    display_found(all);
    return all;
}
int search_by_title(int way){
    char key[50]; // the target of the search
    char title[50];
    int foundcount=0,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    do{
    printf("Please enter the title of the book: \n");
    getchar();
    scanf("%[^\n]",key);
    }while(word_validation(key)==0); // scanning the target title for search
    if(strlen(key)<4)
        return 0;
    int i,j,k,l,x=0,titlelen=0,keylen=0,found=0,not_duplicate=1;
    keylen=strlen(key);
    capitalization(key,keylen); // capitalize the first letter of the target title
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].Book_Title,key);
        if(x==0){
            int way2;
            way2=book_struct_copy(foundcount,i);
            if(way2==1){
            foundcount++;
            book_index[foundcount]=i;}//stores the index of the book in main array to allow for future editing on book after search
        }

    }
    for(i=0;i<bookarraysize;i++)//loop that compares the find key which each other word in the books' title in case the user inputs a part of the title only
    {
        int titlelen=strlen(books[i].Book_Title);
        strcpy(title,books[i].Book_Title);
        for(j=0;j<titlelen;j++)
        {
            if(title[j]==key[0])
            {
                for(k=1;k<keylen;k++)
                {
                    if(title[j+k]!=key[k])
                        break;
                    if(k==keylen-2)
                    {
                        found=1;
                    }
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
            int way2;
            way2=book_struct_copy(foundcount,i);
            if(way2==1){
            foundcount++;
            book_index[foundcount]=i;}
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
    if(foundcount>0 && way!=2)
        display_found(foundcount);

        return foundcount;
}


int search_by_author(int way,int prev){
    char key[50];
    int foundcount=prev,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    do{
    printf("Please enter the name of the author: \n");
    fflush(stdin);
    scanf("%[^\n]",key);
    }while(word_validation(key)==0);
    if(strlen(key)<2)
        return 0;
    char cc;
    cc=toupper(key[0]);
    key[0]=cc;
    int i,x=0;
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].Author,key);
        if(x==0){
            int way2;
            way2=book_struct_copy(foundcount,i);
            if(way2==1){
            foundcount++;
            book_index[foundcount]=i;}//stores the index of the book in main array to allow for future editing on book after search
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
    if(foundcount>0 && way!=2)
        display_found(foundcount);

        return foundcount;
}


int search_by_ISBN(int way,int prev){
    char key[50];
    int foundcount=prev,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    do{
    printf("Please enter the ISBN: \n");
    getchar();
    fflush(stdin);
    scanf("%[^\n]",key);
    }while(ISBN_validation(key)==0 && way!=2);
    //printf("%d\n",strlen(key));
    int ol;
    for(ol=0;ol<strlen;ol++)
        //printf("%c\t",key[ol]);
    if(strlen(key)<2)
        return 0;
    int i,x=0;
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].ISBN,key);
        if(x==0){
            int way2;
            way2=book_struct_copy(foundcount,i);
            if(way2==1){
            foundcount++;
            book_index[foundcount]=i;};//stores the index of the book in main array to allow for future editing on book after search
        }

    }
    char c;
    if(foundcount==0 && way!=2)
    {
        printf("ISBN wasn't found!\n");
    }
    //if(c=='Y'||'y')
        //search_for_a_book();
    //else
        //main_menu();
    if(foundcount>0 && way!=2)
        display_found(foundcount);

        return foundcount;
}


int search_by_category(int way,int prev){
    char key[50];
    int foundcount=prev,*book_index;
    book_index=(int*)malloc(10*sizeof(int));
    do{
    printf("Please enter the category: \n");
    fflush(stdin);
    scanf("%[^\n]",key);
    }while(word_validation(key)==0);
    if(strlen(key)<2)
        return 0;
    char cc;
    cc=toupper(key[0]);
    key[0]=cc;
    int i,x=0;
    printf("Key is %s\n",key);
    for(i=0;i<bookarraysize;i++)
    {
        x=strcmp(books[i].category,key);
        if(x==0){
            int way2;
            way2=book_struct_copy(foundcount,i);
            if(way2==1){
            foundcount++;
            book_index[foundcount]=i;}//stores the index of the book in main array to allow for future editing on book after search
        }

    }
    char c;
    if(foundcount==0 & way!=2)
    {
        printf("Category wasn't found!\n");
    }
    //if(c=='Y'||'y')
      //  search_for_a_book();
    //else
       // main_menu();
    if(foundcount>0 && way!=2)
        display_found(foundcount);
        return foundcount;
}


void insert(){
    char ISBN[18];
    int x;

     printf("Enter information of the new book\n");
     do{
     printf("Please enter book's title: ");getchar();
     //fgets(books[bookarraysize].Book_Title,100,stdin);
     scanf("%[^\n]s",books[bookarraysize].Book_Title);
     }while(word_validation(books[bookarraysize].Book_Title)==0);
     capitalization(books[bookarraysize].Book_Title,strlen(books[bookarraysize].Book_Title));
     do{
     printf("Please enter the author of the book: ");getchar();
     scanf("%[^\n]s",books[bookarraysize].Author);
     }while(word_validation(books[bookarraysize].Author)==0);
     capitalization(books[bookarraysize].Author,strlen(books[bookarraysize].Author));

     do{
     printf("Please enter publisher of the book: ");getchar();
     scanf("%[^\n]s",books[bookarraysize].publisher);
     }while(word_validation(books[bookarraysize].publisher)==0);
     capitalization(books[bookarraysize].publisher,strlen(books[bookarraysize].publisher));
     do{
     printf("Please enter ISBN of book: (as 978-3-16-148410-0)\n");
     scanf("%s",ISBN);
    }while(ISBN_validation(ISBN)==0);
     strcpy(books[bookarraysize].ISBN,ISBN);
     x=check_ISBN_in_books(books[bookarraysize].ISBN);//validates the uniqueness of the new book ISBN
     if(x!=-1)
     {
        printf("Same ISBN already exists for another registered book!!\n");
        printf("Please enter ISBN of book: ");getchar();
     scanf("%[^\n]s",books[bookarraysize].ISBN);}

    do { printf("Please enter date of publication:(day month year) ");
     scanf("%d%d%d",&books[bookarraysize].DateOfPuplication.day,&books[bookarraysize].DateOfPuplication.month,&books[bookarraysize].DateOfPuplication.year);}
     while ((books[bookarraysize].DateOfPuplication.day>31 || books[bookarraysize].DateOfPuplication.day<1)|| (books[bookarraysize].DateOfPuplication.month>12 || books[bookarraysize].DateOfPuplication.month<1)
          || (books[bookarraysize].DateOfPuplication.year>2018 || books[bookarraysize].DateOfPuplication.year < 1600));
      printf("Please enter number of copies: ");getchar();
     scanf("%d",&books[bookarraysize].number_of_copies);
     books[bookarraysize].current_available_number_of_copies=books[bookarraysize].number_of_copies;
     printf("Please enter category of book: ");getchar();
     scanf("%[^\n]s",books[bookarraysize].category);
     capitalization(books[bookarraysize].category,strlen(books[bookarraysize].category));
     books[bookarraysize].borrows=books[bookarraysize].number_of_copies-books[bookarraysize].current_available_number_of_copies;
        bookarraysize++;
    wait_for_it(1);
 }

 void add_new_copy(){
    char ISBN[18];
    int copies;
    int i,r,flag=0;
    do{
    printf("Enter ISBN of the book as (978-3-16-148410-0):\n");
    scanf("%s",ISBN);
    }while(ISBN_validation(ISBN)==0);
    printf("Enter number of copies of the book(must be non-negative number): ");
    do {scanf("%d",&copies);} while (copies<0); // "no negative values" check
    for (i=0;i<bookarraysize;i++){
            r= strcmp(books[i].ISBN,ISBN);// if ISBN found increment the no. of copies by the value entered
        if(r==0)
           {
             books[i].number_of_copies+=copies;
             books[i].current_available_number_of_copies+=copies;
                printf("Copies added successfully!!");
                flag=1;

            }

   }
   if(flag==0)
    printf("Book wasn't found!!");
   wait_for_it(1);
   }
void delete_book(){
    char ISBN[18];
    int found=0,pos,i;
    do{
    printf("enter ISBN of the book as (978-3-16-148410-0):\n");
    scanf("%s",ISBN);
    }while(ISBN_validation(ISBN)==0);
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

           printf("Book deleted successfully!!");
           bookarraysize--; // decrease size of the book array by 1

}
else printf("BOOK NOT FOUND\n");
wait_for_it(1);
}
// saving the changes from the books array to books file
void savebook()
{
    FILE *fbook;
    int i;
    fbook=fopen("books.txt","w");
    if (fbook!=NULL)
    {
        for (i=0;i< bookarraysize ; i++ )
        {
            fprintf(fbook,"%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d\n",books[i].Book_Title,books[i].Author,books[i].publisher,books[i].ISBN
                        ,books[i].DateOfPuplication.day,books[i].DateOfPuplication.month,books[i].DateOfPuplication.year
                        ,books[i].number_of_copies,books[i].current_available_number_of_copies,books[i].category,books[i].borrows);
        }

    }
    fclose(fbook);

}
// prints all data in books array
void print_books(){
    int n=bookarraysize;
    int i;
    printf("Book Title,Author,Publisher,ISBN,Date of Publication,Number of copies,Current Available,Category,Borrows\n");
    for(i=0;i<n;i++)
    {
        printf("%d)%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d\n",i+1,books[i].Book_Title,books[i].Author,books[i].publisher,books[i].ISBN,
           books[i].DateOfPuplication.day,books[i].DateOfPuplication.month,books[i].DateOfPuplication.year,books[i].number_of_copies,
           books[i].current_available_number_of_copies,books[i].category,books[i].borrows);
    }
    wait_for_it(5);
}
//struct copy function
int book_struct_copy(int x,int y){
    int i,duplicate=0,done=0;
    for(i=0;i<x-1;i++)
    {
        if(strcmp(foundbks[i].ISBN,books[y].ISBN)==1)
            duplicate=1;
    }
    if(duplicate!=1){
    strcpy(foundbks[x].Author,books[y].Author);
    strcpy(foundbks[x].Book_Title,books[y].Book_Title);
    strcpy(foundbks[x].category,books[y].category);
    foundbks[x].current_available_number_of_copies=books[y].current_available_number_of_copies;
    foundbks[x].DateOfPuplication=books[y].DateOfPuplication;
    strcpy(foundbks[x].ISBN,books[y].ISBN);
    foundbks[x].number_of_copies=books[y].number_of_copies;
    strcpy(foundbks[x].publisher,books[y].publisher);
    foundbks[x].borrows=books[y].borrows;
    done=1;
    }
    return done;

}
void display_found(int n){
    int i;
    char c;
    printf("Search Results:\n");
    for(i=0;i<n;i++)
    {
        if(foundbks[i].DateOfPuplication.day!=0)
        {
        printf("%d)%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d\n",i+1,foundbks[i].Book_Title,foundbks[i].Author,foundbks[i].publisher,foundbks[i].ISBN
               ,foundbks[i].DateOfPuplication.day,foundbks[i].DateOfPuplication.month,foundbks[i].DateOfPuplication.year
               ,foundbks[i].number_of_copies,foundbks[i].current_available_number_of_copies,foundbks[i].category,foundbks[i].borrows);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////members functions///////////////////////////////////////////////////////////////////
//read members from file and store them in array
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
//searches for a particular ID of a user in the members array and returns its index

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
int number_validation(char number[])
{
    int i,valid=1;
    char c;
    for(i=0;i<strlen(number)-1;i++)
    {
        c=number[i];
        if(isdigit(c)==0){
            printf("Required data must contain numbers!\n");
            valid=0;}
    }
    return valid;

}
int word_validation(char word[])
{
    int i,valid=1;
    char c;
    for(i=0;i<strlen(word)-1;i++)
    {
        c=word[i];
        if(isdigit(c)!=0){
            valid=0;
            printf("A word can't contain numbers!!\n");
    }
    return valid;
}
}

int ISBN_validation(char ISBN[])
{
    int len,i,hyphencount=0,sum=0,x;
    len=strlen(ISBN);
    if(!(len==17 || len==13))
    {
        printf("Wrong ISBN format 1!\n");
        return 0;
    }
    for(i=0;i<len-1;i++)
        if(ISBN[i]=='-')
            hyphencount++;
    if(hyphencount<3)
    {
        printf("Wrong ISBN format 2!\n");
        return 0;
    }
    if(len==14)
    {
        int j=10;
        for(i=0;i<len-1;i++)
        {
            if(ISBN[i]=='-')
                i++;
            x=atoi(ISBN[i]);
            sum+=x*j;
            j--;
        }
        if(sum%11!=0)
        {
            printf("Wrong ISBN format 3!\n");
            return 0;
        }
    }
    if(len==18)
    {
        int j=13;
        for(i=0;i<len-1;i++)
        {
            if(ISBN[i]=='-')
                i++;
            x=atoi(ISBN[i]);
            sum+=x*j;
            j--;
        }
        if(sum%10!=0)
        {
            printf("Wrong ISBN format 4!\n");
            return 0;
        }
    }
    return 1;
}
int email_validation(char email[])
{
    int i,valid=1,found=0;
    int len=strlen(email);
    //printf("check beta");
    for(i=0;i<len-1;i++)
    {
        if(email[i]=='@')
            found=1;
    }
    if(found==0)
        valid=0;
    //printf("chechk gamma");
    if(email[len-1]!='m' || email[len-2]!='o' || email[len-3]!='c' || email[len-4]!='.')
        valid=0;
    if(valid==0){
        printf("Please enter a correct e-mail format!!\n");
}
//printf("check alpha");
return valid;
}
void phone_validation(char phone[])
{ int i=0;
     scanf("%s",phone);
     while (phone[i]!='\0')
     {
         if (phone[i] !='0'&& phone[i] !='1'&&phone[i] !='2'&&phone[i] !='3'&&phone[i] !='4'&&phone[i] !='5'&&phone[i] !='6'
             &&phone[i] !='7'&&phone[i] !='8'&& phone[i] !='9')
 {
              printf("Please Enter numbers only\n");
                        scanf("%s",phone);
          }

    i++;
     }
    if (strlen(phone)!=11 || phone[0]!='0' || phone[1]!='1' || (phone[2]!='1' &&phone[2]!='2' &&phone[2]!='0' &&
                                         phone[2]!='5'))
   {

    do {  printf("Wrong Number Format\nPlease enter member's phone number: ");
            scanf("%s",phone);
            i=0;
            while (phone[i]!='\0')
     {
         if (phone[i] !='0'&& phone[i] !='1'&&phone[i] !='2'&&phone[i] !='3'&&phone[i] !='4'&&phone[i] !='5'&&phone[i] !='6'
             &&phone[i] !='7'&&phone[i] !='8'&& phone[i] !='9')
 {
              printf("Please Enter numbers only\n");
                        scanf("%s",phone);
          }

    i++;
     }
            }
    while (strlen(phone)!=11 || phone[0]!='0' || phone[1]!='1' || (phone[2]!='1' &&phone[2]!='2' &&phone[2]!='0' &&
                                                                    phone[2]!='5'));
                                                                    }}
 void Name_validation(char*name)
 {
      int i=0;
      fflush(stdin);
  scanf("%[^\n]",name);
     while (name[i]!='\0')
     {
         if (name[i] =='0'|| name[i] =='1'||name[i] =='2'||name[i] =='3'||name[i] =='4'||name[i] =='5'||name[i] =='6'
             ||name[i] =='7'||name[i] =='8'|| name[i] =='9')
 {
              printf("Wrong Entry\nPlease Enter The right Name format: ");
                        scanf("%[^\n]",name);
          }

    i++;
     }
     if (strlen(name)>50)
     {
         do { printf("Wrong Entry\nPlease Enter The right Name format: ");
         scanf("%[^\n]",name);
         int i=0;

     while (name[i]!='\0')
     {
         if (name[i] =='0'|| name[i] =='1'||name[i] =='2'||name[i] =='3'||name[i] =='4'||name[i] =='5'||name[i] =='6'
             ||name[i] =='7'||name[i] =='8'|| name[i] =='9')
 {
              printf("Wrong Entry\nPlease Enter The right Name format:");
                        scanf("%[^\n]",name);
          }

    i++;
     }
         }while (strlen(name)>50);
     }

 }
// registration of a new member function
void register_(){
    int n;
    char ID[10];
    char phone[12];
    char building[4];
    char *firstName=(char*)malloc(50*sizeof(char));
    char *lastName=(char*)malloc(50*sizeof(char));
    int x;
    n=memberarraysize++;
    printf("Please enter member's first name: ");
    Name_validation(firstName);
    strcpy(members[n].first_name,firstName);

    printf("Please enter member's last name: ");
    fflush(stdin);
    Name_validation(lastName);
    strcpy(members[n].last_name,lastName);
    //scanf("%[^\n]",members[n].last_name);
    do{
    printf("Please enter member's ID: ");fflush(stdin);
    scanf("%[^\n]",ID);
    }while(number_validation(ID)==0);
    x=check_ID(ID);// check validation of the new ID added
    if(x==-1)
        strcpy(members[n].ID,ID);
    else{
        printf("Same ID already exits for another registered member!!\m");
        printf("Please enter member's ID: ");getchar();
    scanf("%[^\n]",ID);
    }
    printf("Please enter member's address:\n");
    printf("building: ");
    scanf("%s",building);
  int i=0; // building validation

     while (building[i]!='\0')
     {
         if (building[i] !='0'&& building[i] !='1'&&building[i] !='2'&&building[i] !='3'&&building[i] !='4'&&building[i] !='5'&&building[i] !='6'
             &&building[i] !='7'&&building[i] !='8'&& building[i] !='9')
 {
              printf("Please Enter the Building number only\n");
                        scanf("%s",building);
          }

    i++;
     }
     if (strlen(building)>3)
     {
         do { printf("WRONG BUILDING NUMBER\nbuilding: ");
         scanf("%s",building);
         int i=0;

     while (building[i]!='\0')
     {
         if (building[i] !='0'&& building[i] !='1'&&building[i] !='2'&&building[i] !='3'&&building[i] !='4'&&building[i] !='5'&&building[i] !='6'
             &&building[i] !='7'&&building[i] !='8'&& building[i] !='9')
 {
              printf("Please Enter the Building number only\n");
                        scanf("%s",building);
          }

    i++;
     }
         }while (strlen(building)>3);
     }
    strcpy(members[n].member_address.building,building);
    printf("\nstreet: ");getchar();
    scanf("%[^\n]",members[n].member_address.street);
    do{
    printf("\ncity: ");getchar();
    scanf("%[^\n]",members[n].member_address.city);
    }while(word_validation(members[n].member_address.city)!=1);
    printf("Please enter member's phone number: ");
    phone_validation(phone);
    strcpy(members[n].member_Phone_Number, phone );
    do{
    printf("Please enter member's age: ");getchar();
    scanf("%[^\n]",&members[n].member_age);
    }while(number_validation(members[n].member_age)==0);
    do{
    printf("Please enter member's e-mail: ");getchar();
    scanf("%[^\n]",members[n].member_Email);
    }while(email_validation(members[n].member_Email)==-1);
    members[n].borrows=0;
    wait_for_it(2);
}

void remove_member (){
int n=memberarraysize;
int n2=borrowarraysize;
int i;
int flag=0;
int k;
char*ID;
ID=(char*)malloc(15*sizeof(char));
do{
printf("Please enter member's ID: ");
scanf("%s",ID);
}while(number_validation(ID)==0);
for(i=0;i<n2;i++)
{
    if(strcmp(borrows[i].user_i,ID)==1)
    {
        if(borrows[i].date_returned.day==0)
        {
        printf("ID belongs to a user in borrowing registry! Please return the book!!\n ");
        wait_for_it(2);
        }
    }
}
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

// saving the changes from the members array to members file
void savemember()
{
    FILE *fmember;
    int i;
    fmember=fopen("members.txt","w");
    if (fmember!=NULL)
    {
        for (i=0;i< memberarraysize ; i++ )
        {
            fprintf(fmember,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",members[i].last_name,members[i].first_name,members[i].ID,members[i].member_address.building,members[i].member_address.street,members[i].member_address.city
                          ,members[i].member_Phone_Number,members[i].member_age,members[i].member_Email,members[i].borrows);
        }

    }
    fclose(fmember);

}
// prints all data in members array
void print_members(){
    int n=memberarraysize;
    int i;
    printf("First Name,Last Name,ID,Address,Phone Number,Age,E-mail,Borrows\n");
    for(i=0;i<n;i++)
    {
        printf("%d)%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",i+1,members[i].first_name,members[i].last_name,members[i].ID,members[i].member_address.building
               ,members[i].member_address.street,members[i].member_address.city,members[i].member_Phone_Number,members[i].member_age,members[i].member_Email
               ,members[i].borrows);
    }
    wait_for_it(5);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////borrows functions//////////////////////////////////////////////////////////////////////////////
//read borrows from file and store them in array
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


//gets time programmatically
void acquire_date_current(){
    time_t date_current1=time(NULL);
    struct tm tm=*localtime(&date_current1);
    date_current.day=tm.tm_mday;
    date_current.month=tm.tm_mon+1;//month numbered from 1 to 11 .. must add 1
    date_current.year=tm.tm_year+1900;//function gets years since 1900 .. must add 1900 to get current year
}
//date_comparison...compares year first .. then month .. then day
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

//checks for books whose due to return date has passed and wasn't returned using my date compare function
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
    if(n>0){
    printf("List of Overdue books: \n");
    for(i=0;i<n;i++)
    {
    printf("%d)%s,%s,%d-%d-%d,%d/%d/%d,%d/%d/%d\n",i+1,overdue[i].borrowed_ISBN,overdue[i].user_i,overdue[i].date_borrowed.day,overdue[i].date_borrowed.month
                    ,overdue[i].date_borrowed.year,overdue[i].date_due_to_return.day,overdue[i].date_due_to_return.month
                    ,overdue[i].date_due_to_return.year,overdue[i].date_returned.day,overdue[i].date_returned.month,overdue[i].date_returned.year);

}
    }
    else
        printf("No overdue books!!");
wait_for_it(4);
}


//most popular books .. searches until popular count reaches 5
void most_popular_books(int way){
    int i,j,max=0,popularcount=0;i;
    popular=(book*)malloc(5*sizeof(book));
    for(i=0;i<bookarraysize;i++)//loop gets maximum number of borrows in the library
    {
        if(books[i].borrows>max)
            max=books[i].borrows;
    }
    int x=5;
    if (bookarraysize<5)
        x=bookarraysize;
    while(popularcount!=x)
    {
        for(i=0;i<bookarraysize;i++)
        {
            if(books[i].borrows==max){//in case more than one book have same number of borrows
                popular[popularcount]=books[i];
                popularcount++;
                }
            if(popularcount==5)
                break;

        }
        max--;//decrement the max value to search for the less popular books
    }
printf("Most Popular %d books: \n",x,popularcount);
for(j=0;j<popularcount;j++)
{
    printf("%d)%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d\n",j+1,popular[j].Book_Title,popular[j].Author,popular[j].publisher,popular[j].ISBN,
           popular[j].DateOfPuplication.day,popular[j].DateOfPuplication.month,popular[j].DateOfPuplication.year,popular[j].number_of_copies,
           popular[j].current_available_number_of_copies,popular[j].category,popular[j].borrows);
}
if(way==2)
{
wait_for_it(4);
}
}


//searches for a particular ISBN of a book in the borrows array and returns its index
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



//return book function
void return_book(){
    int x,y,z;
    char ISBN[15];
    char ID[10];
    do{
    printf("Please enter the ID of the user returning the book:\n");
    scanf("%s",ID);
    }while(number_validation(ID)==0);
    printf("Please enter the ISBN of the returned book: \n");
    scanf("%s",ISBN);
    x=check_ISBN_in_borrows(ISBN,ID);
    acquire_date_current();
    borrows[x].date_returned=date_current;
    y=check_ISBN_in_books(ISBN);
    books[y].current_available_number_of_copies++;
    books[y].borrows--;
    z=check_ID(ID);
    members[z].borrows--;
    printf("Book returned!");
    sleep(5);
    wait_for_it(3);


}

// saving the changes from the borrows array to borrows file
void saveborrow()
{
    FILE *fborrow;
    int i;
    fborrow=fopen("borrows.txt","w");
    if (fborrow!=NULL)
    {
        for (i=0;i< borrowarraysize ; i++ )
        {
            fprintf(fborrow, "%s,%s,%d/%d/%d,%d/%d/%d,%d/%d/%d\n",borrows[i].borrowed_ISBN,borrows[i].user_i,borrows[i].date_borrowed.day,borrows[i].date_borrowed.month
                    ,borrows[i].date_borrowed.year,borrows[i].date_due_to_return.day,borrows[i].date_due_to_return.month
                    ,borrows[i].date_due_to_return.year,borrows[i].date_returned.day,borrows[i].date_returned.month,borrows[i].date_returned.year);
        }

    }
    fclose(fborrow);

}

// prints all data in borrows array
void print_borrows(){
    int n=borrowarraysize;
    int i;
    printf("ISBN,ID,Date borrowed,Date due to return,Date returned\n");
    for(i=0;i<n;i++)
    {
        printf("%d)%s,%s,%d/%d/%d,%d/%d/%d,%d/%d/%d\n",i+1,borrows[i].borrowed_ISBN,borrows[i].user_i,borrows[i].date_borrowed.day,borrows[i].date_borrowed.month
               ,borrows[i].date_borrowed.year,borrows[i].date_due_to_return.day,borrows[i].date_due_to_return.month,borrows[i].date_due_to_return.year
               ,borrows[i].date_returned.day,borrows[i].date_returned.month,borrows[i].date_returned.year);
    }
    wait_for_it(5);
}
void borrow_book(char *ID){
    int k;
    int x;
    x=search_for_a_book(2);
    if(x>0){
    printf("Which of the books in the list do you wish to borrow?(Enter its list number)");
    scanf("%d",&k);
    int y;
    y=check_ID(ID);
    int z;
    z=check_ISBN_in_borrows(foundbks[k-1].ISBN,ID);
    if(z!=-1)
    {
        printf("The user is borrowing the same book now!!");
        wait_for_it(3);
    }
    if (foundbks[k-1].current_available_number_of_copies>0 && members[y].borrows<3){
    strcpy(borrows[borrowarraysize].borrowed_ISBN,foundbks[k-1].ISBN);
    strcpy(borrows[borrowarraysize].user_i,ID);
    printf("Please enter Dates as following\n Day/Month/Year");
    do{printf("\nDate borrowed: ");
      scanf("%d%d%d",&borrows[borrowarraysize].date_borrowed.day,&borrows[borrowarraysize].date_borrowed.month,&borrows[borrowarraysize].date_borrowed.year);
    }while ((books[bookarraysize].DateOfPuplication.day>31 || books[bookarraysize].DateOfPuplication.day<1)|| (books[bookarraysize].DateOfPuplication.month>12 || books[bookarraysize].DateOfPuplication.month<1)
          || (books[bookarraysize].DateOfPuplication.year>2018 || books[bookarraysize].DateOfPuplication.year < 1600));
    do{printf("\nDate due return: ");
      scanf("%d%d%d",&borrows[borrowarraysize].date_due_to_return.day,&borrows[borrowarraysize].date_due_to_return.month,&borrows[borrowarraysize].date_due_to_return.year);
    }while ((books[bookarraysize].DateOfPuplication.day>31 || books[bookarraysize].DateOfPuplication.day<1)|| (books[bookarraysize].DateOfPuplication.month>12 || books[bookarraysize].DateOfPuplication.month<1)
          || (books[bookarraysize].DateOfPuplication.year>2018 || books[bookarraysize].DateOfPuplication.year < 1600));
    borrows[borrowarraysize].date_returned.day=0;
    borrows[borrowarraysize].date_returned.month=0;
    borrows[borrowarraysize].date_returned.year=0;
    int z;
    char ISBN[20];
    strcpy(ISBN,foundbks[k-1].ISBN);
    z=check_ISBN_in_books(ISBN);
    books[z].current_available_number_of_copies--;
    books[z].borrows++;
    members[y].borrows++;
    printf("\nBook borrow registered successfully!!\n");
    borrowarraysize++;
}
}
    wait_for_it(3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////managing functions/////////////////////////////////////////////////////////////
//wise scan function makes sure the user inputs an integer
char wise_scan(int way){
    char c;
    int x;
    if(way==1){
    getchar();}
    do
    {

        printf("\nPlease enter a number from the list!!\n");
        fflush(stdin);
            scanf("%c",&c);
            x=isdigit(c);
    }while(x!=1);
    return c;
}

// printing arrays data administration function
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

//checking the number of borrowed books for that member to make sure that he has the right to borrow another book or not
void check_member_books(){
    char ID[9];
    int flag=0;
    int index;
    int i;
    do{
printf("please enter user ID:");
scanf("%s",ID);
    }while(number_validation(ID)==0);
for(i=0;i<memberarraysize;i++){
    if(strcmp(ID,members[i].ID)==0)
        { flag=1;
        index=i;
        break;
        }
}
if (flag==1)
    printf("User ID is Valid.");
    else{
            printf("Wrong ID");
            wait_for_it(3);}


    if(members[index].borrows<4){
        borrow_book(ID);}
    else
        printf("Sorry, you can't borrow more books");
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

// managing the available operations of books array
void bookmanagement(){
    int x,y;
printf("1)Insert a new book\n2)Search for a book\n3)Add a new copy\n4)Delete a book\n5)Edit a book\n6)Save changes\n7)Return to main menu\n");

printf("Please enter your choice: ");
char c;
c=wise_scan(1);
sleep(0.5);
    system("cls");
switch(c){
case '1':
    insert();
    break;
case '2':
    search_for_a_book(1);
    break;
case '3':
    add_new_copy();
    break;
case '4':
    delete_book();
    break;
case '5':
    edit_book();
    break;
case '6':
    savetotal(1);
    break;
case '7':
    main_menu(1);
    break;}
}
void administrative(){
    int x;
    printf("1)Most popular books\n2)Overdue books\n3)Save changes\n4)Back to main menu\n");

printf("Enter your choice: ");
char c;
c=wise_scan(1);
sleep(0.5);
    system("cls");
switch(c){
case '1':
    most_popular_books(2);
    break;
case '2':
    overdue_books();
    break;
case '3':
    savetotal(1);
    break;
case '4':
    main_menu(1);
    break;
}
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

void member_management(){
int x;
printf("1)Register\n2)Remove\n3)Save changes\n4)Return back to main menu\n");
printf("Please enter your choice: ");
char c;
c=wise_scan(1);
sleep(0.5);
    system("cls");
switch(c){
case '1':
    register_();
    break;
case '2':
    remove_member();
    break;
case '3':
    savetotal(1);
    break;
case '4':
    main_menu(1);
    break;
    }

}
void borrow_management (){
int x;
printf("1)Borrow\n2)Return book\n3)Save Changes\n4)Return to main menu\n");
printf("Please enter your choice: ");
char c;
c=wise_scan(1);
sleep(0.5);
    system("cls");
switch(c){
case '1':
    check_member_books();
    break;
case '2':
    return_book();
    break;
case '3':
    savetotal(1);
    break;
case '4':
    main_menu(1);
    break;
}
}

//function that waits for an input from the user to direct him either back into the previous sub-menu or directly to the main menu upon getting special character 'm'
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
