/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA5
 *  List.cpp
 *
 *  About: This countains the list ADT with private type node list for the cpp
 *  project assignment 5
 *****************************************************************************************/

#include "List.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// tested for functionality
List::Node::Node(ListElement x)
{
    // this keeps track of the next and previous nodes
    // default to null pointer
    next = nullptr;
    prev = nullptr;

    // this is the data that is stored in the node
    data = x;

    return;
}

// tested for functionalit
List::List()
{

    // setting and creating the list obj
    frontDummy = new Node(-9999);
    backDummy = new Node(9999);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = nullptr;
    afterCursor = nullptr;

    pos_cursor = 0;
    num_elements = 0;

    return;
}

// tested for functionality
List::List(const List &L)
{

    // initializing the vars inside the list
    frontDummy = new Node(-9999);
    backDummy = new Node(9999);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = nullptr;
    afterCursor = nullptr;

    pos_cursor = 0;
    num_elements = 0;

    Node *n = L.frontDummy->next;
    if (L.num_elements != 0) {
        while (n->next != nullptr) {
            insertBefore(n->data);
            n = n->next;
        }
    }

    return;
}

// tested for functionality
List::~List()
{

    Node *n;
    Node *prev;

    if (num_elements > 0) {

        n = frontDummy;

        while (n) {
            prev = n;
            n = n->next;
            delete (prev);
        }
    }
    return;
}

// tested for functionality
// these are the get functions
int List::length() const
{
    return num_elements;
}

ListElement List::front() const
{
    return frontDummy->next->data;
}

ListElement List::back() const
{
    return backDummy->prev->data;
}

int List::position() const
{
    return pos_cursor;
}

ListElement List::peekNext() const
{
    if (pos_cursor < num_elements) {
        return afterCursor->data;
    }
    // cout << "range error in peekNext" << endl;
    exit(1);
}

ListElement List::peekPrev() const
{
    if (pos_cursor > 0) {
        return beforeCursor->data;
    }
    // cout << "range error in peekPrev" << endl;
    exit(1);
}

// starting the manipulation functions
// tested for functionality
void List::clear()
{

    Node *n = frontDummy->next;
    Node *prev;

    while (n != backDummy) {
        prev = n;
        n = n->next;
        delete (prev);
    }

    num_elements = 0;
    pos_cursor = 0;

    return;
}

// tested for functionality
void List::moveFront()
{
    // moves the front node
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;

    return;
}

void List::moveBack()
{
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;

    return;
}
// moves tested
ListElement List::moveNext()
{
    if (pos_cursor < length()) {
        int x = beforeCursor->next->data;

        beforeCursor = beforeCursor->next;
        afterCursor = afterCursor->next;

        pos_cursor += 1;
        return x;
    }

    // cout << "length error in moveNext" << endl;
    exit(1);
}

ListElement List::movePrev()
{
    if (pos_cursor > 0) {
        int x = afterCursor->prev->data;

        beforeCursor = beforeCursor->prev;
        afterCursor = afterCursor->prev;

        pos_cursor -= 1;
        return x;
    }

    // cout << "length error in movePrev" << endl;
    exit(1);
}

// tested
void List::insertAfter(ListElement x)
{
    Node *n = new Node(x);
    if (length() < 1) {

        frontDummy->next = n;
        n->prev = frontDummy;

        n->next = backDummy;
        backDummy->prev = n;

        beforeCursor = frontDummy;
        afterCursor = n;

    } else if ((length() >= 1) && (backDummy == afterCursor)) {

        afterCursor->prev = n;
        n->next = afterCursor;

        beforeCursor->next = n;
        n->prev = beforeCursor;

        afterCursor = n;

    } else {

        afterCursor->prev = n;
        n->next = afterCursor;

        beforeCursor->next = n;
        n->prev = beforeCursor;

        afterCursor = n;
    }

    num_elements += 1;
    return;
}

// tested
void List::insertBefore(ListElement x)
{
    Node *n = new Node(x);

    if (length() < 1) {

        frontDummy->next = n;
        n->prev = frontDummy;

        backDummy->prev = n;
        n->next = backDummy;

        afterCursor = backDummy;
        beforeCursor = n;

    } else if ((length() >= 1) && (beforeCursor == frontDummy)) {

        beforeCursor->next = n;
        beforeCursor->next->prev = beforeCursor;

        n->next = afterCursor;

        afterCursor->prev = n;
        beforeCursor = n;

    } else {

        beforeCursor->next = n;
        beforeCursor->next->prev = beforeCursor;
        n->next = afterCursor;
        afterCursor->prev = n;
        beforeCursor = n;
    }

    num_elements += 1;
    pos_cursor += 1;
    return;
}

// tested
void List::setAfter(ListElement x)
{
    if (pos_cursor < length()) {
        afterCursor->data = x;
        return;
    }

    // cout << "length error in setAfter" << endl;
    exit(1);
}
// tested
void List::setBefore(ListElement x)
{
    if (pos_cursor > 0) {
        beforeCursor->data = x;
        return;
    }

    // cout << "size error in setBefore" << endl;
    exit(1);
}

// tested
void List::eraseAfter()
{

    if (pos_cursor < length()) {

        Node *temp;

        temp = afterCursor;

        afterCursor->next->prev = afterCursor->prev;
        afterCursor->prev->next = afterCursor->next;

        afterCursor = afterCursor->next;

        num_elements -= 1;

        delete (temp);
        return;
    }
    // delete (temp);
    // cout << "length error in eraseAfter" << endl;
    exit(1);
}

// this is also bugged
void List::eraseBefore()
{

    if (pos_cursor > 0) {
        Node *temp;
        temp = beforeCursor;

        beforeCursor->prev->next = beforeCursor->next;
        beforeCursor->next->prev = beforeCursor->prev;

        beforeCursor = beforeCursor->prev;

        pos_cursor -= 1;
        num_elements -= 1;

        delete (temp);
        return;

    } else {
        // delete (temp);
        // cout << "length error in eraseBefore" << endl;
        exit(1);
    }
}

// other functions start here
// tested
int List::findNext(ListElement x)
{

    while (pos_cursor < num_elements) {
        if (moveNext() == x) {
            return position();
        }
    }
    moveBack();
    return -1;
}
// tested
int List::findPrev(ListElement x)
{
    while (position() > 0) {
        if (movePrev() == x) {
            return position();
        }
    }
    moveFront();
    return -1;
}

void List::cleanup()
{

    Node *n = frontDummy;
    Node *iterate;
    Node *node;
    int temp = 2;

    for (int i = 0; i < length(); i++) {
        n = n->next;
        iterate = n->next;
        while ((iterate->next != nullptr) && (iterate != backDummy)) {
            if (iterate == backDummy) {
                break;
            }
            if (iterate->data == n->data) {
                node = iterate;

                iterate->next->prev = iterate->prev;
                iterate->prev->next = iterate->next;

                iterate = iterate->next;

                num_elements -= 1;
                delete (node);

                if (temp < pos_cursor) {
                    pos_cursor -= 1;
                }
            } else {
                iterate = iterate->next;
            }
        }
    }

    return;
}
// tested
List List::concat(const List &L) const
{

    List list;

    Node *n = frontDummy;
    Node *listNode = L.frontDummy;

    n = n->next;
    listNode = listNode->next;

    while (n->next != nullptr) {
        list.insertBefore(n->data);
        n = n->next;
    }
    while (listNode->next != nullptr) {
        list.insertBefore(listNode->data);
        listNode = listNode->next;
    }

    list.moveFront();
    list.pos_cursor = 0;

    return list;
}
// tested
std::string List::to_string() const
{
    Node *n = nullptr;
    std::string s = "(";
    int l = 0;

    for (n = frontDummy->next; n->next != nullptr; n = n->next) {
        s += std::to_string(n->data);

        if (l < length() - 1) {
            s += ", ";
            l += 1;
        }
    }
    s += ")";
    return s;
}

bool List::equals(const List &L) const
{
    Node *n = nullptr;
    Node *m = nullptr;
    bool eq = false;

    eq = (num_elements == L.num_elements);
    n = this->frontDummy;
    m = L.frontDummy;

    while (eq && (n != nullptr)) {
        eq = (n->data == m->data);
        n = n->next;
        m = m->next;
    }

    return eq;
}

// Overriden Operators
std::ostream &operator<<(std::ostream &stream, const List &L)
{
    return stream << L.List::to_string();
}

bool operator==(const List &A, const List &B)
{
    return A.List::equals(B);
}

List &List::operator=(const List &L)
{
    if (this != &L) {
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);

        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);

        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}
