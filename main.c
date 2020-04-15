/*
 * File Name:		main.c
 * Name:			Joshua Andujar
 * Course:			COP 2220C at Valencia College
 * Facilitator:		David Stendel
 * Description:		A contact application with CRUD functionality
 * Team Members:	Jacob Buettner, Nathen Neel and Joshua Andujar
 * Date:
 */

/*
 * The struct should contain all fields related to what all people in your contacts have in
 * common,
 * vvvvvvvvvvvvvvvvvv
 * e.g., ID, first name, last name, street address, city, state, zip, phone, e-mail, etc.,
 * ^^^^^^^^^^^^^^^^^^
 * i.e., include fields you would typically expect to find in an address book. Make sure all data
 * entered by the user is appropriately validated. The application program should use a menu system
 * to do the functions concerning processing contacts,
 * vvvvvvvvvvvvvvvvvv
 * i.e., Create, Retrieve, Update, and Delete
 * ^^^^^^^^^^^^^^^^^^
 * (CRUD). Whether you use an array or list. The idea here is if the user selected Create from the
 * main menu, it would add a new contact, and then, add it to a single collection, e.g., an array.
 * As far as retrieving contacts, it should be able to retrieve all contacts, including all of their
 * data displayed in an appropriate list/table, and one or more contact's information as a result of
 * a search, which you can also use for the Update and Delete functions. Other search and sort
 * functions should be included as appropriate.
 * vvvvvvvvvvvvvvvvvv
 * It does need to be able to permanently store the information, e.g., to a file on the hard
 * drive. Make sure you thoroughly test saving and retrieving the information from a file,
 * ^^^^^^^^^^^^^^^^^^
 * because using pointers can make this tricky, i.e., the
 * next time the program is run from a different system, it may not retrieve the data as expected;
 * in other words, make sure you are saving the actual data and not just a pointer to the data.
 * Hint: Check for the appropriate file and retrieve any data at the start if necessary, i.e.,
 * the file may not exist initially, and then, create and save the data to a file at the end ready
 * to be retrieved the next time the program runs; in other words, you do not need to constantly
 * save and retrieve data from a file while the program is running.
 */

// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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

// Prototypes
void closeContactsFile(FILE**);
void createContact(Contact[]);
void getString(String string);
bool getUserChoice(Contact[]);
void openContactsFile(String, FILE**);
void printAllContacts(Contact[]);
void printMenu();
void printWelcome();
void readContactsFromFile(FILE**, Contact[]);
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
	String test;

	getString(test);

	// Open the file and retrieve contact information.
//	openContactsFile("contacts.txt", &spContacts);
//	readContactsFromFile(&spContacts, contacts);
//	closeContactsFile(&spContacts);
//
//	// User interaction
//	printWelcome();
//	do {
//		printMenu();
//	} while(getUserChoice(contacts));

	return 0;
} // end function main

void createContact(Contact contacts[]) {
	// Variables
	Contact contact = {0};

	contact.id = setID(contacts);
	getString(contact.firstName);

	contacts[contact.id - 1] = contact;
} // end function createContact

/*
 * Name:			closeContactsFile()
 * Parameters:		spContacts	The place where the contacts file to be closed is stored.
 * Processes:		Close an open contacts file.
 * Return Value:	None.
 */
void closeContactsFile(FILE** spFile) {
	// Calculation, closing a file
	if (fclose(*spFile) == EOF) {
		printf("\n**********\n\n");
		printf("\tError occurred while closing the file.");
		printf("\n\n**********\n");
		exit(101);
	} // end if
} // end function closeContactsFile

/* TODO: Incomplete documentation.
 * Name:			getString()
 * Parameters:		None.
 * Processes:		None.
 * Return Value:	None.
 */
void getString(String string) {
	// FIXME: Incomplete function.
	// Variables
	String input = "";

	// Getting input from user.
	printf("Enter a string: ");
	scanf("%[^\n]", input);

	// Validating input.
	for (int length = strlen(input); length; length--) {
		if (!isalpha(input[length - 1])) {
			getString(string);
		}
	}

	// Sending string back to caller.
	strcpy(string, input);
}

/*
 * Name:			getUserChoice()
 * Parameters:		None.
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

/*
 * Name:			openContactsFile()
 * Parameters:		fileName	A string representing the name of the file to be opened.
 * 					spContacts	The place where the opened contacts file will stored.
 * Processes:		Open or create the contacts file in append mode.
 * Return Value:	None.
 */
void openContactsFile(String fileName, FILE** spFile) {
	// Calculation, opening the contacts.txt file
	if ((*spFile = fopen(fileName, "a+")) == NULL) {
		printf("\n**********\n\n");
		printf("\tError occurred while opening the contacts.txt file.");
		printf("\n\n**********\n");
		exit(100);
	} // end if
} // end function openContactsFile

/* TODO: Incomplete documentation.
 * Name:			printAllContacts()
 * Parameters:		None.
 * Processes:		None.
 * Return Value:	None.
 */
void printAllContacts(Contact contacts[]) {
	for (int index = 0; index < MAX_NUMBER_OF_CONTACTS; index++) {
		if (contacts[index].id != 0) {
			printf(
					"%u\n%s\n%s\n%u\n%s\n%s\n%s\n%u\n%lu\n%s\n",
					contacts[index].id,
					contacts[index].firstName,
					contacts[index].lastName,
					contacts[index].houseNumber,
					contacts[index].streetName,
					contacts[index].city,
					contacts[index].state,
					contacts[index].zip,
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

/*
 * Name:			readContactsFromFile()
 * Parameters:		file		The file where contact information is stored.
 * 					contacts	The array where contacts are stored upon application start.
 * Processes:		Read all contacts from a file and store them into an array.
 * Return Value:	None.
 */
void readContactsFromFile(FILE** spFile, Contact contacts[]) {
	// Variables
	Contact contact = {0};
	int numOfContacts = 0;

	// File opened in append / update mode, rewind so that we can read data from file.
	rewind(*spFile);

	while (fscanf(
			*spFile,
			"%u %[^\n] %[^\n] %u %[^\n] %[^\n] %[^\n] %u %lu %[^\n]",
			&contact.id,
			contact.firstName,
			contact.lastName,
			&contact.houseNumber,
			contact.streetName,
			contact.city,
			contact.state,
			&contact.zip,
			&contact.phoneNumber,
			contact.email
			) == 10) {
		contacts[numOfContacts] = contact;
		numOfContacts += 1;
	}
} // end function readContactsFromFile

/*
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