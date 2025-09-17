#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;


class Vector
{
private: 
	vector<double> data;

public:
	Vector(int size) 
	{
		data = vector<double>(size);
	}

	int Size()
	{
		return data.size();
	}

	double& Get(int i)
	{
		return data.at(i);
	}

	void Print()
	{
		for (int i = 0; i < data.size(); i++)
		{
			cout << fixed << setprecision(2) << data[i] << "\t";
		}
		cout << "\n";
	}

	void FillRandom(double min, double max)
	{
		for (int i = 0; i < Size(); i++)
		{
			Get(i) = min + ((double)rand() / RAND_MAX) * (max - min);
		}
	}
};

class Matrix
{
private:
	vector<Vector> rows;

public:

	Matrix(int nRows, int nCols)
	{
		rows = vector<Vector>(nRows, Vector(nCols));
	}


	int RowsCount()
	{
		return rows.size();
	}

	int ColsCount()
	{
		return rows.empty() ? 0 : rows[0].Size();
	}

	double& Element(int i, int j)
	{
		return rows.at(i).Get(j);
	}

	void Print()
	{
		for (int i = 0; i < rows.size(); i++)
		{
			rows[i].Print();
		}
		cout << "\n";
	}

	void FillRandom(double min, double max)
	{
		for (int i = 0; i < RowsCount(); i++)
		{
			rows[i].FillRandom(min, max);
		}
	}

	Matrix Add(Matrix& other)
	{
		if (rows.size() != other.RowsCount() || ColsCount() != other.ColsCount())
		{
			throw invalid_argument("Matrices of different sizes!");
		}

		Matrix result(RowsCount(), ColsCount());
		for (int i = 0; i < RowsCount(); i++)
		{
			for (int j = 0; j < ColsCount(); j++)
			{
				result.Element(i, j) = Element(i, j) + other.Element(i, j);
			}
		}
		return result;
	}

	Matrix Subtract(Matrix& other)
	{
		if (rows.size() != other.RowsCount() || ColsCount() != other.ColsCount())
		{
			throw invalid_argument("Matrices of different sizes!");
		}

		Matrix result(RowsCount(), ColsCount());
		for (int i = 0; i < RowsCount(); i++)
		{
			for (int j = 0; j < ColsCount(); j++)
			{
				result.Element(i, j) = Element(i, j) - other.Element(i, j);
			}
		}
		return result;
	}

	Vector MultiplyByVector(Vector& vector)
	{
		if (ColsCount() != vector.Size()) 
		{
			throw invalid_argument("Matrix and vector sizes mismatch");
		}

		Vector result(RowsCount());
		for (int i = 0; i < RowsCount(); i++)
		{
			double sum = 0;
			for (int j = 0; j < ColsCount(); j++)
			{
				sum += Element(i, j) * vector.Get(j);
			}
			result.Get(i) = sum;
		}
		return result;
	}

	Matrix Multiply(Matrix& other)
	{
		if (ColsCount() != other.RowsCount())
		{
			throw invalid_argument("Matrices of different sizes!");
		}

		Matrix result(RowsCount(), other.ColsCount());
		for (int i = 0; i < RowsCount(); i++)
		{
			for (int j = 0; j < other.ColsCount(); j++)
			{
				double sum = 0;

				for (int k = 0; k < ColsCount(); k++)
				{
					sum += Element(i, k) * other.Element(k, j);
				}
				result.Element(i, j) = sum;
			}
		}
		return result;
	}
};


int main()
{
	srand(time(0));

	Matrix A(3, 3);
	Matrix B(3, 3);

	A.FillRandom(-2.0, 5.0);
	B.FillRandom(-10.0, 10.0);

	cout << "Matrix A:\n";
	A.Print();
	cout << "Matrix B:\n";
	B.Print();
	
	try 
	{
		cout << "A + B:\n";
		A.Add(B).Print();

		cout << "A - B:\n";
		A.Subtract(B).Print();

		cout << "A * B\n";
		A.Multiply(B).Print();


		Vector multiplier(A.ColsCount());
		multiplier.FillRandom(0.0, 3.0);
		

		cout << "A * Vector:\n";
		A.MultiplyByVector(multiplier).Print();
	}
	catch (exception& error) {
		cout << "Error: " << error.what() << endl;
	}

	return 0;
}