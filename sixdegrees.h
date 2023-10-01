#include "Graphs.h"

using namespace std;

class Table{
	public:
		//properties
		unsigned long numBuckets;
		Node **actorLL;
		Node **movieLL;

		// default constructor
		Table();
		// constructor that sets up the hashtable
		Table(unsigned long num);
		// functions
		void add_actor_to_actorLL(Node *); //done
		void add_movie_to_movieLL(Node *); // done
		unsigned long hash(string); //use this for actorLL and movieLL // done
		Node *find_actors_from_movie(string); // done
		Node *find_movies_w_actor(string); // done
};
