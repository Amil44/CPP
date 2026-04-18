#include <iostream>
#include <cstring>

class Product {
private:
    int _id;
    char* _name;
    char* _description;
    double _price;
    short _discount;

public:
    Product() {
        _id = 0;
        _price = 0;
        _discount = 0;
        _name = nullptr;
        _description = nullptr;
    }

    Product(int id, const char* name, const char* description, double price, short discount = 0) {
        _id = id;
        _price = price;
        _discount = discount;

        _name = new char[strlen(name) + 1];
        strcpy_s(_name, strlen(name) + 1, name);

        _description = new char[strlen(description) + 1];
        strcpy_s(_description, strlen(description) + 1, description);
    }

    Product(const Product& other) {
        _id = other._id;
        _price = other._price;
        _discount = other._discount;

        if (other._name) {
            _name = new char[strlen(other._name) + 1];
            strcpy_s(_name, strlen(other._name) + 1, other._name);
        }
        else {
            _name = nullptr;
        }

        if (other._description) {
            _description = new char[strlen(other._description) + 1];
            strcpy_s(_description, strlen(other._description) + 1, other._description);
        }
        else {
            _description = nullptr;
        }
    }

    Product& copy(const Product& other) {
        if (this == &other) return *this;

        delete[] _name;
        delete[] _description;

        _id = other._id;
        _price = other._price;
        _discount = other._discount;

        if (other._name) {
            _name = new char[strlen(other._name) + 1];
            strcpy_s(_name, strlen(other._name) + 1, other._name);
        }
        else {
            _name = nullptr;
        }

        if (other._description) {
            _description = new char[strlen(other._description) + 1];
            strcpy_s(_description, strlen(other._description) + 1, other._description);
        }
        else {
            _description = nullptr;
        }

        return *this;
    }

    double getDiscountPrice() {
        if (_price > 100) {
            short discount = 15;
            double discountedPrice = _price - (_price * discount) / 100.0;
            std::cout << "Applied Discount: " << discount << "%" << std::endl;
            std::cout << "Total Price: " << discountedPrice << std::endl;
            return discountedPrice;
        }
        else {
            std::cout << "Discount is for purchases over $100.\n";
            return _price;
        }
    }

    int getId() const { return _id; }

    void show() {
        std::cout << "Id: " << _id << " | "
            << "Product Name: " << (_name ? _name : "N/A") << " | "
            << "Description: " << (_description ? _description : "N/A") << " | "
            << "Price: " << _price << " |" << std::endl;
    }

    void addProduct() {
        delete[] _name;
        delete[] _description;

        _name = new char[100];
        _description = new char[100];

        std::cout << "Enter product id: ";
        std::cin >> _id;
        std::cin.ignore();

        std::cout << "Enter product name: ";
        std::cin.getline(_name, 100);

        std::cout << "Enter description: ";
        std::cin.getline(_description, 100);

        std::cout << "Enter product price: ";
        std::cin >> _price;
        std::cin.ignore();
    }

    ~Product() {
        delete[] _name;
        delete[] _description;
    }
};

class Stock {
private:
    char* _name;
    Product* _products;
    size_t _count;

public:
    Stock() {
        _name = nullptr;
        _products = nullptr;
        _count = 0;
    }

    void setName() {
        delete[] _name;
        _name = new char[100];
        std::cout << "Enter stock name: ";
        std::cin.ignore();
        std::cin.getline(_name, 100);
    }

    void addProduct() {
        _count++;
        Product* temp = new Product[_count];

        for (int i = 0; i < (int)_count - 1; i++) {
            temp[i].copy(_products[i]);
        }

        delete[] _products;
        _products = temp;
        _products[_count - 1].addProduct();
    }

    Product* getProductById(int id) {
        for (int i = 0; i < (int)_count; i++)
            if (_products[i].getId() == id)
                return &_products[i];
        return nullptr;
    }

    void show() {
        std::cout << "Stock Name: " << (_name ? _name : "N/A") << "\n";
        for (int i = 0; i < (int)_count; i++) {
            _products[i].show();
        }
    }

    ~Stock() {
        delete[] _name;
        delete[] _products;
    }
};

void product(Product& p1) {
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\n===== PRODUCT MENU =====\n";
        std::cout << "1. Get Discount Price\n";
        std::cout << "2. Show Product\n";
        std::cout << "3. Add Product\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose option: ";

        int op; std::cin >> op;

        if (op == 1) p1.getDiscountPrice();
        else if (op == 2) p1.show();
        else if (op == 3) p1.addProduct();
        else if (op == 4) isRunning = false;
        else std::cout << "Invalid operation!\n";
    }
}

void stock(Stock& s1) {
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\n===== STOCK MENU =====\n";
        std::cout << "1. Set Stock Name\n";
        std::cout << "2. Add Product to Stock\n";
        std::cout << "3. Show Stock\n";
        std::cout << "4. Get Product By Id\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose option: ";

        int op; std::cin >> op;

        if (op == 1) s1.setName();
        else if (op == 2) s1.addProduct();
        else if (op == 3) s1.show();
        else if (op == 4) {
            std::cout << "Enter product id to search: ";
            int id; std::cin >> id;
            Product* found = s1.getProductById(id);
            if (found) found->show();
            else std::cout << "Product not found.\n";
        }
        else if (op == 5) isRunning = false;
        else std::cout << "Invalid operation!\n";
    }
}

void mainMenu(Product& p1, Stock& s1) {
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Product\n";
        std::cout << "2. Stock\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose option: ";

        int op; std::cin >> op;

        if (op == 1) product(p1);
        else if (op == 2) stock(s1);
        else if (op == 3) { std::cout << "Exiting...\n"; isRunning = false; }
        else std::cout << "Invalid operation!\n";
    }
}

int main() {
    Product p1;
    Stock s1;
    mainMenu(p1, s1);
}