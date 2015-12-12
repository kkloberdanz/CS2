#include <iostream>

using namespace std;

// prototypes
class node{
    private:
        float coefficient;
        float exponent;
        node* next;
    public:
        // Constructors
        node();
        node(float c, float e, node* ptr);

        // void member functions
        void makeList();/* creates a list, starting with the input pointer to node
                           expects a list of form ax^n + bx^n-1 + cx^n-2 + ... + 0 */
                              
        void printList(); // prints list, starting with the input pointer to node
        
        // returns linked list of type node*
        // first parameter is the list that will contain the solution
        node* add(node*, node*, node*);
};

// implementation
node::node(){
    coefficient = 0;
    exponent = 0;
    next = NULL;
}

node::node(float c, float e, node* ptr){
    coefficient = c;
    exponent = e;
    next = ptr;
}

void node::makeList(){

    float input_exponent;
    float input_coefficient;

    node* currentNode; // pointer to node
    currentNode = this;

    while( true ){
        cout << "Enter a coefficient, followed by an exponent:" << endl;
        cout << "(a coefficient of 0 will exit)" << endl;

        cin >> input_coefficient;

        if( input_coefficient != 0 ){
            cin >> input_exponent;

            // sets values of coefficient and exponent to the input values
            currentNode->coefficient = input_coefficient; 
            currentNode->exponent = input_exponent;

            // creates assigns the pointer "next" to the memory location of
            // a newly created node
            currentNode->next = new node;

            // advances the current node to next node
            currentNode = currentNode->next;

            // assigns the pointer "next" for the newly created node to NULL
            currentNode->next = NULL;
        }else{
            // break from while
            break;
        }
    }
}

void node::printList(){
    node* currentNode = this;

    // the if/else statements within the while ensure proper formating, i.e., 
    // the x and the + signs appear as they would in an equation
    while( currentNode->next != NULL ){
        if( currentNode->exponent != 0 ){
            cout << currentNode->coefficient << "x^" << currentNode->exponent;
        } else {
            cout << currentNode->coefficient;
        }
        currentNode = currentNode->next;
        if( currentNode->next != NULL ){
            cout << " + ";
        }
    }
    cout << endl;
}

node* node::add(node* solution, node* a, node* b){

    while( (a != NULL) || (b != NULL) ) { 
        
        // case 1:
        if( a->exponent == b->exponent ){
            // add the coefficients and set the exponent
            solution->coefficient = a->coefficient + b->coefficient;
            solution->exponent = a->exponent;

            // move to the next node
            a = a->next;
            b = b->next;
        }

        // case 2:
        else if( a->exponent > b->exponent ){
            solution->coefficient = a->coefficient;
            solution->exponent = a->exponent;
            a = a->next;
        }

        // case 3:
        else if( b->exponent > a->exponent ){
            solution->coefficient = b->coefficient;
            solution->exponent = b->exponent;
            b = b->next;
        }

        solution->next = new node;
        solution = solution->next;
        solution->next = NULL;
    } 
    return solution;
}

// main
int main(){

    node* q = new node;
    node* p = new node;
    node* s = new node;

    q->makeList();
    cout << "\nq = ";
    q->printList();

    p->makeList();
    cout << "\np = ";
    p->printList();

    s->add(s, q, p);
    cout << "\ns = ";
    s->printList();

    delete q;
    delete p;
    delete s;
    
    return 0;
}
