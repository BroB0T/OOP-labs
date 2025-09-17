#include <iostream>
#include <cmath>

using namespace std;

class myClass
{
	public:	

	float calculateB(float x, float y, float z)
	{
		return (1 + pow(cos(y - 2 * pow(x, 3)), 2)) / (2 + pow(abs(x), 3.0f / 2.0f) - pow(sin(pow(abs(z), 0.2f)), 2)) + pow(log(abs(z - y)), 2);
	}
	float calculateA(float b, float x, float y, float z)
	{
		return pow(y, 2) + (z + pow(sin(pow(abs(y + b), 1.3f)), 2)) / (pow(z, 2) + abs((pow(x, 2) + y) / (y + pow(x, 3) / 3)));
	}
};


int main()
{
	int N = 11;
	float x = 0.48 * N;
	float y = 0.47 * N;
	float z = -1.32 * N;

	cout << "select the desired action : \n - 0 calculate the function\n - 1 tabulate the function" << endl;
	int inputValue = 0;
	cin >> inputValue;
	
	myClass newClass;

	float b;
	float a;

	if (inputValue == 0)
	{
		b = newClass.calculateB(x, y, z);
		cout << "\n\n b = " << b;

		a = newClass.calculateA(b, x, y, z);

		cout << "\t\t a = " << a;
	}
	else if (inputValue == 1)
	{
		for (x = -1; x <= 1; x += 0.2f)
		{
			cout << "\n" << x;
			b = newClass.calculateB(x, y, z);
			cout << "\t| b = " << b;

			a = newClass.calculateA(b, x, y, z);
			cout << "\t| a = " << a;
		}
	}

	else
	{
		cout << "\n\n error incorrect input";
	}
	
	return 0;
}