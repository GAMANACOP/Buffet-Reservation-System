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
		~Table () {}

		// Setters for table information
		void setTableNumber (int num);
		void setTableGroup(Group newGroup);

		// Getters for table information
		Group getCurrentGroup() const;
		int getTableNumber() const;

		// Function to check if the table is empty
		bool isTableEmpty() const;

		// Function to vacate the table
		void vacateTable();
};

class TablesList {
	private:
		// List of tables
		list<Table> tableList;

		// Number of current tables and occupied tables
		int numOfCurrentTables = 0;
		int numOfOccupiedTables = 0;
		
	public:

		TablesList();
		~TablesList();

		// Functions for creating tables
		void createTable();
		void createTables(const int &numberOfTables);
		
		// Getters for table information
		int  getNumOfCurrentTables() const {return numOfCurrentTables;}
		int  getNumOfOccupiedTables() const {return numOfOccupiedTables;}
		list<Table>& getList() {return tableList;}
		
		// Function for checking table availability
		bool hasAvailableTable();

		// Function for assigning group to tables
		int  assignGroupToTable(const Group group, int tableNum = 0);

		// Function for vacating tables
		void vacateTable(Table &table);

		// Function to find a representative's table
		int  findRepresentativeTable(string representativeName);
		
		// File handling relevant functions
		void saveTablesToFile();
		void loadTablesFromFile();
};

#endif
