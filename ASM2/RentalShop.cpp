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

/*CHECK INPUT FILE FIELD*/
bool RentalShop::checkNullField(string field) {
    if (field == "" || field == "\n") {
        return false;
    }
    /*check if it only contains space*/
    else if (field.find_first_not_of(' ') == field.npos) {
        return false;
    }
    return true;
}
/*check ID Item format*/
bool RentalShop::checkIdItem(string id, vector<string>& IDs) {
    // if id is not a null field
    if (checkNullField(id)) {
        if (id[0] == 'I' && id[4] == '-') {
            bool checkNum = true;
            // check the next 3 digits
            for (int i = 1; i < id.length(); i++) {
                if (i == 4) continue;
                if (!isdigit(id[i])) {
                    checkNum = false;
                }
            }
            if (checkNum) {
                // convert substr from index 5 to a number
                int year = stoi(id.substr(5, id.length() - 5));
                // validate year
                if (year >= 1000 && year <= 2021) {
                    for (int i = 0; i < IDs.size(); i++) {
                        if (id == IDs[i]) {
                            cout << "ID is not unique" << endl;
                            return false;
                        }
                    }
                    IDs.push_back(id);
                    return true;
                }
            }  
        }
        cout << "Wrong ID item format!" << endl;
        return false;
    }
    cout << "ID is empty!" << endl;
    return false;
}
/*check Rental Type*/
bool RentalShop::checkRentalType(string rentalType) {
    if (rentalType == "Game" || rentalType == "DVD" || rentalType == "Record") { 
        return true;
    }
    cout << "Rental type is not Valid!" << endl;
    return false;
}
/*check loan */
void RentalShop::checkLoan(string loan, int& numLoanType, string& loanType) {
    if (checkNullField(loan)) {
        int pos = loan.find('-'); // find the token
        loanType = loan.substr(pos + 1, loan.length());
        if (pos != -1 && (loanType == "day" || loanType == "week")) {
            bool checkNum = true;
            for (int i = 0; i < pos; i++) {
                if (!isdigit(loan[i])) {
                    checkNum = false;
                    numLoanType = -1;
                    return;
                }
            }
            if(checkNum) numLoanType = stoi(loan.substr(0, pos));
        }
        else {
            numLoanType = -1;
            cout << "Wrong loan format!" << endl;
            return;
        }
    }
}
/*check fee*/
void RentalShop::checkFee(string fee, bool &isValid) {
    // Use std::stoi() to convert string to integer
    try {
        // Wrap up code in try-catch block if string is not validated
        float res = stof(fee);
        isValid = true;
        return ;
    }
    catch (std::invalid_argument e) {
        cout << "Fee is not a valid value!\n";
    }
    isValid = false;
    return;
}


void RentalShop::readOneItemInItemFile(ifstream& filein, Item* item, string& genre, vector<string>& IDs) {
    // initialize seven variables to store 
    string id;
    string title;
    string rentalType;
    string loan;
    int numLoanType;
    string loanType;
    int numOfCopy;
    string fee;
    // read id
    getline(filein, id, ',');
    // read title
    getline(filein, title, ',');
    // read rental  type
    getline(filein, rentalType, ',');
    // get loanType and numLoanType
    getline(filein, loan, ',');
    checkLoan(loan, numLoanType, loanType);
    // set number of copy, fee, genre
    filein >> numOfCopy;
    filein.seekg(1, ios_base::cur); // exclude 1 byte of the character "-"

    // check rental type of the Item object
    if (rentalType == "Record" || rentalType == "DVD") {
        getline(filein, fee, ',');
        getline(filein, genre);
    }
    else {
        filein >> fee;
        string temp; // read the "\n" of the line
        getline(filein, temp);
    } 
    if (true) {
        item->setAll(id, title, rentalType, numLoanType, loanType, numOfCopy, stof(fee));
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
    vector<string> IDs;
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
            readOneItemInItemFile(filein, item, genre, IDs);
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
    IDs.clear();
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
    /*
    * for (int i = 0; i < customers.size(); i++) {
        cout << customers[i]->toString() << endl;
    }
    */
    

    for (int i = 0; i < items.size(); i++) {
        cout << items[i]->toString() << endl;
    }

}

