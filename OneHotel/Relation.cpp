//
//  Relation.cpp
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "Relation.h"

std::list<std::string>& Relation::GetPassportList()
{
    return m_PassportList;
}

const std::string& Relation::GetSuiteNo()
{
    return m_SuiteNo;
}

const std::string& Relation::GetCheckInDate()
{
    return m_CheckInDate;
}

const std::string& Relation::GetCheckOutDate()
{
    return m_CheckOutDate;
}

const std::string EnterCheckInDate()
{
    std::string checkInDate;

    while (true) {
        try {
            std::cout << "\nВведите дату заселения постояльца:\n";
            std::getline(std::cin, checkInDate);

            if (checkInDate.length() != 10)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKINDATE);

            else if (checkInDate[0] < '0' || checkInDate[0] > '9' ||
                     checkInDate[1] < '0' || checkInDate[1] > '9' ||
                     checkInDate[3] < '0' || checkInDate[3] > '9' ||
                     checkInDate[4] < '0' || checkInDate[4] > '9' ||
                     checkInDate[6] < '0' || checkInDate[6] > '9' ||
                     checkInDate[7] < '0' || checkInDate[7] > '9' ||
                     checkInDate[8] < '0' || checkInDate[8] > '9' ||
                     checkInDate[9] < '0' || checkInDate[9] > '9')
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKINDATE);

            else if (checkInDate[2] != '.' || checkInDate[5] != '.')
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKINDATE);

            else if (std::stoi(checkInDate.substr(0, 2)) < 1 || std::stoi(checkInDate.substr(0, 2)) > 31)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKINDATE);

            else if (std::stoi(checkInDate.substr(3, 2)) < 1 || std::stoi(checkInDate.substr(3, 2)) > 12)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKINDATE);

            else if (std::stoi(checkInDate.substr(6, 4)) < 1900 || std::stoi(checkInDate.substr(6, 4)) > 2020)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKINDATE);
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return checkInDate;
}

const std::string EnterCheckOutDate()
{
    std::string checkOutDate;

    while (true) {
        try {
            std::cout << "\nВведите дату выселения постояльца:\n";
            std::getline(std::cin, checkOutDate);

            if (checkOutDate.length() != 10)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKOUTDATE);

            else if (checkOutDate[0] < '0' || checkOutDate[0] > '9' ||
                checkOutDate[1] < '0' || checkOutDate[1] > '9' ||
                checkOutDate[3] < '0' || checkOutDate[3] > '9' ||
                checkOutDate[4] < '0' || checkOutDate[4] > '9' ||
                checkOutDate[6] < '0' || checkOutDate[6] > '9' ||
                checkOutDate[7] < '0' || checkOutDate[7] > '9' ||
                checkOutDate[8] < '0' || checkOutDate[8] > '9' ||
                checkOutDate[9] < '0' || checkOutDate[9] > '9')
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKOUTDATE);

            else if (checkOutDate[2] != '.' || checkOutDate[5] != '.')
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKOUTDATE);

            else if (std::stoi(checkOutDate.substr(0, 2)) < 1 || std::stoi(checkOutDate.substr(0, 2)) > 31)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKOUTDATE);

            else if (std::stoi(checkOutDate.substr(3, 2)) < 1 || std::stoi(checkOutDate.substr(3, 2)) > 12)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKOUTDATE);

            else if (std::stoi(checkOutDate.substr(6, 4)) < 1900 || std::stoi(checkOutDate.substr(6, 4)) > 2020)
                throw WrongRelationData(Errors::RelationErrors::WRONG_CHECKOUTDATE);
        }
        catch (WrongData & wd) {
            std::cout << wd.what();
            continue;
        }

        break;
    }

    return checkOutDate;
}
