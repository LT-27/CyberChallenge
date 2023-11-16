#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void checkWord(vector<string> &matrix, string &corretta, int N, int Q, vector<int> &punteggi);

int main(int argc, char **argv)
{
    vector<string> matrix;
    int Q;
    int N;
    string corretta;

    ifstream input(argv[1]);
    ofstream output("output.txt");

    
    string parola;

    input >> Q >> N;
    input >> corretta;

    vector<int> punteggi(N);

    while(input >> parola)
    {
        matrix.push_back(parola);
    }

    checkWord(matrix, corretta, N, Q, punteggi);

    for(int i=0; i<N; i++)
    {
        output << punteggi[i] << endl;
    }
    
    input.close();
    output.close();
    
    return 0;
}

void checkWord(vector<string> &matrix, string &corretta, int N, int Q, vector<int> &punteggi)
{
    
    for(int i=0; i<Q; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(matrix[j][i] == corretta[i])
            {
                punteggi[j]++;
            }
        }
    }
}