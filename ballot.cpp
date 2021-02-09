#include <string>
#include "ballot.hpp"
#include <iostream>

using namespace std;

class Voter;

Ballot::Ballot(int m) {
    this->number_of_basket = m;
    this->voter_list = new Voter*[this->number_of_basket]();
    for(int i = 0; i < this->number_of_basket; i++) {
        this->voter_list[i] = nullptr;
    }
    this->number_of_voter = 0; 
    this->number_of_voted_person = 0;
    this->number_of_postal_code = 0;
}

// Insert voter into the hashtable, and create corresponding PostalEntry if not already exists
void Ballot::insert_voter(Voter* new_voter) {
    int basket_number = (new_voter->getRin() % this->number_of_basket);
    Voter* ptr = this->voter_list[basket_number];
    if(ptr == nullptr) {
        voter_list[basket_number] = new_voter;
    } else {
        while(ptr->getNextVoter() != nullptr) {
            ptr = ptr->getNextVoter();
        }
        ptr->setNextVoter(new_voter);
    }
    this->number_of_voter++;

    int zipcode = new_voter->getPostalCode();
    if(this->postal_entry_head == nullptr) {
        this->postal_entry_head = new PostalEntry(zipcode); 
        this->number_of_postal_code++; 
        return;
    }

    PostalEntry* curr = this->postal_entry_head;
    while(curr->next_entry != nullptr){
        if(curr->postal_code == zipcode){
            return;
        }
        curr = curr->next_entry;
    }
    if(curr->postal_code == zipcode)
        return;
    PostalEntry* new_PE = new PostalEntry(zipcode);
    curr->next_entry = new_PE;
    this->number_of_postal_code++;
}

// Helper method for creating and inserting a new voter
void Ballot::insert_voter(int rin, string first_name, string last_name, int postal_code) {
    Voter* new_voter = new Voter(first_name, last_name, rin, postal_code);
    this->insert_voter(new_voter);
}

// Find the pointer to the voter by hashing its RIN
Voter* Ballot::find_voter_by_rin(int rin) {
    int basket_number = rin % this->number_of_basket;
    Voter* ptr = voter_list[basket_number];
    if(ptr == nullptr) {
        return nullptr;
    } else {
        do{
            if(ptr->getRin() == rin) {
                return ptr;
            } else{
                ptr = ptr->getNextVoter();
            }
        } while(ptr != nullptr);
        return nullptr;
    }
}

// Find the voter by RIN, delete the object, fix the pointers to it if any, and return a bool indicating success/failure
bool Ballot::delete_voter_by_rin(int rin) {
    int basket_number = rin % this->number_of_basket;
    Voter* ptr = voter_list[basket_number];
    if(ptr == nullptr) {
        cout<<"Voter not found."<<endl;
        return false;
    }
    else{
        Voter* prev_voter = ptr;
        ptr = ptr->getNextVoter();
        if(prev_voter->getRin() == rin){
            if(prev_voter->getVotingStatus()){
                this->number_of_voted_person--;
                this->delete_voter_in_postal_entry(prev_voter);
            }
            delete prev_voter;
            voter_list[basket_number] = ptr;
            return true;
        }
        while(ptr != nullptr) { 
            if(ptr->getRin() == rin) {
                if(ptr->getVotingStatus()){
                    this->number_of_voted_person--;
                    this->delete_voter_in_postal_entry(ptr);
                }
                prev_voter->setNextVoter(ptr->getNextVoter());
                delete ptr;
                this->number_of_voter--;
                return true;
            }
            prev_voter = ptr;
            ptr = ptr->getNextVoter();
        }
        cout<<"Deletion failure, voter not found."<<endl;
        return false;
    }
}

// Find and delete the VoteWrapper in PostalEntry
void Ballot::delete_voter_in_postal_entry(Voter* ptr) {
    PostalEntry* tmp = find_postal_entry(ptr->getPostalCode());
    if(tmp){
        tmp->delete_voter_in_postal_entry(ptr->getRin());
    }
    else{
        cout<<"Error found in deletion."<<endl;
    }
}

PostalEntry* Ballot::find_postal_entry(int postal_code){
    PostalEntry* currPostalEntry = this->postal_entry_head;
    while(currPostalEntry != nullptr){
        if(currPostalEntry->postal_code == postal_code){
            return currPostalEntry;
        }
        currPostalEntry = currPostalEntry->next_entry;
    }
    return nullptr;
}

// Change the voting status of a voter
void Ballot::vote_by_rin(int rin) {
    Voter* curr_voter = find_voter_by_rin(rin);
    if(curr_voter != nullptr) {
        if(curr_voter->setVotingStatus()){
            PostalEntry* tmp = this->find_postal_entry(curr_voter->getPostalCode());
            if(tmp != nullptr)
                tmp->register_voter_in_postal_entry(curr_voter);
            else {
                cout<<"ERROR"<<endl; 
                exit(0);
                }
            this->number_of_voted_person++; 
            return;
            }
        cout<< "Voter " << rin << " already voted."<<endl;
    } else {
        cout<< "Voter " << rin << " not found."<<endl;
    }
}

int Ballot::count_unvoted_person() {
    return this->number_of_voter - this->number_of_voted_person;
}

int Ballot::get_number_of_voter() {
    return this->number_of_voter;
}

int Ballot::get_number_of_postal_code() {
    return this->number_of_postal_code;
}

PostalEntry* Ballot::get_postal_entry_head() {
    return this->postal_entry_head;
}

Ballot::~Ballot() {
    for(int i = 0; i < this->number_of_basket; i++) {
        while(this->voter_list[i] != nullptr) {
            this->delete_voter_by_rin(this->voter_list[i]->getRin());
        }
    }
    delete [] this->voter_list;
    this->delete_next_postal_entry(this->postal_entry_head);
}

void Ballot::delete_next_postal_entry(PostalEntry* ptr_pe) {
    if(ptr_pe->next_entry == nullptr){
        delete ptr_pe;
        return;
    }
    else {
        delete_next_postal_entry(ptr_pe->next_entry);
    }
    delete ptr_pe;
}
