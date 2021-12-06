/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 5.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-05
 ***********************************************************************************/

#include "doctest.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <stdexcept>

#include "BinaryTree.hpp"

using namespace ariel;
using namespace std;

TEST_CASE("test foreach") {
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1)
                .add_left(1, 9) 
                .add_left(9, 4) 
                .add_right(9, 5)
                .add_right(1, 3)
                .add_left(1, 2));

    string s;
    for (auto e: tree) {
        s += to_string(e) + " " ;
    }
    CHECK(s == "4 2 5 1 3 ");

}

TEST_CASE("test tree of ints") {
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1)
                .add_left(1, 9) 
                .add_left(9, 4) 
                .add_right(9, 5)
                .add_right(1, 3)
                .add_left(1, 2));

    string s;
    for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
        CHECK_NOTHROW(s += to_string(*it) + " " );
    }
    CHECK(s == "1 2 4 5 3 ");
    s = "";
    for (auto it=tree.begin_inorder(); it!=tree.end_inorder(); ++it) {
        CHECK_NOTHROW(s += to_string(*it) + " " );
    }
    CHECK(s == "4 2 5 1 3 ");
    s = "";
    for (auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it) {
        CHECK_NOTHROW(s += to_string(*it) + " " );
    }
    CHECK(s == "4 5 2 3 1 ");
}

TEST_CASE("test tree of strings") {
    BinaryTree<string> tree;
    CHECK_NOTHROW(tree.add_root("1")
                .add_left("1", "9") 
                .add_left("9", "4") 
                .add_right("9", "5")
                .add_right("1", "3")
                .add_left("1", "2"));

    string s;
    for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
        CHECK_NOTHROW(s += (*it) + " ") ;
    }
    CHECK(s == "1 2 4 5 3 ");
    s = "";
    for (auto it=tree.begin_inorder(); it!=tree.end_inorder(); ++it) {
        CHECK_NOTHROW(s += (*it) + " ") ;
    }
    CHECK(s == "4 2 5 1 3 ");
    s = "";
    for (auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it) {
        CHECK_NOTHROW(s += (*it) + " ") ;
    }
    CHECK(s == "4 5 2 3 1 ");
}

TEST_CASE("Adding with no root") {
    BinaryTree<int> tree;
    CHECK_THROWS(tree.add_left(1,3));
}

TEST_CASE("Adding son to not exist parent") {
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_THROWS(tree.add_left(2,3));
    CHECK_THROWS(tree.add_right(2,3));
}