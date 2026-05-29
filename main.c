/* Name:Mustaqahmad iqbal nadaf.
Date:12/12/2025
Discription:This project implements a complete Address Book Management System in C.
    It allows the user to create, search, edit, delete, list and save contacts.
    
    The program uses a structure 'AddressBook' that stores multiple contacts,
    and each contact contains name, phone number and email ID.

    Features:
    1. Create Contact  
       - Adds a new contact after validating name, phone and email.
    
    2. Search Contact  
       - Search by name, phone or email.
       - Performs exact matching and displays full contact information.
    
    3. Edit Contact  
       - Allows modifying any field of an existing contact.
    
    4. Delete Contact  
       - Removes selected contact and shifts remaining contacts.
    
    5. List Contacts  
       - Displays all stored contacts (with sorting option if enabled).
    
    6. Save Contacts  
       - Writes all contacts to a CSV file (contact.csv).
    
    7. Exit  
       - Closes the program safely.

    Additional Notes:
    - Input validation is included for phone numbers and emails.
    - getchar() is used to clear input buffer after numeric inputs.
    - All operations use array indexing inside the AddressBook structure.

*/

#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    int sortChoice=0;
    do {
            printf("\nAddress Book Menu:\n");
            printf("1. Create contact\n");
            printf("2. Search contact\n");
            printf("3. Edit contact\n");
            printf("4. Delete contact\n");
            printf("5. List all contacts\n");
            printf("6. Save contacts\n");		
            printf("7. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();
            
            switch (choice) 
            {
                case 1:
                    createContact(&addressBook);
                    break;
                case 2:
                    searchContact(&addressBook);
                    break;
                case 3:
                    editContact(&addressBook);
                    break;
                case 4:
                    deleteContact(&addressBook);
                    break;
                case 5:          
                    listContacts(&addressBook,sortChoice);
                    break;
                case 6:
                    printf("Saving and Exiting...\n");
                    saveContactsToFile(&addressBook);
                    break;
                case 7:
                    printf("\33[32mexiting from address book\33[0m\n");
                    return 0;
                    break;
                default:
                    printf("\33[31mInvalid choice, Please try again.\33[0m\n");
            }

        } while (choice != 7);
    
    return 0;
}
