
#include <iostream>
#include <sstream>
using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "operand.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "or.h"
#include "and.h"
#include "equality.h"
#include "greaterThan.h"
#include "lessThan.h"
#include "ternary.h"
#include "negation.h"

SubExpression::SubExpression(Expression* left, Expression* right)
{
    this->left = left;
    this->right = right;
}

Expression* SubExpression::parse(stringstream& in)
{
    Expression* left;
    Expression* right;
   Expression* condition;
    char operation, paren;


    left = Operand::parse(in);


    in >> operation;

   if(operation == '!') {
       in >> paren;
       return new Negation(left,NULL);

   } else if(operation == ':') {
       right = Operand::parse(in);
       in >> paren;
       condition = Operand::parse(in);
       in >> paren;
       return new Ternary(left,right,condition);

   } else {


       right = Operand::parse(in);
       in >> paren;

       switch (operation)
       {
           case '+': return new Plus(left, right);
           case '-': return new Minus(left, right);
           case '*': return new Times(left, right);
           case '/': return new Divide(left, right);
           case '|': return new Or(left, right);
           case '&': return new And(left, right);
           case '=': return new Equality(left, right);
           case '>': return new GreaterThan(left, right);
           case '<': return new LessThan(left, right);
       }
   }
   return 0;
}
