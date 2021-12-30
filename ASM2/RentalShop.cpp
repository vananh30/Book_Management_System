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
    vector<Customer*> customers;
    vl->readFileCustomer(fileinCustomer, customers);
    vl->checkCustomerAndItems(items, customers);
    this->items = items;
    this->customers = customers;
}
RentalShop::~RentalShop() {

}
/*Add item*/
void RentalShop::addItem() {
        //add item
        vector<Item*> items_list;
        Item* item = new Item;
        vector<string> IDs = this->IDs();
        string id;
        string title;
        string rentalType;
        int numLoanType;
        string loanType;
        string numOfCopy;
        string fee;
        string genre;
        Validation* vl = new Validation();
        // read id
        cout << "\nPlease put in the id for the new item: ";
        getline(cin, id);
        // check if the ID is right format
        if (vl->validateIdItem(id)) {
            bool is_exist = false;
            // check if item already exist
            for (int i = 0; i < this->items.size(); i++) {
                if (id == items[i]->getID()) {
                    cerr << "The item ID input is already exist!\n";
                    is_exist = true;
                    break;
                }
            }
            if (is_exist == false) {
                cout << "Please put in the title for the new item: \n";
                getline(cin, title);
                // check if title is null or not
                if (vl->checkNullField(title)) {
                    // read rental  type
                    cout << "Please put in the rental type for the new item\n";
                    cout << "1. Record\n";
                    cout << "2. DVD\n";
                    cout << "3. Game\n";
                    cout << "Your choice [1 - 3]: ";
                    int rentalTypeChoice = this->takeChoice(3);
                    if (rentalTypeChoice == 1 || rentalTypeChoice == 2) {
                        cout << "Please put in the genre for the new item\n"
                            "1. Action\n"
                            "2. Drama\n"
                            "3. Comedy\n"
                            "4. Horror \n"
                            "Your choice: ";
                        int genreChoice = this->takeChoice(4);
                        if (rentalTypeChoice == 1) {
                            rentalType = "Record";
                        }
                        else if (rentalTypeChoice == 2) {
                            rentalType = "DVD";
                        }
                        if (genreChoice == 1) {
                            genre = "Action";
                        }
                        else if (genreChoice == 2) {
                            genre = "Drama";
                        }
                        else if (genreChoice == 3) {
                            genre = "Comedy";
                        }
                        else if (genreChoice == 4) {
                            genre = "Horror";
                        }
                    }
                    else if (rentalTypeChoice == 3) {
                        rentalType = "Game";
                    }
                    // get loanType and numLoanType
                    cout << "Please put in the loan type for the new item\n"
                        "1. 2-day\n"
                        "2. 1-week\n"
                        "Your choice: ";
                    int loanTypeChoice = this->takeChoice(2);
                    if (loanTypeChoice == 1) {
                        numLoanType = 2;
                        loanType = "day";
                    }
                    else if (loanTypeChoice == 2) {
                        numLoanType = 2;
                        loanType = "week";
                    }
                    // set number of copy, fee, genre
                    cout << "Please put in the number of copies available for the new item: ";
                    getline(cin, numOfCopy);
                    if (vl->checkInt(numOfCopy)) {
                        if (atoi(numOfCopy.c_str()) == 0) {
                            item->setStatus(false);
                        }
                        else {
                            item->setStatus(true);
                        }
                        // checkFee
                        cout << "Please put in the rental fee for the new item: ";
                        getline(cin, fee);
                        if (vl->checkFee(fee)) {
                            item->setAll(id, title, rentalType, numLoanType, loanType, atoi(numOfCopy.c_str()), stof(fee));
                            if (rentalTypeChoice == 1) {
                                MovieRecords* mv = new MovieRecords(item);
                                mv->setGenres(genre);
                                items_list = this->items;
                                // add mv to items_list
                                items_list.push_back(mv);
                                // set items_list as this->items
                                this->setItems(items_list);
                                cout << "New Item added: \n";
                                cout << mv->toString();
                            }
                            else if (rentalTypeChoice == 2) {
                                DVDs* dvd = new DVDs(item);
                                dvd->setGenres(genre);
                                items_list = this->items;
                                // add mv to items_list
                                items_list.push_back(dvd);
                                // set items_list as this->items
                                this->setItems(items_list);
                                cout << "New Item added: \n";
                                cout << dvd->toString();
                            }
                            else if (rentalTypeChoice == 3) {
                                Games* game = new Games(item);
                                items_list = this->items;
                                // add mv to items_list
                                items_list.push_back(game);
                                // set items_list as this->items
                                this->setItems(items_list);
                                cout << "New Item added: \n";
                                cout << game->toString();
                            }
                        }
                    }

                }
                else {
                    cerr << "Title cannot be null! \n";
                    }
            }
           
        }
        else {
             cerr << "Id item is wrong format! \n";
        }
        items_list.clear();
}
/*delte item*/
bool RentalShop::deleteItem(string input)
{
    int size = this->items.size();
    string check;
    for (int i = 0; i < size; i++) {
        string check = this->items[i]->getID();
        if (searchItemID(input) != NULL) {
            if (check == input) {
                items.erase(this->items.begin() + i);
                return true;
            }
        }
        else {
            cout << "Your ID item does not existing in the database\n" << endl;
            return false;
        }
    }
}
/*update TITLE item*/
void RentalShop::updateTitleItem(int position) {
    cout << "Your selected item: \n";
    cout << items[position]->toString();
    Validation *vl = new Validation();
    string title;
    cout << "Please put in a new title for the item: ";
    getline(cin, title);
    if (vl->checkNullField(title)) {
        items[position]->setTitle(title);
        cout << "The updated item: \n";
        cout << items[position]->toString();
        return;
    }
    else {
        cerr << "Title cannot be null!";
    }
}
/*update Rental Type*/
void RentalShop::updateRentalTypeItem(int position) {
    cout << "Your selected item: \n";
    cout << items[position]->toString();
    cout
        << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n"
        "Please choose the rental type you want to change to: \n"
        "1. DVD\n"
        "2. Record\n"
        "3. Game\n"
        "Your choice: ";
    int newRentalType = this->takeChoice(3);
    if (newRentalType == 1) { //change type to DVD
        if (this->items[position]->getRentalType() == "DVD") {
            cout << "This item is already DVD \n";
        }
        else {
            DVDs* dvd = new DVDs();
            dvd->setAll(
                this->items[position]->getID(),
                this->items[position]->getTitle(),
                "DVD",
                this->items[position]->getNumLoanType(),
                this->items[position]->getLoanType(),
                this->items[position]->getNumOfCopy(),
                this->items[position]->getFee()
            );
            // if the item is record -> dvd
            if (this->items[position]->getRentalType() == "Record") {
                dvd->setGenres(this->items[position]->getGenres());
            }
            else {
                cout << "Your previous rental type is Game, therefore, you have to choose a Genre for the new DVD items: \n";
                cout << "Please put in the genre for the new item\n"
                    "1. Action\n"
                    "2. Drama\n"
                    "3. Comedy\n"
                    "4. Horror \n"
                    "Your choice: ";
                int newGenre = this->takeChoice(4);
                if (newGenre == 1) dvd->setGenres("Action");
                if (newGenre == 2) dvd->setGenres("Drama");
                if (newGenre == 3) dvd->setGenres("Comedy");
                if (newGenre == 4) dvd->setGenres("Horror");
            }
            dvd->setStatus(this->items[position]->getStatus());
            this->items.push_back(dvd); // add the new update item to vector
            this->items.erase(this->items.begin() + position); // delete the old one   
            cout << "The updated item: \n";
            cout << dvd->toString();
        }
    }
    else if (newRentalType == 2) { // change to record
        if (this->items[position]->getRentalType() == "Record") {
            cout << "This item is already Record \n";
        }
        else {
            MovieRecords* mr = new MovieRecords();
            mr->setAll(
                this->items[position]->getID(),
                this->items[position]->getTitle(),
                "Record",
                this->items[position]->getNumLoanType(),
                this->items[position]->getLoanType(),
                this->items[position]->getNumOfCopy(),
                this->items[position]->getFee()
            );
            // if the item is dvd -> record
            if (this->items[position]->getRentalType() == "DVD") {
                mr->setGenres(this->items[position]->getGenres());
            }
            else {
                cout << "Your previous rental type is Game, therefore, you have to choose a Genre for the new Record items: \n";
                cout << "Please put in the genre for the new item\n"
                    "1. Action\n"
                    "2. Drama\n"
                    "3. Comedy\n"
                    "4. Horror \n"
                    "Your choice: ";
                int newGenre = this->takeChoice(4);
                if (newGenre == 1) mr->setGenres("Action");
                if (newGenre == 2) mr->setGenres("Drama");
                if (newGenre == 3) mr->setGenres("Comedy");
                if (newGenre == 4) mr->setGenres("Horror");
            }
            
            mr->setStatus(this->items[position]->getStatus());
            this->items.push_back(mr); // add the new update item to vector
            this->items.erase(this->items.begin() + position); // delete the old one
            cout << "The updated item: \n";
            cout << mr->toString();
        }
    }
    else if (newRentalType == 3) { // change to game
        cout << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n";
        if (this->items[position]->getRentalType() == "Game") {
            cout << "This item is already Game \n";
        }
        else {
            Games* game = new Games();
            game->setAll(
                this->items[position]->getID(),
                this->items[position]->getTitle(),
                "Game",
                this->items[position]->getNumLoanType(),
                this->items[position]->getLoanType(),
                this->items[position]->getNumOfCopy(),
                this->items[position]->getFee()
            );
            
            game->setStatus(this->items[position]->getStatus());
            this->items.push_back(game); // add the new update item to vector
            this->items.erase(this->items.begin() + position); // delete the old one
            cout << "The updated item: \n";
            cout << game->toString();
        }
    }
}
/*update loan Type*/
void RentalShop::updateLoanTypeItem(int position) {
    cout << "Your selected item: \n";
    cout << items[position]->toString();
    cout << "Please choose the rental type you want to change to: \n"
        "1. 2-day\n"
        "2. 1-week\n"
        "Your choice: ";
    int choice = this->takeChoice(2);
    if (choice == 1) {
        if (items[position]->getLoanType() == "day" && items[position]->getNumLoanType() == 2) {
            cout << "This item loan type is already for 2 days \n";
        }
        else {
            this->items[position]->setLoanType("day");
            this->items[position]->setNumLoanType(2);
        }
    }
    else if (choice == 2) {
        if (items[position]->getLoanType() == "week" && items[position]->getNumLoanType() == 1) {
            cout << "This item loan type is already for 1 week \n";
        }
        else{
            this->items[position]->setLoanType("week");
            this->items[position]->setNumLoanType(1);
        }
    }
    cout << "The updated item: \n";
    cout << items[position]->toString();
}
/*update num of copies*/
void RentalShop::updateNumOfCopyItem(int position) {
    cout << "Your selected item: \n";
    cout << items[position]->toString();
    string numofCopy;
    Validation* vl = new Validation();
    cout << "Please put in the amount of copy available for the item: ";
    getline(cin, numofCopy);
    if (vl->checkInt(numofCopy)) {
        this->items[position]->setNumOfCopy(atoi(numofCopy.c_str()));
        if (atoi(numofCopy.c_str()) == 0) {
            this->items[position]->setStatus(false);
        }
        else {
            this->items[position]->setStatus(true);
        }    
    }
    else {
        cout << "Please enter an integer! \n";
    }
    cout << "The updated item: \n";
    cout << items[position]->toString();
}
/*update fee*/
void RentalShop::updateFeeItem(int position) {
    cout << "Your selected item: \n";
    cout << items[position]->toString();
    Validation* vl = new Validation();
    string fee;
    cout << "Please put in the cost to rent this item: ";
    getline(cin, fee);
    if (vl->checkFee(fee)) {
        this->items[position]->setFee(stof(fee));
    }
    else {
        cout << "Please enter the right type for fee!";
    }
    cout << "The updated item: \n";
    cout << items[position]->toString();
}
/*update Status*/
void RentalShop::updateStatusItem(int position) {
    cout << "Your selected item: \n";
    cout << items[position]->toString();
    Validation* vl = new Validation();
    cout
        << "Reminder: If you change the status of the item, the number of copy will change accordingly!";
    cout << "Please enter the status you wish to change for this item to: \n"
        "1. Borrowed\n"
        "2. available\n"
        "Your choice: ";
    int status = this->takeChoice(2);
    if (status == 1) {
        if (this->items[position]->getStatus()) {
            this->items[position]->setStatus(false);
            this->items[position]->setNumOfCopy(0);
        }
        else {
            cout << "The item is already borrowed and there is no more stock available";
        }
    }
    else if (status == 2) {
        if (this->items[position]->getStatus()) {
            cout << "The item is already available!";
        }
        else {
            this->items[position]->setStatus(true);
            string numberOfCopy;
            while (true) {
                cout << "Please put in the number of copy this item: ";
                getline(cin, numberOfCopy);
                if (vl->checkInt(numberOfCopy)) {
                    this->items[position]->setNumOfCopy(atoi(numberOfCopy.c_str()));
                    break;
                }
                else {
                    cout << "Please enter the right type for int!";
                }
            }
        }
    }
    cout << "The updated item: \n";
    cout << items[position]->toString();
}
void RentalShop::updateGenreItem(int position) {
    cout << "Your selected item: \n";
    cout << items[position]->toString();
    Validation* vl = new Validation();
    if (this->items[position]->getRentalType() == "Game") {
        cerr << "Game item does not have genre! \n";
    }
    else {
        cout << "Please put in the genre for the new item\n"
            "1. Action\n"
            "2. Drama\n"
            "3. Comedy\n"
            "4. Horror \n"
            "Your choice: ";
        int genreChoice = this->takeChoice(4);
        if (genreChoice == 1) {
            this->items[position]->setGenres("Action");
        }
        else if (genreChoice == 2) {
            this->items[position]->setGenres("Drama");
        }
        else if (genreChoice == 3) {
            this->items[position]->setGenres("Comedy");
        }
        else if (genreChoice == 4) {
            this->items[position]->setGenres("Horror");
        }
        cout << "The updated item: \n";
        cout << items[position]->toString();
    }
  
}
/*add customer*/
void RentalShop::addCustomer() {
    // initialize seven variables to store
    string id;
    string name;
    string address;
    string phone;
    string numOfRentals;
    string customerType;
    vector<string> listItem;
    Validation* vl = new Validation();
    vector<string> CUSs = this->CusIDS();
    Customer* cus = new Customer();
    // read id
    while (true) {
        cout << "\nPlease put in the ID for the new customer: ";
        getline(cin, id);
        if (this->searchCusID(id) != NULL) {
            cout << "Wrong input format for ID customer. Your ID custormer has existing in database\n" << endl;
        }
        if (this->searchCusID(id) == NULL && vl->validateIdCus(id)) { break; }
    }
    // read Name
    while (true) {
        cout << "\nPlease put in the Name for the new customer: ";
        getline(cin, name);
        if (!vl->checkNullField(name)) {
            cout << "Wrong input format for Name customer. \n" << endl;
        }
        else {
            break;
        }

    }
    // read address
    while (true) {
        cout << "\nPlease put in the Address for the new customer: ";
        getline(cin, address);
        if (!vl->checkNullField(address)) {
            cout << "Wrong input format for Address customer. \n" << endl;
        }
        else {
            break;
        }

    }
    // read phone
    while (true) {
        cout << "\nPlease put in the Phone for the new customer: ";
        getline(cin, phone);
        if (!vl->checkInt(phone)) {
            cout << "Wrong input format for Phone customer. \n" << endl;
        }
        else {
            break;
        }
    }
    // read the Type of customer
    cout << "Please choose the customer kind for this account: \n"
        "1. Guest\n"
        "2. Regular\n"
        "3. VIP\n"
        "Your choice: ";
    int customerkind = this->takeChoice(3);
    if (customerkind == 1) {
        customerType = "Guest";
    }
    else if (customerkind == 2) {
        customerType = "Regular";
    }
    else if (customerkind == 3) {
        customerType = "VIP";
    }
    // read Number of Rental
    int num_available = 0;
    int num_1_week_available = 0;
    int num_rent = 0;
    while (true) {
        cout << "\nPlease put in the Number of Rental  for the new customer: ";
        getline(cin, numOfRentals);
        if (!vl->checkInt(numOfRentals)) {
            cout << "Wrong input format for Number of Rental customer. \n" << endl;
        }
        else {
            num_rent = atoi(numOfRentals.c_str());
            // check the number of rent
            if (num_rent == 0) {
                break;
            }
            else {
                if (customerkind == 1 && num_rent > 2) {
                    cerr << "Guest cannot borrow more than two items! \n";
                }
                else {
                    // count the number of item now available
                    for (int i = 0; i < this->items.size(); i++) {
                        if (this->items[i]->getStatus() == true) {
                            num_available++;
                            if (this->items[i]->getLoanType() == "week") num_1_week_available++;
                        }
                    }
                    if (num_rent <= num_available) {
                        if (customerkind == 1) {
                            if (num_rent <= num_1_week_available) {
                                break;
                            }
                            else {
                                cerr << "Our shope have " << num_1_week_available << " items 1-week available for Guest Account, plase rent the number smaller than! \n";
                            }
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        cerr << "Our shope have " << num_available << " items available, plase rent the number smaller than! \n";
                    }
                }
            }
        }
    }
    // read list of item
    if (num_rent != 0) {
        cout << "num_rent: " << num_rent << endl;
        if (customerkind == 1) {
            cout << "We have " << num_1_week_available << " items are avalable for Guest! \n";
            for (int i = 0; i < this->items.size(); i++) {
                if (this->items[i]->getLoanType() == "week" && this->items[i]->getStatus() == true) cout << items[i]->toString();
            }
        }
        else {
            cout << "We have " << num_available << " items are avalable! \n";
            for (int i = 0; i < this->items.size(); i++) {
                if (this->items[i]->getStatus() == true) cout << items[i]->toString();
            }
        }
        // read list of items
        while (true) {
            if (num_rent == listItem.size()) break;
            cout << "Please enter the ID of the item that the customer want to loan: ";
            string item_loan = "";
            getline(cin, item_loan);
            // check if the ID is exist in the Items list or not
            bool is_exist = false;
            int item_position = -1;
            for (int i = 0; i < this->items.size(); i++) {
                if (this->items[i]->getID() == item_loan) {
                    is_exist = true;
                    item_position = i;
                    break;
                }
            }
            if (is_exist) {
                // check if the item is avalable or not
                if (this->items[item_position]->getNumOfCopy() == 0) {
                    cerr << "This items is out of stock! \n";
                }
                else {
                    // check if a Guest
                    if (customerkind == 1 && this->items[item_position]->getLoanType() == "day") {
                        cerr << "Guest customer cannot borrowed 2-day item! \n";
                    }
                    else {
                        // check if the item is borrowed by this customer or not
                        if (vl->checkIdItem(item_loan, listItem)) {
                            // minus the number of copy of this item
                            this->items[item_position]->setNumOfCopy(this->items[item_position]->getNumOfCopy() - 1);
                            // set the status to false if it is out of stock
                            if (this->items[item_position]->getNumOfCopy() == 0) this->items[item_position]->setStatus(false);
                        }
                    }
                }
            }
            else {
                cerr << "ID item input does not exist! \n";
            }
        }
    }
    // add customer
    if (vl->checkCustomer(id, CUSs, name, address, phone, numOfRentals, customerType, listItem)) {
        cout << "\nSUCCESSFULLY ADDING NEW CUSTOMER" << endl;
        cus->setAll(id, name, address, phone, num_rent, customerType, listItem);
        if (cus->getcustomerType() == "VIP") {
            VipAccount* vip = new VipAccount(cus);
            vip->setRewardPoint(vip->getnumOfRentals());
            vector<Customer*> customers = this->getCustomers();
            customers.push_back(vip);
            this->setCustomers(customers);
        }
        else if (cus->getcustomerType() == "Guest") {
            GuestAccount* guest = new GuestAccount(cus);
            vector<Customer*> customers = this->getCustomers();
            customers.push_back(guest);
            this->setCustomers(customers);
        }
        else if (cus->getcustomerType() == "Regular") {
            RegularAccount* regular = new RegularAccount(cus);
            vector<Customer*> customers = this->getCustomers();
            customers.push_back(regular);
            this->setCustomers(customers);
        }
        cout << "New customer added: " << endl;
        cout << cus->toString();
    }
}
/*Start Search*/
vector<Item*> RentalShop::searchNoCopy() {
    vector<Item*> result;
    int size = this->items.size();
    for (int i = 0; i < size; i++) {
        if (this->items[i]->getNumOfCopy() == 0) {
            result.push_back(this->items[i]);
        }
    }
    return result;
}

vector<Item*> RentalShop::searchItemTitle(string title) {
    vector<Item*> result;
    int size = this->items.size();
    for (int i = 0; i < size; i++) {
        if (this->items[i]->getTitle() == title) {
            result.push_back(this->items[i]);
        }
    }
    return result;
}

Item* RentalShop::searchItemID(string ID) {
    int size = this->items.size();
    for (int i = 0; i < size; i++) {
        if (this->items[i]->getID() == ID) {
            return this->items[i];
        }
    }
    return NULL;
}

Customer* RentalShop::searchCusID(string ID) {
    int size = this->customers.size();
    for (int i = 0; i < size; i++) {
        if (this->customers[i]->getID() == ID) {
            return this->customers[i];
        }
    }
    return NULL;
}

vector<Customer*> RentalShop::searchCusName(string name) {
    vector<Customer*> result;
    int size = this->customers.size();
    for (int i = 0; i < size; i++) {
        if (this->customers[i]->getName() == name) {
            result.push_back(this->customers[i]);
        }
    }
    return result;
}
/*End Search*/
//New
vector<string> RentalShop::IDs() {
    vector<string> result;
    int size = this->items.size();
    for (int i = 0; i < size; i++) {
        result.push_back(this->items[i]->getID());
    }
    return result;
}
vector<string> RentalShop::CusIDS() {
    vector<string> result;
    int size = this->items.size();
    for (int i = 0; i < size; i++) {
        result.push_back(this->items[i]->getID());
    }
    return result;
}
//end new
bool RentalShop::returnItem(string input, string item, int typeSearch) {
    int size = this->customers.size();
    string checkCus, checkItem;
    int count = 0;
    if (searchItemID(item) == NULL) {
        cout << "Failed return !!! Your item ID input does not existing in the database" << endl;
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (typeSearch == 0) { checkCus = this->customers[i]->getID(); }
        else if (typeSearch == 1) { checkCus = this->customers[i]->getName(); }
        if (checkCus == input) {
            vector <string> ListOfRental = this->customers[i]->getListOfRentals();
            int sizeItem = this->customers[i]->getListOfRentals().size();
            if (sizeItem == 0 && searchItemID(item) != NULL) {
                cout << "Failed return !!! The list of rental of " << this->customers[i]->getName() << " is null.\n" << endl;
                cout << "CURRENTLY CUSTORMER STATUS" << endl;
                cout << this->customers[i]->toString();
                return true;
            }
            for (int j = 0; j < sizeItem; j++) {
                if (ListOfRental[j] == item) {
                    Item* newitem = searchItemID(ListOfRental[j]);
                    newitem->setNumOfCopy(newitem->getNumOfCopy() + 1);
                    if (newitem->getRentalType() == "DVD") {
                        this->customers[i]->setBorrowedDVD(true);
                    }
                    this->customers[i]->setNumOfRentals(this->customers[i]->getnumOfRentals() - 1);
                    ListOfRental.erase(ListOfRental.begin() + j);
                    this->customers[i]->setListOfRentals(ListOfRental);
                    cout << "Successfully return " << newitem->getTitle() << " item (ID: " << newitem->getID() << ") for " << this->customers[i]->getName() << ".\n" << endl;
                    cout << "CURRENTLY CUSTORMER STATUS" << endl;
                    cout << this->customers[i]->toString() << endl;
                    cout << "\nCURRENTLY ITEM STATUS" << endl;
                    cout << newitem->toString();
                    return true;
                }
                if (ListOfRental[j] != item) { count += 1; }
                if (count == sizeItem) {
                    cout << "Failed return !!! " << this->customers[i]->getName() << " has not rent this item before." << endl;
                    cout << searchItemID(ListOfRental[j])->toString();
                    return true;
                }
            }
        }
    }
    if (typeSearch == 0) { cout << "Your custormer ID input does not existing in the database" << endl; }
    else if (typeSearch == 1) { cout << "Your custormer name input does not existing in the database" << endl; }
    return false;
}

Customer* RentalShop::promoteCusID(string input, int type, int typeSearch) {
    int size = this->customers.size();
    string check;
    for (int i = 0; i < size; i++) {
        if (typeSearch == 0) {
            check = this->customers[i]->getID();
        }
        else if (typeSearch == 1) {
            check = this->customers[i]->getName();
        }
        if (check == input) {
            if (type == 0 && this->customers[i]->getcustomerType() == "Guest") {
                if (this->customers[i]->getBorrowedDVD() < 3) {
                    cout << "This member is not eligible to promote to Regular\n" << endl;
                    cout << "This member need to rent and return successfully " << 3 - this->customers[i]->getBorrowedDVD() << " DVD items left!\n" << endl;
                    return this->customers[i];
                }
                else if (this->customers[i]->getBorrowedDVD() >= 3) {
                    cout << "Successfully promote " << this->customers[i]->getName() << " to Regular member\n" << endl;
                    this->customers[i]->setcustomerType("Regular");
                    RegularAccount* newRegular = new RegularAccount(this->customers[i]);
                    customers.push_back(newRegular);
                    this->customers.erase(this->customers.begin() + i);
                    return newRegular;
                }
            }
            else if (type == 0 && this->customers[i]->getcustomerType() == "Regular") {
                cout << "This is already Regular member\n" << endl;
                return this->customers[i];
            }
            else if (type == 0 && this->customers[i]->getcustomerType() == "VIP") {
                cout << "This is already VIP member can not promote to Regular\n" << endl;
                return this->customers[i];
            }
            if (type == 1 && this->customers[i]->getcustomerType() == "Regular") {
                if (this->customers[i]->getBorrowedDVD() < 3) {
                    cout << "This member is not eligible to promote to VIP\n" << endl;
                    cout << "This member need to rent and return successfully " << 3 - this->customers[i]->getBorrowedDVD() << " DVD items left" << endl;
                    return this->customers[i];
                }
                else {
                    cout << "Successfully promote " << this->customers[i]->getName() << " to VIP member\n" << endl;
                    this->customers[i]->setcustomerType("VIP");
                    VipAccount* newVip = new VipAccount(this->customers[i]);
                    this->customers.push_back(newVip);
                    this->customers.erase(this->customers.begin() + i);
                    return newVip;
                }
            }
            else if (type == 1 && this->customers[i]->getcustomerType() == "VIP") {
                cout << "This is already VIP member\n" << endl;
                return this->customers[i];
            }
            else if (type == 1 && this->customers[i]->getcustomerType() == "Guest") {
                cout << "This is Guest member can not promote to VIP member\n" << endl;
                return this->customers[i];
            }
        }
    }
    cout << "Your input does not existing in the database\n" << endl;
    return NULL;
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

/*Start Display*/
void RentalShop::displayNoCopy() {
    int size = this->items.size();
    for (int i = 0; i < size; i++) {
        if (this->items[i]->getNumOfCopy() == 0) {
            cout << this->items[i]->toString() << '\n';
        }
    }
}

void RentalShop::display(vector<Item*> obj) {
    int size = obj.size();
    for (int i = 0; i < size; i++) {
        cout << obj[i]->toString() << '\n';
    }
}

void RentalShop::display(vector<Customer*> obj) {
    int size = obj.size();
    for (int i = 0; i < size; i++) {
        cout << obj[i]->toString() << '\n';
    }
}


void RentalShop::displayGroup(string groupType) {
    int size = this->customers.size();
    for (int i = 0; i < size; i++) {
        if (this->customers[i]->getcustomerType() == groupType) {
            cout << this->customers[i]->toString() << '\n';
        }
    }
}

void RentalShop::printAll() {
    for (int i = 0; i < customers.size(); i++) {
        cout << customers[i]->toString() << endl;
    }

    for (int i = 0; i < items.size(); i++) {
        cout << items[i]->toString() << endl;
    }
}

void RentalShop::printAllCustomerSortedName(int type) {
    int miniPos;
    if (type == 0) {
        for (unsigned int i = 0; i < customers.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < customers.size(); j++)
            {
                if (customers[j]->getName() < customers[miniPos]->getName()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Customer* temp = customers[miniPos];
            customers[miniPos] = customers[i];
            customers[i] = temp;
        }
    }
    if (type == 1) {
        for (unsigned int i = 0; i < customers.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < customers.size(); j++)
            {
                if (customers[j]->getName() > customers[miniPos]->getName()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Customer* temp = customers[miniPos];
            customers[miniPos] = customers[i];
            customers[i] = temp;
        }
    }

    for (unsigned int i = 0; i < customers.size(); i++) {
        cout << customers[i]->toString() << endl;
    }

}

void RentalShop::printAllCustomerSortedID(int type) {
    int miniPos;
    if (type == 0) {
        for (unsigned int i = 0; i < customers.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < customers.size(); j++)
            {
                if (customers[j]->getID() < customers[miniPos]->getID()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Customer* temp = customers[miniPos];
            customers[miniPos] = customers[i];
            customers[i] = temp;
        }
    }
    if (type == 1) {
        for (unsigned int i = 0; i < customers.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < customers.size(); j++)
            {
                if (customers[j]->getID() > customers[miniPos]->getID()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Customer* temp = customers[miniPos];
            customers[miniPos] = customers[i];
            customers[i] = temp;
        }
    }

    for (unsigned int i = 0; i < customers.size(); i++) {
        cout << customers[i]->toString() << endl;
    }

}

void RentalShop::printAllItemSortedName(int type) {
    int miniPos;
    if (type == 0) {
        for (unsigned int i = 0; i < items.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < items.size(); j++)
            {
                if (items[j]->getTitle() < items[miniPos]->getTitle()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Item* temp = items[miniPos];
            items[miniPos] = items[i];
            items[i] = temp;
        }
    }
    if (type == 1) {
        for (unsigned int i = 0; i < items.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < items.size(); j++)
            {
                if (items[j]->getTitle() > items[miniPos]->getTitle()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Item* temp = items[miniPos];
            items[miniPos] = items[i];
            items[i] = temp;
        }
    }

    for (unsigned int i = 0; i < items.size(); i++) {
        cout << items[i]->toString() << endl;
    }

}

void RentalShop::printAllItemSortedID(int type) {
    int miniPos;
    if (type == 0) {
        for (unsigned int i = 0; i < items.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < items.size(); j++)
            {
                if (items[j]->getID() < items[miniPos]->getID()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Item* temp = items[miniPos];
            items[miniPos] = items[i];
            items[i] = temp;
        }
    }
    if (type == 1) {
        for (unsigned int i = 0; i < items.size(); i++)
        {
            miniPos = i;
            for (unsigned int j = i + 1; j < items.size(); j++)
            {
                if (items[j]->getID() > items[miniPos]->getID()) //Change was here!
                {
                    miniPos = j;
                }
            }

            Item* temp = items[miniPos];
            items[miniPos] = items[i];
            items[i] = temp;
        }
    }

    for (unsigned int i = 0; i < items.size(); i++) {
        cout << items[i]->toString() << endl;
    }

}
/*End Display*/
int RentalShop::takeChoice(int limit) {
    /*
    Choices are between 1 and limit [1 - limit]
    @param limit: the maximum choice for the input (e.g limit = 3 -> 3 choices)
    */
    while (true) {
        string input;
        int choice;
        getline(cin, input);

        while (cin.fail() || cin.eof() || input.find_first_not_of("0123456789") != string::npos || input.size() == 0) {
            cout << "Require number in range [1 - " << limit << "]: ";
            if (input.find_first_not_of("0123456789") == string::npos || input.size() == 0) {
                cin.clear();
                //cin.ignore(256, '\n');
                //cout << "REACH" << '\n';
            }
            getline(cin, input);
        }

        string::size_type st;
        choice = stoi(input, &st);
        if (choice >= 1 && choice <= limit) {
            return choice;
        }
        else {
            cout << "Number must be in range [1 - " << limit << "]: ";
        }
    }
}
