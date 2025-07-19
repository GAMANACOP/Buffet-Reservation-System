// ------ VERY IMPORTANCE NOTICE ------
// Compiler version must be C++11 or above
// In Dev C++, this can be set in Tools > Compiler Options > Settings > Code Generation
// Set Language Standard to ISO C++11

#include <iostream> // For cout, cin
#include <queue> // For GroupQueue
#include <iomanip> // For setw, setfill
#include <cstdlib> // For system("CLS") and system("pause")
#include <sstream> // For ostringstream
#include <fstream> // For file handling

#include "Group.h" // For Group class
#include "GroupQueue.h" // For GroupQueue class
#include "Table.h" // For Table class
#include "DefaultValues.h" // For default values like DEFAULT_NUMBER_OF_TABLES, DEFAULT_FEE, etc.
#include "Utils.h" // For utility functions like toLowercase and calculateTextPadding

using namespace std;

// Function to center text within a given width
// Returns a string with spaces added to the left and right to center the text
string centerText(const string& text, int width) {
    int padding = calculateTextPadding(text, width);  // Calculate left padding
    int extra = (width - text.length()) % 2;    // Extra space for odd-length texts
    if (padding > 0)
        return string(padding, ' ') + text + string(padding + extra, ' ');
    return text;
}

// Print out a divider that fills the whole width
void displayLineSeparator(const char& fill) {
	cout << setfill(fill) << setw(COLUMN_WIDTH) << fill;
	cout << setfill(' ') << endl;
}

// Function to print a formatted title with dividers.
void displayTitle(const string& title) {
	displayLineSeparator('=');
	
	int textWidth = COLUMN_WIDTH - 4;
	cout << "||" << setw(textWidth) << left << centerText(title, COLUMN_WIDTH - 4) << "||" << endl;
	displayLineSeparator('=');
}

// Function to print out options menu
void displayList(string options[], int arraySize) {
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
	
	displayLineSeparator('=');
}

// Function to print title and options (refer to printTitle and printOptions)
void displayTitleWithOptions(const string& title, string options[], int arraySize) {
	displayTitle(title);
	displayList(options, arraySize);
}

// Function to display a menu for removing a member from the group
// This function provides options to remove a child, adult, or senior member from the group reservation
void displayRemoveMemberMenu(Group &group) {
	string options[] = {
		"[1] Remove Child",
		"[2] Remove Adult",
		"[3] Remove Senior",
		"[4] Go back"
	};
	int arraySize = sizeof(options)/sizeof(options[0]);
		
	int option;
	
	while (option != 4) {
		system("CLS");
		
		displayTitle("Buffet Reservation System - Removing Member");

		// This section displays the current group information, including the representative's name and total members
		string groupInfo[] = {
			"Group Representative: " + group.getRepresentativeName(),
			"Total Members: " + to_string(group.countTotalMembers()),
			"  - Children: " + to_string(group.countMember("Child")),
			"  - Adults: " + to_string(group.countMember("Adult")),
			"  - Seniors: " + to_string(group.countMember("Senior"))
		};
		int groupInfoSize = sizeof(groupInfo) / sizeof(groupInfo[0]);
		
		displayList(groupInfo, groupInfoSize);

		// Display the options menu for removing a member
		displayList(options, arraySize);
		
		cout << endl;
		cout << "Enter an operation: ";
		cin >> option;
		
		switch (option) {
			case 1: {
				if (group.countMember("Child") <= 0) {
					cout << "Invalid operation. Group current does not have child members." << endl << endl;
					displayLineSeparator('=');
					cout << endl;
					system("pause");
				} else {
					group.removeMember("Child");
				}
				
				displayLineSeparator('=');
				break;
			};
			case 2: {
				if (group.countMember("Adult") <= 0) {
					cout << "Invalid option. Group current does not have adult members." << endl << endl;
					displayLineSeparator('=');
					cout << endl;
					system("pause");
				} else {
					group.removeMember("Adult");
				}
				displayLineSeparator('=');
				break;
			}
			case 3: {
				if (group.countMember("Senior") <= 0) {
					cout << "Invalid option. Group current does not have senior members." << endl << endl;
					displayLineSeparator('=');
					cout << endl;
					system("pause");
				} else {
					group.removeMember("Senior");
				}
				break;
			};
			
			case 4: return;
		}
	} 
}

// Function to print a row with formatted columns
// This function takes four strings and prints them in a formatted row with specified column widths
void printRow(const string& column1, const string& column2, const string& column3, const string& column4) {
	ostringstream oss;
	oss << left << 	setw(MEMBER_TYPE_COL) << column1
		<< 			setw(COUNT_COL)       << column2
		<< 			setw(DISCOUNT_COL)    << column3
		<<			setw(TOTAL_FEE_COL)   << column4;

	cout << centerText(oss.str(), COLUMN_WIDTH);
	cout << endl;
}

// Function to print a divider for computations
// This function prints a line of dashes to separate computation sections in the output
void printComputationDivider(int content_width) {
	// Computation divider row
    string divider_line(content_width, '-');

    cout << centerText(divider_line, COLUMN_WIDTH - 1);
    cout << endl;
}

// Function to print a representative row
// This function prints the representative's name in a formatted row
void printRepresentativeRow(string repName) {
	// Use ostringstream to build line, then center the whole line
    ostringstream oss;
    oss << left	<< 	setw(MEMBER_TYPE_COL) 							<< "Representative Name: "
        << left <<	setw(COUNT_COL + DISCOUNT_COL + TOTAL_FEE_COL)	<< repName;
    
    cout << centerText(oss.str(), COLUMN_WIDTH); // Center the entire string
    cout << endl;
}

void displayPaymentDetails(const Group &group) {
	// Print representative name
	printRepresentativeRow(group.getRepresentativeName());

	printRow("Default Fee:", "P" + formatFloat(DEFAULT_FEE), "", "");
	cout << endl;

	// Print computation divider row
	const int content_width = MEMBER_TYPE_COL + COUNT_COL + DISCOUNT_COL + TOTAL_FEE_COL + 2;
	printComputationDivider(content_width);

	// Print header
	printRow("Member Type", "Count", "Discount", "Total Fee");

	// Child Row
	printRow(
		"Child",
		to_string(group.countMember("Child")),
		to_string(int(DEFAULT_CHILD_DISCOUNT * 100)) + "%",
		"P" + formatFloat(group.computeMemberTotalFee("Child"))
	);

	// Adult Row
	printRow(
		"Adult",
		to_string(group.countMember("Adult")),
		to_string(int(DEFAULT_ADULT_DISCOUNT * 100)) + "%",
		"P" + formatFloat(group.computeMemberTotalFee("Adult"))
	);

	// Senior Row
	printRow(
		"Senior",
		to_string(group.countMember("Senior")),
		to_string(int(DEFAULT_SENIOR_DISCOUNT * 100)) + "%",
		"P" + formatFloat(group.computeMemberTotalFee("Senior"))
	);

	// Computation divider row
	printComputationDivider(content_width);

	// Total row
	printRow(
		"Grand Total",
		to_string(group.countTotalMembers()),
		"",
		"P" + formatFloat(group.computeTotalPayment())
	);

	cout << endl << endl; // Newline for this row
}

// Function to display a menu for computing payment
// This function displays the payment details for a group and waits for user input to continue
void displayComputePaymentMenu(Group &group) {
	start:
		
	displayTitle("Buffet Reservation System - Computing Payment");
	cout << endl;
	
	displayPaymentDetails(group);
    
    displayLineSeparator('=');
    
    system("pause");
}

// Function to display a menu for reserving a group
// This function allows the user to add members to a group, compute payment, confirm reservation,
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
		displayTitle("Buffet Reservation System - Reserving Group");
		
		// Get group's representative name, if there is none.
		if (newGroup.getRepresentativeName().length() == 0) {
			string repName;
			
			cout << endl;
			cout << "Enter the group representative's name: ";
			cin.ignore();
			getline(cin, repName);
			
			newGroup.setRepresentativeName(repName);
			cout << endl;
			displayLineSeparator('=');

		}

		start:
		system("CLS");
		displayTitle("Buffet Reservation System - Reserving Group");

		// This section displays the current group information, including the representative's name and total members
		string groupInfo[] = {
			"Group Representative: " + newGroup.getRepresentativeName(),
			"Total Members: " + to_string(newGroup.countTotalMembers()),
			"  - Children: " + to_string(newGroup.countMember("Child")),
			"  - Adults: " + to_string(newGroup.countMember("Adult")),
			"  - Seniors: " + to_string(newGroup.countMember("Senior"))
		};
		int groupInfoSize = sizeof(groupInfo) / sizeof(groupInfo[0]);
		
		displayList(groupInfo, groupInfoSize);

		// Display the options menu for reserving a group
		displayList(options, arraySize);
		
		cout << endl;
		cout << "Select an operation: ";
		cin >> option;
		
		switch (option) {
			case 1: { // Add Child
				newGroup.addChildMember();
				goto start;
				break;
			}
			case 2: { // Add Adult
				newGroup.addAdultMember();
				goto start;
				break;
			}
			case 3: { // Add Senior
				newGroup.addSeniorMember();
				goto start;
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
				displayLineSeparator('=');
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

// Function to display a menu for cancelling a reservation
// This function allows the user to cancel a reservation by entering the representative's name
void displayCancelReservationMenu(GroupQueue &groupQueue) {
	start:
	// Clear the console and display the title
	system("CLS");
	displayTitle("Buffet Reservation System - Cancel Reservation");

	// Check if the queue is empty
	// If it is empty, display a message and return to the main menu
	if (groupQueue.getQueue().empty()) {
		cout << endl;
		cout << centerText("The queue is empty! No reservations can be cancelled.", COLUMN_WIDTH) << endl << endl;
		displayLineSeparator('=');
		cout << endl;
		system("pause");
		return;
	}

	// Display all queued groups using displayList
	if (!groupQueue.getQueue().empty()) {
		queue<Group> tempQueue = groupQueue.getQueue();

		const int maxGroups = 1000;
		string queuedGroups[maxGroups];

		int idx = 0;

		while (!tempQueue.empty() && idx < maxGroups) {
			const Group &grp = tempQueue.front();
			queuedGroups[idx] = to_string(idx + 1) + ". " + grp.getRepresentativeName() +
				" (Total Members: " + to_string(grp.countTotalMembers()) + ")";
			tempQueue.pop();
			idx++;
		}
		cout << endl << centerText("Queued Groups:", COLUMN_WIDTH) << endl;
		displayList(queuedGroups, idx);
	}

	// If the queue is not empty, prompt the user to enter the representative's name
	// to cancel the reservation

	int groupPosition;
	cout << endl << "Enter the position of the group to be deleted (0 to cancel): ";
	cin >> groupPosition;

	// If user enters 0, cancel and return to main menu
	if (groupPosition == 0) {
		return;
	}

	// Check if the entered position is valid
	if (groupPosition < 0 || groupPosition > groupQueue.getQueue().size()) {
		cout << "Invalid position. Please enter a valid group position." << endl << endl;
		displayLineSeparator('=');
		cout << endl;
		system("pause");
		goto start;
	}
	
	// Attempt to cancel the reservation
	// The cancelReservation function will return true if successful, false otherwise
	bool success = groupQueue.cancelReservation(groupPosition);

	if (!success) {
		cout << "Group with entered representative name is not found." << endl;
	} else {
		cout << "Successfully cancelled reservation for group of at position " << groupPosition << "." << endl << endl;
	}
	
	displayLineSeparator('=');
	
	system("pause");
}


// Function to display available tables
// This function iterates through the list of tables and displays those that are currently available
void displayAvailableTables(TablesList &tables) {
	system("CLS");
	displayTitle("Buffet Reservation System - Available Tables");

	list<Table>::iterator iter;
	
	cout << endl << centerText("Currently Available Tables:", COLUMN_WIDTH) << endl;
	
	bool hasAvailableTable = false;

	// Collect available tables into an array of strings
	string availableTables[DEFAULT_NUMBER_OF_TABLES];
	int availableCount = 0;
	for (iter = tables.getList().begin(); iter != tables.getList().end(); ++iter) {
		if (iter->isTableEmpty()) {
			hasAvailableTable = true;
			availableTables[availableCount++] = "Table #" + to_string(iter->getTableNumber());
		}
	}

	if (!hasAvailableTable) {
		string msg[] = { "There are no available tables." };
		displayList(msg, 1);
	} else {
		displayList(availableTables, availableCount);
	}
	
	system("pause");
}


// Function to display a menu for finding a representative's table
// This function allows the user to search for tables occupied by a specific representative
// and displays the results
void displayFindRepresentativeTableMenu(TablesList &tables) {
	string repName;
	cin.ignore();

	cout << "Enter the representative's name: ";
	getline(cin, repName);

	// Count matches first
	int matchCount = 0;
	list<Table>::iterator it;

	// Iterate through the tables to find matches
	for (it = tables.getList().begin(); it != tables.getList().end(); ++it) {
		if (!it->isTableEmpty() && it->getCurrentGroup().getRepresentativeName() == repName) {
			matchCount++;
		}
	}

	system("CLS");
	displayTitle("Buffet Reservation System - Find Representative's Table");

	// If matches are found, display them
	if (matchCount > 0) {
		string foundTables[matchCount];
		int idx = 0;

		for (it = tables.getList().begin(); it != tables.getList().end(); ++it) {
			if (!it->isTableEmpty() && it->getCurrentGroup().getRepresentativeName() == repName) {
				foundTables[idx++] = "Representative \"" + repName + "\" is found in Table #" + to_string(it->getTableNumber());
			}
		}

		cout << endl << centerText("Found Tables for Representative: " + repName, COLUMN_WIDTH) << endl;
		cout << centerText("Total Matches: " + to_string(matchCount), COLUMN_WIDTH) << endl << endl;
		displayLineSeparator('=');
		displayList(foundTables, matchCount);
	} else {
		cout << endl << centerText("No tables found for representative: " + repName, COLUMN_WIDTH) << endl << endl;
		displayLineSeparator('=');
	}

	system("pause");
}

// Function to display a menu for billing out and vacating occupied tables
void displayBillOutMenu(TablesList &tables) {
	int selectedTableNumber = -1;
	bool successfullyVacateTable = false;
	bool hasOccupiedTable = false;
	list<Table>::iterator iter;

	while (!successfullyVacateTable) {
		system("CLS");
		displayTitle("Buffet Reservation System - Billing Out");

		cout << endl;
		cout << centerText("Occupied Tables:", COLUMN_WIDTH) << endl;

		// Checks if there are occupied tables.
		// If there are no occupied tables, display a message and return to the main menu
		if (tables.getNumOfOccupiedTables() <= 0) {
			cout << centerText("There are no occupied tables.", COLUMN_WIDTH) << endl << endl;
			displayLineSeparator('=');
			cout << endl;
			system("pause"); // Pause before returning to the main menu
			break;
		} else {
			// If there are occupied tables, display them

			// Collect occupied tables into an array of strings
			string occupiedTables[DEFAULT_NUMBER_OF_TABLES + 1];
			int occupiedCount = 0;

			for (iter = tables.getList().begin(); iter != tables.getList().end(); iter++) {
				if (!iter->isTableEmpty()) {
					string entry = "[" + to_string(iter->getTableNumber()) + "] Table #" +
						to_string(iter->getTableNumber()) + " : " +
						iter->getCurrentGroup().getRepresentativeName();
					occupiedTables[occupiedCount++] = entry;
				}
			}

			// Add option to exit
			occupiedTables[occupiedCount++] = "[0] Go back to main menu";

			if (occupiedCount > 0) {
				hasOccupiedTable = true;
				displayList(occupiedTables, occupiedCount);
			}

			cout << "Enter the table number to bill out and vacate (0 to go back): ";
			cin >> selectedTableNumber;

			if (selectedTableNumber == 0) {
				// Go back to main menu
				break;
			}

			// Find the table with the entered table number
			bool found = false;
			for (iter = tables.getList().begin(); iter != tables.getList().end(); ++iter) {
				if (!iter->isTableEmpty() && iter->getTableNumber() == selectedTableNumber) {
					found = true;
					break;
				}
			}

			if (!found) {
				cout << "Invalid table number. Please try again." << endl;
				system("pause");
				continue;
			}

			// Display payment details for the selected table
			Group currentGroup = iter->getCurrentGroup();

			displayLineSeparator('=');
			cout << endl;
			displayPaymentDetails(currentGroup);
			cout << endl;
			displayLineSeparator('=');
			cout << endl;

			float pay = 0;
			float amountToPay = currentGroup.computeTotalPayment();
			cout << "Enter payment: ";
			while (pay < amountToPay) {
				cin >> pay;
				if (pay < amountToPay) {
					cout << "Invalid amount. Enter a valid payment: ";
				}
			}

			system("CLS");
			displayTitle("Buffet Reservation System - Billing Out");
			
			// Instead of using ostringstream, build the strings directly
			string repNameStr = "Representative Name: " + currentGroup.getRepresentativeName();
			string amountDueStr = "Amount Due: P" + formatFloat(amountToPay);
			string payStr = "Amount received: P" + formatFloat(pay);
			string changeStr = "Change: P" + formatFloat(pay - amountToPay);

			string finalPaymentInfo[] = {
				repNameStr,
				amountDueStr,
				payStr,
				changeStr
			};

			int arraySize = sizeof(finalPaymentInfo)/sizeof(finalPaymentInfo[0]);
			displayList(finalPaymentInfo, arraySize);

			cout << endl;

			tables.vacateTable(*iter);

			tables.saveTablesToFile();
			successfullyVacateTable = true;

			system("pause");
		}
	}
}

// Function to display the main menu of the buffet reservation system
// This function clears the console, displays the title, and lists the available options
void displayMainMenu() {
	system("CLS");
	string options[] = {
		"[1] Reserve Group",
		"[2] View Queued Groups",
		"[3] Cancel Reservation",
		"[4] Check Available Tables",
		"[5] Find Representative\'s Table",
		"[6] Assign Queued to Table",
		"[7] Bill out & Vacate Occupied Table",
		"[8] Exit",
	};
	int arraySize = sizeof(options)/sizeof(options[0]);
	displayTitleWithOptions("Buffet Reservation System", options, arraySize);
}


// Function to assign the first group in the queue to an available table
void assignQueuedToTable(GroupQueue &groupQueue, TablesList &tables) {
	// Check if there are available tables first
	if (tables.getNumOfCurrentTables() == tables.getNumOfOccupiedTables()) {
		cout << "There are no available tables to assign a group." << endl;
	} else if (groupQueue.getQueue().empty()) {
		// If the queue is empty, display a message
		cout << "The queue is empty. No queued group to assign a table." << endl << endl;
	} else {
		// If there are available tables and a group in the queue, assign the first group in the queue to an available table
		
		int assignedTableNumber = tables.assignGroupToTable(groupQueue.getQueue().front());

		cout 	<< "Assigned Group of \""
				<< groupQueue.getQueue().front().getRepresentativeName() 
				<< "\" to Table #" << assignedTableNumber << endl << endl;
		groupQueue.getQueue().pop();
		groupQueue.saveQueueToFile();
	}
	system("pause");
}

void displayQueuedGroups(GroupQueue &groupQueue) {
	system("CLS");
	displayTitle("Buffet Reservation System - Queued Groups");

	if (groupQueue.getQueue().empty()) {
		cout << endl << centerText("The queue is empty.", COLUMN_WIDTH) << endl << endl;
		displayLineSeparator('=');
		cout << endl;
		system("pause");
		return;
	}

	queue<Group> tempQueue = groupQueue.getQueue();
	const int maxGroups = 1000;
	string queuedGroups[maxGroups];
	int idx = 0;

	while (!tempQueue.empty() && idx < maxGroups) {
		const Group &grp = tempQueue.front();
		queuedGroups[idx] = to_string(idx + 1) + ". " + grp.getRepresentativeName() +
			" (Total Members: " + to_string(grp.countTotalMembers()) + ")";
		tempQueue.pop();
		idx++;
	}

	displayList(queuedGroups, idx);

	cout << endl;
	system("pause");
}

// Main function to run the buffet reservation system
// This function initializes the tables and group queue, displays the main menu, and handles user input
int main() {
	TablesList tables;
	tables.createTables(DEFAULT_NUMBER_OF_TABLES);
	tables.loadTablesFromFile();
	
	GroupQueue groupQueue;
	groupQueue.loadQueueFromFile();
	
	int option;
	
	while (option != 8) {
		displayMainMenu();
		
		cout << "Select an option: ";
		cin >> option;
		
		switch (option) {
			case 1: { // Reserve group
				displayReserveGroupMenu(groupQueue);
				break;
			}
			case 2: { // View Queued Groups
				displayQueuedGroups(groupQueue);
				break;
			}
			case 3: { // Cancel Reservation
				displayCancelReservationMenu(groupQueue);
				break;
			}
			case 4: { // Check Available Tables
				displayAvailableTables(tables);
				break;
			}
			case 5: { // Find Representative Table
				displayFindRepresentativeTableMenu(tables);
				break;
			}
			case 6: { // Assign Queued to Table
				assignQueuedToTable(groupQueue, tables);
				break;
			}
			case 7: { // TODO: Bill Out & Vacate Occupied Table
				displayBillOutMenu(tables);
				break;
			}
			case 8: { // Exit
				cout << "Thank you for using this program!";
				break;
			}
			default: {
				cout << "Invalid option. Please try again." << endl;
				system("pause");
				break;
			}
		} 
	}
	
	return 0;
}
