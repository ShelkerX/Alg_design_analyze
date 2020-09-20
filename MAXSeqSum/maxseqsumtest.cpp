#include <iostream>
#include <ctime>
#include <string>
#include <limits>
#include <windows.h>
#include <iomanip>

using namespace std;

const int MAXL = 400000000;
const int MININF = numeric_limits<int>::min();
int arr[MAXL];

int maxseqsum_exhaust(const int *arr, const int len);
int maxseqsum_improve_exhaust(const int *arr, const int len);
int maxseqsum_divide(const int *arr, const int len);
int maxseqsum_dp(const int *arr, const int len);
int maxseqsum_timetest(const int *arr, const int len);
float maxseqsum_run(const int type, const int *arr, const int len);
void create_randarr(int *arr, const int len, const int min, const int max);

int main(int argc, char **argv)
{
    if (argc == 5)
    {
        int type = atoi(argv[1]);
        int len = atoi(argv[2]);
        int min = atoi(argv[3]);
        int max = atoi(argv[4]);

        if (type < 0 || type > 3)
            cout << "Type wrong." << endl;
        else if (len > MAXL || len < 1)
            cout << "Length wrong." << endl;
        else
        {
            float sd, us, ms, s;
            create_randarr(arr, len, min, max);
            cout << "Array created." << endl;
            for (sd = maxseqsum_run(-1, arr, len); type < 4; type++)
            {
                s = maxseqsum_run(type, arr, len) - sd;
                ms = s * 1000.0f;
                us = ms * 1000.0f;
                string types[4] = {"maxseqsum_exhaust", "maxseqsum_improve_exhaust", "maxseqsum_divide", "maxseqsum_dp"};
                cout << "Function " << types[type] << " takes " << us << "us(" << ms << "ms," << s << "s) to finish the process." << endl;
            }
        }
    }
    else
        cout << "Parameter wrong." << endl;
    return 0;
}

float maxseqsum_run(const int type, const int *arr, const int len)
{
    //us clock
    LARGE_INTEGER cpuf;
    LARGE_INTEGER sst, eet;
    QueryPerformanceFrequency(&cpuf);
    QueryPerformanceCounter(&sst);

    switch (type)
    {
    case 0:
        maxseqsum_exhaust(arr, len);
        break;
    case 1:
        maxseqsum_improve_exhaust(arr, len);
        break;
    case 2:
        maxseqsum_divide(arr, len);
        break;
    case 3:
        maxseqsum_dp(arr, len);
        break;
    default:
        maxseqsum_timetest(arr, len);
    }
    QueryPerformanceCounter(&eet);

    return (eet.QuadPart - sst.QuadPart) * 1.0f / cpuf.QuadPart;
}

int maxseqsum_exhaust(const int *arr, const int len)
{
    int cursum, maxsum;
    maxsum = MININF;
    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            cursum = 0;
            for (int k = i; k <= j; k++)
                cursum += arr[k];
            if (cursum > maxsum)
                maxsum = cursum;
        }
    }
    return maxsum;
}

int maxseqsum_improve_exhaust(const int *arr, const int len)
{
    int cursum, maxsum;
    maxsum = MININF;
    for (int i = 0; i < len; i++)
    {
        cursum = 0;
        for (int j = i; j < len; j++)
        {
            cursum += arr[j];
            if (cursum > maxsum)
                maxsum = cursum;
        }
    }
    return maxsum;
}

int maxseqsum_divide(const int *arr, const int len)
{
    if (len == 1)
        return arr[0];

    int mid = len / 2;
    int lmaxsum = maxseqsum_divide(arr, mid);
    int rmaxsum = maxseqsum_divide(arr + mid, len - mid);

    int lmaxbordersum = MININF;
    int rmaxbordersum = MININF;
    int cursum = 0;
    for (int i = mid; i >= 0; i--)
    {
        cursum += arr[i];
        if (cursum > lmaxbordersum)
            lmaxbordersum = cursum;
    }
    cursum = 0;
    for (int i = mid; i < len; i++)
    {
        cursum += arr[i];
        if (cursum > rmaxbordersum)
            rmaxbordersum = cursum;
    }
    int maxbrodersum = lmaxbordersum + rmaxbordersum - arr[mid]; //重复计算中间值，保证最大和被更新

    int maxsum;
    maxsum = lmaxsum > rmaxsum ? lmaxsum : rmaxsum;
    maxsum = maxsum > maxbrodersum ? maxsum : maxbrodersum;
    return maxsum;
}

int maxseqsum_dp(const int *arr, const int len)
{
    int cursum, maxsum;
    cursum = 0;
    maxsum = MININF;
    for (int i = 0; i < len; i++)
        if ((cursum = (cursum + arr[i] > arr[i]) ? (cursum + arr[i]) : arr[i]) > maxsum)
            maxsum = cursum;
    return maxsum;
}

int maxseqsum_timetest(const int *arr, const int len)
{
    return 0;
}

void create_randarr(int *arr, const int len, const int min, const int max)
{
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
        arr[i] = tmp;
    }
}