#ifndef PIZZA_H
#define PIZZA_H
#include<iostream>
#include<string>
#include<list>
using namespace std;
class Pizza
{
private:
	string name;
	string size;
	list<string> ingredients;
	string crust_type;

public:
	Pizza();
	Pizza(string size, string crust_type, int pizza_type);
	//copy constractor
	Pizza(const Pizza &given);
	void removeIngredient(int);
	void printPizza();
	string getSize();



	~Pizza();
};

#endif