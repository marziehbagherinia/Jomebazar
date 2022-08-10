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
  waitingPrice = unitPrice - (unitPrice*disPercent);
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
  return waitingPrice*(amount - waitingAmount);
}

void Offer::submitShop()
{
  amount = waitingAmount;
  recommender->chargeWallet(waitingPrice);
}

string Offer::getOfferProperty()
{
	string sID = to_string(id);
	string sPrice = convertToString(to_string(unitPrice));
	string sAmount = to_string(amount);
	string space = "\n";
	string nmd = " | ";
	return sID + nmd + sPrice + nmd + sAmount + space ; 
}

void Offer::getOffer()
{
	string nmd = " | ";
	string output = to_string(productId) + nmd +
					to_string(id) + nmd +
					convertToString(to_string(unitPrice)) + nmd +
					to_string(amount);

	cout << output << endl; 
}


double Offer::getUnitPrice()
{
	return unitPrice;
}

void Offer::getAll()
{
  string nmd = " | ";
  int sellerId = recommender->getID();
  string output = to_string(productId) + nmd +
                  productName + nmd +
                  to_string(sellerId) + nmd +
                  to_string(id) + nmd +
                  convertToString(to_string(waitingPrice)) + nmd +
                  to_string(amount - waitingAmount);

  cout << output << endl; 
}

void Offer::removeDisCode(int discountCode)
{
    int index = distance(dicountCode.begin(), find(dicountCode.begin(), dicountCode.end(), discountCode));

    if (index != dicountCode.size())
    {
      dicountCode.erase(dicountCode.begin() + index);
    }
}
