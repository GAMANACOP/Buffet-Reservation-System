#ifndef TABLE_H
#define TABLE_H

#include "Group.h"

class Table {
	private:
		Group group;
		bool hasGroup = false;
		int tableNumber = 0;
		
	public:
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
		
		void incrementNumofCurrentTables() {numOfCurrentTables++;}
		void decrementNumofCurrentTables() {numOfCurrentTables--;}
		
		int getNumOfCurrentTables() const {return numOfCurrentTables;}
		
		bool hasAvailableTable();
		void assignGroupToTable(Group group);
		
		// File handling relevant functions
		void saveTablesToFile();
		void loadTablesFromFile();
};

#endif
