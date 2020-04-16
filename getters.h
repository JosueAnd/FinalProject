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
void getInt(unsigned int);
void getString(String string);

/*
 * Name:			getString()
 * Parameters:		string		The String where user input will be stored.
 * Processes:		Accepts input from the user and validates. If validation fails the function
 * 					will loop, prompting for input until validation passes.
 * Return Value:	None.
 */
void getInt(unsigned int integer) {
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
			if (!(isdigit(input[length - 1])) ||
				errorFlag) {
				errorFlag = true;
				printf("\n**********\n\n");
				printf("\tError: Invalid characters entered.");
				printf("\t\tPlease try again, but with only numbers  - 9.");
				printf("\n\n**********\n");
				break;
			} else {
				errorFlag = false;
			}
		} // end for loop
	} while (errorFlag);

	// Assigning user input to passed in field.
	strcpy(integer, input);
} // end function getString

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
				errorFlag = false;
			}
		} // end for loop
	} while (errorFlag);

	// Assigning user input to passed in field.
	strcpy(string, input);
} // end function getString

#define FINALPROJECT_GETTERS_H
#endif //FINALPROJECT_GETTERS_H
