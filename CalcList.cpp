/*
Driver: Dawson Murphy
Navigator: Max Aubuchon

This program creates a list that is used as a calculator that can do 
addition, subtraction, multiplication, division, as well as undo the last operation.
*/

#include "CalcList.hpp"

CalcList::CalcList() { // constructor 
    header = new Node;
    trailer = new Node; 
    header->next = trailer;
    trailer->prev = header;
    header->newTotal = 0;
    header->step = 0;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand){        //creates new operations for the list
        
    Node*u = new Node; u->oldTotal = trailer->prev->newTotal;// creates the new node
    u->next = trailer;
    u->prev = trailer->prev;
    trailer->prev->next = u;
    trailer->prev = u;
    u->step = u->prev->step+1; 
    u->change = operand;

    if (func == DIVISION){
        if (operand == 0){
            throw "Attempted to divide by 0 /n"; // doesnt allow divide by 0
        }
        else{
            u->newTotal = u->oldTotal / operand;
            u->sign = '/';
        }
    }
    if (func == ADDITION){
        u ->newTotal = u ->oldTotal + operand;
        u-> sign = '+';
    }
    if (func == SUBTRACTION){
        u ->newTotal = u ->oldTotal - operand;
        u-> sign = '-';
    }
    if (func == MULTIPLICATION){
        u ->newTotal = u ->oldTotal * operand;
        u-> sign = '*';
    }
}

bool CalcList::empty() const {         // checks if list is empty
    return (header->next == trailer);
}

double CalcList::total() const{         //returns the final total of the list
    return trailer->prev->newTotal;
}

void CalcList::remove(Node* v){     
    Node* u = v->prev; // predecessor
    Node* w = v->next; // successor
    u->next = w; // unlink v from list
    w->prev = u;
    delete v;
}

void CalcList::removeLastOperation(){       //removes the last operation from the list
    if(trailer->prev->step == 0){
        throw "Attempted to remove from empty set.\n";
    }
    remove(trailer->prev);
}

std::string CalcList::toString(unsigned short precision) const{     //creates the string output for the list
    std::stringstream strS;     //creates a string object
    Node* p = trailer->prev;

    while( p->step > 0){
        strS << std::fixed << std::setprecision(precision)<< p->step<< ": " << p->oldTotal << p->sign << p->change << '=' << p->newTotal << '\n';
        p = p->prev;
    }
    return strS.str();      //returns the string object
}

