//
//  Suite.cpp
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "Suite.h"

std::string furnishingAlphabet = " АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя-,.()";

Suite& Suite::operator= (const Suite& suite)
{
    m_SuiteNo = suite.m_SuiteNo;
    m_BedsAmount = suite.m_BedsAmount;
    m_RoomsAmount = suite.m_RoomsAmount;
    m_HasBathroom = suite.m_HasBathroom;
    m_Furnishing = suite.m_Furnishing;

    return *this;
}

bool Suite::IsEmpty()
{
    return m_SuiteNo == ""
        && m_BedsAmount == 0
        && m_RoomsAmount == 0
        && m_HasBathroom == false
        && m_Furnishing == "";
}

void Suite::Erase()
{
    m_SuiteNo = "";
    m_BedsAmount = 0;
    m_RoomsAmount = 0;
    m_HasBathroom = false;
    m_Furnishing = "";
}

const std::string& Suite::GetSuiteNo()
{
    return m_SuiteNo;
}

char Suite::GetBedsAmount()
{
    return m_BedsAmount;
}

char Suite::GetRoomsAmount()
{
    return m_RoomsAmount;
}

bool Suite::GetBathroom()
{
    return m_HasBathroom;
}

const std::string& Suite::GetFurnishing()
{
    return m_Furnishing;
}

const std::string EnterSuiteNo()
{
    std::string suiteNo;

    while (true) {
        try {
            std::cout << "\nВведите номер гостиничного номера:\n";
            std::getline(std::cin, suiteNo);

            if (suiteNo.length() != 4)
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_SUITENO);

            else if (suiteNo[0] != 'Л' && suiteNo[0] != 'П' && suiteNo[0] != 'О' && suiteNo[0] != 'М') {
                    throw WrongSuiteData(Errors::SuiteErrors::WRONG_SUITENO);
            }

            for (auto i = 1; i < 4; i++) {
                if (suiteNo[i] < '0' || suiteNo[i] > '9')
                    throw WrongSuiteData(Errors::SuiteErrors::WRONG_SUITENO);
            }
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return suiteNo;
}

char EnterBedsAmount()
{
    std::string bedsAmount;

    while (true) {
        try {
            std::cout << "\nВведите количество мест в гостиничном номере:\n";
            std::getline(std::cin, bedsAmount);

            if (bedsAmount.length() != 1)
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_BEDSAMOUNT);

            else if (bedsAmount.front() < '0' || bedsAmount.front() > '5')
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_BEDSAMOUNT);
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return std::stoi(bedsAmount);
}

char EnterRoomsAmount()
{
    std::string roomsAmount;

    while (true) {
        try {
            std::cout << "\nВведите количество комнат в гостиничном номере:\n";
            std::getline(std::cin, roomsAmount);

            if (roomsAmount.length() != 1)
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_ROOMSAMOUNT);

            else if (roomsAmount.front() < '0' || roomsAmount.front() > '5')
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_ROOMSAMOUNT);
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return std::stoi(roomsAmount);
}

bool EnterBathroom()
{
    std::string hasBathroom;

    while (true) {
        try {
            std::cout << "\nВведите 0, если в номере нет санузла, и 1 в противном случае:\n";
            std::getline(std::cin, hasBathroom);

            if (hasBathroom.length() != 1)
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_BATHROOM);

            else if (hasBathroom.front() != '0' && hasBathroom.front() != '1')
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_BATHROOM);
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return std::stoi(hasBathroom);
}

const std::string EnterFurnishing()
{
    std::string furnishing;

    while (true) {
        try {
            std::cout << "\nВведите оборудование в гостиничном номере:\n";
            std::getline(std::cin, furnishing);

            if (furnishing == "" || furnishing.length() > 250)
                throw WrongSuiteData(Errors::SuiteErrors::WRONG_FURNISHING);

            for (auto i = 0; i < furnishing.length(); i++) {
                for (auto j = 0; j < furnishingAlphabet.length(); j++) {
                    if (furnishing[i] == furnishingAlphabet[j])
                        break;
                    else if (j == furnishingAlphabet.length() - 1 && furnishing[i] != furnishingAlphabet[j])
                        throw WrongSuiteData(Errors::SuiteErrors::WRONG_FURNISHING);
                }
            }
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return furnishing;
}
