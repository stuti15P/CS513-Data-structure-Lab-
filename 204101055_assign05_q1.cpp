/*********************************************************************************/
/***												                          ****/
/* Description:-												                 */
/* This program will find k-closest elements to an element x in an array,where   */
/* element x belongs to the array.												 */	
/* For this I did partitioning of array around element x and build max-heap for  */
/* all elements left to x and min-heap for all elements right to x.After this I'm*/
/* iterating for k times to find k-closest elements and every time I'm comparing*/   
/* between the root elements of max-heap and min-heap whichever is the closest I */
/* am printing that and then deleting  from the heap and then calling max_heapify*/
/* if I am deleting from max_heap else calling min_heapify if I am deleting from */
/* min-heap.     																 */          				
/*																				 */
/*Compiled and Executed in Dev c++ 5.11                                          */
/*Programmer:- Stuti Priyambda                                                   */ 
/*Roll No:- 204101055											                 */
/*********************************************************************************/
#include<iostream>
#include<climits>

using namespace std;


int partition_around_x(int *num_array, int l_index, int h_index)
{

	int pivot_elmnt = num_array[h_index];
	int l= l_index -1;
	for (int i= l_index; i<= h_index- 1; i++) 
    { 
        // If current element is smaller than or equal to pivot 
        if (num_array[i] <= pivot_elmnt) 
        { 
            l =l+1;   // increment index of smaller element 
            int temp_val =num_array[l];
            num_array[l] = num_array[i];
            num_array[i] =temp_val;
        } 
    } 
    int temp2_val =num_array[l+1];
    num_array[l+1] = num_array[h_index];
    num_array[h_index] = temp2_val;
    return l + 1;  
} 

/* Max_heapify Function:--->      */
void max_heapify(int *left_array, int i, int n)
{
	int l_index, r_index, largest_element_index;
	l_index = 2*i + 1; 
	r_index = 2*i + 2; 
	largest_element_index = i; // Initialize largest as root 
	
	// checking if left child is greater than root element
    if (l_index< n && (left_array[l_index] > left_array[largest_element_index]))
        largest_element_index = l_index; 
  
    // checking if right child is greater than largest element till now. 
    if (r_index< n && (left_array[r_index] > left_array[largest_element_index]))
        largest_element_index = r_index; 
  
    // If largest is not root element.
    if (largest_element_index != i) 
    {
    	//swapping ith indexed element and largest_element_index.
    	int temp =left_array[i];
    	left_array[i] =left_array[largest_element_index];
    	left_array[largest_element_index] =temp;
        // max_heapify will be called recursively
        max_heapify(left_array, largest_element_index, n); 
    } 
	
}

//Function for Building Max-Heap 
void build_max_heap(int *left_array, int size)
{
	int start_index = (size/2) -1;
	for(int i =start_index; i>=0; i--)
	{
		max_heapify(left_array, i, size);
	}

}	

/* Min_heapify Function:--->      */
void min_heapify(int *right_array, int i, int n)
{
	int l_index, r_index, smallest_element_index;
	l_index = 2*i + 1; 
	r_index = 2*i + 2; 
	smallest_element_index = i; // Initialize smallest as root element 
	
	// checking if left child is less than root element
    if (l_index< n && (right_array[l_index] < right_array[smallest_element_index]))
        smallest_element_index = l_index; 
  
    // checking if right child is less than smallest element till now. 
    if (r_index< n && (right_array[r_index] < right_array[smallest_element_index]))
        smallest_element_index = r_index; 
  
    // If smallest element is not root element.
    if (smallest_element_index != i) 
    {
    	//swapping ith indexed element and smallest_element_index.
    	int temp =right_array[i];
    	right_array[i] =right_array[smallest_element_index];
    	right_array[smallest_element_index] =temp;
        // max_heapify will be called recursively
        min_heapify(right_array, smallest_element_index, n); 
    } 	
}

//Function for Building Min-Heap
void build_min_heap(int *right_array, int size) 
{
	int start_index = (size/2) -1;
	for(int i =start_index; i>=0; i--)
	{
		min_heapify(right_array, i, size);
	}
}

// Function to delete the root from max_heap. 
void delete_max(int array1[], int &n) 
{ 
	
	if(n<1)
	{
		return;
	}
    // Replace root_element of heap with last element of heap.
    array1[0] = array1[n-1]; 
  	// Decreasing heap-size by 1 
    n = n - 1; 
	// max_heapify the root node 
    max_heapify(array1, 0, n); 
} 

// Function to delete the root from min_heap. 
void delete_min(int array1[], int &n) 
{ 
	if(n<1)
	{
		return;
	}
	// Replace root_element of heap with last element of heap.
    array1[0] = array1[n-1]; 
  	// Decreasing heap-size by 1 
    n = n - 1; 
	// min_heapify the root node 
    min_heapify(array1, 0, n);
}

/*** Function to Find k closest element from element x        ****/
void find_k_closest_element(int x_value, int *left_array, int l_size, int *right_array, int r_size, int k_val)
{
	for(int i=1; i<=k_val; i++)
	{
		int diff1, diff2;
		//Checking whether left_array has at least one element or not.
		if(l_size>0)
			diff1 = x_value - left_array[0];
		/*If there is no remaining element in left_array then start finding remaining closest
		  number to x from the right_array. so, keep diff1 MAX so, that We will only take element 
		  from right array.      */
		else 
			diff1 =INT_MAX;
		//Checking whether right_array has at least one element or not.
		if(r_size>0)
			diff2 = x_value - right_array[0];
		/*If there is no remaining element in right_array then start finding remaining closest
		  number to x from the left_array. so, keep diff2 MAX so, that We will only take element 
		  from left array.      */
		else 
			diff2 =INT_MAX;
		
		if(abs(diff1)<=abs(diff2))
		{
			cout<<left_array[0]<<" ";
			delete_max(left_array, l_size);
		}
		else
		{
			cout<<right_array[0]<<" ";
			delete_min(right_array, r_size);		
		}
	}
		
}
	

int main()
{
	cout<<"\tFinding k closest elements to x, where x Belongs to the array.\n";
	cout<<"**********************************************************************\n\n";
	int array_size, *arr;
	int x_value, k_value, temp, index =-1, indx_ofx_aftr_partition;
	cout<<"Enter the number of elements in array(size of array). \n";
	cin>>array_size;
	arr =new int[array_size];
	cout<<"Enter the numbers in array.After entering number at a index press \"Enter\" to enter at next Index. \n";
	for(int i =0; i<array_size; i++)
	{
		cin>>arr[i];
	}
	cout<<"Enter the key (x) to find k closest elements from that key.\n";
	cin>>x_value;

	//Finding index of key (x_value) in array.
	for(int j=0; j<array_size; j++)
	{
		if(x_value == arr[j])
			index =j;
		else if(index == -1 && (j == array_size-1))
		{
			cout<<"The Entered key is not present in array. So, can't find k closest elements to it. \n";
			return 0;
		}
	}
	
	cout<<"Enter value for k. \n";
	cin>>k_value;
	if(k_value >= array_size)
	{
		//If entered k_value is more than (array_size-1) then we can't find k closest elements to x.
		cout<<"As, Entered k_value is more than total no. of elements present in array except the key_value(x). ";
		cout<<"So, can't Find k closest elements to key_value(x). \n";
		return 0;
	}
	//swapping the position of key_value and last value in array.
	temp = arr[index];
	arr[index] =arr[array_size -1];
	arr[array_size -1] =temp;
	indx_ofx_aftr_partition =partition_around_x(arr, 0, array_size-1);
	  
	int size_of_left_array = indx_ofx_aftr_partition;
	int *left_array = new int[size_of_left_array];
	for(int j=0; j<indx_ofx_aftr_partition; j++)
		left_array[j] =arr[j];
	
	//keeping all elements right to x in an array.
	int size_of_right_array = array_size -(indx_ofx_aftr_partition +1);
	
	int *right_array = new int[size_of_right_array];
	for(int j=0; j<size_of_right_array; j++)
		right_array[j] =arr[j+indx_ofx_aftr_partition+1];
	
	//Now build max-heap for all elements left to x_value.
	build_max_heap(left_array, size_of_left_array);
	
	//Building min-heap for all elements right to x_value.
	build_min_heap(right_array, size_of_right_array);
	cout<<endl;
	//*****************************************************//
	
	/*** finding k closest element to x.   */
	cout<<"K closest element to x are:- \n";
	find_k_closest_element(x_value, left_array, size_of_left_array, right_array, size_of_right_array, k_value);
	
}
