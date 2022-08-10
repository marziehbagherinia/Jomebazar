#ifndef STREAMINGSERVICE_H
#define STREAMINGSERVICE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

#include "Store.h"
#include "Exceptions.h"

using namespace std;

class StreamingService
{
public:
	void run();
	vector < vector <string>> getInput();
	void actOnInput(vector <string> input);
	

private:
	Store store;
	
};

#endif