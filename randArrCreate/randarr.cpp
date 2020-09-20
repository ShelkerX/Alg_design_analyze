#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int len, min, max;
    ofstream fp("arr.txt", ios::out | ios::binary);
    // cout <<argc <<endl;
    // for(int i=0; i<argc; i++)
    //     cout << argv[i] << endl;
    if (argc == 4)
    {
        len = atoi(argv[1]);
        min = atoi(argv[2]);
        max = atoi(argv[3]);
    }
    else
    {
    AGAIN:
        cout << "What`s the lenth, min num, max num of the array?" << endl;
        cin >> len >> min >> max;
        if (cin.fail())
        {
            cout << "Wrong input." << endl;
            cin.sync();
            cin.clear();
            goto AGAIN;
        }
    }

    int tmp, mod;
    mod = (abs(max) > abs(min)) ? abs(max) : abs(min);
    srand(time(NULL));
    for (int i = 0; i < len; i++)
    {
        do
        {
            tmp = rand() % mod + 1;
            tmp *= rand() % 2 ? -1 : 1;
        } while (tmp < min || tmp > max);
        fp << tmp << " ";
    }

    return 0;
}