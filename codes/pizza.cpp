#include "Pizza.h"
#include "Order.h"
#include "OrderList.h"
#include <iostream>
#include <string>
//----------------------PROTOTYPES----------------------

void mainMenu();
void pizzaMenu();
void sizeSelection();
void crustSelection();
void takeOrder();
void ingRemoveMenu();
void drinkMenu();

//----------------------ORDER CLASS----------------------
Order::Order(){}
void Order::setName(string name){
	customer = name;
}
void Order::setPizza(Pizza newPizza){
	pizzas.push_front(newPizza);
}
void Order::setDrink(string drink){ //with drinks
	drinks[drink] += 1;
}

//printing single order
void Order::printOrder(){
	cout << "-----------------------------";
	cout << endl <<"Name: "<<getName()<< endl<<endl;
	for (list<Pizza>::iterator it = pizzas.begin(); it != pizzas.end(); ++it){
		it->printPizza();
	}
	map<string, int>::iterator it;
	for (it = drinks.begin(); it != drinks.end(); ++it){
		cout << it->second << " " << it->first << ", ";
	}
	cout << endl<<endl;

}

string Order::getName(){
	return customer;
}
double Order::getPrice(){
	double price=0.0;
	for (list<Pizza>::iterator it = pizzas.begin(); it != pizzas.end(); ++it){
		if (it->getSize().compare("small") == 0){
			price += 15.0;
			cout<<"small pizza added price is now: "<<price<<endl;
		}
		else if (it->getSize().compare("medium") == 0){
			price += 20.0;
			cout<<"medium pizza added price is now: "<<price<<endl;
		}
		else if (it->getSize().compare("big") == 0){
			price += 25.0;
			cout<<"big pizza added price is now: "<<price<<endl;
		}
	}

	map<string, int>::iterator it;
	for (it = drinks.begin(); it != drinks.end(); ++it){
		//cout << it->second << " " << it->first << " ";
		if (it->first.compare("cola") == 0){
			price = price + 4 * ((double)it->second);
			cout<<"cola added price is now: "<<price<<endl;
		}
		else if (it->first.compare("soda") == 0){
			price = price + 2 * ((double)it->second);
			cout<<"soda added price is now: "<<price<<endl;
		}
		else if (it->first.compare("ice tea") == 0){
			price = price + 3 * ((double)it->second);
			cout<<"ice tea added price is now: "<<price<<endl;
		}
		else if (it->first.compare("fruit juice") == 0){
			price = price + 3.5 * ((double)it->second);
			cout<<"fruit juice added price is now: "<<price<<endl;
		}
	}
	return price;
}

bool Order::operator==(Order given){
	return customer == given.customer;
}

//destractor
Order::~Order()
{
}

//----------------------PIZZA CLASS----------------------
Pizza::Pizza()
{
	this->size = "medium";
	this->ingredients.push_back("mozarella");
	this->crust_type = "normal";
}
//constractor with value
Pizza::Pizza(string size, string crust_type, int pizza_type){
	this->size = size;
	this->crust_type = crust_type;
	if (pizza_type == 1){
		this->name = "Chicken Pizza";
		this->ingredients.push_back("tomato");
		this->ingredients.push_back("onion");
		this->ingredients.push_back("corn");
		this->ingredients.push_back("mushroom");
		this->ingredients.push_back("chicken");
		this->ingredients.push_back("mozarella");
	}
	else if (pizza_type == 2){
		this->name = "Broccoli Pizza";
		this->ingredients.push_back("onion");
		this->ingredients.push_back("corn");
		this->ingredients.push_back("olive");
		this->ingredients.push_back("pepperoni");
		this->ingredients.push_back("broccoli");
		this->ingredients.push_back("mozarella");
	}
	else{
		this->name = "Sausage Pizza";
		this->ingredients.push_back("corn");
		this->ingredients.push_back("mushroom");
		this->ingredients.push_back("olive");
		this->ingredients.push_back("tomato");
		this->ingredients.push_back("sausage");
		this->ingredients.push_back("mozarella");
	}
}
//copy constractor
Pizza::Pizza(const Pizza &given){
	name = given.name;
	size = given.size;
	ingredients = given.ingredients;
	crust_type = given.crust_type;
}
//removing ingredient from pizza
void Pizza::removeIngredient(int ingNum){
	switch (ingNum)
	{
	case 1:
		ingredients.remove("mozarella");
		break;
	case 2:
		ingredients.remove("broccoli");
		break;
	case 3:
		ingredients.remove("pepperoni");
		break;
	case 4:
		ingredients.remove("onion");
		break;
	case 5:
		ingredients.remove("olive");
		break;
	case 6:
		ingredients.remove("corn");
		break;
	default:
		break;
	}
}
//printing single pizza
void Pizza::printPizza(){
	cout << name << "(";
	for (list<string>::iterator it = ingredients.begin(); it != ingredients.end(); ++it){
		cout << *it<<", ";
	}
	cout << ")" << endl;
	cout << "size: " << size << ", crust: " << crust_type << endl;
}
string Pizza::getSize(){
	return size;
}
Pizza::~Pizza()
{
}

//--------------------------------OrderList CLASS---------------------------
OrderList::OrderList(){
		n = 0;
}

void OrderList::takeOrder(){
	Order newOrder;
	string customerName;
	//type selection
	int pizzaType = -1;
	pizzaMenu();
	cin >> pizzaType;
	if(pizzaType==0){
		//not taking any orders
	}else{

	while (pizzaType<0 || pizzaType>3){//make user enter correct input
		cout << "Please make a valid selection" << endl;
		pizzaMenu();
		cin >> pizzaType;
	}

	//size selection
	sizeSelection(); //printing menu
	string pizzaSize;
	cin >> pizzaSize;
	while (!(pizzaSize == "small" || pizzaSize == "medium" || pizzaSize == "big")){//make user correct input
		cout << "Please make a valid selection" << endl;
		sizeSelection();
		cin >> pizzaSize;
	}

	// crust selection
	crustSelection(); //priting choices of crust
	string pizzaCrust;
	cin >> pizzaCrust;
	while (!(pizzaCrust == "thin" || pizzaCrust == "normal" || pizzaCrust == "thick")){ //make user correct input
		cout << "Please make a valid selection" << endl;
		crustSelection();
		cin >> pizzaCrust;
	}

	//amount
	unsigned int amount;
	cout << "Enter the amount: ";
	cin >> amount;

	//creating pizza
	Pizza newPizza(pizzaSize, pizzaCrust, pizzaType);

	//ingrenient removal
	int ingRemove;
	newOrder.setPizza(newPizza);
	while(amount>1){
		cout << "\nPlease enter the number of the ingredient you want to remove from your pizza." << endl;
		ingRemoveMenu();
		cin >> ingRemove;
		Pizza copyPizza(newPizza); //copy constractor invoked here since there are more than one pizza
		while (ingRemove != 0){
			while (ingRemove > 0 && ingRemove<7){
				copyPizza.removeIngredient(ingRemove);
				cin >> ingRemove;
			}
			if (ingRemove != 0){
				cout << "Please make a valid selection" << endl;
				cin >> ingRemove;
			}
		}
		newOrder.setPizza(copyPizza);
		amount--;
	}



	//drinking orders
	int drinkNum = -2;
	cout << "Please choose a drink:";
	drinkMenu();
	cin >> drinkNum;
		while (drinkNum != -1 && drinkNum != 0){
			switch (drinkNum)
			{
			case 1:
				newOrder.setDrink("cola");
				break;
			case 2:
				newOrder.setDrink("soda");
				break;
			case 3:
				newOrder.setDrink("ice tea");
				break;
			case 4:
				newOrder.setDrink("fruit juice");
				break;
			default:
				break;
			}
			cin >> drinkNum;
		}


	cout << "Please enter your name:"<<endl;
	cin >> customerName;
	newOrder.setName(customerName);


	orders.push_back(newOrder);
	cout<<"\nYour order is saved, it will be delivered when it is ready..."<<endl;
	newOrder.printOrder();
	}
}
//printing list of orders
void OrderList::listOrders(){
	int i = 1;
	if(orders.empty()){
		cout<<"List is empty"<<endl;
	}else{
		for (list<Order>::iterator it = orders.begin(); it != orders.end(); ++it){
			cout<<i<<endl;
			it->printOrder();
			i++;
		}
	}
	
}
void OrderList::deliverOrders(){
	listOrders();
	string deliverName;
	Order tempOrder;
	bool found = false;
	cout << "\nPlease write the customer name in order to deliver his/her order: ";
	cin >> deliverName;
	for (list<Order>::iterator it = orders.begin(); it != orders.end(); ++it){
		if (it->getName() == deliverName){
			tempOrder = *it;
			found = true;
			break;
		}
	}
	if (found){ //Delievering and removing order from the orders list
		char answer;
		string prom;
		double price = tempOrder.getPrice();
		cout << "Following order is delivering..." << endl;
		tempOrder.printOrder();
		printf("Total Price: %.2f\n", price);
		cout << "Do you have a promotion code? (y/n)" << endl;
		cin >> answer;

		while (answer == 'y'){
			cout << "Please enter the promotion code: ";
			cin.ignore();
			getline(cin, prom);
			if (prom.compare("I am a student")==0){
				price = price*(0.9);
				printf("Discounted price: %.2f\n",price);
				break;
			}
			else {
				cout << "Promotion code is not accepted!"<<endl;
				cout << "Do you have a promotion code? (y/n)\n" << endl;
				cin >> answer;
			}
		}
		cout << "The order is delivered succesfully!" << endl;

		orders.remove(tempOrder);
	}
	else{
		cout << "\nWrong name" << endl;
	}
}
//-----------------MAIN FUNCTION-------------------------------

int main(){
	int choice = 0;
	OrderList newOrderList;
	while (choice != 4){
		mainMenu();
		cin >> choice;
		while (choice > 4 || choice < 0){
			cout << "Please make a valid selection" << endl;
			mainMenu();
			cin >> choice;
		}
		if (choice == 1){
			newOrderList.takeOrder();

		}
		else if (choice == 2){
			newOrderList.listOrders();
		}
		else if(choice == 3){
			newOrderList.deliverOrders();
		}
		else if (choice == 4){
			cout << "Goodbye...";
			return 0;
		}
	}
	cout << "_EOF_";
	return 0;
}

//--------------------------PRINTING MENUS--------------
void mainMenu(){
	cout << "Welcome to Unicorn Pizza!" << endl;
	cout << "1. Add an order" << endl;
	cout << "2. List orders" << endl;
	cout << "3. Deliver order" << endl;
	cout << "4. Exit" << endl;
	cout << "Choose what to do: ";
}
void pizzaMenu(){
	cout << "Pizza Menu" <<endl;
	cout << "1. Chicken Pizza: mozarella, chicken, mushroom, corn, onion, tomato " << endl;
	cout << "2. Broccoli Pizza : mozarella, broccoli, pepperoni, olive, corn, onion" << endl;
	cout << "3. Sausage Pizza : mozarella, sausage, tomato, olive, mushroom, corn" << endl;
	cout << "0. Back to main menu" << endl;
}
void sizeSelection(){
	cout << "Select size: small (15 TL), medium (20 TL), big (25 TL)" << endl;
}

void crustSelection(){
	cout << "Select crust type: thin, normal, thick" << endl;
}

void ingRemoveMenu(){
	cout << "1. mozarella\n2. broccoli\n3. pepperoni\n4. onion\n5. olive\n6. corn\nPress 0 to save it." << endl;
}
void drinkMenu(){
	cout << "\n0. no drink\n1. cola 4 TL\n2. soda 2 TL\n3. ice tea 3 TL\n4. fruit juice 3.5 TL\nPress -1 for save your order" << endl;
}
