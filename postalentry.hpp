#ifndef POSTALENTRY_H
#define POSTALENTRY_H

class VoterWrapper;
class Voter;

class PostalEntry {
    public:
        int postal_code;
        PostalEntry* next_entry;
        VoterWrapper* voter_wrapper_head;
        int number_of_voted_person;
        PostalEntry(int postal_code);
        int delete_voter_in_postal_entry(int rin);
        VoterWrapper* find_voter_in_postal_entry(int rin);
        int register_voter_in_postal_entry(Voter* new_voter);
        ~PostalEntry();
};

#endif