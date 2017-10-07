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
#pragma warning(disable:4996)

using namespace std;

void menu(), choice(int input), EraseAllSectors(), returnMenu();
int EraseSector(int nSectorNr), ReadWord(int nAddress), writeWord(int nAddress);

//Creates a file that is 20*64k bytes long
int main(void) {
    int X = 64000 * 20;
    FILE *fp = fopen("myfile.bin", "wb");
    fseek(fp, X, SEEK_SET);
    fputc('/0', fp);
    fclose(fp);


    menu();

    return 0;
}
/*When a menu option is called and then the returnMenu is called,
 * when selecting to terminate driver the program reruns the function called prior to returnMenu*/  
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
    int nAddress;
    while (input != 5){
        switch (input) {
            case 1:
                EraseAllSectors();
                break;
            case 2:
                cout << "Enter a Sector to Erase from Memory: ";
                cin >> nAddress;
                EraseSector(nAddress);
                break;
            case 3:
                cout << "Enter an Address to Read From: ";
                cin >> nAddress;
                while (nAddress % 2 != 0)
                {
                    cout << "Invalid address \n";
                    cout << "Enter a New Address: ";
                    cin >> nAddress;
                }
                ReadWord(nAddress);
                break;
            case 4:
                cout << "Enter an Address to Write to: ";
                cin >> nAddress;
                writeWord(nAddress);
                break;
            //Working on Invalid Entry Response
            default:
                cout << "Invalid Entry. Please Enter New Option: ";
                cin >> input;
                choice(input);
                cin.ignore();
                break;
        }
    }
}

void returnMenu(){
    int n;
    char input;
    cout << "Return to Main Menu? (y/n)\n";
    cin >> input;
    cout << endl;
    if (input == 'n') {
    }
    else {
        menu();
    }
}

void EraseAllSectors() {
    int X = 64000 * 20;
    FILE *fp = fopen("myfile.bin", "wb");
    fseek(fp, X, SEEK_SET);
    fputc('/0', fp);
    fclose(fp);

    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    for (int i = 0; i < (64000 * 20); ++i)
    {
        char x = ~0;
        myFile.write(&x, sizeof(char));
    }
    cout << "All Sectors Successfully Erased\n\n";
    returnMenu();
}

int EraseSector(int nSectorNr) {
    fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
    myFile.seekp(nSectorNr * 64000);

    int lb = nSectorNr * 64000;
    int hb = ((nSectorNr + 1) * 64000);

    for (lb; lb < hb; ++lb)
    {
        char x = 1;
        myFile.write(&x, sizeof(char));
    }

    cout << "Sector " << (lb / 64000) - 1 << " Successfully Erased\n\n";
    returnMenu();
    return 0;
}
int ReadWord(int nAddress) {
    char filename[] = "myfile.bin";
    unsigned char buf[2];
    FILE *fp;

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Unable to open file: %s", filename);
        return EXIT_FAILURE;
    }
    fseek(fp, nAddress, SEEK_SET);
    if (fread(buf, 1, 2, fp) == 2)
    {
        printf("%s","The Data at Address " );
        printf("%i", nAddress);
        printf("%s", " Reads: ");
        printf("%02x %02x\n\n", (int)buf[0], (int)buf[1]);

        returnMenu();
    }

    fclose(fp);
    return 0;
}

int writeWord(int nSectorNr) {
    ofstream myFile;
    myFile.open("myfile.bin", ios::out | ios::binary);
    myFile.seekp(nSectorNr * 64000);

    int lb = nSectorNr * 64000;
    int hb = ((nSectorNr + 1) * 64000);

    for (lb; lb < hb; ++lb) {
        unsigned char buf[2], bytes;
        char filename[] = "myfile.bin";
        FILE *fp;

        if ((fp = fopen(filename, "rb")) == NULL)
        {
            printf("Unable to open file: %s\n", filename);
            return EXIT_FAILURE;
        }
        fseek(fp, nSectorNr, SEEK_SET);
        if (fread(buf, 1, 2, fp) == 2)
        {
            cout << "Please enter bytes to write: ";
            cin >> bytes;
            myFile.write((char *)&bytes, sizeof(buf));

            printf("%s","The Data at Address " );
            printf("%i", nSectorNr);
            printf("%s", " Reads: ");
            printf("%02x %02x\n\n", (int)buf[0], (int)buf[1]);

            returnMenu();
        }
    }
}