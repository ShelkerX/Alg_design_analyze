#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    if (argc == 5)
    {
        int len, min, max;
        len = atoi(argv[1]);
        min = atoi(argv[2]);
        max = atoi(argv[3]);
        string add = argv[4];
        ofstream fp(add, ios::out | ios::binary);
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
    }

    return 0;
}