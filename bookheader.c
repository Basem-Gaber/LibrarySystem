#include "Validations.h"
#include "Members.h"
#include "bookheader.h"
#include "borrows.h"
#include "other.h"
#include "admin.h"


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
    if(all>0)
    {
    display_found(all);
    }
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
    if(strlen(key)<2)
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
    if(foundcount==0 && strlen(key)>2)
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
    if(foundcount==0  && strlen(key)>2)
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
    //printf("Key is %s\n",key);
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
