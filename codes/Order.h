#ifndef ORDER_H
#define ORDER_H
#include<string>
#include<list>
#include "Pizza.h"
#include<map>


using namespace std;
class Order{
private:
	string customer;
	list<Pizza> pizzas;
	map<string, int> drinks;
public:
	//constractors 
	Order();
	void setName(string);	
	void setPizza(Pizza);
	void setDrink(string);						//set drinks

	//getters
	string getName();
	void printOrder();
	double getPrice();
	void printOrder() const;
	//operator overload
	bool operator == (Order);

	~Order();
};

#endif

