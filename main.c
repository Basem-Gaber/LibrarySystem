#include "Validations.h"
#include "Members.h"
#include "other.h"
#include "borrows.h"
#include "bookheader.h"
#include "admin.h"

void red(){
 system("COLOR 4"); // change font color
}
void background(){
system("COLOR FC");// change background color
}
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
