// header files
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#include "expression.h"
#include "subexpression.h"
#include "symboltable.h"
#include "parse.h"

//The function prototype
void parseAssignments(stringstream& in);

SymbolTable symbolTable;
//main method
int main()
{
   // declare the variables
   Expression* expression;
   char paren, comma;
   string line;
   // create an input file stream
   ifstream fin("input.txt");
   // check, if the file is not opened
   //then display a error message
   if (!fin.is_open())
       perror("error while opening file");
   //use a loop, to read the content from the file
   while (getline(fin, line))
   {
       symbolTable.init();
       if (!fin)
           break;
       stringstream in(line, ios_base::in);
       in >> paren;
       cout << line << " ";
       expression = SubExpression::parse(in);
       in >> comma;
       //call the function
       parseAssignments(in);
       //Display the result
       double result = expression->evaluate();
       cout << "Value = " << result << endl;
   }
   system("pause");
   return 0;
}

//function definition
void parseAssignments(stringstream& in)
{
   //declare the variables
   char assignop, delimiter;
   string variable;
   double value;
   do
   {
       variable = parseName(in);
       in >> ws >> assignop >> value >> delimiter;
       symbolTable.insert(variable, value);
   } while (delimiter == ',');
}

