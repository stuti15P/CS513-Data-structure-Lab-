/********************************************************************************/
/***												                         ****/
/* Description:-												                */
/* This program will take input as total number of values to be sorted and      */
/* values, store all values in a linked list then apply merge sort to sort the  */
/* linked list.																	*/
/* This program will sort the number using merge sort without using extra space.*/
/*																				*/
/*Compiled and Executed in Dev c++ 5.11                                         */
/*Programmer:- Stuti Priyambda                                                  */
/*Roll No:- 204101055											                */
/********************************************************************************/


#include<iostream>

using namespace std;

// Nodd of Linked-List
class Nodd
{
	public:
		int val;
		Nodd *link;
		Nodd(int val)          //constructor
		{
			this->val =val;
		}
};
/* Storing all values in a single linked list one by one, and return the head node of
   the created linked list.   */
Nodd *storeValueInLinkedList(Nodd *head_nodd, unsigned no_of_value)
{
	int itr =0, value;
	while(itr!= no_of_value)
	{
		itr++;
		cout<<"Enter the value \n";
		cin>>value;
		Nodd *prev_nodd;
		/* if head_nodd is NULL this means this is the first value to be stored in linked list. 
		   head_nodd will always point to the start of the linked list. */
		if(head_nodd ==NULL)
		{
			head_nodd =new Nodd(value);
			head_nodd->link =NULL;
			prev_nodd =head_nodd;
		}
		/* if the entered value is not first one then we hit this else condition, first create a new
		   nodd for storing this value and then link with previous nodd.  */
		else
		{
			Nodd *new_nodd;
			//creating  new nodd
			new_nodd = new Nodd(value);
			new_nodd->link= NULL;
			prev_nodd->link =new_nodd;
			prev_nodd = new_nodd;
		}
	} //while-loop end
	//finally return head_nodd of the created single linked list.
	return head_nodd;
}
/* showList() function will take argument as head_nodd of the created linked list 
	and then iterate through list and print the values of linked list till end. */
void showList(Nodd *head_nodd)
{
	Nodd *curr_nodd =head_nodd;
	while(curr_nodd !=NULL)	
	{
		cout<<curr_nodd->val<<" ";
		curr_nodd =curr_nodd->link;
	}
} 
/* find_middle_nodd() will take head of the linked list as argument and find middle 
	of the linked-list.for finding middle of the linked list we will have two pointers 
	s_ptr, f_ptr. s_ptr will point to next values and f_ptr will point to next to next 
	values in each step.*/
Nodd *find_middle_nodd(Nodd *sorc)
{
	Nodd *prev_ptr =sorc, *s_ptr =sorc;
	Nodd *f_ptr =sorc;
	/* while loop iterates only if f_ptr and next of f_ptr both is not NULL.  */
	while(f_ptr && f_ptr->link)
	{
		prev_ptr =s_ptr;
		f_ptr =f_ptr->link->link;
		s_ptr =s_ptr->link;
	}
	/* if f_ptr becomes NULL this means we have even no. of values in Linked List
	   so, prev_ptr will point to middle of the list. so, return prev_ptr.   */
	if(!f_ptr)
	{
		return prev_ptr;
	}
	/* otherwise we have odd no. of values in Linked list so, s_ptr pointing to 
	   middle of the Linked list. so, return s_ptr. */
	else 
		return s_ptr;
}

/* This function will perform merge operation of the two Linked list which it takes as argument.*/
Nodd* perform_merge(Nodd* ist_list_start_nodd, Nodd* secnd_list_start_nodd) 
{ 
	//sorted_list_nodd will point to head of the merged Linked List.
    Nodd* sorted_list_nodd = NULL; 
    /* If first list has no values simply return second List start nodd. */
    if (!ist_list_start_nodd) 
        return secnd_list_start_nodd; 
    /* If second list has no values simply return first List start nodd. */
    else if (!secnd_list_start_nodd) 
        return ist_list_start_nodd; 
    /* Comparing Ist list values with second List, and sorted_list_nodd will point to 
       lesser values. */
    if (ist_list_start_nodd->val <= secnd_list_start_nodd->val) { 
        sorted_list_nodd = ist_list_start_nodd; 
        /* Ist Linked list nodd has lesser or equal value so, after storing it in sorted_list_nodd
		   move pointer to next value in Ist Linked List and again call perform_merge() to 
		   merge remaing values.   */
        sorted_list_nodd->link = perform_merge(ist_list_start_nodd->link, secnd_list_start_nodd); 
    } 
    else { 
        sorted_list_nodd = secnd_list_start_nodd; 
        /* 2nd Linked list nodd has lesser value so, after storing it in sorted_list_nodd
		   move pointer to next value in 2nd Linked List and again call perform_merge() to 
		   merge remaing values.   */
        sorted_list_nodd->link = perform_merge(ist_list_start_nodd, secnd_list_start_nodd->link); 
    } 
	//finally, returning the pointer pointing to start nodd of the merged List.
    return sorted_list_nodd; 
} 
//Merge Sort

Nodd* merge_sort(Nodd **head_nodd)
{
	//If there is only one nodd simply return the nodd.
	if(!(*head_nodd)->link)
		return *head_nodd;
	//mid_nodd will store the middle of the Linked List.
	Nodd *mid_nodd;
	Nodd *ist_list_start_nodd, *secnd_list_start_nodd;
	ist_list_start_nodd = *head_nodd;
	mid_nodd = find_middle_nodd(*head_nodd);
	//secnd list will start from next value of mid_nodd.
	secnd_list_start_nodd =mid_nodd->link;
	mid_nodd->link =NULL;
	// If ist_list_start_nodd exists i.e.. not NULL then call merge_sort for this list.
	if(ist_list_start_nodd)
	{
		merge_sort(&ist_list_start_nodd);
	}
	// If secnd_list_start_nodd exists i.e.. not NULL then call merge_sort for this list.
	if(secnd_list_start_nodd)
	{
		merge_sort(&secnd_list_start_nodd);
	}
	//If at least any one of the List is not NULL then call perform_merge() to merge the two lists.
	if(ist_list_start_nodd || secnd_list_start_nodd)
	{
		*head_nodd = perform_merge(ist_list_start_nodd, secnd_list_start_nodd);
	}
	return *head_nodd;
}



int main()
{
	unsigned no_of_value;
	cout<<"Enter total no. of values to be sorted\n";
	cin>>no_of_value;
	Nodd * head_nodd ;
	head_nodd =NULL;
	head_nodd =storeValueInLinkedList(head_nodd, no_of_value);
	cout<<"Your entered values before sorting is :-\n";
	if(head_nodd)
		showList(head_nodd);
	else
	{
		cout<<"No values entered for sorting.\n";
		return 0;
	}
	cout<<"\n";
	merge_sort(&head_nodd);
	cout<<"\nValues after merge sort.\n";
	showList(head_nodd);
	
}
