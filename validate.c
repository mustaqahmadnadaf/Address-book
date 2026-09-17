#include<stdio.h>
#include<string.h>
#include "contact.h"

#if 1
//  function for validate the name 
int validateName(char *name)
{
    int i;
    int flag=1;     //flag is 1 assuming first charcter is true

    if(name[0] == '\0')     //if first charecter is null 
    return 0;

    for(i = 0; name[i] != '\0'; i++)
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||
             ( name[i] >='a' && name[i] <= 'z' )||
             name[i] == ' ') )
        {
            flag=0;    //if character is not between A to Z or a to z or 'sapce'  
            break;
    
        }
    }
    return flag;   //returnig flag=0(invalid) or falg=1(valid)
}
#endif

#if 1
//this function validate phone number, beacuse number has to be in 10 digit
// or it does not contain any charcter or symbloe 
int validateNumber(char *phone)
{
    int i;
    int flag = 1;
    int len = strlen(phone);   //finding phone length in len
    
    if(len != 10)  // if number is not 10 digit
    return 0;

    for(i = 0;i < len;i++)
    {
        if(!(phone[i] >='0' && phone[i] <= '9'))
        {
            flag = 0;     //if charecter is not between 0 to 9 then condition is true menase number is not correct 
            break;      //break no need to check further
        }
    }
    return flag;  //return flag(1) if valid or flag(0) if invalid.
}
#endif

#if 1
//function for valtate the email is from user correct or not beacuse email has its certain structure
int validatemail(char *email)   
{
    int i;
    int flag = 1;
    
    if(!(email[0] >= 'a' && email[0] <= 'z')) //first character must be lower case 
    {
        return 0;
    }
    
    for(i = 0;email[i] != '\0'; i++)   //loop run until it found null
    {
        if(!((email[i] >= 'a' && email[i] <= 'z') ||  
            (email[i] >= '0' && email[i] <= '9') ||
             email[i] == '@'||
             email[i] == '.') )
        {
            flag = 0;  //if condition is true meanse mail not correct we break the loop no need to cheake further  
            break;
        }
    }

    if(flag==0)
    return 0;

    char *ptr = strstr(email,"@gmail.com");   //chaking gamail.com is present in string or not
    if(ptr == NULL)          
    return 0;     //if not ptr is NULL

    if(strcmp(ptr,"@gmail.com")!=0)
    return 0;        //strcmp return non zero value

    return 1;    //if difference is zero
}
#endif

#if 0
//function for cheake duplicate Name
int duplicateName(AddressBook *addressBook,char *name)
{
    for(int i=0;i < addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].name,name) == 0) //if strcamp==0 meanse both numbers are same
        {
            return 1;  //duplicate phone
        }
    }
    return 0; //if strcamp!=0 meanse no duplicate found
}
#endif

#if 1
//function for cheake duplicate Phone number
int duplicatePhone(AddressBook *addressBook,char *phone)
{
    for(int i=0;i < addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone) == 0) //if strcamp==0 meanse both numbers are same
        {
            return 1;  //duplicate phone
        }
    }
    return 0; //if strcamp!=0 meanse no duplicate found
}
#endif

#if 1
//function  for cheake duplicate email
int duplicateEmail(AddressBook *addressBook,char *email)
{
    for(int i=0;i < addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email)==0) //strcamp==0
        {
            return 1;  //duplicate email
        }
    }
    return 0; // if strcamp!=0 means no duplicate found
}
#endif
