#include<string>
#include "voter.hpp"

using namespace std;

Voter::Voter() {
    this->is_voted = false;
    this->next_voter = nullptr;
}

Voter::Voter(string first_name, string last_name, int rin, int postal_code) {
    this->first_name = first_name;
    this->last_name = last_name;
    this->rin = rin;
    this->postal_code = postal_code;
    this->is_voted = false;
    this->next_voter = nullptr;
}

bool Voter::setVotingStatus() {
    if(this->getVotingStatus())
        return false;
    this->is_voted = true;
    return true;
}

Voter* Voter::getNextVoter() {
    return this->next_voter;
}

void Voter::setNextVoter(Voter* new_voter) {
    this->next_voter = new_voter;
}

int Voter::getPostalCode() {
    return this->postal_code;
}

bool Voter::getVotingStatus() {
    return this->is_voted;
}

int Voter::getRin() {
    return this->rin;
}

string Voter::getFirstName(){
    return this->first_name;
}

string Voter::getLastName(){
    return this->last_name;
}