#include <stdio.h>
#include <stdlib.h>
typedef struct {
char Book_Title[100];
char Author[50];
char publisher[50];
char ISBN[18]; // International Standard Book Number ..Example: 978-3-16-148410-0
char DateOfPuplication[11]; // Example 30/11/2017
int number_of_copies ;
int current_available_number_of_copies;
char category[30];
}book;
book bookInfo;
 typedef struct {
     char building[4];
     char street[20];
     char city[20];
 }address;
typedef struct{
char member_first_name[50];
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

 FILE* Write_book( );
void read_files_file();
void read_members_file();
void read_borrows_file();
int main()
{
  FILE *BOOk_file_ptr;
BOOk_file_ptr=Write_book();
    return 0;
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

book *books;
books=(book*)malloc(100*sizeof(book));
member *members;
members=(member*)malloc(100*sizeof(member));
borrow *borrows;
borrows=(borrow*)malloc(100*sizeof(member));

void read_books_file (){
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
        books[i]=fscanf(f,"%[^,]%[^,]%[^,]%[^,]%[^,]%d%d%[^,]",books[i].Book_Title,books[i].Author,books[i].publisher,books[i].ISBN
                        ,books[i].DateOfPuplication,books[i].number_of_copies,books[i].current_available_number_of_copies,books[i].category);
        fscanf(f,"\n");
        i++;
    }
    fclose(f);
}

void read_members_file(){
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
}

void read_borrows_file(){
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
        borrows[i]=(f,"%[^,]%[^,]%[^,]%[^,]%[^,]",borrows[i].borrowed_ISBN,borrows[i].user_i,borrows[i].date_borrowed.day,borrows[i].date_borrowed.month
                    ,borrows[i].date_borrowed.year,borrows[i].date_due_to_return.day,borrows[i].date_due_to_return.month
                    ,borrows[i].date_due_to_return.year,borrows[i].date_returned.day,borrows[i].date_returned.month,borrows[i].date_returned.year);
        fscanf(f"\n");
        i++;
    }
    fclose(f);
}

