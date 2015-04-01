#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits.h>
#include <limits>
#include <list>
#include <cstdlib>

//So we have nice pretty exceptions
class ArrayBoundsException {
};

class underflow {
};

class overflow {
};

class division_by_zero {
};

class illegal_argument {
};

class out_of_bounds {
};

class Weighted_graph {
	private:
		static const double INF;
		// your choice
		double** adjmat; 	//adjacency matrix  
		int* darray ; 		//Array storing the degree of each node 
		int edgecount; 		//#edges in the graph
		int vertexcount;	//# of allocated space for vertexs 



	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;
		void insert( int, int, double );

	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Enter definitions for all public functions here

std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}

//Constructor 
Weighted_graph::Weighted_graph(int n ){									//Constructor of class

	vertexcount= n ; 
	adjmat = new double* [vertexcount];
	darray = new int[vertexcount];
	edgecount=0;

	//initialize adjacency matrix to INF for all nodes
	for (int i =0 ; i< vertexcount; i++ ) {
		adjmat[i]= new double[vertexcount];
		for (int j = 0 ; j< vertexcount;j++) {
			adjmat[i][j] = INF;

			if( i == j ) { 
				adjmat[i][j]=0;
			}

		}
		//Make the degree matrix to 0 ie no connected nodes 
		darray[i] = 0 ;
	}
}
//destructor

Weighted_graph::~Weighted_graph() { 					//deletes all global arrays, frees up memory 
	delete [] darray;
	for(int i = 0 ; i <vertexcount; i++ ) { 
		delete [] adjmat[i];

	}
	delete [] adjmat;
	
}

int Weighted_graph::degree(int n) const{			//Returns how many connected nodes to node n there are 
	if(n>=0 && n< vertexcount){
		return darray[n];

	}
	throw illegal_argument();
	
}

int Weighted_graph::edge_count() const{			//Returns # of edges in graph 
	return edgecount;
}

double Weighted_graph::adjacent(int m, int n) const { 		//Checks the adjacency table to see if m and n are connected 
	if(m>=vertexcount || n>=vertexcount|| n<0||m<0){
		throw illegal_argument();
	}
	return adjmat[m][n];
}

bool Weighted_graph::is_connected() const { 				//Uses BFS to check if all nodes are connected 
	int c= 0 ; 
	int connected = 0 ; 
	bool *visited  = (bool*)malloc(vertexcount);
	std::list<int> queue; 

	visited[0] = true; 
	queue.push_back(0);

	while(!queue.empty()){								//While the queue is not empty, keep going 
		c= queue.front(); 
		queue.pop_front();

		for(int i=0;i<vertexcount;++i){					//if theyre adjacenct mark them asa visited 
			if(!visited[i] && adjmat[c][i] != INF && adjmat[c][i] != 0){		
				visited[i]=true;	
				queue.push_back(i);
			}

		}

	}

	for(int j = 0; j< vertexcount;j++){					//Check if everynode was visited, if not return false 
		if(visited[j] == false){
			return false; 
		}
	}
	
	return true;
	free(visited);										//Free up memory 
	queue.clear();

	

	


}

double Weighted_graph::minimum_spanning_tree(int m) const{		//Returns the MST of the graph starting from node M  
	if( m <0 || m>= vertexcount){
		throw illegal_argument();
	}

	int V= vertexcount; 
	double key[V];
	bool goodset[V];
	double weight=0;
	int loc = 0 ;
	for(int i =0 ; i< V; i++ ) { 
		key[i]=INF;
		goodset[i]=false;

	}

	key[m]=0;

	for(int count =0 ; count <V-1 ;count++) { 					// for all ndoes find the lowest weighted edge  given nodes 
		 
		double min = INF; 

		for(int v=0;v<V;v++){
			if(goodset[v]==false && key[v] <min){				//key is weight of the edge between two nodes 
				min = key[v];
				loc = v;
			}

		}
		goodset[loc] = true;
		for(int v=0; v<V; v++ )  { 
			if(goodset[v]==false && adjmat[loc][v]<key[v]){
				key[v] = adjmat[loc][v];
				//std::cout<<"key: "<<key[v]<<"\n";
			}

		}





	}


	for (int i = 0 ; i < V; i++){		
		if(key[i]!=INF)								//Sum up all the keys that are valid and return the value 
			weight  = weight + key[i];
	}
	return weight;

}


void Weighted_graph::insert(int m, int n , double w) {
	if( n>= vertexcount || m>= vertexcount || w <0 || w == INF|| m==n|| m<0 || n<0){	// Checks if input is valid 
		throw illegal_argument();
	}else if ( w==0){
		if(adjmat[m][n]!=INF ){											// If the weight is 0, treat as a delete 
			darray[m]--;
			darray[n]--;
			edgecount--;
		}
		adjmat[m][n]=INF; 
		adjmat[n][m]=INF;

	}else if ( adjmat[m][n]==INF){										// if no edge exists before , add it 
		adjmat[m][n]=w; 
		adjmat[n][m]=w;
		darray[m]++;
		darray[n]++;
		edgecount++;
	}else {
		adjmat[m][n]=w; 												// if edge did exist, replace the old one with the new one 
		adjmat[n][m]=w;
	}


}



#endif
