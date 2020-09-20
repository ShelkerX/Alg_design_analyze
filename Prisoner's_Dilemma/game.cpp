#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>
#include <new>

using namespace std;

const int MAXGAMER = 10000;
enum STRATEGY
{
    RANDOM,
    BETRAY,
    COOPERATION,
    DYNAMIC
};
const bool YES = 1;
const bool NO = 0;
int pro[4] = {25, 25, 25, 25};//RBCD
int DEBUG = 0;

class GAMER
{
private:
    static int tot_gamer;
    int number;
    int score;
    bool choose[MAXGAMER];
    int strategy;

public:
    GAMER(enum STRATEGY instrategy)
    {
        if (instrategy >= RANDOM && instrategy <= DYNAMIC)
        {
            number = tot_gamer++;
            strategy = (int)instrategy;
            score = 0;
            switch (instrategy)
            {
            case RANDOM:
            case BETRAY:
            {
                for (int i = 0; i < MAXGAMER; i++)
                    choose[i] = NO;
            }
            break;
            case COOPERATION:
            case DYNAMIC:
            {
                for (int i = 0; i < MAXGAMER; i++)
                    choose[i] = YES;
            }
            break;
            }
        }
        else
            cout << "Wrong strategy, this gamer need to be delete!" << endl;
    }
    ~GAMER() {}
    int get_number() const { return number; }
    int get_score() const { return score; }
    int get_strategy() const { return strategy; }
    bool get_choose(int opp) const { return choose[opp]; }

    string tran_choose(bool cho) const
    {
        return cho ? "YES" : "NO";
    }
    string tran_strategy(int instrategy)
    {
        string strategy_str[4] = {"R", "B", "C", "D"};
        return strategy_str[instrategy];
    }

    bool ran_choose() const
    {
        bool cho = (rand() % 2 == 1);
        // cout << "rand answer is " << cho << endl;
        return cho;
    }

    void add_score(int n)
    {
        score += n;
    }
    void change_choose(bool cho, int opp)
    {
        if (strategy == RANDOM || strategy == DYNAMIC)
            choose[opp] = cho;
    }
    void meet(GAMER *opp)
    {

        bool my_cho;
        switch (strategy)
        {
        case RANDOM:
            choose[opp->get_number()] = my_cho = ran_choose();
            break;
        case BETRAY:
            my_cho = NO;
            break;
        case COOPERATION:
            my_cho = YES;
            break;
        case DYNAMIC:
            my_cho = choose[opp->get_number()];
            break;
        }

        bool opp_cho = opp->bemet(my_cho, this);
        if (my_cho == YES && opp_cho == YES)
            add_score(3);
        else if (my_cho == NO && opp_cho == NO)
            add_score(1);
        else if (my_cho == NO && opp_cho == YES)
            add_score(5);

        if (strategy == DYNAMIC)
            choose[opp->get_number()] = opp_cho;

        #if DEBUG
        cout << number << "(" << tran_strategy(strategy) << ") meet " << opp->get_number() << "(" << tran_strategy(opp->get_strategy()) << "). Their choose are (" << tran_choose(my_cho) << "," << tran_choose(opp_cho) << ")" << endl;
        #endif
    }
    bool bemet(bool opp_cho, GAMER *opp)
    {
        bool my_cho;
        switch (strategy)
        {
        case RANDOM:
            choose[opp->get_number()] = my_cho = ran_choose();
            break;
        case BETRAY:
            my_cho = NO;
            break;
        case COOPERATION:
            my_cho = YES;
            break;
        case DYNAMIC:
            my_cho = choose[opp->get_number()];
            break;
        }

        if (my_cho == YES && opp_cho == YES)
            add_score(3);
        else if (my_cho == NO && opp_cho == NO)
            add_score(1);
        else if (my_cho == NO && opp_cho == YES)
            add_score(5);

        if (strategy == DYNAMIC)
            choose[opp->get_number()] = opp_cho;

        return my_cho;
    }
};

int GAMER::tot_gamer = 0;

GAMER **gamer_init(int tot_gamer)
{
    srand((int)time(NULL));
    GAMER **List = (GAMER **)operator new(sizeof(GAMER*) * tot_gamer);
    int range_ran = pro[0];
    int range_bet = pro[1] + range_ran;
    int range_coop = pro[2] + range_bet;
    int range_num;
    for (int i = 0; i < tot_gamer; i++)
    {
        range_num = rand() % 100;
        if (range_num < range_ran)
            List[i] = new GAMER(RANDOM);
        else if (range_num < range_bet)
            List[i] = new GAMER(BETRAY);
        else if(range_num < range_coop)
            List[i] = new GAMER(COOPERATION);
        else
            List[i] = new GAMER(DYNAMIC);
    }
    return List;
}

void gamer_delete(GAMER **List, int tot_gamer)
{
    for(int i=0; i<tot_gamer; i++)
        delete List[i];
    delete[] List;
}

int main(int argc, char **argv)
{
    if (argc == 8)
    {
        int round = atoi(argv[1]);
        int tot_gamer = atoi(argv[2]);
        DEBUG = atoi(argv[3]);
        pro[0] = atoi(argv[4]);
        pro[1] = atoi(argv[5]);
        pro[2] = atoi(argv[6]);
        pro[3] = atoi(argv[7]);
        GAMER **List = gamer_init(tot_gamer);
        int i, j;
        while (round--)
        {
            #if DEBUG
            cout << "round " << round + 1 << endl;
            #endif
            for (i = 0; i < tot_gamer; i++)
            {
                for (j = 0; j < tot_gamer; j++)
                    if (i != j)
                        List[i]->meet(List[j]);
            }
            #if DEBUG
            cout << endl;
            #endif
        }

        for (i = 0; i < tot_gamer; i++)
            cout << "Gamer " << List[i]->get_number() << "(" <<List[i]->tran_strategy(List[i]->get_strategy()) << ") has " << List[i]->get_score() << " score." << endl;

        gamer_delete(List, tot_gamer);
    }
    else
        cout << "Wrong input!" << endl;

    return 0;
}