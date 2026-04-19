#include <iostream>
#include <string>

class Player {
    int _id;
    std::string _username;
    int _health;
    int _attack;
    int _level;

public:
    Player() {
        _id = 0;
        _username = "";
        _health = 0;
        _attack = 0;
        _level = 0;
    }

    Player(int id, std::string username, int health, int attack, int level = 1) {
        _id = id;
        _username = username;
        _health = health;
        _attack = attack;
        _level = level;
    }

    void createPlayer() {
        std::cout << "Enter player id: ";
        std::cin >> _id;
        std::cin.ignore();

        std::cout << "Enter username: ";
        std::getline(std::cin, _username);

        std::cout << "Enter health: ";
        std::cin >> _health;

        std::cout << "Enter attack: ";
        std::cin >> _attack;

        _level = 1;
    }

    void takeDamage(int damage) {
        _health -= damage;
        if (_health < 0) _health = 0; 
    }

    void levelUp() {
        if (_username != "") {
            if (_level < 10) {
                _level++;
                _attack += 5;
                _health += 20;
                std::cout << "Player updated successfully.\n";
            }
            else std::cout << "Player is maximum level.\n";
        }
        else std::cout << "Player does not exist.\n";
    }

    bool isAlive() {
        return _health > 0;
    }

    void fight(Player& enemy) {
        std::cout << "\n--- FIGHT START ---\n";
        std::cout << _username << " vs " << enemy._username << "\n\n";

        while (isAlive() && enemy.isAlive()) {
            enemy.takeDamage(_attack);
            std::cout << _username << " attacked " << enemy._username << "! HP: " << enemy._health << "\n";
            if (!enemy.isAlive()) break;

            takeDamage(enemy._attack);
            std::cout << enemy._username << " attacked " << _username << "! HP: " << _health << "\n";
        }

        std::cout << "\n--- RESULT ---\n";
        if (isAlive()) std::cout << _username << " WINS!\n";
        else           std::cout << enemy._username << " WINS!\n";
    }

    int getId() const { return _id; } 

    void show() {
        std::cout << "Id: " << _id << " | "
            << "Username: " << _username << " | "
            << "Health: " << _health << " | "
            << "Attack: " << _attack << " | "
            << "Level: " << _level << " | " << std::endl;
    }
};

class Game {
    std::string _gameName;
    Player* _players;
    size_t _count;

public:
    Game() {
        _gameName = "";
        _players = nullptr;
        _count = 0;
    }

    void setGameName() { 
        std::cout << "Enter game name: ";
        std::cin.ignore();
        std::getline(std::cin, _gameName);
    }

    void addPlayer() { 
        _count++;
        Player* temp = new Player[_count];

        for (int i = 0; i < (int)_count - 1; i++)
            temp[i] = _players[i];

        delete[] _players;
        _players = temp;
        _players[_count - 1].createPlayer();
    }

    Player* getPlayerById(int id) { 
        for (int i = 0; i < (int)_count; i++)
            if (_players[i].getId() == id)
                return &_players[i];
        return nullptr;
    }

    void fightPlayers() {
        int id1, id2;
        std::cout << "Enter first player id: ";
        std::cin >> id1;
        std::cout << "Enter second player id: ";
        std::cin >> id2;

        Player* p1 = getPlayerById(id1);
        Player* p2 = getPlayerById(id2);

        if (!p1 || !p2) { std::cout << "Player not found!\n"; return; }

        p1->fight(*p2);
    }

    void levelUpPlayer() { 
        std::cout << "Enter player id: ";
        int id; std::cin >> id;

        Player* p = getPlayerById(id);
        if (p) p->levelUp();
        else   std::cout << "Player not found!\n";
    }

    void show() { 
        std::cout << "Game Name: " << (_gameName.empty() ? "N/A" : _gameName) << "\n";
        for (int i = 0; i < (int)_count; i++)
            _players[i].show();
    }

    ~Game() { 
        delete[] _players;
    }
};

void playerMenu(Game& g) { 
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\n====== PLAYER MENU ======\n";
        std::cout << "1. Add Player\n";
        std::cout << "2. Show Players\n";
        std::cout << "3. Get Player By Id\n";
        std::cout << "4. Level Up\n";
        std::cout << "5. Exit\n";

        int op; std::cin >> op;

        if (op == 1) g.addPlayer();
        else if (op == 2) g.show();
        else if (op == 3) {
            std::cout << "Enter id: ";
            int id; std::cin >> id;
            Player* p = g.getPlayerById(id);
            if (p) p->show();
            else   std::cout << "Player not found!\n";
        }
        else if (op == 4) g.levelUpPlayer();
        else if (op == 5) isRunning = false;
        else std::cout << "Invalid operation!\n";
    }
}

void gameMenu(Game& g) { 
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\n====== GAME MENU ======\n";
        std::cout << "1. Set Game Name\n";
        std::cout << "2. Show Game\n";
        std::cout << "3. Fight Players\n";
        std::cout << "4. Level Up Player\n";
        std::cout << "5. Exit\n";

        int op; std::cin >> op;

        if (op == 1) g.setGameName();
        else if (op == 2) g.show();
        else if (op == 3) g.fightPlayers();
        else if (op == 4) g.levelUpPlayer();
        else if (op == 5) isRunning = false;
        else std::cout << "Invalid operation!\n";
    }
}

void mainMenu(Game& g) {
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\n====== MAIN MENU ======\n";
        std::cout << "1. Game Settings\n";
        std::cout << "2. Player\n";
        std::cout << "3. Exit\n";

        int op; std::cin >> op;

        if (op == 1) gameMenu(g);
        else if (op == 2) playerMenu(g);
        else if (op == 3) { std::cout << "Exiting...\n"; isRunning = false; }
        else std::cout << "Invalid operation!\n";
    }
}

int main() {
    Game g;
    mainMenu(g);
}