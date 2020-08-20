//
//  List.h
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef List_h
#define List_h

#include "Relation.h"
#include "Suite.h"

struct Element
{
    Relation relation;
    std::shared_ptr<Element> previous;
    std::shared_ptr<Element> next;

    Element()
        : relation()
        , previous(nullptr)
        , next(nullptr)
    {}

    Element(const Relation& relation, const std::shared_ptr<Element> previous, std::shared_ptr<Element> next)
        : relation(relation)
        , previous(previous)
        , next(next)
    {}
};

class List
{
public:
    List()
        : m_Size(0)
        , m_Head(nullptr)
    {}

    void AddElement(Relation&);
    void DeleteByPassport(const std::string&);
    void DeleteBySuite(const std::string&);
    bool CheckGuest(const std::string&);
    bool CheckSuite(Suite&);
    bool IsGuestInList(const std::string&);
    bool IsSuiteInList(const std::string&);
    void FindByPassportNo(const std::string&, std::string&);
    void FindBySuiteNo(const std::string&, std::list<std::string>&);
    friend int FindMedian(int, int, List&);
    friend void HoarSort(int, int, List&);

    size_t GetSize();
    std::shared_ptr<Element> operator[] (size_t);

private:
    size_t m_Size;
    std::shared_ptr<Element> m_Head;
};

int FindMedian(int, int, List&);
void HoarSort(int, int, List&);

#endif /* List_h */
