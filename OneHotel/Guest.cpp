//
//  Guest.cpp
//  OneHotel
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "Guest.h"

std::string fioAlphabet = " АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя-";
std::string destinationAlphabet = fioAlphabet + ",.()";
std::string addressAlphabet = destinationAlphabet + "0123456789";

Guest& Guest::operator= (const Guest& guest)
{
    m_PassportNo = guest.m_PassportNo;
    m_Fio = guest.m_Fio;
    m_BirthYear = guest.m_BirthYear;
    m_Address = guest.m_Address;
    m_ArrivalDestination = guest.m_ArrivalDestination;

    return *this;
}

bool Guest::IsEmpty()
{
    return m_PassportNo == ""
        && m_Fio == ""
        && m_BirthYear == 0
        && m_Address == ""
        && m_ArrivalDestination == ""
        ;
}

void Guest::Erase()
{
    m_PassportNo = "";
    m_Fio = "";
    m_BirthYear = 0;
    m_Address = "";
    m_ArrivalDestination = "";
}

const std::string& Guest::GetPassportNo()
{
    return m_PassportNo;
}

const std::string& Guest::GetFio()
{
    return m_Fio;
}

uint16_t Guest::GetBirthYear()
{
    return m_BirthYear;
}

const std::string& Guest::GetAddress()
{
    return m_Address;
}

const std::string& Guest::GetArrivalDestination()
{
    return m_ArrivalDestination;
}

const std::string EnterPassportNo()
{
    std::string passportNo;

    while (true) {
        try {
            std::cout << "\nВведите паспортные данные постояльца:\n";
            std::getline(std::cin, passportNo);

            if (passportNo.length() != 11)
                throw WrongGuestData(Errors::GuestErrors::WRONG_PASSPORT);

            for (auto i = 0; i < 4; ++i) {
                if (passportNo[i] < '0' || passportNo[i] > '9')
                    throw WrongGuestData(Errors::GuestErrors::WRONG_PASSPORT);
            }

            if (passportNo[4] != '-')
                throw WrongGuestData(Errors::GuestErrors::WRONG_PASSPORT);

            for (auto i = 5; i < 11; ++i) {
                if (passportNo[i] < '0' || passportNo[i] > '9')
                    throw WrongGuestData(Errors::GuestErrors::WRONG_PASSPORT);
            }
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return passportNo;
}

const std::string EnterFio()
{
    std::string fio;

    while (true) {
        try {
            std::cout << "\nВведите ФИО постояльца:\n";
            std::getline(std::cin, fio);

            if (fio == "")
                throw WrongGuestData(Errors::GuestErrors::WRONG_FIO);

            else if (fio.length() > 100)
                throw WrongGuestData(Errors::GuestErrors::WRONG_FIO);

            for (auto i = 0; i < fio.length(); i++) {
                for (auto j = 0; j < fioAlphabet.length(); j++) {
                    if (fio[i] == fioAlphabet[j])
                        break;
                    else if (j == fioAlphabet.length() - 1 && fio[i] != fioAlphabet[j])
                        throw WrongGuestData(Errors::GuestErrors::WRONG_FIO);
                }
            }
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return fio;
}

const uint16_t EnterBirthYear()
{
    std::string birthYear;

    while (true) {
        try {
            std::cout << "\nВведите год рождения постояльца:\n";
            std::getline(std::cin, birthYear);

            if (birthYear.length() != 4)
                throw WrongGuestData(Errors::GuestErrors::WRONG_BIRTHYEAR);

            for (auto i = 0; i < 4; i++) {
                if (birthYear[i] < '0' || birthYear[i] > '9')
                    throw WrongGuestData(Errors::GuestErrors::WRONG_BIRTHYEAR);
            }

            if (std::stoi(birthYear) < 1900 || std::stoi(birthYear) > 2020)
                throw WrongGuestData(Errors::GuestErrors::WRONG_BIRTHYEAR);

        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return std::stoi(birthYear);
}

const std::string EnterAddress()
{
    std::string address;

    while (true) {
        try {
            std::cout << "\nВведите адрес постояльца:\n";
            std::getline(std::cin, address);

            if (address == "" || address.length() > 200)
                throw WrongGuestData(Errors::GuestErrors::WRONG_ADDRESS);

            for (auto i = 0; i < address.length(); i++) {
                for (auto j = 0; j < addressAlphabet.length(); j++) {
                    if (address[i] == addressAlphabet[j])
                        break;
                    else if (j == addressAlphabet.length() - 1 && address[i] != addressAlphabet[j])
                        throw WrongGuestData(Errors::GuestErrors::WRONG_ADDRESS);
                }
            }
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return address;
}

const std::string EnterArrivalDestination()
{
    std::string arrivalDestination;

    while (true) {
        try {
            std::cout << "\nВведите цель прибытия постояльца:\n";
            std::getline(std::cin, arrivalDestination);

            if (arrivalDestination == "" || arrivalDestination.length() > 150)
                throw WrongGuestData(Errors::GuestErrors::WRONG_ARRIVALDESTINATION);

            for (auto i = 0; i < arrivalDestination.length(); i++) {
                for (auto j = 0; j < destinationAlphabet.length(); j++) {
                    if (arrivalDestination[i] == destinationAlphabet[j])
                        break;
                    else if (j == destinationAlphabet.length() - 1 && arrivalDestination[i] != destinationAlphabet[j])
                        throw WrongGuestData(Errors::GuestErrors::WRONG_ARRIVALDESTINATION);
                }
            }
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return arrivalDestination;
}
