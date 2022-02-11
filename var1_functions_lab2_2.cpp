#include "var1_header_Lab2_2.h"


//конструктор по умолчанию
Matrix::Matrix()
{
	//размер матрицы
	p_n = 0;
	p_m = 0;
	//указатель на матрицу
	pointer = NULL;
}


//конструктор с одним параметром
Matrix::Matrix(int n)
{
	//размер матрицы
	p_n = n;
	p_m = n;

	try 
	{
		//выдел€ем пам€ть дл€ матрицы
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//заполн€ем 
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = (rand() % 13) - 4;
	}
	catch (bad_alloc e) {
		//если пам€ть не выделена, сообщить об ошибке
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//конструктор с двум€ параметрами
Matrix::Matrix(int n, int m)
{
	//размер матрицы
	p_n = n;
	p_m = m;

	try
	{
		//выдел€ем пам€ть дл€ матрицы
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//заполн€ем 
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = (rand() % 13) - 4;
	}
	catch (bad_alloc e) {
		//если пам€ть не выделена, сообщить об ошибке
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//конструктор копировани€
Matrix::Matrix(const Matrix& other)
{
	//размер матрицы
	p_n = other.p_n;
	p_m = other.p_m;

	try {
		//выдел€ем пам€ть дл€ матрицы
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//заполн€ем значени€ми
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = other.pointer[i][j];
	}
	catch (bad_alloc e) {
		//если пам€ть не выделена, сообщить об ошибке
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//деструктор
Matrix::~Matrix()
{
	for (int i = 0; i < p_n; i++)
		delete[] pointer[i];

	delete[] pointer;
}


//получени€ числа из матрицы
int Matrix::getMN(int i, int j)
{
	if ((p_n < i) || (i < 0) || (p_m < j) || (j < 0)) {
		//выход за пределы
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
		cout << "\n¬озвращаемое значение 0." << endl;
		return 0;
	} else
		return pointer[i][j];
}


//изменение числа матрицы
void Matrix::setMN(int element, int i, int j)
{
	//выход за пределы матрицы
	if ((p_n < i) || (i < 0)) {
		//выход за пределы
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
		return;
	}
	else if ((p_m < j) || (j < 0)) {
		//выход за пределы
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
		return;
	} else
		pointer[i][j] = element;
}


//печать матрицы
void Matrix::print(const char* name) 
{
	if (!p_n) {
		//выход за пределы
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
	} else {
		cout << "ѕечать объекта " << name << ":" << endl;

		for (int i = 0; i < p_n; i++)
		{
			for (int j = 0; j < p_m; j++)
				cout << pointer[i][j] << "\t";

			cout << endl;
		}

		cout << endl;
	}
}


//оператор присваивани€
Matrix& Matrix::operator=(const Matrix& other)
{
	//присваивание самому себе
	if (this == &other)
		return *this;

	try {
		//освобождаем пам€ть
		for (int i = 0; i < p_n; i++)
			delete[] pointer[i];

		delete[] pointer;

		//размер матрицы
		p_n = other.p_n;
		p_m = other.p_m;

		//выдел€ем пам€ть дл€ матрицы
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//заполн€ем значени€ми
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = other.pointer[i][j];

		return *this;
	}
	catch (bad_alloc e) {
		//если пам€ть не выделена, сообщить об ошибке
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//оператор +=
Matrix & Matrix::operator+=(const Matrix& other)
{
	if (p_n != other.p_n || p_m != other.p_m) {
		setCode(MistakeCodes::DimensionMismatch);
		aboutCode();
		return *this;
	}

	//складываем
	for (int j = 0; j < p_m; j++)
		for (int i = 0; i < p_n; i++)
			pointer[i][j] += other.pointer[i][j];

	return *this;
}


//оператор -=
Matrix& Matrix::operator-=(const Matrix& other)
{
	if (p_n != other.p_n || p_m != other.p_m) {
		setCode(MistakeCodes::DimensionMismatch);
		aboutCode();
		return *this;
	}

	for (int j = 0; j < p_m; j++)
		for (int i = 0; i < p_n; i++)
			pointer[i][j] -= other.pointer[i][j];

	return *this;
}


//оператор умножени€ матрицу на матрицу
Matrix& Matrix::operator*=(const Matrix& other)
{
	if (p_n != other.p_n || p_m != other.p_m) {
		setCode(MistakeCodes::DimensionMismatch);
		aboutCode();
		return *this;
	}

	//создаем новую матрицу
	Matrix newMtrx(*this);

	for (int j = 0; j < p_m; j++)
		for (int i = 0; i < p_n; i++)
			newMtrx.pointer[i][j] = 0;

	//умножаем
	for (int j = 0; j < other.p_m; j++)
		for (int i = 0; i < p_n; i++)
			for (int k = 0; k < other.p_n; k++)
				newMtrx.pointer[i][j] = pointer[i][k] * other.pointer[k][j] + newMtrx.pointer[i][j];

	//переприсваиваем
	*this = newMtrx;

	return *this;
}


//оператор умножени€ матрицу на число
Matrix& Matrix::operator*(const int number)
{
	for (int i = 0; i < p_n; i++)
		for (int j = 0; j < p_m; j++)
			pointer[i][j] = number * pointer[i][j];

	return *this;
}


//сообщение пользователю о коде ошибки 
void Matrix::aboutCode()
{
	switch (getCode()) {
	case MistakeCodes::NotEnoughMemory:
		cout << " од ошибки: 1. ќписание: нехватка пам€ти." << endl;
		break;
	case MistakeCodes::DimensionMismatch:
		cout << " од ошибки: 2. ќписание: несоответствие размерностей матрицы." << endl;
		break;
	case MistakeCodes::OutOfUsedMemory:
		cout << " од ошибки: 3. ќписание: выхода за пределы используемой пам€ти." << endl;
		break;
	}
}


//установка кода ошибки
void Matrix::setCode(const MistakeCodes code)
{
	p_code = code;
}
