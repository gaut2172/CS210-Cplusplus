/*
 * Animal.h
 *
 *  Created on: Apr 11, 2020
 *      Author: 1305052_snhu
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <iostream>
#include <string>
#include <cctype>         // Used for trim function
#include <algorithm>      // Used for trim function
#include <locale>         // Used for trim function

using namespace std;


class Animal {

public:
   Animal();
   Animal(char name, int trackNum);
   virtual ~Animal();

   // Get functions
   string GetName();
   string GetTrackNum();
   string GetType();
   string GetSubType();
   int GetNumEggs();
   int GetIsNursing();

   // Set functions
   void SetName(string nameToSet);
   void SetTrackNum(string numToSet);
   void SetType(string typeToSet);
   void SetSubType(string subTypeToSet);
   void SetNumEggs(int numToSet);
   void SetIsNursing(int nursingValue);

   virtual void PrintAnimal() = 0;       //Makes this an abstract class

protected:
   string m_name;
   string m_trackNum;
   string m_type;
   string m_subType;
   int m_isNursing;
   int m_numEggs;
};

/******************************** Extra General Functions: *********************************/

//Trim whitespace on left side
static inline void ltrim(string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

//Trim whitespace on right side
static inline void rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

//Trim whitespace on right and left sides
static inline void trim(string &s) {
    ltrim(s);
    rtrim(s);
}

#endif /* ANIMAL_H_ */
