#include <string>
#include <list>
#include <queue>

#ifndef GROUP_H
#define GROUP_H

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

		int childCount;
		int adultCount;
		int seniorCount;
		string representativeName;

		void appendNode(Member);
		void deleteNode(string MemberType);
		
	public:
		
		Group() {
			head = NULL;
			childCount = 0;
			adultCount = 0;
			seniorCount = 0;
		}
		
		void setRepresentativeName(string);
		string getRepresentativeName() const {return representativeName;}
		
		// Functions for adding member
		void AddChild();
		void AddAdult();
		void AddSenior();
		
		// Function for removing member
		void RemoveMember(std::string);
		
		// Function for confirming reservation
		void ConfirmReservation(queue<Group> &);
		
		// Functions for computing payments
		float computeTotalPayment() const;
		float computeMemberTotalFee(string memberType) const;
		
		int countMember(string) const;
		int getTotalMembers() const {return adultCount + childCount + seniorCount;}
};

#endif
