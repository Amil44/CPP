#include <iostream>
#include <vector>
//using namespace std;

bool checkWinP1P2(std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& Player2coordinat) {
    bool player1Win = true;
    bool player2Win = true;

    for (int i = 0; i < Player2coordinat.size(); i++) {
        for (int j = 0; j < Player2coordinat[i].size(); j++) {
            if (Player2coordinat[i][j] == 1) {
                player1Win = false;
            }
        }
    }

    for (int i = 0; i < Player1coordinat.size(); i++) {
        for (int j = 0; j < Player1coordinat[i].size(); j++) {
            if (Player1coordinat[i][j] == 1) {
                player2Win = false;
            }
        }
    }

    if (player1Win) {
        std::cout << "Player1 Won!" << std::endl;
        return true;
    }

    if (player2Win) {
        std::cout << "Player2 Won!" << std::endl;
        return true;
    }

    return 0;
}

bool checkWinP1AI(std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& AIcoordinat) {
    bool player1Win = true;
    bool AIWin = true;

    for (int i = 0; i < AIcoordinat.size(); i++) {
        for (int j = 0; j < AIcoordinat[i].size(); j++) {
            if (AIcoordinat[i][j] == 1) {
                player1Win = false;
            }
        }
    }

    for (int i = 0; i < Player1coordinat.size(); i++) {
        for (int j = 0; j < Player1coordinat[i].size(); j++) {
            if (Player1coordinat[i][j] == 1) {
                AIWin = false;
            }
        }
    }

    if (player1Win) {
        std::cout << "Player1 Won!" << std::endl;
        return true;
    }

    if (AIWin) {
        std::cout << "AI Wins!" << std::endl;
        return true;
    }

    return 0;
}

void currentSituationAI(std::vector<std::vector<int>>& Player1coordinatShow, std::vector<std::vector<int>>& AIcoordinatShow) {
    std::cout << "Your Map!" << std::endl;

    for (int i = 0; i < Player1coordinatShow.size(); i++) {
        for (int j = 0; j < Player1coordinatShow[i].size(); j++) {
            int p = Player1coordinatShow[i][j];

            if (p == 0) {
                std::cout << "~ "; // Water
            }
            else if (p == 1) {
                std::cout << "S "; // Ship
            }
            else if (p == 2) {
                std::cout << "X "; // Hit
            }
            else if (p == 3) {
                std::cout << "O "; // Miss
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\nAI Map!" << std::endl;

    for (int i = 0; i < AIcoordinatShow.size(); i++) {
        for (int j = 0; j < AIcoordinatShow[i].size(); j++) {
            int p = AIcoordinatShow[i][j];

            if (p == 0) {
                std::cout << "~ "; // Water
            }
            else if (p == 1) {
                std::cout << "S "; // Ship
            }
            else if (p == 2) {
                std::cout << "X "; // Hit
            }
            else if (p == 3) {
                std::cout << "O "; // Miss
            }
        }
        std::cout << std::endl;
    }

}

void currentSituation(std::vector<std::vector<int>>& Player1coordinatShow, std::vector<std::vector<int>>& Player2coordinatShow) {
    std::cout << "Your Map!" << std::endl;

    for (int i = 0; i < Player1coordinatShow.size(); i++) {
        for (int j = 0; j < Player1coordinatShow[i].size(); j++) {
            int p = Player1coordinatShow[i][j];

            if (p == 0) {
                std::cout << "~ "; // Water
            }
            else if (p == 1) {
                std::cout << "S "; // Ship
            }
            else if (p == 2) {
                std::cout << "X "; // Hit
            }
            else if (p == 3) {
                std::cout << "O "; // Miss
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\nPlayer2 Map!" << std::endl;

    for (int i = 0; i < Player2coordinatShow.size(); i++) {
        for (int j = 0; j < Player2coordinatShow[i].size(); j++) {
            int p = Player2coordinatShow[i][j];

            if (p == 0) {
                std::cout << "~ "; // Water
            }
            else if (p == 1) {
                std::cout << "S "; // Ship
            }
            else if (p == 2) {
                std::cout << "X "; // Hit
            }
            else if (p == 3) {
                std::cout << "O "; // Miss
            }
        }
        std::cout << std::endl;
    }

}

void player1(std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& Player2coordinat, std::vector<std::vector<int>>& Player2coordinatShow) {
    std::cout << "\nYour turn!" << std::endl;

    char row;
    std::cout << "Select row(A-J): ";
    std::cin >> row;

    int rowIndex = toupper(row) - 'A';

    int column;
    std::cout << "Select column: ";
    std::cin >> column;
    column--;


    if ((rowIndex >= 0 && rowIndex < 10) && (column >= 0 && column < 10)) {
        if (Player2coordinat[rowIndex][column] == 1) {
            Player2coordinatShow[rowIndex][column] = 2;
            Player2coordinat[rowIndex][column] = 2;
        }
        else if (Player2coordinat[rowIndex][column] == 2 || Player2coordinat[rowIndex][column] == 3) {
            std::cout << "That Coordinate Has Already Hit!" << std::endl;
        }
        else {
            Player2coordinatShow[rowIndex][column] = 3;
        }
    }
    else {
        std::cout << "Invalid value!" << std::endl;
    }


    while (Player2coordinat[rowIndex][column] != 0) {
        if (checkWinP1P2(Player1coordinat, Player2coordinat)) {
            exit(0);
        }
        else {
            char row;
            std::cout << "Select row(A-J): ";
            std::cin >> row;

            int rowIndex = toupper(row) - 'A';

            int column;
            std::cout << "Select column: ";
            std::cin >> column;
            column--;

            if ((rowIndex >= 0 && rowIndex < 10) && (column >= 0 && column < 10)) {
                if (Player2coordinat[rowIndex][column] == 1) {
                    Player2coordinatShow[rowIndex][column] = 2;
                    Player2coordinat[rowIndex][column] = 2;
                }
                else if (Player2coordinat[rowIndex][column] == 2 || Player2coordinat[rowIndex][column] == 3) {
                    std::cout << "That Coordinate Has Already Hit!" << std::endl;
                    continue;
                }
                else {
                    Player2coordinat[rowIndex][column] = 3;
                    Player2coordinatShow[rowIndex][column] = 3;
                    break;
                }
            }
            else {
                std::cout << "Invalid value!" << std::endl;
            }
        }

    }
}

void player2(std::vector<std::vector<int>>& Player2coordinat, std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& Player1coordinatShow) {

    std::cout << "\nPlayer2 turn!" << std::endl;

    char row2;
    std::cout << "Select row(A-J): ";
    std::cin >> row2;

    int rowIndex2 = toupper(row2) - 'A';

    int column2;
    std::cout << "Select column: ";
    std::cin >> column2;
    column2--;

    if (Player1coordinat[rowIndex2][column2] == 1) {
        Player1coordinatShow[rowIndex2][column2] = 2;
        Player1coordinat[rowIndex2][column2] = 2;
    }
    else if (Player1coordinat[rowIndex2][column2] == 2 || Player1coordinat[rowIndex2][column2] == 3) {
        std::cout << "That Coordinate Has Already Hit!" << std::endl;
    }
    else {
        Player1coordinatShow[rowIndex2][column2] = 3;
    }

    while (Player1coordinat[rowIndex2][column2] != 0) {
        if (checkWinP1P2(Player1coordinat, Player2coordinat)) {
            exit(0);
        }
        else {
            char row2;
            std::cout << "Select row(A-J): ";
            std::cin >> row2;

            int rowIndex2 = toupper(row2) - 'A';

            int column2;
            std::cout << "Select column: ";
            std::cin >> column2;
            column2--;

            if (rowIndex2 >= 0 && rowIndex2 < 10 && column2 >= 0 && column2 < 10) {
                if (Player1coordinat[rowIndex2][column2] == 1) {
                    Player1coordinatShow[rowIndex2][column2] = 2;
                    Player1coordinat[rowIndex2][column2] = 2;
                }
                else if (Player1coordinat[rowIndex2][column2] == 2 || Player1coordinat[rowIndex2][column2] == 3) {
                    std::cout << "That Coordinate Has Already Hit!" << std::endl;
                    continue;
                }
                else {
                    Player1coordinatShow[rowIndex2][column2] = 3; 
                    Player1coordinat[rowIndex2][column2] = 3;
                    break;
                }
            }
            else {
                std::cout << "Invalid value!" << std::endl;
            }
        }


    }

}

static int lastHitRow = -1;
static int lastHitCol = -1;
static bool ifHit = false;
static int targetDir = 0; // 0: up, 1: down, 2: left, 3: right

void playerAI(std::vector<std::vector<int>>& AIcoordinat, std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& Player1coordinatShow) {
    std::cout << "\nAI turn!" << std::endl;
    
    int r, c;
    bool foundTarget = false;

    if (ifHit) {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // (R, C)
        
        for (int i = 0; i < 4; i++) {
            int nextR = lastHitRow + directions[i][0];
            int nextC = lastHitCol + directions[i][1];

            if (nextR >= 0 && nextR < 10 && nextC >= 0 && nextC < 10 && Player1coordinatShow[nextR][nextC] == 0) {
                r = nextR;
                c = nextC;
                foundTarget = true;
                break;
            }
        }
    }

    if (!foundTarget) {
        ifHit = false;
        do {
            r = rand() % 10;
            c = rand() % 10;
        } while (Player1coordinatShow[r][c] != 0); 
    }

    std::cout << "AI targets: " << char('A' + r) << (c + 1) << std::endl;

    if (Player1coordinat[r][c] == 1) { 
        std::cout << "AI Hit your ship!" << std::endl;

        Player1coordinatShow[r][c] = 2;
        Player1coordinat[r][c] = 2;
        lastHitRow = r;
        lastHitCol = c;
        ifHit = true;
        
        if (!checkWinP1AI(Player1coordinat, AIcoordinat)) {
            playerAI(AIcoordinat, Player1coordinat, Player1coordinatShow);
        }
    } 
    else { 
        std::cout << "AI Missed!" << std::endl;
        Player1coordinatShow[r][c] = 3;
        Player1coordinat[r][c] = 3;
    }
}

void BatlleWithAI(std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& Player1coordinatShow) {
    std::vector<std::vector<int>> AIcoordinat(10, std::vector<int>(10, 0));
    std::vector<std::vector<int>> AIcoordinatShow(10, std::vector<int>(10, 0));

    short int ship = 1; // S

    enum Ship {
        Carrier = 5,     // Carrier : 5 cell
        Battleship = 4,  // Battleship : 4 cell
        Submarine = 3,   // Submarine : 3 cell
        Cruiser = 3,     // Cruiser : 3 cell
        Destroyer = 2    // Destroyer : 2 cell
    };

    Ship ships[] = { Carrier, Battleship, Submarine, Cruiser, Destroyer };

    enum Along {
        Up = 1, // Row++      
        Down = -1, // Row--
        Left = -1, // Col--
        Right  = 1, // Col++    
    };

    Along moves[] = { Up, Down, Left, Right };
    short int till = 5;

    for (int i = 0; i < till; i++) {
        short int check = 0;
        short int x = 0;

        srand(time(0));

        int randomAlong = rand() % 4 + 1;
        int randomMove = moves[randomAlong];

        short unsigned int randomNumRow = rand() % 10;
        short unsigned int randomNumCol = rand() % 10;

        for (int j = 0; j < ships[i]; j++) {
            if (AIcoordinat[randomNumRow][randomNumCol] != ship && (AIcoordinat[randomNumRow + 1][randomNumCol] == 0 && AIcoordinat[randomNumRow - 1][randomNumCol] == 0 && AIcoordinat[randomNumRow][randomNumCol + 1] == 0 && AIcoordinat[randomNumRow][randomNumCol - 1] == 0)){
                AIcoordinat[randomNumRow][randomNumCol] = ship;
            }
                
            else {
                till++;
                break;
            }

            if (randomMove == Up) {
                randomNumRow++;
            }
            else if (randomMove == Down){
                randomNumRow--;
            }
            else if (randomMove == Left){
                randomNumCol--;
            }
            else if (randomMove == Right){
                randomNumCol++;
            }
        }
    }

    while (!checkWinP1AI(Player1coordinat, AIcoordinat)) {
        currentSituationAI(Player1coordinatShow, AIcoordinatShow);
        player1(Player1coordinat, AIcoordinat, AIcoordinatShow);
        currentSituationAI(Player1coordinatShow, AIcoordinatShow);
        playerAI(AIcoordinat, Player1coordinat, Player1coordinatShow);
    }

}

void TwoPlayersMode(std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& Player1coordinatShow) {
    std::vector<std::vector<int>> Player2coordinat = {
    {0,0,0,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,0,0,1},
    {0,0,0,0,0,0,1,0,0,1},
    {0,0,0,0,0,0,1,0,0,0}
    };

    std::vector<std::vector<int>> Player2coordinatShow = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    while (!checkWinP1P2(Player1coordinat, Player2coordinat)) {
        currentSituation(Player1coordinatShow, Player2coordinatShow);
        player1(Player1coordinat, Player2coordinat, Player2coordinatShow);
        currentSituation(Player1coordinatShow, Player2coordinatShow);
        player2(Player2coordinat, Player1coordinat, Player1coordinatShow);
    }
}

void GameMode(std::vector<std::vector<int>>& Player1coordinat, std::vector<std::vector<int>>& Player1coordinatShow) {
    bool isTrue = true;

    std::cout << "===== Mode =====" << std::endl;
    std::cout << "1.Two Players\n2.Batlle with AI\n3.Exit" << std::endl;

    int op;
    std::cout << "\nSelect: ";
    std::cin >> op;
    std::cout << std::endl;

    while (isTrue) {
        if (op == 1) {
            TwoPlayersMode(Player1coordinat, Player1coordinatShow);
        }
        else if (op == 2) {
            BatlleWithAI(Player1coordinat, Player1coordinatShow);
        }
        else if (op == 3) {
            isTrue = false;
        }
    }
}

int main() {
    std::vector<std::vector<int>> Player1coordinat = {
        {0,0,0,1,1,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {1,1,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1,0,0,1},
        {0,0,0,0,0,0,1,0,0,1},
        {0,0,0,0,0,0,1,0,0,0}
    };

    std::vector<std::vector<int>> Player1coordinatShow = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    bool isTrue = true;

    while (isTrue) {
        std::cout << "===== Menu =====" << std::endl;
        std::cout << "1.Start Game\n2.Exit" << std::endl;

        int op;
        std::cout << "\nSelect: ";
        std::cin >> op;
        std::cout << std::endl;

        if (op == 1) {
            GameMode(Player1coordinat, Player1coordinatShow);
        }
        else if (op == 2) {
            std::cout << "Program is closing ..." << std::endl;
            isTrue = false;
        }
    }

    return 0;
}