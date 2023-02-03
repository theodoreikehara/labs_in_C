/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA7
 *  Dictionary.cpp
 *
 *  About: contains all the function definitions
 *****************************************************************************************/

#include "Dictionary.h"

void clear();

// Node constructor
Dictionary::Node::Node(keyType k, valType v)
{
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Dictionary constructor
Dictionary::Dictionary()
{
    nil = nullptr;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D)
{
    nil = nullptr;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, root);
}
Dictionary::~Dictionary()
{
    clear();
}

// Helper Functions
//
// appends the string representation using in order tree traversal
void Dictionary::inOrderString(std::string &s, Node *R) const
{
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right);
    }
    return;
}

// appends the string representation using pre order tree traversal
void Dictionary::preOrderString(std::string &s, Node *R) const
{
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
    return;
}

// inserts copy
void Dictionary::preOrderCopy(Node *R, Node *N)
{
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
    return;
}

void Dictionary::postOrderDelete(Node *R)
{
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        num_pairs--;
        delete (R);
    }
    return;
}

// dictionary search
Dictionary::Node *Dictionary::search(Node *R, keyType k) const
{
    if (R == nil || k == R->key) {
        return R;
    } else if (k < R->key) {
        return search(R->left, k);
    }
    return search(R->right, k);
}

// find min in dictionary
Dictionary::Node *Dictionary::findMin(Node *R)
{
    if (size() > 0) {
        while (R->left != nil) {
            R = R->left;
        }
        return R;
    }
    return nil;
}

// find max in dictionay
Dictionary::Node *Dictionary::findMax(Node *R)
{

    if (size() > 0) {
        while (R->right != nil) {
            R = R->right;
        }
        return R;
    }
    return nil;
}

// find next in dictionary
Dictionary::Node *Dictionary::findNext(Node *N)
{
    // N is current
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node *y = N->parent;
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

// find prev in dictionary
Dictionary::Node *Dictionary::findPrev(Node *N)
{
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node *y = N->parent;
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}

// transplant in dictionary
void Dictionary::transplant(Node *&R, Node *&V)
{
    if (R->parent == nil) {
        root = V;
    } else if (R == R->parent->left) {
        R->parent->left = V;
    } else {
        R->parent->right = V;
    }
    if (V != nil) {
        V->parent = R->parent;
    }
}

// access functions
//

// gets the size
int Dictionary::size() const
{
    return num_pairs;
}

// checks if dictionary contains something
bool Dictionary::contains(keyType k) const
{
    Node *N = search(root, k);
    if (N == nil) {
        return false;
    }
    return true;
}

// gets the value given key of the dictionary
valType &Dictionary::getValue(keyType k) const
{

    bool exist = contains(k);

    if (exist == 1) {
        Node *N = search(root, k);
        return N->val;
    }

    throw std::logic_error("Error in get value");
}

// has a curent iterator defined
bool Dictionary::hasCurrent() const
{
    if (current == nil) {
        return false;
    }
    return true;
}

// returns the current key
keyType Dictionary::currentKey() const
{
    if (current == nil) {
        throw std::logic_error("Error in current key");
    }

    return current->key;
}

// returns the current val
valType &Dictionary::currentVal() const
{
    if (current == nil) {
        throw std::logic_error("Error in current val");
    }

    return current->val;
}

// manipulation functions
//

// clears the dictionary
void Dictionary::clear()
{
    postOrderDelete(root);
    current = nil;
    root = nil;
    return;
}

// sets the vale at the key with val
void Dictionary::setValue(keyType k, valType v)
{
    Node *y = nil;
    Node *n = new Node(k, v);
    Node *x = root;

    while (x != nil) {
        y = x;
        if (n->key == x->key) {
            x->val = n->val;
            delete n;
            return;
        } else if (n->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    if (y == nil) {
        root = n;
        num_pairs++;
        return;
    } else if (n->key < y->key) {
        y->left = n;
        n->parent = y;
        num_pairs++;
        return;
    }

    y->right = n;
    n->parent = y;
    num_pairs++;
    return;
}

// remove from dictionary
void Dictionary::remove(keyType k)
{
    Node *N = search(root, k);

    if (N->left == nil) {
        transplant(N, N->right);
    } else if (N->right == nil) {
        transplant(N, N->left);
    } else {
        Node *y = findMin(N->right);
        if (y->parent != N) {
            transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
    }

    if (current == N) {
        current = nil;
    }
    num_pairs--;
    delete (N);
}

// begin function
void Dictionary::begin()
{
    if (num_pairs == 0) {
        throw std::logic_error("Error in begin");
    }

    if (root->left == nil) {
        current = root;
        return;
    }

    current = findMin(root->left);
    return;
}

// end function
void Dictionary::end()
{
    if (num_pairs == 0) {
        throw std::logic_error("Error in end");
    }

    if (root->right == nil) {
        current = root;
        return;
    }

    current = findMax(root->right);
    return;
}

// next function
void Dictionary::next()
{
    if (hasCurrent() == false) {
        throw std::logic_error("Error in next");
    }

    current = findNext(current);
    return;
}

// prev function
void Dictionary::prev()
{
    if (hasCurrent() == false) {
        throw std::logic_error("Error in prev");
    }

    current = findPrev(current);
    return;
}

// to string function
std::string Dictionary::to_string() const
{
    std::string s;
    inOrderString(s, root);
    return s;
}

// pre string
std::string Dictionary::pre_string() const
{
    std::string s;
    preOrderString(s, root);
    return s;
}

// equals function
bool Dictionary::equals(const Dictionary &D) const
{

    std::string s1 = pre_string();
    std::string s2 = D.pre_string();

    if (s1 == s2) {
        return true;
    }

    return false;
}

// overloaded operators
std::ostream &operator<<(std::ostream &stream, Dictionary &D)
{
    return stream << D.Dictionary::to_string();
}

bool operator==(const Dictionary &A, const Dictionary &B)
{
    return A.Dictionary::equals(B);
}

Dictionary &Dictionary::operator=(const Dictionary &D)
{
    if (this != &D) {
        Dictionary temp = D;
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
        std::swap(nil, temp.nil);
    }
    return *this;
}

