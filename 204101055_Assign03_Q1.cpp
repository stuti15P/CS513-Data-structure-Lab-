/********************************************************************************/
/***												                         ****/
/* Description:-												                */
/* This program will take number of persons and number of persons to be skipped */
/* before killing next one as input and arrange all persons in circular fashion.*/
/* Circular linked-list is used to arrange all persons in a circle FACING       */
/* TOWARDS CENTRE.The persons will be standing in clock-wise. i.e.. 2 will stand*/
/* left to 1. 3 will stand left to 2. 4 will stand left to 3 and so on...       */
/* In output,program shows the order of execution as well as the number of links*/
/* traversed in circular linked list before only one person remaining. 			*/
/*																				*/
/*Compiled and Executed in Dev c++ 5.11                                         */
/*Programmer:- Stuti Priyambda                                                  */
/*Roll No:- 204101055											                */
/********************************************************************************/

#include<iostream>

using namespace std;

/* Nodd class represents a node in the circular doubly linked list. 
   Doubly Linked List implementation because in case of single Linked
   List efficient deletion is not possible. */
class Nodd
{
	public:
		int val;			//Enter the val, this val will represent person number.
		Nodd *forward_link;			// forward_link to represent next person to the current one.
		Nodd *backward_link;		//backward_link to represent previous person to the current one.
		Nodd(int val)		//Constructor
		{
			this->val =val;
		}
};
/* arrangePersonsInCircularFashion() function will arrange all the persons
   in circle and return the head(start) Nodd of the linked list       */
Nodd* arrangePersonsInCircle(int num)
{
	int itr;
	Nodd *head_nodd = new Nodd(1);
	head_nodd->forward_link =NULL;
	head_nodd->backward_link =NULL;
	Nodd *previos_nodd = head_nodd;
	for(itr =2; itr<= num; itr++)
	{
		Nodd *new_nodd = new Nodd(itr);
		previos_nodd->forward_link =new_nodd;
		new_nodd->backward_link =previos_nodd;
		previos_nodd = new_nodd;
	}
	/*Making the linked list circular i.e.. connecting the last nodd's forward_link to 
	  starting one (head_nodd) . */
	previos_nodd->forward_link =head_nodd;
	head_nodd->backward_link =previos_nodd;
	return head_nodd;
}

/* findOrdrOfJosephusProblmExecution() function will take argument as start_nodd (representing
   the person from which counting starts) and k_value(the no. of persons to be skipped)  and show  
   the order of execution as well as total no. of links traversed till only one person left.  */	
void findOrdrOfJosephusProblmExecution(Nodd *start_nodd, int num, int k_value)
{
	/* no_of_liinks_traversed denotes the number of link traversed before killing a person.
	   and total_no_of_liinks_traversed denotes total number of link traversed before program 
	   terminates i.e.. only one person left and all get killed.   */
	unsigned no_of_liinks_traversed =0, total_no_of_liinks_traversed=0;
	int person_left = num;
	
	Nodd *head_nodd =start_nodd;
	/* Since Josephus problem continues till only one person i.e.. Josephus left
	   So, iterating  in the while loop till all get killed except one person. */
	while(person_left >1)
	{
		Nodd *nodd =head_nodd;
		/* Here, start_nodd  is representing the person from which couting starts in 
		   each case after killing the next person.
		   cur_nodd is  representing the current person while counting the k persons 
		   starting from the ist person i.e.. start_nodd. */
		int cont;
		Nodd *cur_nodd;
		cur_nodd = start_nodd;
		/* starting from persons from whom counting starts we will skip k persons */
		no_of_liinks_traversed = k_value% person_left;
		
		for(cont =0; cont< no_of_liinks_traversed; cont++)
		{
			cur_nodd =cur_nodd->forward_link;
		}
		
		cout<<"person "<<start_nodd->val<<" kills person "<<cur_nodd->val<<"\n";
		
		/* Updating the total number of link traversed, adding no_of_liinks_traversed for no. of 
		   link traversed before killing next person and adding 1 to it because 1 link advancement 
		   needed to update the start_nodd i.e.. from where next counting is going to start. */
		total_no_of_liinks_traversed += no_of_liinks_traversed+ 1;
		
		/* Updating the start_nodd and cur_nodd and freeing up memory after killing the person*/
		start_nodd =cur_nodd->forward_link;		
		start_nodd->backward_link =cur_nodd->backward_link;
		cur_nodd->backward_link->forward_link =start_nodd;
		free(cur_nodd);             // freeing up the memory i.e.. removing the person who get killed. 
		
		person_left--;
		
	}
	cout<<"Finally, person "<<start_nodd->val<<" is left and everyone else is killed\n";
	cout<<"\nThe No. of links traversed till only one person is left is : "<<total_no_of_liinks_traversed<<"\n";	
}
int main()
{
	int num, k_value;
	cout<<"Enter number of persons in Josephus Problem\n";
	cin>>num;
	cout<<"Enter the number of persons to be skipped before killing next person\n";
	cin>>k_value;
	if(num<=0 ||k_value<0)
	{
		cout<<"number of persons can't be less than 1 and no. of person to be skipped can't be less than 0\n";
		cout<<"!!!! please enter appropriate value. !!!";
		return 0;
	}
	/*After Taking the number of persons and the k_value (i.e.. number of persons
	  to be skipped before killing the next one) We have to arrange all persons 
	  in circular fashion and each one will face towards centre. So, here the 
	  function arrangePersonsInCircle() will  do that.   */
	Nodd *head_nodd; 
	head_nodd = arrangePersonsInCircle(num);
	
	/*Function to find the Order of execution of Josephus Problem and no. of links traversed.*/
	findOrdrOfJosephusProblmExecution(head_nodd, num, k_value);
	
}


