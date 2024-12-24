
void shiftNode(vector<int>&initial_path,int node,int pos)
{
    vector<int>tem(initial_path.size(),0);
    tem[pos]=node;
    int a=0;
    for(auto va:initial_path)
    {
        if(va!=node)
        {
            if(a==pos)a++;
            tem[a]=va;
            a++;
        }
    }
    initial_path=tem;
}


void nodeShift(vector<int>&initial_path)
{
    while(1)
    {
        lld initial_cost=calculateTotalCost(initial_path);
        int flag=0;
        for(int i=0;i<totalNumberOfCity;i++)
        {
            for(int j=0;j<totalNumberOfCity;j++)
            {
                // reverse(initial_path.begin()+i,initial_path.begin()+j+1);
                // swap(initial_path[i],initial_path[j]);
                // cout<<"L"<<endl;
                shiftNode(initial_path,initial_path[i],j);
                lld temCost=calculateTotalCost(initial_path);
                if(temCost<initial_cost) 
                {
                    flag=1;
                    initial_cost=temCost;
                }
                else
                {
                    shiftNode(initial_path,initial_path[j],i);
                }
            }
        }
        if(flag==0)break;
    }
}

vector<int> nodeShiftHeuristics(vector<int>initial_path)
{
    nodeShift(initial_path);
    return initial_path;
}