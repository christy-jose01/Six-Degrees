#include "sixdegrees.h"
#include <sstream>
#include <algorithm>
#include <array>
#include <fstream>
#include <stdexcept>

using namespace std;

int main(int argc, char **argv){
	if(argc < 3){ // must provide 2 arguments as input
		throw std::invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>"); 
	}

	// parse the cleaned_movielist file first
	ifstream movielist;
	movielist.open("cleaned_movielist.txt");

	string line;
	char *buff;
	char *cline;
	char *movie;
	
	Table data(150000); //initialize the Table

	// store the line
	while(getline(movielist, line)){
	// checks if the line is empty
		if(line.length()==0){
			continue;
		}
		buff = strdup(line.c_str()); // copying the line
		cline = strtok(buff, " "); // tokenize movie by whitespace
		movie = cline;
		cline = strtok(NULL, " ");


		// go through the entire line
		while(cline!=NULL){	
			Node *n = new Node(string(cline), string(movie));
			// add the actor and movie to the actorLL and movieLL	
			data.add_actor_to_actorLL(n);
			data.add_movie_to_movieLL(n);
			cline = strtok(NULL, " ");
		}
	}
	// finish parsing the cleaned_movielist
	movielist.close();

	// onto the actual program
	ifstream input; 
	ofstream output;

	input.open(argv[1]);
	output.open(argv[2]);

	// store actor 1 and actor 2
	char *actor1;
	char *actor2;

	while(getline(input, line)){
		// checks if the line is empty
		if(line.length()==0){
			continue;
		}
		buff = strdup(line.c_str()); // copying the line
		cline = strtok(buff, " "); // tokenize movie by whitespace
		actor1 = cline;
		cout << "actor 1 is " + (string)cline <<endl;
		cline = strtok(NULL, " ");
		actor2 = cline;
		cout << "actor 2 is " + (string)actor2 <<endl;
		cline = strtok(NULL, " ");

		// check if actor1 is the same as actor2
		// if true: Output = Actor1
		if(string(actor1) == string(actor2)){
			output << string(actor1) <<endl;
		}
		// check if both actor1 and actor2 are NOT present 
		// if true: Output = "Not present"
		else if((data.find_movies_w_actor(string(actor1))==NULL) ||
		(data.find_movies_w_actor(string(actor2))== NULL) ){
			output << "Not present" <<endl;
		}
		// create Path = bfs(Actor1, Actor2)
		// check if there is a Path between actor1 and actor2
		// if no: Output = "Not present"
		// if yes: Output = printPath
	}


	input.close();
	output.close();
}
