double computeEntropy(vector<Car>&cars){
    unordered_map<string,ll>labelCounts;
    for(auto& car:cars){
        labelCounts[car.decision]++;
    }
    double entropy=0.0;
    for(auto& labelCount:labelCounts){
        double probability=double(labelCount.second)/double(cars.size());
        entropy-=probability*log2(probability);
    }
    return entropy;
}



double computeInformationGain(vector<Car>& cars,string& attribute) {
    double currentEntropy=computeEntropy(cars);

    map<string,vector<Car>>subsets;
    for(auto& car:cars){
        subsets[car.attributes[attribute]].push_back(car);
    }

    double weightedEntropy=0.0;
    for(auto& va:subsets){
        weightedEntropy+=(double(va.second.size())/double(cars.size()))*computeEntropy(va.second);
    }
    return currentEntropy-weightedEntropy;
}

string selectBestAttribute(vector<Car>& cars,vector<string>& attributes){
    string bestAttr;
    double highestGain=-1.0;
    for(string& attr:attributes){
        double gain=computeInformationGain(cars,attr);
        if(gain>highestGain){
            highestGain=gain;
            bestAttr=attr;
        }
    }
    return bestAttr;
}

string selectRandomlyFromTopThreeAttributes(vector<Car>& cars,vector<string>& attributes){
    vector<pair<double,string>>attributeGains;
    for(string& attr:attributes){
        double gain=computeInformationGain(cars,attr);
        attributeGains.push_back({gain,attr});
    }
    sort(attributeGains.begin(),attributeGains.end());
    reverse(attributeGains.begin(),attributeGains.end());
    int tem=3;
    // tem=min(tem,(int)attributeGains.size());
    int randomIndex=rnd()%tem;
    if(attributeGains.size()<3)return attributeGains[0].second;
    return attributeGains[randomIndex].second;
}