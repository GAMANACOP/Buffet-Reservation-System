#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "Table.h"
#include "Group.h"

string DEFAULT_TABLES_FILENAME = "BRSTables.txt";

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
	incrementNumofCurrentTables();
	newTable.setTableNumber(getNumOfCurrentTables());
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



void TablesList::assignGroupToTable(Group group) {
	list<Table>::iterator iter;
	
	bool assigned = false;
	
	for (iter = tableList.begin(); iter != tableList.end(); iter++) {
		if (iter->isTableEmpty()) {
			if (!assigned) {
				iter->setTableGroup(group);
				assigned = true;
			}
		}
	}
	
	saveTablesToFile();
}




