///*
// * File Name:		main.c
// * Name:			Joshua Andujar
// * Course:			COP 2220C at Valencia College
// * Facilitator:		David Stendel
// * Description:		A contact application with CRUD functionality
// * Team Members:	Jacob Buettner, Nathen Neel and Joshua Andujar
// * Date:
// */
//
//#ifndef FINALPROJECT_FILEFUNCS_H
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#include "definitions.h"
//
//// Prototypes
//void closeContactsFile(FILE**);
//void openContactsFile(String, FILE**, String);
//void readContactsFromFile(Contact[], FILE**);
//void saveAndExit(Contact[], String);
//void writeToFile(Contact[], FILE**);
//
///*
// * Name:			closeContactsFile()
// * Parameters:		spFile		The place where the contacts file to be closed is stored.
// * Processes:		Close an open contacts file.
// * Return Value:	None.
// */
//void closeContactsFile(FILE** spFile) {
//	// Calculation, closing a file
//	if (fclose(*spFile) == EOF) {
//		printf("\n**********\n\n");
//		printf("\tError occurred while closing the file.");
//		printf("\n\n**********\n");
//		exit(101);
//	} // end if
//} // end function closeContactsFile
//
///*
// * Name:			openContactsFile()
// * Parameters:		fileName	A string representing the name of the file to be opened.
// * 					spFile		The place where the opened contacts file will stored.
// * Processes:		Open or create the contacts file in append mode.
// * Return Value:	None.
// */
//void openContactsFile(String fileName, FILE** spFile, String mode) {
//	// Calculation, opening the contacts.txt file
//	if ((*spFile = fopen(fileName, mode)) == NULL) {
//		printf("\n**********\n\n");
//		printf("\tError occurred while opening the contacts.txt file.");
//		printf("\n\n**********\n");
//		exit(100);
//	} // end if
//} // end function openContactsFile
//
///*
// * Name:			readContactsFromFile()
// * Parameters:		spFile			The file where contact information is stored.
// * 					contacts[]		The array where contacts are stored upon application start.
// * Processes:		Read all contacts from a file and store them into an array.
// * Return Value:	None.
// */
//void readContactsFromFile(Contact contacts[], FILE** spFile) {
//	// Variables
//	int numOfContacts = 0;
//	Contact* contact = &contacts[numOfContacts];
//
//	rewind(*spFile);
//
//	// TODO: Look into doing this with fgets, for example see getString()
//	while (fscanf(
//			*spFile,
//			"%u %[^\n] %[^\n] %u %[^\n] %[^\n] %[^\n] %u %lu %[^\n]",
//			&contact -> id,
//			contact -> firstName,
//			contact -> lastName,
//			&contact -> houseNumber,
//			contact -> streetName,
//			contact -> city,
//			contact -> state,
//			&contact -> zip,
//			&contact -> phoneNumber,
//			contact -> email
//	) == 10) {
//		numOfContacts += 1;
//		contact = &contacts[numOfContacts];
//	}
//} // end function readContactsFromFile
//
///*
// * Name:			saveAndExit()
// * Parameters:		contacts[]		The array where contacts are stored upon application start.
// * 					fileName		A string representing the name of the file to be opened.
// * Processes:		Open the contacts file, prepare for writing, write contacts to the file and
// * 					close.
// * Return Value:	None.
// */
//void saveAndExit(Contact contacts[], String fileName) {
//	FILE* contactsFile = NULL;
//	openContactsFile(fileName, &contactsFile, "w");
//	writeToFile(contacts, &contactsFile);
//	closeContactsFile(&contactsFile);
//} // end function saveAndExit
//
///*
// * Name:			writeToFile()
// * Parameters:		contacts[]		The array where contacts are stored upon application start.
// * 					spFile			The place where the opened contacts file will stored.
// * Processes:		Write contacts to the file, resetting index numbers here to prevent the need
// * 					to refactor contacts on delete operations.
// * Return Value:	None.
// */
//void writeToFile(Contact contacts[], FILE** spFile) {
//	for (int contact = 0, index = 1; contact < MAX_NUMBER_OF_CONTACTS; contact++) {
//		if (contacts[contact].id != 0) {
//			fprintf(
//					*spFile,
//					"%u\n%s\n%s\n%u\n%s\n%s\n%s\n%u\n%lu\n%s\n",
//					index,
//					contacts[contact].firstName,
//					contacts[contact].lastName,
//					contacts[contact].houseNumber,
//					contacts[contact].streetName,
//					contacts[contact].city,
//					contacts[contact].state,
//					contacts[contact].zip,
//					contacts[contact].phoneNumber,
//					contacts[contact].email
//			);
//			// Circumvent need for cascading ID changes during operation (delete operations).
//			index += 1;
//		}
//	}
//}
//
//#define FINALPROJECT_FILEFUNCS_H
//#endif //FINALPROJECT_FILEFUNCS_H
