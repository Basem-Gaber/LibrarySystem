#include "Validations.h"
#include "Members.h"
#include "bookheader.h"
#include "borrows.h"
#include "other.h"
#include "admin.h"

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
    scanf("%[^\n]",members[n].member_age);
    }while(number_validation(members[n].member_age)==0 || strlen(members[n].member_age)>2);
    do{
    printf("Please enter member's e-mail: ");getchar();
    scanf("%[^\n]",members[n].member_Email);
    }while(email_validation(members[n].member_Email)==0);
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
    if(strcmp(borrows[i].user_i,ID)==0)
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
