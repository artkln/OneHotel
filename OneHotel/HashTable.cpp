//
//  HashTable.cpp
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "HashTable.h"

HashTable::HashTable()
{
    m_Table.reserve(m_Size);

    for (auto i = 0; i < m_Size; i++) {
        m_Table.emplace_back();
    }
}

size_t HashTable::HashFunc(const std::string& key) const
{
    static int arr[7]{
            47777, 106783, 24121, 93529, 71963, 138239, 6637
    };
    size_t index = 0;
    size_t hash = 1;
    for (auto it = key.begin(); it != key.end(); ++it) {
        hash = hash * arr[index] + *it;
        index++;
        if (index == 7)
            index = 0;
    }
    return hash;
}

void HashTable::FindByPassportNo(const std::string& passportNo, Guest& foundGuest)
{
    Cell& hashCell = m_Table[HashFunc(passportNo) % m_Size];
    std::shared_ptr<Cell> currentCollision = hashCell.collision;

    if (hashCell.guest.IsEmpty())
        return;
    else if (hashCell.guest.GetPassportNo() == passportNo)
        foundGuest = hashCell.guest;
    else if (currentCollision) {
        while (currentCollision->guest.GetPassportNo() != passportNo && currentCollision->collision) {
            currentCollision = currentCollision->collision;
        }

        if (currentCollision->guest.GetPassportNo() == passportNo)
            foundGuest = currentCollision->guest;
    }
}

void HashTable::FindByFio(const std::string& fio, std::list<Guest>& foundGuests)
{
    std::shared_ptr<Cell> currentCollision;

    for (auto& currentCell : m_Table) {
        if (currentCell.guest.GetFio() == fio) {
            foundGuests.emplace_back(currentCell.guest);

            if (currentCell.collision) {
                currentCollision = currentCell.collision;
                while (currentCollision->guest.GetFio() != fio && currentCollision->collision) {
                    currentCollision = currentCollision->collision;
                }

                if (currentCollision->guest.GetFio() == fio)
                    foundGuests.emplace_back(currentCollision->guest);
            }
        }
        else if (currentCell.collision) {
            currentCollision = currentCell.collision;
            while (currentCollision->guest.GetFio() != fio && currentCollision->collision) {
                currentCollision = currentCollision->collision;
            }

            if (currentCollision->guest.GetFio() == fio)
                foundGuests.emplace_back(currentCollision->guest);
        }
    }
}

bool HashTable::AddElement(Guest& guestToAdd)
{
    Cell& hashCell = m_Table[HashFunc(guestToAdd.GetPassportNo()) % m_Size];
    std::shared_ptr<Cell> currentCollision = hashCell.collision;

    if (hashCell.guest.GetPassportNo() == guestToAdd.GetPassportNo())
        return false;
    else if (!hashCell.guest.IsEmpty() && hashCell.collision) {
        while (currentCollision->guest.GetPassportNo() != guestToAdd.GetPassportNo()
            && currentCollision->collision) {
            currentCollision = currentCollision->collision;
        }

        if (currentCollision->guest.GetPassportNo() == guestToAdd.GetPassportNo())
            return false;
    }

    if (hashCell.guest.IsEmpty())
        hashCell.guest = guestToAdd;
    else if (!hashCell.collision) {
        hashCell.collision = std::make_shared<Cell>(guestToAdd);
    }
    else
        currentCollision->collision = std::make_shared<Cell>(guestToAdd);

    return true;
}

bool HashTable::DeleteElement(const std::string& passportNo)
{
    Cell& hashCell = m_Table[HashFunc(passportNo) % m_Size];
    std::shared_ptr<Cell> currentCollision = hashCell.collision;

    if (hashCell.guest.IsEmpty())
        return false;
    else if (hashCell.guest.GetPassportNo() == passportNo) {
        if (!currentCollision) {
            hashCell.guest.Erase();
            return true;
        }
        else
        {
            hashCell.guest = currentCollision->guest;
            hashCell.collision = currentCollision->collision;
            currentCollision.reset();
            return true;
        }
    }
    else {
        while (currentCollision->guest.GetPassportNo() != passportNo && currentCollision->collision) {
            currentCollision = currentCollision->collision;
        }

        if (currentCollision->guest.GetPassportNo() == passportNo)
        {
            std::shared_ptr<Cell> previousCollision = hashCell.collision;
            if (previousCollision == currentCollision) {
                hashCell.collision = currentCollision->collision;
            }
            else {
                while (previousCollision->collision != currentCollision) {
                    previousCollision = previousCollision->collision;
                }
                previousCollision->collision = currentCollision->collision;
            }
            currentCollision.reset();
            return true;
        }
        else
            return false;
    }
}

void HashTable::ShowTable()
{
    for (auto i = 0; i < m_Size; i++) {
        if (!m_Table[i].guest.IsEmpty())
            break;
        else if (i == m_Size - 1 && m_Table[i].guest.IsEmpty()) {
            std::cout << "\nСписок постояльцев пуст!\n";
            return;
        }
        else
            continue;
    }

    size_t countHashCells = 0;
    size_t countCollisions = 0;
    std::shared_ptr<Cell> currentCollision;

    for (auto i = 0; i < m_Size; i++) {
        if (!m_Table[i].guest.IsEmpty()) {
            countHashCells++;
            std::cout << std::endl << countHashCells << '.' << " ФИО: " << m_Table[i].guest.GetFio() << std::endl;
            std::cout << "   Год рождения: " << m_Table[i].guest.GetBirthYear() << std::endl;
            std::cout << "   Паспортные данные: " << m_Table[i].guest.GetPassportNo() << std::endl;

            currentCollision = m_Table[i].collision;
            while (currentCollision) {
                countCollisions++;
                std::cout << std::endl << countHashCells << '.' << countCollisions << '.'
                    << " ФИО: " << currentCollision->guest.GetFio() << std::endl;
                std::cout << "   Год рождения: " << currentCollision->guest.GetBirthYear() << std::endl;
                std::cout << "   Паспортные данные: " << currentCollision->guest.GetPassportNo() << std::endl;
                currentCollision = currentCollision->collision;
            }
            countCollisions = 0;
        }
        else
            continue;
    }
}

void HashTable::ClearTable()
{
    for (auto& currentCell : m_Table) {
        if (!currentCell.guest.IsEmpty())
            currentCell.guest.Erase();

        if (currentCell.collision)
            currentCell.collision = nullptr;
    }
}
