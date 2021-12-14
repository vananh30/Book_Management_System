#include "RentalShop.h"
/*getter*/

vector<Customer*> RentalShop::getCustomers() {
    return this->customers;
}

vector<Item*> RentalShop::getItems() {
    return this->items;
}
/*setter*/
void RentalShop::setCustomers(vector<Customer*> customers) {
    this->customers = customers;
}
void RentalShop::setItems(vector<Item*> items) {
    this->items = items;
}

/*Constructor*/
RentalShop::RentalShop(ifstream& fileinItem, ifstream& fileinCustomer) {
    Validation* vl = new Validation(fileinItem, fileinCustomer);
    vector<Item*> items;
    vl->readFileItem(fileinItem, items);
    this->items = items;

    vector<Customer*> customers;
    vl->readFileCustomer(fileinCustomer, customers);
    this->customers = customers;
}
RentalShop::~RentalShop() {
   
}



/*delete pointer vector*/
void RentalShop::deletePointerVector() {
    for (int i = 0; i < items.size(); i++) {
        delete items[i];
    }
    items.clear();
    for (int i = 0; i < customers.size(); i++) {
        delete customers[i];
    }
    customers.clear();
}

/*delete pointer vector*/
void RentalShop::printAll() {
    
     for (int i = 0; i < customers.size(); i++) {
        cout << customers[i]->toString() << endl;
    }
     /*
    for (int i = 0; i < items.size(); i++) {
        cout << items[i]->toString() << endl;
    }
    */

}

