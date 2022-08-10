#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map> 
#include <stdlib.h>
#include <ctime>
#include <bits/stdc++.h>

using namespace std; 

#define TRAINFLE "train.csv"
#define CLASSPROB "class probabilities"
#define PERCENT "%"
#define RECALL "Recall: "
#define PRECISION "Precision: "
#define ACCURACY "Accuracy: "


vector< vector< string >> readDatas(string filename);
double getProb(string filename);
map <string, double> provideModel(vector< vector< string >> helperV, int select);
vector <string> provideData(string data);
map<string, int> saveData(vector< vector< string >> tests);
int computePerProb(vector <string> providedTest, map <string, double> &goodProbably, 
				   map <string, double> &badProbably, double totalProb);
map <string, int> computeProb(map <string, int> testScore);
void getReasult(map <string, int> testRealScore, map <string, int> testResult);

#endif