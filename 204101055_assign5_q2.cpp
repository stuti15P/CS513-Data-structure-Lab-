/*********************************************************************************/
/***												                          ****/
/* Description:-												                 */
/* This is an efficient program (Time complexity of this program is O(|V| +|E|) )*/
/* and will take a DAG (Directed Acyclic Graph) as input and also an Ordering of */
/* the vertices of the DAG.                     	                             */
/* It returns TRUE if the ordering is Topological sort of the DAG. Else FALSE    */
/*																			     */
/*Compiled and Executed in Dev c++ 5.11                                          */
/*Programmer:- Stuti Priyambda                                                   */ 
/*Roll No:- 204101055											                 */
/*********************************************************************************/


#include<iostream>
#include<conio.h>
#define TRUE 1
#define FALSE 0

using namespace std; 
//structure representing an adjacency list nodd.
struct adjacency_list_nodd 
{ 
    int vertx; 
    struct adjacency_list_nodd* link; 
}; 
//structure for representation of an adjacency-list to represent the GRAPH.
struct adjacency_list 
{ 
    struct adjacency_list_nodd *head;  
}; 
bool flag =FALSE;
class Graph 
{ 
	 
    int v;   										//v represents no.of vertex in the DAG(Directed Acyclic Graph)   
	struct adjacency_list *adjcnc_list;            //Pointer to an array of adjacency list  of Graph               
    int *indegree_arr = new int[v+1] ; 							//Array to store indegree of the vertices
    
	public: 
    	Graph(int v)
		{
			this->v =v;
			this->adjcnc_list = (struct adjacency_list*) malloc((v+1) * sizeof(struct adjacency_list)); 
			if(this->adjcnc_list !=NULL)
			{
				// Initializing  each adjacency list as NULL. 
    			for (int i = 1; i <= v; ++i) 
        			this->adjcnc_list[i].head = NULL; 
				// Initialising all vertex indegree_arr with 0 
    			for (int i = 1; i <=v; i++) 
        			indegree_arr[i]= 0; 	
        	}
        	else
        		flag =FALSE;
        	
		} 
		//Function to build dag.
		void build_dag();
  		// function to add an edge to graph 
    	void add_edge(int start_vertex, int end_vertex); 
    	//Function to check whether given ordering is topological sort or not.
    	bool check_topological_sort();
    	/* Function to detect cycle in the graph , So that It will check whether 
    	   the USER has input a DAG or not.     */
    	bool detect_cycle();
    	/* helper function for Knowing whether Graph is DAG or not */
    	bool detect_cycle_helper(int v, bool *visted, bool *recr_stack);
  	
}; 
 
 
// Adding Edges to build the DAG.
void Graph::add_edge(int start_vertex, int end_vertex) 
{ 
	//cretaing a new nodd in the adjacency List
	struct adjacency_list_nodd* new_nodd = (struct adjacency_list_nodd*) malloc(sizeof(struct adjacency_list_nodd)); 
    new_nodd->vertx = end_vertex; 
    new_nodd->link = NULL; 
 
    new_nodd->link = this->adjcnc_list[start_vertex].head; 
    this->adjcnc_list[start_vertex].head = new_nodd; 
    
	// increasing indegree of end_vertex by 1 
    indegree_arr[end_vertex]++; 
} 

/* Function to build Directed Acyclic Graph. */
void Graph::build_dag()
{
	int s_vertex, e_vertex, no_of_edges, itr =0;
	string s_flag;
	
	cout<<"Enter no. of edges in DAG\n";
	cin>>no_of_edges;
	cout<<"\nAs instruction given in the question vertices numbered from 1 to n(n is total no. of vertices in DAG).";
	cout<<"please enter vertex numbered between 1 to n.\n";
	cout<<"**********************************************************************************************\n\n";
	while(itr != no_of_edges)
	{
		cout<<"Enter start vertex of edge. \n";
		cin>>s_vertex;
		if (s_vertex==0 ||s_vertex >v)
		{
			cout<<"!! Entered starting vertex of the edge is wrong !!.please Enter vertex from 1 to n (n is total no. of vertices in DAG).\n";
			cout<<"!! Enter correct vertex Number. !!\n";
			exit(0);
		}
		cout<<"Enter end vertex of edge. \n";
		cin>>e_vertex;
		if (e_vertex==0 ||e_vertex >v)
		{
			cout<<"!! Entered ending vertex of an edge is wrong !!. please Enter vertex from 1 to n (n is total no. of vertices in DAG).\n";
			cout<<"!! Enter correct vertex Number. !!\n";
			exit(0);
		}
		//Building DAG by connecting vertices of GRAPH by adding Edges.
	
		this->add_edge(s_vertex, e_vertex);
		itr++;
		
	}
}

/*  This function will take ordering of vertices as input and checks whether provided
	ordering is a Topological sort of the DAG or not.If it is topological ordering of
	the DAG then returns TRUE otherwise FALSE. */
bool Graph::check_topological_sort()
{
	//This array will keep the ordering of vertices which user will input.
	int *ordering_arr; 
	cout<<"Please input the ordering of vertices that you want to check.\n";
	ordering_arr = (int *)malloc(v* sizeof(int));
	for(int i =0; i<v; i++)
	{
		cin>>ordering_arr[i];
	}
	cout<<"\n\n";
	//Now checking whether given ordering is topological sort or not.
	for(int i=0; i<v; i++)
	{
		int curr_vertex = ordering_arr[i];
		
		//Checking whether this current vertex of input ordering has indegree 0 or not.
		//If it is not 0, means this is not topological sort of the graph.
		
		if(indegree_arr[curr_vertex]!= 0 )
			return FALSE;	
		
    	struct adjacency_list_nodd* padjlist = this->adjcnc_list[curr_vertex].head; 
        
        //Iterating in while-loop to decrease the indegree of the neighbouring vertices of curr_vertex.
        while (padjlist!= NULL) 
        {
        	indegree_arr[padjlist->vertx] -=1;
           	padjlist = padjlist->link; 
        } 
    
    } 
	
	return TRUE;
}

// detect_cycle_helper
bool Graph::detect_cycle_helper(int u, bool *visted, bool *rec_stack) 
{ 
    if(visted[u] == FALSE) 
    { 
        // Mark the current node as visited and part of recursion stack 
        visted[u] = TRUE; 
        rec_stack[u] = TRUE; 
  		
  		struct adjacency_list_nodd* padjlist = this->adjcnc_list[u].head; 
        
        //Iterating in while-loop to for all the vertices neighbouring to this vertex
        while (padjlist!= NULL) 
        {
        	if ( !visted[padjlist->vertx] && detect_cycle_helper(padjlist->vertx, visted, rec_stack) ) 
                return TRUE; 
            else if (rec_stack[padjlist->vertx]) 
                return TRUE; 
                
           	padjlist = padjlist->link; 
        } 
  		
    } 
    rec_stack[u] = FALSE;  // remove the vertex from recursion stack 
    return FALSE; 
} 

// Function will Return true if the graph contains a cycle, else false. 

bool Graph::detect_cycle() 
{ 
    // Mark all the vertices as not visited and not stack 
    bool *visted_arr = new bool[v+1]; 
    bool *recr_stack = new bool[v+1]; 
    for(int i = 1; i <= v; i++) 
    { 
        visted_arr[i] = FALSE; 
        recr_stack[i] = FALSE; 
    } 
  
    // Call the recursive helper function to detect cycle in different dfs trees 
    for(int i = 1; i <= v; i++) 
        if (detect_cycle_helper(i, visted_arr, recr_stack)) 
            return TRUE; 
  
    return FALSE; 
} 
int main() 
{ 
    // Creating Directed Acyclic Graph using adjacency list representation.
    int n;
    bool flag1 =TRUE;
    while(flag1)
    {
	
	    cout<<"Enter number of vertices. \n";
	    cin>>n;
	    Graph g(n); 
	    if(flag)
	    {
	    	cout<<"Sorry!! Memory has not been allocated for adjacency list.";
	    	return 0;
		}
	    g.build_dag();
	    /* If the  ordering is a topological sort of the DAG then check_topological_sort() 
	       function will return TRUE otherwise FALSE.   */
	       
	    if (g.detect_cycle())
	    {
	    	cout<<"\n\n********************************************************\n";
	    	cout<<"You entered a graph which is not a DAG.Since it has a cycle.\n\n";
	    	cout<<"!!! Input Graph must be DAG.create a new  DAG !!! \n\n";
	    	cout<<"**********************************************\n";
	    	continue;
	    	//return 0;
		}
		else
			flag1 =FALSE;
	
    	if(g.check_topological_sort())
    		cout<<"TRUE \n";
    	else
    		cout<<"FALSE \n";
	}
    return 0; 
} 
