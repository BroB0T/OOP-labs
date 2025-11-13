#include <iostream>
using namespace std;

template <typename T>
int findElement(const T arr[], int size, const T& value)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

int main()
{
    try
    {
        cout << "Enter array size: ";
        int size;
        cin >> size;

        if (cin.fail() || size <= 0) throw runtime_error("expected integer value");

        int* array = new int[size];
        cout << "Enter " << size << " integer values:\n";
        for (int i = 0; i < size; i++)
        {
            cout << i+1 << ") ";
            cin >> array[i];
            cout << "\n";

            if (cin.fail() || size <= 0) throw runtime_error("expected integer value");
        }

        int value;
        cout << "Enter the search value: ";
        cin >> value;

        int index = findElement(array, size, value);

        if (index != -1)
        {
            cout << "Element " << value << " found at index " << index << endl;
        }
            
        else
        {
            cout << "Element not found\n";
        } 

        delete[] array;
        return 0;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}