#include "Interface.h"

Interface::Interface() {
    this->menuChoice = 0;
}

void Interface::menu() {
    cout << "Welcome to Genieís video store\n";
    cout << "Enter an option below\n";
    cout << "1.  Add a new item, update or delete an existing item\n";
    cout << "2.  Add new customer or update an existing customer\n";
    cout << "3.  Promote an existing customer\n";
    cout << "4.  Rent an item\n";
    cout << "5.  Return an item\n";
    cout << "6.  Display all items\n";
    cout << "7.  Display out-of-stock items\n";
    cout << "8.  Display all customers\n";
    cout << "9.  Display group of customers\n";
    cout << "10. Search items or customers\n";
    cout << "11. Exit\n";
    cout << "Your choice [1 - 11]: ";
}

void Interface::menu1() {
    cout << "1. Add item\n";
    cout << "2. Update item\n";
    cout << "3. Delete item\n";
    cout << "Your choice [1 - 3]: ";
    int subChoice = this->takeChoice(3);
    if (subChoice == 1) {
        this->rs->addItem();
    }
    else if (subChoice == 2) {
        Validation* vl = new Validation();
        this->rs->printAllItemSortedID(1);
        string ID;
        while (true) {
            cout << "Please write the ID of the item you want to change here: ";
            getline(cin, ID);
            if (vl->validateIdItem(ID)) {
                int position = -1;
                for (int i = 0; i < rs->getItems().size(); i++) {
                    if (ID == rs->getItems()[i]->getID()) {
                        position = i;
                        break;
                    }
                }
                if (position == -1) {
                    cerr << "Id input is not exist in the Item list \n";
                }
                else{
                    cout << "Choose what kind of data you would like to change: \n"
                        "1. Title\n"
                        "2. Rental Type\n"
                        "3. Loan Type\n"
                        "4. Number of Copy\n"
                        "5. Fee\n"
                        "6. Status\n"
                        "7. genre\n"
                        "Your choice: ";
                    int kind = this->takeChoice(7);
                    if (kind == 1) {
                        rs->updateTitleItem(position);
                    }
                    else if (kind == 2) {
                        rs->updateRentalTypeItem(position);
                    }
                    else if (kind == 3) {
                        rs->updateLoanTypeItem(position);
                    }
                    else if (kind == 4) {
                        rs->updateNumOfCopyItem(position);
                    }
                    else if (kind == 5) {
                        rs->updateFeeItem(position);
                    }
                    else if (kind == 6) {
                        rs->updateStatusItem(position);
                    }
                    else if (kind == 7) {
                        rs->updateGenreItem(position);     
                    }
                    break; //break from the big loop and return to
                }
            }
        }
    }
    else if (subChoice == 3) {
    while (true)
    {
        string word;
        cout << "ID items: ";
        getline(cin, word);
        cout << '\n';
        bool newitem = this->rs->deleteItem(word);
        if (newitem) {
            newitem;
            break;
        }
    }
    }
}

void Interface::menu2() {
    cout << "1. Add customer\n";
    cout << "2. Update customer\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    Validation* vl = new Validation();
    if (subChoice == 1) {
        rs->addCustomer();
    }
    else if (subChoice == 2) {
        this->rs->printAllCustomerSortedID(1);
        Validation* vl = new Validation();
        string ID;
        while (true) {
            cout << "Please write the ID of the Customer you want to change here: ";
            getline(cin, ID);
            Customer* update_customer = this->rs->searchCusID(ID);
            if (update_customer == NULL) {
                cout << "You have put in the wrong ID ";
                cout << "Please try again ";
            }
            else if (update_customer->getcustomerType() == "Guest" || update_customer->getcustomerType() == "Regular") {
                cout << "Choose what kind of data you would like to change: \n"
                    "Note: If you change the rental list section, number of rental will also change accordingly.\n"
                    "1. Name\n"
                    "2. Address\n"
                    "3. Phone\n"
                    "4. Customer type\n"
                    "5. Rental list\n"
                    "Your choice: ";
                int kind = this->takeChoice(5);
                if (kind == 1) {
                    string name;
                    cout << "Please put in a new name for the customer: ";
                    getline(cin, name);
                    update_customer->setName(name);
                    break;
                }
                else if (kind == 2) {
                    string address;
                    cout << "Please put in a new address for the customer: ";
                    getline(cin, address);
                    update_customer->setName(address);
                    break;
                }
                else if (kind == 3) {
                    string Phonenumber;
                    cout << "Please put in a new phone number for the customer: ";
                    getline(cin, Phonenumber);
                    update_customer->setName(Phonenumber);
                    break;
                }
                else if (kind == 4) {
                    cout << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n"
                        "Please choose the rental type you want to change to: \n"
                        "1. Guest\n"
                        "2. Regular\n"
                        "3. VIP\n"
                        "Your choice: ";
                    int newcustomertype = this->takeChoice(3);
                    if (newcustomertype == 1) {
                        if (update_customer->getcustomerType() == "Guest") {
                            cout << "This account is already a guest account!";
                        }
                        else if (update_customer->getcustomerType() == "Regular") {
                            vector<Customer*> customers;
                            RegularAccount* newupdatecustomer = new RegularAccount;
                            newupdatecustomer->setAll(
                                update_customer->getID(),
                                update_customer->getName(),
                                update_customer->getAdress(),
                                update_customer->getPhone(),
                                update_customer->getnumOfRentals(),
                                update_customer->getcustomerType(),
                                update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        }
                    }
                    else if (newcustomertype == 2) {
                        if (update_customer->getcustomerType() == "Regular") {
                            cout << "This account is already a regular account!";
                        }
                        else if (update_customer->getcustomerType() == "Guest") {
                            vector<Customer*> customers;
                            GuestAccount* newupdatecustomer = new GuestAccount;
                            newupdatecustomer->setAll(
                                update_customer->getID(),
                                update_customer->getName(),
                                update_customer->getAdress(),
                                update_customer->getPhone(),
                                update_customer->getnumOfRentals(),
                                update_customer->getcustomerType(),
                                update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        }
                    }
                    else if (newcustomertype == 3) {
                        if (update_customer->getcustomerType() == "Regular") {
                            vector<Customer*> customers;
                            RegularAccount* newupdatecustomer = new RegularAccount;
                            newupdatecustomer->setAll(
                                update_customer->getID(),
                                update_customer->getName(),
                                update_customer->getAdress(),
                                update_customer->getPhone(),
                                update_customer->getnumOfRentals(),
                                update_customer->getcustomerType(),
                                update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        }
                        else if (update_customer->getcustomerType() == "Guest") {
                            vector<Customer*> customers;
                            GuestAccount* newupdatecustomer = new GuestAccount;
                            newupdatecustomer->setAll(
                                update_customer->getID(),
                                update_customer->getName(),
                                update_customer->getAdress(),
                                update_customer->getPhone(),
                                update_customer->getnumOfRentals(),
                                update_customer->getcustomerType(),
                                update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        }
                    }
                    break;
                }
                else if (kind == 5) {
                    vector<Item*> items = this->rs->getItems();
                    this->rs->printAllCustomerSortedID(1);
                    cout << "Reminder: Making changes in the list of rental item will also affect the number of rental item!\n";
                    cout << "Please choose what would you like to do with the list of item: \n"
                        "1. Add an item\n"
                        "2. Reduce item\n"
                        "Your choice: \n";
                    int Rentallistchoice = this->takeChoice(2);
                    if (Rentallistchoice == 1) {
                        if (update_customer->getcustomerType() == "Guest") {
                            string item_ID;
                            cout << "List of items available: \n";
                            int vid_borrowed = 0;
                            this->rs->printAllItemSortedID(1);
                            cout << "Reminder: The account that you want to update is a Guest account so you can not borrow 3 or more videos at a time or a 1-week type video!\n";
                            cout << "Please type in the ID of the item that you wish to loan: ";
                            getline(cin, item_ID);
                            if (vl->validateIdItem(item_ID)) {
                                for (int i = 0; i < items.size(); i++) {
                                    if (items[i]->getID() == item_ID) {
                                        vector<string> borrowed_item = update_customer->getListOfRentals();
                                        for (int a = 0; a < borrowed_item.size(); a++) {
                                            if (this->rs->searchItemID(borrowed_item[a])->getRentalType() == "Video" && this->rs->searchItemID(borrowed_item[a])->getLoanType() == "1-week")
                                            {
                                                vid_borrowed += vid_borrowed;
                                            }
                                        }
                                        if (items[i]->getLoanType() == "1-week" && items[i]->getRentalType() == "Video" && vid_borrowed == 2) {
                                            cout << "This account have already rent 2 of 1-week type video so this account can not loan more!";
                                        }
                                        else if (items[i]->getLoanType() == "2-day" && items[i]->getRentalType() == "Video") {
                                            cout << "Guest account can not loan 2-day type video!";
                                        }
                                        else {
                                            if (items[i]->getNumOfCopy() > 0) {
                                                items[i]->setNumOfCopy(items[i]->getNumOfCopy() - 1);
                                                if (items[i]->getNumOfCopy() == 0) {
                                                    items[i]->setStatus(false);
                                                }
                                                update_customer->setNumOfRentals(update_customer->getnumOfRentals() + 1);
                                                update_customer->getListOfRentals().push_back(items[i]->getID());
                                            }
                                            else if (items[i]->getNumOfCopy() == 0) {
                                                cout << "There is no more stock available for this item in stock!";
                                            }
                                        }
                                    }
                                    cout << "You have enter wrong item ID!";
                                    break;
                                }
                            }
                            else {
                                cout << "You have enter the wrong item ID!";
                            }
                        }
                        else if (update_customer->getcustomerType() == "Regular") {
                            string item_ID;
                            cout << "List of items available: \n";
                            int vid_borrowed = 0;
                            this->rs->printAllItemSortedID(1);
                            cout << "Please type in the ID of the item that you wish to loan: ";
                            getline(cin, item_ID);
                            if (vl->validateIdItem(item_ID)) {
                                Item* choosen_item = this->rs->searchItemID(item_ID);
                                if (choosen_item->getNumOfCopy() > 0) {
                                    choosen_item->setNumOfCopy(choosen_item->getNumOfCopy() - 1);
                                    if (choosen_item->getNumOfCopy() == 0) {
                                        choosen_item->setStatus(false);
                                    }
                                    update_customer->setNumOfRentals(update_customer->getnumOfRentals() + 1);
                                    update_customer->getListOfRentals().push_back(choosen_item->getID());
                                }
                                else if (choosen_item->getNumOfCopy() == 0) {
                                    cout << "There is no more stock available for this item in stock!";
                                }
                            }
                            else {
                                cout << "You have enter the wrong item ID";
                            }
                        }
                    }
                    else if (Rentallistchoice == 2) {
                        if (update_customer->getcustomerType() == "Guest") {
                            string item_ID;
                            cout << "List of items that the user currently has: \n";
                            for (int i = 0; i < update_customer->getnumOfRentals(); i++) {
                                cout << this->rs->searchItemID(update_customer->getListOfRentals()[i] + "\n");
                            }
                            cout << "Please type in the ID of the item that you wish to delete: ";
                            getline(cin, item_ID);
                            if (vl->validateIdItem(item_ID)) {
                                bool founditem = false;
                                int position = 0;
                                for (int i = 0; i < items.size(); i++) {
                                    if (items[i]->getID() == item_ID) {
                                        vector<string> borrowed_item = update_customer->getListOfRentals();
                                        for (int i = 0; i < update_customer->getnumOfRentals(); i++) {
                                            if (update_customer->getListOfRentals()[i] == item_ID) {
                                                founditem = true;
                                                position = i;
                                            }
                                        }
                                        if (founditem) {
                                            update_customer->getListOfRentals().erase(update_customer->getListOfRentals().begin() + position);
                                            if (this->rs->searchItemID(item_ID)->getNumOfCopy() == 0) {
                                                this->rs->searchItemID(item_ID)->setStatus(false);
                                            }
                                            this->rs->searchItemID(item_ID)->setNumOfCopy(this->rs->searchItemID(item_ID)->getNumOfCopy() + 1);
                                            update_customer->setNumOfRentals(update_customer->getnumOfRentals() - 1);
                                        }
                                    }
                                    cout << "You have enter wrong item ID!";
                                    break;
                                }
                            }
                            else {
                                cout << "You have enter the wrong item ID!";
                            }
                        }
                        else if (update_customer->getcustomerType() == "Regular") {
                            string item_ID;
                            cout << "List of items that the user currently has: \n";
                            for (int i = 0; i < update_customer->getnumOfRentals(); i++) {
                                cout << this->rs->searchItemID(update_customer->getListOfRentals()[i] + "\n");
                            }
                            cout << "Please type in the ID of the item that you wish to delete: ";
                            getline(cin, item_ID);
                            if (vl->validateIdItem(item_ID)) {
                                bool founditem = false;
                                int position = 0;
                                for (int i = 0; i < items.size(); i++) {
                                    if (items[i]->getID() == item_ID) {
                                        vector<string> borrowed_item = update_customer->getListOfRentals();
                                        for (int i = 0; i < update_customer->getnumOfRentals(); i++) {
                                            if (update_customer->getListOfRentals()[i] == item_ID) {
                                                founditem = true;
                                                position = i;
                                            }
                                        }
                                        if (founditem) {
                                            update_customer->getListOfRentals().erase(update_customer->getListOfRentals().begin() + position);
                                            if (this->rs->searchItemID(item_ID)->getNumOfCopy() == 0) {
                                                this->rs->searchItemID(item_ID)->setStatus(false);
                                            }
                                            this->rs->searchItemID(item_ID)->setNumOfCopy(this->rs->searchItemID(item_ID)->getNumOfCopy() + 1);
                                            update_customer->setNumOfRentals(update_customer->getnumOfRentals() - 1);
                                        }
                                    }
                                    cout << "You have enter wrong item ID!";
                                    break;
                                }
                            }
                            else {
                                cout << "You have enter the wrong item ID!";
                            }
                        }
                    }
                    break;
                }
                else if (kind == 6) {

                }
            }
            else if (update_customer->getcustomerType() == "VIP") {
                cout << "Choose what kind of data you would like to change: \n"
                    "Note: If you change the rental list section, number of rental will also change accordingly.\n"
                    "1. Name\n"
                    "2. Address\n"
                    "3. Phone\n"
                    "4. Customer type\n"
                    "5. Rental list\n"
                    "6. Reward point\n"
                    "Your choice: ";
                int kind = this->takeChoice(6);
                if (kind == 1) {
                    string name;
                    cout << "Please put in a new name for the customer: ";
                    getline(cin, name);
                    update_customer->setName(name);
                    break;
                }
                else if (kind == 2) {
                    string address;
                    cout << "Please put in a new address for the customer: ";
                    getline(cin, address);
                    update_customer->setName(address);
                    break;
                }
                else if (kind == 3) {
                    string Phonenumber;
                    cout << "Please put in a new phone number for the customer: ";
                    getline(cin, Phonenumber);
                    update_customer->setName(Phonenumber);
                    break;
                }
                else if (kind == 4) {
                    cout << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n"
                        "Please choose the rental type you want to change to: \n"
                        "1. Guest\n"
                        "2. Regular\n"
                        "3. VIP\n"
                        "Your choice: ";
                    int newcustomertype = this->takeChoice(3);
                    if (newcustomertype == 1) {
                        vector<Customer*> customers;
                        VipAccount* newupdatecustomer = new VipAccount;
                        newupdatecustomer->setAll(
                            update_customer->getID(),
                            update_customer->getName(),
                            update_customer->getAdress(),
                            update_customer->getPhone(),
                            update_customer->getnumOfRentals(),
                            update_customer->getcustomerType(),
                            update_customer->getListOfRentals());
                        newupdatecustomer->setRewardPoint(newupdatecustomer->getnumOfRentals() * 10);
                        customers = this->rs->getCustomers();
                        customers.push_back(newupdatecustomer);// can't delete the old vector or access the old vector
                        this->rs->setCustomers(customers);
                        cout << "The update process has been successful!";
                    }
                    else if (newcustomertype == 2) {
                        vector<Customer*> customers;
                        VipAccount* newupdatecustomer = new VipAccount;
                        newupdatecustomer->setAll(
                            update_customer->getID(),
                            update_customer->getName(),
                            update_customer->getAdress(),
                            update_customer->getPhone(),
                            update_customer->getnumOfRentals(),
                            update_customer->getcustomerType(),
                            update_customer->getListOfRentals());
                        newupdatecustomer->setRewardPoint(newupdatecustomer->getnumOfRentals() * 10);
                        customers = this->rs->getCustomers();
                        customers.push_back(newupdatecustomer);// can't delete the old vector or access the old vector
                        this->rs->setCustomers(customers);
                        cout << "The update process has been successful!";
                    }
                    else if (newcustomertype == 3) {
                        cout << "This account is already a VIP account!";
                    }
                    break;
                }
                else if (kind == 5) {
                    vector<Item*> items = this->rs->getItems();
                    this->rs->printAllCustomerSortedID(1);
                    cout << "Reminder: Making changes in the list of rental item will also affect the number of rental item!\n";
                    cout << "Please choose what would you like to do with the list of item: \n"
                        "1. Add an item\n"
                        "2. Reduce item\n"
                        "Your choice: ";
                    int Rentallistchoice = this->takeChoice(3);
                    if (Rentallistchoice == 1) {
                        string item_ID;
                        cout << "List of items available: \n";
                        int vid_borrowed = 0;
                        this->rs->printAllItemSortedID(1);
                        cout << "Please type in the ID of the item that you wish to loan: ";
                        getline(cin, item_ID);
                        if (vl->validateIdItem(item_ID)) {
                            Item* choosen_item = this->rs->searchItemID(item_ID);
                            if (choosen_item->getNumOfCopy() > 0) {
                                choosen_item->setNumOfCopy(choosen_item->getNumOfCopy() - 1);
                                if (choosen_item->getNumOfCopy() == 0) {
                                    choosen_item->setStatus(false);
                                }
                                update_customer->setNumOfRentals(update_customer->getnumOfRentals() + 1);
                                update_customer->getListOfRentals().push_back(choosen_item->getID());
                                VipAccount* vip = new VipAccount(update_customer);
                                vip->setRewardPoint(vip->getnumOfRentals() + 10);
                            }
                            else if (choosen_item->getNumOfCopy() == 0) {
                                cout << "There is no more stock available for this item in stock!";
                            }
                        }
                    }
                    else if (Rentallistchoice == 2) {
                        string item_ID;
                        cout << "List of items that the user currently has: \n";
                        for (int i = 0; i < update_customer->getnumOfRentals(); i++) {
                            cout << this->rs->searchItemID(update_customer->getListOfRentals()[i] + "\n");
                        }
                        cout << "Please type in the ID of the item that you wish to delete: ";
                        getline(cin, item_ID);
                        if (vl->validateIdItem(item_ID)) {
                            bool founditem = false;
                            int position = 0;
                            for (int i = 0; i < items.size(); i++) {
                                if (items[i]->getID() == item_ID) {
                                    vector<string> borrowed_item = update_customer->getListOfRentals();
                                    for (int i = 0; i < update_customer->getnumOfRentals(); i++) {
                                        if (update_customer->getListOfRentals()[i] == item_ID) {
                                            founditem = true;
                                            position = i;
                                        }
                                    }
                                    if (founditem) {
                                        update_customer->getListOfRentals().erase(update_customer->getListOfRentals().begin() + position);
                                        if (this->rs->searchItemID(item_ID)->getNumOfCopy() == 0) {
                                            this->rs->searchItemID(item_ID)->setStatus(false);
                                        }
                                        this->rs->searchItemID(item_ID)->setNumOfCopy(this->rs->searchItemID(item_ID)->getNumOfCopy() + 1);
                                        update_customer->setNumOfRentals(update_customer->getnumOfRentals() - 1);
                                    }
                                }
                                cout << "You have enter wrong item ID!";
                                break;
                            }
                        }
                        else {
                            cout << "You have enter the wrong item ID!";
                        }
                    }
                }
                else if (kind == 6) {
                    string new_reward_point;
                    VipAccount* vip = new VipAccount(update_customer);
                    cout << "The current Reward point that this account has is " + vip->getRewardPoint();
                    cout << "\n Please write the new Reward point that this account has: ";
                    getline(cin, new_reward_point);
                    if (vl->checkInt(new_reward_point)) {
                        vip->setRewardPoint(stoi(new_reward_point));
                    }
                }
            }
            break;
        }
    }
}

void Interface::menu3() {
    cout << "1. Promote custormer by ID\n";
    cout << "2. Promote custormer by Name\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    if (subChoice == 1) {
        cout << '\n';
        cout << "1. Promote customer from Guest to Regular\n";
        cout << "2. Promote customer from Regular to VIP\n";
        cout << "Your choice [1 - 2]: ";
        int subsubChoice = this->takeChoice(2);
        cout << '\n';
        string word;
        if (subsubChoice == 1) {
            while (true)
            {
                cout << "ID: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 0, 0);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
        else if (subsubChoice == 2) {
            while (true)
            {
                cout << "ID: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 1, 0);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
    }
    if (subChoice == 2) {
        cout << '\n';
        cout << "1. Promote customer from Guest to Regular\n";
        cout << "2. Promote customer from Regular to VIP\n";
        cout << "Your choice [1 - 2]: ";
        int subsubChoice = this->takeChoice(2);
        cout << '\n';
        string word;
        if (subsubChoice == 1) {
            while (true)
            {
                cout << "Name: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 0, 1);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
        else if (subsubChoice == 2) {
            while (true)
            {
                cout << "Name: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 1, 1);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
    }
}

void Interface::menu4() {
    string cusID;
    string itemID;
    Validation* vl = new Validation();
    vector<Item*> items = this->rs->getItems();
    vector<Customer*> customers = this->rs->getCustomers();
    vector<string> listItems;
    bool found_cus = false;
    bool found_item = false;
    while (true) {
        cout << "Please choose the customer that will be renting an item:\n";
        this->rs->printAllCustomerSortedID(1);
        cout << "Please put in that customer ID: ";
        getline(cin, cusID);
        if (vl->validateIdCus(cusID)) {
            for (int i = 0; i < customers.size(); i++) {
                if (customers[i]->getID() == cusID) {
                    found_cus = true;
                }
            }
            if (found_cus) {
                Customer* cus = this->rs->searchCusID(cusID);
                while (true) {
                    cout << "Please choose the item that customer will be renting an item:\n";
                    this->rs->printAllItemSortedID(1);
                    cout << "Please put in that Item ID: ";
                    getline(cin, itemID);
                    if (vl->validateIdItem(itemID)) {
                        for (int i = 0; i < items.size(); i++) {
                            if (items[i]->getID() == itemID) {
                                found_item = true;
                                break;
                            }
                        }
                        if (found_item) {
                            Item* item = this->rs->searchItemID(itemID);
                            if (cus->getcustomerType() == "Guest") {
                                int vid_borrowed = 0;
                                for (int i = 0; i < items.size(); i++) {
                                    vector<string> borrowed_item = cus->getListOfRentals();
                                    for (int a = 0; a < borrowed_item.size(); a++) {
                                        if (this->rs->searchItemID(borrowed_item[a])->getRentalType() == "Video" &&
                                            this->rs->searchItemID(borrowed_item[a])->getLoanType() == "1-week") {
                                            vid_borrowed += vid_borrowed;
                                        }
                                    }
                                    if (item->getLoanType() == "1-week" &&
                                        item->getRentalType() == "Video" &&
                                        vid_borrowed == 2) {
                                        cout << "This account have already rent 2 of 1-week type video so this account can not loan more!";
                                    }
                                    else if (item->getLoanType() == "2-day" &&
                                        item->getRentalType() == "Video") {
                                        cout << "Guest account can not loan 2-day type video!";
                                    }
                                    else {
                                        if (item->getNumOfCopy() > 0) {
                                            item->setNumOfCopy(items[i]->getNumOfCopy() - 1);
                                            if (item->getNumOfCopy() == 0) {
                                                item->setStatus(false);
                                            }
                                            cus->setNumOfRentals(cus->getnumOfRentals() + 1);
                                            listItems = cus->getListOfRentals();
                                            listItems.push_back(item->getID());
                                            cus->setListOfRentals(listItems);
                                        }
                                        else if (item->getNumOfCopy() == 0) {
                                            cout << "There is no more stock available for this item in stock!\n";
                                        }
                                    }
                                    cout << "You have enter wrong item ID!\n";
                                    break;
                                }
                            }
                            else if (cus->getcustomerType() == "Regular") {
                                if (item->getNumOfCopy() > 0) {
                                    item->setNumOfCopy(item->getNumOfCopy() - 1);
                                    if (item->getNumOfCopy() == 0) {
                                        item->setStatus(false);
                                    }
                                    cus->setNumOfRentals(cus->getnumOfRentals() + 1);
                                    listItems = cus->getListOfRentals();
                                    listItems.push_back(item->getID());
                                    cus->setListOfRentals(listItems);
                                }
                                else if (item->getNumOfCopy() == 0) {
                                    cout << "There is no more stock available for this item in stock!\n";
                                }
                            }
                            else if (cus->getcustomerType() == "VIP") {
                                if (item->getNumOfCopy() > 0) {
                                    item->setNumOfCopy(item->getNumOfCopy() - 1);
                                    if (item->getNumOfCopy() == 0) {
                                        item->setStatus(false);
                                    }
                                    cus->setNumOfRentals(cus->getnumOfRentals() + 1);
                                    listItems = cus->getListOfRentals();
                                    listItems.push_back(item->getID());
                                    cus->setListOfRentals(listItems);
                                    VipAccount* vip = new VipAccount(cus);
                                    vip->setRewardPoint(vip->getnumOfRentals() + 10);
                                }
                                else if (item->getNumOfCopy() == 0) {
                                    cout << "There is no more stock available for this item in stock!\n";
                                }
                            }
                            break;
                        }
                        else {
                            cout << "You have enter an item's ID that is not in the database!\n";
                        }
                        break;
                    }
                    else {
                        cout << "Please choose again! \n";
                    }
                }
                break;
            }
            else {
                cout << "You have enter a customer's ID that is not in the database!\n";
            }
            break;
        }
        else {
            cout << "Please choose again!\n";
        }
    }
}

void Interface::menu5() {
    cout << "1. Return item for custormer by ID\n";
    cout << "2. Return item for custormer by Name\n";
    cout << "Your choice [1 - 2]:";
    int subChoice = this->takeChoice(2);
    if (subChoice == 1) {
        string word, item;
        while (true)
        {
            cout << "\nID of customer to return: ";
            getline(cin, word);
            cout << "ID of item to return: ";
            getline(cin, item);
            cout << '\n';
            bool newitem = this->rs->returnItem(word, item, 0);
            if (newitem) {
                newitem;
                break;
            }
        }
    }
    if (subChoice == 2) {
        string word, item;
        while (true)
        {
            cout << "\nName of customer to return: ";
            getline(cin, word);
            cout << "ID of item to return: ";
            getline(cin, item);
            cout << '\n';
            bool newitem = this->rs->returnItem(word, item, 1);
            if (newitem) {
                newitem;
                break;
            }
        }
    }
}

void Interface::menu6() {
    cout << "1. Sorted by Title\n";
    cout << "2. Sorted by ID\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    cout << '\n';
    cout << "1. Sorted assending\n";
    cout << "2. Sorted desending\n";
    cout << "Your choice [1 - 2]: ";
    if (subChoice == 1) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllItemSortedName(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllItemSortedName(1);
        }
    }
    if (subChoice == 2) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllItemSortedID(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllItemSortedID(1);
        }
    }
}

void Interface::menu7() {
    this->rs->displayNoCopy();
}

void Interface::menu8() {
    cout << "1. Sorted by name\n";
    cout << "2. Sorted by ID\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    cout << '\n';
    cout << "1. Sorted assending\n";
    cout << "2. Sorted desending\n";
    cout << "Your choice [1 - 2]: ";
    if (subChoice == 1) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllCustomerSortedName(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllCustomerSortedName(1);
        }
    }
    if (subChoice == 2) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllCustomerSortedID(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllCustomerSortedID(1);
        }
    }
}

void Interface::menu9() {
    cout << "1. Guest\n";
    cout << "2. Regular\n";
    cout << "3. VIP\n";
    cout << "Your choice [1 - 3]: ";
    int subChoice = this->takeChoice(3);
    cout << '\n';

    const char* group[3] = { "Guest", "Regular", "VIP" };
    this->rs->displayGroup(group[subChoice - 1]);
}

void Interface::menu10() {
    cout << "1. Item\n";
    cout << "2. Customer\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);

    if (subChoice == 1) {
        cout << '\n';
        cout << "1. ID\n";
        cout << "2. Title\n";
        cout << "Your choice [1 - 2]: ";
        subChoice = this->takeChoice(2);

        this->menu10_1(subChoice);
    }
    else if (subChoice == 2) {
        cout << '\n';
        cout << "1. ID\n";
        cout << "2. Name\n";
        cout << "Your choice [1 - 2]: ";
        subChoice = this->takeChoice(2);

        this->menu10_2(subChoice);
    }
}

void Interface::menu10_1(int subChoice) {
    cout << '\n';
    string word;
    if (subChoice == 1) {
        Item* i1;
        while (true) {
            cout << "ID: ";
            getline(cin, word);
            i1 = this->rs->searchItemID(word);
            if (i1 != NULL) {
                cout << '\n';
                break;
            }
        }
        cout << i1->toString();
    }
    else if (subChoice == 2) {
        vector<Item*> i1;
        while (true) {
            cout << "Title: ";
            getline(cin, word);
            i1 = this->rs->searchItemTitle(word);
            if (i1.size() != 0) {
                cout << '\n';
                break;
            }
        }
        this->rs->display(i1);
    }
}

void Interface::menu10_2(int subChoice) {
    cout << '\n';
    string word;
    if (subChoice == 1) {
        Customer* c1;
        while (true) {
            cout << "ID: ";
            getline(cin, word);
            c1 = this->rs->searchCusID(word);
            if (c1 != NULL) {
                cout << '\n';
                break;
            }
        }
        cout << c1->toString();
    }
    else if (subChoice == 2) {
        vector<Customer*> c1;
        while (true) {
            cout << "Name: ";
            getline(cin, word);
            c1 = this->rs->searchCusName(word);
            if (c1.size() != 0) {
                cout << '\n';
                break;
            }
        }
        this->rs->display(c1);
    }
}

void Interface::menu11() {
    Validation v;
    v.writeFile(rs->getItems(), rs->getCustomers());
}

void Interface::option(int menuChoice, RentalShop** rs) {
    this->rs = *rs;
    this->menuChoice = menuChoice;
    cout << '\n';

    switch (menuChoice)
    {
    case 1:
        this->menu1();
        break;
    case 2:
        this->menu2();
        break;
    case 3:
        this->menu3();
        break;
    case 4:
        this->menu4();
        break;
    case 5:
        this->menu5();
        break;
    case 6:
        this->menu6();
        break;
    case 7:
        this->menu7();
        break;
    case 8:
        this->menu8();
        break;
    case 9:
        this->menu9();
        break;
    case 10:
        this->menu10();
        break;
    case 11:
        this->menu11();
        break;
    default:
        break;
    }
    cout << '\n';
}

int Interface::takeChoice(int limit) {
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
