#include "Vip.h"
Vip::Vip() {

}
Vip::Vip(Customer *cus) {
	this->id = cus->getID();
	this->address = cus->getAdress();
	this->name = this->getName();
	this->phone = this->getPhone();
	this->numOfRentals = this->getnumOfRentals();
	this->customerType = this->getcustomerType();
	this->listOfRentals = this->getListOfRentals();
}
Vip::~Vip() {

}
string Vip::toString() {
	return Customer::toString() + "\nVIP object!";
}