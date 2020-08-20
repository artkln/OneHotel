//
//  WrongData.h
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef WrongData_h
#define WrongData_h

#include <iostream>

namespace Errors
{
    enum class GuestErrors {
        WRONG_PASSPORT,
        WRONG_FIO,
        WRONG_BIRTHYEAR,
        WRONG_ADDRESS,
        WRONG_ARRIVALDESTINATION
    };

    enum class SuiteErrors {
        WRONG_SUITENO,
        WRONG_BEDSAMOUNT,
        WRONG_ROOMSAMOUNT,
        WRONG_BATHROOM,
        WRONG_FURNISHING
    };

    enum class RelationErrors {
        WRONG_CHECKINDATE,
        WRONG_CHECKOUTDATE
    };
}


using namespace Errors;


class WrongData : public std::exception { };


class WrongGuestData final : public WrongData
{
public:
    WrongGuestData(GuestErrors error) : m_Error(error) { }
    const char* what() const noexcept override;

private:
    GuestErrors m_Error;
};

class WrongSuiteData : public WrongData
{
public:
    WrongSuiteData(SuiteErrors error) : m_Error(error) { }
    const char* what() const noexcept override;

private:
    SuiteErrors m_Error;
};

class WrongRelationData final : public WrongData
{
public:
    WrongRelationData(RelationErrors error) : m_Error(error) { }
    const char* what() const noexcept override final;
private:
    RelationErrors m_Error;
};

#endif /* WrongData_h */
