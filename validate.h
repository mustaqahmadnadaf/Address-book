#ifndef validate_h
#define validate_h

#include "contact.h"

//validate a name
int validateName(char *name);

//validate phone number
int validateNumber(char *phone);

//validate email 
int validatemail(char *email);

//check duplicate name
int duplicate(AddressBook *addressBook,char *name);

//check duplicate phone number
int duplicatePhone(AddressBook *addressBook,char *phone);

//check duplicate email
int duplicateEmail(AddressBook *addressBook,char *email);
#endif