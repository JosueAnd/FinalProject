/*
 * File Name:		main.c
 * Name:			Joshua Andujar
 * Course:			COP 2220C at Valencia College
 * Facilitator:		David Stendel
 * Description:		A contact application with CRUD functionality.
 * Team Members:	Nathen Neel, Jacob Buettner and Joshua Andujar
 * Date:			4/18/2020
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
int compareFirstAsc(const void*, const void*);
int compareFirstDsc(const void*, const void*);
int compareLastAsc(const void*, const void*);
int compareLastDsc(const void*, const void*);
void createContact(Contact[]);
void getEmail(String);
unsigned long int getInt();
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
unsigned int setID(Contact[]);
//void sortAscending(Contact contacts[]);
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

	system("pause");
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
 * Name:			compareFirstAsc()
 * Parameters:		cont1		The first contact for comparison.
 * 					cont2		The second contact for comparison.
 * Processes:		Compare two contacts by their first name and report which comes first
 * 					alphabetically.
 * Return Value:	An integer representing whether or not one string comes before another
 * 					alphabetically.
 */
int compareFirstAsc(const void* cont1, const void* cont2) {
	Contact* contact1 = (Contact*) cont1;
	Contact* contact2 = (Contact*) cont2;
	return strcmp(contact1->firstName, contact2->firstName);
}

/*
 * Name:			compareFirstDsc()
 * Parameters:		cont1		The first contact for comparison.
 * 					cont2		The second contact for comparison.
 * Processes:		Compare two contacts by their first name and report which comes last
 * 					alphabetically.
 * Return Value:	An integer representing whether or not one string comes before another
 * 					alphabetically.
 */
int compareFirstDsc(const void* cont1, const void* cont2) {
	Contact* contact1 = (Contact*) cont1;
	Contact* contact2 = (Contact*) cont2;
	return -strcmp(contact1->firstName, contact2->firstName);
}

/*
 * Name:			compareLastAsc()
 * Parameters:		cont1		The first contact for comparison.
 * 					cont2		The second contact for comparison.
 * Processes:		Compare two contacts by their last name and report which comes first
 * 					alphabetically.
 * Return Value:	An integer representing whether or not one string comes before another
 * 					alphabetically.
 */
int compareLastAsc(const void* cont1, const void* cont2) {
	Contact* contact1 = (Contact*) cont1;
	Contact* contact2 = (Contact*) cont2;
	return strcmp(contact1->lastName, contact2->lastName);
}

/*
 * Name:			compareLastDsc()
 * Parameters:		cont1		The first contact for comparison.
 * 					cont2		The second contact for comparison.
 * Processes:		Compare two contacts by their last name and report which comes last
 * 					alphabetically.
 * Return Value:	An integer representing whether or not one string comes before another
 * 					alphabetically.
 */
int compareLastDsc(const void* cont1, const void* cont2) {
	Contact* contact1 = (Contact*) cont1;
	Contact* contact2 = (Contact*) cont2;
	return -strcmp(contact1->lastName, contact2->lastName);
}

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
		// Getting user input.
		if (fgets(input, MAX_STRING_LENGTH, stdin) == NULL) {
			errorFlag = true; // If no characters read in or error occurs, set errorFlag to true
		} else {
			errorFlag = false;
		}

		// Validating input.
		for (unsigned long length = strlen(input); length; length--) {
			// Checking if each character is an alphabetic, punctuation (@ or .) or space character.
			if (!(isalpha(input[length - 1]) ||
				  isspace(input[length - 1]) ||
				  ispunct(input[length - 1]) ||
				  isdigit(input[length - 1])) ||
				  errorFlag) {
				errorFlag = true;
				printf("\n**********\n\n");
				printf("\tError: Invalid characters entered.\n");
				printf("\t\tPlease try again, but with only letters A - Z or a - z.");
				printf("\n\n**********\n");
				printf("\nNew Attempt: ");
				break;
			} else {
				// Changing newline marker to string terminator.
				if (input[length - 1] == '\n') {
					input[length - 1] = '\0';
				}
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
unsigned long int getInt() {
	// Variables
	String input = "";
	bool errorFlag = false;

	// Calculation
	do {
		// Getting user input.
		if (fgets(input, MAX_STRING_LENGTH, stdin) == NULL) {
			errorFlag = true; // If no characters read in or error occurs, set errorFlag to true
		} else {
			errorFlag = false;
		}

		// Validating input.
		for (unsigned long length = strlen(input); length; length--) {
			// Checking if each character is a digit.
			if (!(isdigit(input[length - 1]) ||
				  input[length - 1] == '\n') ||
				  errorFlag) {
				errorFlag = true;
				printf("\n**********\n\n");
				printf("\tError: Invalid characters entered.\n");
				printf("\t\tPlease try again, but with only numbers 1 - 9.");
				printf("\n\n**********\n");
				printf("\nNew Attempt: ");
				break;
			} else {
				// Changing newline marker to string terminator.
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
	bool errorFlag = false; // Used to detect input error and prompt user for input again.

	// Calculation
	do {
		// Getting user input.
		if (fgets(input, MAX_STRING_LENGTH, stdin) == NULL) {
			errorFlag = true; // If no characters read in or error occurs, set errorFlag to true
		} else {
			errorFlag = false;
		}

		// Validating input.
		for (unsigned long length = strlen(input); length; length--) {
			// Checking if each character is an alphabetic or space character.
			if (!(isalpha(input[length - 1]) ||
				  isspace(input[length - 1])) ||
				  errorFlag) {
				errorFlag = true;
				printf("\n**********\n\n");
				printf("\tError: Invalid characters entered.\n");
				printf("\t\tPlease try again, but with only letters A - Z or a - z.");
				printf("\n\n**********\n");
				printf("\nNew Attempt: ");
				break;
			} else {
				// Changing newline marker to string terminator.
				if (input[length - 1] == '\n') {
					input[length - 1] = '\0';
				}
				errorFlag = false;
			}
		} // end for loop
	} while (errorFlag);

	// Title Case the string
	if (input[0] >= 'a' && input[0] <= 'z') {
		input[0] = (char) (input[0] - 32);
	}
	for(unsigned long character = 1; character < strlen(input); character++) {
		if (input[character] >= 'A' && input[character] <= 'Z') {
			if (input[character - 1] != ' ') {
				input[character] = (char) (input[character] + 32);
			} // end inner if
		} else {
			if (input[character - 1] == ' ') {
				input[character] = (char) (input[character] - 32);
			}
		} // end outer if / else
	} // end for

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
	bool sentinel = true; // Used in while loop in main.c to decide when to terminate the program.

	// Getting user choice.
	printf("Choice: ");

	// Call the appropriate function for the chosen menu option.
	switch(getInt()) {
		case 1:
			createContact(contacts);
			break;
		case 2:
			printAllContacts(contacts, 'v');
			break;
		case 3:
			qsort(contacts, MAX_NUMBER_OF_CONTACTS, sizeof(Contact), compareFirstAsc);
			printAllContacts(contacts, 'v');
			break;
		case 4:
			qsort(contacts, MAX_NUMBER_OF_CONTACTS, sizeof(Contact), compareFirstDsc);
			printAllContacts(contacts, 'v');
			break;
		case 5:
			qsort(contacts, MAX_NUMBER_OF_CONTACTS, sizeof(Contact), compareLastAsc);
			printAllContacts(contacts, 'v');
			break;
		case 6:
			qsort(contacts, MAX_NUMBER_OF_CONTACTS, sizeof(Contact), compareLastDsc);
			printAllContacts(contacts, 'v');
			break;
		case 7:
			searchContacts(contacts);
			break;
		case 8:
			updateContact(contacts);
			break;
		case 9:
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
 * 					mode		Mode to open the file in. Only modes of fopen() accepted here.
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

/*
 * Name:			printAllContacts()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * 					mode			Mode of printing; v: View mode, display contact data, u:
 * 									Update mode, display name and ID.
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
	printf("| 3) Sort ascending (by First Name).                                       |\n");
	printf("| 4) Sort descending (by First Name).                                      |\n");
	printf("| 5) Sort ascending (by Last Name).                                        |\n");
	printf("| 6) Sort descending (by Last Name).                                       |\n");
	printf("| 7) Contact search.                                                       |\n");
	printf("| 8) Update or Delete a contact.                                           |\n");
	printf("| 9) Save and exit.                                                        |\n");
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
	printf("| 10) Delete.                                                              |\n");
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
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * 					spFile			The file where contact information is stored.
 * Processes:		Read all contacts from a file and store them into an array.
 * Return Value:	None.
 */
void readContactsFromFile(Contact contacts[], FILE** spFile) {
	// Variables
	int numOfContacts = 0;
	Contact* contact = &contacts[numOfContacts];

	// Set the file for reading.
	rewind(*spFile);

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
	// Variables
	FILE* contactsFile = NULL;

	// Open in write mode to overwrite previous contents and save only content in array.
	openContactsFile(fileName, &contactsFile, "w");
	writeToFile(contacts, &contactsFile);
	closeContactsFile(&contactsFile);
} // end function saveAndExit

/*
 * Name:			searchContacts()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		Search contacts by first and last name based on user input.
 * Return Value:	None.
 */
void searchContacts(Contact contacts[]) {
	// Variables
	Contact results[MAX_NUMBER_OF_CONTACTS] = {0};
	Contact* pContact = NULL;
	int numOfMatches = 0;
	String searchCriteria = "";

	// Get search criteria from user.
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
			// Leaving original string alone and assigning to a copy string but in all lower case.
			toLower(tempFirstName, pContact -> firstName);
			toLower(tempLastName, pContact -> lastName);
			/*
			 * Using strstr, if any portion of the searchCriteria is found in the searched string
			 * then the string will be returned, which is greater than 0, causing the if to
			 * evaluate as true. Null returned otherwise causing if to evaluate as false.
			 */
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
 * Processes:		Set the ID for a new contact based on IDs of other contacts.
 * Return Value:	An integer value to be used as a new Contact's ID.
 */
unsigned int setID(Contact contacts[]) {
	// Variables
	unsigned int greatestID = 0;
	String control = {0};

	/*
	 * Loop through and find largest index with a stored contact. By basing the condition on a
	 * required field of input for the user, we eliminate ID based discrepancies like adding a
	 * contact after a contact has been deleted. We find the largest index by comparing the
	 * firstNames in each to a control String. If they match, we know that field was blank from
	 * file as the string validation doesn't allow for blank fields. Largest index with a
	 * firstName is our last assigned ID.
	 */
	for (int contact = 0; contact < MAX_NUMBER_OF_CONTACTS; contact++) {
		if (strcmp(contacts[contact].firstName, control) != 0)
			greatestID = contact + 1 > greatestID ? contact + 1 : greatestID;
	}

	return greatestID + 1;
} // end function setID

/*
 * Name:			toLower()
 * Parameters:		copy		String variable where the lowercase version of the string will be
 * 								stored.
* 					original	Original string to be turned into all lower case.
 * Processes:		Checks each character for case, changing to lower as appropriate and filling
 * 					into the copy string so as to leave the original alone.
 * Return Value:	None.
 */
void toLower(String copy, const String original) {
	for (int character = 0; original[character] != '\0' && original[character] != '\n'; character++) {
		if (original[character] >= 'A' && original[character] <= 'Z') {
			/*
			 * Since characters are really number codes, and lower case are 32 away from their
			 * upper case equivalents, we can add 32 to an upper case character to get their
			 * lower case equivalent.
			 */
			copy[character] = (char) (original[character] + 32);
		} else {
			copy[character] = original[character];
		}
	}
} // end function toLower

/*
 * Name:			updateContact()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * Processes:		Present a list of contact names and IDs for user to choose from. Then allow
 * 					the user to choose which portion of the contact to update, accepting input as
 * 					appropriate.
 * Return Value:	None.
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

		// Switch on option number from printUpdateOptions().
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
			case 10:
				/*
				 * All contact related operations are based off of non-zero ID, so setting ID to
				 * zero is sufficient to "delete" the contact. It will be ignored in any other
				 * operation, to include writing to file.
				 */
				printf("\nContact \"%s %s\" has been deleted.\n\n", pContact -> firstName,
						pContact -> lastName);
				pContact -> id = 0;
				break;
			default:
				// Display message to user warning of invalid choice.
				printf("\n**********\n\n");
				printf("\tInvalid option chosen. Please try again entering the number to the "
					   "left of the option in the displayed menu.");
				printf("\n\n**********\n");
				errorFlag = true;
		} // end switch
	} while (errorFlag);
} // end function updateContact

/*
 * Name:			writeToFile()
 * Parameters:		contacts[]		The array where contacts are stored upon application start.
 * 					spFile			The place where the opened contacts file will stored.
 * Processes:		Write contacts to the file, resetting index numbers here to prevent the need
 * 					to refactor contacts on delete operations.
 * Return Value:	None.
 */
void writeToFile(Contact contacts[], FILE** spFile) {
	// Write each contact to file.
	for (int contact = 0, index = 1; contact < MAX_NUMBER_OF_CONTACTS; contact++) {
		// Skip any contacts with ID of 0, as they are either blank or marked for delete.
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
		} // end if
	} // end for
} // end function writeToFile