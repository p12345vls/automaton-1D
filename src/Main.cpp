//============================================================================
// Author      : pavlos p
// Description : One-dimensional cellular automaton where two possible states
//               are possible (0 and 1) and the rule to determine the state of
//                 a cell in the next generation depends only on the current state
//                 of the cell and its two immediate neighbors.
//============================================================================

#include <iostream>
#include "Automaton.h"
using namespace std;

int main(){

   bool exit=false;
   char answer;
   int rule,width;

   do
   {
      cout << "Enter Rule (0 - 255) : ";
      cin >> rule;

      cout << "\nEnter displayWidth 1-121 : ";
      cin >> width;

      if (rule < 0 || rule > 255)
      {
         cout << "Not valid rule\n";
      }
      else if (width < 0 || width > 121)
      {
         cout << "Not valid width\n";
      }
      else
      {
         Automaton a(rule, width);
         a.propagateNewGeneration();

         cout << "continue? y / n :";
         cin >> answer;

         if (answer != 'y')
            exit = true;
      }
      if (exit)
      {
         cout << "\nEnd";
      }

   } while (!exit);

   return 0;
}
