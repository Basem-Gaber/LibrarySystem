#include "Validations.h"
#include "Members.h"
#include "bookheader.h"
#include "borrows.h"
#include "other.h"
#include "admin.h"

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
    sleep(0.5);
    wait_for_it(3);


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
    printf("%d and %d",(foundbks[k-1].current_available_number_of_copies>0),(members[y].borrows<3));
    if (foundbks[k-1].current_available_number_of_copies>0 && members[y].borrows<3){
    strcpy(borrows[borrowarraysize].borrowed_ISBN,foundbks[k-1].ISBN);
    strcpy(borrows[borrowarraysize].user_i,ID);
    printf("Please enter Dates as following\n Day/Month/Year");
    do{printf("\nDate borrowed: ");
      scanf("%d%d%d",&borrows[borrowarraysize].date_borrowed.day,&borrows[borrowarraysize].date_borrowed.month,&borrows[borrowarraysize].date_borrowed.year);
    }while ((borrows[borrowarraysize].date_borrowed.day>31 || borrows[borrowarraysize].date_borrowed.day<1)|| (borrows[borrowarraysize].date_borrowed.month>12 || borrows[borrowarraysize].date_borrowed.month<1)
          || (borrows[borrowarraysize].date_borrowed.year>2018 || borrows[borrowarraysize].date_borrowed.year < 1600));
    do{printf("\nDate due return: ");
      scanf("%d%d%d",&borrows[borrowarraysize].date_due_to_return.day,&borrows[borrowarraysize].date_due_to_return.month,&borrows[borrowarraysize].date_due_to_return.year);
    }while ((borrows[borrowarraysize].date_due_to_return.day>31 || borrows[borrowarraysize].date_due_to_return.day<1)|| (borrows[borrowarraysize].date_due_to_return.month>12 || borrows[borrowarraysize].date_due_to_return.month<1)
          || (borrows[borrowarraysize].date_due_to_return.year>2018 || borrows[borrowarraysize].date_due_to_return.year < 1600));
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
else{
printf("No books available to be borrowed or user already borrowed 3 books!\n");
}
}
    wait_for_it(3);
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
            fprintf(fborrow, "%s,%s,%d/%d/%d,%d/%d/%d,%d/%d/%d\n",borrows[i].borrowed_ISBN,borrows[i].user_i,borrows[i].date_borrowed.day,borrows[i].date_borrowed.month
                    ,borrows[i].date_borrowed.year,borrows[i].date_due_to_return.day,borrows[i].date_due_to_return.month
                    ,borrows[i].date_due_to_return.year,borrows[i].date_returned.day,borrows[i].date_returned.month,borrows[i].date_returned.year);
        }

    }
    fclose(fborrow);

}
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
