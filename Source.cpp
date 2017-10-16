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

void menu(), choice(int input), EraseAllSectors(), returnMenu(), writeWord(int nAddress), EraseSector(int nSectorNr), createFile();

int checkAddress(int nAddress);

unsigned char* ReadWord(int nAddress);

int main(void) {
    
    cout << "Creators: \n"
    << "Kristian Kilpatrick\nCorey Wandrisco\nMeshari Algumaizi\nJordan Day\n& Fernando Lorenzo\n\n";
    
    menu();
    return 0;
}
//displays menu input options
void menu() {
    int input;
    cout << "*****DRIVER*************\n"
    << "*****MENU OPTIONS*******\n\n";
    cout << "1 - Erase All Sectors\n"
    << "2 - Erase a Sector from Memory\n"
    << "3 - Read a Word from Memory\n"
    << "4 - Write a Word to Memory\n"
    << "5 - Terminate Driver\n\n";
    cout << "Enter A Menu Option: ";
    cin >> input;
    cin.ignore();
    cout << endl;
    choice(input);
}

//allows user to input a choice
void choice(int input) {
    int nAddress, nSector, nnAddress;
    while (input != 5) {
        switch (input) {
            case 1:
                EraseAllSectors();
                returnMenu();
                break;
                
            case 2:
                cout << "Enter a sector to erase from memory: ";
                cin >> nSector;
                while (nSector < 0 || nSector >19)
                {
                    cout << "\nInvalid sector. Try again: ";
                    cin >> nSector;
                    cout << "\n";
                }
                EraseSector(nSector);
                returnMenu();
                break;
                
            case 3:
                cout << "Enter an address location to read from: ";
                cin >> nAddress;
                nnAddress = checkAddress(nAddress);
                ReadWord(nnAddress);
                returnMenu();
                break;
                
            case 4:
                cout << "Enter an address location to write to: ";
                cin >> nAddress;
                nnAddress = checkAddress(nAddress);
                writeWord(nnAddress);
                returnMenu();
                break;
                
            case 5:
                cout << "DRIVER TERMINATED.";
                break;
                
                //Working on Invalid Entry Response
            default:
                cout << "Invalid Entry. Please enter new option: ";
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
    while (input != 3) {
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
    cout << "All sectors successfully erased\n\n";
}

//erase a sector from user prompt, creates a file if one is not present
void EraseSector(int nSectorNr) {
    
    createFile();
    
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    myFile.seekp(nSectorNr * 65536);
    
    int lb = nSectorNr * 65536;
    int hb = ((nSectorNr + 1) * 65536);
    
    for (lb; lb < hb; ++lb)
    {
        char x = ~0;
        myFile.write(&x, sizeof(char));
    }
    myFile.close();
    cout << "Sector " << (lb / 65536) - 1 << " successfully erased.\n\n";
}

//reads a word from an address in the file, creates a file if one is not present
unsigned char* ReadWord(int nAddress) {
    
    createFile();
    
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
    
    createFile();
    
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
    int nnAddress;
    
    if (nAddress % 2 != 0) {
        while (nAddress % 2 != 0 || nAddress < 0 || nAddress > 20 * 65536) {
            cout << "Invalid address \n";
            cout << "Enter a new address location: ";
            cin >> nAddress;
            nnAddress = nAddress;
        }
        return nnAddress;
    }
    else {
        return nAddress;
    }
}

//creates a file if one is not already created
void createFile() {
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    
    if (!myFile.is_open()) {
        int X = 65536 * 20;
        FILE *fp = fopen("myfile.bin", "wb");
        fseek(fp, X, SEEK_SET);
        fputc('/0', fp);
        fclose(fp);
        EraseAllSectors();
    }
}
