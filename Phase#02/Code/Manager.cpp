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
	throw PermissionDenied();
}

void Manager::getWallet(int count)
{
	throw PermissionDenied();
}

/*
void Manager::setOffers(Offer* offer)
{
	offers.push_back(offer);
	offerIds.push_back(offer->getID());
}

Offer* Manager::addOffer(map <string, string> informations, int productId, int offerID)
{
	throw PermissionDenied();
}

Offer* Manager::changeOffer(map <string, string> informations, int offerId)
{
	throw PermissionDenied();
}

int Manager::isMyOffer(int offerId)
{
	int index = distance(offerIds.begin(), find(offerIds.begin(), offerIds.end(), offerId));
	if (index != offerIds.size()) {
		return index;
	}
	else {
		return -1;
	}
}

int Manager::isMyUnitPrice(double unitPrice)
{
	for (int i = 0; i < offers.size(); ++i)
	{
		if (offers[i]->getUnitPrice() == unitPrice)
		{
			return i;
		}
	}
	return -1;
}

void Manager::generateDiscount(map <string, string> informations, int offerID)
{
	throw PermissionDenied();
}

void Manager::editOffer(Offer* offer, int offerId)
{
	int index = isMyOffer(offerId); 
	if (index != -1)
	{
		offers[index] = offer;
	}
}

void Manager::getMyOffer()
{
	throw PermissionDenied();
}

void Manager::getAllOffers(string order, string field)
{
	if (field == OFFERID)
	{
		if (order == ASCEND)
		{
			for (int i = 0; i < offers.size(); ++i)
				offers[i]->getOffer();
		}
		else if (order == DESCEND)
		{
			for (int i = offers.size() - 1; i > -1; i--)
				offers[i]->getOffer();
		}
		
	}
	else if (field == OFFERPRICE)
	{
		vector <Offer*> sortedOffers = sortOnOfferPrice();
		
		if (order == ASCEND)
		{
			for (int i = 0; i < sortedOffers.size(); ++i)
				sortedOffers[i]->getOffer();
		}
		else if (order == DESCEND)
		{
			for (int i = sortedOffers.size() - 1; i > -1; i--)
				sortedOffers[i]->getOffer();
		}

	}

}

vector <Offer*> Manager::sortOnOfferPrice()
{
	vector <Offer*> sortedOffers;
	vector <double> newOfferPrice;

	for (int i = 0; i < offers.size(); ++i)
	{
		newOfferPrice.push_back(offers[i]->getUnitPrice());
	}

	sort(newOfferPrice.begin(), newOfferPrice.end());

	int index;

	for (int i = 0; i < newOfferPrice.size(); ++i)
	{
		index = isMyUnitPrice(newOfferPrice[i]);

		if (index != -1)
			sortedOffers.push_back(offers[index]);	
	}

	return sortedOffers;
}

void Manager::chargeWallet(double amount)
{
	throw PermissionDenied();
}

void Manager::addToCart(Product* product, int amount, int discountCode)
{
	throw PermissionDenied();
}*/