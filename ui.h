////
//// Created by josue on 4/16/20.
////
//
//#ifndef FINALPROJECT_UI_H
//
//#include <stdio.h>
//
//#include "contact.h"
//#include "definitions.h"
//
//// Prototypes
//bool getUserChoice(Contact contacts[]);
//void printMenu();
//void printWelcome();
//
///*
// * Name:			getUserChoice()
// * Parameters:		contacts[]		The array where contacts are stored upon application start.
// * Processes:		Get an integer choice matching a menu option and call appropriate functions
// * 					to carry out that process.
// * Return Value:	An integer representing the users choice to continue interacting with the
// * 					program (non-zero value) or terminate its use (zero).
// */
//bool getUserChoice(Contact contacts[]) {
//	// Variables
//	unsigned int choice = 0;
//	bool sentinel = true;
//
//	printf("Choice: ");
//	choice = getInt();
//
//	// Call the appropriate function for the chosen menu option.
//	switch(choice) {
//		case 1:
//			createContact(contacts);
//			break;
//		case 2:
//			printAllContacts(contacts, 'v');
//			break;
//		case 3:
//			searchContacts(contacts);
//			break;
//		case 4:
//			updateContact(contacts);
//			break;
//		// FIXME: Incomplete switch logic.
////		case 5:
////			printf("");
////			break;
//		case 6:
//			printf("\n\nYou have chosen to exit. Good bye! :)\n\n");
//			sentinel = false;
//			saveAndExit(contacts, "contacts.txt");
//			break;
//		default:
//			// Display message to use warning of invalid choice.
//			printf("\n**********\n\n");
//			printf("\tInvalid option chosen. Please try again entering the number to the "
//				   "left of the option in the displayed menu.");
//			printf("\n\n**********\n");
//			// Reprint the menu.
//			printMenu();
//			// Catch the return value of the recurred function for continuance or exit condition.
//			sentinel = getUserChoice(contacts);
//			break;
//	} // end switch
//	return sentinel;
//} // end function getUserChoice
//
///*
// * Name:			printMenu()
// * Parameters:		None.
// * Processes:		Print a menu of application options to the user.
// * Return Value:	None.
// */
//void printMenu() {
//	printf("____________________________________________________________________________\n");
//	printf("|                                                                          |\n");
//	printf("|                              Menu Options:                               |\n");
//	printf("|                              _____________                               |\n");
//	printf("|                                                                          |\n");
//	printf("| 1) Create a new contact.                                                 |\n");
//	printf("| 2) Print all contacts.                                                   |\n");
//	printf("| 3) Contact search.                                                       |\n");
//	printf("| 4) Update a contact.                                                     |\n");
//	printf("| 5) Delete a contact.                                                     |\n");
//	printf("| 6) Save and exit.                                                        |\n");
//	printf("|                                                                          |\n");
//	printf("____________________________________________________________________________\n");
//} // end function printMenu
//
///*
// * Name:			printWelcome()
// * Parameters:		None.
// * Processes:		Print a welcome message to the user.
// * Return Value:	None.
// */
//void printWelcome() {
//	printf("____________________________________________________________________________\n");
//	printf("|                                                                          |\n");
//	printf("|                        Welcome to the Contact Book                       |\n");
//	printf("|                                                                          |\n");
//} // end function printWelcome
//
//#define FINALPROJECT_UI_H
//#endif //FINALPROJECT_UI_H
