#pragma once
#include "Customer.h"
#include "Item.h"
#include <vector>
#include<iostream>
#include<string>
#include<fstream>
#include"MovieRecords.h"
#include"DVDs.h"
#include"Games.h"
#include "Customer.h"
class RentalShop
{
private:
	//vector<Customer*> customers;
	vector<Item*> items;
	vector<Customer*> customers;
	/*Read one line of the Items.txt file to check which rental type the line is*/
	static void readOneItemInItemFile(ifstream& filein, Item* item, string& genre);
	static int checkTypeItem(Item* item);
	static void readFileItem(ifstream& filein, vector<Item*>& items);
public:
	
	RentalShop(ifstream& filein);
	~RentalShop();
	
	/*getter*/
	vector<Customer*> getCustomers();
	vector<Item*> getItems();
	/*setter*/
	void setCustomers(vector<Customer*> customers);
	void setItems(vector<Item*> items);




	/*delete vector pointer*/
	void deletePointerVector();
	
	
};

