#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    //--------------------------Setup Files---
    string key;
    string inputFileName;
    string outputFileName;
    cout << "Please enter your key: " << endl;
    cin >> key;
    cout << "Please enter input file: " << endl;
    cin >> inputFileName;
    ifstream in;
    in.open(inputFileName);
    char c = in.get();
    while (in.good())
    {
        cout << c;
        c = in.get();
    }
    in.close();
    return 0;
}
