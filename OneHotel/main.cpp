//
//  main.cpp
//  OneHotel
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "HashTable.h"
#include "Windows.h"
#include "Tree.h"
#include "List.h"

void RegistrateGuest(HashTable& table)
{
    std::string passportNo = EnterPassportNo();
    std::string fio = EnterFio();
    uint16_t birthYear = EnterBirthYear();
    std::string address = EnterAddress();
    std::string arrivalDestination = EnterArrivalDestination();

    Guest guest(passportNo, fio, birthYear, address, arrivalDestination);

    bool isAdded;
    isAdded = table.AddElement(guest);
    isAdded ? std::cout << "\nПостоялец успешно зарегистрирован!\n"
        : std::cout << "\nТакой постоялец уже зарегистрирован!\n";
}

void DeleteGuest(HashTable& table, List& list)
{
    std::string passportNo = EnterPassportNo();

    bool isDeleted;
    isDeleted = table.DeleteElement(passportNo);
    isDeleted ? std::cout << "\nПостоялец успешно удалён!\n"
        : std::cout << "\nТакого постояльца не зарегистировано!\n";

    if (list.IsGuestInList(passportNo))
        list.DeleteByPassport(passportNo);
}

void AddSuite(Tree& tree)
{
    std::string suiteNo = EnterSuiteNo();
    char bedsAmount = EnterBedsAmount();
    char roomsAmount = EnterRoomsAmount();
    bool bathroom = EnterBathroom();
    std::string furnishing = EnterFurnishing();

    Suite suite(suiteNo, bedsAmount, roomsAmount, bathroom, furnishing);

    bool isAdded;
    isAdded = tree.AddElement(suite);
    isAdded ? std::cout << "\nГостиничный номер успешно добавлен!\n"
        : std::cout << "\nТакой гостиничный номер уже добавлен!\n";
}

void DeleteSuite(Tree& tree, List& list)
{
    std::string suiteNo = EnterSuiteNo();

    bool isDeleted;
    isDeleted = tree.DeleteElement(suiteNo);
    isDeleted ? std::cout << "\nГостиничный номер успешно удалён!\n"
        : std::cout << "\nТакого номера нет в гостинице!\n";

    if (list.IsSuiteInList(suiteNo))
        list.DeleteBySuite(suiteNo);
}

void CheckIn(HashTable& table, Tree& tree, List& list)
{
    std::string passportNo = EnterPassportNo();

    Guest foundGuest;
    table.FindByPassportNo(passportNo, foundGuest);
    if (foundGuest.IsEmpty()) {
        std::cout << "\nТакой постоялец не зарегистрирован в гостинице!\n";
        return;
    }

    bool isRelated;
    isRelated = list.CheckGuest(passportNo);
    if (isRelated) {
        std::cout << "\nТакой постоялец уже зарегистрирован в номере!\n";
        return;
    }

    std::string suiteNo = EnterSuiteNo();

    Suite foundSuite;
    tree.FindByNumber(suiteNo, foundSuite);
    if (foundSuite.IsEmpty()) {
        std::cout << "\nТакой номер не зарегистрирован в гостинице!\n";
        return;
    }

    bool isEnoughBeds;
    isEnoughBeds = list.CheckSuite(foundSuite);
    if (!isEnoughBeds) {
        std::cout << "\nВ выбранном номере нет свободных мест!\n";
        return;
    }

    std::string checkInDate = EnterCheckInDate();
    std::string checkOutDate = EnterCheckOutDate();

    Relation relation(passportNo, suiteNo, checkInDate, checkOutDate);

    list.AddElement(relation);
    HoarSort(0, list.GetSize() - 1, list);

    std::cout << "\nПостоялец успешно зарегистрирован в номере!\n";
}

void CheckOut(HashTable& table, Tree& tree, List& list)
{
    std::string passportNo = EnterPassportNo();

    Guest foundGuest;
    table.FindByPassportNo(passportNo, foundGuest);
    if (foundGuest.IsEmpty()) {
        std::cout << "\nТакой постоялец не зарегистрирован в гостинице!\n";
        return;
    }

    bool isRelated;
    isRelated = list.CheckGuest(passportNo);
    if (!isRelated) {
        std::cout << "\nТакой постоялец не зарегистрирован в номере!\n";
        return;
    }

    list.DeleteByPassport(passportNo);

    std::cout << "\nПостоялец выселен из номера!\n";
}

void FindByPassportNo(HashTable& table, List& list)
{
    Guest foundGuest;
    std::string passportNo = EnterPassportNo();

    table.FindByPassportNo(passportNo, foundGuest);

    if (foundGuest.IsEmpty())
        std::cout << "\nПостояльцев с таким номером паспорта не зарегистрировано!\n";
    else {
        std::cout << "\n1. Паспортные данные: " << foundGuest.GetPassportNo() << std::endl <<
            "2. ФИО: " << foundGuest.GetFio() << std::endl << "3. Год рождения: " << foundGuest.GetBirthYear() <<
            std::endl << "4. Адрес: " << foundGuest.GetAddress() << std::endl << "5. Цель прибытия: "
            << foundGuest.GetArrivalDestination() << std::endl;

        std::string foundSuiteNo;
        list.FindByPassportNo(passportNo, foundSuiteNo);
        if (foundSuiteNo.empty())
            std::cout << std::endl << "Постоялец не зарегистрирован в номере." << std::endl;
        else
            std::cout << std::endl << "Постоялец зарегистрирован в номере " << foundSuiteNo << std::endl;
    }
}

void FindBySuiteNo(HashTable& table, Tree& tree, List& list)
{
    Suite foundSuite;
    std::string suiteNo = EnterSuiteNo();

    tree.FindByNumber(suiteNo, foundSuite);

    if (foundSuite.IsEmpty())
        std::cout << "\nТаких гостиничных номеров не зарегистрировано!\n";
    else {
        std::cout << "\n1. Номер: " << foundSuite.GetSuiteNo() << std::endl <<
            "2. Количество мест: " << std::to_string(foundSuite.GetBedsAmount()) << std::endl << "3. Количество комнат: "
            << std::to_string(foundSuite.GetRoomsAmount()) << std::endl << "4. Наличие санузла: ";
        foundSuite.GetBathroom() ? std::cout << "есть" : std::cout << "нет";
        std::cout << std::endl << "5. Оборудование: " << foundSuite.GetFurnishing() << std::endl;

        std::list<std::string> foundPassportNo;
        list.FindBySuiteNo(suiteNo, foundPassportNo);
        if (foundPassportNo.empty())
            std::cout << std::endl << "В номере не зарегистрированы постояльцы." << std::endl;
        else {
            size_t countGuests = 0;
            std::cout << std::endl << "В номере зарегистрированы следующие постояльцы:" << std::endl;

            for (auto it = foundPassportNo.begin(); it != foundPassportNo.end(); ++it) {
                countGuests++;
                Guest foundGuest;
                table.FindByPassportNo(*it, foundGuest);

                std::cout << std::endl << countGuests << '.' << " ФИО: " << foundGuest.GetFio() << std::endl
                    << "   Паспортные данные: " << *it << std::endl;
            }
        }
    }
}

void FindByFurnishing(Tree& tree)
{
    size_t count = 0;
    std::shared_ptr<Node> rootNode = tree.GetRootNode();
    std::string furnishing = EnterFurnishing();
    std::list<Suite> foundSuites;

    tree.FindByFurnishing(rootNode, furnishing, foundSuites);

    if (foundSuites.empty())
        std::cout << "\nГостиничных номеров с таким оборудованием нет!\n";
    else {
        for (auto it = foundSuites.begin(); it != foundSuites.end(); ++it) {
            count++;
            std::cout << std::endl << count << '.' << " Номер: " << it->GetSuiteNo() << std::endl
                << "   Количество мест: " << std::to_string(it->GetBedsAmount()) << std::endl
                << "   Количество комнат: " << std::to_string(it->GetRoomsAmount()) << std::endl
                << "   Оборудование: " << it->GetFurnishing() << std::endl;
        }
    }
}

void FindByFio(HashTable& table)
{
    std::string fio = EnterFio();
    std::list<Guest> foundGuests;

    table.FindByFio(fio, foundGuests);

    if (foundGuests.empty())
        std::cout << "\nПостояльцев с такими фамилиями не зарегистрировано!\n";
    else {
        size_t countGuests = 0;
        std::cout << std::endl << "Постояльцы с совпадающими фамилиями:" << std::endl;

        for (auto it = foundGuests.begin(); it != foundGuests.end(); ++it) {
            countGuests++;

            std::cout << std::endl << countGuests << '.' << " ФИО: " << it->GetFio() << std::endl
                << "   Паспортные данные: " << it->GetPassportNo() << std::endl;
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU");

    std::string choice, ans;
    HashTable table;
    Tree tree;
    List list;

    while (true) {
        std::cout << std::string(1000, '\n');

        std::cout << "Добро пожаловать в систему регистрации постояльцев в гостинице!\n"
            << "Выберите действие:\n\n";

        std::cout << "1. Регистрация нового постояльца\n"
            << "2. Удаление данных о постояльце\n"
            << "3. Просмотр всех зарегистрированных постояльцев\n"
            << "4. Очистка данных о постояльцах\n"
            << "5. Поиск постояльца по номеру паспорта\n"
            << "6. Поиск постояльца по ФИО\n"
            << "7. Добавление нового гостиничного номера\n"
            << "8. Удаление сведений о гостиничном номере\n"
            << "9. Просмотр всех имеющихся гостиничных номеров\n"
            << "10. Очистка данных о гостиничных номерах\n"
            << "11. Поиск гостиничного номера по номеру\n"
            << "12. Поиск гостиничного номера по фрагментам оборудования\n"
            << "13. Регистрация вселения постояльца\n"
            << "14. Регистрация выселения постояльца\n"
            << "0. Выход из программы\n\n";

        while (true) {
            try {
                std::getline(std::cin, ans);

                if (ans.length() != 1 || ans.length() != 2)
                    throw std::invalid_argument("");

                for (auto i = 0; i < ans.length(); i++) {
                    if (ans[i] < '0' || ans[i] > '9')
                        throw std::invalid_argument("");
                }
         
                if (std::stoi(ans) < 0 || std::stoi(ans) > 14) {
                    throw std::out_of_range("");
                }
            }
            catch (std::invalid_argument & ia) {
                std::cout << "Ошибка: введите целочисленный параметр!\n\n";
                continue;
            }
            catch (std::out_of_range & oor) {
                std::cout << "Ошибка: введите параметр в диапазоне от 0 до 14!\n\n";
                continue;
            }

            break;
        }

    switch (std::stoi(ans)) {
        case 1:
            RegistrateGuest(table);
            break;
        case 2:
            DeleteGuest(table, list);
            break;
        case 3:
            table.ShowTable();
            break;
        case 4:
            table.ClearTable();
            std::cout << "\nСписок постояльцев очищен!\n";
            break;
        case 5:
            FindByPassportNo(table, list);
            break;
        case 6:
            FindByFio(table);
            break;
        case 7:
            AddSuite(tree);
            break;
        case 8:
            DeleteSuite(tree, list);
            break;
        case 9:
        {
            std::shared_ptr<Node> rootNode = tree.GetRootNode();
            size_t countNodes = 0;
            tree.Print(rootNode, countNodes);
            break;
        }
        case 10:
        {
            tree.ClearTree();
            std::cout << "\nСписок гостиничных номеров очищен!\n";
            break;
        }
        case 11:
            FindBySuiteNo(table, tree, list);
            break;
        case 12:
            FindByFurnishing(tree);
            break;
        case 13:
            CheckIn(table, tree, list);
            break;
        case 14:
            CheckOut(table, tree, list);
            break;
        }

        if (std::stoi(ans)) {
            std::cout << "Нажмите любую клавишу, чтобы вернуться в главное меню: ";
            std::cin >> choice;
            std::cin.ignore(32256, '\n');
        }
        else
            break;
    }

    return 0;
}
