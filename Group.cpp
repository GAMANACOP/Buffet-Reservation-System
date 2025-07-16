#include "Group.h"
#include "DefaultValues.h"

#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <fstream>

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
		if (head->data.getMemberType() == MemberType) {
			
			MemberNode *tempPtr = head;
			tempPtr = head->next;
			delete head;
			head = tempPtr;
			
			if (MemberType == "Child") {
				childCount--;
			} else if (MemberType == "Adult") {
				adultCount--;
			} else if (MemberType == "Senior") {
				seniorCount--;
			}
			return;
		} else {
			MemberNode *nodePtr = head->next;
			MemberNode *prevNode = head;
			
			while (nodePtr) {
				if (nodePtr->data.getMemberType() == MemberType) {
					prevNode->next = nodePtr->next;
					delete nodePtr;
					
					if (MemberType == "Child") {
						childCount--;
					} else if (MemberType == "Adult") {
						adultCount--;
					} else if (MemberType == "Senior") {
						seniorCount--;
					}
					
					return;
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
	childCount++;
}

void Group::AddAdult() {
	Member newMember;
	newMember.setMemberType("Adult");
	newMember.setDiscount(DEFAULT_ADULT_DISCOUNT);
	appendNode(newMember);
	adultCount++;
}

void Group::AddSenior() {
	Member newMember;
	newMember.setMemberType("Senior");
	newMember.setDiscount(DEFAULT_SENIOR_DISCOUNT);
	appendNode(newMember);
	seniorCount++;
}

void Group::setRepresentativeName(string repName) {
	representativeName = repName;
}

int Group::countMember(string memberType) const {
	if (memberType == "Child") {
		return childCount;
	} else if (memberType == "Adult") {
		return adultCount;
	} else if (memberType == "Senior") {
		return seniorCount;
	}
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
