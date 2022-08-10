#include "User.h"

User::User(int _id, string _email, string _username, string _password)
: id(_id), email(_email), username(_username), password(_password)
{
	wallet.push_back(0);
} 

bool User::findUser(map <string, string> informations)
{
	if (informations[EMAIL] == email && informations[PASSWORD] == password)
		return true;
	return false;
}

int User::getID()
{
	return id;
}

void User::submitCart(double payableAmount)
{

}

string User::getUsername()
{
	return username;
}

/*
int User::get()
{
	return id;
}

void User::addToCart(Product* product, int offerId, int amount, int discountCode)
{

}*/
