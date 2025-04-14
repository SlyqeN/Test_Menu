#include "CMenu.h"
#include <iostream>
#include <limits>

void CMenu::addItem(const CMenuItem& item) {
    items.push_back(item);
}

void CMenu::run() const {
    while (true) {
        std::cout << "\n====== Главное меню ======\n";

        int i = 1;
        for (auto it = items.begin(); it != items.end(); ++it) {
            std::cout << i++ << ". " << it->getTitle() << "\n";
        }

        std::cout << "0. Выход\nВыберите пункт: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        if (choice == 0) break;

        if (choice < 1 || choice > items.getSize()) {
            std::cout << "Неверный пункт! Попробуйте снова.\n";
            continue;
        }

        items[choice - 1].execute();
    }
}
