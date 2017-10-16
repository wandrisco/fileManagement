/*
 
 Kristian Kilpatrick
 J00444517
 
 Corey Wandrisco
 J00486359
 
 User 3
 J
 
 Fernando Lorenzo
 J00612810
 
 Assigned:10-04-2017
 Due: 10-17-2017
 
 The purpose of this code is to simulate driver functions for
 our file system.
 
 */

#include <stdio.h>
#include <fstream>
#include <iostream>


using namespace std;

void menu(), choice(int input), EraseAllSectors(), returnMenu(), writeWord(int nAddress), EraseSector(int nSectorNr);
int checkAddress(int nAddress);
char* ReadWord(int nAddress);

//Creates a file that is 20*64k bytes long
int main(void) {
    
    menu();
    
    return 0;
}

void menu(){
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

void choice(int input) {
    int nAddress, nSector, nnAddress, nnnAddress;
    while (input != 5){
        switch (input) {
            case 1:
                EraseAllSectors();
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
                break;
                
            case 3:
                cout << "Enter an address location to read from: ";
                cin >> nAddress;
                nnAddress = checkAddress(nAddress);
                ReadWord(nnAddress);
                break;
                
            case 4:
                cout << "Enter an address location to write to: ";
                cin >> nAddress;
                nnAddress = checkAddress(nAddress);
                writeWord(nnAddress);
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

void returnMenu(){
    char input;
    cout << "Return to Main Menu? (y/n)\n";
    cin >> input;
    cout << endl;
    while (input = 'y'){
        menu();
    }
}

void EraseAllSectors() {
    int X = 65536 * 20;
    FILE *fp = fopen("myfile.bin", "wb");
    fseek(fp, X, SEEK_SET);
    fputc('/0', fp);
    fclose(fp);
    
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    for (int i = 0; i <= (65536 * 20); ++i)
    {
        char x = ~0;
        myFile.write(&x, sizeof(char));
    }
    cout << "All sectors successfully erased\n\n";
    returnMenu();
}

void EraseSector(int nSectorNr) {
    
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    myFile.seekp(nSectorNr * 65536);
    
    int lb = nSectorNr * 65536;
    int hb = ((nSectorNr + 1) * 65536);
    
    for (lb; lb < hb; ++lb)
    {
        char x = 1;
        myFile.write(&x, sizeof(char));
    }
    
    cout << "Sector " << (lb / 65536) - 1 << " successfully erased\n\n";
    returnMenu();
}

char* ReadWord(int nAddress) {
    
    char filename[] = "myfile.bin";
    unsigned char buf[2];
    FILE *fp;
    
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Unable to open file: %s", filename);
        return 0;
    }
    
    fseek(fp, nAddress, SEEK_SET);
    
    if (fread(buf, 1, 2, fp) == 2)
    {
        printf("%s", "The data at address ");
        printf("%i", nAddress);
        printf("%s", " Reads: ");
        printf("%02x %02x\n\n", (int)buf[0], (int)buf[1]);
        
        returnMenu();
    }
    
    fclose(fp);
}
//writeWord just needs a little touch up. Not successfully writing byte, and only writes one byte

void writeWord(int nAddress) {
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    
    if (!myFile.is_open()){
        cout << "The file cannot be opened.\n";
        menu();
    }
    else {
        myFile.seekp(nAddress);
        char bytes[2];
        
        cout << "Enter bytes to be written to address location " << (nAddress - 1) << ": ";
        cin >> bytes;
        cin.ignore();
        cout << endl;
        
        myFile.write(bytes, 2);
        
        cout << bytes << " was successfully written to address location " << (nAddress - 1) << ".\n\n";
        returnMenu();
    }
}


int checkAddress(int nAddress) {
    int nnAddress;
    
    if (nAddress % 2 != 0) {
        while (nAddress % 2 != 0) {
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
