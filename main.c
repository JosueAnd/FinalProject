/*
 * File Name:		main.c
 * Name:			Joshua Andujar
 * Course:			COP 2220C at Valencia College
 * Facilitator:		David Stendel
 * Description:		A contact application with CRUD functionality
 * Team Members:	Jacob Buettner, Nathen Neel and Joshua Andujar
 * Date:
 */

// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "definitions.h"
#include "fileLogic.h"

// Prototypes
void createContact(Contact[]);
void getString(String string);
bool getUserChoice(Contact[]);
void printAllContacts(Contact[]);
void printMenu();
void printWelcome();
int setID(Contact[]);

/*
 * Name:			main()
 * Parameters:		None.
 * Processes:		TODO: Add a function description here.
 * Return Value:	An integer representing an error code; if the program ends without error, zero
 *					will be returned to the calling program or operating system.
 */
int main() {
	// Variables
	FILE *spContacts = NULL;
	Contact contacts[MAX_NUMBER_OF_CONTACTS] = {0};

	// Open the file, retrieve contact information and close file.
	openContactsFile("contacts.txt", &spContacts);
	readContactsFromFile(&spContacts, contacts);
	closeContactsFile(&spContacts);

	// User interaction
	printWelcome();
	do {
		printMenu();
	} while(getUserChoice(contacts));

	return 0;
} // end function main

/*
 * Name:			createContact()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		Prompt the user to enter values for all fields of a Contact and add to contacts.
 * Return Value:	None.
 */
void createContact(Contact contacts[]) {
	// Variables
	Contact contact = {0};

	// ID is auto set as last known ID + 1.
	contact.id = setID(contacts);

	// Getting all other fields as input from user.
	printf("Please enter the first name of the contact: ");
	getString(contact.firstName);

	printf("Please enter the last name of the contact: ");
	getString(contact.lastName);

	printf("Please enter the house number of the contact: ");
	//getInt(contact.houseNumber);

	printf("Please enter the street name the contact lives at: ");
	getString(contact.streetName);

	printf("Please enter the city the contact lives in: ");
	getString(contact.city);

	printf("Please enter the state the contact lives in: ");
	getString(contact.state);

	printf("Please enter the contact's zip code: ");
	//getInt(contact.zip);

	printf("Please enter the contact's phone number: ");
	//getInt(contact.phoneNumber);

	printf("Please enter the contact's email: ");
	getString(contact.email);

	// Adding contact to contacts array, index is always ID - 1.
	contacts[contact.id - 1] = contact;
} // end function createContact

/*
 * Name:			getString()
 * Parameters:		string		The String where user input will be stored.
 * Processes:		Accepts input from the user and validates. If validation fails the function
 * 					will loop, prompting for input until validation passes.
 * Return Value:	None.
 */
void getString(String string) {
	// Variables
	String input = "";
	bool errorFlag = false;

	do {
		// Getting user input. FIXME: Allow no input for empty field, set to zero?
		if (fgets(input, MAX_STRING_LENGTH, stdin) == NULL) {
			errorFlag = true; // If no characters read in or error occurs, set errorFlag to true
		} else {
			errorFlag = false;
		}

		// Validating input.
		for (unsigned long length = strlen(input); length; length--) {
			if (!(isalpha(input[length - 1]) ||
				  isspace(input[length - 1])) ||
				errorFlag) {
				errorFlag = true;
				printf("\n**********\n\n");
				printf("\tError: Invalid characters entered.");
				printf("\t\tPlease try again, but with only characters A - Z or a - z.");
				printf("\n\n**********\n");
				break;
			} else {
				errorFlag = false;
			}
		} // end for loop
	} while (errorFlag);

	// Assigning user input to passed in field.
	strcpy(string, input);
} // end function getString

/* TODO: Incomplete documentation.
 * Name:			getUserChoice()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		Get an integer choice matching a menu option and call appropriate functions
 * 					to carry out that process.
 * Return Value:	An integer representing the users choice to continue interacting with the
 * 					program (non-zero value) or terminate its use (zero).
 */
bool getUserChoice(Contact contacts[]) {
	// Variables
	char inStr = 0;
	unsigned int choice = 0;
	bool sentinel = true;

	printf("Choice: ");
	scanf("%s", &inStr);
	choice = strtoul(&inStr, NULL, 0);

	// Call the appropriate function for the chosen menu option.
	switch(choice) {
		case 1:
			createContact(contacts);
			break;
		case 2:
			printAllContacts(contacts);
			break;
		// FIXME: Incomplete switch logic.
//		case 3:
//			use strstr(haystack, needle) to find portion and return it
//			printf("");
//			break;
//		case 4:
//			printf("");
//			break;
//		case 5:
//			printf("");
//			break;
		case 6:
			printf("\n\nYou have chosen to exit. Good bye! :)\n\n");
			sentinel = false;
			break;
		default:
			// Display message to use warning of invalid choice.
			printf("\n**********\n\n");
			printf("\tInvalid option chosen. Please try again entering the number to the "
					"left of the option in the displayed menu.");
			printf("\n\n**********\n");
			// Reprint the menu.
			printMenu();
			// Catch the return value of the recurred function for continuance or exit condition.
			sentinel = getUserChoice(contacts);
			break;
	} // end switch
	return sentinel;
} // end function getUserChoice

/* TODO: Incomplete documentation.
 * Name:			printAllContacts()
 * Parameters:		contacts
 * Processes:		None.
 * Return Value:	None.
 */
void printAllContacts(Contact contacts[]) {
	for (int index = 0; index < MAX_NUMBER_OF_CONTACTS; index++) {
		if (contacts[index].id != 0) {
			// Print name.
			printf(
					"Name: %s %s\n",
					contacts[index].firstName,
					contacts[index].lastName
			);
			// Print address.
			printf(
					"Address:\n\t%u %s\n\t%s, %s %u\n",
					contacts[index].houseNumber,
					contacts[index].streetName,
					contacts[index].city,
					contacts[index].state,
					contacts[index].zip
					);
			// Print contact information.
			printf(
					"Phone Number: %lu\nEmail: %s\n",
					contacts[index].phoneNumber,
					contacts[index].email
					);
		}
	}
} // end function printAllContacts

/*
 * Name:			printMenu()
 * Parameters:		None.
 * Processes:		Print a menu of application options to the user.
 * Return Value:	None.
 */
void printMenu() {
	printf("____________________________________________________________________________\n");
	printf("|                                                                          |\n");
	printf("|                              Menu Options:                               |\n");
	printf("|                              _____________                               |\n");
	printf("|                                                                          |\n");
	printf("| 1) Create a new contact.                                                 |\n");
	printf("| 2) Print all contacts.                                                   |\n");
	printf("| 3) Contact search.                                                       |\n");
	printf("| 4) Update a contact.                                                     |\n");
	printf("| 5) Delete a contact.                                                     |\n");
	printf("| 6) Save and exit.                                                        |\n");
	printf("|                                                                          |\n");
	printf("____________________________________________________________________________\n");
} // end function printMenu

/*
 * Name:			printWelcome()
 * Parameters:		None.
 * Processes:		Print a welcome message to the user.
 * Return Value:	None.
 */
void printWelcome() {
	printf("____________________________________________________________________________\n");
	printf("|                                                                          |\n");
	printf("|                        Welcome to the Contact Book                       |\n");
	printf("|                                                                          |\n");
} // end function printWelcome

/* TODO: Incomplete documentation.
 * Name:			setID()
 * Parameters:		None.
 * Processes:		Set the ID for a new contact.
 * Return Value:	An integer value to be used as a new Contact's ID.
 */
int setID(Contact contacts[]) {
	// Variables
	int greatestID = 0,
		index = 0;
	if (contacts[index].id == 0) {
		return 1;
	} else {
		while(contacts[index].id > greatestID) {
			greatestID += 1;
			index += 1;
		}
		return greatestID + 1;
	}
} // end function setID