#include "StreamingService.h"

void StreamingService::run()
{
	vector < vector <string>> input;
	input = getInput();
	
	int checker = 0;

	while(checker != input.size())
	{
		actOnInput(input[checker]);
		checker++;
	}
}


vector < vector <string>> StreamingService::getInput()
{
	string line;
	vector <string> helperv;
    vector < vector <string>> input;

    while (!cin.eof())
    {
      string line;
      getline(cin, line);

      helperv.clear();
      stringstream ss(line);
      while(ss)
      {
        string word;
        ss >> word;
        helperv.push_back(word);
      }
      helperv.pop_back();
      input.push_back(helperv);
    }

    input.pop_back();
	return input;
}

void StreamingService::actOnInput(vector <string> input)
{
	
	store.actOn(input);
}