#include <stdio.h>
#include "file.h"

//save all cnontacts to csv file
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contact.csv","w");   //open the file in write mode

    if(fp == NULL)  //if fopen() fails, fp becomes NULL
    {
        printf("\33[31mError: Cannot open cantact.csv for writing\33[0m\n");
        return;    
    }

    //write each contact in csv format: name, phone or email.
    for(int i = 0;i < addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
    }

    fclose(fp);  //close the file
    printf("\33[32mContacts saved successfully\33[0m\n");
}

//load all contacts from csv file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contact.csv","r");   //open file for reading
    
    if(fp == NULL) //if fopen() fails,fp becomes NULL
    {
        printf("\33[31mError: Cannot open cantact.csv for reading\33[0m\n");
        return;
    }

    addressBook->contactCount = 0;  //eset contact count

    //read until end of file
    while(!feof(fp))     //loop until EoF
    {    
        if(addressBook->contactCount>=MAX_CONTACTS)  //stop if we rech maximum cintacts
        break;

        //point to next contact structure
        Contact *c = &addressBook->contacts[addressBook->contactCount];

        //read one line in csv format:name until cama, number until coma or email until new line
        if(fscanf(fp,"%[^,],%[^,],%[^\n]\n",c->name,c->phone,c->email)==3)
        {
            addressBook->contactCount++;   //successfully read one contact
        }
        else
        {
            break;  //stop reading if format is mismatches
        }
    }
    fclose(fp);  //close file
}
