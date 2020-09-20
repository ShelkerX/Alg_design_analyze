#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

const int MAXL = 100000000;
const int MININF = numeric_limits<int>::min();
int arr[MAXL];

int maxseqsum_exhaust(const int *arr, const int len);
int maxseqsum_improve_exhaust(const int *arr, const int len);
int maxseqsum_divide(const int *arr, const int len);
int maxseqsum_dp(const int *arr, const int len);
int maxseqsum_timetest(const int *arr, const int len);

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        int type = atoi(argv[1]);
        ifstream arrs(argv[2], ios::in | ios::binary);
        vector<int> vint;

        int tmp;
        while (!arrs.eof())
        {
            arrs >> tmp;
            vint.push_back(tmp);
        }

        if (vint.size())
        {
            int len = (vint.size() < MAXL) ? vint.size() : MAXL;
            for (int i = 0; i < len; i++)
                arr[i] = vint[i];

            int maxseqsum = MININF;
<<<<<<< HEAD
            //us clock
            float usd;
            LARGE_INTEGER cpuf;
            LARGE_INTEGER sst, eet;
            QueryPerformanceFrequency(&cpuf);
            //get delta time
            QueryPerformanceCounter(&sst);
            maxseqsum_timetest(arr,len);
            QueryPerformanceCounter(&eet);
            usd = (eet.QuadPart - sst.QuadPart)*1000000.0f / cpuf.QuadPart;

            QueryPerformanceCounter(&sst);
            
=======
            clock_t st, et;
            st = clock();
>>>>>>> parent of 23aa365... us timer complete
            switch (type)
            {
            case 0:
                maxseqsum = maxseqsum_exhaust(arr, len);
                break;
            case 1:
                maxseqsum = maxseqsum_improve_exhaust(arr, len);
                break;
            case 2:
                maxseqsum = maxseqsum_divide(arr, len);
                break;
            case 3:
                maxseqsum = maxseqsum_dp(arr, len);
                break;
            }
<<<<<<< HEAD
            QueryPerformanceCounter(&eet);
            
            float us, ms, s;
            us = (eet.QuadPart - sst.QuadPart)*1000000.0f / cpuf.QuadPart - usd;
            ms = us/1000.0f;
            s = ms/1000.0f;
=======
            et = clock();

>>>>>>> parent of 23aa365... us timer complete
            string types[4] = {"maxseqsum_exhaust", "maxseqsum_improve_exhaust", "maxseqsum_divide", "maxseqsum_dp"};
            cout << "Function " << types[type] << " takes " << (double)(((long long)et) - ((long long)st)) / CLOCKS_PER_SEC << "s to finish the process." << endl;
            cout << "Answer is " << maxseqsum << "." << endl;
        }
        else
            cout << "The array is empty." << endl;
    }
    else
        cout << "Parameter wrong." << endl;
    return 0;
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