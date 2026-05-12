#include <iostream>
#include <string>

class Payment {
public:
    virtual void processPayment(double amount) = 0;
    virtual bool validatePayment() = 0;
    virtual std::string getPaymentType() = 0;

    void showReceipt(double amount) {
        std::cout << "========== RECEIPT ==========\n";
        std::cout << "Payment Type : " << getPaymentType() << "\n";
        std::cout << "Amount       : " << amount << " AZN\n";
        std::cout << "Status       : Successful\n";
        std::cout << "=============================\n";
    }

    virtual ~Payment() {
        std::cout << "[Payment] base class destroyed\n";
    }

    virtual void logTransaction() {
        std::cout << "[Payment] Transaction logged (base version)\n";
    }
};

class CashPayment : public Payment {
public:
    void processPayment(double amount) override {
        std::cout << "[Cash] " << amount << " AZN paid\n";
    }

    bool validatePayment() override {
        std::cout << "[Cash] Validating cash payment...\n";
        return true;
    }

    std::string getPaymentType() override {
        return "Cash";
    }

    ~CashPayment() {
        std::cout << "[CashPayment] payment class destroyed\n";
    }
};

class CardPayment : public Payment {
    std::string lastFour;
public:
    CardPayment(const std::string& last4 = "1042") : lastFour(last4) {}

    void processPayment(double amount) override final {
        std::cout << "[Card] **** **** **** " << lastFour
            << " charged " << amount << " AZN\n";
    }

    bool validatePayment() override {
        std::cout << "[Card] Validating card...\n";
        return true;
    }

    std::string getPaymentType() override {
        return "Card";
    }

    void logTransaction() override {
        std::cout << "[CardPayment] Card transaction logged (derived version)\n";
    }

    ~CardPayment() {
        std::cout << "[CardPayment] payment class destroyed\n";
    }
};

class OnlinePayment : public Payment {
    std::string provider;
public:
    OnlinePayment(const std::string& prov = "PayPal") : provider(prov) {}

    void processPayment(double amount) override {
        std::cout << "[Online] Paid " << amount
            << " AZN via " << provider << "\n";
    }

    bool validatePayment() override {
        std::cout << "[Online] Validating online payment...\n";
        return true;
    }

    std::string getPaymentType() override {
        return "Online (" + provider + ")";
    }

    ~OnlinePayment() {
        std::cout << "[OnlinePayment] payment class destroyed\n";
    }
};

class PremiumCardPayment : public CardPayment {
public:
    bool validatePayment() override {
        std::cout << "[PremiumCard] Validating premium card...\n";
        return true;
    }

    std::string getPaymentType() override {
        return "Premium Card";
    }

    ~PremiumCardPayment() {
        std::cout << "[PremiumCardPayment] payment class destroyed\n";
    }
};

int main() {
    const double AMOUNT = 50.00;
    std::cout << "===== STAGE 1: processPayment + showReceipt =====\n\n";

    CashPayment   cash;
    CardPayment   card("1042");
    OnlinePayment online("PayPal");

    cash.processPayment(AMOUNT);
    card.processPayment(AMOUNT);
    online.processPayment(AMOUNT);

    std::cout << "\n--- Receipts ---\n";
    cash.showReceipt(AMOUNT);
    card.showReceipt(AMOUNT);
    online.showReceipt(AMOUNT);

    std::cout << "\n===== STAGE 2: Virtual Destructor + VTable =====\n\n";
    {
        Payment* payments[3];
        payments[0] = new CashPayment();
        payments[1] = new CardPayment("9999");
        payments[2] = new OnlinePayment("PayPal");

        std::cout << "--- Processing payments ---\n";
        for (int i = 0; i < 3; i++) {
            payments[i]->processPayment(AMOUNT);
        }

        std::cout << "\n--- Destructor order (on delete) ---\n";
        for (int i = 0; i < 3; i++) {
            delete payments[i];
        }
    }

    std::cout << "\n--- PremiumCardPayment (processPayment is final, no override) ---\n";
    {
        PremiumCardPayment premium;
        premium.processPayment(AMOUNT); 
        std::cout << "Type: " << premium.getPaymentType() << "\n";
    }

    std::cout << "\n===== STAGE 3: Early vs Late Binding =====\n\n";

    CardPayment cardObj("5555");
    Payment* ptr = &cardObj;  

    std::cout << "--- Calling via Payment* pointer ---\n";

    ptr->logTransaction();

    std::cout << "\n--- Calling directly on CardPayment object ---\n";
    cardObj.logTransaction(); 

    std::cout << "\n[Note] Remove 'virtual' from Payment::logTransaction()\n"
        << "       and re-run — ptr->logTransaction() will call the\n"
        << "       BASE version even though the object is a CardPayment.\n"
        << "       That is early/static binding in action.\n";

    return 0;
}