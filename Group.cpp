#include "Group.h"

#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <fstream>

float const DEFAULT_FEE = 200;
float const DEFAULT_CHILD_DISCOUNT = 0.05;
float const DEFAULT_ADULT_DISCOUNT = 0.0;
float const DEFAULT_SENIOR_DISCOUNT = 0.2;


using namespace std;

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

void Group::ConfirmReservation(queue<Group> &groupQueue) {
	groupQueue.push(*this);
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

void Group::setRepresentativeName(string repName) {
	representativeName = repName;
}

int Group::countMember(string memberType) const {
	int count = 0;
	
	MemberNode *nodePtr = head;
	
	while (nodePtr) {
		
		if (nodePtr->data.getMemberType() == memberType) {
			count++;
		}
		
		nodePtr = nodePtr->next;
	}
	
	return count;
}

float Group::computeMemberTotalFee(string memberType) const {
	float payment = 0.0;
	
	MemberNode *nodePtr = head;
	
	while (nodePtr) {
		if (nodePtr->data.getMemberType() == memberType) {
			payment += DEFAULT_FEE - (DEFAULT_FEE * nodePtr->data.getDiscount());	
		}
		
		nodePtr = nodePtr->next;
	}
	
	return payment;
}

float Group::computeTotalPayment() const {
	return (computeMemberTotalFee("Child") + computeMemberTotalFee("Adult") + computeMemberTotalFee("Senior"));
}
