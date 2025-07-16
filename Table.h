#include "Group.h"

#ifndef TABLE_H
#define TABLE_H

class Table {
	private:
		Group group;
		bool hasGroup;
		int tableNumber;
		
	public:
		Table () {
			hasGroup = false;
			tableNumber = 0;
		}
		Group getCurrentGroup() const {return group;}
		int getTableNumber() const {return tableNumber;}
		bool isTableEmpty() const {return !hasGroup;}
		void setTableNumber (int num);
		void setTableGroup(Group newGroup);
};

class TablesList {
	private:
		
		list<Table> tableList;
		int numOfCurrentTables = 0;
		int numOfOccupiedTables = 0;
		
	public:
		void createTable();
		void createTables(const int &numberOfTables);
		
		int getNumOfCurrentTables() const {return numOfCurrentTables;}
		list<Table>& getList() {return tableList;}
		
		bool hasAvailableTable();
		void displayAvailableTables();
		int assignGroupToTable(Group group, int tableNum = 0);
		int findRepresentativeTable(string representativeName);
		
		// File handling relevant functions
		void saveTablesToFile();
		void loadTablesFromFile();
};

#endif
