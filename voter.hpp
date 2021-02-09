#ifndef VOTER_H
#define VOTER_H

#include <string>
#include <iostream>

class Voter {
    private:
        std::string first_name;
        std::string last_name;
        int rin;
        int postal_code;
        bool is_voted;
        Voter* next_voter;
    
    public:
        Voter ();
        Voter (std::string first_name, std::string last_name, int rin, int postal_code);
        bool setVotingStatus();
        bool getVotingStatus();
        int getPostalCode();
        Voter* getNextVoter();
        void setNextVoter(Voter* newVoter);
        int getRin();
        std::string getFirstName();
        std::string getLastName();
};

#endif
