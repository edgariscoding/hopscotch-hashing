/* ===================================
 * Name: Edgar Sanchez
 * Class: Data Structures and Algorithms
 * UNT Fall 2017 Programming Assignment 02
 * Hopscotch Hashing
 * =================================== */
#include <iostream>
#include <iomanip>
using namespace std;

const int TABLE_SIZE = 17;
const int MAX_DIST = 4;

int insertValue(int);
int deleteValue(int);
int searchValue(int);
void outputTable();

void clearKey(int);
int hashValue(int);

struct Buckets {
    bool inUse = false;
    int value = 0;
    int hop[MAX_DIST] = {0};
};
Buckets bucket[TABLE_SIZE];

int main() {
    int option = 0;
    int value = 0;
    int key = 0;

    do {
        cout << "\nHOPSCOTCH HASHING MENU:\n"
                "+------------------------+\n"
                "|    1 - Insert Value    |\n"
                "|    2 - Delete Value    |\n"
                "|    3 - Search Value    |\n"
                "|    4 - Output Table    |\n"
                "|    5 - Exit Program    |\n"
                "+------------------------+\n\n"
                "Enter operation to perform: ";
        cin >> option;
        cout << endl;
        switch ( option ) {
            case 1: do {
                    cout << "Enter positive integer value to insert into Hopscotch Hash Table: ";
                    cin >> value;
                    } while (value < 1);

                    key = insertValue(value);
                    if(key >= 0) {
                        cout << value << " inserted at position " << key << endl;
                    } else if (key == -1) {
                        cerr << "ERROR: Unable to insert " << value << " into Hash Table: Hopscotch Hash Failed" << endl;
                    } else if (key == -2) {
                        cerr << "ERROR: Unable to insert 16 into Hash Table: Linear Probe Failed" << endl;
                    }
                    break;
            case 2: do {
                    cout << "Enter positive integer value to delete from Hopscotch Hash Table: ";
                    cin >> value;
                    } while (value < 1);

                    key = deleteValue(value);
                    if(key >= 0) {
                        cout << value << " deleted from position " << key << "." << endl;
                    } else {
                        cerr << "Value not found" << endl;
                    }
                    break;
            case 3: do {
                    cout << "Enter positive integer value to search for in Hopscotch Hash Table: ";
                    cin >> value;
                    } while (value < 1);

                    key = searchValue(value);
                    if(key >= 0) {
                        cout << value << " found at position " << key << "." << endl;
                    } else {
                        cerr << "Value not found" << endl;
                    }
                    break;
            case 4: cout << "HOPSCOTCH HASHING TABLE:\n";
                    outputTable();
                    break;
            case 5: cout << "Program terminated by user..." << endl;
                    break;
            default:cerr << "ERROR: Please select operation between 1 and 5, inclusively." << endl;
                    break;
        }
    } while (option != 5);
    return 0;
}

// Attempts to insert a value or recursively move values if insertion fails
int insertValue(int value) {
    int key = hashValue(value);

    // Inserts a value
    // Returns insertion key if successful
    // Exits loop if insertion is unsuccessful
    for(int i = 0; i < MAX_DIST; ++i) {
        if(bucket[key].hop[i] == 0 && !bucket[key + i].inUse) {
            key = key + i;
            if(key >= TABLE_SIZE) {
                // Out of bounds
                return -2;
            }

            bucket[key - i].hop[i] = 1;

            bucket[key].inUse = true;
            bucket[key].value = value;
            return key;
        }
    }

    // Moves a value using recursion
    // Returns insertion key if successful
    // Exits loop if move is unsuccessful
    for(int i = 0; i < MAX_DIST; ++i) {
        if(bucket[key].hop[i] == 0) {
            int parentKey = hashValue(bucket[key + i].value);
            int distance = (key + i) - parentKey;

            for(int j = 0; j < MAX_DIST; ++j) {
                if(!bucket[parentKey + j].inUse) {
                    bucket[parentKey + j].inUse = true;

                    bucket[parentKey + j].value = bucket[key + i].value;

                    bucket[parentKey].hop[j] = 1;
                    bucket[parentKey].hop[distance] = 0;

                    clearKey(key + i);
                    insertValue(value);
                    return key + i;
                }
            }
        }
    }

    // Insert and move failed
    return -1;
}

// Deletes a value and returns it's corresponding key
int deleteValue(int value) {
    int key = hashValue(value);

    if(bucket[key].hop[0] == 1 && bucket[key].value == value) {
        bucket[key].inUse = false;
        bucket[key].value = 0;
        bucket[key].hop[0] = 0;
        return key;
    }
    else if(bucket[key].hop[1] == 1 && bucket[key + 1].value == value) {
        bucket[key + 1].inUse = false;
        bucket[key + 1].value = 0;
        bucket[key].hop[1] = 0;
        return key + 1;
    }
    else if(bucket[key].hop[2] == 1 && bucket[key + 2].value == value) {
        bucket[key + 2].inUse = false;
        bucket[key + 2].value = 0;
        bucket[key].hop[2] = 0;
        return key + 2;
    }
    else if(bucket[key].hop[3] == 1 && bucket[key + 3].value == value) {
        bucket[key + 3].inUse = false;
        bucket[key + 3].value = 0;
        bucket[key].hop[3] = 0;
        return key + 3;
    }
    else {
        // Value not found
        return -1;
    }
}

// Clears key field for a corresponding value
void clearKey(int key) {
    bucket[key].inUse = false;
    bucket[key].value = 0;
    bucket[key].hop[0] = 0; //TODO set corresponding parent key to 0 if value doesnt belong
}

// Searches for a value and returns it's corresponding key
int searchValue(int value) {
    int key = hashValue(value);

    if(bucket[key].hop[0] == 1 && bucket[key].value == value) {
        return key;
    }
    else if(bucket[key].hop[1] == 1 && bucket[key + 1].value == value) {
        return key + 1;
    }
    else if(bucket[key].hop[2] == 1 && bucket[key + 2].value == value) {
        return key + 2;
    }
    else if(bucket[key].hop[3] == 1 && bucket[key + 3].value == value) {
        return key + 3;
    }
    else {
        // Value not found
        return -1;
    }
}

// Prints the current table
void outputTable() {
    cout << "+------------------------+\n"
            "|   #  |  item  |   hop  |\n"
            "+------------------------+\n";
    for(int i = 0; i < TABLE_SIZE; ++i){
        cout << "|  " << setw(2) << i << "  |  " << setw(4) << bucket[i].value << "  |  " << bucket[i].hop[0] << bucket[i].hop[1] << bucket[i].hop[2] << bucket[i].hop[3] << "  |\n";
    }
    cout << "+------------------------+" << endl;
}

// Generates and returns hashValue for a given value
int hashValue(int value) {
    return value % TABLE_SIZE;
}