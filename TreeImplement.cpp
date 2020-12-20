/* PROGRAM FUNCTION IMPLEMENTATION FILE */

//Including the required libraries and header files
#include <iostream>
#include <cstring>
#include "Tree.h"

//Including the required entities/identifiers
using std::cin;
using std::cout;
using std::endl;

/* Implementations of the member methods of Stack class */

//Constructor implementation
template <class datatype>
Stack<datatype>::Stack()
{
    size = 0;
    TOS = -1;
    stack_ptr = new datatype [size];
}

//Destructor implementation
template <class datatype>
Stack<datatype>::~Stack()
{      
    delete [] stack_ptr;
}

//Method to insert/push an element onto the flexible stack
template <class datatype>
void Stack<datatype>::push(datatype value)
{
    size++; 

    //Allocating another array with incremented size
    datatype* temp1 = new datatype [size];
    
    //Copying over all the elements to the new array
    for(int i=0; i<size-1; i++)
        temp1[i] = stack_ptr[i];
    
    
    datatype* temp2 = stack_ptr;
    
    //Deleting previous array
    delete [] temp2;
    
    //Shifting the pointer to the new array
    stack_ptr = temp1;
    
    //Pushing the value onto the new stack
    TOS++;
    stack_ptr[TOS] = value;
    
}

//Method to delete/pop the element from the stack
template <class datatype>
void Stack<datatype>::pop()
{    
    TOS--;
}

//Method to obtain the current TOS [Top of Stack] element 
template <class datatype>
datatype Stack<datatype>::top()
{
    return stack_ptr[TOS];
}

/* Function Implementations */

//Function to create a linked list node
node create_node(char value)
{
    node temp = new struct Node;
    temp->data = value;
    temp->left = temp->right = nullptr;
    
    return temp;
}

//Function to check if the character is an operand
bool check_operand(char value)
{
    if((value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z'))
        return true;
    else if(value >= '0' && value <= '9')
        return true;
    else 
        return false;
}

//Function to check if the character is an operator
bool check_operator(char value)
{
    if(value == '*' || value == '/' || value == '%' || value == '+' || value == '-' || value == '^')
        return true;
    else 
        return false;
}

//Function to check and return the precedance of the operator/character
int check_precedance(char value)
{
    if(value == '(')
        return 1;
    else if(value == '+' || value == '-')
        return 2;
    else if(value == '*' || value == '/' || value == '%')
        return 3;
    else if(value == '^')
        return 4;
    
    return 0;
}

//Function to convert the expression into the binary tree format
node convert_to_tree(char* expression)
{
    //Declaraing 2 stacks - stack_1 for the characters & stack_2 for the linked list nodes
    Stack<char> stack_1;
    Stack<node> stack_2;
    node temp1, temp2, temp3, temp4, temp5, temp6, temp7;
    
    //Pushing the '(' character as per the steps for conversion from infix to postfix notation
    stack_1.push('(');
    
    //Iterating through the characters of the expression
    for(unsigned i=0; i<strlen(expression); i++)
    {
        //If character is an operand push it onto stack_2
        if(check_operand(expression[i]))
        {
            temp1 = create_node(expression[i]);
            stack_2.push(temp1);
        }
        
        //If character is '(' push it onto stack_1
        else if(expression[i] == '(')
        {
            stack_1.push('(');
        }
        
        //If character is an operator, then
        else if(check_operator(expression[i]))
        {
            //If operator has a greater/equal precedance than the TOS, then push it onto stack_1
            if(check_precedance(expression[i]) >= check_precedance(stack_1.top()))
            {
                stack_1.push(expression[i]);
            }
            
            //If operator has a lesser precedance than the TOS, then,
            else if(check_precedance(expression[i]) < check_precedance(stack_1.top()))
            {
                //While precedance of TOS is greater, keep popping from stack_1 and pushing the popped element into stack_2
                while(check_precedance(expression[i]) < check_precedance(stack_1.top()))
                {
                    temp2 = create_node(stack_1.top());
                    stack_1.pop();
                    stack_2.push(temp2);
                    
                    //Linking the top 3 elements on stack_2 as the node, right child and left child respectively
                    temp6 = stack_2.top();
                    stack_2.pop();
                    temp3 = create_node(temp6->data);
                    temp3->right = stack_2.top();
                    stack_2.pop();
                    temp3->left = stack_2.top();
                    stack_2.pop();
                    
                    stack_2.push(temp3);
                }
                
                //When the precedance TOS is lesser/equal, push the operator onto stack_1 
                stack_1.push(expression[i]);
            }
        }
        
        //If character is ')', then
        else if(expression[i] == ')')
        {
            //While TOS is not '(', keep popping from stack_1 and pushing the popped element into stack_2
            while(stack_1.top() != '(')
            {
                temp4 = create_node(stack_1.top());
                stack_1.pop();
                stack_2.push(temp4);
                
                //Linking the top 3 elements on stack_2 as the node, right child and left child respectively
                temp7 = stack_2.top();
                temp5 = create_node(temp7->data);
                stack_2.pop();
                temp5->right = stack_2.top();
                stack_2.pop();
                temp5->left = stack_2.top();
                stack_2.pop();
                
                stack_2.push(temp5);
            }
            
            //When the TOS is ')', pop it from stack_1
            stack_1.pop();
        }
    }
    
    //Returning the root node of the binary tree
    return stack_2.top();
}

//Function for preorder traversal of the expression tree
void preorder(node root) 
{
    if(root != nullptr)
    {
        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}

//Function for inorder traversal of the expression tree
void inorder(node root)
{
    if(root != nullptr)
    {
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
}

//Function for postorder traversal of the expression tree
void postorder(node root) 
{
    if(root != nullptr)
    {
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<" ";
    }
}

//Function for obtaining the input arithmetic expression
char* obtaining_expression()
{
    const unsigned size = 200;

    //Ensuring that new line character is ignored from cin buffer for subsequent calls
    static int count = 0;
    if(count == 0)
        goto  skip;
    else
        cin.ignore(size,'\n');
    skip:
    count++;
    
    cout<<"Enter your arithmetic expression in the infix notation: ";
    
    char* temp_expression = new char [size];
    
    //Taking input until '\n' or next line
    cin.getline(temp_expression, size);
    
    //Allocating another array of the appropriate size
    char* expression = new char [strlen(temp_expression)+1];
    unsigned i=0;
    
    //Copying over all the elements to the new array
    while (i != strlen(temp_expression))
    {
        expression[i] = temp_expression[i];
        i++;
    }
    
    //Deleting the previous array
    delete [] temp_expression;
   
    //Adding the ')' character as per the steps for conversion from infix to postfix notation
    expression[i] = ')';
    i++;
    
    //Adding the terminating null character
    expression[i] = '\0';
    
    return expression;
}

//Function to display the different notations of the input expression
void display_notations(node root)
{
    //Displaying the menu
    cout<<"Enter your choice:"<<endl<<"1. Display the prefix notation"<<endl<<"2. Display the infix notation"<<endl<<"3. Display the postfix notation"<<endl;
    cout<<"4. Quit"<<endl;
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    
    int choice;
    
    //Performing operations based on the user's choice
    do
    {
        again:
        cout<<"Choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            cout<<"Prefix notation: ";
            preorder(root);
            cout<<endl;
            break;
            case 2:
            cout<<"Infix notation: ";
            inorder(root);
            cout<<endl;
            break;
            case 3:
            cout<<"Postfix notation: ";
            postorder(root);
            cout<<endl;
            break;
            case 4:
            break;
            default:
            cout<<"Incorrect choice. Please enter again."<<endl;
            goto again;
        }
    } while(choice != 4);
    
}
