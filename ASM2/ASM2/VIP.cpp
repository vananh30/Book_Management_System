#include "VIP.h"
VIP::VIP() {

}
VIP::VIP(Customer* cus) {
	this->id = cus->getID();
	this->name = cus->getName();
	this->address = cus->getAdress();
	this->phone = cus->getPhone();
	this->numOfRentals = cus->getnumOfRentals();
	this->customerType = cus->getcustomerType();
	this->listOfRentals = cus->getListOfRentals();
}
VIP::~VIP() {

}
string VIP::toString() {
	return "hi";
}