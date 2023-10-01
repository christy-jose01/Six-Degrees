#include "Graphs.h"

using namespace std;

///////////////////// Path functions
void Path :: enqueue_path(Path p, Node *adding){
	// check if the LL is NULL
	if(p.vertex == NULL){
		p.vertex = adding;
	}
	else{
		//go to the bottom of the LL and add it there
		Node *here = p.vertex;
		while(here->next!=NULL){
			here = here->next;
		}
		// now we are all the way at the bottom
		here->next = adding;
		// set the pointer to NULL. we don't need it anymore
		here = NULL;
	}
}

bool Path :: dequeue_path(Path p, Node *removing){
	// check if the LL is already empty
	if(p.vertex == NULL){
		return false;
	}
	removing = p.vertex;
	Node *newNext = p.vertex->next;
	p.vertex = newNext;
	removing->next = NULL;
	// the removing node is now disconnected from everything
	delete(removing);
	return true;
}

string Path :: printPath(Path p){
	Node *here = p.vertex;
	string out = "";
	while(here->next!=NULL){
		out+= here->actorName + " -"+ here->next->movie + "- ";
		here = here->next;
	}
	// add the last actor
	out+=here->actorName;

	return out;
}

Node * Path :: last_element(Node *n){
  Node *here = n;
  while(here->next!=NULL){
    here = here->next;
  }
  return here;
}

///////////////////////// Graph functions

void Graph :: addEdge(Node *start, Node *dest){
	//dest goes in g[start]
	Node *here = start;
	while(here->next!=NULL){
		here = here->next;
	}
	here->next = dest;
}

Node * Graph :: joinNodes(Node *firstlist, Node *secondlist){
	Node *here = firstlist;
	while(here->next!=NULL){
		here = here->next;
	}
	here->next = secondlist;
}

Node * Graph :: allConnections(Table t, Node *to_find){
	string a = to_find->actorName;
	string m = to_find->movie;
	Node *returning = t.find_actors_from_movie(m);
	// we have the cast from movie m
	Node *mov = t.find_movies_w_actor(a);

	// adding cast from the rest of the movies
	while((mov!=NULL)&&(mov->movie!= m)){
		string m2 = mov->movie;
		Node *add = t.find_actors_from_movie(m2);
		returning = joinNodes(returning, add);
		mov=mov->next;
	}
	return returning;
}

bool Graph :: Node_in_LL(Node *comparing, Node *LL){
	while(LL!=NULL){
		if(LL = comparing){
			return true;
		}
		LL = LL->next;
	}
	return false;
}

Path * Graph :: bfs(Table t, string actor1, string actor2){
	// constructing Node for actor1
	Node *abc = t.find_movies_w_actor(actor1);
	string m1 = abc->movie;
	Node *a1 = new Node(actor1, m1);
	// constructing Node for actor2
	Node *def = t.find_movies_w_actor(actor2);
	string m2 = def->movie;
	Node *a2 = new Node(actor2, m2);
	// finished constructing Nodes
	Path starter = new Path();
	starter->vertex = a1;

	Node *visited = a1;
	vector <Path> to_visit; //LLPath
	to_visit.push_back(starter);

	while(!to_visit.empty()){
		Path current = to_visit.begin();
		to_visit.erase(to_visit.begin()); // dequeues Path from LL
		
		Node *edge = last_element(current.vertex);
		// compare edge to a2
		if(edge == a2){ // this most likely will not be the case
			return current;
		}

		// go through neighbors
		Node *neighbors = allConnections(t, edge);
		while(neighbors!=NULL){
			if(!Node_in_LL(neighbors, visited)){
				Path queueing = current;
				enqueue_path(queueing, neighbors); // the Path is extended
				to_visit.push_back(queueing); // add this extended Path to the queue of Paths
        visited->next = neighbors; 
			}
			neighbors = neighbors->next;
		}

		if(!Node_in_LL(edge, visited)){
			visited->next = edge;
		}
	}

	// if it has yet to  return anything, return an empty Path
	Path empty = new Path();
  return empty;
}
