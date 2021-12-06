#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
using namespace std;

// #include "BinaryTree.hpp"
// using namespace ariel;

struct Node {
    int key;                                                                                                                                                                                            //kepasion
    Node *right, *left;
    Node(int k) : key(k), right(nullptr), left(nullptr){}
    Node() : key(0), right(nullptr), left(nullptr){
        *this = *(new Node(0));
    }
    friend ostream& operator<<(ostream& out, const Node &n) {
        out << n.key << " eyal";
        return out;
    }
};

int main() {
    // Node<int> n1{1};
    // Node<int> n2{2};
    // Node<int> n3{3};
    // Node<int> n4{4};
    // // cout << n1 << " " << n2 << endl; 
    // // cout << n3 << " " << n4 << endl;
    // n1.left = &n2;
    // cout << n1.key << " " << *(n1.left) << endl;

    // BinaryTree<int> tree;
    // tree.add_root(1);
    // tree.add_right(1, 9);
    map<int, Node*> m;
    m[3];
    cout << m[3];
    cout << typeid(m[3]).name() << endl;
    m.at(3)->left = m[4];
    // for(auto& e: m) {
    //     cout << e.first << " " << e.second->key << endl;
    // }
}