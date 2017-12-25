#include "Validations.h"
#include "Members.h"
#include "bookheader.h"
#include "borrows.h"
#include "other.h"
#include "admin.h"

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
    if(popular[j].borrows!=0)
    {
    printf("%d)%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d\n",j+1,popular[j].Book_Title,popular[j].Author,popular[j].publisher,popular[j].ISBN,
           popular[j].DateOfPuplication.day,popular[j].DateOfPuplication.month,popular[j].DateOfPuplication.year,popular[j].number_of_copies,
           popular[j].current_available_number_of_copies,popular[j].category,popular[j].borrows);
    }
}
if(way==2)
{
wait_for_it(4);
}
}
