/*
 * File Name:		main.c
 * Name:			Joshua Andujar
 * Course:			COP 2220C at Valencia College
 * Facilitator:		David Stendel
 * Description:		A contact application with CRUD functionality
 * Team Members:	Jacob Buettner, Nathen Neel and Joshua Andujar
 * Date:
 */

#ifndef FINALPROJECT_FILELOGIC_H

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"

// Prototypes
void closeContactsFile(FILE** spFile);
void openContactsFile(String fileName, FILE** spFile);
void readContactsFromFile(FILE** spFile, Contact contacts[]);

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
 * Name:			openContactsFile()
 * Parameters:		fileName	A string representing the name of the file to be opened.
 * 					spFile		The place where the opened contacts file will stored.
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

	// FIXME: Look into doing this with fgets, for example see getString()
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

#define FINALPROJECT_FILELOGIC_H
#endif //FINALPROJECT_FILELOGIC_H
