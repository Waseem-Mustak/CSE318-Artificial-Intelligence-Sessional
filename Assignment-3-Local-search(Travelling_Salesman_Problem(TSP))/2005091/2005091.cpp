#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <dirent.h>
#include <sys/stat.h>
using namespace __gnu_pbds;
using namespace std;
#define lld double
mt19937 rnd(time(0));

int totalNumberOfCity;
vector<pair<int,pair<lld,lld>>>allCities;

#include "helper.h"
#include "nearestInsertion.h"
#include "simpleMST.h"
#include "nearestNeighbour.h"
#include "2opt.h"
#include "nodeSwap.h"
#include "nodeShift.h"



// int main()
// {
//     string input;
//     ifstream file("./testinput/ch130.tsp");
//     int line=0;
//     while(getline(file,input))
//     {
//         if(input=="EOF")break;
//         line++;
//         if(line>6)
//         {
//             stringstream temInput(input);
//             int node;
//             lld X,Y;
//             temInput>>node>>X>>Y;
//             allCities.push_back({node,{X,Y}});
//         }
//     }
//     totalNumberOfCity=allCities.size();
//     vector<int>path;
//     cout<<"nearestInsertionConstructionHeuristics"<<endl;
//     path=nearestInsertionConstructionHeuristics();
//     printPath(path);

//     cout<<"nearestNeighbourHeuristicHeuristics"<<endl;
//     path=nearestNeighbourHeuristicHeuristics();
//     printPath(path);

//     cout<<"simpleMinimumSpanningTreeBasedHeuristic"<<endl;
//     path=simpleMinimumSpanningTreeBasedHeuristic();
//     printPath(path);

    

//     cout<<"twoOptHeuristics"<<endl;
//     path=twoOptHeuristics(path);
//     printPath(path);

//     cout<<"nodeSwapHeuristics"<<endl;
//     path=nodeSwapHeuristics(path);
//     printPath(path);

//     cout<<"nodeShiftHeuristics"<<endl;
//     path=nodeShiftHeuristics(path);
//     printPath(path);
// } 



int main()
{
    ofstream csvWrite("output.csv");
    csvWrite<<"testCase,Heuristic,cost,after_2Opt,after_nodeShift,after_nodeSwap\n";
    DIR *directory = opendir("testinput");
    struct dirent *starting;
    while((starting=readdir(directory))!=nullptr)
    {
        string filename=starting->d_name;
        if (filename=="."||filename=="..")continue;
        allCities.clear();
        string input;
        ifstream file("./testinput/"+filename);
        int line=0;
        while(getline(file,input))
        {
            if(input=="EOF")break;
            line++;
            if(line>6)
            {
                stringstream temInput(input);
                int node;
                lld X,Y;
                temInput>>node>>X>>Y;
                allCities.push_back({node,{X,Y}});
            }
        }
        totalNumberOfCity=allCities.size();
        // cout<<totalNumberOfCity<<endl;

        // csvWrite<<2<<","<<3<<","<<4<<","<<5<<","<<6<<","<<7<<","<<8<<endl;

        vector<int>path;
        path=nearestInsertionConstructionHeuristics();
        vector<int>pathTwoOpt=twoOptHeuristics(path);
        vector<int>pathNodeShift=nodeShiftHeuristics(path);
        vector<int>pathNodeSwap=nodeSwapHeuristics(path);
        csvWrite<<filename<<",nearestInsertion,"<<calculateTotalCost(path)<<","<<calculateTotalCost(pathTwoOpt)
            <<","<<calculateTotalCost(pathNodeShift)<<","<<calculateTotalCost(pathNodeSwap)<<"\n";

        path=nearestNeighbourHeuristicHeuristics();
        pathTwoOpt=twoOptHeuristics(path);
        pathNodeShift=nodeShiftHeuristics(path);
        pathNodeSwap=nodeSwapHeuristics(path);
        csvWrite<<""<<",nearestNeighbour,"<<calculateTotalCost(path)<<","<<calculateTotalCost(pathTwoOpt)
            <<","<<calculateTotalCost(pathNodeShift)<<","<<calculateTotalCost(pathNodeSwap)<<"\n";

        path=simpleMinimumSpanningTreeBasedHeuristic();
        pathTwoOpt=twoOptHeuristics(path);
        pathNodeShift=nodeShiftHeuristics(path);
        pathNodeSwap=nodeSwapHeuristics(path);
        csvWrite<<""<<",simpleMST,"<<calculateTotalCost(path)<<","<<calculateTotalCost(pathTwoOpt)
            <<","<<calculateTotalCost(pathNodeShift)<<","<<calculateTotalCost(pathNodeSwap)<<"\n";
        
        file.close();
    }

    closedir(directory);
    csvWrite.close();
    return 0;
}
