//
//  Guest.h
//  OneHotel
//
//  Created by Артём Калинин on 20.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef Guest_h
#define Guest_h

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "WrongData.h" 

class Guest
{
public:
    Guest()
        : m_PassportNo("")
        , m_Fio("")
        , m_BirthYear(0)
        , m_Address("")
        , m_ArrivalDestination("")
    {}

    Guest(const std::string& passportNo, const std::string& fio, const uint16_t birthYear,
        const std::string& address, const std::string& arrivalDestination)
        : m_PassportNo(passportNo)
        , m_Fio(fio)
        , m_BirthYear(birthYear)
        , m_Address(address)
        , m_ArrivalDestination(arrivalDestination)
    {}

    Guest& operator= (const Guest&);

    bool IsEmpty();
    void Erase();

    const std::string& GetPassportNo();
    const std::string& GetFio();
    uint16_t GetBirthYear();
    const std::string& GetAddress();
    const std::string& GetArrivalDestination();

private:
    std::string m_PassportNo;
    std::string m_Fio;
    uint16_t m_BirthYear;
    std::string m_Address;
    std::string m_ArrivalDestination;
};

const std::string EnterPassportNo();
const std::string EnterFio();
const uint16_t EnterBirthYear();
const std::string EnterAddress();
const std::string EnterArrivalDestination();

#endif /* Guest_h */
