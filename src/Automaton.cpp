/*
 * Automaton.cpp
 *
 *  Created on: Jul 15, 2017
 *  Author: pavlos p
 */
#include "Automaton.h"

Automaton::Automaton(int new_rule, int displayWidth)
{
   rules = new bool[BYTE];
   this->thisGen = "*";
   this->extremeBit = " ";

   setDisplayWidth(displayWidth);
   setSeed(displayWidth);
   setRule(new_rule);
}

Automaton::Automaton()
{
   rules = new bool[BYTE];
   this->newRule = 0;
   this->thisGen = "*";
   this->extremeBit = " ";
   this->displayWidth = MAX_DISPLAY_WIDTH;
   setSeed(displayWidth);
}

Automaton::~Automaton()
{
   delete[] rules;
   delete[] ruleSet;
   delete[] cellSets;
   delete[] arrayGen;
}

bool Automaton::setRule(int new_rule)
{
   string bitCells[BYTE] =
   { "111", "110", "101", "100", "011", "010", "001", "000" };

   if (checkBounds(new_rule))
   {
      int digit, index = 0;

      for (int i = BYTE - 1; i >= 0; index++, i--)
      {
         digit = getRule() >> i;
         if (digit & 1)
         {
            rules[index] = 1;
         }
         else
         {
            rules[index] = 0;
         }
      }
      this->newRule = new_rule;
      createRuleSets(rules, bitCells);
      return true;
   }
   return false;
}

void Automaton::createRuleSets(bool rules[], string ruleCells[])
{
   ruleSet = new string[BYTE];

   for (int i = 0; i < BYTE; i++)
   {
      string s = rules[i] == 1 ? "*" : " ";
      ruleSet[i] = ruleCells[i] + ":" + s;
   }
}

void Automaton::applyRule(bool rules[], string cellSets[])
{
   int index = 0;

   for (int i = 0; i < thisGen.length(); i++)
   {
      if (((i + 2) < thisGen.length()))
      {
         cellSets[index] = boolString(rules[i]) + boolString(rules[i + 1])
               + boolString(rules[i + 2]);
      }
      index++;
   }
}

void Automaton::propagateNewGeneration()
{
   int currentSize = thisGen.length(); //first gen's length

   cellSets = new string[currentSize];
   arrayGen = new bool[currentSize];
   string nextGen;

   //converts first gen to binary number
   for (int i = 0; i < currentSize; i++)
   {
      bool b = thisGen[i] == '*' ? 1 : 0;
      arrayGen[i] = b;
   }
   applyRule(arrayGen, cellSets);
   cout << thisGen << endl; //printing the first gen

   int numberOfGenerations = 50;
   //propagate 50 generations
   while (numberOfGenerations != 0)
   {
      nextGen = toStringCurrentGen(cellSets);
      cout << nextGen;
      for (int i = 0; i < nextGen.length(); i++)
      {
         arrayGen[i] = stringBool(nextGen[i]);
      }
      applyRule(arrayGen, cellSets);
      numberOfGenerations--;

   }
}


string Automaton::toStringCurrentGen(string cellSets[])
{
   string currentGen;

   for (int j = 0; j < getDisplayWidth(); j++)
   {
      for (int i = 0; i < BYTE; i++)
      {
         if (ruleSet[i].substr(0, 3) == cellSets[j])
            currentGen += ruleSet[i].substr(4);
      }
   }
   return " " + currentGen + "\n";
}

bool Automaton::checkBounds(int new_rule)
{
   bool inBounds = new_rule >= 0 && new_rule <= 255;

   if (!inBounds)
   {
      cout << "not in bounds" << endl;
      return false;
   }
   else
   {
      this->newRule = new_rule;
      cout << "start" << endl;
      return true;
   }
}

void Automaton::setSeed(int displayWidth)
{
   string temp = "";
   temp.append(displayWidth, ' ');
   temp.insert(displayWidth / 2, thisGen);
   thisGen = temp;
}

bool Automaton::setDisplayWidth(int width)
{
   if (displayWidth > 0 || displayWidth <= MAX_DISPLAY_WIDTH)
   {
      this->displayWidth = width;
      return true;
   }
   return false;
}

/* ------------- RUN (OUTPUT) --------------------------------------------------
 *
 * Enter Rule (0 - 255) : 4

Enter displayWidth 1-121 : 50
start
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
                         *
continue? y / n :y
Enter Rule (0 - 255) : 126

Enter displayWidth 1-121 : 100
start
                                                  *
                                                 ***
                                                ** **
                                               *******
                                              **     **
                                             ****   ****
                                            **  ** **  **
                                           ***************
                                          **             **
                                         ****           ****
                                        **  **         **  **
                                       ********       ********
                                      **      **     **      **
                                     ****    ****   ****    ****
                                    **  **  **  ** **  **  **  **
                                   *******************************
                                  **                             **
                                 ****                           ****
                                **  **                         **  **
                               ********                       ********
                              **      **                     **      **
                             ****    ****                   ****    ****
                            **  **  **  **                 **  **  **  **
                           ****************               ****************
                          **              **             **              **
                         ****            ****           ****            ****
                        **  **          **  **         **  **          **  **
                       ********        ********       ********        ********
                      **      **      **      **     **      **      **      **
                     ****    ****    ****    ****   ****    ****    ****    ****
                    **  **  **  **  **  **  **  ** **  **  **  **  **  **  **  **
                   ***************************************************************
                  **                                                             **
                 ****                                                           ****
                **  **                                                         **  **
               ********                                                       ********
              **      **                                                     **      **
             ****    ****                                                   ****    ****
            **  **  **  **                                                 **  **  **  **
           ****************                                               ****************
          **              **                                             **              **
         ****            ****                                           ****            ****
        **  **          **  **                                         **  **          **  **
       ********        ********                                       ********        ********
      **      **      **      **                                     **      **      **      **
     ****    ****    ****    ****                                   ****    ****    ****    ****
    **  **  **  **  **  **  **  **                                 **  **  **  **  **  **  **  **
   ********************************                               ********************************
  **                              **                             **                              **
 ****                            ****                           ****                            ****
 *  **                          **  **                         **  **                          **  *
continue? y / n :y
Enter Rule (0 - 255) : 130

Enter displayWidth 1-121 : 51
start
                         *
                        *
                       *
                      *
                     *
                    *
                   *
                  *
                 *
                *
               *
              *
             *
            *
           *
          *
         *
        *
       *
      *
     *
    *
   *
  *
 *


























continue? y / n :y
Enter Rule (0 - 255) : 110

Enter displayWidth 1-121 : 101
start
                                                  *
                                                 **
                                                ***
                                               ** *
                                              *****
                                             **   *
                                            ***  **
                                           ** * ***
                                          ******* *
                                         **     ***
                                        ***    ** *
                                       ** *   *****
                                      *****  **   *
                                     **   * ***  **
                                    ***  **** * ***
                                   ** * **  ***** *
                                  ******** **   ***
                                 **      ****  ** *
                                ***     **  * *****
                               ** *    *** ****   *
                              *****   ** ***  *  **
                             **   *  ***** * ** ***
                            ***  ** **   ******** *
                           ** * ******  **      ***
                          *******    * ***     ** *
                         **     *   **** *    *****
                        ***    **  **  ***   **   *
                       ** *   *** *** ** *  ***  **
                      *****  ** *** ****** ** * ***
                     **   * ***** ***    ******** *
                    ***  ****   *** *   **      ***
                   ** * **  *  ** ***  ***     ** *
                  ******** ** ***** * ** *    *****
                 **      ******   ********   **   *
                ***     **    *  **      *  ***  **
               ** *    ***   ** ***     ** ** * ***
              *****   ** *  ***** *    ********** *
             **   *  ***** **   ***   **        ***
            ***  ** **   ****  ** *  ***       ** *
           ** * ******  **  * ***** ** *      *****
          *******    * *** ****   ******     **   *
         **     *   **** ***  *  **    *    ***  **
        ***    **  **  *** * ** ***   **   ** * ***
       ** *   *** *** ** ******** *  ***  ******* *
      *****  ** *** ******      *** ** * **     ***
     **   * ***** ***    *     ** *********    ** *
    ***  ****   *** *   **    *****       *   *****
   ** * **  *  ** ***  ***   **   *      **  **   *
  ******** ** ***** * ** *  ***  **     *** ***  **
 **      ******   ******** ** * ***    ** *** * ***
 **     **    *  **      ******** *   ***** ***** *
continue? y / n :y
Enter Rule (0 - 255) : 30

Enter displayWidth 1-121 : 31
start
               *
              ***
             **  *
            ** ****
           **  *   *
          ** **** ***
         **  *    *  *
        ** ****  ******
       **  *   ***     *
      ** **** **  *   ***
     **  *    * **** **  *
    ** ****  ** *    * ****
   **  *   ***  **  ** *   *
  ** **** **  *** ***  ** ***
 **  *    * ***   *  ***  *  *
 * ****  ** *  * *****  *******
 * *   ***  **** *    ***
 * ** **  ***    **  **  *
 * *  * ***  *  ** *** ****
 * **** *  ******  *   *   *
 * *    ****     **** *** ***
 * **  **   *   **    *   *  *
 * * *** * *** ** *  *** ******
 * * *   * *   *  ****   *
 * * ** ** ** *****   * ***
 * * *  *  *  *    * ** *  *
 * * ***********  ** *  *****
 * * *          ***  ****    *
 * * **        **  ***   *  ***
 * * * *      ** ***  * *****
 * * * **    **  *  *** *    *
 * * * * *  ** ******   **  ***
 * * * * ****  *     * ** ***
 * * * * *   ****   ** *  *  *
 * * * * ** **   * **  ********
 * * * * *  * * ** * ***
 * * * * **** * *  * *  *
 * * * * *    * **** *****
 * * * * **  ** *    *    *
 * * * * * ***  **  ***  ***
 * * * * * *  *** ***  ***  *
 * * * * * ****   *  ***  ****
 * * * * * *   * *****  ***   *
 * * * * * ** ** *    ***  * **
 * * * * * *  *  **  **  *** *
 * * * * * ******* *** ***   **
 * * * * * *       *   *  * **
 * * * * * **     *** ***** * *
 * * * * * * *   **   *     * *
 * * * * * * ** ** * ***   ** *
 * * * * * * *  *  * *  * **  *
continue? y / n :n

End
 *
 */
