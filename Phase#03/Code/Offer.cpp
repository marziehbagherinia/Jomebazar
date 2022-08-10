#include "Offer.h"

string convertToString(string input)
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


Offer::Offer(int _id, int _productId, string _productName, double _unitPrice, int _amount, User* _recommender)
: id(_id),
  productId(_productId),
  productName(_productName),
  unitPrice(_unitPrice),
  amount(_amount),
  recommender(_recommender)
{
  waitingAmount = 0;
  waitingPrice = 0;
}

int Offer::getID()
{
	return id;
}

void Offer::setNewFeatures(double newUnitPrice, int newAmount)
{
	unitPrice = newUnitPrice;
	amount = newAmount;
}

void Offer::generateDisCode(double _disPercent, int disNumber)
{
	for (int i = 0; i < disNumber; ++i)
	{
		dicountCode.push_back(rand());
		cout << dicountCode[i] << endl; 
	}
	disPercent = _disPercent;
}

void Offer::setOrder(int _amount, int _discountCode)
{
  if (_discountCode != 0)
  {
    checkDisCodeValidation(_discountCode);
    removeDisCode(_discountCode);
  }

  checkAmountValidation(_amount);
  waitingAmount = amount - _amount;
  waitingPrice = (_amount)*unitPrice;
}

void Offer::checkDisCodeValidation(int _discountCode)
{
  if (find(dicountCode.begin(), dicountCode.end(), _discountCode) == dicountCode.end())
    throw BadRequest();
}

void Offer::checkAmountValidation(int _amount)
{
  if (_amount > amount)
    throw BadRequest();
}

double Offer::getPrice()
{
  return waitingPrice;
}

void Offer::submitShop()
{
  amount = waitingAmount;
  waitingAmount = 0;
  recommender->chargeWallet(waitingPrice);
}

map<string, string> Offer::getOfferProperty()
{
  map<string, string> informations;
  informations["id"] = to_string(id);
  informations["unitPrice"] = convertToString(to_string(unitPrice));
  informations["offerAmount"] = to_string(amount);
  if (waitingAmount == 0)
  {
    informations["waitingAmount"] = to_string(amount);
  }
  else 
  {
    informations["waitingAmount"] = to_string(amount - (amount - waitingAmount));
  }

  return informations;
}

map <string, string> Offer::getOffer()
{
  map <string, string> informations;
  informations["productId"] = to_string(productId);
  informations["offerId"] = to_string(id);
  informations["unitPrice"] = convertToString(to_string(unitPrice));
	informations["offerAmount"] = to_string(amount);
  
  return informations;
}


double Offer::getUnitPrice()
{
	return unitPrice;
}

map <string, string> Offer::getAll()
{
  map <string, string> informations;
  int sellerId = recommender->getID();
  informations["sellerId"] = to_string(sellerId);
  informations["productId"] = to_string(productId);
  informations["productName"] = productName;
  informations["offerId"] = to_string(id);
  informations["totalPrice"] = convertToString(to_string(unitPrice));
  informations["allPrice"] = convertToString(to_string(waitingPrice));

  if (waitingAmount == 0)
  {
    informations["amount"] = to_string(0);
  }

  else
  {
    informations["amount"] = to_string(amount - waitingAmount);
  }

  return informations;

}

void Offer::removeDisCode(int discountCode)
{
    int index = distance(dicountCode.begin(), find(dicountCode.begin(), dicountCode.end(), discountCode));

    if (index != dicountCode.size())
    {
      dicountCode.erase(dicountCode.begin() + index);
    }
}
