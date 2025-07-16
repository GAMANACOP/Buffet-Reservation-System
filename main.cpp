#include <iostream>
#include <queue>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "Group.h"
#include "GroupQueue.h"
#include "Table.h"

#define COLUMN_WIDTH 100


// Variables for number of columns
const int MEMBER_TYPE_COL = 20; // Width for "Member Type" column
const int COUNT_COL       = 20; // Width for "Count" column
const int TOTAL_FEE_COL   = 15; // Width for "Total Fee" column

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
	
	cout << endl;
	
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
	
	cout << endl;
}

// Function to print title and options (refer to printTitle and printOptions)
void printTitleAndOptions(const string& title, string options[], int arraySize) {
	printTitle(title);
	printOptions(options, arraySize);
}

void displayRemoveMemberMenu(Group &group) {
	string options[] = {
		"[1] Remove Child",
		"[2] Remove Adult",
		"[3] Remove Senior",
		"[4] Go back"
	};
	int arraySize = sizeof(options)/sizeof(options[0]);
	
	printTitle("Buffet Reservation System - Removing Member");
	
	int option;
	switch (option) {
		case 1: group.RemoveMember("Child");
		case 2: group.RemoveMember("Adult");
		case 3: group.RemoveMember("Senior");
		
		case 4: return;
	}
}

template <typename T1, typename T2, typename T3>
void printRow(T1 column1, T2 column2, T3 column3) {
	// Use ostringstream to build line, then center the whole line
    ostringstream oss;
    oss << left << setw(MEMBER_TYPE_COL) << column1
               << left << setw(COUNT_COL)       << column2
               << left << setw(TOTAL_FEE_COL)   << column3;
    
    cout << centerText(oss.str(), COLUMN_WIDTH); // Center the entire string
    cout << endl;
}

void printComputationDivider(int content_width) {
	// Computation divider row
    string divider_line(content_width, '-');

    cout << centerText(divider_line, COLUMN_WIDTH - 1);
    cout << endl;
}

void printRepresentativeRow(string repName) {
	// Use ostringstream to build line, then center the whole line
    ostringstream oss;
    oss << left << setw(MEMBER_TYPE_COL) 					<< "Representative: "
               << left << setw(COUNT_COL + TOTAL_FEE_COL) 	<< repName;
    
    cout << centerText(oss.str(), COLUMN_WIDTH); // Center the entire string
    cout << endl;
}

void displayComputePaymentMenu(Group &group) {
	start:
		
	printTitle("Buffet Reservation System - Computing Payment");
	cout << endl;
	
	
    // Print representative name
	printRepresentativeRow(group.getRepresentativeName());
	
	// Print computation divider row
	const int content_width = MEMBER_TYPE_COL + COUNT_COL + TOTAL_FEE_COL;
    printComputationDivider(content_width);
	
	// Print header
	printRow("Member Type", "Count", "Total Fee");

    // --- Print Data Rows ---
    // For each data row, build the line using ostringstream and then center it.

    // Child Row
    printRow("Child", group.countMember("Child"), group.computeMemberTotalFee("Child"));

    // Adult Row
    printRow("Adult", group.countMember("Adult"), group.computeMemberTotalFee("Adult"));

    // Senior Row
    printRow("Senior", group.countMember("Senior"), group.computeMemberTotalFee("Senior"));
    
    // Computation divider row
    printComputationDivider(content_width);

	// Total row
    ostringstream total_row_oss;
    total_row_oss << left << setw(MEMBER_TYPE_COL) << ""
                  << left << setw(COUNT_COL)       << group.getTotalMembers()
                  << left << setw(TOTAL_FEE_COL)   << group.computeTotalPayment();
    cout << centerText(total_row_oss.str(), COLUMN_WIDTH);
    cout << endl << endl; // Newline for this row
    
    printDivider('=');
}

void displayReserveGroupMenu(GroupQueue &groupQueue) {
	Group newGroup;
	
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
	
	start:
		
	printTitle("Reserving Group");
	
	// Get group's representative name, if there is none.
	while (newGroup.getRepresentativeName().length() == 0) {
		string repName;
		
		cout << endl;
		cout << "Enter the group representative's name: ";
		cin.ignore();
		getline(cin, repName);
		
		newGroup.setRepresentativeName(repName);
		cout << endl;
	}
	
	printDivider('=');
	printOptions(options, arraySize);
	printDivider('=');
	
	int option;
	
	menuStart:
			
	while (option != 4 && option != 6) {
		cout << "Select an operation: ";
		cin >> option;
		
		switch (option) {
			case 1: { // Add child
				newGroup.AddChild();
				
				cout << "Successfully added child to group!" << endl;
				goto menuStart;
				break;
			}
			case 2: { // Add Adult
				newGroup.AddAdult();
				cout << "Successfully added adult to group!" << endl;
				goto menuStart;
				break;
			}
			case 3: { // Add Senior
				newGroup.AddSenior();
				cout << "Successfully added senior to group!" << endl;
				goto menuStart;
				break;
			}
			case 4: { // Remove member
				displayRemoveMemberMenu(newGroup);
				goto menuStart;
				break;
			}
			case 5: {
				system("CLS");
				displayComputePaymentMenu(newGroup);
				goto menuStart;
				break;
			}
			case 6: {
				groupQueue.appendToQueue(newGroup);
				groupQueue.saveQueueToFile();
				cout << "Successfully added group to queue!" << endl;
				system("pause");
				break;
			}
			case 7: {
				system("CLS");
				break;
			}
		}
	}
}

void displayMainMenu() {
	system("CLS");
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
	printTitleAndOptions("Buffet Reservation System", options, arraySize);
	printDivider('=');
}

int main() {
	TablesList tables;
	tables.createTables(10);
	
	GroupQueue groupQueue;
	groupQueue.loadQueueFromFile();
	
	int option;
	
	while (option != 7) {
		displayMainMenu();
		
		cout << "Select an option: ";
		cin >> option;
		
		switch (option) {
			case 1: { // Reserve group
				system("CLS");
				displayReserveGroupMenu(groupQueue);
				break;
			}
			case 2: { // TODO: Cancel Reservation
				break;
			}
			case 3: { // TODO: Check Available Tables
				break;
			}
			case 4: { // TODO: Find Representative Table
				break;
			}
			case 5: { // Check Available Tables
				if (groupQueue.getQueue().empty()) {
					cout << "The queue is empty! No queued to assign to table." << endl;
				} else {
					tables.assignGroupToTable(groupQueue.getQueue().front());
					groupQueue.getQueue().pop();
					groupQueue.saveQueueToFile();
				}
				system("pause");
				break;
			}
			case 6: { // TODO: Bill Out & Vacate Occupied Table
				
				break;
			}
		}
	} 
	
	return 0;
}
