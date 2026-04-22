#pragma once
using namespace std;

struct rbt_node {
    rbt_node* parent = nullptr;
    rbt_node* right = nullptr;
    rbt_node* left = nullptr;
    int elem;
    bool isRed = true;
};