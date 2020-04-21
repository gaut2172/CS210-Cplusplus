/*
 * Mammal.h
 *
 *  Created on: Apr 13, 2020
 *      Author: 1305052_snhu
 */

#ifndef MAMMAL_H_
#define MAMMAL_H_

#include "Animal.h"
using namespace std;

class Mammal : public Animal {
public:
   Mammal();
   virtual ~Mammal();
   virtual void PrintAnimal() = 0;   // Makes abstract class
};

/************************* Child Classes: **************************/
class Bat : public Mammal {
public:
   // Constructor
   Bat(string name, string trackNum, int nursingValue) {
      m_name = name;
      m_trackNum = trackNum;
      m_isNursing = nursingValue;
      m_subType = "Bat";
   }
   void PrintAnimal() {
      string tempNameVar = (this->GetName());
      trim(tempNameVar);
      cout << tempNameVar << " is a Bat. " << this->GetTrackNum() << ", Nursing value: " << this->GetIsNursing() << endl;
   }
};
class Whale : public Mammal {
public:
   // Constructor
   Whale(string name, string trackNum, int nursingValue) {
      m_name = name;
      m_trackNum = trackNum;
      m_isNursing = nursingValue;
      m_subType = "Whale";
   }
   void PrintAnimal() {
      string tempNameVar = (this->GetName());
      trim(tempNameVar);
      cout << tempNameVar << " is a Whale. " << this->GetTrackNum() << ", Nursing value: " << this->GetIsNursing() << endl;
   }
};
class SeaLion : public Mammal {
public:
   // Constructor
   SeaLion(string name, string trackNum, int nursingValue) {
      m_name = name;
      m_trackNum = trackNum;
      m_isNursing = nursingValue;
      m_subType = "Sea Lion";
   }
   void PrintAnimal() {
      string tempNameVar = (this->GetName());
      trim(tempNameVar);
      cout << tempNameVar << " is a Sealion. " << this->GetTrackNum() << ", Nursing value: " << this->GetIsNursing() << endl;
   }
};


#endif /* MAMMAL_H_ */
