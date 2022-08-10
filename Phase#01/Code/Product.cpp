#include "Product.h"

string convertingToString(string input)
{
  int help = 0;
  size_t found = input.find('.');

  if (found != string::npos)
  {
    for (int i = input.length() - 1; i > -1; i--)
    {
      if (input[i] == '0')
          help++;

      if (input[i-1] == '.')
      {
        help++;
        break;
      }
    }

    if (help > 0){
      if (input[input.length() - help] == '.')
      {
        input.erase(input.begin()+(input.length() - help ), input.end());
      }
      else
        input.erase(input.begin()+(input.length() - help + 1), input.end());
      
    }
  }

  return input;
    
}

Product::Product(int _id, string _name)
: name(_name),
  id(_id)
{

}

int Product::getID()
{
  return id;
}

string Product::getName()
{
  return name;
}

void Product::addToOffers(Offer* offer)
{
	offers.push_back(offer);
}

void Product::editOffer(int offerId, double newUnitPrice, int newAmount)
{
	int index = findOffer(offerId);
	if (index != -1)
	{
		offers[index]->setNewFeatures(newUnitPrice, newAmount);
	}
}

int Product::findOffer(int offerId)
{
  for (int i = 0; i < offers.size(); ++i)
  {
    if (offers[i]->getID() == offerId)
      return i;
  }
  return -1;
}

void Product::generateDisC(int offerId, double disPercent, int disNumber)
{
  int index = findOffer(offerId);
  if (index != -1)
  {
    offers[index]->generateDisCode(disPercent, disNumber);
  }
}

Offer* Product::setNewOrder(int offerId, int amount, int discountCode)
{
  int index = findOffer(offerId);
  if (index != -1)
  {
    offers[index]->setOrder(amount, discountCode);
  }
  return offers[index];
}

void Product::addToComments(string comment, User* commenter)
{
  
  string commenterName = commenter->getUsername();
  userComment[commenterName].push_back(comment);
  
}

void Product::printComments(User* user)
{
  cout << name << endl;

  for (auto it = userComment.begin(); it != userComment.end(); ++it) 
  {
    for (int i = 0; i < it->second.size(); ++i)
      cout << it->first << " | " << it->second[i] << endl;
  }
}

void Product::getProducts()
{
	cout << id << " | " << name << endl;
}

void Product::getOfferOnProduct()
{
	cout << "productId | productName | offerId | offerUnitPrice | offerAmount" << endl;
	for (int i = 0; i < offers.size(); ++i)
		cout << id << " | " << 
          name << " | " << 
          offers[i]->getOfferProperty();
}