#include <iostream>
#include <queue>
#include "Group.h"

using namespace std;

class Table {
	private:
		Group group;
		bool hasGroup = false;
		int tableNumber;
		
	public:
		Group getCurrentGroup() {
			return group;
		}
		int getTableNumber() {
			return tableNumber;
		}
		
		void setTableNumber (int num) {
			tableNumber = num;
		}
		
		void setTableGroup(Group newGroup) {
			group = newGroup;
			hasGroup = true;
		}
		
		bool isTableEmpty() {
			return hasGroup;
		}
};



class TablesList {
	private:
		struct TableNode {
			Table data;
			TableNode *next;
		};
		
		TableNode *head;
		
		void saveTablesToFile();
		void loadTablesFromFile();
		
	public:
		int numOfTables = 0;
		
		void createTable() {
			Table newTable;
			newTable.setTableNumber(++numOfTables);
			
			TableNode *newNode = new TableNode;
			newNode->data = newTable;
			newNode->next = NULL;
			
			TableNode *nodePtr;
			
			if (!head) {
				head = newNode;
			} else {
				nodePtr = head;
				
				while (nodePtr->next) {
					nodePtr = nodePtr->next;
				}
				
				nodePtr->next = newNode;
			}
		}
		
		void createTables(const int &num) {
			for (int i = 0; i < num; i++) {
				createTable();
			}
		}
		
		bool hasAvailableTable() {
			
			
			
			return false;
		}
};

int main() {
	
	queue<Group> groupQueue;
	TablesList Tables;
	Tables.createTables(10);
	
	return 0;
}
