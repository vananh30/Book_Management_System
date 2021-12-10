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

void RentalShop::readOneItemInItemFile(ifstream& filein, Item* item, string& genre) {
    // initialize seven variables to store 
    string id;
    string title;
    string rentalType;
    int numLoanType;
    string loanType;
    int numOfCopy;
    float fee;
    // read id
    getline(filein, id, ',');
    // read title
    getline(filein, title, ',');
    // read rental  type
    getline(filein, rentalType, ',');
    // check what type of rental Type
    item->setID(id);
    item->setTitle(title);
    item->setRentalType(rentalType);
    // set loanType and numLoanType
    filein >> numLoanType;
    item->setNumLoanType(numLoanType);
    filein.seekg(1, ios_base::cur); // exclude 1 byte of the character "-"
    getline(filein, loanType, ',');
    item->setLoanType(loanType);
    // set number of copy, fee, genre
    filein >> numOfCopy;
    item->setNumOfCopy(numOfCopy);
    filein.seekg(1, ios_base::cur); // exclude 1 byte of the character "-"
    filein >> fee;
    item->setFee(fee);
    // check rental type of the Item object
    if (item->getRentalType() == "Record" || item->getRentalType() == "DVD") {
        filein.seekg(1, ios_base::cur); // exclude 1 byte of the character "," 
        getline(filein, genre);
    }
    else {
        string temp; // read the "\n" of the line
        getline(filein, temp);      
    }

    
    
}
/*Check type of item
    return 2 : Record
    return 1: DVDs
    return 0: Game*/
int RentalShop::checkTypeItem(Item* item) {
    if (item->getRentalType() == "Record") {
        return 2;
    }
    else if (item->getRentalType() == "DVD") {
        return 1;
    }
    else if (item->getRentalType() == "Game") {
        return 0;
    }
    // cout << "Invalid Type!";
    return -1;
}

/*Read file and classofy the Item then add to vector Item*/
void RentalShop::readFileItem(ifstream& filein, vector<Item*>& items) {
    string temp; // initialize to check "#" before
   // move the pointer to the start of the line
    int space_back = 0; // the size to move back
    int temp_space_back = 0;
    for (;;) {
        if (!filein) break; // read until the end of the file
        getline(filein, temp);
        space_back = filein.tellg();
        if (temp[0] != '#') break; // check the first element is "#" then break
        temp_space_back = space_back;
    }
    filein.seekg(temp_space_back - space_back, ios_base::cur);  // move back
    for (;;) {
        if (!filein) break; // read until the end of the file
            Item* item = new Item();
            string genre = "";
            readOneItemInItemFile(filein, item, genre);
            int checkType = checkTypeItem(item);
            if (checkType == 2) {
                MovieRecords* mv = new MovieRecords(item);
                mv->setGenres(genre);
                items.push_back(mv);
            }
            else if (checkType == 1) {
                DVDs* dvd = new DVDs(item);
                dvd->setGenres(genre);
                items.push_back(dvd);
            }
            else if (checkType == 0) {
                Games* game = new Games(item);
                items.push_back(game);
            }
        }  
}

/*=====================================================
=========================CUSTOMER======================
==========================================================*/
/*read one line of the item in Customer file*/

void RentalShop::readOneCustomerInCustomerFile(ifstream& filein, Customer* customer) {
    // initialize seven variables to store
    string id;
    string name;
    string address;
    string phone;
    int numOfRentals;
    string customerType;
    vector<string> listItem;
    // read id
    getline(filein, id, ',');
    // read title
    getline(filein, name, ',');
    // read rental  type
    getline(filein, address, ',');
    getline(filein, phone, ',');
    filein >> numOfRentals;
    filein.seekg(1, ios_base::cur); // exclude 1 byte of the character ","
    filein >> customerType;
    string items;
    // check the number of rental 
    if (numOfRentals != 0) {
        for (int i = 0; i < numOfRentals; i++) {
            filein >> items;
            listItem.push_back(items);
        }
    }
    string temp; // read the "\n" of the line
    getline(filein, temp);
    customer->setAll(id, name, address, phone, numOfRentals, customerType, listItem);
}

/*Read file and classofy the Item then add to vector Item*/
void RentalShop::readFileCustomer(ifstream& filein, vector<Customer*>& customers) {

    string temp; // initialize to check "#" before
    // move the pointer to the start of the line
    int space_back = 0; // the size to move back
    int temp_space_back = 0;
    for (;;) {
        if (!filein) break; // read until the end of the file
        getline(filein, temp);
        space_back = filein.tellg();
        if (temp[0] != '#') break; // check the first element is "#" then break
        temp_space_back = space_back;
    } 
    filein.seekg(temp_space_back - space_back, ios_base::cur);  // move back
    for (;;) {
        if (!filein) break;
        Customer* customer = new Customer();
        readOneCustomerInCustomerFile(filein, customer);
        if (customer->getcustomerType() == "VIP") {
            VipAccount* vip = new VipAccount(customer);
            customers.push_back(vip);
        }
        else if (customer->getcustomerType() == "Guest") {
            GuestAccount* guest = new GuestAccount(customer);
            customers.push_back(guest);
        }
        else if (customer->getcustomerType() == "Regular") {
            RegularAccount* regular = new RegularAccount(customer);
            customers.push_back(regular);
        }     
        }
}
/*Constructor*/
RentalShop::RentalShop(ifstream& fileinItem, ifstream& fileinCustomer) {
    vector<Item*> items;
    readFileItem(fileinItem, items);
    this->items = items;

    vector<Customer*> customers;
    readFileCustomer(fileinCustomer, customers);
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

    for (int i = 0; i < items.size(); i++) {
        cout << items[i]->toString() << endl;
    }

}

