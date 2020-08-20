//
//  WrongData.cpp
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "WrongData.h"

const char* WrongGuestData::what() const noexcept
{
    const char* output;

    if (m_Error == GuestErrors::WRONG_PASSPORT)
        output = "Неверный формат паспортных данных постояльца. Повторите ввод:\n";
    else if (m_Error == GuestErrors::WRONG_FIO)
        output = "Неверный формат ФИО постояльца. Повторите ввод:\n";
    else if (m_Error == GuestErrors::WRONG_BIRTHYEAR)
        output = "Неверный формат года рождения постояльца. Повторите ввод:\n";
    else if (m_Error == GuestErrors::WRONG_ADDRESS)
        output = "Неверный формат адреса постояльца. Повторите ввод:\n";
    else
        output = "Неверный формат цели прибытия постояльца. Повторите ввод:\n";

    return output;
}

const char* WrongSuiteData::what() const noexcept
{
    const char* output;

    if (m_Error == SuiteErrors::WRONG_SUITENO)
        output = "Неверный формат номера гостиничного номера. Повторите ввод:\n";
    else if (m_Error == SuiteErrors::WRONG_BEDSAMOUNT)
        output = "Неверный формат количества мест в гостиничном номере. Повторите ввод:\n";
    else if (m_Error == SuiteErrors::WRONG_ROOMSAMOUNT)
        output = "Неверный формат количества комнат в гостиничном номере. Повторите ввод:\n";
    else if (m_Error == SuiteErrors::WRONG_BATHROOM)
        output = "Неверный формат наличия санузла в гостиничном номере. Повторите ввод:\n";
    else
        output = "Неверный формат оборудования в гостиничном номере. Повторите ввод:\n";

    return output;
}

const char* WrongRelationData::what() const noexcept
{
    const char* output;
    if (m_Error == RelationErrors::WRONG_CHECKINDATE)
        output = "Неверный формат даты вселения постояльца. Повторите ввод:\n";
    else
        output = "Неверный формат даты выселения постояльца. Повторите ввод:\n";

    return output;
}
