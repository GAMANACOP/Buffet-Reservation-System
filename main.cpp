#include <iostream>
#include <queue>
#include <iomanip>
#include <cstdlib>

#include "Group.h"

#define COLUMN_WIDTH 100

using namespace std;

int calculateTextPadding(const string& text, int width) {
	return (width - text.length()) / 2;
}

string centerText(const string& text, int width) {
    int padding = calculateTextPadding(text, width);  // Calculate left padding
    int extra = (width - text.length()) % 2;    // Extra space for odd-length texts
    if (padding > 0)
        return string(padding, ' ') + text + string(padding + extra, ' ');
    return text;
}

// Print out a divider that fills the whole width
void printDivider(const char& fill) {
	cout << setfill(fill) << setw(COLUMN_WIDTH) << fill;
	cout << setfill(' ') << endl;
}

// Function to print a formatted title with dividers.
void printTitle(const string& title) {
	printDivider('=');
	
	int textWidth = COLUMN_WIDTH - 4;
	cout << "||" << setw(textWidth) << left << centerText(title, COLUMN_WIDTH - 4) << "||" << endl;
	printDivider('=');
}

// Function to print out options menu
void printOptions(string options[], int arraySize) {
	int leastLinePadding = 0;
	
	for (int i = 0; i < arraySize; i++) {
		int linePadding = calculateTextPadding(options[i], COLUMN_WIDTH);
		if (leastLinePadding == 0) {
			leastLinePadding = linePadding;
		} else {
			if (linePadding < leastLinePadding) leastLinePadding = linePadding;
		}
		
	}
	
	for (int i = 0; i < arraySize; i++) {
		cout << string(leastLinePadding, ' ') + options[i] << "\n";
	}
}

// Function to print title and options (refer to printTitle and printOptions)
void printTitleAndOptions(const string& title, string options[], int arraySize) {
	printTitle(title);
	cout << endl;
	printOptions(options, arraySize);
	cout << endl;
}

void displayMainMenu() {
	string options[] = {
		"[1] Reserve Group",
		"[2] Cancel Reservation",
		"[3] Check Available Tables",
		"[4] Find Table",
		"[5] Assign Queued to Table",
		"[6] Bill out & Vacate Occupied Table",
		"[7] Exit",
	};
	int arraySize = sizeof(options)/sizeof(options[0]);
	printTitleAndOptions("Buffet Reservation System v1.0", options, arraySize);
	printDivider('=');
}

void displayReserveGroupMenu() {
	string options[] = {
		"[1] Add Child",
		"[2] Add Adult",
		"[3] Add Senior",
		"[4] Remove Member",
		"[5] Compute Payment",
		"[6] Confirm Reservation",
		"[7] Cancel Reservation",
	};
	int arraySize = sizeof(options)/sizeof(options[0]);
	printTitleAndOptions("Reserving Group", options, arraySize);
	printDivider('=');
	
	int option;
	
	cout << "Select an operation: ";
	cin >> option;
	
	switch (option) {
		
	}
}

int main() {
	
	
	int option;
	
	while (option != 7) {
		displayMainMenu();
		
		cout << "Select an option: ";
		cin >> option;
		
		switch (option) {
			case 1: {
				system("CLS");
				displayReserveGroupMenu();
				system("pause");
				break;
			}
		}
	} 
	
	return 0;
}
