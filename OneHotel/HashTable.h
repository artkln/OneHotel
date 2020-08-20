//
//  HashTable.h
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include "guest.h"

struct Cell
{
    Guest guest;
    std::shared_ptr<Cell> collision;

    Cell()
        : guest()
        , collision(nullptr)
    {}

    Cell(const Cell& cell)
        : guest(cell.guest)
        , collision(cell.collision)
    {}

    Cell(const Guest& guest)
        : guest(guest)
        , collision(nullptr)
    {}
};

class HashTable
{
public:
    HashTable();
    size_t HashFunc(const std::string&) const;
    bool AddElement(Guest&);
    bool DeleteElement(const std::string&);
    void FindByPassportNo(const std::string&, Guest&);
    void FindByFio(const std::string&, std::list<Guest>&);
    void ShowTable();
    void ClearTable();

private:
    std::vector<Cell> m_Table;
    const size_t m_Size = 5;
};

#endif /* HashTable_h */
