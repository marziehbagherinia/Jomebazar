#include "Manager.h"

Manager::Manager(int _id, string _email, string _username, string _password)
: User(_id, _email, _username, _password)
{

}

void Manager::ableToSeller()
{
	throw PermissionDenied();
}

void Manager::ableToBuyer()
{
	throw PermissionDenied();
}

void Manager::ableToManager()
{
	
}

void Manager::chargeWallet(double amount)
{
	throw PermissionDenied();
}

double Manager::getCash()
{
	throw Server::Exception("Permission Denied");
}

void Manager::getWallet(int count)
{
	throw PermissionDenied();
}

int Manager::whatIsMyType() 
{
	return 1;
}