
/*********************         poly.cpp                    ******************************/
/*                                                                                      */
/* Description:-                                                                        */
/* This cpp program will generate a polynomial with given (coefficient and exponent)    */
/* pair after that we can perform multiplication with a constant and get new polynomial */
/* and we can add/subtract two different polynomials, also we can find the value of      */
/* polynomial at certain x value.                                                        */
/* for creation of polynomial the programme is overloading '+=' or '-=' operator.        */
/* for addition OR subtraction of two polynomials, overloaded '+' or '-' operator.       */
/* for multiplication with a constant overloaded '*=' operator.                          */
/*                                                                                       */
/*		                                                                                 */
/* Compiled and executed in Dev-C++ 5.11                                                 */
/*                                                                                       */
/* Programmer:- Stuti Priyambda                                                          */
/* Roll No:- 204101055                                                                   */
/*****************************************************************************************/

#include<iostream>
#include<iterator>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

/* Poly is a class having two private data members coeff, representing coefficient
   of the polynomial term and expon representing degree/exponent of the polynomial
   term and some public member functions to perform operations on polynomial. */

class Poly
{

    float coeff;     //coefficient of a term in polynomial.
    int expon;      //exponent of a term in polynomial.
    //vector storing (coefficient and exponent) pairs for each terms in polynomial.
    vector <pair<float, int> > coeff_expon;
    public:
    Poly(float coeff =0, int expon =0) //constructor
    {
        this->coeff =coeff;
        this->expon =expon;
    }
    ~Poly()      //Destructor
    {
	}
    void operator +=(Poly p); //declaration of overloading "+=" operator.
    void operator -=(Poly p); //declaration of overloading "-=" operator.
    Poly operator +(Poly p);  //declaration of overloading  "+"  operator.
    Poly operator -(Poly p);  //declaration of overloading  "-"  operator.
    void operator *=(float num); //declaration of overloading "*=" operator.

    //member-function declaration:-
    int createPolynomial();      //to create polynomial.
    void multiplyByConst();     //to multiply a polynomial with a constant.
    void addSubtractPolynomial(); //to add/subtract the existing polynomial with a new polynomial.
    void display();               //to display the polynomial.
    void findValueAtx();          //to find value of the polynomial at certain x
    double power(float x, int pow);  //this function helps in calculating value of polynomial by finding power of exponent.

    /* sortCoeffExponVector()  function is to sort the "coeff_expon" vector in
      decreasing order of exponent, also if more than one terms entered by the user,
      have same exponent then add their coefficient and make a single term.*/
    void sortCoeffExponVector(vector<pair<float, int> > &coeff_expon);

};

/*******   Overloading of "+=" operator.          */
/* This is being called if we are adding a term with + ve coefficient ie.. 2x^3. {c += Poly(2,3)}*/
void Poly::operator +=(Poly p)
{
	this->coeff_expon.push_back(make_pair(p.coeff, p.expon)); //pushing the (coefficient , exponent) pair in vector.
}

/*******     Overloading of "-=" operator.         */
/* This is being called if we are adding a term with - ve coefficient i.e.. -2x^3. {c -= Poly(2,3)}*/
void Poly::operator -=(Poly p)
{

    this->coeff_expon.push_back(make_pair(p.coeff, p.expon));  //pushing the (coefficient , exponent) pair in vector.
}

/*******   Overloading of "+" operator.          */
/* This is being called if we want to add two polynomials. ie.. c3= c1+c2 */
Poly Poly::operator +(Poly p)
{
    Poly temp;              //created an object of Poly class to store the resultant polynomial which we get after addition of two polynomials.
    int i =0,j =0,k=0;      //i,j k are variables to iterate through ist, 2nd , resultant polynomials respectively.
    int vec1_size =this->coeff_expon.size();     // to get the number of terms in Ist polynomial.
    int vec2_size =p.coeff_expon.size();        // to get the number of terms in 2nd polynomial.

    /* Iterate through while loop till we have terms in
       both polynomials. starting with the first terms in
       both Polynomials compare the exponent of the terms .*/
    while(i<vec1_size && j<vec2_size)
    {
        //If exponents are equal so, just add their coefficient
        // to make a single term and push the (coefficient,
        // exponent) pair in the vector of newly created temp object of
        // Poly class to get the third polynomial.

        if(this->coeff_expon[i].second ==p.coeff_expon[j].second)
        {
            int temp_exp; float temp_coeff;         //local variables to hold exponent, coefficient respectively.
            temp_coeff= this->coeff_expon[i].first + p.coeff_expon[j].first;    //adding the coefficients with same exponent in ist, 2nd polynomial.
            temp_exp = this->coeff_expon[i].second;  
            if(temp_coeff!= 0)          //after adding coefficients with SAME exponent in both polynomials, if we get non-zero coefficient then only push into vector.
            	temp.coeff_expon.push_back(make_pair(temp_coeff, temp_exp));
            i++; j++; k++;

        }
        /* If exponent of jth term in 2nd polynomial is greater than exponent
           of ith term in ist polynomial then push the 2nd polynomial term in vector
		   e.g :- Ist polynomial (-2x^3 +1x^2) , 2nd Polynomial is (9x^7 +5) since 7>3
		   so, push (9,7).    */
        else if(this->coeff_expon[i].second <p.coeff_expon[j].second)
        {
            temp.coeff_expon.push_back(make_pair(p.coeff_expon[j].first, p.coeff_expon[j].second));
            j++;k++;

        }
        /* If exponent of ith term in first polynomial is greater than exponent
           of jth term in 2nd polynomial then push first polynomial term in vector*/
        else
        {
            temp.coeff_expon.push_back(make_pair(this->coeff_expon[i].first, this->coeff_expon[i].second));
            i++;k++;
        }
    }// end of while-loop

    /* If number of terms in Ist polynomial is remaining but not in 2nd polynomial
       then push all the terms of Ist polynomial in vector of resultant polynomial*/
	while(i<vec1_size)
    {
        temp.coeff_expon.push_back(make_pair(this->coeff_expon[i].first, this->coeff_expon[i].second ));
        i++;k++;
    }
    /* If number of terms in 2nd polynomial is remaining but not in ist polynomial
       then push all the terms of 2nd polynomial in vector of resultant polynomial.*/
    while(j<vec2_size)
    {
        temp.coeff_expon.push_back(make_pair(p.coeff_expon[j].first, p.coeff_expon[j].second));
        j++;k++;
    }
    return temp;
}

/***   Overloading definition of "-" operator.  ***/
/* This is being called if we want to subtract two polynomials. ie.. c3= c1-c2 */
Poly Poly::operator -(Poly p)
{

    Poly temp;  //created an object of Poly class to store the resultant polynomial which we get after addition of two polynomials.
    int i =0,j =0,k=0;  //i,j k are variables to iterate through ist, 2nd , resultant polynomials respectively.
    int vec1_size =this->coeff_expon.size(); // to get the number of terms in Ist polynomial.
    int vec2_size =p.coeff_expon.size(); // to get the number of terms in 2nd polynomial.

    /* Iterate through while loop till we have terms in
       both polynomials. starting with the first terms in
       both Polynomials compare the exponent of the terms .*/

    while(i<vec1_size && j<vec2_size)
    {
        //If exponents are equal so, just subtract their coefficient
        // to make a single term and push the (coefficient,
        // exponent) pair in the vector of newly created temp object of
        // Poly class to get the third polynomial.

        if(this->coeff_expon[i].second ==p.coeff_expon[j].second)
        {
            int temp_exp; float temp_coeff;               //local variables to hold exponent, coefficient respectively.
            temp_coeff= this->coeff_expon[i].first - p.coeff_expon[j].first;       //subtracting the coefficients with same exponent in ist, 2nd polynomial.
            temp_exp = this->coeff_expon[i].second;
            if(temp_coeff!= 0)           //after subtracting coefficients of same exponent in both polynomials, if we get non-zero coefficients then only push into vector.
            	temp.coeff_expon.push_back(make_pair(temp_coeff, temp_exp));
            i++; j++; k++;

        }
        /*if exponent of jth term in 2nd polynomial is greater than exponent of ith term in ist polynomial
          then first change the sign of jth term of 2nd polynomial and then push into the vector.
		   e.g:- ist_polynomial is (2x^5 +3x^4) - 2nd polynomial is (-6x^7+2x^1) so, we will have to 
		   push (6, 7) not (-6,7).  */
         else if(this->coeff_expon[i].second <p.coeff_expon[j].second)
        {
            int tCoeff =p.coeff_expon[j].first;      //local variable to hold coefficient of jth term in 2nd polynomial.
            temp.coeff_expon.push_back(make_pair(-tCoeff, p.coeff_expon[j].second));
            j++;k++;

        }
        /*if exponent of ith term in ist polynomial is greater than exponent of jth term in 2nd polynomial
          then push ith term of ist polynomial into the vector.  */
        else
        {
            temp.coeff_expon.push_back(make_pair(this->coeff_expon[i].first, this->coeff_expon[i].second));
            i++;k++;
        }
    }// end of while-loop

    /* If number of terms in Ist polynomial is remaining but not in 2nd polynomial then just add 
	   all terms of Ist Polynomial in vector of resultant Polynomial.*/
	while(i<vec1_size)
    {
        temp.coeff_expon.push_back(make_pair(this->coeff_expon[i].first, this->coeff_expon[i].second ));
        i++;k++;
    }
    /* If number of terms in 2nd polynomial is remaining but not in ist polynomial then just add 
	   all terms of 2nd Polynomial in vector of resultant Polynomial.*/
    while(j<vec2_size)
    {
        int tCoeff =p.coeff_expon[j].first;
        temp.coeff_expon.push_back(make_pair(-tCoeff, p.coeff_expon[j].second));
        j++;k++;
    }
    return temp;
}

/***   Overloading of "*=" operator.    ****/
void Poly::operator *=(float num)
{
    vector<pair<float, int> > ::iterator itr;
    if(coeff_expon.size() ==0)
        cout<<"Either polynomial is 0 OR No Polynomial given,to multiply with. First enter the Polynomial. \n";
    else
    {
        for(itr =coeff_expon.begin(); itr < coeff_expon.end(); itr++)
        {
            itr->first = (itr->first)* num;

        }
    }

}

/*createPolynomial() function is to create a new polynomial, return 0 if failed
	e.g:- 1)if no. of terms entered is not positive number
	      2)if exponent of any term entered is -ve
		  3)if all the terms entered with 0 coefficient.
otherwise return 1. */
int Poly::createPolynomial()
{
    int noOfTerms;
    bool polyFlag =0; //This polyFlag variable will be 1 if there is at least one term in polynomial with non-zero coefficient.
    cout<<"\nPlease, Enter the no.of terms in polynomial. \n";
    cin>>noOfTerms;
    if(noOfTerms >0)
    {
        float coeff; int expon;
        while(noOfTerms--)
        {
            cout<<"Enter the coefficient.\n";
            cin>>coeff;
            cout<<"Enter the exponent.\n";
            cin>>expon;
            if(expon>=0)
            {
                if(coeff >0)
                {
                    *this+= Poly(coeff, expon);    //if coefficient is +ve overload += operator.
                    polyFlag =1;
                }
                else if(coeff <0)
                {
                    *this-= Poly(coeff, expon);     //if coefficient is -ve overload -= operator.
                    polyFlag =1;
                }
            }
            else
            {
                cout<<"Exponent can't be -ve, in polynomial.\n";
                if(this->coeff_expon.size()>0)
                {
                	cout<<"created polynomial is\n";
					this->display();
					cout<<"\n";
					return 1;
				}
                return 0;

            }

        }
    }
    else
    {
        cout<<"Number of Terms must be positive\n";
        return 0;
    }
    if(polyFlag ==0)
    {
        cout<<"The Polynomial is:- \n0\n";
        return 1;
    }
    cout<<"The polynomial you created is:-\n";
    this->display();
    cout<<"\n\n";
    return 1;
}

//create new Polynomial and add/subtract to the existing one and  generate new Polynomial.
void Poly::addSubtractPolynomial()
{
    Poly c2, c3; //created two objects of Poly class c2 is the new polynomial and c3 is the result of addition/subtraction of both polynomial.
    if(this->coeff_expon.size()==0)   //vector size of polynomial is 0. i.e.. polynomial doesn't exist.
    {
        cout<<"\nEither there is no existing polynomial OR existing polynomial is 0.Let's create the new polynomial.";
        c2.createPolynomial();
        *this =c2;
    }
    else
    {
        cout<<"\ncreate the 2nd polynomial(or terms) to add/subtract. \n";
        if(c2.createPolynomial())
        {
            bool oprFlag= 0;
            cout<<"Do you want to add this polynomial or subtract.\n";
            cout<<"For addition press 1,subtraction press 0\n";
            cin>>oprFlag;
            if(oprFlag)
                c3 = *this + c2; // Overloading of '+' Operator.
            else
                c3 = *this -c2; // Overloading of '-' Operator.
            cout<<"The new polynomial after addition/subtraction of 2nd polynomial(terms) is:-\n";
            if(c3.coeff_expon.size()!=0)
            	c3.display();
            else
            	cout<<0<<"\n";
            cout<<"\n";
            *this =c3;
        }
    }
    return;
}
//Multiply the polynomial by a constant.
void Poly::multiplyByConst()
{
    float constValue;
    cout<<"\n\nPlease, Enter the Constant to multiply with polynomial.\n";
    cin>>constValue;
    if (constValue ==0)
    {
		cout<<"The Polynomial becomes 0.\n";
		this->coeff_expon.clear();           //since multiplication with 0 makes polynomial 0. so, erase coeff_expon vector.
		return;
	}
    *this *=constValue;  //using overloading of '*=' operator.
    if(this->coeff_expon.size() !=0)
    {
    	cout<<"\nThe new Polynomial is -:\n";
    	this->display();
    }
    cout<<"\n";

}

/* sortCoeffExponVector() function is to sort the "coeff_expon" vector in
    decreasing order of exponent, also if more than one terms have
    same exponent then add their coefficient and make a single term.
	e.g:- If user entered polynomial as  2x^3 + 3x^5 -6x^1 +4x^5   This function
	will change it as 7x^5 +2x^3 -6x^1 .*/

void Poly::sortCoeffExponVector(vector<pair<float, int> > &coeff_expon)
{
        int exp, i, j, noOfTerms, vecSize;
        vector <pair<float, int> > tempVec;
        float coeff;
        noOfTerms =coeff_expon.size();
        //Insertion sort logic
        for(j = 1; j<noOfTerms; j++)
        {
            exp= coeff_expon[j].second; //take exponent
            coeff =coeff_expon[j].first; //take coefficient
            i=j-1;
            while(i >= 0 && coeff_expon[i].second<exp)
            {
                coeff_expon[i+1].second = coeff_expon[i].second;
                coeff_expon[i+1].first = coeff_expon[i].first;
                i--;
            }

            coeff_expon[i+1].second = exp;   //inserting the coefficient and exponent in right place
            coeff_expon[i+1].first =coeff;
        }
        // add coefficient of SAME exponents and push (coefficients, exponent) in the local vector tempVec.
        i =0, j=0;
        vecSize =coeff_expon.size();
        while(i<vecSize)
        {
            int counts =0;
            float sum = coeff_expon[i].first;
            for(j =i+1; j<vecSize; j++)
            {
                if(coeff_expon[i].second !=coeff_expon[j].second)
                    break;
                else
                {
                    sum += coeff_expon[j].first;
                    counts++;
                }
            }

            i++;
            tempVec.push_back(make_pair(sum, coeff_expon[j-1].second));
            if(counts)
                i=i+counts;
        }// End of While -loop.

        coeff_expon.clear();    //clear the instance member vector "coeff_expon".
        vector <pair<float, int> >::iterator itr;
        for(itr =tempVec.begin(); itr < tempVec.end(); itr++)  //iterate through vector "tempVec".
        {
            coeff_expon.push_back(make_pair(itr->first, itr->second)); // push all the (coefficient, exponent) pair from tempVec  to "coeff_expon" vector.
        }

}
//Display the  Polynomial.
void Poly::display()
{
    //Sort the vector by decreasing order of exponent and also add the coefficients with the same exponent.
    this->sortCoeffExponVector(this->coeff_expon);
    vector <pair<float, int> >::iterator ptr;
    for(ptr = this->coeff_expon.begin(); ptr < this->coeff_expon.end(); ptr++)
    {
        if(ptr> this->coeff_expon.begin() && ptr< this->coeff_expon.end() && ptr->first >=0)
            cout<<"+";
        cout<<ptr->first;
        if(ptr->second !=0)
            cout<<"x^"<< ptr->second<<" ";

    }

}
// to calculate power of exponent
double Poly::power(float x, int pow)
{
    if(pow ==0)
        return 1;
    double res =power(x, pow/2);
    if(pow %2 ==0)
        return res *res;
    else
        return x*res*res;

}
//to find Polynomial value at certain x.
void Poly::findValueAtx()
{
    if(this->coeff_expon.size() ==0)
        cout<<"\nEither Polynomial is 0 or there is no polynomial , first enter the polynomial to evaluate.\n";
    else
    {
        float x; double valueAtx =0.0;
        cout<<"\n\nPlease, Enter the value of x.\n";
        cin>>x;
        vector <pair<float, int> >::iterator itr;
        for(itr =this->coeff_expon.begin(); itr <this->coeff_expon.end(); itr++)
        {
            valueAtx += (itr->first)*(this->power(x, itr->second));
        }
        cout<<"Polynomial value at x="<<x<<" is "<<valueAtx<<"\n";
    }
    cout<<"\n";
}
menu()
{
    Poly c;
    system("cls");
    while(1)
    {
        cout<<"*-------------------------------------------------------------------------------*\n";
        cout<<"\t\tEnter your choices :-\n\n";
        cout<<"press 1, to create a new polynomial (overloading '+=', '-=').\n";
        cout<<"press 2, to find polynomial value at certain x.\n";
        cout<<"press 3, if you have to add or subtract another polynomial(terms) to the existing polynomial and generate a new polynomial(overloading '+', '-') \n";
        cout<<"press 4, to multiply a polynomial by  a constant (overloading '*='') \n";
        cout<<"press 5, to exit";
        cout<<"\n*------------------------------------------------------------------------------*\n";
        switch(getch())
        {

            case '1':
            {
                Poly c1;
                c1.createPolynomial();
                c=c1;
            }
            break;
            case '2':
                c.findValueAtx();
            break;
            case '3': c.addSubtractPolynomial();
            break;
            case '4': c.multiplyByConst();
            break;
            case '5': exit(0);
            break;

            default:
                system("cls");
                cout<<"\nEnter 1 to 5 only";
                cout<<"\n Enter any key\n";
                getch();
        }
}
}

int main()
{

    menu();

}


