#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <stdexcept>

namespace ariel {

    enum iterator_type { PREORDER, INORDER, POSTORDER };

    template<typename T> class BinaryTree {

        struct Node {
            T _key;                                                                                                                                                                                            //kepasion
            Node* _right, * _left;
            Node(T k) : _key(k), _right(nullptr), _left(nullptr) {}
            Node(const Node* o) : _key(0), _right(nullptr), _left(nullptr) {
                if (o) {
                    _key = o->_key;
                    if (o->_right) {
                        if (_right) { delete _right; }
                        _right = new Node(o->_right);
                    }
                    if (o->_left) {
                        if (_left) { delete _left; }
                        _left = new Node(o->_left);
                    }
                }
            }
        };

        class Iterator {

            /*_____*/  private: /*_____*/
            std::vector<Node*> _ordered;
            unsigned long _curr;
            void fill(iterator_type type, Node* n);

            /*_____*/  public: /*_____*/
            Iterator(iterator_type type, Node* n) : _curr(0) {
                fill(type, n);
                _ordered.push_back(nullptr);
            }
            Iterator& operator++() { _curr++; return *this; }
            Iterator operator++(int) { Iterator tmp = *this; _curr++; return tmp; }
            T& operator*() const { return _ordered.at(_curr)->_key; }
            T* operator->() const { return &_ordered.at(_curr)->_key; }
            bool operator==(Iterator const& o) const { return _ordered.at(_curr) == o._ordered.at(o._curr); }
            bool operator!=(Iterator const& o) const { return _ordered.at(_curr) != o._ordered.at(o._curr); }
        };

        Node* _root;


        public:
        /* Constructors: */
        BinaryTree() : _root(nullptr) {}
        BinaryTree(const BinaryTree& other) : _root(new Node(other._root)) {}

        /* Copy assignment operator: */
        BinaryTree& operator=(const BinaryTree& other) {
            if (this == &other) { return *this; }
            delete(this->_root);
            _root = new Node(other._root);
            return *this;
        }

        BinaryTree& operator=(BinaryTree&& other) noexcept {
            _root = other._root;
            other._root = nullptr;
            return *this;
        }

        BinaryTree(BinaryTree&& other) noexcept {
            _root = other._root;
            other._root = nullptr;
        }

        ~BinaryTree() { freeTree(_root); }
        void freeTree(Node* root) {
            if (root == nullptr) { return; }
            freeTree(root->_right);
            freeTree(root->_left);
            delete root;
        }
        BinaryTree& add_root(const T& r);
        BinaryTree& add_right(const T& n, const T& v);
        BinaryTree& add_left(const T& n, const T& v);
        auto begin_preorder() { return Iterator(PREORDER, _root); }
        auto end_preorder() { return Iterator(PREORDER, nullptr); }
        auto begin_inorder() { return Iterator(INORDER, _root); }
        auto end_inorder() { return Iterator(INORDER, nullptr); }
        auto begin_postorder() { return Iterator(POSTORDER, _root); }
        auto end_postorder() { return Iterator(POSTORDER, nullptr); }
        auto begin() { return begin_inorder(); }
        auto end() { return end_inorder(); }
        template<typename E> friend std::ostream& operator<<(std::ostream& out, BinaryTree<E> const& b);
        Node* get_node(Node* n, T key) {
            if (!n) { return nullptr; }
            if (n->_key == key) { return n; }
            Node* found = get_node(n->_left, key);
            if (found) { return found; }
            return get_node(n->_right, key);
        }
    };

    /* ====================================== IMPLEMENTATIONS ========================================== */

    template<typename T> std::ostream& operator<<(std::ostream& out, BinaryTree<T> const& b) {
        out << "this is a tree";
        return out;
    }

    template<typename T> BinaryTree<T>& BinaryTree<T>::add_root(const T& r) {
        if (_root) { _root->_key = r; }
        else { _root = new Node(r); };
        return *this;
    }

    template<typename T> BinaryTree<T>& BinaryTree<T>::add_right(const T& n, const T& v) {
        Node* f = get_node(_root, n);
        if (!f) { throw std::invalid_argument{ "n is not exist" }; }
        if (f->_right == nullptr) { f->_right = new Node(v); }
        else { f->_right->_key = v; }
        return *this;
    }

    template<typename T> BinaryTree<T>& BinaryTree<T>::add_left(const T& n, const T& v) {
        Node* f = get_node(_root, n);
        if (!f) { throw std::invalid_argument{ "n is not exist" }; }                                                                                                                              //kepasion
        if (f->_left == nullptr) { f->_left = new Node(v); }
        else { f->_left->_key = v; }
        return *this;
    }

    template<typename T> void BinaryTree<T>::Iterator::fill(iterator_type type, Node* n) {                                                                                                                               //kepasion
        if (!n) { return; }
        if (type == PREORDER) { _ordered.push_back(n); }
        fill(type, n->_left);
        if (type == INORDER) { _ordered.push_back(n); }
        fill(type, n->_right);
        if (type == POSTORDER) { _ordered.push_back(n); }
    }
};