#include <bits/stdc++.h>
using namespace std;
#define ll long long
mt19937 rnd(time(0));
vector<string>attributesTypes={"buying","maint","doors","persons","lug_boot","safety"};

struct Node{
    map<string,Node>toNode;
    string decision,pathAttribute;
};
struct Car{
    map<string,string>attributes;
    string decision;
};

map<string,vector<string>>trackAttributes;



#include "informationGain.h"
#include "giniImpurity.h"

string getMajorityLabel(vector<Car>& cars){
    map<string,int>labelCount;
    for(auto& car:cars){
        labelCount[car.decision]++;
    }
    string majorityLabel;
    int maxCount=0;
    for(auto& labelCountPair:labelCount){
        if(labelCountPair.second>maxCount){
            maxCount=labelCountPair.second;
            majorityLabel=labelCountPair.first;
        }
    }
    return majorityLabel;
}

bool allExamplesHaveSameLabel(vector<Car>& cars){
    if (cars.empty())return true;
    string firstLabel=cars[0].decision;
    for(auto& car:cars){
        if(car.decision!=firstLabel)return false;
    }
    return true;
}



Node buildDecisionTree(vector<Car>& cars,vector<string>& attributes,vector<Car>& parentDataset,int num){
    Node node;
    if(cars.empty()){
        node.decision=getMajorityLabel(parentDataset);
    }
    else if(allExamplesHaveSameLabel(cars)){ 
        node.decision=cars[0].decision;
    }
    else if(attributes.empty()){
        node.decision=getMajorityLabel(cars);
    }
    else {
        string bestAttribute;
        if(num==1)bestAttribute=selectBestAttribute(cars,attributes);
        else if(num==2)bestAttribute=selectRandomlyFromTopThreeAttributes(cars,attributes);
        else if(num==3)bestAttribute=selectBestAttributeGINI(cars,attributes);
        else if(num==4)bestAttribute=selectRandomlyFromTopThreeAttributesGINI(cars,attributes);
        node.pathAttribute=bestAttribute;

        map<string,vector<Car>>subsets;
        vector<Car>tem;
        for(auto va:trackAttributes[bestAttribute])subsets[va]=tem;
        for(auto& car:cars){
            subsets[car.attributes[bestAttribute]].push_back(car);
        }
        vector<string>remainingAttributes=attributes;
        remainingAttributes.erase(find(remainingAttributes.begin(),remainingAttributes.end(),bestAttribute));

        for(auto& val:subsets){
            node.toNode[val.first]=buildDecisionTree(val.second,remainingAttributes,cars,num);
        }
    }
    return node;
}

string findResult(Node& root, Car& car){
    if(root.toNode.empty())return root.decision;
    string tem=car.attributes[root.pathAttribute];
    if (root.toNode.count(tem)){
        return findResult(root.toNode.at(tem),car);
    }
    return root.decision;
}


vector<Car> loadCarData(const string& fileName) {
    freopen(fileName.c_str(), "r", stdin);
    vector<Car> cars;
    string line;

    while (cin >> line) {
        Car car;
        stringstream ss(line);
        string value;
        vector<string> values;

        while (getline(ss, value, ',')) {
            values.push_back(value);
        }
        for (size_t i = 0; i < attributesTypes.size(); i++) {
            car.attributes[attributesTypes[i]] = values[i];
        }
        car.decision = values.back();
        cars.push_back(car);
    }
    return cars;
}


pair<vector<Car>, vector<Car>> partitionDataset(vector<Car>& cars, double trainRatio) {
    shuffle(cars.begin(), cars.end(), rnd);
    int splitIndex = static_cast<int>(trainRatio * cars.size());
    return {
        vector<Car>(cars.begin(), cars.begin() + splitIndex),
        vector<Car>(cars.begin() + splitIndex, cars.end())
    };
}


double evaluateAccuracy(Node& root, vector<Car>& testSet) {
    int correctPredictions = 0;
    for (Car& car : testSet) {
        if (findResult(root, car) == car.decision) {
            correctPredictions++;
        }
    }
    return (double(correctPredictions) / testSet.size()) * 100.0;
}


int main() {
    vector<string>v1={"vhigh","high","med","low"};
    trackAttributes["buying"]=v1;

    v1={"vhigh","high","med","low"};
    trackAttributes["maint"]=v1;

    v1={"2","3","4","5more"};
    trackAttributes["doors"]=v1;

    v1={"2","4","more"};
    trackAttributes["persons"]=v1;

    v1={"small","med","big"};
    trackAttributes["lug_boot"]=v1;

    v1={"low","med","high"};
    trackAttributes["safety"]=v1;


    vector<Car> cars = loadCarData("car.data");
    for(int x=20;x<100;x+=20){
        double totalAccuracyIG = 0.0,totalAccuracyT3IG=0.0,totalAccuracyGI=0.0,totalAccuracyT3GI=0.0;
        for (int i = 0; i < 20; i++) {
            auto va = partitionDataset(cars, double(x)/100.0);
            // auto va1=partitionDataset(cars,0.8);
            // cout<<double(x)/100.0<<endl;
            auto trainingData=va.first;
            auto testData=va.second;
            // while (testData.size()>20)
            // {
                
            // }
            
            vector<Car>parentData;
            Node root = buildDecisionTree(trainingData, attributesTypes, parentData,1);
            double tem1 = evaluateAccuracy(root, testData);
            totalAccuracyIG+=tem1;


            root = buildDecisionTree(trainingData, attributesTypes, parentData,2);
            double tem2 = evaluateAccuracy(root, testData);
            totalAccuracyT3IG+=tem2;

            root = buildDecisionTree(trainingData, attributesTypes, parentData,3);
            double tem3 = evaluateAccuracy(root, testData);
            totalAccuracyGI+=tem3;

            root = buildDecisionTree(trainingData, attributesTypes, parentData,4);
            double tem4 = evaluateAccuracy(root, testData);
            totalAccuracyT3GI+=tem4;
            // for(auto va:attributesTypes)cout<<va<<" ";
            // cout<<endl;
            // totalAccuracy += tem;
            // cout << "Accuracy: " << tem << "%" << endl;
            // cout<<tem1<<","<<tem3<<","<<tem2<<","<<tem4<<endl;
        }
        cout<<totalAccuracyIG/20<<","<<totalAccuracyGI/20<<","<<totalAccuracyT3IG/20<<","<<totalAccuracyT3GI/20<<endl;

    }
    // double totalAccuracyIG = 0.0,totalAccuracyT3IG=0.0,totalAccuracyGI=0.0,totalAccuracyT3GI=0.0;
    // for (int i = 0; i < 20; i++) {
    //     auto va = partitionDataset(cars, 0.8);
    //     auto trainingData=va.first;
    //     auto testData=va.second;
    //     vector<Car>parentData;
    //     Node root = buildDecisionTree(trainingData, attributesTypes, parentData,1);
    //     double tem1 = evaluateAccuracy(root, testData);
    //     totalAccuracyIG+=tem1;


    //     root = buildDecisionTree(trainingData, attributesTypes, parentData,2);
    //     double tem2 = evaluateAccuracy(root, testData);
    //     totalAccuracyT3IG+=tem2;

    //     root = buildDecisionTree(trainingData, attributesTypes, parentData,3);
    //     double tem3 = evaluateAccuracy(root, testData);
    //     totalAccuracyGI+=tem3;

    //     root = buildDecisionTree(trainingData, attributesTypes, parentData,4);
    //     double tem4 = evaluateAccuracy(root, testData);
    //     totalAccuracyT3GI+=tem4;
    //     // for(auto va:attributesTypes)cout<<va<<" ";
    //     // cout<<endl;
    //     // totalAccuracy += tem;
    //     // cout << "Accuracy: " << tem << "%" << endl;
    //     cout<<tem1<<","<<tem3<<","<<tem2<<","<<tem4<<endl;
    // }
    // cout<<totalAccuracyIG/20<<","<<totalAccuracyGI/20<<","<<totalAccuracyT3IG/20<<","<<totalAccuracyT3GI/20<<endl;
    return 0;
}
