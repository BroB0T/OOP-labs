#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

using namespace std;

class Rectangle
{
private:
    double a;
    double b;

public:
    Rectangle() : a(1), b(1) {}

    Rectangle(double a, double b)
    {
        setSides(a, b);
    }

    void setSides(double _a, double _b)
    {
        if (_a <= 0 || _b <= 0)
            throw invalid_argument("Sides of a rectangle must be positive!");
        a = _a;
        b = _b;
    }

    double getA() const { return a; }
    double getB() const { return b; }

    double getArea() const
    {
        return a * b;
    }

    double getPerimeter() const
    {
        return 2 * (a + b);
    }

    double getDiagonal() const
    {
        return sqrt(a * a + b * b);
    }

    Rectangle& operator++()
    {
        a++;
        b++;
        return *this;
    }

    Rectangle& operator--()
    {
        if (a - 1 <= 0 || b - 1 <= 0)
            throw out_of_range("Cannot decrease sides below or equal to zero!");
        a--;
        b--;
        return *this;
    }

    void printInfo() const
    {
        cout << fixed << setprecision(2);
        cout << "\tSide a: " << a << "\n";
        cout << "\tSide b: " << b << "\n";
        cout << "\tPerimeter: " << getPerimeter() << "\n";
        cout << "\tArea: " << getArea() << "\n";
        cout << "\tDiagonal: " << getDiagonal() << "\n";
    }
};

int main()
{
    Rectangle rect;
    int inputValue = 0;

    while (inputValue != 4)
    {
        cout << "\nEnter a choice:\n1 - Set rectangle sides\n2 - Increment sides\n3 - Decrement sides\n4 - Exit\n";

        cin >> inputValue;

        try
        {
            switch (inputValue)
            {
                case 1:
                {
                    double a, b;
                    cout << "Enter side a: ";
                    cin >> a;
                    cout << "Enter side b: ";
                    cin >> b;
                    rect.setSides(a, b);
                    rect.printInfo();
                    break;
                }
                case 2:
                {
                    ++rect;
                    cout << "Sides incremented\n";
                    rect.printInfo();
                    break;
                }
                case 3:
                {
                    --rect;
                    cout << "Sides decremented\n";
                    rect.printInfo();
                    break;
                }
                case 4:
                    cout << "Exiting program\n";
                    break;
                default:
                    cout << "Invalid choice. Try again\n";
            }
        }
        catch (const exception& ex)
        {
            cerr << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}

