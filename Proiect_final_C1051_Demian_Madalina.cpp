#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
//#include <bits/stdc++.h>
#include <list>
#include <map>
#pragma warning(disable:4996)

using namespace std;

// Class Declarations
class Product {
private:
    const int id;
    char* name = nullptr;
    double price = 0;
    int promotions[7]{};
    static int instances;

public:
    Product() :id(Product::instances++) { }

    Product(
        const char* name,
        double price) : id(Product::instances++) {
        this->name = new char[strlen(name) + 1];
        if (this->name == nullptr) {
            cout << "Memory allocation error on Product() constructor, this->name field." << endl;
            exit(1);
        }

        strcpy(this->name, name);
        this->price = price;
        for (int i = 0; i < 7; ++i) {
            promotions[i] = 0;
        }
    }

    Product(
        const char* name,
        double price,
        const int promotions[]
    ) :id(Product::instances++) {
        this->name = new char[strlen(name) + 1];
        if (this->name == nullptr) {
            cout << "Memory allocation error on Product() constructor, this->name field." << endl;
            exit(1);
        }

        strcpy(this->name, name);
        this->price = price;
        for (int i = 0; i < 7; ++i) {
            if (promotions[i] < 0 || promotions[i] > 100) {
                cout << "The discount for a certain product must be between 0 and 100 inclusive." << endl;
                exit(1);
            }

            this->promotions[i] = promotions[i];
        }
    }

    Product(const Product& product) :id(product.id) {
        ++Product::instances;
        this->setPrice(product.price);
        this->setName(product.name);
        this->setPromotions(product.promotions, 7);
    }

    Product& operator=(const Product& product) {
        this->setPrice(product.price);
        this->setName(product.name);
        this->setPromotions(product.promotions, 7);
        return *this;
    }

    int getId() {
        return id;
    }

    char* getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int* getPromotions() {
        return this->promotions;
    }

    void setPrice(double price) {
        if (price <= 0) {
            cout << "The price of the product must be greater than 0." << endl;
            exit(1);
        }

        this->price = price;
    }

    void setName(const char name[]) {
        if (strlen(name) == 0) {
            cout << "The name of the product is missing." << endl;
        }

        this->name = new char[strlen(name) + 1];
        if (this->name == nullptr) {
            cout << "Memory allocation error on Product() constructor, this->name field." << endl;
            exit(1);
        }

        strcpy(this->name, name);
    }

    void setPromotions(const int promotions[], int length) {
        if (length != 7) {
            cout << "The size of promotions array is not equal to 7.";
            exit(1);
        }

        for (int i = 0; i < 7; ++i) {
            if (promotions[i] < 0 || promotions[i] > 100) {
                cout << "The discount for a certain product must be between 0 and 100 inclusive." << endl;
                exit(1);
            }

            this->promotions[i] = promotions[i];
        }
    }

    Product& operator+(double priceCoefficient) {
        this->price += priceCoefficient;
        return *this;
    }

    Product& operator+=(double priceCoefficient) {
        this->price += priceCoefficient;
        return *this;
    }

    int& operator[](int index) {
        if (index < 0 || index >= 7) {
            cout << endl << "Invalid  day (Must be between 0 and 7).";
            exit(1);
        }
        return this->promotions[index];
    }

    Product& operator--() {
        this->price--;
        return *this;
    }

    Product operator--(int) {
        Product prev = *this;
        --(*this);
        return prev;
    }

    operator double() {
        return price;
    }

    bool operator!() {
        for (int i = 0; i < 7; ++i) {
            if (promotions[i] != 0) {
                return true;
            }
        }

        return false;
    }

    bool operator>(const Product& product) {
        return this->price > product.price;
    }

    bool operator==(const Product& product) {
        return strcmp(this->name, product.name) == 0 && this->price == product.price;
    }

    bool operator!=(const Product& product) {
        return !(strcmp(this->name, product.name) == 0 && this->price == product.price);
    }

    double calculatePrice(int day) {
        int promotion = promotions[day];
        double discount = ((double)promotion / 100.0) * price;
        return price - discount;
    }

    bool hasDiscount() {
        int counter = 0;
        for (int i = 0; i < 7; ++i) {
            if (promotions[i] > 0) {
                ++counter;
            }
        }

        return counter != 0;
    }

    friend ostream& operator<<(ostream& out, const Product& product) {
        if (product.name != nullptr) {
            out << "The " << product.name << " product with ID=" << product.id << " has a price of " << product.price << "RON. The promotions for this product per day are: " << endl;
            out << "   MONDAY: " << product.promotions[0] << "%;" << endl;
            out << "  TUESDAY: " << product.promotions[1] << "%;" << endl;
            out << "WEDNESDAY: " << product.promotions[2] << "%;" << endl;
            out << " THURSDAY: " << product.promotions[3] << "%;" << endl;
            out << "   FRIDAY: " << product.promotions[4] << "%;" << endl;
            out << " SATURDAY: " << product.promotions[5] << "%;" << endl;
            out << "   SUNDAY: " << product.promotions[6] << "%." << endl;
        }
        else {
            cout << "The product was not completely initialized." << endl;
        }

        return out;
    }

    friend istream& operator>>(istream& in, Product& product) {
        delete[] product.name;
        char aux[100];
        strcpy(aux, "");
        cout << "Introduce the product name: ";
        fflush(stdin);
        gets_s(aux);
        product.name = new char[strlen(aux) + 1];
        strcpy(product.name, aux);

        cout << "Introduce the price for this product: ";
        in >> product.price;

        cout << "Introduce the promotions for this product per day." << endl;
        cout << "   MONDAY: ";
        in >> product.promotions[0];
        cout << "  TUESDAY: ";
        in >> product.promotions[1];
        cout << "WEDNESDAY: ";
        in >> product.promotions[2];
        cout << " THURSDAY: ";
        in >> product.promotions[3];
        cout << "   FRIDAY: ";
        in >> product.promotions[4];
        cout << " SATURDAY: ";
        in >> product.promotions[5];
        cout << "   SUNDAY: ";
        in >> product.promotions[6];
        cout << endl;

        return in;
    }

    ~Product() {
        delete[] name;
        --Product::instances;
        //  cout << "A product has been destroyed." << endl;
    }
};

class Buyer {
protected:
    char name[30]{};
    double budget = 0;
    int numberOfProducts = 0;
    int maxNumberOfProducts = 10;
    // HAS-A
    Product* products = nullptr;

    void performCopying(const Buyer& buyer) {
        strcpy(this->name, buyer.name);
        this->budget = buyer.budget;
        this->numberOfProducts = buyer.numberOfProducts;
        this->products = new Product[buyer.maxNumberOfProducts];
        if (this->products == nullptr) {
            cout << "Memory allocation error. products was not properly initialized.";
            exit(1);
        }

        for (int i = 0; i < buyer.numberOfProducts && i < buyer.maxNumberOfProducts; ++i) {
            this->products[i] = buyer.products[i];
        }
    }

    void removeLastProduct() {
        Product* temp = products;
        --numberOfProducts;
        products = new Product[numberOfProducts];
        if (products == nullptr) {
            cout << "The resizing for products did not go well.";
            exit(1);
        }

        for (int i = 0; i < numberOfProducts; ++i) {
            products[i] = temp[i];
        }

        delete[] temp;
    }

public:
    Buyer() {
        numberOfProducts = 0;
        maxNumberOfProducts = 10;
        products = new Product[maxNumberOfProducts];
        if (products == nullptr) {
            cout << "Memory allocation error. products was not properly initialized.";
            exit(1);
        }
    }

    Buyer(const char name[]) {
        strcpy(this->name, name);
        budget = 0;
        numberOfProducts = 0;
        maxNumberOfProducts = 10;
        products = new Product[maxNumberOfProducts];
        if (products == nullptr) {
            cout << "Memory allocation error. products was not properly initialized.";
            exit(1);
        }
    }

    Buyer(
        const char name[],
        double budget,
        int maxNumberOfProducts
    ) {
        strcpy(this->name, name);
        this->budget = budget;
        numberOfProducts = 0;
        this->maxNumberOfProducts = maxNumberOfProducts;
        products = new Product[maxNumberOfProducts];
        if (products == nullptr) {
            cout << "Memory allocation error. products was not properly initialized.";
            exit(1);
        }
    }

    Buyer(const Buyer& buyer) {
        performCopying(buyer);
    }

    Buyer& operator=(const Buyer& buyer) {
        performCopying(buyer);
        return *this;
    }

    char* getName() {
        return this->name;
    }

    double getBudget() {
        return this->budget;
    }

    int getNumberOfProducts() {
        return this->numberOfProducts;
    }

    int getMaxNumberOfProducts() {
        return this->maxNumberOfProducts;
    }

    Product* getProducts() {
        return this->products;
    }

    void setBudget(double budget) {
        if (budget < 0) {
            cout << "The budget must be greater than zero." << endl;
            exit(1);
        }
        this->budget = budget;
    }

    virtual double calculateTotalPrice() {
        double sum = 0;
        for (int i = 0; i < numberOfProducts; ++i) {
            sum += (double)products[i];
        }

        return sum;
    }

    void addProduct(Product& product, int day) {
        if (products == nullptr) {
            products = new Product[maxNumberOfProducts];
            if (products == nullptr) {
                cout << "Memory allocation error. products was not properly initialized.";
                exit(1);
            }
        }

        double totalPrice = calculateTotalPrice();
        double newProductPrice = product.calculatePrice(day);
        if (totalPrice + newProductPrice > budget) {
            cout << "The product " << product.getName() << " is too expensive for your budget." << endl;
            return;
        }

        if (numberOfProducts == maxNumberOfProducts) {
            Product* temp = products;
            maxNumberOfProducts += 10;
            products = new Product[maxNumberOfProducts];
            for (int i = 0; i < numberOfProducts && i < maxNumberOfProducts; ++i) {
                products[i] = temp[i];
            }

            delete[] temp;
        }

        product.setPrice(newProductPrice);
        if (numberOfProducts < maxNumberOfProducts) {
            products[numberOfProducts] = product;
            ++numberOfProducts;
        }

    }

    void pay() {
        if (numberOfProducts == 0) {
            cout << "The buyer " << name << " has no products!!!" << endl;
            return;
        }

        double totalPrice = calculateTotalPrice();
        budget -= totalPrice;
        numberOfProducts = 0;
        delete[] products;
        products = nullptr;
        cout << "The buyer " << name << " payed." << "The shopping took " << totalPrice << "RON. The buyer " << name << " has a budget of "
            << budget << "RON left." << endl;
    }

    bool operator!() {
        numberOfProducts = 0;
        delete[] products;
        products = nullptr;

        if (products != nullptr) {
            cout << "The products could not be deleted." << endl;
            return 0;
        }

        cout << "Deleted all the products successfully." << endl;
        return 1;
    }

    Buyer& operator+(double newBudget) {
        this->budget += newBudget;
        return *this;
    }

    Product operator[](int index) {
        if (index >= numberOfProducts) {
            throw "Index Out Of Bound Exception.";
        }

        return products[index];
    }

    bool operator==(Buyer& buyer) {
        if (this->budget == buyer.budget) {
            return true;
        }

        return false;
    }

    operator double() {
        return calculateTotalPrice();
    }

    bool operator <(const Buyer& buyer) {
        return this->numberOfProducts < buyer.numberOfProducts;
    }

    void setName(const char name[]) {
        if (strlen(name) > 0) {
            strcpy(this->name, name);
        }
    }

    Buyer& operator--() {
        if (numberOfProducts == 0) {
            return *this;
        }

        removeLastProduct();
        return *this;
    }

    Buyer operator--(int) {
        Buyer buyer = *this;
        --(*this);
        return buyer;
    }

    friend ostream& operator<<(ostream& out, const Buyer& buyer) {
        out << "Buyer's name: " << buyer.name << endl;
        out << "Buyer's budget: " << buyer.budget << endl;
        out << "Number of products: " << buyer.numberOfProducts << endl;
        if (buyer.numberOfProducts != 0) {
            out << "The products are: " << endl;
        }

        for (int i = 0; i < buyer.numberOfProducts; ++i) {
            cout << "Product " << i + 1 << ": " << buyer.products[i].getName() << " with price "
                << (double)buyer.products[i] << "." << endl;
        }

        return out;
    }

    friend istream& operator>>(istream& in, Buyer& buyer) {
        cout << "Introduce the name of the buyer: ";
        fflush(stdin);
        gets_s(buyer.name);
        cout << "Introduce the budget: ";
        in >> buyer.budget;

        return in;
    }

    ~Buyer() {
        delete[] products;
        // cout << "A buyer has been destroyed." << endl;
    }
};

class EmployedBuyer : public Buyer {
private:
    int discountForShopping = 0;

public:
    EmployedBuyer() : Buyer() {

    }

    EmployedBuyer(const char name[]) : Buyer(name) {

    }

    EmployedBuyer(
        const char name[],
        double budget,
        int maxNumberOfProducts,
        int discountForShopping
    ) : Buyer(name, budget, maxNumberOfProducts) {
        this->discountForShopping = discountForShopping;
    }

    EmployedBuyer(const EmployedBuyer& buyer) : Buyer(buyer) {
        discountForShopping = buyer.discountForShopping;
    }

    EmployedBuyer& operator=(const EmployedBuyer& employedBuyer) {
        this->performCopying(employedBuyer);
        discountForShopping = employedBuyer.discountForShopping;
        return *this;
    }

    EmployedBuyer& operator--() {
        if (numberOfProducts == 0) {
            return *this;
        }

        this->removeLastProduct();
        return *this;
    }

    EmployedBuyer operator--(int) {
        EmployedBuyer buyer = *this;
        --(*this);
        return buyer;
    }

    int getDiscountForShopping() {
        return discountForShopping;
    }

    // Overriding
    virtual double calculateTotalPrice() {
        double totalPriceWithoutDiscount = Buyer::calculateTotalPrice();
        return totalPriceWithoutDiscount * (1.00 - (double)discountForShopping / 100.0);
    }

    friend ostream& operator<<(ostream& out, const EmployedBuyer& employedBuyer) {
        out << "Employed buyer's name: " << employedBuyer.name << endl;
        out << "Employed buyer's budget: " << employedBuyer.budget << endl;
        out << "Employed buyer's discout for shopping: " << employedBuyer.discountForShopping << "%." << endl;
        out << "Number of products: " << employedBuyer.numberOfProducts << endl;
        if (employedBuyer.numberOfProducts != 0) {
            out << "The products are: " << endl;
        }

        for (int i = 0; i < employedBuyer.numberOfProducts; ++i) {
            cout << "Product " << i + 1 << ": " << employedBuyer.products[i].getName() << " with price "
                << (double)employedBuyer.products[i] << "." << endl;
        }

        return out;
    }

    friend istream& operator>>(istream& in, EmployedBuyer& employedBuyer) {
        cout << "Introduce the name of the employed buyer: ";
        fflush(stdin);
        gets_s(employedBuyer.name);
        cout << "Introduce the budget: ";
        in >> employedBuyer.budget;
        cout << "Introduce the discount for shopping: ";
        in >> employedBuyer.discountForShopping;

        return in;
    }
};

class CashRegister {
private:
    char name[30]{};
    bool isActive = 0;
    int cashRegisterCapacity = 0;
    int currentServedBuyers = 0;
    Buyer* buyers;

    void performCopying(const CashRegister& cashRegister) {
        strcpy(name, cashRegister.name);
        isActive = cashRegister.isActive;
        currentServedBuyers = cashRegister.currentServedBuyers;
        cashRegisterCapacity = cashRegister.cashRegisterCapacity;
        buyers = new Buyer[cashRegisterCapacity];
        if (buyers == nullptr) {
            cout << "Memory allocation error. buyers was not properly initialized." << endl;
            exit(1);
        }

        for (int i = 0; i < currentServedBuyers && i < cashRegisterCapacity; ++i) {
            buyers[i] = cashRegister.buyers[i];
        }
    }

public:
    CashRegister() {
        currentServedBuyers = 0;
        isActive = 1;
        cashRegisterCapacity = 5;
        buyers = new Buyer[cashRegisterCapacity];
        if (buyers == nullptr) {
            cout << "Memory allocation error. buyers was not properly initialized." << endl;
            exit(1);
        }
    }

    CashRegister(const char name[]) {
        strcpy(this->name, name);
        isActive = 1;
        currentServedBuyers = 0;
        cashRegisterCapacity = 5;
        buyers = new Buyer[cashRegisterCapacity];
        if (buyers == nullptr) {
            cout << "Memory allocation error. buyers was not properly initialized." << endl;
            exit(1);
        }
    }

    CashRegister(
        const char name[],
        int cashRegisterCapacity
    ) {
        strcpy(this->name, name);
        isActive = 1;
        currentServedBuyers = 0;
        this->cashRegisterCapacity = cashRegisterCapacity;
        buyers = new Buyer[cashRegisterCapacity];
        if (buyers == nullptr) {
            cout << "Memory allocation error. buyers was not properly initialized." << endl;
            exit(1);
        }
    }

    CashRegister(const CashRegister& cashRegister) {
        performCopying(cashRegister);
    }

    CashRegister& operator=(const CashRegister& cashRegister) {
        performCopying(cashRegister);
        return *this;
    }

    void setIsActive(bool isActive) {
        if (currentServedBuyers == 0) {
            this->isActive = isActive;
        }
    }

    void setCashRegisterCapacity(int cashRegisterCapacity) {
        if (cashRegisterCapacity < this->cashRegisterCapacity) {
            if (currentServedBuyers == 0) {
                this->cashRegisterCapacity = cashRegisterCapacity;
                buyers = new Buyer[cashRegisterCapacity];
                if (buyers == nullptr) {
                    cout << "Memory allocation error. buyers was not properly initialized." << endl;
                    exit(1);
                }
            }
        }
        else {
            Buyer* temp = buyers;
            buyers = new Buyer[cashRegisterCapacity];
            this->cashRegisterCapacity = cashRegisterCapacity;
            if (buyers == nullptr) {
                cout << "Memory allocation error. buyers was not properly initialized." << endl;
                exit(1);
            }

            for (int i = 0; i < currentServedBuyers; ++i) {
                buyers[i] = temp[i];
            }

            delete[] temp;
        }
    }

    void setName(const char name[]) {
        if (strlen(name) > 0) {
            strcpy(this->name, name);
        }
    }

    void addBuyer(Buyer& buyer) {
        if (currentServedBuyers == cashRegisterCapacity) {
            cout << "No more available places.";
            exit(1);
        }

        buyers[currentServedBuyers] = buyer;
        ++currentServedBuyers;
    }

    void removeBuyer() {
        if (currentServedBuyers == 0) {
            return;
        }

        buyers[0].pay();
        for (int i = 1; i < currentServedBuyers; ++i) {
            buyers[i - 1] = buyers[i];
        }

        --currentServedBuyers;
    }

    int getCurrentServedBuyers() {
        return currentServedBuyers;
    }

    operator int() {
        return currentServedBuyers;
    }

    Buyer operator[](int index) {
        if (index >= currentServedBuyers) {
            cout << "Index is out of bound." << endl;
            exit(1);
        }

        return buyers[index];
    }

    bool operator==(CashRegister& cashRegister) {
        if (cashRegisterCapacity == cashRegister.cashRegisterCapacity) {
            return true;
        }

        return false;
    }

    bool operator>(const CashRegister& cashRegister) {
        return (strcmp(name, cashRegister.name) > 0);
    }

    bool operator!() {
        if (currentServedBuyers == 0) {
            return 0;
        }

        currentServedBuyers = 0;
        delete[] buyers;
        buyers = nullptr;

        if (buyers != nullptr) {
            cout << "The buyers could not be deleated." << endl;
            return 0;
        }

        cout << "The buyers deleted." << endl;
        return 1;

    }

    CashRegister& operator+(int capacity) {
        this->cashRegisterCapacity += capacity;
        return *this;
    }

    CashRegister& operator+=(int capacity) {
        this->cashRegisterCapacity += capacity;
        return *this;
    }

    CashRegister& operator--() {
        removeBuyer();
        return *this;
    }

    CashRegister operator--(int) {
        CashRegister cashRegister = *this;
        --(*this);
        return cashRegister;
    }

    Buyer* getBuyers() {
        return buyers;
    }

    char* getName() {
        return name;
    }

    bool getIsActive() {
        return isActive;
    }

    int getCashRegisterCapacity() {
        return cashRegisterCapacity;
    }

    friend ostream& operator<<(ostream& out, const CashRegister& cashRegister) {
        if (cashRegister.isActive) {
            out << "The " << cashRegister.name << " is active and has a capacity of " << cashRegister.cashRegisterCapacity << " buyers."
                << " Currently, there are " << cashRegister.currentServedBuyers << " buyers being served." << endl;
        }
        else {
            out << "The " << cashRegister.name << " is inactive and has a capacity of " << cashRegister.cashRegisterCapacity << " buyers."
                << " Currently, there are " << cashRegister.currentServedBuyers << " buyers being served." << endl;
        }

        for (int i = 0; i < cashRegister.currentServedBuyers; ++i) {
            cout << cashRegister.buyers[i] << endl;
        }

        return out;
    }

    friend istream& operator>>(istream& in, CashRegister& cashRegister) {
        cout << "Is the cash register active? ";
        in >> cashRegister.isActive;
        cout << "Introduce the name of the cash register: ";
        fflush(stdin);
        gets_s(cashRegister.name);
        cout << "Introduce the capacity of the cash register: ";
        in >> cashRegister.cashRegisterCapacity;

        return in;
    }

    ~CashRegister() {
        delete[] buyers;
    }
};

class Provider {
private:
    char name[30]{};
    Product* products = nullptr;
    int numberOfProducts = 0;
    int capacity = 0;

    void performCopying(const Provider& provider) {
        strcpy(this->name, provider.name);
        this->capacity = provider.capacity;
        this->numberOfProducts = provider.numberOfProducts;
        products = new Product[this->capacity];
        if (products == nullptr) {
            cout << "Memory allocation error. products in Provider class was not properly allocated.";
            exit(1);
        }

        for (int i = 0; i < this->numberOfProducts && i < this->capacity; ++i) {
            this->products[i] = provider.products[i];
        }
    }

    void resizeProducts(int capacity) {
        Product* temp = products;
        products = new Product[capacity];
        if (products == nullptr) {
            cout << "Memory allocation error. products in Provider class was not properly allocated.";
            exit(1);
        }

        for (int i = 0; i < numberOfProducts && i < capacity; ++i) {
            products[i] = temp[i];
        }

        this->capacity = capacity;
    }

public:
    Provider() {
        capacity = 10;
        products = new Product[capacity];
        numberOfProducts = 0;
        if (products == nullptr) {
            cout << "Memory allocation error. products in Provider class was not properly allocated.";
            exit(1);
        }
    }

    Provider(
        const char name[]
    ) {
        strcpy(this->name, name);
        capacity = 10;
        products = new Product[capacity];
        numberOfProducts = 0;
        if (products == nullptr) {
            cout << "Memory allocation error. products in Provider class was not properly allocated.";
            exit(1);
        }
    }

    Provider(
        const char name[],
        int capacity
    ) {
        strcpy(this->name, name);
        this->capacity = capacity;
        numberOfProducts = 0;
        products = new Product[this->capacity];
        if (products == nullptr) {
            cout << "Memory allocation error. products in Provider class was not properly allocated.";
            exit(1);
        }
    }

    Provider(const Provider& provider) {
        performCopying(provider);
    }

    Provider& operator=(const Provider& provider) {
        performCopying(provider);
        return *this;
    }

    Product& createProduct(
        const char name[],
        double price
    ) {
        for (int i = 0; i < numberOfProducts; ++i) {
            if (strcmp(products[i].getName(), name) == 0 && products[i].getPrice() == price) {
                cout << "This product already exists." << endl;
                return products[i];
            }
        }

        Product product(name, price);
        if (numberOfProducts == capacity) {
            resizeProducts(capacity * 2);
        }

        products[numberOfProducts] = product;
        ++numberOfProducts;

        return products[numberOfProducts - 1];
    }

    int getNumberOfProducts() {
        return numberOfProducts;
    }

    Provider& operator++() {
        resizeProducts(capacity * 2);
        return *this;
    }

    Provider operator++(int) {
        Provider provider = *this;
        ++(*this);
        return provider;
    }

    bool operator==(const Provider& provider) {
        if (strcmp(provider.name, this->name) != 0 || provider.numberOfProducts != this->numberOfProducts) {
            return false;
        }

        for (int i = 0; i < this->numberOfProducts; ++i) {
            if (this->products[i] != provider.products[i]) {
                return false;
            }
        }

        return true;
    }

    void setName(const char name[]) {
        if (strlen(name) == 0) {
            cout << "You have given an empty name for Provider." << endl;
            exit(1);
        }

        strcpy(this->name, name);
    }

    void setCapacity(int capacity) {
        resizeProducts(capacity);
    }

    char* getName() {
        return this->name;
    }

    int getCapacity() {
        return this->capacity;
    }

    bool operator>(const Provider& provider) {
        return this->numberOfProducts > provider.numberOfProducts;
    }

    bool operator<(const Provider& provider) {
        return this->numberOfProducts < provider.numberOfProducts;
    }

    Product* getProducts() {
        return this->products;
    }

    Product operator[](int index) {
        if (index >= numberOfProducts) {
            cout << "Index is out of bound." << endl;
            exit(1);
        }

        return products[index];
    }

    Provider& operator+(int capacity) {
        this->capacity += capacity;
        return *this;
    }
    operator int() {
        return capacity;
    }

    void operator!() {
        delete[] products;
        products = nullptr;
        capacity = 10;
        products = new Product[capacity];
        numberOfProducts = 0;
        if (products == nullptr) {
            cout << "Memory allocation error. products in Provider class was not properly allocated.";
            exit(1);
        }
    }

    void removeProduct(Product product) {
        for (int i = 0; i < numberOfProducts; ++i) {
            if (products[i] == product) {
                for (int j = i; j < numberOfProducts - 1; ++j) {
                    products[i] = products[i + 1];
                }
                --numberOfProducts;
            }
        }
    }

    friend ostream& operator<<(ostream& out, const Provider& provider) {
        out << "Provider's name: " << provider.name << endl;
        out << "Provider's products: " << provider.numberOfProducts << endl;
        out << "Provider's capacity: " << provider.capacity << endl;

        for (int i = 0; i < provider.numberOfProducts; ++i) {
            out << provider.products[i].getName() << " " << provider.products[i].getPrice() << endl;
        }

        return out;
    }

    friend istream& operator>>(istream& in, Provider& provider) {
        cout << "Enter the provider's name: ";
        fflush(stdin);
        gets_s(provider.name);
        cout << "Introduce the provider's capacity: ";
        in >> provider.capacity;
        provider.resizeProducts(provider.capacity);

        return in;
    }

    ~Provider() {
        delete[] products;
    }
};

class Shop {
private:
    char name[30]{};
    int numberOfCashRegisters = 0;
    int maxNumberOfCashRegisters{};
    CashRegister* cashRegisters = nullptr;
    int numberOfProducts = 0;
    int maxNumberOfProducts{};
    Product* products = nullptr;
    int numberOfBuyers = 0;
    int maxNumberOfBuyers{};
    Buyer* buyers = nullptr;
    static int totalNumberOfBuyers;

    void performCopying(const Shop& shop) {
        strcpy(this->name, shop.name);
        this->maxNumberOfBuyers = shop.maxNumberOfBuyers;
        this->maxNumberOfProducts = shop.maxNumberOfProducts;
        this->maxNumberOfCashRegisters = shop.maxNumberOfCashRegisters;
        this->cashRegisters = new CashRegister[this->maxNumberOfCashRegisters];
        this->buyers = new Buyer[this->maxNumberOfBuyers];
        this->products = new Product[this->maxNumberOfProducts];

        if (cashRegisters == nullptr) {
            cout << "cashRegisters in Shop class could not be instantiated.";
            exit(1);
        }

        if (products == nullptr) {
            cout << "products in Shop class could not be instantiated.";
            exit(1);
        }

        if (buyers == nullptr) {
            cout << "buyers in Shop class could not be instantiated.";
            exit(1);
        }

        for (int i = 0; i < shop.numberOfCashRegisters; ++i) {
            this->addCashRegister(shop.cashRegisters[i]);
        }

        for (int i = 0; i < shop.numberOfBuyers; ++i) {
            this->addBuyer(shop.buyers[i]);
        }


        for (int i = 0; i < shop.numberOfProducts; ++i) {
            this->addProduct(shop.products[i]);
        }
    }

public:
    Shop() {
        numberOfCashRegisters = 0;
        numberOfProducts = 0;
        numberOfBuyers = 0;
    }

    Shop(
        const char name[],
        int maxNumberOfCashRegisters,
        int maxNumberOfProducts,
        int maxNumberOfBuyers
    )
    {
        strcpy(this->name, name);
        numberOfCashRegisters = 0;
        numberOfProducts = 0;
        numberOfBuyers = 0;
        this->maxNumberOfBuyers = maxNumberOfBuyers;
        this->maxNumberOfProducts = maxNumberOfProducts;
        this->maxNumberOfCashRegisters = maxNumberOfCashRegisters;
        cashRegisters = new CashRegister[maxNumberOfCashRegisters];
        products = new Product[maxNumberOfProducts];
        buyers = new Buyer[maxNumberOfBuyers];
        if (cashRegisters == nullptr) {
            cout << "cashRegisters in Shop class could not be instantiated.";
            exit(1);
        }

        if (products == nullptr) {
            cout << "products in Shop class could not be instantiated.";
            exit(1);
        }

        if (buyers == nullptr) {
            cout << "buyers in Shop class could not be instantiated.";
            exit(1);
        }
    }

    Shop(const Shop& shop) {
        performCopying(shop);
    }

    Shop& operator=(const Shop& shop) {
        performCopying(shop);
        return *this;
    }

    void changeCashRegisterActivity(
        int indexOfCashRegister,
        bool activity
    ) {
        for (int i = 0; i < numberOfCashRegisters; ++i) {
            if (i == indexOfCashRegister) {
                cashRegisters[i].setIsActive(activity);
                break;
            }
        }
    }

    void setPromotionsToProduct(
        int promotions[],
        int length,
        const char name[]
    ) {
        for (int i = 0; i < numberOfProducts; ++i) {
            if (strcmp(products[i].getName(), name) == 0) {
                products[i].setPromotions(promotions, length);
                break;
            }
        }
    }

    // This function takes a Buyer as a parameter and places him in queue (coadă) at the cash register, so that
    // he could pay for his products later on. This operation is performed if and only any of the cash register
    // has a free spot in the queue. This operation is performed by analyzing each of the cash registers and checking
    // which one has the fewest buyers and placing him there (which is exactly how it happens in real life - a buyer
    // goes to the cash register which has less buyers).
    void goToCashRegister(Buyer& buyer) {
        int minCapacity = cashRegisters[0].getCurrentServedBuyers(), minIndex = 0, k = 0;

        // First of all, we have to determine the index of the buyer, because we will have
        // to remove him from the list of buyers. Therefore, we have to know the index before
        // performing the removal. 
        for (int i = 0; i < numberOfBuyers; ++i) {
            if (strcmp(buyers[i].getName(), buyer.getName()) == 0) {
                k = i;
                break;
            }
        }

        // Checking if the cash register is free, first of all, and if this is the case, we iterate through
        // all free cash registers and determine which one has the fewest buyers, so we can place our buyer
        // in that specific queue.
        for (int i = 1; i < numberOfCashRegisters; ++i) {
            if (cashRegisters[i].getIsActive() == 1 && cashRegisters[i].getCurrentServedBuyers() < cashRegisters[i].getCashRegisterCapacity()) {
                if (cashRegisters[i].getCurrentServedBuyers() < minCapacity) {
                    minCapacity = cashRegisters[i].getCurrentServedBuyers();
                    minIndex = i;
                }
            }
        }

        // If our minimum index is equal to 0, this means we could not find any other cash register that has fewer
        // buyers than this one (the one at index 0). This generates 2 situations.
        // 1. Either this cash register is the cash register with the fewest buyers.
        // 2. Either this cash register is full. 
        if (minIndex == 0) {
            // This is the 2nd situation, in which case we do not have free space in the queue.
            if (cashRegisters[minIndex].getCashRegisterCapacity() == minCapacity) {
                cout << "We are sorry, we can not serve you at this moment. Please, wait." << endl;
                return;
            }
            // This is the 1st situation, in which case we add the buyer.
            else {
                cashRegisters[minIndex].addBuyer(buyers[k]);
            }
        }
        // Either way around, we have found the cash register with the fewest buyers, so we add our
        // buyer in the queue.
        else {
            cashRegisters[minIndex].addBuyer(buyers[k]);
        }
    }

    void pay(int cashRegisterIndex) {
        for (int i = 0; i < numberOfCashRegisters; ++i) {
            if (i == cashRegisterIndex) {
                Buyer* buyers = cashRegisters[i].getBuyers();
                for (int j = 0; j < numberOfBuyers; ++j) {
                    if (strcmp(this->buyers[j].getName(), buyers[0].getName()) == 0) {
                        for (int k = j; k < numberOfBuyers - 1; ++k) {
                            this->buyers[k] = this->buyers[k + 1];
                        }
                        --this->numberOfBuyers;
                        break;
                    }
                }

                cashRegisters[i].removeBuyer();
            }
        }
    }

    void placeProduct(
        const char name[],
        Product& product,
        int day
    ) {
        for (int i = 0; i < numberOfBuyers; ++i) {
            if (strcmp(buyers[i].getName(), name) == 0) {
                buyers[i].addProduct(product, day);
                break;
            }
        }
    }

    void addBuyer(Buyer& buyer) {
        if (numberOfBuyers == maxNumberOfBuyers) {
            return;
        }

        // for (int i = 0; i < numberOfBuyers; ++i) {
        //     if (strcmp(buyers[i].getName(), buyer.getName()) == 0) {
        //         break;
        //     }
        // }

        Shop::totalNumberOfBuyers++;
        buyers[numberOfBuyers] = buyer;
        ++numberOfBuyers;
    }

    void addCashRegister(CashRegister& cashRegister) {
        if (numberOfCashRegisters == maxNumberOfCashRegisters) {
            return;
        }

        // for (int i = 0; i < numberOfCashRegisters; ++i) {
        //     if (strcmp(cashRegisters[i].getName(), cashRegister.getName()) == 0) {
        //         break;
        //     }
        // }

        cashRegisters[numberOfCashRegisters] = cashRegister;
        ++numberOfCashRegisters;

    }

    char* getName() {
        return name;
    }

    int getNumberOfBuyers() {
        return numberOfBuyers;
    }

    int getMaxNumberOfBuyers() {
        return maxNumberOfBuyers;
    }

    int getNumberOfCashRegisters() {
        return numberOfCashRegisters;
    }

    int getMaxNumberOfCashRegisters() {
        return maxNumberOfCashRegisters;
    }

    int getNumberOfProducts() {
        return numberOfProducts;
    }

    int getMaxNumberOfProducts() {
        return maxNumberOfProducts;
    }

    void setMaxNumberOfCashRegisters(int maxNumberOfCashRegisters) {
        this->maxNumberOfCashRegisters = maxNumberOfCashRegisters;
    }

    void setMaxNumberOfBuyers(int maxNumberOfBuyers) {
        this->maxNumberOfBuyers = maxNumberOfBuyers;
    }

    void setMaxNumberOfProducts(int maxNumberOfProducts) {
        this->maxNumberOfProducts = maxNumberOfProducts;
    }

    Product* getProducts() {
        return products;
    }

    Buyer* getBuyers() {
        return buyers;
    }

    CashRegister* getCashRegisters() {
        return cashRegisters;
    }

    void addProduct(Product& product) {
        if (numberOfProducts == maxNumberOfProducts) {
            return;
        }

        // for (int i = 0; i < numberOfProducts; ++i) {
        //     if (strcmp(products[i].getName(), product.getName()) == 0) {
        //         break;
        //     }
        // }

        products[numberOfProducts] = product;
        ++numberOfProducts;
    }

    static int getTotalNumberOfBuyers() {
        return Shop::totalNumberOfBuyers;
    }

    friend ostream& operator<<(ostream& out, const Shop& shop) {
        out << "Shop's name: " << shop.name << endl;
        out << "Maximum number of cash registers: " << shop.maxNumberOfCashRegisters << endl;
        out << "Maximum number of products: " << shop.maxNumberOfBuyers << endl;
        out << "Maximum number of buyers: " << shop.maxNumberOfBuyers << endl;
        out << "Number of cash registers: " << shop.numberOfCashRegisters << endl;
        for (int i = 0; i < shop.numberOfCashRegisters; ++i) {
            out << shop.cashRegisters[i].getName();
            out << " is serving " << shop.cashRegisters[i].getCurrentServedBuyers() << " buyers." << endl;
        }
        out << "Number of products: " << shop.numberOfProducts << endl;
        for (int i = 0; i < shop.numberOfProducts; ++i) {
            out << shop.products[i].getName() << endl;
        }
        out << "Number of buyers: " << shop.numberOfBuyers << endl;
        for (int i = 0; i < shop.numberOfBuyers; ++i) {
            out << shop.buyers[i].getName();
            out << " has " << shop.buyers[i].getNumberOfProducts() << " products." << endl;
        }

        return out;
    }

    friend istream& operator>>(istream& in, Shop& shop) {
        cout << "Enter the shop's name: ";
        fflush(stdin);
        gets_s(shop.name);
        cout << "Introduce the maximum nr of cash registers: ";
        in >> shop.maxNumberOfCashRegisters;
        cout << "Introduce the maximum nr of products: ";
        in >> shop.maxNumberOfProducts;
        cout << "Introduce the maximum nr of buyers: ";
        in >> shop.maxNumberOfBuyers;

        shop.cashRegisters = new CashRegister[shop.maxNumberOfCashRegisters];
        shop.products = new Product[shop.maxNumberOfProducts];
        shop.buyers = new Buyer[shop.maxNumberOfBuyers];
        if (shop.cashRegisters == nullptr) {
            cout << "cashRegisters in Shop class could not be instantiated.";
            exit(1);
        }

        if (shop.products == nullptr) {
            cout << "products in Shop class could not be instantiated.";
            exit(1);
        }

        if (shop.buyers == nullptr) {
            cout << "buyers in Shop class could not be instantiated.";
            exit(1);
        }
        return in;
    }

    ~Shop() {
        delete[] cashRegisters;
        delete[] products;
        delete[] buyers;
    }
};

class TextFileProcessor {

public:
    TextFileProcessor() {}

    void readProductFromFile(
        ifstream& file,
        vector<Product>& products
    ) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream lineStream(line);
            string items[9];
            for (int i = 0; i < 9; ++i) {
                getline(lineStream, items[i], ',');
            }

            int promo[] = {
                stoi(items[2]),
                stoi(items[3]),
                stoi(items[4]),
                stoi(items[5]),
                stoi(items[6]),
                stoi(items[7]),
                stoi(items[8])
            };
            char* productName = new char[items[0].length() + 1];
            strcpy(productName, items[0].c_str());
            Product product(productName, stod(items[1]), promo);
            products.push_back(product);
        }
    }

    void readBuyerFromFile(
        ifstream& file,
        vector<Buyer>& buyers
    ) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream lineStream(line);
            string items[4];
            for (int i = 0; i < 4; ++i) {
                getline(lineStream, items[i], ',');
            }

            if (stoi(items[3]) < 0) {
                char* buyerName = new char[items[0].length() + 1];
                strcpy(buyerName, items[0].c_str());
                double budget = stod(items[1]);
                int numberOfProducts = stoi(items[2]);
                Buyer buyer(buyerName, budget, numberOfProducts);
                buyers.push_back(buyer);
            }
        }
    }

    void readEmployedBuyerFromFile(
        ifstream& file,
        vector<EmployedBuyer>& buyers
    ) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream lineStream(line);
            string items[4];
            for (int i = 0; i < 4; ++i) {
                getline(lineStream, items[i], ',');
            }

            double discount = stod(items[3]);
            if (discount >= 0) {
                char* buyerName = new char[items[0].length() + 1];
                strcpy(buyerName, items[0].c_str());
                double budget = stod(items[1]);
                int numberOfProducts = stoi(items[2]);
                EmployedBuyer employedBuyer(buyerName, budget, numberOfProducts, discount);
                buyers.push_back(employedBuyer);
            }
        }
    }

    void readProviderFromFile(
        ifstream& file,
        vector<Provider>& providers
    ) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream lineStream(line);
            string items[2];
            for (int i = 0; i < 2; ++i) {
                getline(lineStream, items[i], ',');
            }

            char* providerName = new char[items[0].length() + 1];
            strcpy(providerName, items[0].c_str());
            int capacity = stoi(items[1]);
            Provider provider(providerName, capacity);
            providers.push_back(provider);
        }
    }

    void readCashRegisterFromFile(
        ifstream& file,
        vector<CashRegister>& cashRegisters
    ) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream lineStream(line);
            string items[2];
            for (int i = 0; i < 2; ++i) {
                getline(lineStream, items[i], ',');
            }

            char* cashRegisterName = new char[items[0].length() + 1];
            strcpy(cashRegisterName, items[0].c_str());
            int capacity = stoi(items[1]);
            CashRegister cashRegister(cashRegisterName, capacity);
            cashRegisters.push_back(cashRegister);
        }
    }
};

// Generic class
// We declare an implicit type that could be anything decided by us
template <typename K> class BinaryFileWriter {
public:
    virtual void writeToFile(ofstream& binaryFile, ifstream& inputFile) = 0;
    virtual void writeToFile(ofstream& binaryFile, vector<K> data) = 0;
};

template <typename K> class ProviderBinaryFileWriter : public BinaryFileWriter<K> {
public:
    virtual void writeToFile(ofstream& binaryFile, ifstream& inputFile) {
        TextFileProcessor textFileProcessor;
        vector<Provider> providers;
        textFileProcessor.readProviderFromFile(inputFile, providers);
        for (auto provider : providers) {
            binaryFile.write(provider.getName(), sizeof(char) * strlen(provider.getName()));
            int x = provider.getCapacity();
            binaryFile.write((char*)&x, sizeof(int));
        }
    }

    virtual void writeToFile(ofstream& binaryFile, vector<Provider> providers) {
        for (auto provider : providers) {
            binaryFile.write(provider.getName(), sizeof(char) * strlen(provider.getName()));
            int x = provider.getCapacity();
            binaryFile.write((char*)&x, sizeof(int));
        }
    }
};

template <typename K> class ProductBinaryFileWriter : public BinaryFileWriter<K> {
public:
    virtual void writeToFile(ofstream& binaryFile, ifstream& inputFile) {
        TextFileProcessor textFileProcessor;
        vector<Product> products;
        textFileProcessor.readProductFromFile(inputFile, products);
        for (auto product : products) {
            binaryFile.write(product.getName(), sizeof(char) * strlen(product.getName()));
            double x = product.getPrice();
            binaryFile.write((char*)&x, sizeof(double));
            binaryFile.write((char*)product.getPromotions(), sizeof(int) * 7);
        }
    }

    virtual void writeToFile(ofstream& binaryFile, vector<Product> products) {
        for (auto product : products) {
            binaryFile.write(product.getName(), sizeof(char) * strlen(product.getName()));
            double x = product.getPrice();
            binaryFile.write((char*)&x, sizeof(double));
            binaryFile.write((char*)product.getPromotions(), sizeof(int) * 7);
        }
    }
};

template <typename K> class BuyerBinaryFileWriter : public BinaryFileWriter<K> {
public:
    virtual void writeToFile(ofstream& binaryFile, ifstream& inputFile) {
        TextFileProcessor textFileProcessor;
        vector<Buyer> buyers;
        textFileProcessor.readBuyerFromFile(inputFile, buyers);
        for (auto buyer : buyers) {
            binaryFile.write(buyer.getName(), sizeof(char) * strlen(buyer.getName()));
            double x = buyer.getBudget();
            binaryFile.write((char*)&x, sizeof(double));
            int y = buyer.getMaxNumberOfProducts();
            binaryFile.write((char*)&y, sizeof(int));
        }
    }

    virtual void writeToFile(ofstream& binaryFile, vector<Buyer> buyers) {
        for (auto buyer : buyers) {
            binaryFile.write(buyer.getName(), sizeof(char) * strlen(buyer.getName()));
            double x = buyer.getBudget();
            binaryFile.write((char*)&x, sizeof(double));
            int y = buyer.getMaxNumberOfProducts();
            binaryFile.write((char*)&y, sizeof(int));
        }
    }
};

template <typename K> class EmployedBuyerBinaryFileWriter : public BinaryFileWriter<K> {
public:
    virtual void writeToFile(ofstream& binaryFile, ifstream& inputFile) {
        TextFileProcessor textFileProcessor;
        vector<EmployedBuyer> employedBuyers;
        textFileProcessor.readEmployedBuyerFromFile(inputFile, employedBuyers);
        for (auto employedBuyer : employedBuyers) {
            binaryFile.write(employedBuyer.getName(), sizeof(char) * strlen(employedBuyer.getName()));
            double x = employedBuyer.getBudget();
            binaryFile.write((char*)&x, sizeof(double));
            int y = employedBuyer.getMaxNumberOfProducts();
            binaryFile.write((char*)&y, sizeof(int));
            int z = employedBuyer.getDiscountForShopping();
            binaryFile.write((char*)&z, sizeof(int));
        }
    }

    virtual void writeToFile(ofstream& binaryFile, vector<EmployedBuyer> employedBuyers) {
        for (auto employedBuyer : employedBuyers) {
            binaryFile.write(employedBuyer.getName(), sizeof(char) * strlen(employedBuyer.getName()));
            double x = employedBuyer.getBudget();
            binaryFile.write((char*)&x, sizeof(double));
            int y = employedBuyer.getMaxNumberOfProducts();
            binaryFile.write((char*)&y, sizeof(int));
            int z = employedBuyer.getDiscountForShopping();
            binaryFile.write((char*)&z, sizeof(int));
        }
    }
};

template <typename K> class CashRegisterBinaryFileWriter : public BinaryFileWriter<K> {
public:
    virtual void writeToFile(ofstream& binaryFile, ifstream& inputFile) {
        TextFileProcessor textFileProcessor;
        vector<CashRegister> cashRegisters;
        textFileProcessor.readCashRegisterFromFile(inputFile, cashRegisters);
        for (auto cashRegister : cashRegisters) {
            binaryFile.write(cashRegister.getName(), sizeof(char) * strlen(cashRegister.getName()));
            int x = cashRegister.getCashRegisterCapacity();
            binaryFile.write((char*)&x, sizeof(int));
            int y = cashRegister.getIsActive();
            binaryFile.write((char*)&y, sizeof(int));
        }
    }

    virtual void writeToFile(ofstream& binaryFile, vector<CashRegister> cashRegisters) {
        for (auto cashRegister : cashRegisters) {
            binaryFile.write(cashRegister.getName(), sizeof(char) * strlen(cashRegister.getName()));
            int x = cashRegister.getCashRegisterCapacity();
            binaryFile.write((char*)&x, sizeof(int));
            int y = cashRegister.getIsActive();
            binaryFile.write((char*)&y, sizeof(int));
        }
    }
};

class ReportGenerator {
public:
    virtual void generateReport(ofstream& file) = 0;
};

class ShopReportGenerator : public ReportGenerator {
private:
    Shop shop;

public:
    ShopReportGenerator(const Shop& shop) {
        this->shop = shop;
    }

    void setShop(Shop shop) {
        this->shop = shop;
    }

    virtual void generateReport(ofstream& file) {
        Product* products = shop.getProducts();
        Buyer* buyers = shop.getBuyers();
        CashRegister* cashRegisters = shop.getCashRegisters();

        cout << shop << endl;

        file << "Report for shop " << shop.getName() << endl;
        file << "Number of cash registers: " << shop.getNumberOfCashRegisters() << endl;
        for (int i = 0; i < shop.getNumberOfCashRegisters(); ++i) {
            file << cashRegisters[i].getName();
            file << " is serving " << cashRegisters[i].getCurrentServedBuyers() << " buyers." << endl;
        }
        file << "Number of products: " << shop.getNumberOfProducts() << ". The products are: " << endl;
        for (int i = 0; i < shop.getNumberOfProducts(); ++i) {
            file << products[i].getName() << endl;
        }
        file << "Number of buyers: " << shop.getNumberOfBuyers() << endl;
        for (int i = 0; i < shop.getNumberOfBuyers(); ++i) {
            file << buyers[i].getName();
            file << " has " << buyers[i].getNumberOfProducts() << " products." << endl;
        }
    }
};

class ProviderReportGenerator : public ReportGenerator {
private:
    Provider provider;

public:
    ProviderReportGenerator(Provider provider) {
        this->provider = provider;
    }

    virtual void generateReport(ofstream& file) {
        Product* products = provider.getProducts();

        cout << provider << endl;

        file << "Report for provider " << provider.getName() << endl;
        file << "Number of products: " << provider.getNumberOfProducts() << ". The products are: " << endl;
        for (int i = 0; i < provider.getNumberOfProducts(); ++i) {
            file << products[i].getName() << " with price equal to " << products[i].getPrice() << "RON." << endl;
        }
    }
};

class ProductReportGenerator : public ReportGenerator {
private:
    vector<Product> products;

public:
    ProductReportGenerator(vector<Product> products) {
        for (auto product : products) {
            // push_back() - adauga un element la sfarsitul listei
            // Daca avem vector cu elementele p1 - p2 - p3, atunci, dupa ce este apelat push_back(p4),
            // vom avem p1 - p2 - p3 - p4
            this->products.push_back(product);
        }
    }

    void generateReport(ofstream& file) {
        file << "Report for all the products read from .csv files." << endl;
        file << "The products are: " << endl;
        for (auto product : products) {
            cout << product << endl;
            file << product.getName() << " has a price of " << product.getPrice() << "RON." << endl;
            int* promotions = product.getPromotions();
            file << "The promotions for this product are as follows: " << endl;
            file << "   MONDAY: " << promotions[0] << "%;" << endl;
            file << "  TUESDAY: " << promotions[1] << "%;" << endl;
            file << "WEDNESDAY: " << promotions[2] << "%;" << endl;
            file << " THURSDAY: " << promotions[3] << "%;" << endl;
            file << "   FRIDAY: " << promotions[4] << "%;" << endl;
            file << " SATURDAY: " << promotions[5] << "%;" << endl;
            file << "   SUNDAY: " << promotions[6] << "%." << endl;
            file << endl;
        }
    }
};

class Menu {
private:
    map<int, int> history;

public:
    Menu() { }

    void displayMenu() {
        cout << endl;
        cout << "Sweets Shop application menu. Below are the available functionalities:" << endl;
        cout << "1. Read the data from files(if provided in command line) or define all the data manually in the main program." << endl;
        cout << "2. Read a Product from keyboard." << endl;
        cout << "3. Read a Buyer from keyboard." << endl;
        cout << "4. Read an Employed Buyer from keyboard." << endl;
        cout << "5. Read a Cash Register from keyboard." << endl;
        cout << "6. Read a Provider from keyboard." << endl;
        cout << "7. Read a Shop from keyboard." << endl;
        cout << "8. Create a product via a provider." << endl;
        cout << "9. Do the shopping." << endl;
        cout << "10. Display all the products." << endl;
        cout << "11. Display all the buyers." << endl;
        cout << "12. Display all the cash registers." << endl;
        cout << "13. Display all the providers." << endl;
        cout << "14. Get application(menu) history." << endl;
        cout << "-1. Exit the application." << endl;
        cout << endl;
    }

    int getMenuOption() {
        int option;

        cout << "Enter your option: ";
        cin >> option;

        // The method count() returns 1 if the key(option in our case) is present
        // and 0 otherwise.
        if (history.count(option) == 1) {
            int times = history[option];
            history[option] = times + 1;
        }
        else {
            // The insert() methods takes a pair of elements and introduces them in the map.
            history.insert(pair<int, int>(option, 1));
        }

        return option;
    }

    void getHistory() {
        // The map is not a structure that can use index to retrieve elements, so we need a dedicated
        // iterator to retrieve them. In this case, we use an iterator(which is a pointer *) to retrieve the elements.
        // The iterator starts with the first element(which is a pair<int, int>) of the map(history.begin()) and goes
        // all the way to the last element(history.end()).
        for (map<int, int>::iterator itr = history.begin(); itr != history.end(); ++itr) {
            if (itr->first == 1) {
                cout << "All the data was defined manually by the user." << endl;
            }
            else if (itr->first == 2) {
                cout << "A number of " << itr->second << " products were read from keyboard." << endl;
            }
            else if (itr->first == 3) {
                cout << "A number of " << itr->second << " buyers were read from keyboard." << endl;
            }
            else if (itr->first == 4) {
                cout << "A number of " << itr->second << " employed buyers were read from keyboard." << endl;
            }
            else if (itr->first == 5) {
                cout << "A number of " << itr->second << " cash registers were read from keyboard." << endl;
            }
            else if (itr->first == 6) {
                cout << "A number of " << itr->second << " providers were read from keyboard." << endl;
            }
            else if (itr->first == 7) {
                cout << "A number of " << itr->second << " shops were read from keyboard." << endl;
            }
            else if (itr->first == 8) {
                cout << "A number of " << itr->second << " products were created via a provider." << endl;
            }
            else if (itr->first == 9) {
                cout << "The shopping was done " << itr->second << " times." << endl;
            }
            else if (itr->first == 10) {
                cout << "The products were displayed " << itr->second << " times." << endl;
            }
            else if (itr->first == 11) {
                cout << "The buyers were displayed " << itr->second << " times." << endl;
            }
            else if (itr->first == 12) {
                cout << "The cash registers were displayed " << itr->second << " times." << endl;
            }
            else if (itr->first == 13) {
                cout << "The providers were displayed " << itr->second << " times." << endl;
            }
        }

        cout << endl;
    }
};

// Static variables
int Product::instances = 0;
int Shop::totalNumberOfBuyers = 0;

// Main Program
int main(int argc, char** argv) {
    // Creating the instances used to populate the binary files with data
    ProviderBinaryFileWriter<Provider>* providerBinaryFileWriter = new ProviderBinaryFileWriter<Provider>;
    ProductBinaryFileWriter<Product>* productsBinaryFileWriter = new ProductBinaryFileWriter<Product>;
    BuyerBinaryFileWriter<Buyer>* buyerBinaryFileWriter = new BuyerBinaryFileWriter<Buyer>;
    EmployedBuyerBinaryFileWriter<EmployedBuyer>* employedBuyerBinaryFileWriter = new EmployedBuyerBinaryFileWriter<EmployedBuyer>;
    CashRegisterBinaryFileWriter<CashRegister>* cashRegisterBinaryFileWriter = new CashRegisterBinaryFileWriter<CashRegister>;
    // Data structures to store the entities outside the menu
    vector<Product> products;
    vector<Buyer> buyers;
    vector<EmployedBuyer> employedBuyers;
    vector<Provider> providers;
    vector<CashRegister> cashRegisters;
    list<Shop> shops;

    Menu menu;
    menu.displayMenu();
    int option = 0;

    while (option != -1) {
        option = menu.getMenuOption();
        if (option == -1) {
            menu.getHistory();
            cout << "Application was terminated with success." << endl;
            return 0;
        }

        if (option == 1) {
            break;
        }

        if (option == 2) {
            cout << "Reading a Product from keyboard: " << endl;

            Product product;
            cin >> product;
            products.push_back(product);
            cout << endl;
        }

        if (option == 3) {
            cout << "Reading a Buyer from keyboard: " << endl;

            Buyer buyer;
            cin >> buyer;
            buyers.push_back(buyer);
            cout << endl;
        }

        if (option == 4) {
            cout << "Reading an Employed Buyer from keyboard: " << endl;

            EmployedBuyer employedBuyer;
            cin >> employedBuyer;
            employedBuyers.push_back(employedBuyer);
            cout << endl;
        }

        if (option == 5) {
            cout << "Reading a Cash Register from keyboard: " << endl;

            CashRegister cashRegister;
            cin >> cashRegister;
            cashRegisters.push_back(cashRegister);
            cout << endl;
        }

        if (option == 6) {
            cout << "Reading a Provider from keyboard: " << endl;

            Provider provider;
            cin >> provider;
            providers.push_back(provider);
        }

        if (option == 7) {
            cout << "Reading a Shop from keyboard: " << endl;

            Shop shop;
            cin >> shop;

            if (cashRegisters.size() == 0) {
                cout << "There are no cash registers in the system, therefore the shop can not be created." << endl;
                continue;
            }

            if (buyers.size() == 0 && employedBuyers.size() == 0) {
                cout << "There are no buyers in the system, therefore the shop can not be created." << endl;
                continue;
            }

            if (products.size() == 0) {
                cout << "There are no products in the system, therefore the shop can not be created." << endl;
                continue;
            }

            for (auto cashRegister : cashRegisters) {
                shop.addCashRegister(cashRegister);
            }

            for (auto product : products) {
                shop.addProduct(product);
            }

            if (buyers.size() != 0) {
                for (auto buyer : buyers) {
                    shop.addBuyer(buyer);
                }
            }

            if (employedBuyers.size() != 0) {
                for (auto employedBuyer : employedBuyers) {
                    shop.addBuyer(employedBuyer);
                }
            }

            shops.push_back(shop);

        }

        if (option == 8) {
            cout << "Creating a Product via a provider: " << endl;
            if (providers.size() == 0) {
                cout << "There is no provider created in the system." << endl;
                continue;
            }

            char productName[100];
            char providerName[100];
            double productPrice;

            cout << "Enter the name of the product: ";
            fflush(stdin);
            gets(productName);
            cout << "Enter the price of the product: ";
            cin >> productPrice;
            cout << "Enter the name of the provider: ";
            fflush(stdin);
            gets(providerName);

            for (auto provider : providers) {
                if (strcmp(provider.getName(), providerName) == 0) {
                    Product product(provider.createProduct(productName, productPrice));
                    products.push_back(product);
                    break;
                }
            }
        }

        if (option == 9) {
            cout << "Do shopping option." << endl;
            fflush(stdin);
            char shopName[100];
            Shop shop;
            cout << "Enter the name of the shop: ";
            gets(shopName);
            fflush(stdin);
            bool wasShopFound = 0;
            for (auto& _shop : shops) {
                if (strcmp(_shop.getName(), shopName) == 0) {
                    bool placeProducts = 1;
                    int day;

                    cout << "Enter the day of the week: ";
                    cin >> day;
                    set<string> names;
                    set<string> buyersThatPlacedProducts;

                    for (auto buyer : buyers) {
                        string s = buyer.getName();
                        names.insert(s);
                    }

                    for (auto buyer : employedBuyers) {
                        string s = buyer.getName();
                        names.insert(s);
                    }

                    while (placeProducts) {
                        char buyerName[100];
                        char productName[100];
                        fflush(stdin);
                        cout << "Enter the name of the buyer who will select a product: ";
                        gets(buyerName);
                        string s = buyerName;

                        if (!names.count(s)) {
                            cout << "The entered buyer does not exist in the system." << endl;
                            continue;
                        }

                        buyersThatPlacedProducts.insert(buyerName);

                        fflush(stdin);
                        cout << "Enter the name of the selected product: ";
                        gets(productName);
                        Product product;
                        for (auto _product : products) {
                            if (strcmp(_product.getName(), productName) == 0) {
                                product = _product;
                                break;
                            }
                        }

                        _shop.placeProduct(buyerName, product, day);
                        cout << "Place more products?" << endl;
                        cin >> placeProducts;
                        if (!placeProducts) {
                            break;
                        }
                    }

                    for (auto _buyer : buyers) {
                        string s = _buyer.getName();
                        if (buyersThatPlacedProducts.count(s)) {
                            _shop.goToCashRegister(_buyer);
                        }
                    }

                    for (auto _employedBuyer : buyers) {
                        string s = _employedBuyer.getName();
                        if (buyersThatPlacedProducts.count(s)) {
                            _shop.goToCashRegister(_employedBuyer);
                        }
                    }

                    for (int i = 0; i < _shop.getNumberOfCashRegisters(); ++i) {
                        _shop.pay(i);
                    }
                    wasShopFound = 1;
                }
                if (wasShopFound) {
                    break;
                }
            }

            if (!wasShopFound) {
                cout << "The specified shop was not found in the system." << endl;
            }
        }

        if (option == 10) {
            if (products.size() == 0) {
                cout << "There are no products." << endl << endl;
                continue;
            }

            cout << "Display all the products: " << endl;
            for (auto product : products) {
                cout << product << endl;
            }
        }

        if (option == 11) {
            if (buyers.size() == 0 && employedBuyers.size() == 0) {
                cout << "There are no buyers." << endl;
                continue;
            }

            cout << "Display all the buyers(including the employed buyers): " << endl;
            for (auto buyer : buyers) {
                cout << buyer << endl;
            }

            for (auto employedBuyer : employedBuyers) {
                cout << employedBuyer << endl;
            }
        }

        if (option == 12) {
            if (cashRegisters.size() == 0) {
                cout << "There are no Cash Registers to display." << endl;
                continue;
            }

            for (auto cashRegister : cashRegisters) {
                cout << cashRegister << endl;
            }
        }

        if (option == 13) {
            if (providers.size() == 0) {
                cout << "There are no Providers to display." << endl;
                continue;
            }

            for (auto provider : providers) {
                cout << provider << endl;
            }
        }

        if (option == 14) {
            menu.getHistory();
        }

        cout << endl;
    }

    // If there is any argument passed while executing the program, then it must be the case
    // when we have input files, so we will extract the data (namely the entities from there)
    if (argc > 1) {
        cout << "Reading data from file." << endl;
        // argv[1] - the file containing the Product attributes
        ifstream productFile(argv[1]);
        // argv[2] - the file containing the Buyer attributes
        ifstream buyerFile(argv[2]);
        // argv[2] - the file containing the Employed Buyer attributes
        ifstream employedBuyerFile(argv[2]);
        // argv[3] - the file containing the Provider attributes
        ifstream providerFile(argv[3]);
        // argv[4] - the file containing the Cash Register attributes
        ifstream cashRegisterFile(argv[4]);

        // The instance used to extract data from text files
        // The utility class has methods for each type of entity
        TextFileProcessor textFileProcessor;
        textFileProcessor.readProductFromFile(productFile, products);
        textFileProcessor.readBuyerFromFile(buyerFile, buyers);
        textFileProcessor.readEmployedBuyerFromFile(employedBuyerFile, employedBuyers);
        textFileProcessor.readProviderFromFile(providerFile, providers);
        textFileProcessor.readCashRegisterFromFile(cashRegisterFile, cashRegisters);

        // The output binary file
        // We use a single binary file to store all the entities
        ofstream binaryFile;

        // argv[5] - the output binary file where all the data is persisted
        binaryFile.open(argv[5], ios::binary | ios::out);

        // Since we have already processed the text files, the pointer associated with each file has 
        // reached the EOF (end of file). Therefore, we have to move the pointer to the beginning of the file,
        // so we can parse (iterate through) the date again. We repeat this process for each file.
        productFile.clear();
        productFile.seekg(0);
        buyerFile.clear();
        buyerFile.seekg(0);
        employedBuyerFile.clear();
        employedBuyerFile.seekg(0);
        providerFile.clear();
        providerFile.seekg(0);
        cashRegisterFile.clear();
        cashRegisterFile.seekg(0);

        // Using the instances declared above to populate the binary file.
        providerBinaryFileWriter->writeToFile(binaryFile, providerFile);
        productsBinaryFileWriter->writeToFile(binaryFile, productFile);
        buyerBinaryFileWriter->writeToFile(binaryFile, buyerFile);
        employedBuyerBinaryFileWriter->writeToFile(binaryFile, employedBuyerFile);
        cashRegisterBinaryFileWriter->writeToFile(binaryFile, cashRegisterFile);
        binaryFile.close();
        productFile.close();
        buyerFile.close();
        employedBuyerFile.close();
        providerFile.close();
        cashRegisterFile.close();

        // In the same time, we display the data associated with each entity to the standard output, 
        // which is the console in our case.
        for (auto product : products) {
            cout << product << endl;
        }

        for (auto buyer : buyers) {
            cout << buyer << endl;
        }

        for (auto employedBuyer : employedBuyers) {
            cout << employedBuyer << endl;
        }

        for (auto provider : providers) {
            cout << provider << endl;
        }

        for (auto cashRegister : cashRegisters) {
            cout << cashRegister << endl;
        }

        return 0;
    }

    int promo1[] = { 0, 5, 0, 10, 0, 0, 0 };
    Product product1("Oreo", 7, promo1);
    products.push_back(product1);
    Product product2 = product1;
    // cout << product2 << endl;

    int promo2[] = { 0, 5, 0, 20, 0, 10, 0 };
    product2.setName("Milka");
    product2.setPrice(10);
    product2.setPromotions(promo2, 7);
    // cout << product2 << endl;
    products.push_back(product2);
    // cout << products[1] << endl;

    Product product3(product2);
    product3 = product3 + 4.00;
    product3.setName("Nutella");
    // cout << product3 << endl;
    products.push_back(product3);
    // cout << products[2] << endl;

    Buyer buyer1("Madalina Demian", 200.00, 10);
    buyer1.addProduct(product1, 1);
    buyer1.addProduct(product2, 1);
    buyer1.addProduct(product3, 1);

    // cout << buyer1 << endl;
    // cout << buyers[0];

    // cout << product1.getName() << endl;
    // cout << buyer1.getBudget() << endl;
    // cout << buyer1.getNumberOfProducts() << endl;
    // Product* listOfProducts = buyer1.getProducts();
    // for (int i = 0; i < buyer1.getNumberOfProducts(); ++i) {
    //     cout << listOfProducts[i].getName() << endl;
    // }

    cout << "The result of deleting all the products for buyer1: " << !buyer1 << endl;
    // cout << buyer1 << endl;

    buyer1.addProduct(product1, 1);
    buyer1.addProduct(product2, 1);
    buyer1.addProduct(product3, 1);
    buyer1.pay();
    // cout << buyer1 << endl;

    // cout << "New budget: " << buyer1.getBudget() << endl;

    Buyer buyer2("Ana Toma", 544.8, 10);
    buyer2.addProduct(product1, 1);
    buyer2.addProduct(product2, 1);
    buyers.push_back(buyer1);
    buyers.push_back(buyer2);

    // cout << buyer2 << endl;


    // cout << (double)buyer2 << endl;

    EmployedBuyer employee1("Andrei Anuta", 1000.00, 10, 15);
    employedBuyers.push_back(employee1);
    // cout << employee1 << endl;

    int promo3[] = { 10, 0, 0, 10, 5, 0, 0 };
    Product product5("Mars", 20, promo3);
    int promo4[] = { 0, 0, 5, 0, 0, 0, 0 };
    Product product6("Choco duo", 5, promo4);
    products.push_back(product5);
    products.push_back(product6);

    employee1.addProduct(product5, 0);
    employee1.addProduct(product6, 1);
    // cout << employee1 << endl;
    employee1.pay();
    // cout << employee1 << endl;

    EmployedBuyer employee2(employee1);
    employee2.setName("Ion Vlaicu");
    // cout << employee2;

    EmployedBuyer employee3 = employee1;
    employee3.setName("Marin Tudor");
    cout << "sadsdasdasda" << endl;

    cout << employee1 << endl;
    cout << employee3 << endl;
    employee3.addProduct(product1, 0);
    // cout << employee3 << endl;
    --employee3;
    // cout << employee3 << endl;
    --employee3;
    // cout << employee3 << endl;

    try {
        cout << employee3[0] << endl;
    }
    catch (const char* exception) {
        cout << exception << endl;
    }

    employee3.setBudget(400.50);
    // cout << employee3 << endl;
    employee3.pay();

    Product product7("Snickers", 6.5, promo3);
    // cout << product7.hasDiscount() << endl;
    // cout << product7.calculatePrice(1) << endl;

    CashRegister cashRegister1("Cash register 1", 4);
    cashRegister1.addBuyer(buyer1);
    cashRegisters.push_back(cashRegister1);
    // cout << cashRegister1 << endl;

    CashRegister cashRegister2(cashRegister1);
    cashRegister2.setName("Cash register 2");
    cashRegister2.addBuyer(employee1);
    cashRegister2.addBuyer(buyer2);
    // cout << cashRegister2 << endl;

    !cashRegister1;
    // cout << cashRegister1 << endl;

    // if (cashRegister1 == cashRegister2) {
    //     cout << "The cash register 1 has the same capacity as the cash register 2." << endl;
    // } else { 
    //     cout << "The cash register 1 has NOT the same capacity as the cash register 2." << endl;
    // }
    cout << endl;

    // cout << cashRegister2[1];
    // cout << endl;

    // if (cashRegister1 > cashRegister2) {
    //     cout << "The Cash Register 1 has the same name than the cash register 2." << endl;
    // } else {
    //     cout << "The Cash Register 1 has NOT the same name than the cash register 2." << endl;
    // }
    cout << endl;

    // cashRegister2 += 2;
    // cout << cashRegister2 << endl;

    !cashRegister2;
    cout << cashRegister2 << endl;

    // cout << cashRegister2[1] << endl;

    // cout << (int)cashRegister1 << endl;

    Provider provider1("Chocolate SRL");
    Product product8(provider1.createProduct("Bounty", 2.99));
    Product product9(provider1.createProduct("Twix", 2.50));
    Product product10(provider1.createProduct("Mars", 2.10));
    // cout << product8 << endl;
    // cout << product9 << endl;
    // cout << product10 << endl;
    // cout << provider1 << endl;
    provider1.removeProduct(product9);
    providers.push_back(provider1);
    // cout << provider1 << endl;

    product10.setPromotions(promo3, 7);
    // cout << product10 << endl;

    Buyer buyer4("Henri Coanda", 10, 10);
    buyer4.setBudget(100.00);
    buyer4.addProduct(product8, 3);
    buyer4.addProduct(product9, 3);
    buyer4.pay();
    cout << endl;

    Buyer buyer5("Aurel Vlaicu", 200.00, 10);
    buyer5.addProduct(product9, 2);
    buyer5.addProduct(product10, 2);
    buyer5.addProduct(product3, 2);
    --buyer5;
    buyer5.pay();
    cout << endl;
    // cout << provider1[1] << endl;
    //!provider1;
    cout << provider1 << endl;
    // cout << provider1[1] << endl;

    Provider provider2(provider1);
    provider2.setName("Nefis");
    provider2.removeProduct(product8);
    provider2.removeProduct(product9);
    Product product11(provider2.createProduct("Biscuiti", 15));

    cout << provider2 << endl;

    // if (provider1 == provider2) {
    //     cout << "It is the same provider." << endl;
    // } else {
    //     cout << "The providers are NOT the same." << endl;
    // }

    // if (provider1 < provider2) {
    //     cout << "The provider first has less products than the second provider." << endl;
    // } else { 
    //     cout << "The provider first has more products than the second provider." << endl;
    // }

    // cout << provider1[1] << endl;

    !provider1;
    // cout << provider1 << endl;

    Provider provider3;
    provider3.setName("Bucuria");
    // cin >> provider3;
    // cout << provider3 << endl;

    cout << product11 << endl;
    product11.setPromotions(promo1, 7);
    // cout << product11 << endl;
    // cout << provider2 << endl;

    const char* shopName = "Nr1";
    Shop shop(shopName, 5, 100, 15);
    CashRegister _cashRegister1("CashRegister1", 4);
    CashRegister _cashRegister2("CashRegister2", 5);
    Buyer _buyer1("Madalina Demian", 200.00, 10);
    Buyer _buyer2("Ana Toma", 300.00, 10);
    Product _product1("Oreo", 7, promo1);
    Product _product2("Twix", 10, promo1);
    Product _product3("Milka", 8, promo1);

    shop.addCashRegister(_cashRegister1);
    shop.addCashRegister(_cashRegister2);
    shop.addProduct(_product1);
    shop.addProduct(_product2);
    shop.addProduct(_product3);
    shop.addBuyer(_buyer1);
    shop.addBuyer(_buyer2);
    shop.placeProduct("Madalina Demian", _product1, 2);
    shop.placeProduct("Madalina Demian", _product2, 2);
    shop.placeProduct("Ana Toma", _product3, 2);

    shop.goToCashRegister(_buyer1);
    shop.goToCashRegister(_buyer2);
    cout << shop << endl;
    shop.pay(0);
    cout << shop << endl;

    ofstream shopReportFile("shop-report.rpt");
    ofstream providerReportFile("provider-report.rpt");
    ofstream productsReportFile("products-generator.rpt");
    ReportGenerator* shopReportGenerator = new ShopReportGenerator(shop);
    ReportGenerator* providerReportGenerator = new ProviderReportGenerator(provider1);
    ReportGenerator* providerReportGenerator2 = new ProviderReportGenerator(provider2);
    ReportGenerator* productsReportGenerator = new ProductReportGenerator(products);

    vector<ReportGenerator*> reportGenerators;
    reportGenerators.push_back(shopReportGenerator);
    reportGenerators.push_back(providerReportGenerator);
    reportGenerators.push_back(providerReportGenerator2);
    reportGenerators.push_back(productsReportGenerator);

    reportGenerators[0]->generateReport(shopReportFile);
    reportGenerators[1]->generateReport(providerReportFile);
    reportGenerators[2]->generateReport(providerReportFile);
    reportGenerators[3]->generateReport(productsReportFile);

    shopReportFile.close();
    providerReportFile.close();
    productsReportFile.close();

    const char* binaryFileName = "data.dat";
    ofstream binaryFile;
    binaryFile.open(binaryFileName, ios::binary | ios::out);
    productsBinaryFileWriter->writeToFile(binaryFile, products);
    buyerBinaryFileWriter->writeToFile(binaryFile, buyers);
    employedBuyerBinaryFileWriter->writeToFile(binaryFile, employedBuyers);
    cashRegisterBinaryFileWriter->writeToFile(binaryFile, cashRegisters);
    providerBinaryFileWriter->writeToFile(binaryFile, providers);
    binaryFile.close();

    menu.getHistory();
}