#include <iostream>
#include <fstream>        // Used for working with files
#include <jni.h>          // Used for connecting C++ to Java
#include <vector>
#include <sstream>        // Used for iterating through strings and conversions
#include <bits/stdc++.h>  // Used in LoadDataFromFile() for transform() to make string lowercase
#include <windows.h>      // Used for Sleep() to make program pause for a second
#include "Animal.h"
#include "Oviparous.h"
#include "Mammal.h"

using namespace std;

void GenerateData();
void LoadDataFromFile(vector<Animal*>& myVector);
void AddAnimal(vector<Animal*>& myVector);
void RemoveAnimal(vector<Animal*>& myVector);
void DisplayAnimals(vector<Animal*>& myVector);
int DisplayMenu();
bool RunProgram(vector<Animal*>& myVector, int choice);




int main(){
   vector<Animal*> animalVector;                // Vector of Animal object pointers
   int menuChoice;
   bool keepGoing = true;

   while (keepGoing == true) {                  // Keep going until user opts to exit
      menuChoice = DisplayMenu();               // Show menu options
      keepGoing = RunProgram(animalVector, menuChoice);     //Run various functions on/for animal vector
   }
   return 0;
}



// Java integration code lets user add animal to text file
void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}



// Loads animals from text file into vector
void LoadDataFromFile(vector<Animal*>& myVector){
   ifstream inFS;                                               // Input file stream object for traversing .txt file
   stringstream ss;                                             // Stream object for traversing through string of user answers
   vector<int> intVector;                                       // Keeps track of integer found in string stream object
   vector<Animal*>::iterator ptr;                               // Iterator for traversing through vector
   string currLine, currTrackNum, currName, currSubType, temp;
   int currNumEggs = 0;
   int currIsNursing = 0;
   int found;                                                   // For finding an integer in string

   inFS.open("zoodata.txt");                          // Try opening .txt file
   if (!inFS.is_open()) {                             // If can't open, throw exception
      throw string("ERROR: Could not open file.");
   }

   while (!inFS.eof()) {                                 // Iterate through file until reaching end
      try {
         getline(inFS, currLine);                        // Get current line from text file into string
         ss << currLine;                                 // Make string into string stream
         cout << endl;
         while (!ss.eof()) {                             // Iterate through each item of the string stream
            ss >> temp;                                  // Extracting word by word from stream
            if (stringstream(temp) >> found) {           // Check if current word is integer
               intVector.push_back(found);               // Keep track of the found integer
            }
         }

         if (intVector.size() > 3) {                     // If there are more than 3 integers in user answers, throw an exception
            throw string("ERROR: Consider the following and resubmit answers:\n"
                  "      Too many integers detected in answers.\n"
                  "      Number of eggs and nursing value should be integers.\n"
                  "      Track number can be alphanumeric.\n"
                  "      Name, type, and sub-type should be alphabetical.\n"
                  "      Track number should have no spaces.\n"
                  "      Do not exceed character limits.");
         }
         if (currLine.substr(0,1) != "0" || currLine.substr(7,1) != " ") {      // Make sure track number input was 6 characters max
            throw string("ERROR: Track number can have maximum of 6 characters.");
         }
         currTrackNum = currLine.substr(1, 6);                                  // Find track number
         if (currTrackNum.find(' ') != string::npos) {                          // If there are any spaces in track number, throw error
            throw string("ERROR: Track number cannot contain spaces.");
         }
         for (ptr = myVector.begin(); ptr < myVector.end(); ++ptr) {            // Search animal vector for any matching track number
            if ((*ptr)->GetTrackNum() == currTrackNum) {                        // If track number already taken, throw error
               throw string("ERROR: Track number ") + currTrackNum + string(" already exists!");
            }
         }

         currName = currLine.substr(8, 15);                // Find name of animal
         currNumEggs = intVector.at(1);                    // Find number of eggs laid
         if (currNumEggs < 0) {                            // If number of eggs is negative number, throw error
            throw string("ERROR: Number of eggs must be a non-negative integer.");
         }
         currIsNursing = intVector.at(2);                  // Find nursing value
         if (currIsNursing != 0 && currIsNursing != 1) {   // If nursing value is not 1 or 0 (yes or no), throw error
            throw string("ERROR: Wrong input for nursing question. Must be 0 for no, 1 for yes.");
         }


         currSubType = currLine.substr(42, 15);            // Find animal sub-type (ex: crocodile)
         trim(currSubType);                                // Trim whitespace
         transform(currSubType.begin(), currSubType.end(), currSubType.begin(), ::tolower);      // Make sub-type string lowercase for comparison

         if (currSubType == "crocodile") {                                             // If sub-type chosen is crocodile, add crocodile object
            cout << "Crocodile found in file! Added to program." << endl;
            if (currIsNursing == 1) {                                                          // If nursing value is yes, ignore and inform user
               cout << "(But crocodiles don't nurse! Nursing value set back to 0.)" << endl;
            }
            myVector.push_back(new Crocodile(currName, currTrackNum, currNumEggs));    // Add Crocodile pointer object
         }
         else if (currSubType == "goose") {                                             // If sub-type chosen is goose, add goose object
            cout << "Goose found in file! Added to program." << endl;
            if (currIsNursing == 1) {                                                          // If nursing value is yes, ignore and inform user
               cout << "(But geese don't nurse! Nursing value set back to 0.)" << endl;
            }
            myVector.push_back(new Goose(currName, currTrackNum, currNumEggs));    // Add Goose pointer object
         }
         else if (currSubType == "pelican") {                                             // If sub-type chosen is pelican, add pelican object
            cout << "Pelican found in file! Added to program." << endl;
            if (currIsNursing == 1) {                                                          // If nursing value is yes, ignore and inform user
               cout << "(But pelicans don't nurse! Nursing value set back to 0.)" << endl;
            }
            myVector.push_back(new Pelican(currName, currTrackNum, currNumEggs));    // Add Pelican pointer object
         }
         else if (currSubType == "bat") {                                             // If sub-type chosen is bat, add bat object
           cout << "Bat found in file! Added to program." << endl;
           if (currNumEggs != 0) {                                                          // If numEggs positive, inform user it will be ignored
              cout << "(But bats don't lay eggs! Number of eggs set back to 0.)" << endl;
           }
           myVector.push_back(new Bat(currName, currTrackNum, currIsNursing));    // Add bat pointer object
         }
         else if (currSubType == "whale") {                                             // If sub-type chosen is whale, add whale object
            cout << "Whale found in file! Added to program." << endl;
            if (currNumEggs != 0) {                                                      // If numEggs positive, inform user it will be ignored
               cout << "(But whales don't lay eggs! Number of eggs set back to 0.)" << endl;
            }
            myVector.push_back(new Whale(currName, currTrackNum, currIsNursing));    // Add whale pointer object
         }
         else if (currSubType == "sealion" || currSubType == "sea lion") {    // If sub-type chosen is sea lion, add SeaLion object
            cout << "Sea lion found in file! Added to program." << endl;
            if (currNumEggs != 0) {                                                      // If numEggs positive, inform user it will be ignored
               cout << "(But sea lions don't lay eggs! Number of eggs set back to 0.)" << endl;
            }
            myVector.push_back(new SeaLion(currName, currTrackNum, currIsNursing));    // Add SeaLion pointer object
         }
         else {                                                                           // If sub-type was not a valid choice throw error
            throw string("ERROR: Invalid sub-type of animal chosen. Check spelling. \n"
                  "Must be one of the following: crocodile, goose, pelican, bat, whale, or sea lion");
         }
         ss.clear();             // Clear string stream object for next loop iteration
         intVector.clear();      // Clear integer vector to keep track of next loop iteration

      }catch (int error) {
         cout << "Error #" << error << endl;
      }catch (invalid_argument const& error) {
        cout << "ERROR: Number of eggs must be a non=negative integer. Nursing value must be 1 or 0." << endl;
        cout << "**Make sure answers to questions don't exceed character limits." << endl;
      }catch (out_of_range const& error) {
         cout << "ERROR: Could not convert string to integer for one of the questions. Integer overflow, out of range throw." << endl;
         cout << "**Make sure answers to questions don't exceed character limits." << endl;
      }catch (string& error) {
         cout << error << endl;
      }catch(...) {cout << "Could not convert string to integer, reason unknown." << endl;
      cout << "**Make sure answers to questions don't exceed character limits." << endl;
      }
   }
   cout << endl;
   Sleep(1000);           // Pause program for one second
   inFS.close();          // Close txt file
}



// Adds an animal to vector
void AddAnimal(vector<Animal*>& myVector) {
   string addType, addSubType, addName, addTrackNum;
   int addNumEggs   = 0;
   int addIsNursing = 0;
   int addConfirm;
   vector<Animal*>::iterator ptr;                      // Used to traverse vector

   cout << "=========================================================================\n"
           "++++++++++++++++++++++++++  Add Animal Record  ++++++++++++++++++++++++++\n"
           "=========================================================================\n" << endl;

   try {
      cout << "What is the animal's name that you would like to add? (maximum of 15 characters)" << endl;
      cin.ignore();                  // Ignore newline character because cin was used last
      getline(cin, addName);
      if (cin.fail()) {              // If getline() failed for any reason, clear failure and throw error
         cin.clear();
         throw string("ERROR: Could not read input. Confirm data type.");
      }
      if (addName.length() > 15) {                 // If name input was more than limit throw error
         throw string("ERROR: Animal name has a maximum of 15 characters.");
      }


      cout << "\nWhat is his/her track number (must be 6 characters): " << endl; // What is animal's track number?
      getline(cin, addTrackNum);
      if (cin.fail()) {              // If getline() failed throw error
         cin.clear();
         throw string("ERROR: Unable to read track number. Wrong data type.");
      }
      if ((addTrackNum.find(' ') != string::npos) || (addTrackNum.size() != 6)) {  // If track number contains space or is not 6 characters
         throw string("ERROR: No spaces allowed in track number.\n"
               "       Track number must be 6 characters.\n");
      }
      for (ptr = myVector.begin(); ptr < myVector.end(); ++ptr) {        // Search current animals for same track number
         if ((*ptr)->GetTrackNum() == addTrackNum) {                     // If track number already used, throw error
            throw string("ERROR: Track number ") + addTrackNum + string(" already exists!");
         }
      }


      cout << "\nIs " << addName << " an oviparous or a mammal?" << endl;     // Is the animal TYPE oviparous or mammal?
      getline(cin, addType);
      if (cin.fail()) {                    // If getline() failed, throw error
         cin.clear();
         throw string("ERROR: Could not read input. Confirm data type.");
      }
      transform(addType.begin(), addType.end(), addType.begin(), ::tolower);      // Make animal type lowercase for comparison


      if (addType == "oviparous") {
         cout << "Is " << addName << " a crocodile, goose, or pelican?" << endl;    // What is animal's sub-type?
         getline(cin, addSubType);
         if (cin.fail()) {             // If getline() failed, throw error
            cin.clear();
            throw string("ERROR: Could not read input. Confirm data type.");
         }
         transform(addSubType.begin(), addSubType.end(), addSubType.begin(), ::tolower);      // Make subtype lowercase for comparison

         if (addSubType != "crocodile" && addSubType != "goose" && addSubType != "pelican") {     // If subtype not valid answer throw error
            throw string("ERROR: Our zoo only accepts crocodile, goose, or pelican oviparous\'. Please check spelling.");
         }
         cout << "\nHow many eggs has " << addName << " laid? (must be integer)" << endl;    // How many eggs has the animal laid?
         cin >> addNumEggs;
         if (cin.fail() || addNumEggs < 0) {       // If input problem or numEggs is negative, throw error
            throw string("ERROR: Number of eggs value must be a non-negative integer.");
         }
      }


      else if (addType == "mammal") {
         cout << "\nIs " << addName << " a bat, whale, or sea lion?" << endl;          // What's the animal's sub-type?
         getline(cin, addSubType);
         if (cin.fail()) {             // If getline() failed, throw error
            cin.clear();
            throw string("ERROR: Could not read input. Confirm data type.");
         }
         transform(addSubType.begin(), addSubType.end(), addSubType.begin(), ::tolower);      // Make sub-type lowercase
         if (addSubType != "bat" && addSubType != "whale" && addSubType != "sealion" && addSubType != "sea lion") {  // If not valid choice
            throw string("ERROR: Our zoo only accepts bat, whale, or sea lion mammals. Please check spelling.");     // Throw error
         }

         cout << "\nIs " << addName << " currently nursing? (0 for no, 1 for yes)" << endl;   // Is the mammal nursing?
         cin >> addIsNursing;
         if (cin.fail()) {       // If cin integer input failed, throw error
            cin.clear();
            throw string("ERROR: Could not read input. Confirm nursing value is integer.");
         }
         if (addIsNursing != 0 && addIsNursing != 1) {     // If nursing value not integers 0 or 1, throw error
            throw string("ERROR: Wrong input for nursing question. Must be 0 for no, 1 for yes.");
         }
      }
      else {                  // If user inputted animal type other than mammal or oviparous, throw error
         throw string("ERROR: New animal record must be oviparous or mammal. Check spelling.");
      }


      addType[0] = toupper(addType[0]);            // Capitalize first letter of mammal/oviparous
      addSubType[0] = toupper(addSubType[0]);      // Capitalize first letter of animal sub-type
      cout << "\n **" << addName <<
            "\n   Type: " << addType <<
            "\n   Sub-type: " << addSubType <<
            "\n   Track Number: " << addTrackNum <<
            "\n   Number of eggs laid: " << addNumEggs <<
            "\n   Nursing: " << addIsNursing << endl;
      addSubType[0] = tolower(addSubType[0]);            // Make sub-type lowercase again for later comparison

      // Confirm addition of animal?
      cout << "\n**Confirm the above data. Would you like to add animal to zoo records? (1 to confirm, 2 to exit)\n" << endl;
      if (!(cin >> addConfirm)) {      // Get integer user input, if failed, clear and ignore for next cin, throw error
         cin.clear();
         cin.ignore(10000, '\n');
         throw string("ERROR: Confirm nursing value is integer.");
      }
      cout << "\n---------------------------------------------------------------------------------------\n" << endl;

      switch (addConfirm) {
      case 1:
         if (addSubType == "crocodile") {                             // If crocodile subtype, create new Crocodile pointer, add to vector
            Crocodile* addCroc = new Crocodile(addName, addTrackNum, addNumEggs);
            myVector.push_back(addCroc);
         }
         else if (addSubType == "goose") {
            Goose* addGoose = new Goose(addName, addTrackNum, addNumEggs);
            myVector.push_back(addGoose);
         }
         else if (addSubType == "pelican") {
            Pelican* addPelican = new Pelican(addName, addTrackNum, addNumEggs);
            myVector.push_back(addPelican);
         }
         else if (addSubType == "bat") {
            Bat* addBat = new Bat(addName, addTrackNum, addIsNursing);
            myVector.push_back(addBat);
         }
         else if (addSubType == "whale") {
            Whale* addWhale = new Whale(addName, addTrackNum, addIsNursing);
            myVector.push_back(addWhale);
         }
         else if (addSubType == "sealion" || addSubType == "sea lion") {
            SeaLion* addSeaLion = new SeaLion(addName, addTrackNum, addIsNursing);
            myVector.push_back(addSeaLion);
         }
         else {               // If sub-type was not a valid option, throw error
            throw string("ERROR: Our zoo only accepts crocodiles, geese, pelicans, bats, whales, or sea lions. "
                  "Please check spelling.");
         }
         cout << addName << " was added to our zoo records! Welcome " << addName << "!\n" << endl;   // Tell user addition was successful
         break;

      case 2:
         cout << "Canceling addition and exiting to menu..." << endl;        // If user does not want to add the record, don't add to vector
         break;
      default:               // Else, throw error
         throw string("ERROR: Could not read input for add confirmation. Must be 1, 2, or 3.");
         break;
      }

   }catch(string& error) {
      cout << error << endl;
   }catch(...) {
      cout << "ERROR: Unknown reason. Check spelling. Make sure answers don\'t exceed character limits.\n" << endl;
   }
   Sleep(1000);         // Pause program for one second
}



// Removes animal from vector via tracking number
void RemoveAnimal(vector<Animal*>& myVector) {
   string delTrackNum;
   int confirmDel;
   bool animalDeleted = false;
   vector<Animal*>::iterator ptr;          // Used to iterate through vector

   cout << "=====================================================================================\n"
           "-------------------------------- Remove Animal Record  ------------------------------\n"
           "=====================================================================================\n" << endl;
   cout << "This option allows you to delete an animal record from our database.\n"
           "Let\'s look up the animal\'s information.\n\n"

           "What is the his or her track number?" << endl;
   try {
       cin.ignore();
       getline(cin, delTrackNum);
       if (cin.fail()) {             // If getline() failed, throw error
          cin.clear();
          throw string("ERROR: Could not read input. Confirm data type.");
       }
       for (ptr = myVector.begin(); ptr < myVector.end();) {           // Search animals in vector for the tracking number
          if ((*ptr)->GetTrackNum() == delTrackNum) {                  // If there is an animal with that tracking number, display it
             cout << "\n **" << (*ptr)->GetName() <<
                     "\n   Type: " << (*ptr)->GetType() <<
                     "\n   Sub-type: " << (*ptr)->GetSubType() <<
                     "\n   Track Number: " << (*ptr)->GetTrackNum() <<
                     "\n   Number of eggs laid: " << (*ptr)->GetNumEggs() <<
                     "\n   Nursing: " << (*ptr)->GetIsNursing() << "\n\n\n"
                     "**Please confirm the above information." << endl;

             cout << "Do you really want to delete this record? (0 for no, 1 for yes)\n" << endl;   // Confirm record deletion
             cout << "  >";

             cin >> confirmDel;
             cout << "\n-------------------------------------------------------------------------\n" << endl;
             if (cin.fail()) {         // If cin input failed, throw error
                cin.clear();
                cin.ignore();
                throw string("ERROR: Confirm deletion by inputing 1, cancel deletion with 0.");
             }

             switch (confirmDel) {    // 0 for cancel delete, 1 for confirm delete
             case 0:
                cout << "Deletion canceled." << endl;
                ptr++;                // Iterator go to next object in vector
                break;
             case 1:
                delete *ptr;                       // Deallocate memory for the object on the heap
                ptr = myVector.erase(ptr);         // Erase the element in vector, move iterator to next valid object
                cout << "Animal successfully deleted." << endl;
                animalDeleted = true;              // Remember we deleted a record
                Sleep(1500);                       // Program pause for 1.5 seconds
                cout << "\n" << endl;
                break;
             default:                      // If user input was not 0 or 1, throw error
                throw string("ERROR: Answer must be 0 for no or 1 for yes.");
             }
          }
          else {              // If this iteration did not have the same track number, move on to next object in vector
             ptr++;
          }
       }
       if (animalDeleted == false) {             // If we never deleted an animal after searching the vector, inform user
          cout << "\n-------------------------------------------------------------------------\n" << endl;
          cout << "Could not find an animal with that tracking number.\n" << endl;
          Sleep(1000);                           // Program pause for one second
       }

   }catch (string& error) {
      cout << error << endl;
   }
}



// Display main menu options
int DisplayMenu() {
   int userInput;
   bool valid = false;

   cout << "=========================================================================\n"
           "----------------- Welcome to the Wild Life Zoo Database! ----------------\n"
           "=========================================================================\n" << endl;
   cout << "Choose one of the following options:\n\n"
           "1- Generate animal data\n"
           "2- Load file\n"
           "3- Display current animal data\n"
           "4- Add record\n"
           "5- Delete record\n"
           "6- Save changes to database file\n"
           "7- Exit program\n" << endl;

   cout << "  >";

   while (valid == false) {
      try{
         cin >> userInput;
         if (cin.fail()) {       // If input failed, throw error
            cin.clear();
            cin.ignore(10000, '\n');
            throw string ("\nERROR: Could not read input. Verify answer is integer 1-7.");
         }
         if (userInput >= 1 && userInput <= 7) {         // If user entered valid response
            valid = true;
            return userInput;       // Return menu response
         }
         else{
            cout << userInput << endl;       // If not an integer 1-7, throw error
            throw string("\nERROR: Valid menu options are 1, 2, 3, 4, 5, 6, or 7.\n\nPlease try again...");
         }

      }catch(string& error) {
         cout << error << endl;
      }catch(...) {cout << "\nUnknown error.\n\n  >";}
   }
   return 0;
}



// Display animals in vector in tabular format
void DisplayAnimals(vector<Animal*>& myVector) {
   string pressEnter;
   vector<Animal*>::iterator ptr;         // Used for iterating thru vector

   cout << "\n\n\n" << endl;
   cout << "=======================================================================================\n"
           "----------------------------------  List of Animals -----------------------------------\n"
           "=======================================================================================\n" << endl;
   cout << "                 Here is the complete list of animals added so far:\n"
           "                   **Make sure to save before exiting program!**" << endl;
   cout << "=======================================================================================" << endl;
   cout << "       Name        | Track Number  |   Type   |  Sub-type  | Number of Eggs | Nursing  " << endl;
   cout << "=======================================================================================\n";

   if (myVector.size() == 0) {         // If there is no animals in vector yet
      cout << "\n                **There are no animals in the current system.**\n"
           "                    Please add animals via the main menu option." << endl;
      cout << "---------------------------------------------------------------------------------------\n" << endl;
   }
   else {                // If there are animals in the vector
     for (ptr = myVector.begin(); ptr < myVector.end(); ptr++) {        // Loop thru vector, displaying each animal's information

         cout << " " << setw(18) << left << (*ptr)->GetName() << "  "
              << setw(14) << (*ptr)->GetTrackNum() << "  "
              << setw(9) << (*ptr)->GetType() << "  "
              << setw(11) << (*ptr)->GetSubType() << "  "
              << setw(16) << (*ptr)->GetNumEggs() << "  "
              << setw(9) << (*ptr)->GetIsNursing() << endl;
         cout << "---------------------------------------------------------------------------------------" << endl;
     }
     cout << endl;
   }
   cout << "Press Enter to continue..." << endl;


   cin.ignore();                  // Ignore last cin's \n character
   getline(cin, pressEnter);
   if (cin.fail()) {              // If getline() failed, throw error
      cin.clear();
   }
}



// Save animals in vector to text file, overwriting existing text file
void SaveDataToFile(vector<Animal*>& myVector) {
   ofstream oFS;
   vector<Animal*>::iterator ptr;
   int counter;

   oFS.open("zoodata.txt");                        // Try opening .txt file to write to it
   if (!oFS.is_open()) {                             // If can't open, throw exception
      throw string("ERROR: Could not open file for output stream.");
   }

   counter = 1;    // Count iterations
   for (ptr = myVector.begin(); ptr < myVector.end(); ++ptr) {       // Iterate through vector of animals, writing data of each to text file
      if (counter != 1) {        // If not the first item in vector, write newline character first
         oFS << endl;
      }
      oFS << "0" << left << setw(7) << (*ptr)->GetTrackNum()            // Write animal data to file, format everything exactly as the java function does
          << setw(17) << (*ptr)->GetName()
          << setw(17) << (*ptr)->GetType()
          << setw(17) << (*ptr)->GetSubType()
          << (*ptr)->GetNumEggs() << " "
          << (*ptr)->GetIsNursing();
      ++counter;
   }
   oFS.close();               // Close text file
   cout << "**Save successfully complete.\n" << endl;
   Sleep(1000);
}



// Runs various functions based on menu choice
bool RunProgram(vector<Animal*>& myVector, int choice) {
   cout << "\n-------------------------------------------------------------------------\n" << endl;

   switch (choice) {
   case 1:                                                     // Run java code
      cout << "Attempting to generate data...\n" << endl;
      GenerateData();
      break;
   case 2:                                                     // Load animal data from text file into vector
      LoadDataFromFile(myVector);
      break;
   case 3:                                                     // Displays vector of animals in tabular format
      DisplayAnimals(myVector);
      break;
   case 4:                                                     // Add animal record to vector
      AddAnimal(myVector);
      break;
   case 5:                                                     // Removes animal record from vector
      RemoveAnimal(myVector);
      break;
   case 6:                                                     // Save vector of animals to text file, overwriting whatever was there
      SaveDataToFile(myVector);
      break;
   case 7:                                                     // Exits program
      cout << "Exiting program..." << endl;  // REMOVE
      return false;
      break;
   default:                                                    // Print error, let user try again
      cout << "Error occurred. Please try again." << endl;
      return true;
      break;
   }
   return true;               // Goes back to main menu
}
