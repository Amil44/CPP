#include <iostream>
#include <cstdlib>
#include <ctime>

enum Damage {
    Fire = 30,
    Freeze = 20,
    Thunder = 35
};

class Fighter {
public:
    std::string name;
    short int health;

    void attack(Fighter& enemy) {
        std::cout << "Your turn!\n";

        std::cout << "0. Fire (30)\n";
        std::cout << "1. Freeze (20)\n";
        std::cout << "2. Thunder (35)\n";

        std::cout << "Select: ";
        int choice;
        std::cin >> choice;

        int dmg = 0;

        switch (choice) {
            case 0: 
                dmg = Fire;
                break;

            case 1: 
                dmg = Freeze; 
                break;

            case 2: 
                dmg = Thunder; 
                break;

            default:
                std::cout << "Invalid attack!\n";
                return;
        }

        enemy.health -= dmg;
        std::cout << "You dealt " << dmg << " damage!\n";
    }
};

void whoWin(Fighter& character1, Fighter& character2) {
    if (character1.health < 1) {
        std::cout << "AI Won!\n";
        exit(0);
    }

    if (character2.health < 1) {
        std::cout << "You Won!\n";
        exit(0);
    }
}

void AIattack(Fighter& player) {
    std::cout << "AI turn!\n";

    int attacks[3] = { Fire, Freeze, Thunder };
    int randomIndex = rand() % 3;

    int dmg = attacks[randomIndex];
    player.health -= dmg;

    std::cout << "AI dealt " << dmg << " damage!\n";
}

void menu(Fighter& character1, Fighter& character2) {
    bool running = true;

    while (running) {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Exit\n";

        std::cout << "Select: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Game Started!\n";

            while (true) {
                whoWin(character1, character2);

                character1.attack(character2);
                whoWin(character1, character2);

                AIattack(character1);
                whoWin(character1, character2);

                std::cout << "Your HP: " << character1.health << "\n";
                std::cout << "AI HP: " << character2.health << "\n";
            }
            break;

        case 2:
            std::cout << "Exiting...\n";
            running = false;
            break;

        default:
            std::cout << "Invalid choice!\n";
        }
    }
}

int main() {
    srand(time(0));

    Fighter character1;
    character1.name = "Warrior";
    character1.health = 100;

    Fighter character2;
    character2.name = "AI Warrior";
    character2.health = 100;

    menu(character1, character2);

    return 0;
}