#include "Group.h"
#include <iostream>
#include <string>
#include <list>
#include <deque>

float DEFAULT_CHILD_DISCOUNT = 0.05;
float DEFAULT_ADULT_DISCOUNT = 0.0;
float DEFAULT_SENIOR_DISCOUNT = 0.2;

using namespace std;


Group Table::getCurrentGroup() const {
	return group;
}

int Table::getTableNumber() const {
	return tableNumber;
}

void Table::setTableNumber (int num) {
	tableNumber = num;
}
		
void Table::setTableGroup(Group newGroup) {
	group = newGroup;
	hasGroup = true;
}
		
bool Table::isTableEmpty() const {
	return !hasGroup;
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

void Group::appendNode(Member newMember) {
	MemberNode *newNode = new MemberNode;
	newNode->data = newMember;
	newNode->next = NULL;
	
	if (!head) {
		head = newNode;
	} else {
		MemberNode *nodePtr = head;
		
		while (nodePtr->next) {
			nodePtr = nodePtr->next;
		}
		
		nodePtr->next = newNode;
	}
}

void Group::RemoveMember(string MemberType) {
	if (!head) {
		cout << "List is empty";
	} else {
		MemberNode *nodePtr = head;
		if (head->data.getMemberType() == MemberType) {
			head = nodePtr->next;
			delete head;
			totalMembers--;
		} else {
			MemberNode *nodePtr = head->next;
			MemberNode *prevNode = head;
			
			while (nodePtr) {
				if (nodePtr->data.getMemberType() == MemberType) {
					prevNode->next = nodePtr->next;
					delete nodePtr;
					totalMembers--;
				} else {
					prevNode = nodePtr;
					nodePtr = nodePtr->next;
				}
			}
		}
	}
}

void Group::AddChild() {
	Member newMember;
	newMember.setMemberType("Child");
	newMember.setDiscount(DEFAULT_CHILD_DISCOUNT);
	appendNode(newMember);
	totalMembers++;
}

void Group::AddAdult() {
	Member newMember;
	newMember.setMemberType("Adult");
	newMember.setDiscount(DEFAULT_ADULT_DISCOUNT);
	appendNode(newMember);
	totalMembers++;
}

void Group::AddSenior() {
	Member newMember;
	newMember.setMemberType("Senior");
	newMember.setDiscount(DEFAULT_SENIOR_DISCOUNT);
	appendNode(newMember);
	totalMembers++;
}


