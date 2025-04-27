#include <iostream>
#include "Models/Client/Client.h"
#include "Models/Employee/Employee.h"
#include "menu/Auth/AuthManager.h"
#include "menu/CMenu.h"
#include "menu/MyVector.h"

int main() {
    
    MyVector<Client> clients;
    MyVector<Employee> employees;
    employees.push_back(Employee("admin", "admin123", "Администратор"));

    AuthManager auth(clients, 100, employees, 10);
    std::string currentUserLogin;

    CMenu mainMenu;

    mainMenu.addItem(CMenuItem("Регистрация клиента", [&]() {
        Client newClient;
        std::cin >> newClient;

        if (auth.registerClient(newClient.getLogin(), newClient.getPassword())) {
            std::cout << "Регистрация успешна!\n";
        } else {
            std::cout << "Ошибка: Логин занят или достигнут лимит клиентов!\n";
        }
    }));

    mainMenu.addItem(CMenuItem("Войти", [&]() {
        std::string login, password;
        std::cout << "Логин: ";
        std::cin >> login;
        std::cout << "Пароль: ";
        std::cin >> password;

        int role = auth.authenticate(login, password);
        currentUserLogin = login;

        if (role == 0) {
            std::cout << "Ошибка: Неверный логин или пароль!\n";
            return;
        }

        CMenu userMenu;
        if (role == 1) { // Меню клиента
            userMenu.addItem(CMenuItem("Оформить вклад", [&]() {
                Deposit deposit;
                std::cin >> deposit;

                for (int i = 0; i < clients.getSize(); ++i) {
                    if (clients[i].getLogin() == currentUserLogin) {
                        if (clients[i].addDeposit(deposit)) {
                            std::cout << "Вклад успешно добавлен!\n";
                        } else {
                            std::cout << "Ошибка: Превышен лимит вкладов!\n";
                        }
                        break;
                    }
                }
            }));

            userMenu.addItem(CMenuItem("Мой профиль", [&]() {
                for (int i = 0; i < clients.getSize(); ++i) {
                    if (clients[i].getLogin() == currentUserLogin) {
                        clients[i].displayInfo();
                        const Deposit* deposits = clients[i].getDeposits();
                        for (int j = 0; j < clients[i].getDepositCount(); ++j) {
                            std::cout << "🔹 " << deposits[j] << "\n";
                        }
                        break;
                    }
                }
            }));

        } else if (role == 2) { // Меню сотрудника
            userMenu.addItem(CMenuItem("Список клиентов", [&]() {
                if (clients.getSize() == 0) {
                    std::cout << std::endl;
                    std::cout << "Список клиентов пуст.\n";
                    return;
                }
                std::cout << std::endl;
                std::cout << "Список клиентов (" << clients.getSize() << "):\n";
                for (int i = 0; i < clients.getSize(); ++i) {
                    std::cout << i + 1 << ". " << clients[i].getLogin() << "\n";
                }
            }));

            userMenu.addItem(CMenuItem("Удалить клиента", [&]() {
                std::string targetLogin;
                std::cout << "Введите логин клиента: ";
                std::cin >> targetLogin;

                if (auth.removeClient(targetLogin)) {
                    std::cout << "Клиент " << targetLogin << " удалён!\n";
                } else {
                    std::cout << std::endl;
                    std::cout << "Ошибка: Клиент не найден!\n";
                }
            }));

            userMenu.addItem(CMenuItem("Сортировать клиентов", [&]() {
                auth.sortClients();
                std::cout << "Клиенты отсортированы по логину.\n";

                for (int i = 0; i < clients.getSize(); ++i) {
                    std::cout << "  " << i + 1 << ". " << clients[i].getLogin() << "\n";
                }
            }));

            userMenu.addItem(CMenuItem("Просмотр вкладов", [&]() {
                if (clients.getSize() == 0) {
                    std::cout << std::endl;
                    std::cout << "Нет клиентов для просмотра.\n";
                    return;
                }

                std::cout << "Выберите клиента (1-" << clients.getSize() << "): ";
                int choice;
                std::cin >> choice;

                if (choice < 1 || choice > clients.getSize()) {
                    std::cout << std::endl;
                    std::cout << "Ошибка: Неверный выбор!\n";
                    return;
                }

                employees[0].viewClientDeposits(clients[choice - 1]);
            }));
        }

        userMenu.run();
    }));
    mainMenu.addItem(CMenuItem("Демонстрация вектора (весь диапазон)", []() {
        MyVector<std::string> vec;
    
        std::cout << "\nДобавление строк в вектор\n";
        vec.push_back("Один");
        vec.push_back("Два");
        vec.push_back("Три");
    
        std::cout << "Размер после добавления: " << vec.getSize() << "\n";
    
        std::cout << "\nИтерация по диапазону:\n";
        for (auto it:vec) {
            std::cout << "  * " << it << "\n";
        }
    
        std::cout << "\nУдаляем элемент с индексом 1\n";
        vec.erase(1);
    
        std::cout << "После удаления:\n";
        for (auto it:vec) {
            std::cout << "  * " << it << "\n";
        }
    
        std::cout << "\nДобавим элементы вновь\n";
        vec.push_back("Четыре");
        vec.push_back("Пять");
    
        std::cout << "Итоговое содержимое:\n";
        for (auto it:vec) {
            std::cout << "  * " << it << "\n";
        }
    
        std::cout << "Общий размер: " << vec.getSize() << "\n";
    }));
    
    mainMenu.run();
}
