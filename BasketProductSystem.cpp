#include <iostream>
#include <cstring>

enum Category {
	Diary,
	Food,
	Electronics,
	Clothing
};

class Product {
	short _id;
	char* _name;
	float _price;
	short _discount;
	Category _category;

public:
	Product() {
		_id = 0;
		_name = nullptr;
		_price = 0;
		_discount = 0;
	}

	Product(short id, const char* name, float price, short discount, Category category) {
		_id = id;
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name);
		_price = price;
		_category = category;
		_discount = discount;
	}

	Product(const Product& other) {
		_id = other._id;
		_name = new char[strlen(other._name) + 1];
		strcpy_s(_name, strlen(other._name) + 1, other._name);
		_price = other._price;
		_category = other._category;
		_discount = other._discount;
	}

	Product(Product&& other) noexcept {
		_id = other._id;
		_name = other._name;       
		_price = other._price;
		_category = other._category;
		_discount = other._discount; 
		other._name = nullptr;
	}

	Product& operator=(const Product& other) {
		if (this == &other)
			return *this;

		delete[] _name;

		_id = other._id;

		_name = new char[strlen(other._name) + 1];
		strcpy_s(_name, strlen(other._name) + 1, other._name);

		_price = other._price;
		_category = other._category;
		_discount = other._discount;

		return *this;
	}

	~Product() {
		delete[] _name;
		_name = nullptr;
	}

	void setProduct(short id, const char* name, float price, short discount, Category category) {
		delete[] _name;
		_id = id;
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name);
		_price = price;
		_category = category;
		_discount = discount;
	}

	void getProduct() const{
		std::cout << "Id: " << _id << " | "
			<< "Name: " << _name << " | "
			<< "Price: " << _price << " | "
			<< "Category: " << categorySelect(_category) << " | " << std::endl;
	}

	static const char* categorySelect(Category catg) {
		switch (catg) {
		case Diary: return "Diary";
		case Food: return "Food";
		case Electronics: return "Electronics";
		case Clothing: return "Clothing";
		default: return "Unknown";
		}
	}

	void setPrice(float price) {
		_price = price;
	}

	short getId() const  { return _id; }
	const char* getName() const { return _name; }
	float getPrice() const { return _price; }
	short getDiscount() const { return _discount; }
	Category getCategory() const { return _category; }
};

class Basket{
	Product* product;
	float totalPrice;
	short count;
public:
	Basket() {
		product = nullptr;
		totalPrice = 0;
		count = 0;
	}


	Basket(const Basket& other) {
		totalPrice = other.totalPrice;
		count = other.count;

		if (other.product) {
			product = new Product[count];
			for (int i = 0; i < count; i++) {
				product[i] = other.product[i];
			}
		}
		else {
			product = nullptr;
		}
	}

	Basket(Basket&& other) {
		product = other.product;
		totalPrice = other.totalPrice;
		count = other.count;
		other.product = nullptr;
		other.totalPrice = 0;
		other.count = 0;
	}

	void addProduct(const Product& p) {
		Product* temp = new Product[count + 1];

		for (int i = 0; i < count; i++) {
			temp[i] = product[i];
		}

		temp[count] = p;

		delete[] product;
		product = temp;
		count++;
	}

	float getTotalPrice() const {
		float sum = 0;
		for (int i = 0; i < count; i++) {
			sum += product[i].getPrice();
		}
		return sum;
	}

	short getTotalProductCount() const { return count; }

	float getDiscount() {
		float total = getTotalPrice();

		if (total > 200) {
			std::cout << "Discount Applied.\n";
			std::cout << "Total Prices: ";
			total = total - (total * 10) / 100;
			return total;
		}
		else {
			std::cout << "No Discount.";
			return total;
		}
	}

	Basket& operator++() {
		for (int i = 0; i < count; i++) {
			product[i].setPrice(product[i].getPrice() + 1);
		}
		return *this;
	}

	Basket& operator--() {
		for (int i = 0; i < count; i++) {
			float newPrice = product[i].getPrice() - 1;
			if (newPrice < 0) newPrice = 0;

			product[i].setPrice(newPrice);
		}
		return *this;
	}

	bool operator==(const Basket& other) const { return this->getTotalPrice() == other.getTotalPrice(); }

	Basket operator*(float factor) const {
		Basket result = *this;

		for (int i = 0; i < result.count; i++) {
			float newPrice = result.product[i].getPrice() * factor;
			result.product[i].setProduct( result.product[i].getId(), result.product[i].getName(), newPrice, result.product[i].getDiscount(), result.product[i].getCategory() );
		}
		return result;
	}

	Basket& operator=(const Basket& other) {
		if (this == &other)
			return *this;

		delete[] product;

		count = other.count;
		totalPrice = other.totalPrice;

		if (other.product) {
			product = new Product[count];
			for (int i = 0; i < count; i++) {
				product[i] = other.product[i];
			}
		}
		else {
			product = nullptr;
		}

		return *this;
	}

	~Basket() {
		delete[] product;
		product = nullptr;
	}
};

int main() {
	Basket basket1;
	Basket basket2;

	Product p1(101, "Cicibebe", 5.4, 0, Food);
	Product p2(102, "Cheese", 2.2, 0, Diary);
	Product p3(103, "Headphone", 199.9, 10, Electronics);

	p1.getProduct();
	p2.getProduct();
	p3.getProduct();

	basket1.addProduct(p1);
	basket1.addProduct(p2);
	basket1.addProduct(p3);

	std::cout << "\n------ Total Prices------\n";
	std::cout << basket1.getTotalPrice();

	std::cout << "\n------ Total Product------\n";
	std::cout << basket1.getTotalProductCount();

	std::cout << "\n------ Discount ------\n";
	std::cout << basket1.getDiscount() ;

	std::cout << "\n------ After ++ ------\n";
	++basket1;
	std::cout << basket1.getTotalPrice() << std::endl;

	std::cout << "\n------ After -- ------\n";
	--basket1;
	std::cout << basket1.getTotalPrice() << std::endl;

	std::cout << "\n------ After (basket2 = basket1 * 2) ------\n";
	basket2 = basket1 * 2;
	std::cout << basket1.getTotalPrice() << std::endl;

	std::cout << "\n------ After (basket1 == basket2) ------\n";
	if (basket1 == basket2) {
		std::cout << "Baskets are equal\n";
	}
	else {
		std::cout << "Baskets are not equal\n";
	}

	return 0;
}