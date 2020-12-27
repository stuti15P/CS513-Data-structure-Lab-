/***************************************************************************/
/***												                  ******/
/* Description:-												           */
/* This program will implement a queue using two stacks.In one stack       */
/* we will perform Insertion of element, deletion will be performed        */
/* from other stack.If first stack(stak1) is full and stak2 is empty       */
/* then first we transfer all the elements from stak1 to stak2 and then    */
/* perform insertion in stak1.If stak2 is not empty then Insertion of new  */
/* element will be blocked.											       */
/*For deletion if stak2 is empty then we trasfer element from stak1 provided*/ 
/*stack1 is not empty, otherwise Underflow condition hits.                */
/*																		   */
/*Compiled and Executed in Dev c++ 5.11                                    */
/*Programmer:- Stuti Priyambda                                            */
/*Roll No:- 204101055											           */
/***************************************************************************/

#include<iostream>
#include<conio.h>
#define TRUE 1
#define FALSE 0
#define STAKSIZE 100                		    //defined stack size as macros

using namespace std;
template <class T>
class Stack
{
	private:
		int sptr;      					     //sptr is the stack-pointer pointing top-most value in the stack.
		T *stak;							 //stak is a pointer of T type

	public:
		Stack()						         //Constructor.
		{
			sptr = -1;						//initially stack pointer will be -1.
			stak = new T[STAKSIZE];		    //allocating memory for stack and returning base address which will be stored in stak.

		}

		bool isEmpty();       	    	    //isEmpty() will return TRUE if stack is empty otherwise return FALSE.
		bool isFull();				       //isFull() will return TRUE if stack is full otherwise return FALSE.
		void push(T val);     		      //push() will add value "val" into the stack on the topmost.
		T pop();			  		     //pop() will remove value from the topmost and decrement the stackpointer(sptr).
		void display(bool flag);		 //display the element present in Stack.
		~Stack()			  		 //destructor.
		{
			delete[] stak;
		}
};
template<class T>
class Queue
{
	private:
	Stack<T>  stk1;						//creating object of  Stack class
	Stack<T>  stk2;						//creating object of  Stack class
	public:
	void qenque(T val);					//function for inserting the  value "val"  into the queue.
	T qdeque();							//function for deleting element from queue.
	bool qIsEmpty();					//will return True if Queue is Empty else False.
	bool qIsFull();						//will return True if Queue is Full else False.
	void qdisplay();					//will display the queue.

};

/* flag to decide how stack value will be shown,whether top to bottom 
   or bottom to top to dispaly Queue.    */
bool flag =0;

template <class T> bool Stack<T>::isEmpty()
{
	/*if stack pointer is -1 it means stack is empty so, return True */
	if(sptr ==-1)							
		return TRUE;
	/*otherwise stack must have  some element  so, return False */
	else
		return FALSE;
}

 template <class T>bool Stack<T>::isFull()
{
	/* As, this is Array implementation of stack, and array indices starts from 0
	   so, if  stack pointer (sptr) = totalsize of stack -1 it means stack will 
	   be full. so, return True.   */
	if(sptr ==STAKSIZE -1)
		return TRUE;
	/* otherwise return False */
	else
		return FALSE;
}

template <class T> void Stack<T>::push(T val)
{
	/* Before pushing value into the stack, checking stack is full or not, if full 
	   then  function just returns back without pushing value in the stack */
	if(isFull())
	{
		return;
	}
	/* if stack is not full then first increment the stack pointer(sptr)  and  then
	    push value into the stack.    */
	stak[++sptr] =val;
}

template <class T> T Stack<T>::pop()
{
	/* before popping up the value from stack, will just check whether stack is empty 
	   or not. if empty then can't pop value from the stack.  */
	if(isEmpty())
	{
		/* As Stack is empty so, it can't return any value of T type. */
		exit(1);      
	}
	/* If Stack is not empty then pop the value from the stack and decrement the stack-
	   pointer by 1.  */
	else
	{
		T val;
		val=stak[sptr--];
		return val;
	}
}


template <class T> void Stack<T>::display(bool flag)
{
	/*I am using flag so, that the  display in Queue will show correctly
	  according to queue properties.  */
	  
	int itr;       //local variable to iterate through stack.
	
	/* If flag is not set i.e.. flag is '0' then show the stack bottom to top. */
	if(flag==0)
	{
		for(itr =0; itr<=this->sptr; itr++)
		{
			cout<<stak[itr]<<" ";
		}
	}
	/* If flag is  set i.e.. flag is '1' then show the stack top to bottom. */
	else
	{
		for(itr =this->sptr; itr>=0; itr--)
		{
			cout<<stak[itr]<<" ";
		}
	}
	
}

/* function to check whether Queue is empty or not.If empty then return True else False.  */
template <class T> bool Queue<T> ::qIsEmpty()
{
	if(this->stk1.isEmpty() && this->stk2.isEmpty())
		return TRUE;
	else
		return FALSE;
}

/* function to check whether Queue is full or not. If full then return True else False. */
template <class T> bool Queue<T> ::qIsFull()
{
	if(stk1.isFull() &&stk2.isFull())
		return TRUE;
	else
		return FALSE;
}
			      
template <class T> void Queue<T> ::qenque(T val)
{
	/* If stack stk1 is not full then push value into the stack.  */
	if(!stk1.isFull())
	{
		stk1.push(val);
	}
		
	else
	{
		/*if stack stk1 is full and stk2 is also full then Queue Overflow. */
		if(stk2.isFull())
			cout<<"Overflow!! can't insert this element in queue: Queue is full \n";
		/* If stack stk1 is full but stk2 is empty then first transfer all value from 
		   stk1 to stk2 and then push the new value (that we want to insert) in stk1. */
		else if(stk2.isEmpty())
		{
			/*flag will be set if we are pushing value in stack stk2 from stk1.so, that the 
			first inserted value in Queue which is now in stk2 can be first shown. */
			flag =1;                 
			while(!stk1.isEmpty())
			{
				T temp;
				temp =stk1.pop();
				stk2.push(temp);
			}
			stk1.push(val);
		}
		/* If stack stk1 is full but stk2 is not empty then block the Insertion. */
		else
		{
			cout<<"can't insert this element in queue:  INSERTION BLOCKED \n";
			return;
		}
	}
}

template <class T> T Queue<T>::qdeque()
{
	//If both stack stk1, stk2 is empty then Underflow condition.
	if(stk1.isEmpty() && stk2.isEmpty())
	{
		cout<<"Underflow!!  can't perform deletion in queue:As, queue is empty. \n";
		exit(1);
	}
	//If stack stk2 is not empty then pop value from stack stk2.
	T val;
	if(!stk2.isEmpty())
	{
		val =stk2.pop();
		return val;
	}
	/* If stack stk2 is empty and stack stk1 is not empty then first transfer 
	   all value from Stack stk1 to stk2 and then pop element from stack stk2. */
	else if(stk2.isEmpty() && (!stk1.isEmpty()))
	{
		while(!stk1.isEmpty())
		{
			T temp;
			temp =stk1.pop();
			stk2.push(temp);
		}
		val =stk2.pop();
		return val;
	}
	
			
}
//Function to show display value in Queue.
template <class T> void Queue<T>::qdisplay()  
{

	int itr;       //local variable to iterate through stack.
	if(qIsEmpty())
	{
		cout<<"Nothing to display, Queue is empty.\n";
	}
	else if(flag ==1)
    {
    	cout<<"Queue is :-\n";
    	/* If flag =1, it means Ist inserted element is now in stack stk2 from
    	   top to bottom, so passing this Flag to show the stk2 value top to bottom. 
		   and  will show stack stk1  from bottom to top so, passing (!flag). */
    	stk2.display(flag);
    	stk1.display(!flag);
    }
    else if(!stk1.isEmpty())
    {
    	/* If stack stk1 is not empty and stack stk2 is also not empty then 
    	First show stack stk2 and then stack stk1.  */
    	cout<<"Queue is :-\n";
    	if(!stk2.isEmpty())
    	{
    		stk2.display(flag);
		}
		stk1.display(flag);
	}
    else
    {
    	/* If Stack stk1 is empty then Show Stack stk2 from top to bottom. */
    	cout<<"Queue is :-\n";
    	stk2.display(!flag);
    }
    
}

int main()
{
	Queue<int> q;
	system("cls");
	while(1)
	{
		cout<<"\n*--------------------------------------------------------------*\n";
		cout<<"press 1, to insert value in the queue. \n";
		cout<<"press 2, to delete value from queue. \n";
		cout<<"press 3, to display the Queue. \n";
		cout<<"press 0, to exit. \n";
		cout<<"*---------------------------------------------------------------*\n";
		switch(getch())
		{
			case '1':
			{
				int value;
				cout<<"enter value to insert in queue. \n";
				cin>>value;
				q.qenque(value);
			}
			break;
			case '2':
            {
            	int value;
                value =q.qdeque();
                cout<<value<<" deleted from queue\n";
            }
            break;
            case '3':
            {
                q.qdisplay();
            }
            break;
            case '4':
            	exit(0);
            break;
            default:
                system("cls");
                cout<<"\nEnter 0 to 3 only";
                cout<<"\n Enter any key\n";
                getch();
		}

	}

}

