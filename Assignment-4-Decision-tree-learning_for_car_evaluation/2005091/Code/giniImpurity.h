double calculateGiniImpurity(vector<Car>& dataset) {
    int totalRows = dataset.size();
    if (totalRows == 0) return 0.0;
    map<string, int> classCounts;
    for (auto& car : dataset) {
        classCounts[car.decision]++;
    }
    double gini = 1.0;
    for (auto& pair : classCounts) {
        double probability = (double)pair.second / (double)totalRows;
        gini -= probability * probability;
    }
    return gini;
}

double calculateWeightedGiniForAttribute(vector<Car>& dataset, string& attribute) {
    double weightedGini = 0.0;
    set<string> uniqueValues;
    for (auto& car : dataset) {
        uniqueValues.insert(car.attributes.at(attribute));
    }
    for (auto& value : uniqueValues) {
        vector<Car> subset;
        for (auto& car : dataset) {
            if (car.attributes.at(attribute) == value) {
                subset.push_back(car);
            }
        }
        weightedGini += ((double)subset.size() / (double)dataset.size()) * calculateGiniImpurity(subset);
    }
    return weightedGini;
}

string selectBestAttributeGINI(vector<Car>& dataset, vector<string>& attributes) {
    string bestAttribute;
    double lowestGini = 2.0;
    for (string& attribute : attributes) {
        double gini = calculateWeightedGiniForAttribute(dataset, attribute);
        if (gini < lowestGini) {
            lowestGini = gini;
            bestAttribute = attribute;
        }
    }
    return bestAttribute;
}


string selectRandomlyFromTopThreeAttributesGINI(vector<Car>& cars, vector<string>& attributes) {
    vector<pair<double, string>> attributeGinis;
    for (string& attr : attributes) {
        double gini = calculateWeightedGiniForAttribute(cars, attr);
        attributeGinis.push_back({gini, attr});
    }
    sort(attributeGinis.begin(), attributeGinis.end());
    int randomIndex=rnd()%3;
    if(attributeGinis.size()<3)return attributeGinis[0].second;
    return attributeGinis[randomIndex].second;
}