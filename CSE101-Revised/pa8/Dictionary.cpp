/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA8
 *  Dictionary.cpp
 *
 *  About: contains all the function definitions using red and black
 *****************************************************************************************/

#include "Dictionary.h"

// red is 0
// black is 1
// undef is -1

// Node constructor
Dictionary::Node::Node(keyType k, valType v)
{
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = -1;
}

// Dictionary constructor
Dictionary::Dictionary()
{
    nil = new Node("/1000", -10000);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D)
{
    nil = new Node("/1000", -10000);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}
Dictionary::~Dictionary()
{
    clear();
    root = nullptr;
    current = nullptr;
    delete nil;
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

// RBT Helper Functions (Optional) -----------------------------------------
//

// left rotate function for rbt using given psudo code
void Dictionary::LeftRotate(Node *N)
{

    // N is x as given in the psudo code
    Node *y = N->right;
    N->right = y->left;

    if (y->left != nil) {
        y->left->parent = N;
    }

    y->parent = N->parent;

    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }

    y->left = N;
    N->parent = y;

    return;
}

// right rotate function for rbt using given psudo code
void Dictionary::RightRotate(Node *N)
{
    // N is the x in the psuodo code
    Node *y = N->left;

    N->left = y->right;

    if (y->right != nil) {
        y->right->parent = N;
    }

    y->parent = N->parent;

    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->right) {
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }

    y->right = N;
    N->parent = y;

    return;
}

// red is 0
// black is 1
void Dictionary::RB_InsertFixUp(Node *N)
{

    // N is Z given in psudo code

    // using the red black code above and using the rb insert fix psudo code
    Node *y;
    int red = 0;
    int black = 1;

    while (N->parent->color == red) {
        if (N->parent == N->parent->parent->left) {

            y = N->parent->parent->right;

            if (y->color == red && y != nil) {
                N->parent->color = black;       // case 1
                y->color = black;               // case 1
                N->parent->parent->color = red; // case 1
                N = N->parent->parent;          // case 1
            } else {
                if (N == N->parent->right) {
                    N = N->parent; // case 2
                    LeftRotate(N); // case 2
                }
                N->parent->color = black;       // case 3
                N->parent->parent->color = red; // case 3
                RightRotate(N->parent->parent); // case 3
            }
        } else {

            y = N->parent->parent->left;

            if (y->color == red && y != nil) {
                N->parent->color = black;       // case 4
                y->color = black;               // case 4
                N->parent->parent->color = red; // case 4
                N = N->parent->parent;          // case 4
            } else {
                if (N == N->parent->left) {
                    N = N->parent;  // case 5
                    RightRotate(N); // case 5
                }
                N->parent->color = black;       // case 6
                N->parent->parent->color = red; // case 6
                LeftRotate(N->parent->parent);  // case 6
            }
        }
    }
    root->color = black;
    return;
}

// Transplant using psudo code provided
void Dictionary::RB_Transplant(Node *U, Node *V)
{
    if (U->parent == nil) {
        root = V;
    } else if (U == U->parent->left) {
        U->parent->left = V;
    } else {
        U->parent->right = V;
    }

    V->parent = U->parent;
}

// Delete fixup using given psudo code
void Dictionary::RB_DeleteFixUp(Node *N)
{

    // N is x in the psudo code
    int red = 0;
    int black = 1;

    Node *W;

    while (N != root && N->color == black) {
        if (N == N->parent->right) {
            W = N->parent->right;

            if (W->color == red) {
                W->color = black;       // case 1
                N->parent->color = red; // case 1
                LeftRotate(N->parent);  // case 1
                W = N->parent->right;   // case 1
            }
            if (W->left->color == black && W->right->color == black) {
                W->color = red; // case 2
                N = N->parent;  // case 2
            } else {
                if (W->right->color == black) {
                    W->left->color = black; // case 3
                    W->color = red;         // case 3
                    RightRotate(N);         // case 3
                    W = N->parent->right;   // case 3
                }

                W->color = N->parent->color; // case 4
                N->parent->color = black;    // case 4
                W->right->color = black;     // case 4
                LeftRotate(N->parent);       // case 4
                N = root;                    // case 4
            }
        } else {
            W = N->parent->left;

            if (W->color == red) {
                W->color = black;       // case 5
                N->parent->color = red; // case 5
                RightRotate(N->parent); // case 5
                W = N->parent->left;    // case 5
            }
            if (W->right->color == black && W->left->color == black) {
                W->color = red; // case 6
                N = N->parent;  // case 6
            } else {
                if (W->left->color == black) {
                    W->right->color = black; // case 7
                    W->color = red;          // case 7
                    LeftRotate(W);           // case 7
                    W = N->parent->left;     // case 7
                }
                W->color = N->parent->color; // case 8
                N->parent->color = black;    // case 8
                W->left->color = black;      // case 8
                RightRotate(N->parent);      // case 8
                N = root;                    // case 8
            }
        }
    }
    N->color = black;
}

// RB delete using the given psudo code
void Dictionary::RB_Delete(Node *N)
{

    // N is z in the psudo code
    int black = 1;

    Node *y = N;
    Node *x;

    int y_original_color = y->color;

    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == N) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }

        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == black) {
        RB_DeleteFixUp(x);
    }
    return;
}

// Access functions --------------------------------------------------------
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

    if (contains(k)) {
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
    if (hasCurrent()) {
        return current->key;
    }

    throw std::logic_error("Error in current key");
}

// returns the current val
valType &Dictionary::currentVal() const
{
    if (hasCurrent()) {
        return current->val;
    }
    throw std::logic_error("Error in current val");
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
        if (k == x->key) {
            x->val = v;
            return;
        } else if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    n->parent = y;
    if (y == nil) {
        root = n;
    } else if (k < y->key) {
        y->left = n;
    } else {
        y->right = n;
    }

    n->right = nil;
    n->left = nil;
    // 0 for red
    n->color = 0;
    num_pairs++;
    RB_InsertFixUp(n);
    return;
}

// remove from dictionary
void Dictionary::remove(keyType k)
{
    if (contains(k)) {
        Node *n = search(root, k);
        if (current == n) {
            current = nil;
        }
        RB_Delete(n);
        delete n;
        num_pairs--;
        return;
    }
    throw std::logic_error("Error in remove\n");
}

// begin function
void Dictionary::begin()
{
    if (size() == 0) {
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

