#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct taskNode{
    int id;
    string flag;
    int points;
};

struct submissionsNode{
    int id;
    int tid;
    string flag;
    int time;
};

struct playerNode{
    int id;
    int points;
    vector<int> time;
    vector<int> flagVector;
};

bool checkFlag(string pflag, string tflag);
bool comparePlayers(const playerNode &a, const playerNode &b);
bool containFlags(vector<int> vect, int tid);

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int M, N, S;
    input >> M >> N >> S;

    vector<taskNode> tasks(N);
    vector<submissionsNode> submissions(S);
    vector<playerNode> players(M);
    for(auto& player : players)
    {
        player.flagVector.resize(N);
        player.time.resize(N);
    }

    taskNode taskStruct;

    for(int i=0; i<N; i++)
    {
        input >> taskStruct.id;
        input >> taskStruct.flag;
        input >> taskStruct.points;
        tasks.at(i) = taskStruct;
    }

    submissionsNode submissionsStruct;

    for(int j=0; j<S; j++)
    {
        input >> submissionsStruct.id;
        input >> submissionsStruct.tid;
        input >> submissionsStruct.flag;
        input >> submissionsStruct.time;

        if(checkFlag(submissionsStruct.flag, tasks[submissionsStruct.tid-1].flag))
        {
            if(players[submissionsStruct.id-1].flagVector[submissionsStruct.tid-1] == 0)
            {
                players[submissionsStruct.id-1].flagVector[submissionsStruct.tid-1] = submissionsStruct.tid;
                players[submissionsStruct.id-1].id = submissionsStruct.id;
                players[submissionsStruct.id-1].points += tasks[submissionsStruct.tid-1].points;
                players[submissionsStruct.id-1].time[submissionsStruct.tid-1] = submissionsStruct.time;

            } else if(players[submissionsStruct.id-1].flagVector[submissionsStruct.tid-1] == submissionsStruct.tid)
            {
                if(players[submissionsStruct.id-1].time[submissionsStruct.tid-1] > submissionsStruct.time)
                {
                    players[submissionsStruct.id-1].time[submissionsStruct.tid-1] = submissionsStruct.time;
                }
            }   
        }
    }

    for(int i=0; i<players.size(); i++)
    {
        if(players[i].id == 0)
        {
            players[i].id = i+1;
        }
        sort(players[i].time.begin(), players[i].time.end(), greater<>());
    }
    
    sort(players.begin(), players.end(), comparePlayers);

    for(int i = 0; i < players.size(); i++)
    {
        output << players[i].id << " " << players[i].points << endl;
    }

    input.close();
    output.close();

    return 0;
}

bool checkFlag(string pflag, string tflag)
{
    bool check=true;

    for(int i=0; i<10; i++)
    {
        if(pflag[i] != tflag[i])
        {
            check=false;
            i=10;
        }
    }
    return check;
}

bool comparePlayers(const playerNode &a, const playerNode &b)
{
    if (a.points != b.points)
    {
        return a.points > b.points;
    }
    else if (a.time != b.time)
    {
        return a.time < b.time;
    }
    else
        return a.id < b.id;
}

bool containFlags(vector<int> vect, int tid)
{
    bool check=true;
    if(vect[tid-1] == tid)
    {
        check=false;
    }
    return check;
}
