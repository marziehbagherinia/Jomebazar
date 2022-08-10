#include "Buyer.h"

Buyer::Buyer(int _id, string _email, string _username, string _password)
: User(_id, _email, _username, _password)
{

}

void Buyer::ableToSeller()
{
	throw PermissionDenied();
}

void Buyer::ableToBuyer()
{
	
}

void Buyer::ableToManager()
{
	throw PermissionDenied();
}

void Buyer::chargeWallet(double amount)
{
	checkAmountValidation(amount);

	double lastBalance = wallet[wallet.size() - 1];
	
	wallet.push_back(lastBalance + amount);

}

void Buyer::checkAmountValidation(double amount)
{
	if (amount <= 0)
		throw BadRequest();
}

double Buyer::getCash()
{
	return wallet[wallet.size() - 1];
}

int Buyer::submitCart(double payableAmount)
{
	cout << payableAmount << "  " << wallet[wallet.size() - 1] << endl;
	
	if (payableAmount > wallet[wallet.size() - 1])
	{
		return 0;
	}

	wallet.push_back(wallet[wallet.size() - 1] - payableAmount);
	return 1;
}

void Buyer::getWallet(int count)
{
	int temp = count;
	int counter = wallet.size() - 1;

	if (count > wallet.size())
	{
		cout << "credit" << endl;
		for (int i = wallet.size(); i > 0; --i)
		{
			cout << wallet[i - 1] << endl;
		}
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

int Buyer::whatIsMyType() 
{
	return 3;
}