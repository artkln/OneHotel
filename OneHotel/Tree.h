//
//  Tree.h
//  OneHotel
//
//  Created by Артём Калинин on 21.08.2020.
//  Copyright © 2020 Артём Калинин. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include "suite.h"

struct Node
{
    Suite suite;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;

    Node()
        : suite()
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
    {}

    Node(const Suite& suite, const std::shared_ptr<Node> left, const std::shared_ptr<Node> right,
        const std::shared_ptr<Node> parent)
        : suite(suite)
        , left(left)
        , right(right)
        , parent(parent)
    {}
};

class Tree
{
public:
    Tree()
        : m_RootNode(nullptr)
    {}

    void BigLeftRotation(std::shared_ptr<Node>);
    void SmallLeftRotation(std::shared_ptr<Node>);
    void BigRightRotation(std::shared_ptr<Node>);
    void SmallRightRotation(std::shared_ptr<Node>);

    std::shared_ptr<Node> GetRootNode();

    int GetHeight(std::shared_ptr<Node>);
    int ComputeBalance(std::shared_ptr<Node>);
    void BalanceTree(std::shared_ptr<Node>);
    bool AddElement(Suite&);
    bool DeleteElement(const std::string&);
    void Print(std::shared_ptr<Node>, size_t&);
    void FindByNumber(const std::string&, Suite&);
    void FindByFurnishing(std::shared_ptr<Node>, const std::string&, std::list<Suite>&);
    void ClearTree();

private:
    std::shared_ptr<Node> m_RootNode;
};

#endif /* Tree_h */
