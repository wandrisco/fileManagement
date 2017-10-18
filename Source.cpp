/*
 Kristian Kilpatrick
 J00444517
 
 Corey Wandrisco
 J00486359
 
 Meshari Algumaizi
 J00553541
 
 Jordan Day
 J00466008
 
 Fernando Lorenzo
 J00612810
 
 Assigned:10-04-2017
 Due: 10-16-2017
 
 The purpose of this code is to simulate driver functions for
 our file system.
 
 **Version 1.0**
 
 */


#include <stdio.h>
#include <fstream>
#include <iostream>
#pragma warning(disable:4996)

using namespace std;

void menu(), choice(int input), EraseAllSectors(), returnMenu(), writeWord(int nAddress), EraseSector(int nSectorNr), createFile(), checkInput();

int checkAddress(int nAddress), checkSector(int nSector);

unsigned char* ReadWord(int nAddress);

int main(void) {
    
    cout << "*Creators* \n"
    << "Kristian Kilpatrick,\nCorey Wandrisco,\nMeshari Algumaizi,\nJordan Day,\n& Fernando Lorenzo\n\n";
    
    menu();
    return 0;
}
//displays menu input options

void menu() {
    int input;
    cout << "*DRIVER*\n"
    << "*MENU OPTIONS*\n\n";
    cout << "1 - Erase All Sectors\n"
    << "2 - Erase a Sector from Memory\n"
    << "3 - Read a Word from Memory\n"
    << "4 - Write a Word to Memory\n"
    << "5 - Terminate Driver\n\n";
    cout << "Enter a menu option: ";
    cin >> input;
    cin.ignore();
    cout << endl;
    choice(input);
}

//allows user to input a choice
void choice(int input) {
    int nAddress, nSector, newAddress, newSector;
    while (input) {
        switch (input) {
            case 1:
                EraseAllSectors();
                returnMenu();
                break;
                
            case 2:
                createFile();
                cout << "Enter a sector to erase from memory: ";
                cin >> nSector;
                newSector = checkSector(nSector);
                EraseSector(newSector);
                returnMenu();
                break;
                
            case 3:
                createFile();
                cout << "Enter an address location to read from: ";
                cin >> nAddress;
                newAddress = checkAddress(nAddress);
                ReadWord(newAddress);
                returnMenu();
                break;
                
            case 4:
                createFile();
                cout << "Enter an address location to write to: ";
                cin >> nAddress;
                newAddress = checkAddress(nAddress);
                writeWord(newAddress);
                returnMenu();
                break;
                
            case 5:
                exit(1);
                
                //Working on Invalid Entry Response
            default:
                cout << "Invalid Menu Option. Please enter new option: ";
                cin >> input;
                choice(input);
                cin.ignore();
                break;
        }
    }
}

//prompts user to return back to menu or repeat function
void returnMenu() {
    char input;
    cout << "Return to Main Menu? (y/n)\n";
    cin >> input;
    cout << endl;
    while (input) {
        switch (input) {
            case 'y':
                menu();
                break;
            case 'n':
                break;
        }
        break;
    }
}

//erases all sectors in the file, creates a file if one is not present
void EraseAllSectors() {
    
    createFile();
    
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    for (int i = 0; i <= (65536 * 20); ++i)
    {
        char x = ~0;
        myFile.write(&x, sizeof(char));
    }
    cout << "All sectors successfully erased\n";
}

//erase a sector from user prompt, creates a file if one is not present
void EraseSector(int nSectorNr) {
    
    //createFile();
    
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    myFile.seekp(nSectorNr * 65536);
    
    int lb = (nSectorNr * 65536);
    int hb = ((nSectorNr + 1) * 65536);
    
    for (lb; lb < hb; ++lb)
    {
        char x = ~0;
        myFile.write(&x, sizeof(char));
    }
    myFile.close();
    cout << "Sector " << (lb / 65536) - 1 << " successfully erased.\n";
}

//reads a word from an address in the file, creates a file if one is not present
unsigned char* ReadWord(int nAddress) {
    
    //createFile();
    
    char filename[] = "myfile.bin";
    unsigned char buf[2];
    unsigned char* tempWord;
    tempWord = new unsigned char[2];
    FILE *fp;
    
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Unable to open file: %s", filename);
        return NULL;
    }
    
    fseek(fp, nAddress, SEEK_SET);
    
    if (fread(buf, 1, 2, fp) == 2)
    {
        printf("%s", "The data at address ");
        printf("%i", nAddress);
        printf("%s", " Reads: ");
        printf("%02x %02x\n\n", (int)buf[0], (int)buf[1]);
        tempWord = buf;
        fclose(fp);
        return tempWord;
    }
}

//bitwise does not check, but does write, creates a file if one is not present
void writeWord(int nAddress) {
    
    //createFile();
    
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    
    if (!myFile.is_open()) {
        cout << "The file cannot be opened.\n";
        menu();
    }
    else {
        myFile.seekg(nAddress);
        char bytes[2];
        short oldWord = *ReadWord(nAddress);
        cout << "\nEnter bytes to be written to address location " << (nAddress) << ": ";
        cin >> bytes;
        short newWord = *bytes;
        newWord = newWord & oldWord;
        memcpy(bytes, &newWord, 2);
        cin.ignore();
        cout << endl;
        
        myFile.write(bytes, 2);
        
        cout << newWord << " was successfully written to address location " << (nAddress) << ".\n\n";
        myFile.close();
    }
}

//checks if the address entered is valid
int checkAddress(int nAddress) {
    int newAddress;
    
    if (nAddress % 2 != 0) {
        while (nAddress % 2 != 0 || nAddress < 0 || nAddress > 20 * 65536) {
            cout << "Invalid address \n";
            cout << "Enter a new address location: ";
            cin >> nAddress;
            newAddress = nAddress;
        }
        return newAddress;
    }
    else {
        return nAddress;
    }
}

//checks if the sector entered is valid
int checkSector(int nSector) {
    int newSector;
    
    if (nSector < 0 || nSector > 19) {
        while (nSector < 0 || nSector > 19) {
            cout << "\nInvalid sector. Enter new sector: ";
            cin >> nSector;
            cout << "\n";
            newSector = nSector;
        }
        return newSector;
    }
    else {
        return nSector;
    }
}

//creates a file if one is not already created
void createFile() {
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    
    if (!myFile.is_open()) {
        char input;
        cout << "myfile.bin does not exist. Would you like to create it?(y/n)\n";
        cin >> input;
        cout << endl;
        if (input == 'y') {
            int X = 65536 * 20;
            FILE *fp = fopen("myfile.bin", "wb");
            fseek(fp, X, SEEK_SET);
            fputc('/0', fp);
            fclose(fp);
            cout << "myfile.bin successfully created.\n\n";
        }
        else {
            cout << "myfile.bin not created. Returning to Main Menu.\n\n";
            menu();
        }
    }
    /*else {
     cout << "myfile.bin was successfully opened.\n\n";
     }*/
}

