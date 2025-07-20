#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "Table.h"
#include "Group.h"
#include "Utils.h"
#include "DefaultValues.h"

using namespace std;


// Sets the table number for the table.
void Table::setTableNumber (int num) {
	tableNumber = num;
}

// Sets the group for the table.
void Table::setTableGroup(Group newGroup) {
	group = newGroup;
	hasGroup = true;
}

// Checks if the table is empty (i.e., has no group assigned).
bool Table::isTableEmpty() const {
	return !hasGroup;
}

// Returns the current group assigned to the table.
Group Table::getCurrentGroup() const {
	return group;
}

// Returns the table number of the table.
int Table::getTableNumber() const {
	return tableNumber;
}

// Returns the number of members in the current group assigned to the table.
void Table::vacateTable() {
	hasGroup = false;
	group = Group();
}

// Default constructor for TablesList.
TablesList::TablesList() {
	// Initialize the list of tables and counters
	numOfCurrentTables = 0;
	numOfOccupiedTables = 0;
}

// Destructor for TablesList.
TablesList::~TablesList() {
	// Clear the list of tables
	tableList.clear();
}


bool TablesList::hasAvailableTable() {
	list<Table>::iterator iter;
	
	for (iter = tableList.begin(); iter != tableList.end(); iter++) {
		if ((*iter).isTableEmpty()) {
			return true;
		}
	}
	
	return false;
}

// Creates a new table and adds it to the table list.
// This function increments the number of current tables and assigns a table number.
void TablesList::createTable() {
	Table newTable;
	numOfCurrentTables++;
	newTable.setTableNumber(numOfCurrentTables);
	tableList.push_back(newTable);
}

// Creates a specified number of tables.
// This function is used to initialize the buffet reservation system with a certain number of tables.
void TablesList::createTables(const int &numberOfTables) {
	for (int i = 0; i < numberOfTables; i++) {
		createTable();
	}
}

// Saves the current state of the tables to a file.
// The file will be overwritten each time this function is called.
// File structure:
// - table_number
// - representative_name
// - child_count
// - adult_count
// - senior_count
void TablesList::saveTablesToFile() {
	ofstream tablesFile(DEFAULT_TABLES_FILENAME, ofstream::trunc);

	list<Table>::iterator iter;
	
	for (iter = tableList.begin(); iter != tableList.end(); iter++) {
		
		int tableNum = iter->getTableNumber();
		string repName = iter->getCurrentGroup().getRepresentativeName();
		int childCount = iter->getCurrentGroup().countMember("Child");
		int adultCount = iter->getCurrentGroup().countMember("Adult");
		int seniorCount = iter->getCurrentGroup().countMember("Senior");

		tablesFile 	<< tableNum << "\n"
					<< repName << "\n"
					<< childCount << "\n"
					<< adultCount << "\n"
					<< seniorCount;
		if (iter != tableList.end()) {
			tablesFile << "\n";
		}
	}
	
	tablesFile.close();
}

// Loads the tables from a file.
// This function reads the table data from the file and populates the table list.
// The file should be in the same format as saved by saveTablesToFile().
// If the file does not exist or is empty, no tables will be loaded.
void TablesList::loadTablesFromFile() {
	ifstream tablesFile(DEFAULT_TABLES_FILENAME);
	
	if (tablesFile.is_open()) {
		int savedTableNumber = 0;
		int savedTables = 0;

		while (savedTables <= DEFAULT_NUMBER_OF_TABLES && tablesFile >> savedTableNumber) {
			savedTables++;
			tablesFile.ignore();
			
			Group savedGroup;		
			
			string savedRepName = "";
			getline(tablesFile, savedRepName);
						
			savedGroup.setRepresentativeName(savedRepName);
			
			int childCount = 0, adultCount = 0, seniorCount = 0;
			
			tablesFile >> childCount;
			tablesFile >> adultCount;
			tablesFile >> seniorCount;
			
			for (int i = 0; i < childCount; i++) {
				savedGroup.addChildMember();
			}
			for (int i = 0; i < adultCount; i++) {
				savedGroup.addAdultMember();
			}
			for (int i = 0; i < seniorCount; i++) {
				savedGroup.addSeniorMember();
			}
			
			assignGroupToTable(savedGroup, savedTableNumber);
		}
		
	}
		
	tablesFile.close();
}

// Assigns a group to a table.
// If tableNum is specified, it assigns the group to that specific table.
// If tableNum is 0, it assigns the group to the first available table.
// Returns the assigned table number, or -1 if no table was assigned.
int TablesList::assignGroupToTable(const Group group, int tableNum) {	
	bool assigned = false;
	int assignedTableNumber = -1;
	
	list<Table>::iterator iter;
	
	// If tableNum is specified, force assign the group to that specific table.
	if (tableNum > 0) {		
		int index = 1;
		for (iter = tableList.begin(); iter != tableList.end(); iter++) {
			if (index == tableNum && group.getRepresentativeName().length() > 0) {
				iter->setTableGroup(group);
				assignedTableNumber = iter->getTableNumber();
				numOfOccupiedTables++;
				break;
			} else {
				index++;
			}
		}
		
		return assignedTableNumber;
	} else {

		// If tableNum is 0, find an empty table.
		// Assigns group to the first available table.
		for (iter = tableList.begin(); iter != tableList.end(); iter++) {
			if (iter->isTableEmpty() && !assigned) {
				iter->setTableGroup(group);
				assignedTableNumber = iter->getTableNumber();
				numOfOccupiedTables++;
				break;
			}
		}
	}

	saveTablesToFile();
	
	return assignedTableNumber;
}

// Returns the table number of the representative's group.
// If not found, returns 0;
int TablesList::findRepresentativeTable(string representativeName) {
	list<Table>::iterator iter;

	for (iter = tableList.begin(); iter != tableList.end(); iter++) {
		if (!iter->isTableEmpty()) {
			if (toLowercase(iter->getCurrentGroup().getRepresentativeName()) == toLowercase(representativeName)) {
				return iter->getTableNumber();
			}
		}
	}
	
	return 0;
}

// Vacates the specified table.
// This function sets the table to empty and decrements the number of occupied tables.
void TablesList::vacateTable(Table &table) {
	table.vacateTable();
	numOfOccupiedTables--;
}

