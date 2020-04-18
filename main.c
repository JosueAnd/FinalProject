/*
 * File Name:		main.c
 * Name:			Joshua Andujar
 * Course:			COP 2220C at Valencia College
 * Facilitator:		David Stendel
 * Description:		A contact application with CRUD functionality.
 * Team Members:	Nathen Neel and Joshua Andujar
 * Date:
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
void getEmail(String);
unsigned int getInt();
void getString(String);
bool getUserChoice(Contact[]);
void openContactsFile(String, FILE**, String);
void printAllContacts(Contact[], char);
void printMenu();
void printUpdateOptions();
void printWelcome();
void readContactsFromFile(Contact[], FILE**);
void saveAndExit(Contact[], String);
void searchContacts(Contact[]);
int setID(Contact[]);
void toLower(String, const String);
void updateContact(Contact[]);
void writeToFile(Contact[], FILE**);

/*
 * Name:			main()
 * Parameters:		None.
 * Processes:		Runs a contact book with functionality to Create, Retrieve, Update and Delete
 * 					contact information.
 * Return Value:	An integer representing an error code; if the program ends without error, zero
 *					will be returned to the calling program or operating system.
 */
int main() {
	// Variables
	FILE* spContacts;
	Contact contacts[MAX_NUMBER_OF_CONTACTS] = {0};

	// Open the file, retrieve contact information and close file.
	openContactsFile("contacts.txt", &spContacts, "a+");
	readContactsFromFile(contacts, &spContacts);
	closeContactsFile(&spContacts);

	// User interaction
	printWelcome();
	do {
		printMenu();
	} while(getUserChoice(contacts));

	return 0;
} // end function main

/*
 * Name:			closeContactsFile()
 * Parameters:		spFile		The place where the contacts file to be closed is stored.
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

/*
 * Name:			createContact()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		Prompt the user to enter values for all fields of a Contact and add to contacts.
 * Return Value:	None.
 */
void createContact(Contact contacts[]) {
	// Variables
	Contact* pContact = &contacts[setID(contacts) - 1];

	// ID is auto set as last known ID + 1. The + 1 is accounted for in setID.
	pContact -> id = setID(contacts);

	// Getting all other fields as input from user.
	printf("Please enter the first name of the contact: ");
	getString(pContact -> firstName);

	printf("Please enter the last name of the contact: ");
	getString(pContact -> lastName);

	printf("Please enter the house number of the contact: ");
	pContact -> houseNumber = getInt();

	printf("Please enter the street name the contact lives at: ");
	getString(pContact -> streetName);

	printf("Please enter the city the contact lives in: ");
	getString(pContact -> city);

	printf("Please enter the state the contact lives in: ");
	getString(pContact -> state);

	printf("Please enter the contact's zip code: ");
	pContact -> zip = getInt();

	printf("Please enter the contact's phone number: ");
	pContact -> phoneNumber = getInt();

	printf("Please enter the contact's email: ");
	getEmail(pContact -> email);
} // end function createContact

/*
 * Name:			getEmail()
 * Parameters:		string		The String where user input will be stored.
 * Processes:		Accepts input from the user and validates. If validation fails the function
 * 					will loop, prompting for input until validation passes.
 * Return Value:	None.
 */
void getEmail(String string) {
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
				  isspace(input[length - 1]) ||
				  ispunct(input[length - 1])) ||
				errorFlag) {
				errorFlag = true;
				printf("\n**********\n\n");
				printf("\tError: Invalid characters entered.");
				printf("\t\tPlease try again, but with only letters A - Z or a - z.");
				printf("\n\n**********\n");
				printf("\nNew Attempt: ");
				break;
			} else {
				if (input[length - 1] == '\n')
					input[length - 1] = '\0';
				errorFlag = false;
			}
		} // end for loop
	} while (errorFlag);

	// Assigning user input to passed in field.
	strcpy(string, input);
} // end function getEmail

/*
 * Name:			getInt()
 * Parameters:		None.
 * Processes:		Accepts input from the user and validates. If validation fails the function
 * 					will loop, prompting for input until validation passes.
 * Return Value:	An integer chosen by the application user.
 */
unsigned int getInt() {
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
			if (!(isdigit(input[length - 1]) ||
				  input[length - 1] == '\n') ||
				errorFlag) {
				errorFlag = true;
				printf("\n**********\n\n");
				printf("\tError: Invalid characters entered.");
				printf("\t\tPlease try again, but with only numbers 1 - 9.");
				printf("\n\n**********\n");
				printf("\nNew Attempt: ");
				break;
			} else {
				if (input[length - 1] == '\n') {
					input[length - 1] = '\0';
				}
				errorFlag = false;
			}
		} // end for loop
	} while (errorFlag);

	// Assigning user input to passed in field.
	return strtol(input, NULL, 0);
} // end function getInt

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
				printf("\t\tPlease try again, but with only letters A - Z or a - z.");
				printf("\n\n**********\n");
				printf("\nNew Attempt: ");
				break;
			} else {
				if (input[length - 1] == '\n')
					input[length - 1] = '\0';
				errorFlag = false;
			}
		} // end for loop
	} while (errorFlag);

	// Assigning user input to passed in field.
	strcpy(string, input);
} // end function getString

/*
 * Name:			getUserChoice()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		Get an integer choice matching a menu option and call appropriate functions
 * 					to carry out that process.
 * Return Value:	An integer representing the users choice to continue interacting with the
 * 					program (non-zero value) or terminate its use (zero).
 */
bool getUserChoice(Contact contacts[]) {
	// Variables
	unsigned int choice = 0;
	bool sentinel = true;

	printf("Choice: ");
	choice = getInt();

	// Call the appropriate function for the chosen menu option.
	switch(choice) {
		case 1:
			createContact(contacts);
			break;
		case 2:
			printAllContacts(contacts, 'v');
			break;
		case 3:
			searchContacts(contacts);
			break;
		case 4:
			updateContact(contacts);
			break;
			// FIXME: Incomplete switch logic.
//		case 5:
//			printf("");
//			break;
		case 6:
			printf("\n\nYou have chosen to exit. Good bye! :)\n\n");
			sentinel = false;
			saveAndExit(contacts, "contacts.txt");
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
 * 					spFile		The place where the opened contacts file will stored.
 * Processes:		Open or create the contacts file in append mode.
 * Return Value:	None.
 */
void openContactsFile(String fileName, FILE** spFile, String mode) {
	// Calculation, opening the contacts.txt file
	if ((*spFile = fopen(fileName, mode)) == NULL) {
		printf("\n**********\n\n");
		printf("\tError occurred while opening the contacts.txt file.");
		printf("\n\n**********\n");
		exit(100);
	} // end if
} // end function openContactsFile

/* TODO: Incomplete documentation.
 * Name:			printAllContacts()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		Prints all contacts and information from the contact book.
 * Return Value:	None.
 */
void printAllContacts(Contact contacts[], char mode) {
	printf
			("\n|                                Contacts:                                 |\n");
	for (int index = 0; index < MAX_NUMBER_OF_CONTACTS; index++) {
		if (contacts[index].id != 0) {
			printf
					("============================================================================");
			// Print name.
			printf(
					"\n\nName: %s %s\n",
					contacts[index].firstName,
					contacts[index].lastName
			);
			if (mode == 'v') {
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
						"Phone Number: %lu\nEmail: %s\n\n",
						contacts[index].phoneNumber,
						contacts[index].email
				);
			} else if (mode == 'u') {
				printf("ID: %u\n\n", contacts[index].id);
			}
		} // end if
	} // end for
	printf("============================================================================");
	printf
			("\n|                              End Contacts:                               |\n\n");
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
 * Name:			printUpdateOptions()
 * Parameters:		None.
 * Processes:		Print a menu of update options to the user.
 * Return Value:	None.
 */
void printUpdateOptions() {
	printf("____________________________________________________________________________\n");
	printf("|                                                                          |\n");
	printf("|                             Update Options:                              |\n");
	printf("|                             _______________                              |\n");
	printf("|                                                                          |\n");
	printf("| 1) First Name.                                                           |\n");
	printf("| 1) Last Name.                                                            |\n");
	printf("| 3) House Number.                                                         |\n");
	printf("| 4) Street Name.                                                          |\n");
	printf("| 5) City.                                                                 |\n");
	printf("| 6) State.                                                                |\n");
	printf("| 7) Zip Code.                                                             |\n");
	printf("| 8) Phone Number.                                                         |\n");
	printf("| 9) Email.                                                                |\n");
	printf("|                                                                          |\n");
	printf("____________________________________________________________________________\n");
} // end function printUpdateOptions

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
 * Parameters:		spFile			The file where contact information is stored.
 * 					contacts[]		The array where contacts are stored upon application start.
 * Processes:		Read all contacts from a file and store them into an array.
 * Return Value:	None.
 */
void readContactsFromFile(Contact contacts[], FILE** spFile) {
	// Variables
	int numOfContacts = 0;
	Contact* contact = &contacts[numOfContacts];

	rewind(*spFile);

	// TODO: Look into doing this with fgets, for example see getString()
	while (fscanf(
			*spFile,
			"%u %[^\n] %[^\n] %u %[^\n] %[^\n] %[^\n] %u %lu %[^\n]",
			&contact -> id,
			contact -> firstName,
			contact -> lastName,
			&contact -> houseNumber,
			contact -> streetName,
			contact -> city,
			contact -> state,
			&contact -> zip,
			&contact -> phoneNumber,
			contact -> email
	) == 10) {
		numOfContacts += 1;
		contact = &contacts[numOfContacts];
	}
} // end function readContactsFromFile

/*
 * Name:			saveAndExit()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * 					fileName		A string representing the name of the file to be opened.
 * Processes:		Open the contacts file, prepare for writing, write contacts to the file and
 * 					close.
 * Return Value:	None.
 */
void saveAndExit(Contact contacts[], String fileName) {
	FILE* contactsFile = NULL;
	openContactsFile(fileName, &contactsFile, "w");
	writeToFile(contacts, &contactsFile);
	closeContactsFile(&contactsFile);
} // end function saveAndExit

/*
 * Name:			searchContacts()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		TODO: Add processes.
 * Return Value:	TODO: Add return value.
 */
void searchContacts(Contact contacts[]) {
	// Variables
	Contact results[MAX_NUMBER_OF_CONTACTS] = {0};
	Contact* pContact = NULL;
	int numOfMatches = 0;
	String searchCriteria = "";

	printf("Please enter a name to search by (First or Last, not both): ");
	getString(searchCriteria);

	// Converting searchCriteria to lower case for comparison.
	toLower(searchCriteria, searchCriteria);

	// Searching through contacts for a match
	for (int contact = 0; contact < MAX_NUMBER_OF_CONTACTS; contact++) {
		pContact = &contacts[contact];
		if (pContact -> id != 0) {
			String tempFirstName = "";
			String tempLastName = "";
			toLower(tempFirstName, pContact -> firstName);
			toLower(tempLastName, pContact -> lastName);
			if (strstr(tempFirstName, searchCriteria) ||
				strstr(tempLastName, searchCriteria)) {
				results[numOfMatches] = contacts[contact];
				numOfMatches += 1;
			} // end inner if
		} // end outer if
	} // end for

	// Print contacts if at least one match was found, else notify of no matches.
	if (numOfMatches > 0) {
		printAllContacts(results, 'v');
	} else {
		printf
				("\n|         Sorry, no contacts found matching your search criteria.          |\n");
	}
} // end function searchContacts

/*
 * Name:			setID()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
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

/* TODO: Incomplete documentation.
 * Name:			toLower()
 * Parameters:		None.
 * Processes:		None.
 * Return Value:	None.
 */
void toLower(String copy, const String original) {
	for (int character = 0; original[character] != '\0' && original[character] != '\n'; character++) {
		if (original[character] >= 'A' && original[character] <= 'Z') {
			copy[character] = original[character] + 32;
		} else {
			copy[character] = original[character];
		}
	}
} // end function toLower

/*
 * Name:			updateContact()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		TODO: Add processes.
 * Return Value:	TODO: Add return value.
 */
void updateContact(Contact contacts[]) {
	// Variables
	Contact* pContact = NULL;
	bool errorFlag = false;

	// Print contacts in update mode for user to choose from and enter ID.
	printAllContacts(contacts, 'u');

	// Ask which contact they want to update.
	printf("Which contact do you want to update? Enter their ID number: ");
	pContact = &contacts[getInt() - 1];

	do {
		// Reset errorFlag on every iteration.
		errorFlag = false;
		// Ask what about the contact they would like to update.
		printUpdateOptions();
		printf("What about this contact do you want to update? Enter an option number from the "
			   "menu above: ");

		// Switch
		switch (getInt()) {
			case 1:
				printf("Please enter the first name of the contact: ");
				getString(pContact -> firstName);
				break;
			case 2:
				printf("Please enter the last name of the contact: ");
				getString(pContact -> lastName);
				break;
			case 3:
				printf("Please enter the house number of the contact: ");
				pContact -> houseNumber = getInt();
				break;
			case 4:
				printf("Please enter the street name the contact lives at: ");
				getString(pContact -> streetName);
				break;
			case 5:
				printf("Please enter the city the contact lives in: ");
				getString(pContact -> city);
				break;
			case 6:
				printf("Please enter the state the contact lives in: ");
				getString(pContact -> state);
				break;
			case 7:
				printf("Please enter the contact's zip code: ");
				pContact -> zip = getInt();
				break;
			case 8:
				printf("Please enter the contact's phone number: ");
				pContact -> phoneNumber = getInt();
				break;
			case 9:
				printf("Please enter the contact's email: ");
				getEmail(pContact -> email);
				break;
			default:
				// Display message to use warning of invalid choice.
				printf("\n**********\n\n");
				printf("\tInvalid option chosen. Please try again entering the number to the "
					   "left of the option in the displayed menu.");
				printf("\n\n**********\n");
				errorFlag = true;
		} // end switch
	} while (errorFlag);
} // end updateContact

/*
 * Name:			writeToFile()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * 					spFile			The place where the opened contacts file will stored.
 * Processes:		Write contacts to the file, resetting index numbers here to prevent the need
 * 					to refactor contacts on delete operations.
 * Return Value:	None.
 */
void writeToFile(Contact contacts[], FILE** spFile) {
	for (int contact = 0, index = 1; contact < MAX_NUMBER_OF_CONTACTS; contact++) {
		if (contacts[contact].id != 0) {
			fprintf(
					*spFile,
					"%u\n%s\n%s\n%u\n%s\n%s\n%s\n%u\n%lu\n%s\n",
					index,
					contacts[contact].firstName,
					contacts[contact].lastName,
					contacts[contact].houseNumber,
					contacts[contact].streetName,
					contacts[contact].city,
					contacts[contact].state,
					contacts[contact].zip,
					contacts[contact].phoneNumber,
					contacts[contact].email
			);
			// Circumvent need for cascading ID changes during operation (delete operations).
			index += 1;
		}
	}
}