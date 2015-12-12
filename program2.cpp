/*  
 *  Programmer: Kyle Kloberdanz
 *  Class     : CS2 Data Structure
 *
 *  This program will output the arithmetic expressions (converted to
 *  postfixStack notation) to the screen
 *
 *  This program has only been tested for expressions containing
 *  single digit integers and the opperators: -, +, /, *, ^, (, )
 */
#include <iostream>
#include <fstream>
#include <cmath>

// My implementation of the data structure 'stack'
//#include "stack.h"

// stack.h
//#ifndef STACK_H
//#define STACK_H 
namespace kyle{
    class stack{
        private:
            static const int CAPACITY = 50;
            int amount_in_stack;
            int arr[CAPACITY];
            int popped_item;

        public:
            // constructor
            stack();

            // returns the size of stack
            int size() { return amount_in_stack; }

            // returns total capacity of stack
            int capacity() { return CAPACITY; }

            // returns the top item of the stack WITHOUT deleting
            int top() { return arr[amount_in_stack - 1]; }

            // inserts new item n to the top of the stack
            void push(int n);

            // returns and deletes the top item
            int pop();

            // returns true if empty, false if not empty
            bool isEmpty();
    };
}
//#endif
// stack.cpp
#include <cassert>

namespace kyle{
    stack::stack(){
        amount_in_stack = 0;
        int i;
        for( i = 0; i < CAPACITY; i++){
            arr[i] = 0;
        }
    }

    void stack::push(int n){
        assert( size() < CAPACITY );
        arr[amount_in_stack] = n;
        amount_in_stack++;
    }

    int stack::pop(){
        popped_item = top();
        amount_in_stack--;
        return popped_item;
    }

    bool stack::isEmpty(){
        if (amount_in_stack == 0) { return true; }
        else{ return false; }
    }
}
using namespace std;

// kyle::stack
using namespace kyle;

/* prototypes */
// returns the In Stack Priority
int ISP(char);

// returns the Incoming Character Priority
int ICP(char);

// takes an expression in postfix notation and evaluates it
double evaluatePostfix(string);

// takes an expression in infix notation, and converts it to postfix
string convertPostfixtoPrefix(string);



// begin main
int main(){

    string line;

    cout << "Enter an expression" << endl;
    cin >> line;

    cout << "Infix notation: " << line << endl;

    string convertedLine;

    cout << "Postfix notation: ";
    convertedLine = convertPostfixtoPrefix(line);
    cout << convertedLine << endl;

    cout << "solution = " << evaluatePostfix(convertedLine) << endl;
    return 0;
}



// returns the In Stack Priority
int ISP(char c){
    if( c == '^' )                  { return 3; }
    if( (c == '*') || (c == '/') )  { return 2; }
    if( (c == '+') || (c == '-') )  { return 2; }
    if( c == '(' )                  { return 0; }
}

// returns the Incoming Character Priority
int ICP(char c){
    if( c == '^' )                  { return 4; }
    if( (c == '*') || (c == '/') )  { return 2; }
    if( (c == '+') || (c == '-') )  { return 1; }
    if( c == '(' )                  { return 4; }
}

double evaluatePostfix( string str ){
    int i;
    int symbol;
    double a;
    double b;
    double result = 0;
    stack s;

    for( i = 0; i < str.size(); i++ ){
        symbol = str[i];

        if( symbol != ' ' ){

            // if character is operand
            if( (symbol >= 48) && (symbol <= 57) ){
                s.push((char)symbol);
            }

            // if character is operator
            if( (symbol == '+') ||
                (symbol == '-') ||
                (symbol == '/') ||
                (symbol == '*') ||
                (symbol == '^')    ){
                
                // order of opperations: a opperator b
                b = s.pop();
                a = s.pop();
                
                // because a and b are the ascii representation of the numbers,
                // 48 must be subtracted to get the numerical value
                b = b - 48;
                a = a - 48;

                switch( symbol ){
                    case '+':
                        result = a + b;
                        break;
                    case '-':
                        result = a - b;
                        break;
                    case '/':
                        result = a / b;
                        break;
                    case '*':
                        result = a * b;
                        break;
                    case '^':
                        result = pow(a, b);
                        break;
                    default:
                        cout << "Problem occured within switch statement";
                        cout << "in function: evaluatePostfix" << endl;
                }

                // 48 must be added so that s will hold the ascii representation of the
                // numbers and opperators
                s.push(result + 48);

            } // end if( operator )
        } // end( if not space )
    } // end for( not end of string )
    return result;
} // end function: evaluatePostfix

string convertPostfixtoPrefix(string line){ 

    string postfixString;
    int i;
    stack postfixStack;
    char incomingSymbol;


    // Algorithm to convert to postfix
    for( i = 0; i < line.size(); i++ ){

        incomingSymbol = line[i];

        if( incomingSymbol != ' ' ){
            // case 1:
            // if operand, print it 
            if( ((int)incomingSymbol >= 48) && ((int)incomingSymbol <= 57) ){
                postfixString += incomingSymbol;
            } // end case 1:


            // case 2:
            // if ( or if stack is empty, push operator on stack
            else if( (incomingSymbol == '(') ){
                postfixStack.push( incomingSymbol );
            } // end case 2


            // case 3:
            else if( incomingSymbol == ')'){
              
                while( postfixStack.top() != 40 ){
                    postfixString += (char)postfixStack.top();
                    (char)postfixStack.pop();
                }
                // removes left paren
                postfixStack.pop();
            } // end case 3


            // case 4:
            else if( ISP(postfixStack.top()) >= ICP(incomingSymbol) ){
                while( ( ISP(postfixStack.top()) >= ICP(incomingSymbol)) 
                         || (not postfixStack.isEmpty()) ){

                    postfixString += (char)postfixStack.top();
                    (char)postfixStack.pop();
                    //incomingSymbol = line[i];
                }
                postfixStack.push(incomingSymbol);
            } // end case 4


            // case 5:
            // incomingSymbol has greater priority
            else if( not (ISP(postfixStack.top()) >= ICP(incomingSymbol) ) ){ 
                postfixStack.push(incomingSymbol);
            } // end case 5


            // default
            else {
                cout << "Default case encountered" << endl;
            }
        }
    } // end for
    while( not postfixStack.isEmpty() ){
        postfixString += (char)postfixStack.top();
        (char)postfixStack.pop();
    }

    return postfixString;

} // end function: convertPostfixtoPrefix
