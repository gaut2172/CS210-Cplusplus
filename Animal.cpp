/*
 * Animal.cpp
 *
 *  Created on: Apr 11, 2020
 *      Author: 1305052_snhu
 */

#include "Animal.h"


Animal::Animal() {
   m_name = "Default name";
   m_trackNum = "0";
   m_type = "Type";
   m_subType = "Sub-type";
   m_numEggs = 0;
   m_isNursing = 0;
}
Animal::Animal(char name, int trackNum) {
   m_name = name;
   m_trackNum = trackNum;
   m_type = "Type";
   m_subType = "Sub-type";
   m_numEggs = 0;
   m_isNursing = 0;
}
Animal::~Animal() {
}
string Animal::GetName() {
   return m_name;
}
string Animal::GetTrackNum() {
   return m_trackNum;
}
string Animal::GetType() {
   return m_type;
}
string Animal::GetSubType() {
   return m_subType;
}
void Animal::SetName(string nameToSet) {
   m_name = nameToSet;
}
void Animal::SetTrackNum(string numToSet) {
   m_trackNum = numToSet;
}
void Animal::SetType(string typeToSet) {
   m_type = typeToSet;
}
void Animal::SetSubType(string subTypeToSet) {
   m_subType = subTypeToSet;
}
int Animal::GetNumEggs() {
   return m_numEggs;
}
int Animal::GetIsNursing() {
   return m_isNursing;
}
void Animal::SetIsNursing(int nursingValue) {
   m_isNursing = nursingValue;
}
void Animal::SetNumEggs(int numToSet) {
   m_numEggs = numToSet;
}

