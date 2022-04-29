#include<iostream>
#include<fstream>
#include <string>
using namespace std;

int main() {
    fstream dataFile;
    cout << "------------- TOTAL TIMES ---------------" << endl;
    dataFile.open("../../../data.txt", ios::in);
    string beeline, astar, dfs, dijkstra;
    if(dataFile.is_open()) {

       
        //cout << "opened file for reading" << endl;
        /* FILE STRUCTURE

        int (time for Beeline)
        int (time for Astar)
        int (time for DFS)
        int (time for Dijkstra)

        */
        getline(dataFile, beeline);
        getline(dataFile, astar);
        getline(dataFile, dfs);
        getline(dataFile, dijkstra);

        dataFile.close();
    }

    // output times

    cout << "BEELINE TIME: " << beeline << " seconds" << endl;
    cout << "ASTAR TIME: " << astar << " seconds" << endl;
    cout << "DFS TIME: " << dfs << " seconds" << endl;
    cout << "DIJKSTRA TIME: " << dijkstra << " seconds" << endl;

    // COMPARING TO BEELINE
    cout << "------------- DATA ANALYSIS --------------" << endl;
    double diff;

    diff = stod(beeline)/stod(astar);

    cout << "BEELINE is " << diff << " times faster than ASTAR" << endl;
    diff = stod(beeline)/stod(dfs);
    cout << "BEELINE is " << diff << " times faster than DFS" << endl;
    diff = stod(beeline)/stod(dijkstra);
    cout << "BEELINE is " << diff << " times faster than DIJKSTRA" << endl;
    cout << "------------------------------------------" << endl;

}
