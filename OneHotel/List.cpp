//
//  List.cpp
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "List.h"

size_t List::GetSize()
{
    return m_Size;
}

std::shared_ptr<Element> List::operator[] (size_t index)
{
    std::shared_ptr<Element> currentElement = m_Head;

    if (!index)
        return m_Head;
    else {
        while (index) {
            currentElement = currentElement->next;
            index--;
        }

        return currentElement;
    }
}

void List::AddElement(Relation& relationToAdd)
{
    if (!m_Head)
        m_Head = std::make_shared<Element>(relationToAdd, nullptr, nullptr);
    else {
        std::shared_ptr<Element> currentElement = m_Head;

        while (currentElement) {
            if (currentElement->relation.GetSuiteNo() == relationToAdd.GetSuiteNo()) {
                std::string passportToAdd = relationToAdd.GetPassportList().front();
                std::list<std::string>& currentList = currentElement->relation.GetPassportList();

                currentList.emplace_back(passportToAdd);
                return;
            }
            else if (!currentElement->next)
                break;
            else
                currentElement = currentElement->next;
        }

        currentElement->next = std::make_shared<Element>(relationToAdd, currentElement, nullptr);
    }

    m_Size++;
}

bool List::IsGuestInList(const std::string& passportNo)
{
    std::shared_ptr<Element> currentElement = m_Head;

    while (currentElement) {
        std::list<std::string>& currentList = currentElement->relation.GetPassportList();

        for (auto it = currentList.begin(); it != currentList.end(); ++it) {
            if (passportNo == *it)
                return true;
        }

        currentElement = currentElement->next;
    }

    return false;
}

bool List::IsSuiteInList(const std::string& suiteNo)
{
    std::shared_ptr<Element> currentElement = m_Head;

    while (currentElement) {
        if (currentElement->relation.GetSuiteNo() == suiteNo)
            return true;
        else
            currentElement = currentElement->next;
    }

    return false;
}

void List::FindByPassportNo(const std::string& passportNo, std::string& foundSuiteNo)
{
    std::shared_ptr<Element> currentElement = m_Head;

    while (currentElement) {
        std::list<std::string>& currentList = currentElement->relation.GetPassportList();

        for (auto it = currentList.begin(); it != currentList.end(); ++it) {
            if (passportNo == *it) {
                foundSuiteNo = currentElement->relation.GetSuiteNo();
                return;
            }
        }

        currentElement = currentElement->next;
    }
}

void List::FindBySuiteNo(const std::string& suiteNo, std::list<std::string>& foundPassportNo)
{
    std::shared_ptr<Element> currentElement = m_Head;

    while (currentElement) {
        if (currentElement->relation.GetSuiteNo() == suiteNo) {
            foundPassportNo = currentElement->relation.GetPassportList();
            return;
        }
        else
            currentElement = currentElement->next;
    }
}

void List::DeleteByPassport(const std::string& passportNo)
{
    std::shared_ptr<Element> currentElement = m_Head;

    while (currentElement) {
        std::list<std::string>& currentList = currentElement->relation.GetPassportList();

        for (auto it = currentList.begin(); it != currentList.end(); ++it) {
            if (passportNo == *it) {
                currentList.erase(it);
                break;
            }
        }

        if (currentList.empty()) {
            if (currentElement == m_Head) {
                std::shared_ptr<Element> elementToDelete = m_Head;
                m_Head = m_Head->next;
                elementToDelete.reset();
            }
            else if (currentElement->next) {
                currentElement->previous->next = currentElement->next;
                currentElement->next->previous = currentElement->previous;
                currentElement.reset();
            }
            else
                currentElement.reset();

            m_Size--;
            return;
        }

        currentElement = currentElement->next;
    }
}

void List::DeleteBySuite(const std::string& suiteNo)
{
    std::shared_ptr<Element> currentElement = m_Head;

    while (currentElement) {
        if (currentElement->relation.GetSuiteNo() == suiteNo) {
            if (currentElement == m_Head) {
                std::shared_ptr<Element> elementToDelete = m_Head;
                m_Head = m_Head->next;
                elementToDelete.reset();
            }
            else if (currentElement->next) {
                currentElement->previous->next = currentElement->next;
                currentElement->next->previous = currentElement->previous;
                currentElement.reset();
            }
            else
                currentElement.reset();

            return;
        }
        else
            currentElement = currentElement->next;
    }

    m_Size--;
}

bool List::CheckGuest(const std::string& passportNo)
{
    std::shared_ptr<Element> currentElement = m_Head;
    std::list<std::string> currentList;

    while (currentElement) {
        currentList = currentElement->relation.GetPassportList();

        for (auto it = currentList.begin(); it != currentList.end(); ++it) {
            if (passportNo == *it)
                return true;
        }
        currentElement = currentElement->next;
    }

    return false;
}

bool List::CheckSuite(Suite& suiteToCheck)
{
    std::shared_ptr<Element> currentElement = m_Head;
    std::list<std::string> currentList;

    while (currentElement) {
        currentList = currentElement->relation.GetPassportList();

        if (currentElement->relation.GetSuiteNo() == suiteToCheck.GetSuiteNo()) {
            if (suiteToCheck.GetBedsAmount() > currentList.size())
                return true;
            else
                return false;
        }
        else
            currentElement = currentElement->next;
    }

    return true;
}

int FindMedian(int L, int R, List& list)
{
    int i = -1;
    std::shared_ptr<Element> Left = list[L];
    std::shared_ptr<Element> Right = list[R];
    std::shared_ptr<Element> Median = list[(L + R) / 2];

    if (Left->relation.GetSuiteNo() == Median->relation.GetSuiteNo()
        && Median->relation.GetSuiteNo() == Right->relation.GetSuiteNo()) {
        i = L;

        while (list[i]->relation.GetSuiteNo() == Median->relation.GetSuiteNo() && i < R) {
            i += 1;
        }

        if (list[i]->relation.GetSuiteNo() != Median->relation.GetSuiteNo())
            Median = list[i];
    }

    if (Left->relation.GetSuiteNo() == Median->relation.GetSuiteNo()
        && Median->relation.GetSuiteNo() == Right->relation.GetSuiteNo())
        return -1;
    else {
        if (Left->relation.GetSuiteNo() <= Median->relation.GetSuiteNo()) {
            if (Median->relation.GetSuiteNo() <= Right->relation.GetSuiteNo()) {
                if (i == -1)
                    return (L + R) / 2;
                else
                    return i;
            }
            else {
                if (Left->relation.GetSuiteNo() <= Right->relation.GetSuiteNo())
                    return R;
                else
                    return L;
            }
        }
        else {
            if (Left->relation.GetSuiteNo() >= Right->relation.GetSuiteNo()) {
                if (Median->relation.GetSuiteNo() >= Right->relation.GetSuiteNo()) {
                    if (i == -1)
                        return (L + R) / 2;
                    else
                        return i;
                }
                else
                    return R;
            }
            else
                return L;
        }
    }
}


void HoarSort(int L, int R, List& list)
{
    int MedIndex;
    std::shared_ptr<Element> MedItem;

    MedIndex = FindMedian(L, R, list);

    if (MedIndex != -1) {
        MedItem = list[MedIndex];
        int i = L, j = R;

        while (i <= j) {
            while (list[i]->relation.GetSuiteNo() < MedItem->relation.GetSuiteNo()) {
                i += 1;
            }

            while (list[j]->relation.GetSuiteNo() > MedItem->relation.GetSuiteNo()) {
                j -= 1;
            }

            if (i <= j) {
                Relation temp = list[i]->relation;
                list[i]->relation = list[j]->relation;
                list[j]->relation = temp;

                i += 1;
                j -= 1;
            }
        }

        if (L < j) HoarSort(L, j, list);
        if (i < R) HoarSort(i, R, list);
    }
}
