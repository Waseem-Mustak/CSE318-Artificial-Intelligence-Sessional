

int findCityWithMinCost(vector<int>&visitedCities,vector<int>&unVisitedCities)
{
    lld minCost=distanceOfTwoCity(visitedCities[0],unVisitedCities[0]);
    int cityWithMinCost=unVisitedCities[0];
    
    for(auto unVisitedCity:unVisitedCities)
    {
        
        lld temCost=distanceOfTwoCity(unVisitedCity,visitedCities[0]);
        for(auto visitedCity:visitedCities)
        {
            lld cost=distanceOfTwoCity(unVisitedCity,visitedCity);
            if(cost<temCost)temCost=cost;
        }
        if(temCost<minCost)
        {
            minCost=temCost;
            cityWithMinCost=unVisitedCity;
        }
    }
    return cityWithMinCost;
}

int findPosToAddCity(vector<int>&initial_tour,int cityWithMinCost)
{
    lld costToReduce=distanceOfTwoCity(initial_tour[0],initial_tour[initial_tour.size()-1]);
    costToReduce-=distanceOfTwoCity(initial_tour[0],cityWithMinCost);
    costToReduce-=distanceOfTwoCity(cityWithMinCost,initial_tour[initial_tour.size()-1]);
    int pos=0;
    for(int i=1;i<initial_tour.size();i++)
    {
        lld temCost=distanceOfTwoCity(initial_tour[i],initial_tour[i-1]);
        temCost-=distanceOfTwoCity(initial_tour[i],cityWithMinCost);
        temCost-=distanceOfTwoCity(cityWithMinCost,initial_tour[i-1]);
        if(temCost>costToReduce)  // greaterthen because it will be subtracted from actual cost of whole tour
        {
            costToReduce=temCost;
            pos=i;
        }
    }
    return pos;
}

vector<int> nearestInsertionConstructionHeuristics()
{
    int startingCity=rnd();
    startingCity=(((startingCity%totalNumberOfCity)+totalNumberOfCity)%totalNumberOfCity)+1;

    vector<int>initial_tour;
    initial_tour.push_back(startingCity);

    vector<int>unVisitedCities;
    for(int i=1;i<=totalNumberOfCity;i++)
    {
        if(i!=startingCity)unVisitedCities.push_back(i);
    }
    

    while(initial_tour.size()<totalNumberOfCity)
    {
        int cityWithMinCost=findCityWithMinCost(initial_tour,unVisitedCities);
        
        int posToAdd=findPosToAddCity(initial_tour,cityWithMinCost);

        vector<int>initial_tour_tem;
        for(int i=0;i<posToAdd;i++)initial_tour_tem.push_back(initial_tour[i]);
        initial_tour_tem.push_back(cityWithMinCost);
        for(int i=posToAdd;i<initial_tour.size();i++)initial_tour_tem.push_back(initial_tour[i]);
        initial_tour=initial_tour_tem;

        vector<int>unVisitedCities_tem;
        for(int i=0;i<unVisitedCities.size();i++)
        {
            if(unVisitedCities[i]!=cityWithMinCost)unVisitedCities_tem.push_back(unVisitedCities[i]);
        }
        unVisitedCities=unVisitedCities_tem;
    }
    return initial_tour;
}