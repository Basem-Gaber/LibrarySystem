#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
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
 book *books;
 member *members;
 borrow *borrows;
void insert(){
     books;
     printf("Enter information of the new book\n");
     printf("Please enter book's title: ");
     scanf("%s",book.Book_Title);
     printf("Please enter the author of the book: ");
     scanf("%s",book.Auther);
     printf("Please enter publisher of the book: ");
     scanf("%s",book.publisher);
     printf("Please enter ISBN of book: ");
     scanf("%s",book.ISBN);
     printf("Please enter date of publication: ");
     scanf("%s",book.DateOfPuplication);
     printf("Please enter number of copies: ");
     scanf("%d",&book.number_of_copies);
     printf("Please enter category of book: ");
     scanf("%s",book.category);

 }
void add_new(int n){
    char ISBN[18];
    int copies;
    int i;
    books[n];
    printf("enter ISBN of the book: ");
    scanf("%s", ISBN);
    printf("enter number of copies of the book: ");
    scanf("%d",&copies);
    for (i=0;i<n;i++){
        if(strcmp([i].ISBN, ISBN)==1)
            book[i].number_of_copies+=copies;
    }

}
void most_popular(){
printf("most popular books:\n");
printf("1)");

}
void delete_book(){



}
void bookmanagement(){
    int x;
printf("1)insert a new book\n2)search for a book\n3)add a new copy\n 4)delete a book\n");
do{
printf("Please enter your choice: ");
scanf("%d",&x);}while(x<=0|x>4);
switch(x){
case 1:
    insert();
    break;
case 2:
    search();
    break;
case 3:
    add_new();
    break;
case 4:
    delete_book();
    break;}
}
void main_menu(){
    int x;
printf("1)book management\n2)member management\n3)borrow management\n4)administrative actions\n5) save changes\n6) exit\n");
do{
printf("Enter your choice: ");
scanf("%d",&x);}while(x<=0|x>5);
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
    save();
    break;
case 6:
    exit();
    break;}

}
void member_management(){
int x;
printf("1)Register\n2)Remove\n3)Return back to main menu\n");
printf("Please enter your choice: ");
scanf("%d",&x);
switch(x){
case 1:
    register_();
    break;
case 2:
    remove_();
    break;
case 3:
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
    borrow();
    break;
case 2:
    return_();
    break;
case 3:
    main_menu();
    break
}
}

void register_(){
     members[n];
    printf("Please enter member's first name: ");
    scanf("%s",member.member_1st_name);
    printf("Please enter member's last name: ");
    scanf("%s",member.member_Phone_Number);
    printf("Please enter member's ID: ");
    scanf("%s",member.member_ID);
    printf("Please enter member's address:\n");
    printf("building: ");
    scanf("%s",member.member_address.building);
    printf("\nstreet: ");
    scanf("%s",member.member_address.street);
    printf("\ncity: ");
    scanf("%s",member.member_address.city);
    printf("Please enter member's phone number: ");
    scanf("%d",member.member_Phone_Number);
    printf("Please enter member's age: ");
    scanf("%d",member.member_age);
    printf("Please enter member's e-mail: ");
    scanf("%s",member.member_Email);
    n=n+1;
}
void remove (int n){
members[n];
int i;
int k;
printf("Please enter member's ID: ");
scanf("%s",member.member_ID);
for(i=0;i<n;i++){
    if(strcmp(members[i].member_ID,member.member_ID)==1){
        for (k=i;k<n;k++){
            books[i]=books[i+1];
        }


    }
}




}
FILE* Write_book()
 { int i=1,flag=0,test=0;
     FILE* bookPtr;
     bookPtr=fopen ("D:\\program1.txt" ,"w");
     if(bookPtr == NULL)
    {
       printf("Error!");
       exit(1);
    }
     printf("please enter the book information\nplease Enter -1 when you're Done\n");
     while (test!=-1)
     {
         printf("Enter the book title #%d\n",i);
         getchar();
         gets(bookInfo.Book_Title);
         fprintf(bookPtr,"%s\t",bookInfo.Book_Title);
          printf("Enter the book #%d auther\n",i);
          getchar();
         gets(bookInfo.Auther);
 fprintf(bookPtr,"%s\t",bookInfo.Auther);
         printf("Enter the book #%d publisher\n",i);
          getchar();
         gets(bookInfo.publisher);
         fprintf(bookPtr,"%s\t",bookInfo.publisher);
         printf("Enter the book #%d ISBN\n",i);
          getchar();
         gets(bookInfo.ISBN);
         fprintf(bookPtr,"%s\t",bookInfo.ISBN);
         printf("Enter the book #%d date of publication\n",i);
          getchar();
         gets(bookInfo.DateOfPuplication);
         fprintf(bookPtr,"%s\t",bookInfo.DateOfPuplication);
         printf("Enter the book #%d category\n",i);
          getchar();
         gets(bookInfo.category);
         fprintf(bookPtr,"%s\t",bookInfo.category);
          printf("Enter the book #%d number of copies\n",i);
          scanf("%d",&bookInfo.number_of_copies);
          fprintf(bookPtr,"%d\t",bookInfo.number_of_copies);
           printf("Enter the book #%d current available number of copies\n",i);
         scanf("%d",&bookInfo.current_available_number_of_copies);
         fprintf(bookPtr,"%d\n",bookInfo.current_available_number_of_copies);
       printf(" If you Done please enter -1\n");
       scanf("%d",&test);


 i++;

 } fclose(bookPtr);
 }

 int read_books_file (){
     FILE* f;
     int i=0;
     f=fopen("books.txt","r");
     if(f==NULL)
     {
         printf("Books text file doesn't exist!\n");
         exit(11);
     }
     while(!feof(f))
     {
         books[i]=fscanf(f,"%[^,]%[^,]%[^,]%[^,]%d%d%d%d%d%[^,]",books[i].Book_Title,books[i].Author,books[i].publisher,books[i].ISBN
                         ,books[i].DateOfPuplication.day,books[i].DateOfPuplication.month,books[i].DateOfPuplication.year,books[i].number_of_copies,books[i].current_available_number_of_copies,books[i].category);
         fscanf(f,"\n");
         i++;
     }
     fclose(f);
  return i+1;
 }

 int read_members_file(){
     FILE* f;
     int i=0;
     f=fopen("members.txt","r");
     if(f==NULL)
     {
         printf("Members text file doesn't exist!\n");
         exit(21);
     }
     while(!feof(f))
     {
         members[i]=fscanf(f,"%[^,]%[^,]%[^,]%[^,]%[^,]%[^,]",members[i].member_last_name,members[i].member_first_name,members[i].member_address.building,members[i].member_address.street,members[i].member_address.city
                           ,members[i].member_Phone_Number,members[i].member_age,members[i].member_Email);
         fscanf(f,"\n");
         i++;
     }
     fclose(f);
  return i+1;
 }

 int read_borrows_file(){
     FILE* f;
     int i=0;
     f=fopen("borrows.txt","r");
     if(f==NULL)
     {
         printf("Borrows file doesn't exist!\n");
         exit(31);
     }
     while(!feof(f))
     {
         borrows[i]=(f,"%[^,]%[^,]%d%d%d%d%d%d%d%d%d",borrows[i].borrowed_ISBN,borrows[i].user_i,borrows[i].date_borrowed.day,borrows[i].date_borrowed.month
                     ,borrows[i].date_borrowed.year,borrows[i].date_due_to_return.day,borrows[i].date_due_to_return.month
                     ,borrows[i].date_due_to_return.year,borrows[i].date_returned.day,borrows[i].date_returned.month,borrows[i].date_returned.year);
         fscanf(f"\n");
         i++;
     }
    fclose(f);
  return i+1;
 }





int main()
{
   main_menu();

 books=(book*)malloc(100*sizeof(book));
 members=(member*)malloc(100*sizeof(member));
 borrows=(borrow*)malloc(100*sizeof(member));
     FILE *BOOk_file_ptr;
 BOOk_file_ptr=Write_book();
    return 0;
}
