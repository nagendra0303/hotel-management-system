#include <bits/stdc++.h>
#include <list>
#include <queue>
using namespace std;

// Declaring a class for room
class Room {
public:
    int roomnumber;
    string roomtype;
    double costperday;
    bool isAssigned;
    Room(int i, string s, double d){
        this->roomnumber = i;
        this->roomtype = s;
        this->costperday = d;
        this->isAssigned = false;
    }
};
// Declaring a class to store customer details
class Customer {
public:
    string name;
    string phonenumber;
    int roomnumber;
    int numdays;
    string preferredFood;
    double totalprice;
};
//class to store food item and its price
class Food {
public:
    string fooditem;
    double price;
};

// Declaring a class for the hotel
class Hotel {
public:
    list<Room> Floor[5];
    queue<Room> bookedrooms;
    list<Customer> customers;
    list<Food> fooditems;

    // Constructor to initialize the hotel rooms and food items
    Hotel() {
        int i, j;
        for (i = 0; i < 5; i++) {
            for (j = 1; j < 11; j++) {
                string a;
                double b;
                if (i == 0 || i == 4) {
                    a = "Standard";
                    b = 1500;
                } else if (i == 1 || i == 3) {
                    a = "Deluxe";
                    b = 5000;
                } else {
                    a = "VIP";
                    b = 10000;
                }
                Floor[i].push_back(Room((i * 100) + j, a, b));
            }
        }

        fooditems.push_back(Food{"Tea", 20});
        fooditems.push_back(Food{"Coffee", 30});
        fooditems.push_back(Food{"Sandwich", 100});
        fooditems.push_back(Food{"Meals", 200});
        fooditems.push_back(Food{"Pizza", 250});
        fooditems.push_back(Food{"Biryani", 300});
    }

    // Function to book a room based on the customer's preferences
    void bookRoom(string name, string phonenumber, int numdays, int n) {
        int i;
        string type;
        switch (n) {
        case 1:
            type = "Standard";
            break;
        case 2:
            type = "Deluxe";
            break;
        case 3:
            type = "VIP";
            break;
        }
        if (n == 1 || n == 2 || n == 3) {
            for (i = 0; i < 5; i++) {
                for (auto &room : Floor[i]) {
                    if (!room.isAssigned && room.roomtype == type) {
                        room.isAssigned = true;
                        Customer customer;
                        customer.name = name;
                        customer.phonenumber = phonenumber;
                        customer.roomnumber = room.roomnumber;
                        customer.numdays = numdays;
                        customer.totalprice = numdays * room.costperday;
                        customers.push_back(customer);
                        bookedrooms.push(room);
                        cout << "Room booked successfully for " << name << " (Room Number: " << room.roomnumber << ")\n";
                        return;
                    }
                }
            }
            cout << "No available rooms of type " << type << ".\n";
        } else {
            cout << "Invalid room type.\n";
        }
    }

    private:
    // Helper function to find a customer by room number
    Customer &findCustomerByRoomNumber(int roomNumber) {
        auto it = find_if(customers.begin(), customers.end(), [roomNumber](const Customer &customer) {
            return customer.roomnumber == roomNumber;
        });
        if (it != customers.end()) {
            return *it;
        } else {
            // Return a reference to a dummy customer if the customer is not found (should not happen)
            static Customer dummyCustomer;
            return dummyCustomer;
        }
    }

    // Helper function to find a customer by name
    Customer &findCustomerByName(const string &name) {
        auto it = find_if(customers.begin(), customers.end(), [name](const Customer &customer) {
            return customer.name == name;
        });
        if (it != customers.end()) {
            return *it;
        } else {
            // Return a reference to a dummy customer if the customer is not found (should not happen)
            static Customer dummyCustomer;
            return dummyCustomer;
        }
    }

    public:
    // Function to order food for a customer
    void orderFood(string name, int num) {
        if (!bookedrooms.empty()) {
            Customer &customer = findCustomerByName(name);
            if (num >= 1 && num <= 6) {
                auto it = next(fooditems.begin(), num - 1);
                customer.preferredFood = it->fooditem;
                customer.totalprice += it->price;
                cout << "Food item ordered successfully.\n";
            } else {
                cout << "Invalid food item.\n";
            }
        } else {
            cout << "No rooms booked.\n";
        }
    }

    // Function to display details for all customers
    void Customerinfo() {
        if (!bookedrooms.empty()) {
            cout << "Customer Details for All Customers:\n";
            for (const Customer &customer : customers) {
                cout << "---------------------------------------\n";
                cout << "Name: " << customer.name << "\n";
                cout << "Phone Number: " << customer.phonenumber << "\n";
                cout << "Room Number: " << customer.roomnumber << "\n";
                cout << "Number of Days: " << customer.numdays << "\n";
                cout << "Total Cost: $" << customer.totalprice << "\n";
                if (!customer.preferredFood.empty()) {
                    cout << "Preferred Food Item: " << customer.preferredFood << "\n";
                }
            }
            cout << "---------------------------------------\n";
        } else {
            cout << "No rooms booked.\n";
        }
    }

    // Function to vacate a room and remove the corresponding customer
    void vacateRoom() {
        if (!bookedrooms.empty()) {
            Room &room = bookedrooms.front();
            const Customer &customer = findCustomerByRoomNumber(room.roomnumber);

            // Mark the room as unassigned
            room.isAssigned = false;

            // Remove the customer from the list
            customers.remove_if([&](const Customer &c) {
                return c.roomnumber == customer.roomnumber;
            });

            // Display messages
            cout << "Room " << room.roomnumber << " vacated successfully.\n";
            cout << "Thank you, " << customer.name << ", for staying with us!\n";

            // Remove the room from the queue
            bookedrooms.pop();
        } else {
            cout << "No rooms booked.\n";
        }
    }
};

int main() {
    Hotel Taj;
    cout << "..............Welcome to THE TAJ HOTEL............\n\n\n\n\n";

    while (true) {
        int choice;
        cout << "Choose an option:\n";
        cout << "1. Book Room\n2. Order Food\n3. Vacate Room\n4. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter your details:\n";
            string name, phonenumber;
            int numdays;
            cout << "Name: ";
            cin >> name;
            cout << "Phone Number: ";
            cin >> phonenumber;
            cout << "Number of days of stay: ";
            cin >> numdays;
            cout << "What type of room do you want?\n";
            cout << "1. Standard\n2. Deluxe\n3. VIP\n";
            int type;
            cin >> type;
            Taj.bookRoom(name, phonenumber, numdays, type);
            break;
        }
        case 2: {
            if (!Taj.bookedrooms.empty()) {
                string name;
                cout << "Enter the name of the customer to order food: ";
                cin >> name;
                cout << "Do you want to order food? (y/n): ";
                char foodChoice;
                cin >> foodChoice;
                if (foodChoice == 'y' || foodChoice == 'Y') {
                    cout << "Choose a food item:\n";
                    cout << "1. Tea ($20)\n2. Coffee ($30)\n3. Sandwich ($100)\n4. Meals ($200)\n5. Pizza ($250)\n6. Biryani ($300)\n";
                    int foodItem;
                    cin >> foodItem;
                    Taj.orderFood(name, foodItem);
                }
            } else {
                cout << "No rooms booked.\n";
            }
            break;
        }
        case 3: {
            Taj.vacateRoom();
            break;
        }
        case 4: {
            cout << "Exiting the program.\n";
            Taj.Customerinfo();
            return 0;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
        }
    }

    return 0;
}
