//
//  Relation.h
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef Relation_h
#define Relation_h

#include <iostream>
#include "wrongData.h"
#include <string>
#include <list>

class Relation
{
public:
    Relation()
        : m_PassportList()
        , m_SuiteNo("")
        , m_CheckInDate("")
        , m_CheckOutDate("")
    {}

    Relation(const std::string& passportNo, const std::string& suiteNo,
        const std::string& checkInDate, const std::string& checkOutDate) {
        m_PassportList.emplace_back(passportNo);
        m_SuiteNo = suiteNo;
        m_CheckInDate = checkInDate;
        m_CheckOutDate = checkOutDate;
    }

    Relation(const Relation& relation)
        : m_PassportList(relation.m_PassportList)
        , m_SuiteNo(relation.m_SuiteNo)
        , m_CheckInDate(relation.m_CheckInDate)
        , m_CheckOutDate(relation.m_CheckOutDate)
    {}

    std::list<std::string>& GetPassportList();
    const std::string& GetSuiteNo();
    const std::string& GetCheckInDate();
    const std::string& GetCheckOutDate();

    friend bool operator== (const Relation&, const Relation&);
    friend bool operator!= (const Relation&, const Relation&);

private:
    std::list<std::string> m_PassportList;
    std::string m_SuiteNo;
    std::string m_CheckInDate;
    std::string m_CheckOutDate;
};

const std::string EnterCheckInDate();
const std::string EnterCheckOutDate();

#endif /* Relation_h */
