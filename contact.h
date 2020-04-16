//
// Created by josue on 4/16/20.
//

#ifndef FINALPROJECT_CONTACT_H

#include <stdbool.h>
#include <stdio.h>

#include "definitions.h"
#include "getters.h"

// Prototypes
void createContact(Contact contacts[]);
void printAllContacts(Contact contacts[]);
int setID(Contact contacts[]);

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
	getInt(contact.houseNumber);

	printf("Please enter the street name the contact lives at: ");
	getString(contact.streetName);

	printf("Please enter the city the contact lives in: ");
	getString(contact.city);

	printf("Please enter the state the contact lives in: ");
	getString(contact.state);

	printf("Please enter the contact's zip code: ");
	getInt(contact.zip);

	printf("Please enter the contact's phone number: ");
	getInt(contact.phoneNumber);

	printf("Please enter the contact's email: ");
	getString(contact.email);

	// Adding contact to contacts array, index is always ID - 1.
	contacts[contact.id - 1] = contact;
} // end function createContact

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

#define FINALPROJECT_CONTACT_H
#endif //FINALPROJECT_CONTACT_H
