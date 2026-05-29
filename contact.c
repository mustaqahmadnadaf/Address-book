#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include"validate.h"

void listContacts(AddressBook *addressBook, int sortChoice) 
{
    // check the address book is empty 
    if(addressBook->contactCount==0)
    {    
        printf("\33[31mNo contact found\33[0m\n");
        return;   //if no conatcts are there exit function
    }
    
    //print all contacts details
    printf("\n----List of contacts----\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("Contact %d:\n",i+1);
        printf("Name: %s\n",addressBook->contacts[i].name);
        printf("Phone: %s\n",addressBook->contacts[i].phone);
        printf("email: %s\n",addressBook->contacts[i].email);
        printf("------------------\n");    
    }
    
}

void initialize(AddressBook *addressBook) 
{    
   //start with zero contacts in the address book
   addressBook->contactCount = 0;
  
    //populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    //creating  name in contact

    char name[30];  //tempoary arry to store user input
    int ret;        //declering integer verible to store validation   
 
    do
    {
       printf("Enter the name: ");
       scanf("%[^\n]",name);       //getting input from user
       getchar();                  // remove leftover new line from buffer

       ret=validateName(name);    //function call for check name is valid(validate.c)

       if(ret==0)             //if name is incorrect
       {
        printf("\33[31mInvalid name, Please try again.\33[0m\n\n");
       }
        
    } while (ret==0);       //loop run again until find correct name

    //save name in addressBook structure
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);

    printf("\33[32m****Name added successfully****\33[0m\n\n");

    
    //creat phone nummber in contact
    char phone[20];   //taking tempparay arry for number
    int retnum;       //taking integer veriable return value store in retnum

    do
    {
        printf("Enter phone number: "); 
        scanf("%[^\n]",phone);     //taking input from user
        getchar();         //clear buffer

        retnum=validateNumber(phone);     //function call for validate number(validate.c)

        if(retnum==0)   //if return value in incorrect
        {
            printf("\33[31mInvalid number, please try again.\33[0m\n\n");
        }
        int dupli=duplicatePhone(addressBook,phone);  //function call for check duplicate number(validate.c)
    
        if(dupli==1)  //check duplicate phone number
        {
        printf("\33[31mError,phone number is alarady exists\33[0m\n\n");
        retnum=0;   //repeat 
        }
        
    } while (retnum==0);    //loop is repeat until it found correct number
    

    //save number in structure
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);  //
    printf("\33[32m****Number added successfully****\33[0m\n\n");
    

    //creat mail
    char email[50]; //store email input
    int retmail;  //store return value from validatemail
    do
    {
        printf("Enter email address: ");
        scanf("%[^\n]",email);    //taking input from user
        getchar();        //remove new line
       
        retmail=validatemail(email);     //fuction call  for validate email(logic in validate.c)
        
        if(retmail==0)   //if email is not correct
        {
            printf("\33[31mInvalid email,please try again\33[0m\n\n");
        }

       int dupli=duplicateEmail(addressBook,email);     //function call for check this alarady present or not
        if(dupli==1)
        {
            printf("\33[31mError,email is already exists\33[0m\n\n");
            retmail=0;
        }
    }while(retmail==0);   //loop repeat until valide email

    //save email into structure
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);

    //increment contactCount
    addressBook->contactCount++;

    printf("\33[32m****Contact added sucssefully****!\33[0m\n\n");
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    if(addressBook->contactCount==0)
    {   
        // if no contacts exists then no need to serch.
        printf("\33[31mNo cantact is  found to search.\33[0m\n");
        return ;
    }
    int choice;     //stored user choice
    char serchkey[50];  //temoparary string to store the serch text entered by user

    do       //using do while for checking correct choice
    {
        printf("\n---- Search Contact ----\n");
        printf("1. Search by Name\n");
        printf("2. Search by Phone\n");
        printf("3. Search by Email\n");
        printf("4. Exit serch\n");
        printf("Enter your choice: ");
            
        scanf("%d",&choice);   //read user choice 1(name),2(phone),3(email),4(exit)
        getchar();    //to remove leftover new line

        if(choice < 1 || choice > 4)   //we are checking is choice is  1,2,3,4 or not
        {
            printf("\33[31mInvalid choice, Please try again.\33[0m\n");
        }

    }while(choice <1 || choice >4);  //repeat untill choice is correct
    if(choice==4)
    {
        printf("\33[32m-----Exiting search-----\33[0m\n");
        return;
    }

    int found_index=0;  //to count how many matches found

    //ask user what text they want to search
    do
    {  
        printf("Enter serch text: ");
        scanf("%[^\n]",serchkey);     //read the serch text from user
        getchar(); 

        for(int i=0;i < addressBook->contactCount;i++)   //loop for find the match
        {
            int match=0;   //flag to indicate current cantact matches serch text
            
            //compare by name
            if(choice==1 && strcmp(addressBook->contacts[i].name,serchkey)==0)    //looking name is matching or not
            {  
                match=1;       
            }
              
            //compare by phone
            else if(choice==2 && strcmp(addressBook->contacts[i].phone,serchkey)==0)  //findinf phone number is matching
            {
                match=1;
            }
 
            //compare by email 
            else if(choice==3 && strcmp(addressBook->contacts[i].email,serchkey)==0)   //looking email is matching or not
            {
                match=1;
            }
        
            if(match)  //if  match found dispaly details
            {
                found_index++;  //intilize count
                printf("\n---MAtch %d---\n",found_index);
                printf("Name: %s\n",addressBook->contacts[i].name);
                printf("Phone: %s\n",addressBook->contacts[i].phone);
                printf("Email: %s\n",addressBook->contacts[i].email);
            }
        }

        if(found_index==0)  //if no match found repeat search
        {
            printf("\33[31mNo matching contact found.\33[0m\n\n");
        }

    }while(found_index==-1);
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    //if no contacts exits,there is nothing to edit
    if(addressBook->contactCount==0)
    {
        printf("\33[31mNo contact is avalilable to edit\33[0m\n");
        return;
    }

    char serchkey[50];  //temporary string to store input
    int index=-1;  //index of conatct to be edited

    printf("\n----Edit contact-----\n");
    printf("Enter name/phone/email of contact to edit: ");
    scanf("%[^\n]",serchkey);   //read serach key
    getchar();   //remove newline 

    //serchig contact using name/phone/email
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if( (strcmp(addressBook->contacts[i].name,serchkey)==0)||
        (strcmp(addressBook->contacts[i].phone,serchkey)==0) ||
        (strcmp(addressBook->contacts[i].email,serchkey)==0) )
        {
            index=i; //conatact found at this index
            break;
        }
    }

    if(index==-1)  //if contact is not exsit
    {
        printf("\33[31mContact not found.\33[0m\n");
        return;
    }

    //show contact detail before editing
    printf("\nContact Found:\n");
    printf("1. Name:  %s\n", addressBook->contacts[index].name);
    printf("2. Phone: %s\n", addressBook->contacts[index].phone);
    printf("3. Email: %s\n", addressBook->contacts[index].email);

    //chosse what has to edit or exit
    int choice;
    do 
    {
        printf("\nSelect what do you want to edit\n");
        printf("1.Edit Name\n");
        printf("2.Edit Phone\n");
        printf("3.Edit Email\n");
        printf("4.Exit\n");

       printf("Enter the choice: ");
        scanf("%d",&choice);  
        getchar();
        if(choice <1 ||choice >4) 
        {
            printf("\33[31mInvalid choice, please try again.\33[0m\n");
        }

    }while(choice <1 ||choice >4);  //loop repeate untill usere choose correct number
    
    if(choice==4) //if input is 4 exits from edit function 
    {
        return;
    }


    //Edit name
    if(choice==1)
    {
        char newName[30]; 
        int valid;

        do
        {
            printf("Enter new name: ");
            scanf("%[^\n]",newName);   //creating new name
            getchar();

            valid=validateName(newName);  //cheak phone format
            if(valid==0)
            {
                printf("\33[31mInvalid name.Try again.\33[0m\n");
            }
            
        } while (valid==0);  //loop repeat untill user give valid name
        
        strcpy(addressBook->contacts[index].name,newName);  //update name
        printf("\33[32mName is updated successfully\33[0m\n\n");
    }

    //edit phone number
    else if(choice==2)
    {
        char newPhone[20];
        int valid;

        do
        {
            printf("Enter new phone: ");
            scanf("%[^\n]", newPhone);
            getchar();

            valid = validateNumber(newPhone);  //validate phone number
            if(valid==0)
            {
                printf("\33[31mInvalid phone. Try again.\33[0m\n");
                continue;
            }
                
           // Check phone number is alarady exists
           if(duplicatePhone(addressBook, newPhone) == 1 &&
            strcmp(addressBook->contacts[index].phone, newPhone) != 0)
            {
                printf("\33[31mError: phone already exists.\33[0m\n");
                valid = 0;
            }

        }while(valid==0);  //loop repeat untill user give valid and unquie number
            
        strcpy(addressBook->contacts[index].phone, newPhone);  //update phone number
        printf("\33[32mPhone number updated successfully!\33[0m\n");
    }
        
    //Edit email 
    else if(choice == 3)
    {
        char newEmail[50];
        int valid;

        do {
            printf("Enter new email: ");
            scanf("%[^\n]", newEmail);
            getchar();

            valid = validatemail(newEmail);  //cheack email format
            if(!valid)
            {
                printf("\33[31mInvalid email, please try again.\33[0m\n");
                continue;
            }

            // Check duplicate email
            if(duplicateEmail(addressBook, newEmail) == 1 &&
               strcmp(addressBook->contacts[index].email, newEmail) != 0)
            {
                printf("\33[31mError: email already exists.\33[0m\n");
                valid = 0;
            }

        } while(!valid);

        strcpy(addressBook->contacts[index].email, newEmail); //update email
        printf("\33[32mEmail updated successfully!\33[0m\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    if(addressBook->contactCount==0)   //if contact is not exits,nothing to delete
    {
        printf("\33[31mContact is not found\33[0m\n");
        return;
    }
    char serchkey[30];  //temparray string to stored serch key
    int index=-1;    //stored index of contact to delete 

    printf("\nEnter the name/ phone/email: ");  //rread the serchkey(name/phone/email)
    scanf("%[^\n]",serchkey);   
    getchar();

    //serch contact by name or phone or email
    for(int i=0;i<addressBook->contactCount;i++)
    {
        //cheake name,phone ,email
        if((strcmp(addressBook->contacts[i].name,serchkey)==0) ||
           (strcmp(addressBook->contacts[i].phone,serchkey)==0) ||
           (strcmp(addressBook->contacts[i].email,serchkey)==0)) 
          {
            index=i;    //index where the contact is found
            break;    //stop serching after match
          }
    }
    if(index==-1)   //if we not found  contacts[i]==serchkey
    {
        printf("\33[31mContcts is not found\33[0m\n");
        return;
    }
    
    //if contact is found print detail
    printf("\33[32m----Contact is found---\33[0m\n");  
    printf("Name: %s\n",addressBook->contacts[index].name);
    printf("Number: %s\n",addressBook->contacts[index].phone);
    printf("email: %s\n",addressBook->contacts[index].email);

    int choice;  
    printf("\nDo you want to delete this contact\n");
    printf("0.No\n");
    printf("1.Yes\n");

    printf("Enter the choice: ");  //read input user what to delete or not
    scanf("%d",&choice);  //clear newline

    //if user choose not to delete
    if(choice==0)
    {
        printf("\33[32mDeletation cancelation\33[0m\n");
        return;
    }
    //Delete and shifting remaning contacts to left
    for(int i=index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];  //shifting contacts
    }
    //deleting number of catacts
    addressBook->contactCount--; //decrese total contacts

    printf("\33[32mContact Deleted succesfully\33[0m\n");
}
