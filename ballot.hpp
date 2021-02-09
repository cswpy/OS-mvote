#ifndef BALLOT_H
#define BALLOT_H
#include <string>
#include "voter.hpp"
#include "voterwrapper.hpp"
#include "postalentry.hpp"

class Voter;

class Ballot {
    private:
        int number_of_voter;
        int number_of_basket;
        int number_of_voted_person;
        int number_of_postal_code;
        Voter** voter_list;
        PostalEntry* postal_entry_head;

    public:
        Ballot(int m);
        void insert_voter(Voter* new_voter);
        void insert_voter(int rin, std::string first_name, std::string last_name, int postal_code);
        bool delete_voter_by_rin(int rin);
        Voter* find_voter_by_rin(int rin);
        int count_unvoted_person();
        int get_number_of_voter();
        void delete_voter_in_postal_entry(Voter* ptr);
        void print_zipcode_in_descending_order();
        PostalEntry* find_postal_entry(int postal_code);
        PostalEntry* get_postal_entry_head();
        void print_sorted_zipcodes();
        void vote_by_rin(int rin);
        int get_number_of_postal_code();
        void delete_next_postal_entry(PostalEntry* ptr_pe);
        ~Ballot();
};

#endif