#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>

#include "User.h"

#define ASCEND "ASCEND"
#define DESCEND "DESCEND"
#define OFFERPRICE "offerPrice"
#define FIELD "field"
#define OFFERID "offerId"

using namespace std;

class Manager : public User
{
public:
	Manager(int _id, string _email, string _username, string _password);
	void ableToSeller();
	void ableToManager();
	void ableToBuyer();
	void chargeWallet(double amount);
	void getWallet(int count);
	double getCash();
	
	//void setMyOffers(Offer* offer);
/*	void setOffers(Offer* offer);
	Offer* addOffer(map <string, string> informations, int productId, int offerID);
	int isMyOffer(int productID);
	Offer* changeOffer(map <string, string> informations, int offerId);
	void generateDiscount(map <string, string> informations, int offerId);
	void editOffer(Offer* offer, int productId);
	void getMyOffer();
	void getAllOffers(string order, string field);
	int isMyUnitPrice(double unitPrice);
	vector <Offer*> sortOnOfferPrice();
	void chargeWallet(double amount);
	void addToCart(Product* product, int amount, int discountCode);

private:
	vector <int> offerIds;
	vector <Offer*> offers;
*/	
};

#endif