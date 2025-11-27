#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main() 
{
    int rows = 0;
    int cols = 0;
    bool containsZero = false;

    srand(time(0));

    cout << "Enter the number of rows: ";
    if (!(cin >> rows) || rows <= 0)
    {
        cout << "Invalid input for number of rows.\n";
        return 1;
    }

    cout << "Enter the number of columns: ";
    if (!(cin >> cols) || cols <= 0)
    {
        cout << "Invalid input for number of columns.\n";
        return 1;
    }

    vector<vector<int>> matrix(rows, vector<int>(cols));

    for_each(matrix.begin(), matrix.end(), [&](vector<int>& row)
    {
        generate(row.begin(), row.end(), [&]()
        {
            int result = (rand() % 11) - 5;
            if (!containsZero && result == 0) containsZero = true;
            return result;
        });
    });

    if (!containsZero)
    {
        matrix[rand() % rows][rand() % cols] = 0;
    }

    cout << "\nGenerated matrix:\n";
    for_each(matrix.begin(), matrix.end(), [&](const vector<int>& row)
    {
        for_each(row.begin(), row.end(), [&](int value)
        {
            cout << value << '\t';
        });
        cout << "\n";
    });

    int totalNegatives = 0;
    int rowNumber = 0;

    for_each(matrix.begin(), matrix.end(), [&](const vector<int>& row)
    {
        rowNumber++;
        bool hasZero = find(row.begin(), row.end(), 0) != row.end();

        if (hasZero)
        {
            int negatives = count_if(row.begin(), row.end(), [](int value) { return value < 0; });
            totalNegatives += negatives;
            cout << "\nRow " << rowNumber << " contains at least one zero and has " << negatives << " negative element";
        }
    });

    cout << "\n\nTotal number of negative elements in rows containing at least one zero: " << totalNegatives << "\n";

    return 0;
}
