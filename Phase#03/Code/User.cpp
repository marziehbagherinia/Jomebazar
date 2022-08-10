#include "User.h"

User::User(int _id, string _email, string _username, string _password)
: id(_id), email(_email), username(_username), password(_password)
{
	wallet.push_back(0);
} 

bool User::findUser(map <string, string> informations)
{
	if (informations[USERNAME] == username && informations[PASSWORD] == password)
		return true;
	return false;
}

int User::getID()
{
	return id;
}

int User::submitCart(double payableAmount)
{
	return 0;
}

string User::getUsername()
{
	return username;
}

int User::whatIsMyType() 
{
	return 0;
}