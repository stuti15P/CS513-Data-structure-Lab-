/*************************************************************/
/* This program is  implementing Tower of Hanoi by Iterative  */
/* approach. I have implemented a stack class and this stack  */
/* is used to keep discs. 									  */
/*                                    						  */
/* Compiled and Executed in Dev c++ 5.11                      */
/* Programmer:- Stuti Priyambda                               */
/* RollNo:- 204101055										  */
/*															  */
/*************************************************************/ 														

#include<iostream>
#include<math.h>
#define TRUE 1
#define FALSE 0

using namespace std;

class Stack
{
	private:
		int stkptr;						//stkptr is stackpointer, point to topmost element of the Stack.
		int *stak;						//stak is the base address of array.
		int staksize;					//represents the stack size.
	public:
		Stack(int staksize)
		{
			stkptr =-1;
			stak = new int[staksize];
			this->staksize =staksize;
		}

		bool isEmpty();       	    	 //isEmpty() will return TRUE if stack is empty otherwise return FALSE.
		bool isFull();				    //isFull() will return TRUE if stack is full otherwise return FALSE.
		void push(int val);     	   //push() will add value "val" into the stack on the topmost.
		int pop();			  		  //pop() will remove value from the topmost.
		~Stack()			  		 //destructor.
		{
			delete[] stak;
		}
};
void itrativeToh(int no_of_disc, Stack &sorc, Stack &auxlry, Stack &destn);


bool Stack::isEmpty()
{
	/*if stack pointer is -1 it means stack is empty so, return True */
	if(stkptr ==-1)
		return TRUE;
	/*otherwise stack must have  some element  so, return False */
	else
		return FALSE;
}

bool Stack::isFull()
{
	/* As, this is Array implementation of stack, and array indices starts from 0
	   so, if  stack pointer (sptr) = totalsize of stack -1 it means stack will 
	   be full. so, return True.   */
	if(stkptr ==staksize -1)
		return TRUE;
	/* otherwise return False */
	else
		return FALSE;
}

void Stack::push(int val)
{
	/* Before pushing value into the stack, checking stack is full or not, if full 
	   then  function just returns back without pushing value in the stack */
	if(isFull())
	{
		return;
	}
	/* if stack is not full then first increment the stack pointer(stkptr)  and  then
	    push value into the stack.    */
	stak[++stkptr] =val;
}

int Stack::pop()
{
	/* before popping up the value from stack, will just check whether stack is empty 
	   or not. if empty then can't pop value from the stack.  */
	if(isEmpty())
	{
		/* As Stack is empty so, it can't pop any value.  so, returning -1.  Disc
		   number can't be negative. so, returning -1 to show that stack is empty.  */
        return -1;
	}
	else
	{
		/* If Stack is not empty then pop the value from the stack and decrement the stack-
	       pointer by 1.  */
		int val;
		val=stak[stkptr--];
		return val;
	}
}


//Displaying the movement of discs by showDiscMovement()
void showDiscMovement(unsigned disc, string srcPeg, string destPeg )
{
    cout<<"Moved the disk "<<disc<<" from "<<srcPeg<<" to "<<destPeg<<endl;
}
void moveDiscBtwnTwoPegs(Stack &sorc, Stack &destn, string src, string dest)
{

    int peg1UpperDisc = sorc.pop();
    int peg2UpperDisc = destn.pop();

    // When peg1 has no disc on it. i.e.. peg1 is empty.
    if (peg1UpperDisc == -1)
    {
    	//moving the peg2 (i.e.. destn stack) topmost disc on to peg1.(i.e on sorc stack)
        sorc.push(peg2UpperDisc);
        showDiscMovement(peg2UpperDisc, dest, src);
    }

    // When peg2 has no disc on it. i.e.. peg2 is empty.
    else if (peg2UpperDisc == -1)
    {
    	//moving the peg1 (i.e.. sorc stack) topmost disc on to peg2.(i.e on destn stack)
        destn.push(peg1UpperDisc);
        showDiscMovement(peg1UpperDisc, src, dest);
    }

    /*If top disc of peg1 is greater than top disc of peg2 then 
      push back the top of the peg1 disc (which we have popped 
	  and stored in "peg1UpperDisc") and then push the top of 
      the peg2 disc (which we have already popped and stored in 
      "peg2UpperDisc") on to peg1.   */
    else if (peg1UpperDisc > peg2UpperDisc)
    {
        sorc.push(peg1UpperDisc);
        sorc.push(peg2UpperDisc);
        showDiscMovement(peg2UpperDisc, dest, src);
    }

    /*If top disc of peg2 is greater than top disc of peg1 then 
      push back the top of the peg2 disc which we have popped 
	  and stored in "peg1UpperDisc" and then push the top of 
      the peg2 disc (which we have already popped and stored in 
      "peg2UpperDisc") on to peg2.   */
    else
    {
        destn.push(peg2UpperDisc);
        destn.push(peg1UpperDisc);
        showDiscMovement(peg1UpperDisc, src, dest);
    }
}

//Iterartive function of Tower of Hanoi.
void itrativeToh(unsigned no_of_disc, Stack &sorc, Stack &auxlry, Stack &destn)
{
    int itr, no_of_movement;

    string src ="src", dest ="dest", helper= "helper";

    /* If number of discs is even, then interchange destination peg and  helper peg. */
    if(no_of_disc % 2 == 0)
    {
        string temp = dest;
        dest = helper;
        helper = temp;
    }
    no_of_movement = pow(2, no_of_disc) - 1;
	/* itr is iterator representing current no_of_movement. */
    for (itr = 1; itr <= no_of_movement; itr++)
    {
		/* if current no. of movement is divisible by 3 then the disc 
		   movement between auxlry and destn stack will happen. */
        if(itr % 3 == 0)
            moveDiscBtwnTwoPegs(auxlry, destn, helper, dest);
        /* if current no. of movement is divided by 3  and gives remainder '1'  
		   then the disc movement between sorc and destn stack will happen. */
        else if(itr % 3 == 1)
            moveDiscBtwnTwoPegs(sorc, destn, src, dest);
        /* if current no. of movement is divided by 3  and gives remainder '2'  
		   then the disc movement between sorc and auxlry stack will happen. */
        else
            moveDiscBtwnTwoPegs(sorc, auxlry, src, helper);
    }
}

int main()
{
	unsigned no_of_disc;
	int itr;
	cout<<"Enter no. of discs. \n";
	cin>>no_of_disc;
	/* creating three object of stack class each of size =no_of_disc.
	   these three objects of stack class will behave like peg on which
	   discs will be kept   */
	Stack sorc(no_of_disc), auxlry(no_of_disc), destn(no_of_disc);
	/* Pushing all discs onto the sorc stack keeping the biggest at the 
	   bottom and smallest at the top.  */
	for(itr= no_of_disc; itr>=1; itr--)
        sorc.push(itr);
    //calling the iterativeToh()
    itrativeToh(no_of_disc, sorc, auxlry, destn);

}
