#include "Seller.h"

Seller::Seller(int _id, string _email, string _username, string _password)
: User(_id, _email, _username, _password)
{
}

void Seller::ableToSeller()
{

}

void Seller::ableToManager()
{
	throw PermissionDenied();
}

void Seller::ableToBuyer()
{
	throw PermissionDenied();
}

void Seller::chargeWallet(double amount)
{
	wallet.push_back(amount);
}

double Seller::getCash()
{
	throw Server::Exception("Permission Denied");
}

void Seller::getWallet(int count)
{
	int temp = count;
	int counter = wallet.size() - 1;

	if (count > wallet.size())
	{
		cout << "credit" << endl;
		for (int i = wallet.size(); i > 0; --i)
			cout << wallet[i - 1] << endl;
	}

	else
	{
		while(temp != 0)
		{
			cout << wallet[counter] << endl;
			temp--;
			counter--;
		}
	}
}

int Seller::whatIsMyType() 
{
	return 2;
}