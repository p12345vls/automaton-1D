/*
 * Automaton.h
 *
 *  Created on: Jul 15, 2017
 *  Author: pavlos p
 */

#ifndef AUTOMATON_H_
#define AUTOMATON_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;


class Automaton{
public:
   const static int BYTE = 8;
   const static int MAX_DISPLAY_WIDTH = 121;

   /*constructors*/
   Automaton();
   ~Automaton();
   Automaton(int new_rule, int displayWidth);

   /*
    * converts the integer newRule a number from 0-255, to an array of eight booleans.
    *
    * @par new_rule the rule.
    * @return true if rule is a number from 0-255.
    */
   bool setRule(int new_rule);

   /*sets the width of the display
    *
    * @par width the width
    * @return true if  0 < width < MAX_DISPLAY_WIDTH
    */
   bool setDisplayWidth(int width);

   /*
    * @par cellSets[] the set of cells in a form of pair values, example (111:*)
    * @return the current gen, "*" or " " , depending on the rule
    */
   string toStringCurrentGen(string cellSets[]);

   /*starts with the default gen, a single "*" and
    *creates new generations depending on the rule by calling applyRule()
    *and toStringCurrentGen()
    */
   void propagateNewGeneration();

   /* sets the first default gen according to the display width
    *
    * @par displayWidth the display width
    */
   void setSeed(int displayWidth);

   /*
    * creates pair values according to the rule,
    *  for example (011:*, 111:' ', 100:*,...)
    */
   void createRuleSets(bool rules[], string ruleCells[]);

   /* applies the rules by creating the cell sets of a binary number
    *
    * @par rules[] the rules
    * @par cellSets the cell sets
    */
   void applyRule(bool rules[], string cellsSets[]);

   /* converts boolean value to string
    *
    * @par b the boolean value
    * @return "1" if true, "0" otherwise
    */
   string boolString(bool b) { return b ? "1" : "0";};

   /* converts char digit value to boolean
    *
    * @par digit the char value
    * @return 1 if true, 0 otherwise
    */
   bool stringBool(char digit) { return digit=='*'? 1 : 0; };

   /* getter for the new rule
    *
    * @return the new rule
    */
   int getRule() { return this->newRule; };

   /* getter for the display Width
    *
    * @return the display Width
    */
   int getDisplayWidth(){ return this->displayWidth; };

private:
   /*array for the binary digits*/
   bool *rules;

   /*array for the pair values(111:'',101:*,...)*/
   string *ruleSet;

   /*array for cell sets (111,001,101...)*/
   string *cellSets;

   /*array for storing the new gen every time a new generation accurs*/
   bool *arrayGen;

   /*the gen*/
   string thisGen;

   // bit, ("*" or " ")
   string extremeBit;

    /* the display width*/
   int displayWidth;

   /*the new rule */
   int newRule;

   /*
    * helper method to check the bounds of the new rule
    *
    * @par new_rule the new rule
    * @return true if (0 <= rule <=255)
    */
   bool checkBounds(int new_rule);
};
#endif /* AUTOMATON_H_ */
