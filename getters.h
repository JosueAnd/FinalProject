//
// Created by josue on 4/16/20.
//

#ifndef FINALPROJECT_GETTERS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

// Prototypes
void getEmail(String string);
unsigned int getInt();
void getString(String string);
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

#define FINALPROJECT_GETTERS_H
#endif //FINALPROJECT_GETTERS_H