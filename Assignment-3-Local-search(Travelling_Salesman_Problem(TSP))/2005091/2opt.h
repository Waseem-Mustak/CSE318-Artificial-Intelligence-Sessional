
void twoOpt(vector<int>&initial_path)
{
    while(1)
    {
        lld initial_cost=calculateTotalCost(initial_path);
        int flag=0;
        for(int i=0;i<totalNumberOfCity;i++)
        {
            for(int j=i+1;j<totalNumberOfCity;j++)
            {
                reverse(initial_path.begin()+i,initial_path.begin()+j+1);
                lld temCost=calculateTotalCost(initial_path);
                if(temCost<initial_cost) 
                {
                    flag=1;
                    initial_cost=temCost;
                }
                else reverse(initial_path.begin()+i,initial_path.begin()+j+1);
            }
        }
        if(flag==0)break;
    }
}

vector<int> twoOptHeuristics(vector<int>initial_path)
{
    twoOpt(initial_path);
    return initial_path;
}