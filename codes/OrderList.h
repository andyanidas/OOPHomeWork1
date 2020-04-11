class OrderList{
private:
	int n;
	list<Order> orders;
public:
	OrderList();
	void takeOrder();
	void listOrders();
	void deliverOrders();
};
