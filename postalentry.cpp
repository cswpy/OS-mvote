#include <string>
#include "postalentry.hpp"
#include "voterwrapper.hpp"
#include "voter.hpp"

using namespace std;

class VoterWrapper;
class Voter;

PostalEntry::PostalEntry(int postal_code): postal_code(postal_code), next_entry(nullptr), voter_wrapper_head(nullptr), number_of_voted_person(0) 
{}

// Given a RIN, delete a VoteWrapper in the PostalEntry. If RIN is -1, delete the last VoteWrapper
int PostalEntry::delete_voter_in_postal_entry(int rin) {
    if(rin == -1){
        if(this->number_of_voted_person == 0)
            return -1;
        else if(this->number_of_voted_person == 1){
            delete this->voter_wrapper_head;
            this->number_of_voted_person--;
            return 0;
        }
        VoterWrapper* curr = this->voter_wrapper_head;
        while(curr->next_voter->next_voter != nullptr){
            curr = curr->next_voter;
        }
        this->number_of_voted_person--;
        delete curr->next_voter;
        curr->next_voter = nullptr;
        return 0;
    }
    else {
        if(this->voter_wrapper_head == nullptr)
            return -1;
        VoterWrapper* prev = this->voter_wrapper_head;
        VoterWrapper* curr = this->voter_wrapper_head->next_voter;
        if (prev->voter->getRin() == rin) {
            this->voter_wrapper_head = curr;
            this->number_of_voted_person--; 
            delete prev; 
            return 0;
        }

        while(curr != nullptr){
            if(curr->voter->getRin() == rin){
                prev->next_voter = curr->next_voter;
                this->number_of_voted_person--;
                delete curr;
                return 0;
            }
            prev = curr;
            curr = curr->next_voter;
        }
        return -1;
    }
}
// Append a new VoterWrapper to the end of the linked list
int PostalEntry::register_voter_in_postal_entry(Voter* new_voter) {
    if(this->voter_wrapper_head == nullptr) {
        this->voter_wrapper_head = new VoterWrapper(new_voter); 
        this->number_of_voted_person++; 
        return 0;
    }
    else
    {
        VoterWrapper* curr = this->voter_wrapper_head;
        while(curr->next_voter != nullptr){
            curr = curr->next_voter;
        }
        curr->next_voter = new VoterWrapper(new_voter);
        this->number_of_voted_person++;
        return 0;
    }

}

PostalEntry::~PostalEntry() {
    while(this->number_of_voted_person != 0)
        this->delete_voter_in_postal_entry(-1);
}
