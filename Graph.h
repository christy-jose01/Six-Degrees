#include <cstdlib>
#include <string.h>
#include <cstring>
#include <iostream>
#include <list>

using namespace std;

class Node{
	public:
		//properties of Node
		string actorName;
		string movie;
		Node *next;
		
		// default contructor
		Node(){
			actorName = "";
			movie = "";
			next = NULL;
		}
		// constructor that sets the contents
		Node(string a, string m){
			actorName = a;
			movie = m;
			next = NULL;
		}
};

class Path{
	public:
		// properties of Path
		int steps;
		Node *vertex;

		// default constructor
		Path(){
			steps = 1;
			vertex = NULL;
		}
		// constructor that sets up contents
		Path(int s){
			steps = s;
			vertex = NULL;
		}
		// functions
		void enqueue_path(Path, Node *); // done
		bool dequeue_path(Path, Node *); // done
		string printPath(Path); // done
		Node * last_element(Node *);
};

class Graph{
	public:
		//properties
		int numVertices;
		Path **g;
		// default constructor
		Graph(){
			numVertices = 1;
			g = (Node **)calloc(1, sizeof(Node *));
		}
		// constructor that sets the vertices
		Graph(int v){
			numVertices = v;
			g = (Node **)calloc(numVertices, sizeof(Node *));
		}
		//functions
		void addEdge(Node *, Node *); // done
		Node *allConnections(Table, Node *); // done
		Path *bfs(Table, string, string);
		Node * joinNodes(Node *, Node *); // done
		bool Node_in_LL(Node *, Node *); // done
};

