/* Assignment
 * COC2910 - Data Structure and OOP Lab
 * Mohammad Umar Asif
 * A2CO - 43
 * 18COB176 
 * GK-7690
 */
 
/* This is a C++ program to obtain the postfix/infix notation of the arithmetic expression 
 * that is entered in the infix notation using the binary tree data structure.
 */

/* MAIN PROGRAM FILE */

//Including the required libraries and header files
#include <iostream>
#include "Tree.h"

//Including the required entities/identifiers
using std::cin;
using std::cout;
using std::endl;

int main()
{
    //Displaying welcome message
    cout<<"Welcome! This is a C++ program to obtain the postfix/infix notation of the arithmetic expression"<<endl;
    cout<<"entered in the infix notation using the binary tree data structure."<<endl;
    cout<<"================================================================================================"<<endl;
    
    again1:
    
    //Obtaining the input arithmetic expression
    char* infix_notation = nullptr;
    infix_notation = obtaining_expression();
    
    //Converting the expression into the binary tree format
    node root = nullptr;
    root = convert_to_tree(infix_notation);
    
    //Displaying the notations based on user's choice
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    display_notations(root);
    
    //Asking the user if they would like to enter another expression
    int option;
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Would you like to enter another expression? (1. Yes / 2. No): ";
    again2:
    
    cin>>option;

    switch(option)
    {
        case 1:
	cout<<"------------------------------------------------------------------------------------------------"<<endl;
        goto again1;
        break;
        case 2:
        break;
        default:
        cout<<"Incorrect choice. Please enter again: ";
        goto again2;
    }
    
    cout<<"================================================================================================"<<endl;
    cout<<"Thank you."<<endl;
    cout<<"Created by Mohammad Umar Asif"<<endl;
    return 0;
} 

