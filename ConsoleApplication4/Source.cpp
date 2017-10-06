/*
Kristian Kilpatrick
J00444517

Other members

Assigned:10-04-2017
Due: 10-11-2017

The purpose of this code is to simulate driver functions for 
our file system. 

*/


#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;


void EraseAllSectors();
void EraseSector(int nSectorNr);

//Creates a file that is 20*64k bytes long
int main(void) {
	int X = 64000 * 20;
	int n,choice;
	FILE *fp = fopen("myfile.bin", "wb");
	fseek(fp, X, SEEK_SET);
	fputc('/0', fp);
	fclose(fp);

	cout << "Enter Menu Option: \n";
	cin >> choice;

	switch (choice)
	{

	case 1: EraseAllSectors();
		break;
	case 2:
		cout << "Enter a sector: \n";
		cin >> n;
		EraseSector(n);
		break;
	}
	return 0;
}
// idea for erase all function 
void EraseAllSectors() {
	fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
		for (int i = 0; i < (64000 * 20); ++i)
		{
			char x = ~0;
			myFile.write(&x, sizeof(char));
		}
	}

void EraseSector(int nSectorNr)
{
	
	
	fstream myFile("myfile.bin", ios::in | ios::out | ios::binary);
	

	
		int lb = nSectorNr * 64000;
		int hb = ((nSectorNr + 1) * 64000);
		for (lb; lb < hb; ++lb)
		{
			char x = 1;
			myFile.write(&x, sizeof(char));
		}
} 

