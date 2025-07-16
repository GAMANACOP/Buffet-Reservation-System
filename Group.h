#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <list>
#include <queue>

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
		int totalMembers;
		string representativeName;

		void appendNode(Member);
		void deleteNode(string MemberType);
		
	public:
		
		Group() {
			head = NULL;
			totalMembers = 0;
		}
		
		void setRepresentativeName(std::string);
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
		float computeMemberTotalFee(std::string) const;
		
		int countMember(std::string) const;
		int getTotalMembers() const {return totalMembers;}
};

#endif
