/* PROGRAM FUNCTION HEADER FILE */

//Using include guard
#ifndef TREE_H
#define TREE_H

//Utilizing a template for Stack class
template <class datatype>

//Creating the stack with the required data members and member methods
class Stack
{
private:
    int size;
    int TOS;
    datatype* stack_ptr;
public:
    Stack();
    
    void push(datatype value);
    void pop();
    datatype top();
    
    ~Stack();
};

//Creating a linked list node
struct Node
{
    char data;
    struct Node* left;
    struct Node* right;
};

//Defining struct Node* as node
typedef struct Node* node;

//Function prototypes
node create_node(char value);
bool check_operand(char value);
bool check_operator(char value);
int check_precedance(char value);
node convert_to_tree(char* expression);
void preorder(node root);
void inorder(node root);
void postorder(node root); 
char* obtaining_expression();
void display_notations(node root);

#endif

