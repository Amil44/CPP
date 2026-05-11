#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void AddTask() {
    std::cout << "Add Text: ";

    std::ofstream file("Task.txt", std::ios::app);

    if (!file.is_open()) {
        std::cout << "File doesn't exist.";
    }

    std::string text;
    std::cin.ignore();
    getline(std::cin, text);

    file << text << std::endl;

    file.close();
}

void ShowTask() {
    std::cout << "Your Text:" << std::endl;
    std::ifstream file("Task.txt");

    std::string text;

    while (getline(file, text)) {
        std::cout << text << std::endl;
    }

    file.close();
}

void DeleteTask() {
    std::ifstream inFile("Task.txt");

    if (!inFile.is_open()) {
        std::cout << "File doesn't exist.\n";
    }

    std::vector<std::string> lines;
    std::string text;

    while (getline(inFile, text)) {
        lines.push_back(text);
        std::cout << text << std::endl;
    }

    inFile.close();

    std::cout << "Remove line: ";
    int line;
    std::cin >> line;

    if (line < 1 || line > lines.size()) {
        std::cout << "Invalid line number.\n";
    }

    lines.erase(lines.begin() + (line - 1));

    std::ofstream outFile("Task.txt");

    for (int i = 0; i < lines.size(); i++) {
        outFile << lines[i] << std::endl;
    }

    outFile.close();

    std::cout << "Line removed successfully.\n";
}

void Menu() {
    bool isT = true;

    while (isT) {
        std::cout << "===== MENU =====\n";
        std::cout << "1.Add Task\n2.Show Task\n3.Delete Task\n4.Exit\n";

        std::cout << "Select: ";
        int select; std::cin >> select;

        if (select == 1) AddTask();
      
        else if (select == 2) ShowTask();
        
        else if (select == 3) DeleteTask();
        
        else if (select == 4) {
            std::cout << "Program is closing...\n";
            isT = false;
        }
        else std::cout << "Invalid operatin!\n";
        
    }
}

int main(){
    Menu(); return 0;
}
