#include <bits/stdc++.h>
using namespace std;

int k,n,explored,expanded,totalNode;
vector<int>sourceState,destinationState,Distance,parent;
map<vector<int>,int>node;
vector<vector<int>>allStates;
vector<pair<int,int>> graph={{1,0},{-1,0},{0,1},{0,-1}};


pair<int,int> gridPos(int node)
{
    return {node/k,node%k};
}

int vectorPos(int r,int c)
{
    return r*k+c;
}



int hammingDistance(vector<int> &state)
{
    int value=0;
    for(int i=0;i<state.size()-1;i++)
    {
        if(state[i]!=destinationState[i])value++;
    }
    return value;
}


int manhattanDistance(vector<int> &state)
{
    int value = 0;
    for(int i=0;i<state.size();i++)
    {
        if(!state[i])continue;
        auto va=gridPos(i);
        auto r=va.first;
        auto c=va.second;

        auto va1=gridPos(state[i]-1);
        auto r1=va1.first;
        auto c1=va1.second;

        value+=abs(r-r1)+abs(c-c1);
    }
    return value;
}


bool isSolvable(vector<int> &state)
{
    int rowOfZero;
    for(int i=0;i<state.size();i++)
    {
        if(state[i]==0)
        {
            rowOfZero=gridPos(i).first;
        }
    }

    int inversionCount=0;
    for(int i=0;i<state.size();i++)
    {
        if(state[i]==0)continue;
        for(int j=i+1;j<state.size();j++)
        {
            if(state[j]==0)continue;
            if(state[j]<state[i])
            {
                inversionCount++;
            }
        }
    }

    if((k%2==1)&&(inversionCount%2==0))
    {
        return true;
    }
    else if((k%2==0)&&((inversionCount+(k-rowOfZero-1))%2==0))
    {
        return true;
    }
    return false;
}



void init()
{
    Distance.clear();
    parent.clear();
    node.clear();
    allStates.clear();

    Distance.push_back(0);
    Distance.push_back(INT_MAX);

    parent.push_back(-1);
    parent.push_back(-1);

    node[sourceState]=1;
    node[destinationState]=2;

    allStates.push_back(sourceState);
    allStates.push_back(destinationState);

    explored=0;
    expanded=0;
    totalNode=2;
}


void aStar(int flag)
{
    init();

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>priorityQueue;
    
    priorityQueue.push({0,0});
    while(!priorityQueue.empty())
    {
        explored++;

        auto tem=priorityQueue.top();
        priorityQueue.pop();
        int presentNode=tem.second;
        if(presentNode==1)return;
        vector<int> presentState=allStates[presentNode];


        int indexOfZero=0;
        for(auto val:allStates[presentNode])
        {
            if(val==0)break;
            else indexOfZero++;
        }
        auto gridPosOfZero=gridPos(indexOfZero);
        auto rowOfZero=gridPosOfZero.first;
        auto callOfZero=gridPosOfZero.second;
        for(auto val:graph)
        {
            auto destinationRowOfZero=rowOfZero+val.first;
            auto destinationCallOfZero=callOfZero+val.second;


            if((destinationRowOfZero>=0)&&(destinationRowOfZero<k)&&(destinationCallOfZero>=0)&&(destinationCallOfZero<k))
            {
                int nextIndexOfZero=vectorPos(destinationRowOfZero,destinationCallOfZero);

                vector<int>nextState=presentState;
                swap(nextState[indexOfZero],nextState[nextIndexOfZero]);
                
                if(!node[nextState])
                {
                    allStates.push_back(nextState);
                    Distance.push_back(INT_MAX);
                    parent.push_back(-1);
                    totalNode++;
                    node[nextState]=totalNode;
                    
                }
                int destinationNode=node[nextState]-1;

                if((Distance[destinationNode]>1+Distance[presentNode]))
                {

                    expanded++;
                    Distance[destinationNode]=1+Distance[presentNode];
                    if(flag==0)
                    {
                        priorityQueue.push({Distance[destinationNode]+manhattanDistance(nextState),destinationNode});
                    }
                    else priorityQueue.push({Distance[destinationNode]+hammingDistance(nextState),destinationNode});
                    parent[destinationNode]=presentNode;
                }
            }
        }
    }
}


void Print(int node)
{
    vector<vector<int>> path;
    while(parent[node]!=-1)
    {
        path.push_back(allStates[node]);
        node=parent[node];
    }
    path.push_back(sourceState);
    reverse(path.begin(),path.end());

    cout<<"Minimum Moves: "<<path.size()-1<<endl;

    int move=0;
    for(auto val:path)
    {
        cout<<"Move: "<<move<<endl;
        move++;
        int a=0;
        for(int i=0;i<k;i++)
        {
            for(int j=0;j<k;j++)
            {
                if(!val[a])
                {
                    cout<<"*"<<" ";
                    a++;
                    continue;
                }
                cout<<val[a]<<" ";
                a++;
            }
            cout<<endl;
        }
        cout<<endl;
    }
}

int main()
{
    cin>>k;
    n=k*k;

    for(int i=1;i<=n;i++)
    {
        string input;
        cin>>input;
        if(input=="*")sourceState.push_back(0);
        else
        {
            int a=0;
            for(auto c:input)
            {
                a*=10;
                a+=(c-'0');
            }
            sourceState.push_back(a);
        }
    }


    if(!isSolvable(sourceState))
    {
        cout<<"Not solvable"<<endl;
        return 0;
    }

    for(int i=1;i<=n;i++)
    {
        if(i!=n)destinationState.push_back(i);
        else destinationState.push_back(0);
    }




    aStar(0);
    cout<<"Manhattan"<<endl;
    cout<<"Expanded "<<expanded<<endl;
    cout<<"Explored "<<explored<<endl;
    cout<<endl;

    aStar(1);
    cout<<"Hamming"<<endl;
    cout<<"Expanded "<<expanded<<endl;
    cout<<"Explored "<<explored<<endl;
    cout<<endl;

    Print(1);
}


// input:
// 3
// 1 2 0
// 3 4 5
// 6 7 8

// output:
// Manhattan
// Expanded 2002
// Explored 1274

// Hamming
// Expanded 12894
// Explored 8315

// Minimum Moves: 22
// Move: 0
// 1 2 * 
// 3 4 5 
// 6 7 8 

// Move: 1
// 1 * 2 
// 3 4 5 
// 6 7 8 

// Move: 2
// 1 4 2 
// 3 * 5 
// 6 7 8 

// Move: 3
// 1 4 2 
// * 3 5 
// 6 7 8 

// Move: 4
// 1 4 2 
// 6 3 5 
// * 7 8 

// Move: 5
// 1 4 2 
// 6 3 5 
// 7 * 8 

// Move: 6
// 1 4 2 
// 6 3 5 
// 7 8 * 

// Move: 7
// 1 4 2 
// 6 3 * 
// 7 8 5 

// Move: 8
// 1 4 2 
// 6 * 3 
// 7 8 5 

// Move: 9
// 1 4 2 
// * 6 3 
// 7 8 5 

// Move: 10
// 1 4 2 
// 7 6 3 
// * 8 5 

// Move: 11
// 1 4 2 
// 7 6 3 
// 8 * 5 

// Move: 12
// 1 4 2 
// 7 * 3 
// 8 6 5 

// Move: 13
// 1 * 2 
// 7 4 3 
// 8 6 5 

// Move: 14
// 1 2 * 
// 7 4 3 
// 8 6 5 

// Move: 15
// 1 2 3 
// 7 4 * 
// 8 6 5 

// Move: 16
// 1 2 3 
// 7 4 5 
// 8 6 * 

// Move: 17
// 1 2 3 
// 7 4 5 
// 8 * 6 

// Move: 18
// 1 2 3 
// 7 4 5 
// * 8 6 

// Move: 19
// 1 2 3 
// * 4 5 
// 7 8 6 

// Move: 20
// 1 2 3 
// 4 * 5 
// 7 8 6 

// Move: 21
// 1 2 3 
// 4 5 * 
// 7 8 6 

// Move: 22
// 1 2 3 
// 4 5 6 
// 7 8 * 
