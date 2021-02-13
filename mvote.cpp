#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "ballot.hpp"
#include "voter.hpp"

using namespace std;

// Comparator function for sorting the PostalEntries, if same, return the PostalEntry with larger zipcode
bool comparator(PostalEntry* PE_a, PostalEntry* PE_b) {
    return PE_a->number_of_voted_person == PE_b->number_of_voted_person ? PE_a->postal_code > PE_b->postal_code : PE_a->number_of_voted_person > PE_b->number_of_voted_person;
}

void insertion_sort(PostalEntry** PE_list, PostalEntry** PE_list_end) {
    for(int i = 1; i < (PE_list_end - PE_list); i++){
        PostalEntry* key = PE_list[i];
        int j = i - 1;

        while(j >= 0 && !comparator(PE_list[j], key)){
            PE_list[j+1] = PE_list[j];
            j = j - 1;
        }
        PE_list[j+1] = key;
    }
}

int argumentParser(int argc, char *argv[], int& number_of_basket, string& filename) {
    if(argc != 5) {
        cout<<"[ERROR] Incorrect argument number"<<endl;
        return -1;
    } else {
        for(int i = 0; i < argc; i++)
            if(strcmp(argv[i], "-m" ) == 0) 
                number_of_basket = (int)atoi(argv[++i]);
            else if(strcmp(argv[i], "-f") == 0)
                filename = string(argv[++i]);
            return 0;
    }
}

int commandParser(Ballot* my_ballot, istream& stream) {
    string raw_input;
    while(getline(stream, raw_input)) {
        istringstream command (raw_input);
        string word;
        // word stores the first keyword
        while(getline(command, word, ' ')) {
                if(word == "exit"){
                    cout<<"Program terminated."<<endl;
                    delete my_ballot;
                    return EXIT_SUCCESS;
                }
                else if(word == "v"){
                    cout<<"Number of people voted: "<<my_ballot->get_number_of_voter() - my_ballot->count_unvoted_person()<<endl;
                    break;
                }
                else if (word == "perc"){
                    float perc = (my_ballot->get_number_of_voter() - my_ballot->count_unvoted_person()) / (float)my_ballot->get_number_of_voter();
                    cout<<"Percentage of people voted: "<<perc*100<<"%"<<endl;
                    break;
                }
                else if (word == "l"){
                    string key;
                    getline(command, key, ' ');
                    Voter* target_voter = my_ballot->find_voter_by_rin(stoi(key));
                    if(target_voter) {
                        string voting_status = target_voter->getVotingStatus() ? "Yes" : "No";
                        cout<<"Found voter with RIN "<<key<<endl;
                        cout<<"First Name: "<<target_voter->getFirstName()<<endl<<"Last Name: "<<target_voter->getLastName()<<endl;
                        cout<<"Postal Code: "<<target_voter->getPostalCode()<<endl<<"Voting status: "<<voting_status<<endl;
                    } else{
                        cout<<"[ERROR] Voter not found."<<endl;
                    }
                }
                else if (word == "i"){
                    string rin, postal_code, first_name, last_name;
                    getline(command, rin, ' ');
                    getline(command, first_name, ' ');
                    getline(command, last_name, ' ');
                    getline(command, postal_code, ' ');

                    if(my_ballot->find_voter_by_rin(stoi(rin)) != nullptr) {
                        cout << "[ERROR] RIN " << rin << " already exists." << endl;
                    } else {
                        my_ballot->insert_voter(stoi(rin), first_name, last_name, stoi(postal_code));
                    }
                }
                else if (word == "d"){
                    string rin;
                    getline(command, rin, ' ');
                    if(! my_ballot->delete_voter_by_rin(stoi(rin))){
                        cout << "[ERROR] Voter not found."<<endl;
                    }
                }
                else if (word == "r"){
                    string rin;
                    getline(command, rin, ' ');
                    my_ballot->vote_by_rin(stoi(rin));
                }
                else if (word == "bv"){
                    string filename;
                    getline(command, filename, ' ');

                    fstream voter_register;
                    voter_register.open(filename, ios::in);
                    if(!voter_register) {
                        cout<<"File not found"<<endl;
                        continue;
                    }
                    else {
                        cout<<"Reading the file"<<endl;
                        string line;
                        int rin;
                        while(voter_register >> rin) {
                            my_ballot->vote_by_rin(rin);
                        }
                        cout << "Bulk voted all voter from the file."<<endl;
                    }
                }
                else if (word == "z"){//Done
                    string postal_code;
                    getline(command, postal_code, ' ');
                    PostalEntry* PE = my_ballot->find_postal_entry(stoi(postal_code));
                    cout << "Number of voted person with zipcode " << postal_code << ": " << PE->number_of_voted_person << endl;
                    VoterWrapper* VW = PE->voter_wrapper_head;
                    while(VW != nullptr){
                        cout << VW->voter->getRin() <<endl;
                        VW = VW->next_voter;
                    }
                }
                else if (word == "o"){
                    int number_of_postal_code = my_ballot->get_number_of_postal_code();
                    PostalEntry** PE_list = new PostalEntry*[number_of_postal_code];
                    PostalEntry* curr_PE = my_ballot->get_postal_entry_head();
                    for(int i = 0; i < number_of_postal_code; i++){
                        PE_list[i] = curr_PE;
                        curr_PE = curr_PE->next_entry;
                    }
                    insertion_sort(PE_list, PE_list + number_of_postal_code);
                    for(int i = 0; i < number_of_postal_code; i++){
                        cout << PE_list[i]->postal_code << " " << PE_list[i]->number_of_voted_person << endl; 
                    }
                    delete PE_list;
                }
                else {
                    cout << "Invalid arguments" << endl;
                }
            }

        }
    return EXIT_SUCCESS;
    }
    

int main(int argc, char *argv[]) {
    int number_of_basket;
    string filename;
    if(argumentParser(argc, argv, number_of_basket, filename) == -1)
        return EXIT_FAILURE;

    fstream voter_roster;
    voter_roster.open(filename, ios::in);
    if(!voter_roster) {
        cout<<"File not found"<<endl;
        return EXIT_FAILURE;
        }
    else {
        cout<<"Reading the file"<<endl;
        Ballot* my_ballot = new Ballot(number_of_basket);
        string line;
        int rin, postal_code;
        string first_name, last_name;
        while(voter_roster >> rin >> first_name >> last_name >> postal_code) {
            my_ballot->insert_voter(rin, first_name, last_name, postal_code);
        }
        cout << "Registered all voter from the file."<<endl;

        commandParser(my_ballot, cin);

    return EXIT_SUCCESS;

    }
};