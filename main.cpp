
#include <iostream>
#include <cctype>
#include <cstring>
#include <limits>

using namespace std;

void welcome();

void displayMenu();

void readOption(char &option); 

void encode(char encodeFileName[]);

void readInput(char fName[], char lName[], bool &lateFlag);

void readInput(char parsedID[], char fileName[]);

void readTime(char strTime[]);

const char SEPARATOR = '_';

const int MAX_FILENAME_CHARS = 100;

const int MAX_TEMP_CHARS = 25;

void set_to_null(char arr[]);

int main() {
    // Declare appropriate local variables.
    char next = '\0';    
    bool encoding = true;
    char filename[MAX_FILENAME_CHARS + 1] = {0};

    welcome();
    // In an appropriate loop call the functions and output the encoded file name.
    // Repeat the menu in the loop until the user chooses to quit.
    // main() should do nothing more than the above steps.

    do {
        displayMenu();
        readOption(next);
        encoding = next == 'e';
        if(encoding) {
            encode(filename);
            cout << endl;
            cout << "Your encoded file name is: " << filename << endl;
            cout << endl;
        }
    } while(encoding);

    cout << endl;
    cout << "Thank you for using my fileName generator!" << endl;
}

// - This function prints a welcome message to the user.
void welcome() {
    cout << "Welcome to my fileName encoding program!!" << endl;
}

// - This function prints the menu to the user. Your menu must have 2 items - Encode file name and quit. Here is an example:
// (E)ncode a file name
// (Q)uit
void displayMenu() {
    cout << "Please pick an option below:" << endl;
    cout << "(e)Encode a file name" << endl;
    cout << "(q)Quit" << endl;
}

// This function will read an option and return to the called function through the reference parameter.
// You must do validation to make sure that the character is E/e or Q/q and nothing other than that. Use a while loop to do this.
void readOption(char &option) {
    bool valid = false;
    do {
        cin >> option;

        // https://en.cppreference.com/w/cpp/string/byte/tolower
        option = tolower(option);
        switch(option) {
            case 'e': // fallthrough
            case 'q': 
                valid = true;
                break;
            default: 
                cout << "Invalid option! Please try again!!" << endl;
        }
    } while(!valid);
}

// This should be a void function that takes 1 char array encodeFileName.
// Declare appropriate local variables.
// Call the readInput() function to read student’s names and lateFlag.
// Call the readInput() function to read Student ID and filename.
// Call the readTime() function to read the submitted time. (***new for this level***)
// Fill the encodeFileName array based on the six pieces of information adding underscores between.
// Start with the student’s names, if the assignment is late, put LATE in the filename and nothing otherwise, add the parsed Student ID, add the time, without the colon, and then finally add the filename.
// For example: If late: smith_sue_LATE_5587_1824_prog2.c
// If it is not late: smith_sue_5587_1824_prog2.c
// Use strncpy() and strcat() functions - refer to Sections 10.4 and 10.5 C-String library functions in your zyBooks.  Look at my example code file.
void encode(char encodeFileName[]){
    char time[MAX_TEMP_CHARS + 1] = {0};
    char temp_filename[MAX_TEMP_CHARS + 1] = {0};
    char first[MAX_TEMP_CHARS + 1] = {0};
    char last[MAX_TEMP_CHARS + 1] = {0};
    bool late = false;
    char parsedId[MAX_TEMP_CHARS + 1] = {0};
    readInput(first, last, late);
    readInput(parsedId, temp_filename);
    readTime(time);

    strcat(encodeFileName, last);
    encodeFileName[strlen(encodeFileName)] = SEPARATOR;

    strcat(encodeFileName, first);
    encodeFileName[strlen(encodeFileName)] = SEPARATOR;

    if(late) {
        strcat(encodeFileName, "LATE");
        encodeFileName[strlen(encodeFileName)] = SEPARATOR;
    }

    strcat(encodeFileName, parsedId);
    encodeFileName[strlen(encodeFileName)] = SEPARATOR;

    strcat(encodeFileName, time);
    encodeFileName[strlen(encodeFileName)] = SEPARATOR;

    strcat(encodeFileName, temp_filename);
}


//  - overloaded function
// This void function should take 2 char arrays and 1 bool variable by reference.
// It reads the student’s first name, last name and if the assignment is late or not. Student last name (e.g. Smith) (char array). Student first name (e.g. Sue) (char array)
// Make sure all character data for the student’s name is lowercase - you may write a function to convert a cstring to all lowercase.
// If the assignment was late or not (e.g., Y or N) (bool var). Must do data validation for this.
// Hint: Remember an overloaded function has the same function name but different types of parameters or the number of parameters are different.
void readInput(char fName[], char lName[], bool &lateFlag) {
    cout << "Enter your last name: ";
    cin >> lName;
    // https://en.cppreference.com/w/cpp/string/byte/strlen
    for(int i = 0; i < strlen(lName); i++) {
        lName[i] = tolower(lName[i]);
    }

    cout << "Enter your first name: ";
    cin >> fName;
    for(int i = 0; i < strlen(fName); i++) {
        fName[i] = tolower(fName[i]);
    }

    bool valid = false;
    char c = '\0';
    do{
        cout << "Was your assignment Late [y/n]? ";
        cin >> c;
        c = tolower(c);
        switch(c) {
            case 'y': // fallthrough
            case 'n': 
                valid = true;
                break;
            default: 
                cout << "Invalid option! Please try again!!" << endl;
        }
    } while (!valid);

    lateFlag = c == 'y';
}

//  - overloaded function
// This void function should take 1 char array for the parsed 4 digit Student ID that will be returned and another char array for the filename.
// The Student ID (e.g., 977-15-5587) (char array) is a local variable. Use the strncpy() function to copy from position 7 till the end of the string. strncpy(parsedID, stdID + 7, 4) will copy 4 characters from the 7th position in the stdID string to the parsedID string. Check out this example code file.
// The name of the file (e.g., prog2.cpp) (char array)
void readInput(char parsedID[], char fileName[]) {
    cout << "Enter your Student-ID (format: 222-22-2222): ";
    cin.ignore(MAX_TEMP_CHARS, '-'); // Alternative to strncpy
    cin.ignore(MAX_TEMP_CHARS, '-'); // Ignore through second hyphen
    cin >> parsedID;

    cout << "Enter the file name: ";
    cin >> fileName;
}

//  (***new for this level***)
// This is a void function that should read the time from the user as 2 integers and return one char array by reference (that is the strTime array).
// The time read from the user will be in military time (e.g.. 18:24 for 6:24pm) (2 ints, one for hour and one for mins). Check out this example code file to extract the numbers and convert them to a cstring. This example is not quite sophisticated. You must do data validation by checking the hours are between 0 and 24 and the minutes are between 0 and 60.
// This function must do data validation for the numbers and the HH:MM format. Make sure the colon : is used to separate the mins and hours.
void readTime(char strTime[]) {
    cout << "Enter the time submitted (military time - ex: 18:24 for 6:24pm): ";
    int hours = 0;
    do {
        cin >> hours;
    } while (hours < 0 || hours > 24); 
    strTime[0] = '0' + (hours / 10);
    strTime[1] = '0' + (hours % 10);

    cin.get();// remove colon

    int minutes = 0;
    do {
        cin >> minutes;
    } while (minutes < 0 || minutes > 60); 
    strTime[2] = '0' + (minutes / 10);
    strTime[3] = '0' + (minutes % 10);
}

void set_to_null(char arr[]) {
    for(int i = strlen(arr); i >= 0; i--) {
        arr[i] = '\0';
    }
}
