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
#include <string.h>

// Contact Manipulation Functions
#include "contact.h"
// Macros and User-Defined Types
#include "definitions.h"
// FILE Functions
#include "fileLogic.h"
// User Input Functions
#include "getters.h"
// UI Functions
#include "ui.h"

// Prototypes

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