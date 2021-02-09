mvote :
	g++ mvote.cpp ballot.cpp postalentry.cpp voterwrapper.cpp voter.cpp -g -o mvote

clean :
	rm -rf mvote