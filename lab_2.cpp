#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;


class Vector
{
private:
	double* data;
	int size;

public:
	Vector()
	{
		data = new double[0];
	}

	Vector(int _size) 
	{
		size = _size;
		data = new double[size];
	}

	Vector(const Vector& other)
	{
		size = other.size;
		data = new double[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = other.data[i];
		}
	}

	Vector& operator=(const Vector& other) 
	{
		if (this == &other) return *this;

		delete[] data;
		size = other.size;
		data = new double[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = other.data[i];
		}

		return *this;
	}

	~Vector() 
	{
		delete[] data;
	}

	int Size()
	{
		return size;
	}

	double& Get(int i)
	{
		return data[i];
	}

	void Print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << fixed << setprecision(2) << data[i] << "\t";
		}
		cout << "\n";
	}

	void FillRandom(double min, double max)
	{
		for (int i = 0; i < size; i++)
		{
			Get(i) = min + ((double)rand() / RAND_MAX) * (max - min);
		}
	}
};

class Matrix
{
private:
	Vector* rows;
	int nRows;
	int nCols;

public:

	Matrix(int _nRows, int _nCols)
	{
		nRows = _nRows;
		nCols = _nCols;

		rows = new Vector[nRows];

		for (int i = 0; i < nRows; i++){
			rows[i] = Vector(nCols);
		}
	}

	~Matrix(){
		delete[] rows;
	}

	int RowsCount(){
		return nRows;
	}

	int ColsCount(){
		return nCols;
	}

	double& Element(int i, int j)
	{
		return rows[i].Get(j);
	}

	void Print()
	{
		for (int i = 0; i < nRows; i++)
		{
			rows[i].Print();
		}
		cout << "\n";
	}

	void FillRandom(double min, double max)
	{
		for (int i = 0; i < nRows; i++)
		{
			rows[i].FillRandom(min, max);
		}
	}

	Matrix Add(Matrix& other)
	{
		if (nRows != other.RowsCount() || nCols != other.ColsCount())
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
		if (nRows != other.RowsCount() || nCols != other.ColsCount())
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

	A.FillRandom(-2.0, 5.0);// matrix A value range
	B.FillRandom(-10.0, 10.0); // matrix B value range

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
		multiplier.FillRandom(0.0, 3.0); // multiplier vector value range


		cout << "A * Vector:\n";
		A.MultiplyByVector(multiplier).Print();
	}
	catch (exception& error) {
		cout << "Error: " << error.what() << endl;
	}

	return 0;
}
