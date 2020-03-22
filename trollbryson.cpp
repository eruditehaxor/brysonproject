#include <iostream>
#include <fstream>
using namespace std;

int main()
    {
        ofstream openFile;
        openFile.open("items.txt");
        for (int i = 0; i < 1000; i++)
            {
                openFile << "Bryson is a bitch" << endl;
            }
        return 0;
    }