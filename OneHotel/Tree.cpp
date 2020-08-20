//
//  Tree.cpp
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#include "Tree.h"

std::shared_ptr<Node> Tree::GetRootNode()
{
    return m_RootNode;
}

void Tree::BigLeftRotation(std::shared_ptr<Node> a)
{
    std::shared_ptr<Node> b = a->right;
    std::shared_ptr<Node> c = b->left;
    Suite suite_a = a->suite, suite_c = c->suite;

    a->suite = suite_c;
    c->suite = suite_a;

    b->left = c->right;
    if (b->left)
        b->left->parent = b;
    c->right = c->left;
    c->left = a->left;
    if (c->left)
        c->left->parent = c;
    a->left = c;
    if (a->left)
        a->left->parent = a;
}

void Tree::SmallLeftRotation(std::shared_ptr<Node> a)
{
    std::shared_ptr<Node> b = a->right;
    Suite suite_a = a->suite, suite_b = b->suite;

    a->suite = suite_b;
    b->suite = suite_a;

    a->right = b->right;
    if (a->right)
        a->right->parent = a;
    b->right = b->left;
    b->left = a->left;
    if (b->left)
        b->left->parent = b;
    a->left = b;
    if (a->left)
        a->left->parent = a;
}

void Tree::BigRightRotation(std::shared_ptr<Node> a)
{
    std::shared_ptr<Node> b = a->left;
    std::shared_ptr<Node> c = b->right;
    Suite suite_a = a->suite, suite_c = c->suite;

    a->suite = suite_c;
    c->suite = suite_a;

    b->right = c->left;
    if (b->right)
        b->right->parent = b;
    c->left = c->right;
    c->right = a->right;
    if (c->right)
        c->right->parent = c;
    a->right = c;
    if (a->right)
        a->right->parent = a;
}

void Tree::SmallRightRotation(std::shared_ptr<Node> a)
{
    std::shared_ptr<Node> b = a->left;
    Suite suite_a = a->suite, suite_b = b->suite;

    a->suite = suite_b;
    b->suite = suite_a;

    a->left = b->left;
    if (a->left)
        a->left->parent = a;
    b->left = b->right;
    b->right = a->right;
    if (b->right)
        b->right->parent = b;
    a->right = b;
    if (a->right)
        a->right->parent = a;
}

int Tree::GetHeight(std::shared_ptr<Node> node)
{
    int left, right;

    if (node->left)
        left = GetHeight(node->left);
    else left = -1;

    if (node->right)
        right = GetHeight(node->right);
    else right = -1;

    int max = left > right ? left : right;

    return max + 1;
}

int Tree::ComputeBalance(std::shared_ptr<Node> node)
{
    if (!node->left && node->right)
        return GetHeight(node);
    else if (!node->right && node->left)
        return -GetHeight(node);
    else if (node->left && node->right)
        return GetHeight(node->right) - GetHeight(node->left);
    else
        return 0;
}

void Tree::BalanceTree(std::shared_ptr<Node> newNode)
{
    std::shared_ptr<Node> currentNode = newNode;

    while (currentNode) {
        if (ComputeBalance(currentNode) == 2) {
            if (ComputeBalance(currentNode->right) == -1)
                BigLeftRotation(currentNode);
            else
                SmallLeftRotation(currentNode);
        }
        else if (ComputeBalance(currentNode) == -2) {
            if (ComputeBalance(currentNode->left) == 1)
                BigRightRotation(currentNode);
            else
                SmallRightRotation(currentNode);
        }
        currentNode = currentNode->parent;
    }
}

bool Tree::AddElement(Suite& suiteToAdd)
{
    if (!m_RootNode) {
        m_RootNode = std::make_shared<Node>();
        m_RootNode->suite = suiteToAdd;
        return true;
    }
    else {
        std::shared_ptr<Node> currentNode = m_RootNode;

        while ((suiteToAdd.GetSuiteNo() > currentNode->suite.GetSuiteNo() && currentNode->right) ||
            (suiteToAdd.GetSuiteNo() < currentNode->suite.GetSuiteNo() && currentNode->left)) {
            if (suiteToAdd.GetSuiteNo() > currentNode->suite.GetSuiteNo())
                currentNode = currentNode->right;
            else
                currentNode = currentNode->left;
        }

        if (suiteToAdd.GetSuiteNo() == currentNode->suite.GetSuiteNo())
            return false;
        else {
            std::shared_ptr<Node> newNode = std::make_shared<Node>(suiteToAdd, nullptr, nullptr, currentNode);

            if (suiteToAdd.GetSuiteNo() > currentNode->suite.GetSuiteNo()) {
                if (currentNode->right) {
                    newNode->right = currentNode->right;
                    currentNode->right->parent = newNode;
                }
                currentNode->right = newNode;
            }
            else {
                if (currentNode->left) {
                    newNode->left = currentNode->left;
                    currentNode->left->parent = newNode;
                }
                currentNode->left = newNode;
            }

            BalanceTree(newNode);

            return true;
        }
    }
}

bool Tree::DeleteElement(const std::string& suiteNo)
{
    char direction = ' ';
    std::shared_ptr<Node> currentNode = m_RootNode;
    std::shared_ptr<Node> previousNode(nullptr);

    if (!m_RootNode)
        return false;

    while ((suiteNo > currentNode->suite.GetSuiteNo() && currentNode->right) ||
        (suiteNo < currentNode->suite.GetSuiteNo() && currentNode->left)) {
        previousNode = currentNode;

        if (suiteNo > currentNode->suite.GetSuiteNo()) {
            currentNode = currentNode->right;
            direction = 'R';
        }
        else {
            currentNode = currentNode->left;
            direction = 'L';
        }
    }

    if (suiteNo != currentNode->suite.GetSuiteNo())
        return false;
    else {
        if (currentNode->left && currentNode->right) {
            previousNode = currentNode;

            std::shared_ptr<Node> nodeToDelete = currentNode->right;

            while (nodeToDelete->left) {
                previousNode = nodeToDelete;
                nodeToDelete = nodeToDelete->left;
            }

            currentNode->suite = nodeToDelete->suite;

            if (previousNode != currentNode) {
                previousNode->left = nodeToDelete->right;

                if (previousNode->left)
                    previousNode->left->parent = previousNode;
            }
            else {
                previousNode->right = nodeToDelete->right;
                if (previousNode->right)
                    previousNode->right->parent = previousNode;
            }

            nodeToDelete.reset();
            BalanceTree(previousNode);
            return true;
        }
        else if (!currentNode->left && currentNode->right) {
            if (previousNode) {
                if (direction == 'L') {
                    previousNode->left = currentNode->right;
                    if (previousNode->left)
                        previousNode->left->parent = previousNode;
                }
                else {
                    previousNode->right = currentNode->right;
                    if (previousNode->right)
                        previousNode->right->parent = previousNode;
                }

                currentNode.reset();
                BalanceTree(previousNode);
                return true;
            }
            else {
                std::shared_ptr<Node> nodeToDelete = m_RootNode;
                m_RootNode = currentNode->right;
                m_RootNode->parent = nullptr;
                nodeToDelete.reset();
                return true;
            }
        }
        else if (currentNode->left && !currentNode->right) {
            if (previousNode) {
                if (direction == 'L') {
                    previousNode->left = currentNode->left;
                    if (previousNode->left)
                        previousNode->left->parent = previousNode;
                }
                else {
                    previousNode->right = currentNode->left;
                    if (previousNode->right)
                        previousNode->right->parent = previousNode;
                }

                currentNode.reset();
                BalanceTree(previousNode);
                return true;
            }
            else {
                std::shared_ptr<Node> nodeToDelete = m_RootNode;
                m_RootNode = currentNode->left;
                m_RootNode->parent = nullptr;
                nodeToDelete.reset();
                return true;
            }
        }
        else {
            if (previousNode) {
                if (direction == 'L')
                    previousNode->left = nullptr;
                else
                    previousNode->right = nullptr;

                currentNode.reset();
                BalanceTree(previousNode);
                return true;
            }
            else {
                m_RootNode.reset();
                return true;
            }
        }
    }
}

void Tree::Print(std::shared_ptr<Node> currentNode, size_t& countNodes)
{
    if (!m_RootNode) {
        std::cout << "\nСписок гостиничных номеров пуст!\n";
        return;
    }
    else if (currentNode) {
        Print(currentNode->left, countNodes);
        countNodes++;
        std::cout << std::endl << countNodes << '.' << " Номер: " << currentNode->suite.GetSuiteNo() << std::endl
            << "   Количество мест: " << std::to_string(currentNode->suite.GetBedsAmount()) << std::endl
            << "   Количество комнат: " << std::to_string(currentNode->suite.GetRoomsAmount()) << std::endl
            << "   Оборудование: " << currentNode->suite.GetFurnishing() << std::endl;
        Print(currentNode->right, countNodes);
    }
}

void Tree::FindByNumber(const std::string& suiteNo, Suite& foundSuite)
{
    if (!m_RootNode)
        return;
    else {
        std::shared_ptr<Node> currentNode = m_RootNode;

        while ((suiteNo > currentNode->suite.GetSuiteNo() && currentNode->right) ||
            (suiteNo < currentNode->suite.GetSuiteNo() && currentNode->left)) {
            if (suiteNo > currentNode->suite.GetSuiteNo())
                currentNode = currentNode->right;
            else
                currentNode = currentNode->left;
        }

        if (suiteNo != currentNode->suite.GetSuiteNo())
            return;
        else
            foundSuite = currentNode->suite;
    }
}

void Tree::FindByFurnishing(std::shared_ptr<Node> currentNode,
    const std::string& substr, std::list<Suite>& foundSuites)
{
    if (!currentNode)
        return;
    else
    {
        int full_ind = substr.length() - 1, i, ind;
        while (full_ind < currentNode->suite.GetFurnishing().length()) {
            i = substr.length() - 1;
            ind = full_ind;
            while (i >= 0) {
                if (substr[i] == currentNode->suite.GetFurnishing()[ind]) {
                    i--;
                    ind--;
                }
                else break;
            }
            if (i < 0) {
                foundSuites.emplace_back(currentNode->suite);
                break;
            }
            else
                full_ind++;
        }
    }

    FindByFurnishing(currentNode->left, substr, foundSuites);
    FindByFurnishing(currentNode->right, substr, foundSuites);
}

void Tree::ClearTree()
{
    if (!m_RootNode)
        return;
    else
        m_RootNode.reset();
}
