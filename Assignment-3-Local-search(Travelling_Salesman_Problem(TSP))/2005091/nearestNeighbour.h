

int findCityWithMinCost_(int lastAddedCity,vector<int>&unVisitedCities)
{
    lld minCost=distanceOfTwoCity(lastAddedCity,unVisitedCities[0]);
    int cityWithMinCost=unVisitedCities[0];
    
    for(auto unVisitedCity:unVisitedCities)
    {
        lld temCost=distanceOfTwoCity(unVisitedCity,lastAddedCity);
        if(temCost<minCost)
        {
            minCost=temCost;
            cityWithMinCost=unVisitedCity;
        }
    }
    return cityWithMinCost;
}

vector<int> nearestNeighbourHeuristicHeuristics()
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
        int cityWithMinCost=findCityWithMinCost_(initial_tour[initial_tour.size()-1],unVisitedCities);
        initial_tour.push_back(cityWithMinCost);

        vector<int>unVisitedCities_tem;
        for(int i=0;i<unVisitedCities.size();i++)
        {
            if(unVisitedCities[i]!=cityWithMinCost)unVisitedCities_tem.push_back(unVisitedCities[i]);
        }
        unVisitedCities=unVisitedCities_tem;
    }
    return initial_tour;
}