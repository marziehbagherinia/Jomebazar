#include "handlers.h"

Response *ShowLogin::callback(Request *req) 
{
  UserRepository* users_repository = users_repository->getUserRep();
  int endId = users_repository->getLastId();

  Response *res = new Response;

  res->setHeader("Content-Type", "text/html");

  res->setSessionId("");
  
  string body;
  
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style = \"text-align : center; font-family: Arial, Helvetica, sans-serif; background-color : rgb(0, 0, 67); color : rgb(9, 9, 98);\">";
  body += "<h1 style = \"font-family:georgia,garamond,serif; color: rgb(160, 223, 255);\">";
  body += "Welcome to UTStore";
  body += "</h1>";
  body += "<div style=\"background-color: rgb(160, 223, 255); padding: 70px 70px 70px 70px; max-width: 300px; border-radius: 20px; margin-top: 130px; margin-left: 690px; \">";
  body += "<form action=\"/login\" method=\"post\">";
  body += "<div>";
  body += "<img src=\"profile.png\"; class=\"brand_logo\" style=\"border-radius: 50%;\">";
  body += "</div>";
  body += "<input name=\"username\" type=\"text\" required placeholder=\"Username\" style=\"display:block; margin: auto;";
  body += "margin-bottom: 10px; padding: 5px; width: 94%; border-radius: 10px;\"  />";
  body += "<input name=\"password\" type=\"password\" required placeholder=\"Password\" style=\"display:block; margin: auto;";
  body += "margin-bottom: 20px; margin-bottom: 30px; padding: 5px; width: 94%; border-radius: 10px; \" />";
  body += "<button style=\"color : rgb(9, 9, 98);\" type=\"submit\" style=\" cursor: pointer; display:block; width: 100%; padding: 7px; ";
  body += "border-radius: 10px; background:rgb(72, 118, 231);\">";
  body += "Login";
  body += "</button>";
  body += "<h4 style=\"font-family:georgia,garamond,serif; font-size: 12px; color: rgb(9, 9, 98);\">";
  body += "Don't have an account? ";
  body += "</h4>";
  body += "<a style=\"color : rgb(9, 9, 98);\" href=\"http://localhost:5000/signup\">";
  body += "Signup";
  body += "</a>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";

  res->setBody(body);
  
  return res;
}

Response *ShowSignup::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();
  
  if(req->getSessionId() != "") 
    throw Server::Exception("There is someone loggedin at the moment.");
  
  Response *res = new Response;
  
  res->setHeader("Content-Type", "text/html");
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style = \"text-align : center; font-family: Arial, Helvetica, sans-serif; background-color : rgb(0, 0, 67); color : rgb(9, 9, 98);\">";
  body += "<h1 style = \"font-family:georgia,garamond,serif; color: rgb(160, 223, 255);\">";
  body += "Welcome to UTStore";
  body += "</h1>";
  body += "<div style = \"background-color: rgb(160, 223, 255); border-radius: 10px; padding: 70px 70px 70px 70px; max-width: 300px;  margin-top: 130px; margin-left: 690px; \">";
  body += "<form action=\"/signup\" method=\"post\">";
  body += "<div>";
  body += "<img src=\"profile.png\"; class=\"brand_logo\" style=\"border-radius: 50%;\">";
  body += "</div>";
  body += "<input name=\"username\" type=\"text\" required placeholder=\"Username\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"password\" type=\"password\" required placeholder=\"Password\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"r_password\" type=\"password\" required placeholder=\"Repeat Password\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"email\" type=\"text\" required placeholder=\"Email\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<span>";
  body += "<input style=\"color : rgb(9, 9, 98);\" type=\"radio\" name=\"userType\" value=\"seller\" > Seller";
  body += "<input style=\"color : rgb(9, 9, 98);\" type=\"radio\" name=\"userType\" value=\"buyer\" > Buyer";
  body += "</span>";
  body += "<button style=\"color : rgb(9, 9, 98);\" type=\"submit\" style=\"display:block; width: 100%; padding:  7px;\">Signup</button>";
  body += "<h4 style=\"font-family:georgia,garamond,serif; font-size: 12px; color: rgb(9, 9, 98);\">";
  body += "Already have an account? ";
  body += "</h4>";
  body += "<a style=\"color : rgb(9, 9, 98);\" href=\"http://localhost:5000/login\">Login</a>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";

  res->setBody(body);
  
  return res;
}

Response *LoginHandler::callback(Request *req)
{
  UserRepository* users_repository = users_repository->getUserRep();
  
  if(req->getSessionId() != "") 
    throw Server::Exception("There is someone loggedin at the moment.");

  map<string, string> informations;

  informations["username"] = req->getBodyParam("username");
  informations["password"] = req->getBodyParam("password");
  
  User* loggingin = users_repository->loginCheck(informations);
  
  int sid = loggingin->getID();
  
  Response *res;

  if (loggingin->whatIsMyType() == 1)
  {
    res = Response::redirect("/manager_home");
  }

  else if (loggingin->whatIsMyType() == 2)
  {
    res = Response::redirect("/seller_home");
  }

  else if (loggingin->whatIsMyType() == 3)
  {
    res = Response::redirect("/buyer_home");
  }

  res->setSessionId(to_string(sid));
  
  return res;
}

Response *SignupHandler::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();

    if(req->getSessionId() != "")
    throw Server::Exception("There is sombody loggedin at the moment.");

  map<string, string> informations;
  informations["username"] = req->getBodyParam("username");
  informations["password"] = req->getBodyParam("password");
  string r_password = req->getBodyParam("r_password");
  informations["email"] = req->getBodyParam("email");
  informations["type"] = req->getBodyParam("userType");

  bool dupUser = users_repository->isDuplicateUsername(informations["username"]);

  if (dupUser)
  {
    throw Server::Exception("Your Entered Username has choosen Before!");
  }
  
  if(r_password.size() == 0)
  {
    throw Server::Exception("Please enter the repeat of your password.");
  }
  
  else if(r_password != informations["password"]) 
  {
    throw Server::Exception("The repeat of your password is not right, try again.");
  }
  
  int sid = (users_repository->addUser(informations))->getID();

  Response *res;

  if(informations["type"] == "seller")
  {
    res = Response::redirect("/seller_home");
  }

  else if (informations["type"] == "buyer")
  {
    res = Response::redirect("/buyer_home");
  }

  res->setSessionId(to_string(sid));
  return res;
}

Response *ShowManagerHome::callback(Request *req) 
{
  UserRepository* users_repository = users_repository->getUserRep();

  if(stoi(req->getSessionId()) != 1)
    throw Server::Exception("Login first.");
  
  if(users_repository->isManager(stoi(req->getSessionId())) == 0)
    throw Server::Exception("You can not reach this page.");

  Response *res = new Response;

  res->setHeader("Content-Type", "text/html");
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>body { margin: 0; font-family: Arial, Helvetica, sans-serif;}";
  body += ".topnav { overflow: hidden; background-color: #331;}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: #4CAF50; color: white;}";
  body += "button {position: absolute; left: 1400px;}";
  body += "h2 {text-align: center;text-transform: uppercase; color: #4c8550; margin-top : 100px;}";
  body += "form {margin-top : 100px;}";
  body += "label {color: #4c8550;}";
  body += "::placeholder {color: #4c8550; opacity: 1;}";
  body += "</style></head>";
  body += "<body> <div class=\"topnav\"> <a class=\"active\" href=\"#home\">Home</a>";
  body += "<a href=\"http://localhost:5000/products\">Products</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<body style=\"text-align: center; background-color:#dbffde; color : #4c8550";
  body += "height: 100%; background-repeat: no-repeat; background-size: cover;\"><h2>Upload Store goods</h2> ";
  body += "<div><form action=\"/up\" method=\"post\" enctype=\"multipart/form-data\">";
  body += "<input name=\"file_name\" type=\"text\" placeholder=\"File Name\" />";
  body += "<input type=\"file\" name=\"file\">";
  body += "<span>";
  body += "<input type=\"radio\" name=\"producType\" value=\"car\" >";
  body += "<label for=\"producType\">Car</label>";
  body += "<input type=\"radio\" name=\"producType\" value=\"mobile\" > ";
  body += "<label for=\"producType\">Mobile</label>";
  body += "<input type=\"radio\" name=\"producType\" value=\"tv\" > ";
  body += "<label for=\"producType\">TV</label>";
  body += "</span>";
  body += "<button type=\"submit\">Upload</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowSellerHome::callback(Request *req) 
{
  UserRepository* users_repository = users_repository->getUserRep();

  if(req->getSessionId() == "")
    throw Server::Exception("Login first.");
  
  if(users_repository->isSeller(stoi(req->getSessionId())) == 0)
    throw Server::Exception("You can not reach this page.");

  int userId = stoi(req->getSessionId());
  vector <Offer*> offers = users_repository->getUserOffer(userId);
  map <string, string> informations;

  Response *res = new Response;

  res->setHeader("Content-Type", "text/html");
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>body { margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(255, 230, 217); color:rgb(65, 26, 17);}";
  body += ".topnav { overflow: hidden; background-color: rgb(65, 26, 17);}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: rgb(225, 0, 0); color: white;}";
  body += "table {font-family: arial, sans-serif; border-collapse: collapse;}";
  body += "td, th { border: 1px solid rgb(237, 151, 137); text-align: left; padding: 8px;}";
  body += "tr:nth-child(even) {background-color: rgb(251, 163, 148);}";
  body += "</style></head>";
  body += "<body> <div class=\"topnav\"> <a class=\"active\" href=\"#home\">Home</a>";
  body += "<a href=\"http://localhost:5000/post_offer\">Products</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<body style=\"text-align: center;\"><h2>All My Offers</h2> ";
  body += "<table align=\"center\"> <tr>";
  body += "<th>Product ID</th>";
  body += "<th>Offer ID</th>";
  body += "<th>Offer Unit Price</th>";
  body += "<th>Offer Amount</th>";
  body += "</tr>";
  if (offers.size() == 0)
  {
    body += "<tr><td></td><td></td><td></td><td></td></tr>";
  }
  else
  {
    for (int i = 0; i < offers.size(); ++i)
    {
      informations = offers[i]->getOffer();
      body += "<tr><td>";
      body += informations["productId"];
      body += "</td><td>";
      body += informations["offerId"];
      body += "</td><td>";
      body += informations["unitPrice"];
      body += "</td><td>";
      body += informations["offerAmount"];
      body += "</td></tr>";
    }
  }

  body += "</table>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ShowBuyerHome::callback(Request *req) 
{
  UserRepository* users_repository = users_repository->getUserRep();
  ProductRepository* products_repository = products_repository->getProductRep(); 
  
  int userId = stoi(req->getSessionId());
  
  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isBuyer(userId) == 0)
    throw Server::Exception("You can not reach this page.");

  vector <Car*> cars = products_repository->getCars();
  vector <Mobile*> mobiles = products_repository->getMobiles();
  vector <Tv*> tvs = products_repository->getTvs();

  Response *res = new Response;

  res->setHeader("Content-Type", "text/html");
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>"; 
  body += "body { margin: 0; font-family: Arial, Helvetica, sans-serif; background-color:rgb(207, 236, 255); color:#00005a;}";
  body += "h2 {text-align: center; color:#00005a;}";
  body += ".topnav { overflow: hidden; background-color: rgb(17, 17, 51);}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: #587ad2; color: white;}";
  body += "table {font-family: arial, sans-serif; border-collapse: collapse; text-align: left; margin-top:80px; margin-left: 40px; margin-right: auto; margin-bottom: auto; ";
  body += "border: 1px solid rgb(88, 122, 210); table-layout: fixed; width:30%; color:rgb(65, 26, 17);}";
  body += "td, th {border: 1px solid rgb(88, 122, 210); text-align: left; padding: 8px; width: 15%; overflow: hidden; color:rgb(65, 26, 17);}";
  body += "tr:nth-child(even) {background-color: #70bff7;}";
  body += "tr:nth-child(odd) {background-color: #ebebeb;}";
  body += "</style></head><body>";
  body += "<body> <div class=\"topnav\"> <a class=\"active\" href=\"#home\">Home</a>";
  body += "<a href=\"http://localhost:5000/bank\">Wallet</a>";
  body += "<a href=\"http://localhost:5000/shop\">Shop</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<h2 style=\"font-family:georgia,garamond,serif;\"> ";
  body += "Wellcome to UTStore";
  body += "</h2>";
  body += "<table style=\"max-width:30%; display:inline-block;\">";
  body += "<tr><th> Car Name </th><th> Car ID </th><th> Product Detail</th></tr>";

  if (cars.size() == 0)
  {
    body += "<tr><td></td><td></td><td></td></tr>";
  }

  else 
  {
    for (int i = 0; i < cars.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += "  ";
      body += cars[i]->getName();
      body += "</td><td>";
      body += to_string(cars[i]->getID());
      body += "</td><td>";
      body += "<form action=\"/product_detail\" method=\"post\">";
      body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">show detail</button>";
      body += "<input type=\"hidden\" name=\"id\" value=\"";
      body += to_string(cars[i]->getID());
      body += "\">";
      body += "</form>";
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "<table style=\"max-width:30%; display:inline-block\">";
  body += "<tr><th> Mobile Name </th><th> Mobile ID </th><th>Product Detail</th></tr>";

  if (mobiles.size() == 0)
  {
    body += "<tr><td></td><td></td><td></td></tr>";
  }

  else 
  {
    for (int i = 0; i < mobiles.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += "  ";
      body += mobiles[i]->getName();
      body += "</td><td>";
      body += to_string(mobiles[i]->getID());
      body += "</td><td>";
      body += "<form action=\"/product_detail\" method=\"post\">";
      body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">show detail</button>";
      body += "<input type=\"hidden\" name=\"id\" value=\"";
      body += to_string(mobiles[i]->getID());
      body += "\">";
      body += "</form>";
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "<table style=\"max-width:30%; display:inline-block\">";
  body += "<tr><th> TV Name </th><th> TV ID </th><th>Product Detail</th></tr>";

  if (tvs.size() == 0)
  {
    body += "<tr><td></td><td></td><td></td></tr>";
  }

  else 
  {
    for (int i = 0; i < tvs.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += "  ";
      body += tvs[i]->getName();
      body += "</td><td>";
      body += to_string(tvs[i]->getID());
      body += "</td><td>";
      body += "<form action=\"/product_detail\" method=\"post\">";
      body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">show detail</button>";
      body += "<input type=\"hidden\" name=\"id\" value=\"";
      body += to_string(tvs[i]->getID());
      body += "\">";
      body += "</form>";
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *LogoutHandler::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();

  if(req->getSessionId()== "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  int userId = stoi(req->getSessionId());

  User* currentUser = users_repository->getUser(userId);  

  users_repository->emptyCart(currentUser);

  Response *res = Response::redirect("/login");
  res->setSessionId("");
  return res;
}

Response *UploadHandler::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep(); 
  ProductRepository* products_repository = products_repository->getProductRep();

  int userId = stoi(req->getSessionId());
  
  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isManager(userId) == 0)
    throw Server::Exception("You can not reach this page.");

  ofstream fout;
  fout.open("out.txt"); 

  string type = req->getBodyParam("producType");
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");

  if (fout.is_open())
  {
    fout << file << endl;
  } 

  fout.close();

  map<string, string> informations;

  informations["type"] = type;
  informations["filePath"] = "out.txt"; 

  if (type.length() != 0)
  {
      products_repository->addProducts(informations);
  }

  Response *res = new Response;
  
  res->setHeader("Content-Type", "text/html");
  
  string body;
  
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center; background-color:#dbffde; color: #4c8550; height: 100%;\"";
  body += "<div style=\" line-height: 150px; text-align: center;\">";
  body += "<h2 style=\"font-family:georgia,garamond,serif; color: rgb(76, 133, 80); top: 80px;\"> ";
  body += "<b> Upload Files </b>";
  body += "</h2>";
  body += "<div style=\"background-color: rgb(159, 247, 159); padding: 1%; max-width: 300px; border-radius: 20px; margin-top: 100px; margin-left: auto; margin-bottom: auto; margin-right: auto;\">";
  if (type.length() != 0)
  {
    body += "<p style = \"font-size: 18px; color: rgb(76, 133, 80);\"> <b>You've Uploaded File Successfully. </b></p>";
  }
  else
  {
    body += "<p style = \"font-size: 18px; color: rgb(76, 133, 80);\"> <b> Error! You didn't choose the type of product.</b></p>";
  }

  body += "<form action=\"/products\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Products</button>";
  body += "</form>";
  body += "<form action=\"/manager_home\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Home Page</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *showProducts::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();
  ProductRepository* products_repository = products_repository->getProductRep();

  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isManager(stoi(req->getSessionId())) == 0)
    throw Server::Exception("You can not reach this page.");
  

  vector <Car*> cars = products_repository->getCars();
  vector <Mobile*> mobiles = products_repository->getMobiles();
  vector <Tv*> tvs = products_repository->getTvs();

  Response *res = new Response;

  res->setHeader("Content-Type", "text/html");
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>body { margin: 0; font-family: Arial, Helvetica, sans-serif;}";
  body += ".topnav { overflow: hidden; background-color: #331;}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: #4CAF50; color: white;}";
  body += "ul, #myUL {list-style-type: none;}";
  body += "#myUL {margin-left: 100px;padding: 0;}";
  body += "h2 {text-align: center;}";
  body += ".caret {cursor: pointer; -webkit-user-select: none; -moz-user-select: none; -ms-user-select: none; user-select: none; color:rgb(76, 133, 80);}";
  body += ".caret::before {content: \"* \";color: black;display: inline-block;margin-right: 6px; color:rgb(76, 133, 80);}";
  body += ".caret-down::before {-ms-transform: rotate(90deg);-webkit-transform: rotate(90deg);transform: rotate(90deg);}";
  body += ".nested {display: none;}";
  body += ".active {display: block;}";
  body += "table { font-family: arial, sans-serif; border-collapse: collapse;}";
  body += "td, th {border: 1px solid rgb(101, 196, 105); text-align: left; padding: 8px;}";
  body += "tr:nth-child(even) {background-color: rgb(146, 235, 148);}";
  body += "</style></head>";
  body += "<body>";
  body += "<div class=\"topnav\"> <a class=\"active\" href=\"#home\">Products</a>";
  body += "<a href=\"http://localhost:5000/manager_home\">Home</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<h2 style=\"font-family:georgia,garamond,serif; color: rgb(76, 133, 80);\"> ";
  body += "Store Products";
  body += "</h2>";
  body += "<ul id=\"myUL\"> <li><span class=\"caret\"><b>Products</b></span>";
  body += "<ul class=\"nested\">";
  body += "<li><span class=\"caret\"><b>Car</b></span>";
  body += "<ul class=\"nested\">";
  body += "<table> <tr>";
  body += "<th>Product Name</th> <th>Product ID</th> </tr>";

  if (cars.size() == 0)
  {
    body += "<tr><td></td><td></td></tr>";
  }

  else 
  {
    for (int i = 0; i < cars.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += cars[i]->getName();
      body += "</td><td>";
      body += to_string(cars[i]->getID());
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "</ul></li>";
  body += "<li><span class=\"caret\"><b>Mobile</b></span>";
  body += "<ul class=\"nested\">";
  body += "<table> <tr>";
  body += "<th>Product Name</th> <th>Product ID</th> </tr>";

  if (mobiles.size() == 0)
  {
    body += "<tr> <td> </td> <td> </td> </tr>";
  }

  else 
  {
    for (int i = 0; i < mobiles.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += mobiles[i]->getName();
      body += "</td><td>";
      body += to_string(mobiles[i]->getID());
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "</ul></li>";
  body += "<li><span class=\"caret\"><b>TV</b></span>";
  body += "<ul class=\"nested\">";
  body += "<table> <tr>";
  body += "<th>Product Name</th> <th>Product ID</th> </tr>";

  if (tvs.size() == 0)
  {
    body += "<tr> <td> </td> <td> </td> </tr>";
  }

  else 
  {
    for (int i = 0; i < tvs.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += tvs[i]->getName();
      body += "</td><td>";
      body += to_string(tvs[i]->getID());
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "</ul></li></ul>";
  body += "<script>";
  body += "var toggler = document.getElementsByClassName(\"caret\");";
  body += "var i;";
  body += "for (i = 0; i < toggler.length; i++)";
  body += "{toggler[i].addEventListener(\"click\", function()";
  body += "{this.parentElement.querySelector(\".nested\").classList.toggle(\"active\");";
  body += "this.classList.toggle(\"caret-down\");});}";
  body += "</script>";
  body += "</body>";
  body += "</html>";

  res->setBody(body);
  return res;

}

Response *showPostOffer::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();
  ProductRepository* products_repository = products_repository->getProductRep();
  
  int userId = stoi(req->getSessionId());
  
  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isSeller(userId) == 0)
    throw Server::Exception("You can not reach this page."); 

  vector <Car*> cars = products_repository->getCars();
  vector <Mobile*> mobiles = products_repository->getMobiles();
  vector <Tv*> tvs = products_repository->getTvs();

  Response *res = new Response;

  res->setHeader("Content-Type", "text/html");

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head> <style>";
  body += "body { margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(255, 230, 217); color:rgb(65, 26, 17);}";
  body += "h2 {text-align: center;}";
  body += ".topnav { overflow: hidden; background-color: rgb(65, 26, 17);}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: rgb(225, 0, 0); color: white;}";
  body += "table {font-family: arial, sans-serif; border-collapse: collapse; text-align: left; margin-top:100px; margin-left: 40px; margin-right: auto; margin-bottom: auto; ";
  body += "border: 1px solid rgb(251, 163, 148); table-layout: fixed; width:30%; color:rgb(65, 26, 17);}";
  body += "td, th {border: 1px solid rgb(251, 163, 148); text-align: left; padding: 8px; width: 15%; overflow: hidden; color:rgb(65, 26, 17);}";
  body += "tr:nth-child(even) {background-color: rgb(251, 163, 148);}";
  body += "tr:nth-child(odd) {background-color: #f0f0f0;}";
  body += "</style></head><body>";
  body += "<div class=\"topnav\"> <a class=\"active\" href=\"#home\">Post Offer</a>";
  body += "<a href=\"http://localhost:5000/seller_home\">Home</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<h2 style=\"font-family:georgia,garamond,serif;\"> ";
  body += "Fill the blank to post offer";
  body += "</h2>";
  body += "<div style=\"background-color: rgb(251, 163, 148); padding: 70px 70px 70px 70px; max-width: 300px; border-radius: 20px; margin-top: 50px; margin-left: 690px; \">";
  body += "<form action=\"/post_offer\" method=\"post\">";;
  body += "<input name=\"productID\" type=\"text\" required placeholder=\"product ID\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"offerUnitPrice\" type=\"text\" required placeholder=\"offer Unit Price\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<input name=\"offerAmont\" type=\"text\" required placeholder=\"offer Amont\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\" />";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Signup</button>";
  body += "</form>";
  body += "</div>";
  body += "<table style=\"max-width:30%; display:inline-block;\">";
  body += "<tr><th> Car Name </th><th> Car ID </th></tr>";

  if (cars.size() == 0)
  {
    body += "<tr><td></td><td></td></tr>";
  }

  else 
  {
    for (int i = 0; i < cars.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += "  ";
      body += cars[i]->getName();
      body += "</td><td>";
      body += to_string(cars[i]->getID());
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "<table style=\"max-width:30%; display:inline-block\">";
  body += "<tr><th> Mobile Name </th><th> Mobile ID </th></tr>";

  if (mobiles.size() == 0)
  {
    body += "<tr> <td> </td> <td> </td> </tr>";
  }

  else 
  {
    for (int i = 0; i < mobiles.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += "  ";
      body += mobiles[i]->getName();
      body += "</td><td>";
      body += to_string(mobiles[i]->getID());
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "<table style=\"max-width:30%; display:inline-block\">";
  body += "<tr><th> TV Name </th><th> TV ID </th></tr>";

  if (tvs.size() == 0)
  {
    body += "<tr> <td> </td> <td> </td> </tr>";
  }

  else 
  {
    for (int i = 0; i < tvs.size(); ++i)
    {
      body += "<tr>";
      body += "<td>";
      body += "  ";
      body += tvs[i]->getName();
      body += "</td><td>";
      body += to_string(tvs[i]->getID());
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "</body>";
  body += "</html>";

  res->setBody(body);
  return res;


}

Response *postOfferHandler::callback(Request *req) {

  ProductRepository* products_repository = products_repository->getProductRep();
  UserRepository* users_repository = users_repository->getUserRep();

  int userId = stoi(req->getSessionId());

    if(req->getSessionId() == "")
      throw Server::Exception("There is nobody loggedin at the moment.");

    if(users_repository->isSeller(userId) == 0)
      throw Server::Exception("You can not reach this page.");

  map<string, string> informations;
  informations["productId"] = req->getBodyParam("productID");
  informations["offerUnitPrice"] = req->getBodyParam("offerUnitPrice");
  informations["offerAmount"] = req->getBodyParam("offerAmont");

  User* currentUser = users_repository->getUser(userId);  
  Offer* newOffer = products_repository->addOffer(informations, currentUser);
  users_repository->setOffer(newOffer, userId);

  Response *res = new Response;
  
  res->setHeader("Content-Type", "text/html");
  
  string body;
  
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(255, 230, 217); color:rgb(65, 26, 17); height: 100%;\"";
  body += "background-repeat: no-repeat; background-size: cover;\">";
  body += "<h2 style=\"font-family:georgia,garamond,serif; color: rgb(65, 26, 17); margin-top: 40px; \"> ";
  body += "Set Offer";
  body += "</h2>";
  body += "<div style=\"background-color: rgb(251, 163, 148); padding: 1%; max-width: 300px; border-radius: 20px; margin-top: 80px; margin: auto; \">";
  body += "<p style = \"font-size: 15px;\">You've Done It Successfully.</p>";
  body += "<form action=\"/post_offer\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Products</button>";
  body += "</form>";
  body += "<form action=\"/seller_home\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Home Page</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";

  res->setBody(body);
  return res;
}

Response *ShowBuyerBank::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();
  
  int userId = stoi(req->getSessionId());

  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isBuyer(userId) == 0)
    throw Server::Exception("You can not reach this page.");  

  User* currentUser = users_repository->getUser(userId);

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style>";
  body += ".topnav { overflow: hidden; background-color: rgb(17, 17, 51);}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: #587ad2; color: white;}";
  body += "table, td, th {  border: 1px solid #ddd;text-align: left;}table {border-collapse: collapse;width: 100%;}th, td {padding: 15px;}";
  body += "</style></head>";
  body += "<body style=\"text-align: center; margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(207, 236, 255); color:#00005a;\">";
  body += "<div class=\"topnav\"> <a class=\"active\" href=\"#home\">Wallet</a>";
  body += "<a href=\"http://localhost:5000/buyer_home\">Home</a>";
  body += "<a href=\"http://localhost:5000/shop\">Shop</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<h2 style=\"font-family:georgia,garamond,serif; color: color:#00005a;\"> ";
  body += "My Wallet";
  body += "</h2>";
  body += "<div style=\"background-color: #70bff7; padding: 1%; max-width: 300px; border-radius: 20px; margin: auto; \">";
  body += "<p style = \"font-size: 20px;\">Amount of Money in Your Wallet:</p>";
  body += "<p style = \"font-size: 20px;\">";
  body += to_string(currentUser->getCash());
  body += "</p>";
  body += "<form action=\"/charge_wallet\" method=\"post\">";
  body += "<p>Charge Wallet:</p>";
  body += "<input name=\"amount\" type=\"text\" required placeholder=\"Amount\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%; \"  />";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Charge</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *chargeWalletHandler::callback(Request *req) 
{
  UserRepository* users_repository = users_repository->getUserRep();

  int userId = stoi(req->getSessionId());

  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isBuyer(userId) == 0)
    throw Server::Exception("You can not reach this page.");   

  User* currentUser = users_repository->getUser(userId);

  currentUser->chargeWallet(stod(req->getBodyParam("amount")));
  
  Response *res = new Response;
  
  res->setHeader("Content-Type", "text/html");

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center; margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(207, 236, 255); color:#00005a; \">";
  body += "<h2 style=\"font-family:georgia,garamond,serif; color: color:#00005a;\"> ";
  body += "Wallet Charge";
  body += "</h2>";
  body += "<div style=\"background-color: #70bff7; padding: 1%; max-width: 300px; border-radius: 20px; margin: auto; \">";
  body += "<p style = \"font-size: 15px;\">You've Charged Your Wallet Successfully.</p>";
  body += "<form action=\"/bank\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">My Wallet</button>";
  body += "</form>";
  body += "<form action=\"/buyer_home\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Home Page</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}


Response *productDetailHandler::callback(Request *req) {

  ProductRepository* products_repository = products_repository->getProductRep();

  UserRepository* users_repository = users_repository->getUserRep();

  int userId = stoi(req->getSessionId());

  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isBuyer(userId) == 0)
    throw Server::Exception("You can not reach this page.");   

  int productId = stoi(req->getBodyParam("id"));

  map<string, string> informations = products_repository->getProDetail(productId);

  map<string, string> offerInf;
  
  int Type = products_repository->whatIsMyType(productId);

  vector <Offer*> offerOnProduct = products_repository->getOfferOn(productId);

  Response *res = new Response;

  res->setHeader("Content-Type", "text/html");
  
  string body;
  
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style> body { text-align: center; margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(207, 236, 255); color:#00005a;}"; 
  body += ".topnav { overflow: hidden; background-color: rgb(17, 17, 51);}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: #587ad2; color: white;}";
  body += "table {font-family: arial, sans-serif; border-collapse: collapse;}";
  body += "h2 {font-family: arial, sans-serif; text-align: center; color:#00005a;}";
  body += "table { font-family: arial, sans-serif; border-collapse: collapse; margin-top:100px; margin-right: auto; margin-bottom: auto; margin-left: auto;}";
  body += "td, th {border: 1px solid rgb(88, 122, 210); text-align: left; padding: 8px;}";
  body += "table, th, td {text-align: left; color:rgb(0, 0, 90);}";
  body += "tr:nth-child(even) {background-color: #70bff7;}";
  body += "tr:nth-child(odd) {background-color: #ebebeb;}";
  body += "</style></head>";
  body += "<body> <div class=\"topnav\"> <a class=\"active\" href=\"#home\">Product Detail</a>";
  body += "<a href=\"http://localhost:5000/buyer_home\">Home</a>";
  body += "<a href=\"http://localhost:5000/bank\">Wallet</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<h2>";
  body += "Product ";
  body += to_string(productId);
  body += " detail</h2>";
  body += "<table style=\"max-width:100%;\">";
  
  if (Type == 1)
  {
    body += "<tr><th> Name</th><th> Weight</th><th> Number Of Seats </th><th> Number Of Cylinders </th> <th> EngineCapacity </th> <th> Reverse Parking Sensors </th></tr>";
    body += "<tr><td>";
    body += informations["name"];
    body += "</td><td>";
    body += informations[WEIGHT];
    body += "</td><td>";
    body += informations[NUMSEATS];
    body += "</td><td>";
    body += informations[NUMCYLINDER];
    body += "</td><td>";
    body += informations[ENGINEC];
    body += "</td><td>";
    body += informations[PARKINGSENSOR];
    body += "</td></tr>";

  }
  
  else if (Type == 2)
  {
    body += "<tr><th> Name</th><th> Weight</th><th> CPU Frequency </th><th> Built-in Memory </th> <th> RAM </th> <th> DisplaySize </th> <th> Camera Resolution </th> <th> OperatingSystem </th> </tr>";
    body += "<tr><td>";
    body += informations["name"];
    body += "</td><td>";
    body += informations[WEIGHT];
    body += "</td><td>";
    body += informations[CPUF];
    body += "</td><td>";
    body += informations[BUILTMEM];
    body += "</td><td>";
    body += informations[RAM];
    body += "</td><td>";
    body += informations[DISPLAYSIZE];
    body += "</td><td>";
    body += informations[CAMERARES];
    body += "</td><td>";
    body += informations[OS];        
    body += "</td></tr>";
  }
  
  else if (Type == 3)
  {
    body += "<tr><th> Name</th><th> Screen Size</th><th> Screen Type </th><th> Resolution </th> <th> 3D </th> <th> HDR </th> </tr>";
    body += "<tr><td>";
    body += informations["name"];
    body += "</td><td>";
    body += informations[SCREENSIZE];
    body += "</td><td>";
    body += informations[SCREENTYPE];
    body += "</td><td>";
    body += informations[RESOLUTION];
    body += "</td><td>";
    body += informations[THREED];
    body += "</td><td>";
    body += informations[HDR];
    body += "</td></tr>";
  }
  
  body += "</table>";
  body += "<table style=\"max-width:100%;\">";
  body += "<tr><th> offerID</th><th> Offer Unit Price</th><th> Offer Amount </th> <th> Add To Cart </th></tr>";
  
  if (offerOnProduct.size() == 0)
  {
      body += "<tr><td> </td><td> </td><td> </td><td> </td></tr>";
  }  
  else 
  {
    for (int i = 0; i < offerOnProduct.size(); ++i)
    {
      offerInf = offerOnProduct[i]->getOfferProperty();
      body += "<tr><td>";
      body += "<form action=\"/add_to_cart\" method=\"post\">";
      body += "<input type=\"text\" name=\"offerID\" value=\"";
      body += offerInf["id"];
      body += "\" readonly>";
      body += "</td><td>";
      body += "<input type=\"text\" name=\"offerUnitPrice\" value=\"";
      body += offerInf["unitPrice"];
      body += "\" readonly>";
      body += "</td><td>";
      body += "<input type=\"text\" name=\"offerAmont\" value=\"";
      body += offerInf["offerAmount"];
      body += "\" readonly>";
      body += "</td><td>";
      
      if (stoi(offerInf["offerAmount"]) == 0)
      {
        body += "<input type=\"text\" name=\"cartAmount\" placeholder=\"0\" readonly>";
        body += "<button type=\"submit\" disabled>Submit</button>";
      }
      else
      {
        body += "<select name=\"amountOfOrder\">";
        
        for (int i = 1; i < (stoi(offerInf["offerAmount"]) + 1); ++i)
        {
          body += "<option value=\"";
          body += to_string(i);
          body += "\">";
          body += to_string(i);
          body += "</option>";
        }

         body += "</select>";
         body += "<button type=\"submit\">Submit</button>";
      }

      body += "</td></tr></form>";
    }
  }
  body += "</table>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *addToCartlHandler::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();
  ProductRepository* products_repository = products_repository->getProductRep();

  int userId = stoi(req->getSessionId());
  int offerId = stoi(req->getBodyParam("offerID"));
  int amount = stoi(req->getBodyParam("amountOfOrder"));

  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isBuyer(userId) == 0)
    throw Server::Exception("You can not reach this page.");  

  User* currentUser = users_repository->getUser(userId);

  Offer* order = products_repository->getOrderedOffer(offerId, amount, 0);

  users_repository->addToCart(currentUser, order);
  
  Response *res = new Response;
  
  res->setHeader("Content-Type", "text/html");
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center; margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(207, 236, 255); color:#00005a; \">";
  body += "<h2 style=\"font-family:georgia,garamond,serif; color:#00005a;\"> ";
  body += "Add To Cart";
  body += "</h2>";
  body += "<div style=\"background-color: #70bff7; padding: 1%; max-width: 300px; border-radius: 20px; margin: auto; \">";
  body += "<p style = \"font-size: 15px;\">It Has Done Successfully.</p>";
  body += "<form action=\"/shop\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">My Shop</button>";
  body += "</form>";
  body += "<form action=\"/buyer_home\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Home Page</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *showShopPage::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();

  int userId = stoi(req->getSessionId());

  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isBuyer(userId) == 0)
    throw Server::Exception("You can not reach this page.");  

  User* currentUser = users_repository->getUser(userId);

  vector <Offer*> myCart = users_repository->getCart(currentUser);
  
  Response *res = new Response;

  map <string, string> informations;
  
  res->setHeader("Content-Type", "text/html");

  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head><style> body { margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(207, 236, 255); color:#00005a;}";
  body += "form { margin-left: 40px; margin-top: 20px;}";
  body += ".topnav { overflow: hidden; background-color: rgb(17, 17, 51);}";
  body += ".topnav a {float: left; color: #f2f2f2; text-align: center; padding: 14px 16px; text-decoration: none;font-size: 17px;}";
  body += ".topnav a:hover {background-color: #ddd; color: black;}";
  body += ".topnav a.active {background-color: #587ad2; color: white;}";
  body += "table {font-family: arial, sans-serif; border-collapse: collapse;}";
  body += "h2 {text-align: center; color:#00005a;}";
  body += "table { font-family: arial, sans-serif; border-collapse: collapse; margin-top:100px; margin-left: 40px;}";
  body += "td, th {border: 1px solid rgb(88, 122, 210); text-align: left; padding: 8px;}";
  body += "table, th, td {text-align: left; color:rgb(0, 0, 90);}";
  body += "tr:nth-child(even) {background-color: #70bff7;}";
  body += "tr:nth-child(odd) {background-color: #ebebeb;}";
  body += "</style></head>";
  body += "<body>";
  body += "<div class=\"topnav\"> <a class=\"active\" href=\"#home\">Shop</a>";
  body += "<a href=\"http://localhost:5000/buyer_home\">Home</a>";
  body += "<a href=\"http://localhost:5000/bank\">Wallet</a>";
  body += "<a href=\"http://localhost:5000/logout\">LogOut</a> </div>";
  body += "<h2 style=\"font-family:georgia,garamond,serif;\"> ";
  body += "Shopping";
  body += "</h2>";
  body += "<table style=\"max-width:60%; display:inline-block\">";
  body += "<tr><th> Product ID </th><th> Product Name </th><th> Offer ID </th> <th> Seller ID </th> <th> Total Price </th> <th> Amount </th></tr>";

  if (myCart.size() == 0)
  {
    body += "<tr><td></td><td></td><td></td><td></td><td></td><td></td></tr>";
  }

  else 
  {
    for (int i = 0; i < myCart.size(); ++i)
    {
      informations = myCart[i]->getAll();
      body += "<tr>";
      body += "<td>";
      body += informations["productId"];
      body += "</td><td>";
      body += informations["productName"];
      body += "</td><td>";
      body += informations["offerId"];
      body += "</td><td>";
      body += informations["sellerId"];
      body += "</td><td>";
      body += informations["totalPrice"];
      body += "</td><td>";
      body += informations["amount"];
      body += "</td> </tr>";
    }
  }

  body += "</table>";
  body += "<form action=\"/submit_cart\" method=\"post\">";
  body += "<input type=\"text\" name=\"cash\" value=\"";

  if (myCart.size() == 0)
  {
    body += "0\" readonly>";
    body += "<button type=\"submit\" disabled>Submit</button>";
  }

  else
  {
      double finalCash = 0;
      
      for (int i = 0; i < myCart.size(); ++i)
      {
        informations = myCart[i]->getAll();
        finalCash += stod(informations["allPrice"]);
      }

      body += to_string(finalCash);
      body += "\" readonly>";
      body += "<button type=\"submit\">Submit</button>";
  }

  body += "</form>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *submitCartlHandler::callback(Request *req) {

  UserRepository* users_repository = users_repository->getUserRep();

  int userId = stoi(req->getSessionId());

  if(req->getSessionId() == "")
    throw Server::Exception("There is nobody loggedin at the moment.");

  if(users_repository->isBuyer(userId) == 0)
    throw Server::Exception("You can not reach this page.");  

  User* currentUser = users_repository->getUser(userId);

  int result = users_repository->checkAccountCash(currentUser);
  
  Response *res = new Response;

  map <string, string> informations;
  
  res->setHeader("Content-Type", "text/html");
  
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center; margin: 0; font-family: Arial, Helvetica, sans-serif;  background-color:rgb(207, 236, 255); color:#00005a; \">";
  body += "<h2 style=\"font-family:georgia,garamond,serif; color:#00005a;\"> ";
  body += "Wallet Charge";
  body += "</h2>";
  body += "<div style=\"background-color: #70bff7; padding: 1%; max-width: 300px; border-radius: 20px; margin: auto; \">";

  if (result == 0)
  {
    body += "<p style = \"font-size: 15px;\">Your Cash Is NoT Enough.</p>";
  }
  else if (result == 1)
  {
    body += "<p style = \"font-size: 15px;\">It Has Done Successfully.</p>";
  }

  body += "<form action=\"/bank\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">My Wallet</button>";
  body += "</form>";
  body += "<form action=\"/shop\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Shop</button>";
  body += "</form>";
  body += "<form action=\"/buyer_home\" method=\"get\">";
  body += "<button type=\"submit\" style=\"display:block; width: 100%; padding: 7px;\">Home Page</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}