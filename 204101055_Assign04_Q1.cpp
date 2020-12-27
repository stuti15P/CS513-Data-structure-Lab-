/**********************************************************************************/
/***												                           ****/
/* Description:-												                  */
/* This program will build a binary tree  (every node has at most 2 children.)    */
/* After building the tree I do Iterative tree traversal in both preorder and     */
/* postorder.                                                                     */
/*In Iterative preorder I do traversal in (Root)(Left_subtree)(Right_subtree) way.*/
/*In Iterative postorder I do traversal in (Left_subtree)(Right_subtree)(Root) way*/
/*																				  */
/*Compiled and Executed in Dev c++ 5.11                                           */
/*Programmer:- Stuti Priyambda                                                    */ 
/*Roll No:- 204101055											                  */
/**********************************************************************************/

#include<iostream>
#include<queue>
#define stksize 100
#define TRUE 1
#define FALSE 0


using namespace std;

/* Nodd of Binary-tree */

class Nodd
{
	public:
	int val;              			//val is to keep key value of the nodd.
	Nodd *left_link;				//left link of the nodd
	Nodd *right_link;				//right link of the nodd.
	Nodd(int val)						//Constructor
	{
		this->val =val;
		this->left_link =NULL;
		this->right_link =NULL;
	}
};

/* Stack  is needed so, that I can revisit a earlier visited nodd while
   traversing the tree in Iterative preorder and Iterative postorder.*/
class Stack
{
	int stkptr;						  //this stkptr will point to top element of the stack.
	Nodd* *stak;                     //stak is a pointer which will hold address of the array (which will keep node-pointer)
	public:
		Nodd* pop();                 //Function to pop nodes from stack.
		void push(Nodd* nodd);       //Function to push nodes into the stack.
		bool isEmpty();				 //checks whether stack is empty or not.
		Nodd* find_top_nodd();       //To find top nodes of the stack.
		Stack()
		{
			stkptr =-1;                  //Initially  stkptr will be-1. when there is no element in the stack.
			stak =new Nodd*[stksize];			
		}

};
Nodd* Stack::pop()
{
	Nodd* nodd =NULL;
	//If stkptr is not -1 i.e.. stack is not empty so, nodd from stack can be popped
	//and returned.Otherwise this function will return NULL.
	if(stkptr !=-1)
		nodd = stak[stkptr--];
	return nodd;
}

void Stack::push(Nodd* nodd)
{
	//If stkptr < stksize-1 this means stack is not full. so, more nodes can be pushed.
	if(stkptr <stksize-1)
		stak[++stkptr] =nodd;
	else
		cout<<"Stack overflow!!\n";	
	return;
}
Nodd* Stack::find_top_nodd()
{
	//If stkptr is not equal to -1 i.e.. stack is not empty so, return the top nodd.
	if(stkptr!= -1)
		return stak[stkptr];
	//If stack is empty then return NULL.
	return NULL;
}
bool Stack::isEmpty()
{
	//stkptr is -1 i.e.. Stack is empty so, this function will return True.
	if(stkptr==-1)
		return TRUE;
		
	else
		return FALSE;
}

/*  Building  the Binary tree   in level-order. */
Nodd* build_tree(Nodd *rooot)
{
	int value1;
	cout<<"\nEnter data value at rooot node.\n";
    cin>>value1;
    rooot=new Nodd(value1);
    rooot->left_link = NULL;
    rooot->right_link = NULL;
    
    /* Creating an empty Queue to keep all nodes so, that I can 
       have all nodes of a binary tree level-wise left to right. */ 
    
	queue <Nodd *> noddQueue; 
    noddQueue.push(rooot); 
    /* Iterating in while loop  until queue becomes empty, this queue will become
       empty after we enter last leaf node of the tree.   */ 
    while(!noddQueue.empty())
    {
    	/*getting the front node from queue.This will be the node for which I have to 
		  take input of left child and right child currently.  */ 
    	Nodd* frontnodd =noddQueue.front();
    	int leftval, rightval;
    	Nodd* left_child;
    	Nodd* right_child;
    	/* If left-child will not be NULL then user will give 'y' as input 
		   then the key value inserted by user become the key for 
    	   left child of the curent Nodd. And that new node will be inserted as 
		   left child of the nodd. same happen for right child. */
    	char lch ='n', rch ='n';
    	cout<<"\nDo You want to insert left child of nodd("<<frontnodd->val<<") ";
    	cout<<"For yes enter y, If you don't want  then press n.\n(ONLY ENTER y/n):---\n";
    	cin>>lch;
    	if(lch == 'y' || lch == 'Y')
    	{
	    	cout<<"\nEnter key of left child for nodd("<<frontnodd->val<<")\n";
	    	cin>>leftval;
	    	left_child = new Nodd(leftval);
	    	frontnodd->left_link =left_child;
	    	noddQueue.push(left_child);
	    		
		}
    	cout<<"\nDo You want to insert right child of nodd("<<frontnodd->val<<") ";
    	cout<<"For yes enter y, If you don't want  then press n.\n(ONLY ENTER y/n):---\n";
    	cin>>lch;
    	if(lch == 'y' || lch == 'Y')
    	{
    	
			cout<<"\nEnter key of right child for nodd("<<frontnodd->val<<")\n";
    		cin>>rightval;
    		right_child = new Nodd(rightval);
    		frontnodd->right_link =right_child;
    		noddQueue.push(right_child);
		}
    	noddQueue.pop();
    	
	} //While -loop iterating till Queue of nodds is not empty
	
	return rooot;
}

/*Function to traverse  the tree in preorder  */
void traverse_in_preorder(Nodd *nodd)
{
	Stack stk1;
	cout<<"PREORDER Traversal of the tree is:-\n";
	while(TRUE)
	{
		while(nodd!= NULL)
		{
			cout<<nodd->val<<" ";
			if(nodd!=NULL)
				stk1.push(nodd);
				
			//going to the left-most subtree
			nodd= nodd->left_link;
		}
		//If stack is not empty but nodd becomes null means we visited left-most tree
		//Now pop Node from stack and go to it's right subtree.
		if(!stk1.isEmpty())
		{
			Nodd* nodd1;
			nodd1 =stk1.pop();
			nodd =(nodd1)->right_link;
		}
		//If stack becomes empty then it means we visited all node so, break the while loop.
		else
			break;
	}
	
	return;
}


void traverse_in_postorder(Nodd *nodd)
{
	Stack stk1;
	cout<<"POSTORDER Traversal of the tree is:-\n";
	while(TRUE)
	{
		if(nodd!= NULL)
		{
			stk1.push(nodd);
			//Visiting left sub-tree
			nodd= nodd->left_link;
			
		}
		else
		{
			//If stack becomes empty then it means traversal completed i.e.. all
			// nodes are visited so, come out of while loop.
			if (stk1.isEmpty())
				break;
			else
			{
				Nodd *top_nodd;
				top_nodd =stk1.find_top_nodd();
				if(top_nodd)
				{
					if(top_nodd->right_link ==NULL)
					{
						nodd =stk1.pop();
						//visited left subtree and right child is NULL so, now print nodd key i.e.. val.
						cout<<nodd->val<<" ";
						top_nodd =stk1.find_top_nodd();
						//Finding top nodd of the stack and comparing with it's right child 
						//and nodd . if both are same i.e.. visited left subtree and now visiting right
						//child so, after that print this nodd.
						while(top_nodd && nodd == top_nodd->right_link)
						{
							cout<<top_nodd->val<<" ";
							nodd =stk1.pop();
							top_nodd =stk1.find_top_nodd();
								
						}
						
					}
				}
				if(!stk1.isEmpty())
					nodd =top_nodd->right_link;
				else
					nodd =NULL;
				
			}
			
		} 
	}
	
}
	

int main()
{
	Nodd *rooot =NULL;
	//build the binary tree.
	cout<<"\tBuilding the tree level wise.\n\n";
	cout<<"***********************************************\n";
	rooot =build_tree(rooot);
	traverse_in_preorder(rooot);
	cout<<"\n";
	traverse_in_postorder(rooot);
	
	return 0;
}
