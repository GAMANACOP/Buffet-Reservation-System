#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "Table.h"
#include "Group.h"
#include "Utils.h"
#include "DefaultValues.h"

using namespace std;

void Table::setTableNumber (int num) {
	tableNumber = num;
}
		
void Table::setTableGroup(Group newGroup) {
	group = newGroup;
	hasGroup = true;
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

void TablesList::createTable() {
	Table newTable;
	numOfCurrentTables++;
	newTable.setTableNumber(numOfCurrentTables);
	tableList.push_back(newTable);
}

void TablesList::createTables(const int &numberOfTables) {
	for (int i = 0; i < numberOfTables; i++) {
		createTable();
	}
}

void TablesList::saveTablesToFile() {
	ofstream tablesFile(DEFAULT_TABLES_FILENAME, ofstream::trunc);
	
	// File structure:
	// table_number
	// representative_name
	// child_count
	// adult_count
	// senior_count
	
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

void TablesList::loadTablesFromFile() {
	ifstream tablesFile(DEFAULT_TABLES_FILENAME);
	
	if (tablesFile.is_open()) {
		Group savedGroup;		
		int savedTableNumber = 0;
				
		while (tablesFile >> savedTableNumber) {
			tablesFile.ignore();
			
			string savedRepName = "";
			getline(tablesFile, savedRepName);
			
			savedGroup.setRepresentativeName(savedRepName);
			
			int childCount = 0, adultCount = 0, seniorCount = 0;
			tablesFile >> childCount;
			tablesFile >> adultCount;
			tablesFile >> seniorCount;
			
			for (int i = 0; i < childCount; i++) {
				savedGroup.AddChild();
			}
			for (int i = 0; i < adultCount; i++) {
				savedGroup.AddAdult();
			}
			for (int i = 0; i < seniorCount; i++) {
				savedGroup.AddSenior();
			}
			
			assignGroupToTable(savedGroup, savedTableNumber);
		}
		
	}
	
	tablesFile.close();
}

int TablesList::assignGroupToTable(Group group, int tableNum) {	
	bool assigned = false;
	int assignedTableNumber = -1;
	
	list<Table>::iterator iter;
	
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

