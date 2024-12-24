
lld distanceOfTwoCity(int i,int j)
{
    lld difX=allCities[i-1].second.first-allCities[j-1].second.first;
    lld difY=allCities[i-1].second.second-allCities[j-1].second.second;
    return sqrtl(difX*difX+difY*difY);
}

lld calculateTotalCost(vector<int>&path)
{
    lld totalCost=distanceOfTwoCity(path[0],path[path.size()-1]);
    for(int i=1;i<path.size();i++)
    {
        totalCost+=distanceOfTwoCity(path[i],path[i-1]);
    }
    return totalCost;
}

void printPath(vector<int>&path)
{
    lld totalCost=calculateTotalCost(path);
    cout<<"Total Cost: "<<totalCost<<endl;
    // cout<<path[0]<<" ";
    // for(int i=1;i<path.size();i++)
    // {
    //     cout<<path[i]<<" ";
    // }
    // cout<<path[0]<<endl;
}