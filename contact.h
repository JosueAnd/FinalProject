//
// Created by josue on 4/16/20.
//

#ifndef FINALPROJECT_CONTACT_H

#include <stdbool.h>
#include <stdio.h>

#include "definitions.h"
#include "getters.h"

// Prototypes
void createContact(Contact[]);
void printAllContacts(Contact[], char);
void searchContacts(Contact[]);
int setID(Contact[]);
void updateContact(Contact[]);

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
				getString(pContact->firstName);
				break;
			case 2:
				printf("Please enter the last name of the contact: ");
				getString(pContact->lastName);
				break;
			case 3:
				printf("Please enter the house number of the contact: ");
				pContact->houseNumber = getInt();
				break;
			case 4:
				printf("Please enter the street name the contact lives at: ");
				getString(pContact->streetName);
				break;
			case 5:
				printf("Please enter the city the contact lives in: ");
				getString(pContact->city);
				break;
			case 6:
				printf("Please enter the state the contact lives in: ");
				getString(pContact->state);
				break;
			case 7:
				printf("Please enter the contact's zip code: ");
				pContact->zip = getInt();
				break;
			case 8:
				printf("Please enter the contact's phone number: ");
				pContact->phoneNumber = getInt();
				break;
			case 9:
				printf("Please enter the contact's email: ");
				getEmail(pContact->email);
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

#define FINALPROJECT_CONTACT_H
#endif //FINALPROJECT_CONTACT_H
