# mvote write-up
Author: Phillip Wang (pw1287@nyu.edu)

Course: Operating System

## Instruction

The Makefile compiles two command: make mvote and make clean. 

Make mvote will compile a single program called mvote from all the source code files.

Make clean will delete the executable program.

## Structure
**mvote** - Main driver program

**ballot** - Class that provides access to incapsulated utilities

**voter** - Voter class that implements basic info storage

**postalentry** - Class that collects voters who already voted with the same zipcode

**voterwrapper** - Class that wraps the pointer and points to the next votewrapper in a postalentry

All the classes are separately compiled into hpp file and cpp file.

## Libraries

* iostream - for input and output 
* string - for storing strings
* cstring - for copying and comparing strings
* fstream - for opening and reading files
* algorithms - for sorting the zipcodes
* sstream - for manipulating strings

## File
### mvote
mvote is the entry point of the whole program. Upon being called, it receives two required arguments: -m specifies the size of the hashtable. The number should be proportional to the number of voters specified in -f file.

After registered all the voter information in the file and saves them in the hashtables. The mvote awaits user input and parse it using the commandParser. The commandParser function takes one line of input and save it in a istringstream object that is capable of string manipulation, so that we could identify the first word and stores the arguments correspondingly. Mvote creates an instance of ballot and use its methods to fulfill the requirements.

### Ballot
Ballot is separately compiled by its header file .hpp and the source code file .cpp. Ballot has a member Voter** that stores the address of the Voter* list. We can access the Voter* members in a random access manner. But each Voter is hashed into different cells of the array using the hash function. It also contains a PostalEntry head that points to the first PostalEntry. When inserting new voters, it will create a new PostalEntry* for the zipcode if it does not already exist. The class implements general functions for statistics and methods to manipulate the Voter list and the PostalEntry list.

### PostalEntry
PostalEntry is the class that collects every voted persons under the same zipcode. It implements basic insert, search, and delete method to manage the VoteWrappers inside.

### VoterWrapper
VoterWrapper is a class that wraps the Voter and points to the next VoterWrapper* in the PostalEntry. Only getter methods are implemented.

### Voter
Voter is the fundamental type for storing the information of a single voter. Only implemented getter and setter methods.

