/*
 * File Name:		main.c
 * Name:			Joshua Andujar
 * Course:			COP 2220C at Valencia College
 * Facilitator:		David Stendel
 * Description:		A contact application with CRUD functionality
 * Team Members:	Jacob Buettner, Nathen Neel and Joshua Andujar
 * Date:
 */

#ifndef FINALPROJECT_DEFINITIONS_H

// Macros
#define MAX_STRING_LENGTH 50
#define MAX_NUMBER_OF_CONTACTS 250

// User Defined Types
typedef char String[MAX_STRING_LENGTH];

typedef struct {
	unsigned int id;
	String firstName;
	String lastName;
	unsigned int houseNumber;
	String streetName;
	String city;
	String state;
	unsigned int zip;
	unsigned long int phoneNumber;
	String email;
} Contact;

#define FINALPROJECT_DEFINITIONS_H
#endif //FINALPROJECT_DEFINITIONS_H
