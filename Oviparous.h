/*
 * Oviparous.h
 *
 *  Created on: Apr 11, 2020
 *      Author: 1305052_snhu
 */

#ifndef OVIPAROUS_H_
#define OVIPAROUS_H_

#include "Animal.h"

class Oviparous : public Animal{
public:
   Oviparous();
   virtual ~Oviparous();
   virtual void PrintAnimal() = 0;   // Makes abstract class
};

/************************* Child Classes: **************************/
class Crocodile : public Oviparous {
public:
   // Constructor
	Crocodile(string name, string trackNum, int numOfEggs) {
		m_name = name;
		m_trackNum = trackNum;
	   m_numEggs = numOfEggs;
	   m_subType = "Crocodile";
	}
	void PrintAnimal() {
	   string tempNameVar = (this->GetName());
	   trim(tempNameVar);
		cout << tempNameVar << " is a crocodile. " << this->GetTrackNum() << ", number of eggs: " << this->m_numEggs << endl;
	}
};
class Goose : public Oviparous {
public:
   // Constructor
	Goose(string name, string trackNum, int numOfEggs) {
      m_name = name;
      m_trackNum = trackNum;
      m_numEggs = numOfEggs;
      m_subType = "Goose";
   }
	void PrintAnimal() {
	   string tempNameVar = (this->GetName());
	   trim(tempNameVar);
		cout << tempNameVar << " is a goose. " << this->GetTrackNum() << ", number of eggs: " << this->m_numEggs << endl;
	}
};
class Pelican : public Oviparous {
public:
   // Constructor
	Pelican(string name, string trackNum, int numOfEggs) {
      m_name = name;
      m_trackNum = trackNum;
      m_numEggs = numOfEggs;
      m_subType = "Pelican";
   }
	void PrintAnimal() {
      string tempNameVar = (this->GetName());
      trim(tempNameVar);
      cout << tempNameVar << " is a pelican. " << this->GetTrackNum() << ", number of eggs: " << this->m_numEggs << endl;
	}
};

#endif /* OVIPAROUS_H_ */
