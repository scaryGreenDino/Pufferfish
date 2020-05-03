#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
typedef union key {
    char read[2];
    short bytes = 0;
};
char *P[] = {"49fe", "d3c6", "7326", "1234", "defb", "5a8b", "1e61", "77ad", "94b2", "5731"};
char *S[8][4] = {{"abcb", "7386", "6ea3", "4128"}, {"689b", "22c7", "532d", "a42b"}, {"0e52", "f025", "8724", "9ac0"}, {"776a", "629f", "4510", "3188"}, {"1111", "da99", "52bc", "dead"}, {"deaf", "beef", "5810", "7219"}, {"733b", "5ac7", "2468", "9753"}, {"8263", "820d", "e72f", "410c"}};
char *concat(char *a, char *b)
{
    char *ab = new char[4];
    for (int c = 0; c < 2; c++)
    {
        ab[c] = a[c];
    }
    for (int c = 0; c < 2; c++)
    {
        ab[c + 2] = b[c];
    }
    return ab;
}

char *xora(char *a, char *b)
{
    union key k;
    k.read[0] = a[0];
    k.read[1] = a[1];
    unsigned short c = (short)stoi(b, NULL, 16);
    k.bytes = k.bytes ^ c;
    a[0] = k.read[0];
    a[1] = k.read[1];
    return a;
}
char *xorb(char *a, char *b)
{
    union key ak;
    union key bk;

    ak.read[0] = a[0];
    ak.read[1] = a[1];

    bk.read[0] = b[0];
    bk.read[1] = b[1];
    ak.bytes = ak.bytes ^ bk.bytes;
    a[0] = ak.read[0];
    a[1] = ak.read[1];
    return a;
}
char f(char *a)
{
    return *a;
}

char *encrypt(char *a, char *b, int c)
{
    if (c == 8)
    {
        a = xora(a, P[9]);
        b = xora(b, P[8]);

        return concat(a, b);
    }
    a = xora(a, P[c]);
    char *fa = new char[2];
    *fa = f(a);
    b = xorb(fa, b);
    c++;
    return encrypt(b, a, c);
}
int main()
{

    //--------------------------Setup Files---
    // char *read = &r.read;
    // char *key = &k.read;
    char *a = new char[2];
    char *b = new char[2];
    // key[0] = 'a';
    // key[1] = 'b';
    string inputFileName;
    string outputFileName = "output.txt";
    // char *read = new char[2];
    // cout << "Please enter your key: " << endl;
    // cin >> k;
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
    int r = inSize % 4;
    inSize = inSize + (4 - r);
    char *buffer = (char *)calloc(inSize, sizeof(char));
    in.read(buffer, inSize);
    in.close();
    bool oddFlag = (inSize % 4 != 0);

    if (oddFlag)
    {
        inSize -= 1;
    }
    cout << "Plaintext:  ";
    for (int c = 0; c < inSize; c++)
    {
        printf("%c", buffer[c]);
    }

    cout << endl
         << "Ciphertext: ";

    for (int c = 0; c < inSize; c += 4)
    {
        a[0] = buffer[c];
        a[1] = buffer[c + 1];
        b[0] = buffer[c + 2];
        b[1] = buffer[c + 3];

        char *encrypted = encrypt(a, b, 0);
        printf("%c%c%c%c", encrypted[0], encrypted[1], encrypted[2], encrypted[3]);
        _sleep(1000);
    }
    // if (oddFlag)
    // {
    //     in.read(a, 2);
    //     in.read(b, 2);
    //     char *encrypted = encrypt(a, b, 0);
    //     out.write(encrypted, 1);
    //     cout << r.bytes << endl;
    // }
    free(buffer);
    out.close();
    return 0;
}
