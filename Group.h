#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <list>

using namespace std;

class Member {
	private:
		string memberType;
		float discount;
	public:
		void setMemberType(string mt) { memberType = mt; }
		void setDiscount(float d) { discount = d; }
		
		string getMemberType() const {return memberType;}
		float getDiscount() const {return discount;}
};

class Group {
	private:
		struct MemberNode {
			Member data;
			MemberNode *next;
		};
		
		MemberNode *head;
		string representativeName;

		void appendNode(Member);
		void deleteNode(string MemberType);
		
	public:
		
		int totalMembers;
		
		Group() {
			head = NULL;
			totalMembers = 0;
		}
		
		void setRepresentativeName(std::string);
		void AddChild();
		void AddAdult();
		void AddSenior();
		void RemoveMember(std::string);
		void ConfirmReservation();
		int countChild() const;
		int countSenior() const;
		int countAdult() const;
};


class Table {
	private:
		Group group;
		bool hasGroup = false;
		int tableNumber = 0;
		
	public:
		Group getCurrentGroup() const;
		int getTableNumber() const;
		bool isTableEmpty() const;
		void setTableNumber (int num);
		void setTableGroup(Group newGroup);
};



class TablesList {
	private:
		
		list<Table> tableList;
		int numOftables = 0;
		
		void saveTablesToFile();
		void loadTablesFromFile();
		
	public:
		int numOfTables = 0;
		
		void createTable() {
			Table newTable;
			newTable.setTableNumber(++numOftables);
			tableList.push_back(newTable);
		}
		
		void createTables(const int &numberOfTables) {
			for (int i = 0; i < numberOfTables; i++) {
				createTable();
			}
		}
		
		bool hasAvailableTable();
};

#endif
