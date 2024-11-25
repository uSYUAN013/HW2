#include <iostream>
#include <cmath> 
using namespace std;


class Polynomial;


class Term {
public:
    float coef;
    int exp;
};


class Polynomial {
public:

    Polynomial() : termArray(NULL), capacity(0), terms(0) {}


    Polynomial Add(const Polynomial& poly);


    Polynomial Mult(const Polynomial& poly);


    float Eval(float f) const;


    friend istream& operator>>(istream& is, Polynomial& poly);


    friend ostream& operator<<(ostream& os, const Polynomial& poly);

private:
    Term* termArray;
    int capacity;
    int terms;


    void AddTerm(float coef, int exp);
};


void Polynomial::AddTerm(float coef, int exp) {
    if (coef == 0) return;


    if (terms >= capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Term* newArray = new Term[newCapacity];

        for (int i = 0; i < terms; i++) {
            newArray[i] = termArray[i];
        }

        delete[] termArray;
        termArray = newArray;
        capacity = newCapacity;
    }


    termArray[terms].coef = coef;
    termArray[terms].exp = exp;
    terms++;
}


istream& operator>>(istream& is, Polynomial& poly) {
    cout << "Enter number of terms: ";
    is >> poly.terms;

    poly.capacity = poly.terms;
    poly.termArray = new Term[poly.capacity];

    for (int i = 0; i < poly.terms; i++) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        is >> poly.termArray[i].coef >> poly.termArray[i].exp;
    }

    return is;
}


ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        if (i > 0 && poly.termArray[i].coef > 0)
            os << " + ";
        os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return os;
}


Polynomial Polynomial::Add(const Polynomial& poly) {
    Polynomial result;
    int i = 0, j = 0;

    while (i < terms && j < poly.terms) {
        if (termArray[i].exp == poly.termArray[j].exp) {
            result.AddTerm(termArray[i].coef + poly.termArray[j].coef, termArray[i].exp);
            i++; j++;
        }
        else if (termArray[i].exp > poly.termArray[j].exp) {
            result.AddTerm(termArray[i].coef, termArray[i].exp);
            i++;
        }
        else {
            result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
    }


    while (i < terms) {
        result.AddTerm(termArray[i].coef, termArray[i].exp);
        i++;
    }
    while (j < poly.terms) {
        result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
        j++;
    }

    return result;
}


Polynomial Polynomial::Mult(const Polynomial& poly) {
    Polynomial result;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float newCoef = termArray[i].coef * poly.termArray[j].coef;
            int newExp = termArray[i].exp + poly.termArray[j].exp;
            result.AddTerm(newCoef, newExp);
        }
    }

    return result;
}

float Polynomial::Eval(float f) const {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return result;
}

int main() {
    Polynomial p1, p2;

    cout << "Enter polynomial p1:" << endl;
    cin >> p1;

    cout << "Enter polynomial p2:" << endl;
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;

    float x;
    cout << "Enter a value to evaluate p1: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}
