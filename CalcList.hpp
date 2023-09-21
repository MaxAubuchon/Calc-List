#ifndef CALCLIST_H
#define CALCLIST_H

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "CalcListInterface.hpp"

class Node{ // used to create nodes for the calclist class

    private:
    int step; // show the amount of calculations done
    double oldTotal;
    std::string sign; // */+-
    double change;   // the amount changed by
    double newTotal; 
    Node* prev;
    Node* next;

    friend class CalcList;
};

class CalcList : public CalcListInterface {

  public:
  CalcList();
  bool empty() const; // function to see if empty 
  double total() const;
  void newOperation(const FUNCTIONS func, const double operand);
  void removeLastOperation();
  std::string toString(unsigned short precision) const;

  private:
  Node* header;
  Node* trailer;

  protected:
  void remove(Node* v);
};


#endif