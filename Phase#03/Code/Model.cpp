#include "Model.h"

vector< vector< string >> readDatas(string filename)
 {
 	string name = "./Data/" + filename ; 

	string line, field, firstLine;
    vector <vector <string>> helperV;  
    vector <string> gettingLine;

	ifstream myfile(name.c_str());
    if(myfile.is_open())
    {
        getline(myfile, firstLine);
        
        while (getline(myfile,line))
        {
            gettingLine.clear();
            stringstream ss(line);

            while(getline(ss,field,','))
                gettingLine.push_back(field);

            helperV.push_back(gettingLine); 
        }
    }

    helperV.pop_back();
    return helperV;
 }

 double getProb(string filename)
 {
 	string name = "./Data/" + filename;	
 	string line;

 	ifstream myfile(name.c_str());

 	if(myfile.is_open())
    {
        getline(myfile, line);
        double prob = stod(line);
    }	
 }

 map <string, double> provideModel(vector< vector< string >> helperV, int select)
 {
 	map <string, double> modelData;

 	if (select == 0)
 	{
 		for (int i = 0; i < helperV.size(); ++i)
 			modelData[helperV[i][0]] = stod(helperV[i][1]);		
 	}

 	else if (select == 1)
 	{
 		for (int i = 0; i < helperV.size(); ++i)
 			modelData[helperV[i][0]] = stod(helperV[i][2]);		
 	}

 	return modelData;
 }


vector <string> provideData(string data)
{

	vector <string> v;
	
	stringstream ss(data);

	while(ss)
	{
		string word;
		ss >> word;
		v.push_back(word);
	}

	v.pop_back();

	return v;
}

map<string, int> saveData(vector< vector< string >> tests)
{
	map<string, int> testRealScore;

	for (int i = 0; i < tests.size(); ++i)
		testRealScore[tests[i][0]] = stoi(tests[i][1]);

	return testRealScore;

}

int computePerProb(vector <string> providedTest, map <string, double> &goodProbably, 
				   map <string, double> &badProbably, double totalProb)
{
	srand ( time(NULL) );
	double goodResult = 0;
	double badResult = 0;

	for (int i = 0; i < providedTest.size(); ++i)
	{

		if (isinf(log(goodProbably[providedTest[i]])) == 1 &&
			isinf(log(badProbably[providedTest[i]])) == 1 )
		{
			continue;
		}	

		goodResult += log(goodProbably[providedTest[i]]);
		badResult += log(badProbably[providedTest[i]]);
	}

	goodResult += log(totalProb);
	badResult += log(1 - totalProb);

	if (goodResult > badResult)
	{
		return 0;
	}

	else if (goodResult < badResult)
	{
		return 1;
	}

	else if (rand()%2 == 1)
	{
		 return 1;
	}
	
	else
	{
		return 0;
	}
}

map <string, int> computeProb(map <string, int> testScore)
{
	vector <vector <string>> trains = readDatas(TRAINFLE);

 	map <string, double> goodProbably = provideModel(trains, 0);
 	map <string, double> badProbably = provideModel(trains, 1);

 	double totalProb = getProb(CLASSPROB);
 	
 	for (auto it = testScore.begin(); it != testScore.end(); ++it) 
    	testScore[it->first] = computePerProb(provideData(it->first), 
    						   goodProbably, badProbably, totalProb);

    return testScore;
}

void getReasult(map <string, int> testRealScore, map <string, int> testResult)
{
	double correctDetectedGoodCm = 0;
 	double goodCm = 0;
 	double detectedGoodCm = 0;
 	double correctDetected = 0;

 	for (auto it = testResult.begin(); it != testResult.end(); ++it) 
    {

     	if (testResult[it->first] == 0 && testRealScore[it->first] == 0 )
     		correctDetectedGoodCm++;

     	if (testRealScore[it->first] == 0)
     		goodCm++;

     	if (testResult[it->first] == 0)
     		detectedGoodCm++;

     	if (testResult[it->first] == testRealScore[it->first] )
     		correctDetected++;
    }

    double recall = (correctDetectedGoodCm/goodCm)*100;
    double precision = (correctDetectedGoodCm/detectedGoodCm)*100;
    double accuracy = (correctDetected/testRealScore.size())*100;

    cout << RECALL    << (int)recall    << PERCENT << endl;
    cout << PRECISION << (int)precision << PERCENT << endl;
    cout << ACCURACY  << (int)accuracy  << PERCENT << endl;
}