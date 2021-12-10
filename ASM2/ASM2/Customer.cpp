#include "Customer.h"

string Customer::getID() {
	return this->id;
}
string Customer::getName() {
	return this->name;
}
string Customer::getAdress() {
	return this->address;
}
string Customer::getPhone() {
	return this->phone;
}
int Customer::getnumOfRentals() {
	return this->numOfRentals;
}
string Customer::getcustomerType() {
	return this->customerType;
}
vector<string> Customer::getListOfRentals() {
	return this->listOfRentals;
}
void Customer::setID(string id) {
	this->id = id;
}
void Customer::setName(string name) {
	this->name = name;
}
void Customer::setAddress(string address) {
	this->address = address;
}
void Customer::setPhone(string phone) {
	this->phone = phone;
}
void Customer::setNumOfRentals(int num) {
	this->numOfRentals = num;
}
void Customer::setcustomerType(string type) {
	this->customerType = type;
}
void Customer::setListOfRentals(vector<string> listOfRentals) {
	this->listOfRentals = listOfRentals;
}

/*Constuctor*/
Customer::Customer() {

}
/*Deconstructor*/
Customer::~Customer() {

}
/*toString*/
string Customer::toString() {
	
	// read the list of rentals
	string listRental = "";
	for (int i = 0; i < this->listOfRentals.size(); i++) {
		listRental += listOfRentals[0];
	}
	// return section
	return "Id: " +
		this->id +
		"\nName: " +
		this->getName() +
		"\nAddress: " +
		this->getAdress() +
		"\nPhone: " +
		this->getPhone() +
		"\nNumber of rentals: " +
		to_string(this->getnumOfRentals()) +
		"\nCustomer type: " +
		this->getcustomerType() +
		"\nList of Rental " +
		listRental +  '\n';
}

