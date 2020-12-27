/**********************************************************************************/
/***												                           ****/
/* Description:-												                  */
/* This program will build a binary tree having preorder threads and then using   */
/* those threads  traversing the tree in preorder.                                */
/*																				  */
/*Compiled and Executed in Dev c++ 5.11                                           */
/*Programmer:- Stuti Priyambda                                                    */ 
/*Roll No:- 204101055											                  */
/**********************************************************************************/

#include <iostream> 
#include<queue>
#define staksize 100
#define TRUE 1
#define FALSE 0
using namespace std; 

/* Nodd of Binary-tree having preorder threads.*/

class Nodd
{
	public:
	int val;
	Nodd *left_link;
	Nodd *right_link;
	bool rthreds;
	Nodd(int val)
	{
		this->val =val;
		this->left_link =NULL;
		this->right_link =NULL;
		//rthreds will be TRUE if the nodd will keep preorder successor.
		//It will be false if it will keep it's child.
		bool rthreds =FALSE;
	}
};

class Stack
{
	int stkpntr;                  //this stkpntr will point to top element of the stack.
	Nodd* *stak;  				//stak is a pointer which will hold address of the array (which will keep node-pointer)
	public:
		Nodd* pop();				//Function to pop nodes from stack.
		void push(Nodd* nodd);	    //Function to push nodes into the stack.
		bool isEmpty();				//checks whether stack is empty or not.
		Stack()
		{
			stkpntr =-1;
			stak =new Nodd*[staksize];			
		}

};
//This function pop element from top of the stack.
Nodd* Stack::pop()
{
	Nodd* nodd =NULL;
	if(stkpntr !=-1)
		nodd = stak[stkpntr--];
	return nodd;
}

//This function pushes element at the top of the stack.
void Stack::push(Nodd* nodd)
{
	if(stkpntr <staksize-1)
		stak[++stkpntr] =nodd;
	else
		cout<<"Stack overflow!!\n";	
	return;
}

bool Stack::isEmpty()
{
	//If stkpntr =-1 this means stack is empty so, return TRUE.
	if(stkpntr==-1)
		return TRUE;
	else
		return FALSE;
}

/*  building the Binary tree  having preorder Threads.  */
void travrseTreeUsingThreds(Nodd* rooot)
{	
	//If any of the subchild (left/right) is not NULL then iterate.
	while(rooot->left_link  || rooot->right_link)
	{
		//If the left child is NULL but right child exists so, print 
		//right_child key.
		if (!rooot->left_link  && rooot->right_link)
		{
			cout<<rooot->val<<" ";
			rooot = rooot->right_link;
		}
		//If the left child is not NULL  print left_child key.
		else if (rooot->left_link != NULL){
			cout << rooot->val<<" ";
			rooot = rooot->left_link;
		}
	}
	
	cout << rooot->val;
}
Nodd* buildTree(Nodd *rooot)
{
	int val1;
	cout<<"\nEnter the data at rooot node.\n";
    cin>>val1;
    rooot=new Nodd(val1);
    rooot->left_link = NULL;
    rooot->right_link = NULL;
    rooot->rthreds =FALSE;

    /* This is an empty Queue to enqueue all nodes so, that I will
       have all nodes of a binary tree level-wise left to right. */ 
    
	queue <Nodd *> queueOfNodd; 
    queueOfNodd.push(rooot); 
    while(!queueOfNodd.empty())
    {
    	Nodd* currnodd = queueOfNodd.front();
    	int lchilddata, rchilddata;
    	Nodd* left_chilld;
    	Nodd* right_chilld;
    	char lch ='n', rch ='n';
    	cout<<"\nDo You want to insert left child of nodd("<<currnodd->val<<") ";
    	cout<<"for YES enter y, FOR NO enter n.\n(ONLY ENTER y/n) \n";
    	cin>>lch;
    	if(lch == 'y' || lch == 'Y')
    	{
	    	cout<<"Enter key for left child of nodd("<<currnodd->val<<")\n";
	    	cin>>lchilddata;				
    		Nodd* nodd = new Nodd(lchilddata);
			nodd->right_link = currnodd->right_link;
			//As, nodd will be keeping preorder successor so, rthreds for this nodd will be True.
			nodd->rthreds =TRUE;
			currnodd->left_link = nodd;
			currnodd->right_link = NULL;
			//Since, Now currnodd will not be keeping preorder successor so, rthreds for this nodd will be False.
			currnodd->rthreds =FALSE;
			queueOfNodd.push(nodd);
		}
		cout<<"\nDo You want to insert right child of nodd("<<currnodd->val<<") ";
    	cout<<"for YES enter y, FOR NO enter n.\n(ONLY ENTER y/n) \n";
    	cin>>lch;
    	if(lch == 'y' || lch == 'Y')
    	{
    		cout<<"Enter key for right child for nodd("<<currnodd->val<<")\n";
    		cin>>rchilddata;
    		Nodd* nodd = new Nodd(rchilddata);
			if (currnodd->left_link != NULL)
			{	
				nodd->right_link = currnodd->left_link->right_link;
				//As, nodd is keeping the prorder successor so, rthreds will be True.
				nodd->rthreds =TRUE;
				currnodd->left_link->right_link = nodd;
				//As, currnodd->left_link is keeping the prorder successor so, rthreds will be True.
				currnodd->left_link->rthreds=TRUE;
			}
				
			else
			{	
				nodd->right_link = currnodd->right_link;
				nodd->rthreds =TRUE;
			}
				
					
			currnodd->right_link = nodd;
			queueOfNodd.push(nodd);
		}
		queueOfNodd.pop();
	}
	return rooot;
}

int main() 
{ 
	Nodd *rooot =NULL;
	//build the binary tree with preorder threads.
	cout<<"Building Binary tree having preorder threads\n\n";
	cout<<"********************************************************\n";
	rooot =buildTree(rooot);
	travrseTreeUsingThreds(rooot);
	return 0; 
}
