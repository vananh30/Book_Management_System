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
    filein.seekg(1, ios_base::cur); // exclude 1 byte of the character "-" 

    // check rental type of the Item object
    if (item->getRentalType() == "Record" || item->getRentalType() == "DVD") {
        getline(filein, genre);
    }
    else {
        string temp;
        getline(filein, temp);
    }
    // create a temp that read '\n'    
}
/*Check type of item
    return 2 : Record
    return 1: DVDs
    return 0: Game*/
int RentalShop::checkTypeItem(Item* item) {
    if (item->getRentalType() == "Record") {
        return 2;
    }
    else if (item->getRentalType() == "DVDs") {
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
    // con tro o cuoi file thi dung
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

/*Constructor*/
RentalShop::RentalShop(ifstream& filein) {
    vector<Item*> items;
    readFileItem(filein, items);
    this->items = items;
    // clear memory
    cout << this->items[0]->getID() << endl;
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

