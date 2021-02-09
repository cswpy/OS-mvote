#ifndef VOTERWRAPPER_H
#define VOTERWRAPPER_H

#include "voter.hpp"

class Voter;
class PostalEntry;

class VoterWrapper {
    public:
        Voter* voter;
        VoterWrapper* next_voter;
        friend PostalEntry;
        VoterWrapper(Voter* new_voter);
        Voter* getVoter();
        VoterWrapper* getNextVoterWrapper();
};

#endif