#include <iostream>
#include <queue>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "Group.h"
#include "GroupQueue.h"
#include "Table.h"
#include "DefaultValues.h"

#define COLUMN_WIDTH 100

// Variables for number of columns
const int MEMBER_TYPE_COL = 22; // Width for "Member Type" column
const int COUNT_COL       = 10; // Width for "Count" column
const int DISCOUNT_COL    = 15; // Width for "Total Fee" column
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
	
	printDivider('=');
	
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
	
	printTitleAndOptions("Buffet Reservation System - Removing Member", options, arraySize);
	
	int option;
	
	while (option != 4) {
		cout << "Enter an operation: ";
		cin >> option;
		
		switch (option) {
			case 1: {
				if (group.countMember("Child") <= 0) {
					cout << "Invalid operation. Group current does not have child members." << endl << endl;
				} else {
					group.RemoveMember("Child");
					cout << "Successfully removed a child member from group reservation." << endl << endl;
				}
				
				printDivider('=');
				break;
			};
			case 2: {
				if (group.countMember("Adult") <= 0) {
					cout << "Invalid option. Group current does not have adult members." << endl << endl;
				} else {
					group.RemoveMember("Adult");
					cout << "Successfully removed an adult member from group reservation." << endl << endl;
				}
				printDivider('=');
				break;
			}
			case 3: {
				if (group.countMember("Senior") <= 0) {
					cout << "Invalid option. Group current does not have senior members." << endl << endl;
				} else {
					group.RemoveMember("Senior");
					cout << "Successfully removed a senior member from group reservation." << endl << endl;
				}
				printDivider('=');
				break;
			};
			
			case 4: return;
		}
	} 
}

template <typename T1, typename T2, typename T3, typename T4>
void printRow(T1 column1, T2 column2, T3 column3, T4 column4) {
	
	// Use ostringstream to build line, then center the whole line
    ostringstream oss;
    oss << left << setw(MEMBER_TYPE_COL) << column1
               << left << setw(COUNT_COL)       << column2
               << left << setw(DISCOUNT_COL)   << column3
               << left << setw(TOTAL_FEE_COL)   << column4;
    
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
    oss << left	<< 	setw(MEMBER_TYPE_COL) 							<< "Representative Name: "
        << left <<	setw(COUNT_COL + DISCOUNT_COL + TOTAL_FEE_COL)	<< repName;
    
    cout << centerText(oss.str(), COLUMN_WIDTH); // Center the entire string
    cout << endl;
}

void displayPaymentDetails(Group &group) {
	
    // Print representative name
	printRepresentativeRow(group.getRepresentativeName());
	ostringstream defaultFee;
    defaultFee << "P" << DEFAULT_FEE;
    printRow("Default Fee:", defaultFee.str(), "", "");
    cout << endl;
	
	// Print computation divider row
	const int content_width = MEMBER_TYPE_COL + COUNT_COL + DISCOUNT_COL + TOTAL_FEE_COL + 2;
    printComputationDivider(content_width);    
	
	// Print header
	printRow("Member Type", "Count", "Discount", "Total Fee");

    // --- Print Data Rows ---
    // For each data row, build the line using ostringstream and then center it.

    // Child Row
    ostringstream childDiscountColumn, childTotalFeeColumn;
    
	childDiscountColumn << DEFAULT_CHILD_DISCOUNT * 100 << "%";
	childTotalFeeColumn << "P" << group.computeMemberTotalFee("Child");
	
    printRow("Child", group.countMember("Child"), childDiscountColumn.str(), childTotalFeeColumn.str());

    // Adult Row
    ostringstream adultDiscountColumn, adultTotalFeeColumn;
    
	adultDiscountColumn << DEFAULT_ADULT_DISCOUNT * 100 << "%";
	adultTotalFeeColumn << "P" << group.computeMemberTotalFee("Adult");
	
    printRow("Adult", group.countMember("Adult"), adultDiscountColumn.str(), adultTotalFeeColumn.str());

    // Senior Row
    ostringstream seniorDiscountColumn, seniorTotalFeeColumn;
    
	seniorDiscountColumn << DEFAULT_SENIOR_DISCOUNT * 100 << "%";
	seniorTotalFeeColumn << "P" << group.computeMemberTotalFee("Senior");
	
    printRow("Senior", group.countMember("Senior"), seniorDiscountColumn.str(), seniorTotalFeeColumn.str());
    
    // Computation divider row
    printComputationDivider(content_width);

	// Total row
    ostringstream total_row_oss;
    total_row_oss << left << setw(MEMBER_TYPE_COL) << "Grand Total"
                  << left << setw(COUNT_COL)       << group.getTotalMembers()
                  << left << setw(DISCOUNT_COL)    << ""
                  << left << setw(TOTAL_FEE_COL)   << group.computeTotalPayment();
    cout << centerText(total_row_oss.str(), COLUMN_WIDTH);
    cout << endl << endl; // Newline for this row
}

void displayComputePaymentMenu(Group &group) {
	start:
		
	printTitle("Buffet Reservation System - Computing Payment");
	cout << endl;
	
	displayPaymentDetails(group);
    
    printDivider('=');
    
    system("pause");
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
	
	
	int option;
				
	while (option != 6 && option != 7) {
		system("CLS");
		printTitle("Buffet Reservation System - Reserving Group");
		
		// Get group's representative name, if there is none.
		while (newGroup.getRepresentativeName().length() == 0) {
			string repName;
			
			cout << endl;
			cout << "Enter the group representative's name: ";
			cin.ignore();
			getline(cin, repName);
			
			newGroup.setRepresentativeName(repName);
			cout << endl;
			printDivider('=');
		}
				
		printOptions(options, arraySize);
		
		selectOption:
		cout << "Select an operation: ";
		cin >> option;
		
		switch (option) {
			case 1: { // Add child
				newGroup.AddChild();
				cout << "Successfully added child to group!" << endl;
				cout << endl;
				printDivider('=');
				cout << endl;
				goto selectOption;
				break;
			}
			case 2: { // Add Adult
				newGroup.AddAdult();
				cout << "Successfully added adult to group!" << endl;
				cout << endl;
				printDivider('=');
				cout << endl;
				goto selectOption;
				break;
			}
			case 3: { // Add Senior
				newGroup.AddSenior();
				cout << "Successfully added senior to group!" << endl;
				cout << endl;
				printDivider('=');
				cout << endl;
				goto selectOption;
				break;
			}
			case 4: { // Remove member
				system("CLS");
				displayRemoveMemberMenu(newGroup);
				system("CLS");
				break;
			}
			case 5: { // Compute Payment
				system("CLS");
				displayComputePaymentMenu(newGroup);
				break;
			}
			case 6: { // Confirm Reservation
				groupQueue.appendToQueue(newGroup);
				groupQueue.saveQueueToFile();
				cout << "Successfully added group to queue!" << endl << endl;
				printDivider('=');
				system("pause");
				break;
			}
			case 7: { // Cancel Reservation
				cout << "The reservation has been cancelled." << endl;
				system("pause");
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
		"[4] Find Representative\'s Table",
		"[5] Assign Queued to Table",
		"[6] Bill out & Vacate Occupied Table",
		"[7] Exit",
	};
	int arraySize = sizeof(options)/sizeof(options[0]);
	printTitleAndOptions("Buffet Reservation System", options, arraySize);
}

void displayCancelReservationMenu(GroupQueue &groupQueue) {
	if (groupQueue.getQueue().empty()) {
		cout << "The queue is empty! No reservations can be cancelled." << endl;
		printDivider('=');
		system("pause");
		return;
	}
	
	string representativeName;
	
	cout << "Enter the representative name of the group to be deleted: ";
	cin.ignore();
	getline(cin, representativeName);
	
	bool success = groupQueue.cancelReservation(representativeName);
	
	if (!success) {
		cout << "Group with entered representative name is not found." << endl;
	}
	
	printDivider('=');
	
	system("pause");
}

void displayAvailableTables(TablesList &tables) {
	list<Table>::iterator iter;
	
	printDivider('=');
	
	cout << centerText("Currently Available Tables:", COLUMN_WIDTH) << endl;
	
	bool hasAvailableTable = false;

	for (iter = tables.getList().begin(); iter != tables.getList().end(); iter++) {
		if (iter->isTableEmpty()) {
			hasAvailableTable = true;
		    ostringstream oss;
		    oss << left << "Table #" << iter->getTableNumber();
		    
		    cout << centerText(oss.str(), COLUMN_WIDTH) << endl;
		}
	}
	
	if (!hasAvailableTable) {
		cout << centerText("There are no available tables.", COLUMN_WIDTH) << endl;
	}
	
	printDivider('=');
	system("pause");
}

void displayFindRepresentativeTableMenu(TablesList &tables) {
	string repName;
	cin.ignore();
	
	cout << "Enter the representative's name: ";
	getline(cin, repName);
	
	int tableNumber = tables.findRepresentativeTable(repName);
	
	if (tableNumber > 0) {
		cout << "Representative \"" << repName << "\" is found in Table #" << tableNumber << endl;
	} else {
		cout << "Table of \"" << repName << "\" is not found." << endl;
	}
	
	printDivider('=');
	
	system("pause");
}

int main() {
	TablesList tables;
	tables.createTables(DEFAULT_NUMBER_OF_TABLES);
	tables.loadTablesFromFile();
	
	GroupQueue groupQueue;
	groupQueue.loadQueueFromFile();
	
	int option;
	
	while (option != 7) {
		displayMainMenu();
		
		cout << "Select an option: ";
		cin >> option;
		
		switch (option) {
			case 1: { // Reserve group
				displayReserveGroupMenu(groupQueue);
				break;
			}
			case 2: { // Cancel Reservation
				displayCancelReservationMenu(groupQueue);
				break;
			}
			case 3: { // Check Available Tables
				displayAvailableTables(tables);
				break;
			}
			case 4: { // Find Representative Table
				displayFindRepresentativeTableMenu(tables);
				break;
			}
			case 5: { // Check Available Tables
				if (groupQueue.getQueue().empty()) {
					cout << "The queue is empty! No queued to assign to table." << endl;
				} else {
					int assignedTableNumber = tables.assignGroupToTable(groupQueue.getQueue().front());
					
					cout 	<< "Assigned Group of \""
							<< groupQueue.getQueue().front().getRepresentativeName() 
							<< "\" to Table #" << assignedTableNumber << endl;
					groupQueue.getQueue().pop();
					groupQueue.saveQueueToFile();
					
				}
				system("pause");
				break;
			}
			case 6: { // TODO: Bill Out & Vacate Occupied Table
				
				break;
			}
			case 7: { // Exit
				cout << "Thank you for using this program!";
				break;
			}
		}
	} 
	
	return 0;
}
