#include "voterwrapper.hpp"

using namespace std;

class Voter;

VoterWrapper::VoterWrapper(Voter* new_voter): voter(new_voter), next_voter(nullptr) {}

Voter* VoterWrapper::getVoter(){
    return voter;
}

VoterWrapper* VoterWrapper::getNextVoterWrapper(){
    return next_voter;
}
