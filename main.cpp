#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    //--------------------------Setup Files---
    string key;
    string inputFileName;
    string outputFileName = "output.txt";
    char *read = new char[2];
    // cout << "Please enter your key: " << endl;
    // cin >> key;
    // cout << "Please enter input file: " << endl;
    // cin >> inputFileName;
    inputFileName = "input.txt";
    ifstream in;
    ofstream out;
    long inSize;
    in.open(inputFileName);
    out.open(outputFileName);

    in.seekg(0, in.end);
    inSize = in.tellg();
    in.seekg(0);
    bool oddFlag = (inSize % 2 == 1);

    if (oddFlag)
    {
        inSize -= 1;
    }

    for (int c = 0; c < inSize; c += 2)
    {
        in.read(read, 2);
        out.write(read, 2);
    }
    if (oddFlag)
    {
        in.read(read, 1);
        read[1] = 0;
        out.write(read, 1);
    }
    in.close();
    return 0;
}
