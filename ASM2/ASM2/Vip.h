#pragma once
#include "Customer.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Vip : public Customer
{
public:
	Vip();
	Vip(Customer* cus);
	~Vip();
	string toString();

};

