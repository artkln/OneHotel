//
//  Suite.h
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef Suite_h
#define Suite_h

#include <iostream>
#include <string>
#include <list>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "wrongData.h"

class Suite
{
public:
    Suite()
        : m_SuiteNo("")
        , m_BedsAmount(0)
        , m_RoomsAmount(0)
        , m_HasBathroom(false)
        , m_Furnishing("")
    {}

    Suite(const std::string& suiteNo, const char bedsAmount,
        const char roomsAmount, const bool hasBathroom, const std::string& furnishing)
        : m_SuiteNo(suiteNo)
        , m_BedsAmount(bedsAmount)
        , m_RoomsAmount(roomsAmount)
        , m_HasBathroom(hasBathroom)
        , m_Furnishing(furnishing)
    {}

    Suite& operator= (const Suite&);

    bool IsEmpty();
    void Erase();

    const std::string& GetSuiteNo();
    char GetBedsAmount();
    char GetRoomsAmount();
    bool GetBathroom();
    const std::string& GetFurnishing();

private:
    std::string m_SuiteNo;
    char m_BedsAmount;
    char m_RoomsAmount;
    bool m_HasBathroom;
    std::string m_Furnishing;
};

const std::string EnterSuiteNo();
char EnterBedsAmount();
char EnterRoomsAmount();
bool EnterBathroom();
const std::string EnterFurnishing();

#endif /* Suite_h */
