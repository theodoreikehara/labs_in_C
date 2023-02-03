/****************************************************************************************
 *  Theodore Ikehara
 *  CruzID: tikehara
 *  2022 Spring CSE101 PA6
 *  BigInteger.cpp
 *
 *  About: This countains the BigInteger function definitions
 *****************************************************************************************/

#include "BigInteger.h"

#include <math.h>

using namespace std;

// sets the base
unsigned int power = 9;
long base = pow(10, power);

// constructors
//

BigInteger::BigInteger()
{
    signum = 0;
    return;
}

BigInteger::BigInteger(std::string s)
{

    if (s.empty()) {
        throw std::invalid_argument("BigInteger: constructor: empty string");
    }

    // creates the digits with the list
    ListElement x;
    string temp;
    int condition;

    // determines signum
    if (s[0] == '-') {
        signum = -1;
    } else {
        signum = 1;
    }

    // checks the condition
    if (s[0] != '+' && s[0] != '-') {
        condition = 0;
    } else {
        condition = 1;
    }

    // loads into the digits list
    for (int i = s.size() - 1; i >= condition; i--) {
        if (temp.length() == power) {
            x = stol(temp);
            digits.insertAfter(x);
            temp.clear();
            temp.insert(0, 1, s[i]);
        } else {
            temp.insert(0, 1, s[i]);
        }
    }

    // fixes
    x = stol(temp);
    digits.insertBefore(x);
    digits.moveFront();

    while (true) {
        if ((digits.front() != 0) || (digits.peekNext() != 0)) {
            break;
        } else {
            digits.eraseAfter();
        }
    }

    if (digits.front() == 0) {
        digits.moveFront();
        digits.eraseAfter();
    }

    return;
}

// creates a copy of N
BigInteger::BigInteger(const BigInteger &N)
{
    signum = N.signum;
    digits = N.digits;
}

// access functions below
//

// returns the sign of the num
int BigInteger::sign() const
{
    return signum;
}

// compares the big ints
// returns -1 if A > B
// returns 1 if A < B
// returns 0 if A = B
int BigInteger::compare(const BigInteger &N) const
{

    BigInteger A = *this;
    BigInteger B = N;

    string Astr = A.BigInteger::to_string();
    string Bstr = B.BigInteger::to_string();

    if (Astr.compare(Bstr) > 0) {
        return 1;
    }

    if (Astr.compare(Bstr) < 0) {
        return -1;
    }

    return 0;
}

// Manipulation functions
//

// reset function
void BigInteger::makeZero()
{
    digits.clear();
    signum = 0;
}

// negate function reverses signum
void BigInteger::negate()
{

    if (signum == 1) {
        signum = -1;
    } else if (signum == -1) {
        signum = 1;
    }

    return;
}

// returns a string representation of the bigint
std::string BigInteger::to_string()
{

    string str;
    string temp;

    ListElement x;

    // this determines the sign
    if (signum == 0) {
        return "0";
    }
    if (signum == -1) {
        str += "-";
    }

    // this creates the string
    digits.moveFront();
    x = digits.moveNext();
    str += std::to_string(x);

    while (digits.position() < digits.length()) {
        x = digits.moveNext();
        temp = std::to_string(x);

        while (temp.size() < power) {
            temp.insert(0, 1, '0');
        }

        str += temp;
        temp.clear();
    }

    return str;
}

// this sum the list helps with the other functions
void sumList(List &L, List A, List B, int s)
{
    ListElement x;
    List temp;

    A.moveBack();
    B.moveBack();

    while ((A.position() > 0) || (B.position() > 0)) {
        if ((B.position() == 0) && (A.position() != 0)) {
            x = A.movePrev();
        } else if ((B.position() != 0) && (A.position() == 0)) {
            x = B.movePrev() * s;
        } else {
            x = A.movePrev() + (B.movePrev() * s);
        }

        temp.insertAfter(x);
    }

    while (true) {
        if ((temp.front() == 0) && (temp.peekNext() == 0)) {
            temp.eraseAfter();
        } else {
            break;
        }
    }

    if (temp.front() == 0) {
        temp.moveFront();
        temp.eraseAfter();
    }

    L = temp;
}

// negates the entire list
void negateList(List &L)
{
    List temp;
    L.moveBack();
    while (L.position() > 0) {
        temp.insertAfter(L.movePrev() * -1);
    }
    L = temp;
}

// carry count function helps with the normalize list function
ListElement carry_Count(ListElement x)
{
    ListElement c = x / base;
    if (x % base == 0) {
        return c;
    } else if (x % base != 0 && c > 0) {
        return c;
    } else if (x % base != 0 && c < 0) {
        return (c - 1);
    } else if (x % base == x && x > 0) {
        return 1;
    } else if (x % base == x && x < 0) {
        return -1;
    } else {
        return c;
    }
}
// nomalizes the list
int normalizeList(List &L)
{
    ListElement x;
    List temp;
    int sign = 0;
    int c = 0;
    bool carry = false;
    bool borrow = false;

    if (L.front() > 0) {
        sign = 1;
    } else {
        sign = -1;
        negateList(L);
    }

    L.moveBack();
    while (L.position() > 0) {
        x = L.movePrev();

        if (x >= base && carry == true) {
            x += c;
            c = carry_Count(x);
            x -= ((c) * (base));
            temp.insertAfter(x);
            carry = true;
        } else if (x >= base && carry == false) {
            c = carry_Count(x);
            x -= ((c) * (base));
            temp.insertAfter(x);
            carry = true;
        } else if (x < base && x >= 0 && carry == true) {
            x += c;
            if (x >= base) {
                c = carry_Count(x);
                x -= ((c) * (base));
                temp.insertAfter(x);
                carry = true;
            } else if (x < 0) {
                c = carry_Count(x);
                x += ((c * -1) * (base));
                temp.insertAfter(x);
                carry = true;
            } else {
                c = 0;
                temp.insertAfter(x);
                carry = false;
            }
        }

        else if (x < 0 && borrow == true) {
            x += c;
            c = carry_Count(x);
            x += ((c * -1) * (base));
            temp.insertAfter(x);
            borrow = true;
        } else if (x < 0 && borrow == false) {
            c = carry_Count(x);
            x += ((c * -1) * (base));
            temp.insertAfter(x);
            borrow = true;
        } else if (x >= 0 && x < base && borrow == true) {
            x += c;
            if (x < 0) {
                c = carry_Count(x);
                x += ((c * -1) * (base));
                temp.insertAfter(x);
                borrow = true;
            } else if (x >= base) {
                c = carry_Count(x);
                x -= ((c) * (base));
                temp.insertAfter(x);
                borrow = true;
            } else {
                c = 0;
                temp.insertAfter(x);
                borrow = false;
            }
        } else {
            temp.insertAfter(x);
            carry = false;
            borrow = false;
            c = 0;
        }
    }
    while (true) {
        if (temp.front() == 0 && temp.peekNext() == 0) {
            temp.eraseAfter();
        } else {
            break;
        }
    }
    if (temp.front() == 0) {
        temp.moveFront();
        temp.eraseAfter();
    }
    if ((carry == true || borrow == true) && c != 0) {
        temp.insertAfter(c);
    }
    L = temp;
    return sign;
}

BigInteger BigInteger::add(const BigInteger &N) const
{

    BigInteger temp;
    if (this->sign() == 0 && N.sign() != 0) {
        temp.signum = N.sign();
        temp.digits = N.digits;
    } else if (this->sign() != 0 && N.sign() == 0) {
        temp.signum = this->sign();
        temp.digits = this->digits;
    } else if (this->sign() == -1 && N.sign() == 1) {
        if (this->digits == N.digits) {
            temp.signum = 0;
        } else {
            sumList(temp.digits, N.digits, this->digits, -1);
            temp.signum = normalizeList(temp.digits);
        }
    } else if (this->sign() == -1 && N.sign() == 1) {
        if (this->digits == N.digits) {
            temp.signum = 0;
        } else {
            sumList(temp.digits, N.digits, this->digits, -1);
            temp.signum = normalizeList(temp.digits);
        }
    } else if (this->sign() == 1 && N.sign() == -1) {
        if (this->digits == N.digits) {
            temp.signum = 0;
        } else {
            sumList(temp.digits, this->digits, N.digits, -1);
            temp.signum = normalizeList(temp.digits);
        }
    } else if (this->sign() == 0 && N.sign() == 0) {
        temp.signum = 0;
    } else if ((this->sign() == -1 && N.sign() == -1)) {
        sumList(temp.digits, this->digits, N.digits, 1);
        normalizeList(temp.digits);
        temp.signum = -1;
    } else {
        sumList(temp.digits, this->digits, N.digits, 1);
        temp.signum = normalizeList(temp.digits);
    }
    return temp;
}

BigInteger BigInteger::sub(const BigInteger &N) const
{
    BigInteger temp;
    if (this->sign() == 0 && N.sign() != 0) {
        temp.signum = -1;
        temp.digits = N.digits;
    } else if (this->sign() != 0 && N.sign() == 0) {
        temp.signum = this->sign();
        temp.digits = this->digits;
    } else if (this->sign() == 0 && N.sign() == 0) {
        temp.signum = 0;
    } else if (this->sign() == -1 && N.sign() == 1) {
        sumList(temp.digits, this->digits, N.digits, 1);
        normalizeList(temp.digits);
        temp.signum = -1;
    } else if (this->sign() == 1 && N.sign() == -1) {
        sumList(temp.digits, this->digits, N.digits, 1);
        normalizeList(temp.digits);
        temp.signum = 1;
    } else if (this->sign() == -1 && N.sign() == -1) {
        if (this->digits == N.digits) {
            temp.signum = 0;
        } else {
            sumList(temp.digits, this->digits, N.digits, -1);
            temp.signum = normalizeList(temp.digits) * -1;
        }
    } else {
        if (this->digits == N.digits) {
            temp.signum = 0;
        } else if (this->digits.length() > N.digits.length()) {
            sumList(temp.digits, this->digits, N.digits, -1);
            normalizeList(temp.digits);
            temp.signum = 1;
        } else if (this->digits.length() < N.digits.length()) {
            sumList(temp.digits, N.digits, this->digits, -1);
            normalizeList(temp.digits);
            temp.signum = -1;
        } else if (this->digits.length() == N.digits.length() &&
                   this->digits.front() > N.digits.front()) {
            sumList(temp.digits, N.digits, this->digits, -1);
            normalizeList(temp.digits);
            temp.signum = 1;
        } else if (this->digits.length() == N.digits.length() &&
                   this->digits.front() < N.digits.front()) {
            sumList(temp.digits, N.digits, this->digits, -1);
            normalizeList(temp.digits);
            temp.signum = -1;
        } else {
            sumList(temp.digits, this->digits, N.digits, -1);
            temp.signum = normalizeList(temp.digits);
        }
    }
    return temp;
}
void scalarMultList(List &L, ListElement x)
{
    List temp;
    ListElement y;
    L.moveBack();
    while (L.position() > 0) {
        y = x * L.movePrev();
        temp.insertAfter(y);
    }
    L = temp;
}
List multHelper(List A, List B)
{
    List temp = A;
    List product;
    int shift = 0;
    B.moveBack();
    while (B.position() > 0) {
        scalarMultList(temp, B.movePrev());
        int c = 0;
        temp.moveBack();
        while (c < shift) {
            temp.insertAfter(0);
            c++;
        }
        shift++;
        sumList(product, product, temp, 1);
        normalizeList(product);
        temp = A;
    }
    return product;
}
BigInteger BigInteger::mult(const BigInteger &N) const
{
    BigInteger temp;
    if ((this->sign() == 0 && N.sign() != 0) ||
        (this->sign() != 0 && N.sign() == 0) ||
        (this->signum == 0 && N.sign() == 0)) {
        temp.signum = 0;
    } else if ((this->signum == 1 && N.sign() == -1) ||
               (this->signum == -1 && N.sign() == 1)) {
        temp.signum = -1;
        if (this->digits.length() > N.digits.length()) {
            temp.digits = multHelper(this->digits, N.digits);
        } else if (this->digits.length() < N.digits.length()) {
            temp.digits = multHelper(N.digits, this->digits);
        } else {
            temp.digits = multHelper(this->digits, N.digits);
        }
    } else {
        temp.signum = 1;
        if (this->digits.length() > N.digits.length()) {
            temp.digits = multHelper(this->digits, N.digits);
        } else if (this->digits.length() < N.digits.length()) {
            temp.digits = multHelper(N.digits, this->digits);
        } else if (this->digits.length() == N.digits.length() &&
                   this->digits.front() < N.digits.front()) {
            temp.digits = multHelper(N.digits, this->digits);
        } else {
            temp.digits = multHelper(this->digits, N.digits);
        }
    }
    return temp;
}

std::ostream &operator<<(std::ostream &stream, BigInteger N)
{
    return stream << N.BigInteger::to_string();
}

bool operator==(const BigInteger &A, const BigInteger &B)
{
    if (A.compare(B) == 0) {
        return true;
    } else {
        return false;
    }
}

bool operator<(const BigInteger &A, const BigInteger &B)
{
    if (A.compare(B) == -1) {
        return true;
    } else {
        return false;
    }
}

bool operator<=(const BigInteger &A, const BigInteger &B)
{
    if (A.compare(B) == -1 || A.compare(B) == 0) {
        return true;
    } else {
        return 0;
    }
}

bool operator>(const BigInteger &A, const BigInteger &B)
{
    if (A.compare(B) == 1) {
        return true;
    } else {
        return false;
    }
}

bool operator>=(const BigInteger &A, const BigInteger &B)
{
    if (A.compare(B) == 1 && A.compare(B) == 0) {
        return true;
    } else {
        return false;
    }
}

BigInteger operator+(const BigInteger &A, const BigInteger &B)
{
    BigInteger c = A.add(B);
    return c;
}

BigInteger operator+=(BigInteger &A, const BigInteger &B)
{
    BigInteger c = A.add(B);
    A.signum = c.signum;
    A.digits = c.digits;
    return A;
}

BigInteger operator-(const BigInteger &A, const BigInteger &B)
{
    BigInteger c = A.sub(B);
    return c;
}
BigInteger operator-=(BigInteger &A, const BigInteger &B)
{
    BigInteger c = A.sub(B);
    A.signum = c.signum;
    A.digits = c.digits;
    return A;
}

BigInteger operator*(const BigInteger &A, const BigInteger &B)
{
    BigInteger c = A.mult(B);
    return c;
}
BigInteger operator*=(BigInteger &A, const BigInteger &B)
{
    BigInteger c = A.mult(B);
    A.signum = c.signum;
    A.digits = c.digits;
    return A;
}

