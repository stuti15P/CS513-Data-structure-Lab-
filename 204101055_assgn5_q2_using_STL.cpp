/******************************************************************************/
/***												                       ****/
/* Description:-												              */
/* This program will take a DAG (Directed Acyclic Graph) as input and also an */
/* Ordering of the vertices of the DAG.                                       */
/* It returns TRUE if the ordering is Topological sort of the DAG. Else FALSE */
/*																			  */
/*Compiled and Executed in Dev c++ 5.11                                       */
/*Programmer:- Stuti Priyambda                                                */ 
/*Roll No:- 204101055											              */
/******************************************************************************/



#include<iostream>
#include<list>
#include<vector>
#define TRUE 1
#define FALSE 0

using namespace std; 

class Graph 
{ 
	 
    int v;   										//v represents vertex in the DAG(Directed Acyclic Graph)                             
    list<int> *adjacency_list; 						// Pointer to an array of adjacency list  of Graph 
    vector<int> indegree_vec; 							// vector to store indegree_vec of vertices
    
	public: 
    	Graph(int v)
		{
			this->v =v;
			adjacency_list =new list<int>[v+1];
			// Initialising all indegree_vec with 0 
    		for (int i = 0; i <=v; i++) 
        		indegree_vec.push_back(0); 
				
		} 
		void build_dag();
  		// function to add an edge to graph 
    	void add_edge(int start_vertex, int end_vertex); 
    	//Function to check whether given ordering is topological sort or not.
    	bool check_topological_sort();
    		
}; 

// Adding Edges to build the DAG.
void Graph::add_edge(int start_vertex, int end_vertex) 
{ 
    adjacency_list[start_vertex].push_back(end_vertex);  

	// increasing indegree_vec of end_vertex by 1 
    indegree_vec[end_vertex]++; 
} 
/* Function to build Directed Acyclic Graph. */
void Graph::build_dag()
{
	int s_vertex, e_vertex, no_of_edges, itr =0;
	//string s_flag;
	cout<<"Enter no. of edges in DAG\n";
	cin>>no_of_edges;
	cout<<"As instruction given in the question vertices numbered from 1 to n(n is total no. of vertices in DAG).";
	cout<<"please enter vertex numbered between 1 to n.\n";
	cout<<"********************************************************************************************\n\n";
	while(itr != no_of_edges)
	{
		cout<<"Enter start vertex of edge. \n";
		cin>>s_vertex;
		if (s_vertex==0 ||s_vertex >v)
		{
			cout<<"!! Entered starting vertex of an edge is wrong !!.please Enter vertex from 1 to n (n is total no. of vertices in DAG). \n";
			continue;
		}
		cout<<"Enter end vertex of edge. \n";
		cin>>e_vertex;
		if (e_vertex==0 ||e_vertex >v)
		{
			cout<<"!! Entered ending vertex of an edge is wrong !!. please Enter vertex from 1 to n (n is total no. of vertices in DAG).\n";
			continue;
		}
		//Building DAG by connecting vertices of GRAPH by adding Edges.
	
		this->add_edge(s_vertex, e_vertex);
		itr++;
		
	}
}

bool Graph::check_topological_sort()
{
	//This vector will keep the ordering of vertices which user will input.
	vector <int> ordering_vec;
	cout<<"Please input the ordering of vertices that you want to check.\n";
	for(int i =0; i<v; i++)
	{
		int vertex1;
		cin>>vertex1;
		ordering_vec.push_back(vertex1);
	}
	
	//Now checking whether given ordering is topological sort or not.
	for(int i=0; i<v; i++)
	{
		int curr_vertex = ordering_vec[i];
		
		//Checking whether this current vertex in input ordering has indegree 0 or not.
		//If it is not 0, means this is not topological sort of the graph.
		if(indegree_vec[curr_vertex]!= 0 )
			return FALSE;	
		
		//Another option while loop.
		for(int vertex: adjacency_list[curr_vertex])
		{
			indegree_vec[vertex] -=1;
		}
	}
	return TRUE;
}


int main() 
{ 
    // Creating Directed Acyclic Graph using adjacency list representation.
    int n;
    cout<<"Enter number of vertices in the DAG. \n";
    cin>>n;
    Graph g(n); 
    g.build_dag();
    
    if(g.check_topological_sort())
    	cout<<"TRUE\n";
    else
    	cout<<"FALSE\n";
    return 0; 
} 
