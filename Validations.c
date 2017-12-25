#include "Validations.h"
#include "Members.h"
#include "bookheader.h"
#include "borrows.h"
#include "other.h"
#include "admin.h"

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
    }while(x!=1 || c=='0');
    return c;
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
