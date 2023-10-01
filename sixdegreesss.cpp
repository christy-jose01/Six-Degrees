#include "sixdegrees.h"
#include <stdlib.h>

Table :: Table(){
	numBuckets = 1;
	actorLL = (Node **)calloc(1, sizeof(Node *));
	movieLL = (Node **)calloc(1, sizeof(Node *));;
}

Table :: Table(unsigned long num){
	numBuckets = num;
	actorLL = (Node **)calloc(numBuckets, sizeof(Node *));
	movieLL = (Node **)calloc(numBuckets, sizeof(Node *));
}

// this hash function was inspired by Prof. Rudnick's bluepint for my cse13s hw8
unsigned long Table :: hash(string key){
	unsigned long hash = 5381; // this is our prime number
	int c;
	// turn string into char *
	const char *char_key = key.c_str();

	while(*char_key!= '\0'){
		c = *char_key; //
		hash = ((hash << 5)+ hash) + (unsigned long)c;
		char_key++;
	}
	return hash;
}

void Table :: add_actor_to_actorLL(Node *actor){
	unsigned long hashvalue = hash(actor->actorName);
	unsigned long bucket_nu = hashvalue % numBuckets;

	Node *existing = actorLL[bucket_nu];
	// add the actor to the front of the LL
	Node *adding = actor;
	adding->next = existing;
	actorLL[bucket_nu] = adding;
	return;
}

void Table :: add_movie_to_movieLL(Node *film){
	unsigned long hashvalue = hash(film->movie);
	unsigned long bucket_nu = hashvalue % numBuckets;

	Node *existing = movieLL[bucket_nu];
	// add the film to the front of the LL
	film->next = existing;
	movieLL[bucket_nu] = film;
	return;
}

Node * Table :: find_actors_from_movie(string film){
	unsigned long hashvalue = hash(film);
	unsigned long bucket_nu = hashvalue % numBuckets;

	Node *existing = movieLL[bucket_nu];
	Node *ret = NULL;
	// add all of the nodes w/ same movie to ret
	while(existing!=NULL){
		if(existing->movie == film){
			Node *add = existing;
			add->next = ret;
			ret = add;
		}
		// iterate through the bucket
		existing = existing->next;
	}
	// by now ret should be ready
	return ret;
}

Node * Table ::find_movies_w_actor(string actor){
	unsigned long hashvalue = hash(actor);
	unsigned long bucket_nu = hashvalue % numBuckets;

	Node *existing = actorLL[bucket_nu];
	Node *ret = NULL;
	// add all of the nodes w/ same actor to ret
	while(existing!= NULL){
		if(existing->actorName == actor){
			Node *add = existing;
			add->next = ret;
			ret = add;
		}
		//iterate through bucket
		existing = existing->next;
	}
	// by now the ret should be ready
	return ret;
}
