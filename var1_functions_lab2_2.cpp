#include "var1_header_Lab2_2.h"


//����������� �� ���������
Matrix::Matrix()
{
	//������ �������
	p_n = 0;
	p_m = 0;
	//��������� �� �������
	pointer = NULL;
}


//����������� � ����� ����������
Matrix::Matrix(int n)
{
	//������ �������
	p_n = n;
	p_m = n;

	try 
	{
		//�������� ������ ��� �������
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//��������� 
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = (rand() % 13) - 4;
	}
	catch (bad_alloc e) {
		//���� ������ �� ��������, �������� �� ������
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//����������� � ����� �����������
Matrix::Matrix(int n, int m)
{
	//������ �������
	p_n = n;
	p_m = m;

	try
	{
		//�������� ������ ��� �������
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//��������� 
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = (rand() % 13) - 4;
	}
	catch (bad_alloc e) {
		//���� ������ �� ��������, �������� �� ������
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//����������� �����������
Matrix::Matrix(const Matrix& other)
{
	//������ �������
	p_n = other.p_n;
	p_m = other.p_m;

	try {
		//�������� ������ ��� �������
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//��������� ����������
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = other.pointer[i][j];
	}
	catch (bad_alloc e) {
		//���� ������ �� ��������, �������� �� ������
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//����������
Matrix::~Matrix()
{
	for (int i = 0; i < p_n; i++)
		delete[] pointer[i];

	delete[] pointer;
}


//��������� ����� �� �������
int Matrix::getMN(int i, int j)
{
	if ((p_n < i) || (i < 0) || (p_m < j) || (j < 0)) {
		//����� �� �������
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
		cout << "\n������������ �������� 0." << endl;
		return 0;
	} else
		return pointer[i][j];
}


//��������� ����� �������
void Matrix::setMN(int element, int i, int j)
{
	//����� �� ������� �������
	if ((p_n < i) || (i < 0)) {
		//����� �� �������
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
		return;
	}
	else if ((p_m < j) || (j < 0)) {
		//����� �� �������
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
		return;
	} else
		pointer[i][j] = element;
}


//������ �������
void Matrix::print(const char* name) 
{
	if (!p_n) {
		//����� �� �������
		setCode(MistakeCodes::OutOfUsedMemory);
		aboutCode();
	} else {
		cout << "������ ������� " << name << ":" << endl;

		for (int i = 0; i < p_n; i++)
		{
			for (int j = 0; j < p_m; j++)
				cout << pointer[i][j] << "\t";

			cout << endl;
		}

		cout << endl;
	}
}


//�������� ������������
Matrix& Matrix::operator=(const Matrix& other)
{
	//������������ ������ ����
	if (this == &other)
		return *this;

	try {
		//����������� ������
		for (int i = 0; i < p_n; i++)
			delete[] pointer[i];

		delete[] pointer;

		//������ �������
		p_n = other.p_n;
		p_m = other.p_m;

		//�������� ������ ��� �������
		pointer = new int* [p_n];

		for (int i = 0; i < p_n; i++)
			pointer[i] = new int[p_m];

		//��������� ����������
		for (int i = 0; i < p_n; i++)
			for (int j = 0; j < p_m; j++)
				pointer[i][j] = other.pointer[i][j];

		return *this;
	}
	catch (bad_alloc e) {
		//���� ������ �� ��������, �������� �� ������
		setCode(MistakeCodes::NotEnoughMemory);
		aboutCode();
		exit(-1);
	}
}


//�������� +=
Matrix & Matrix::operator+=(const Matrix& other)
{
	if (p_n != other.p_n || p_m != other.p_m) {
		setCode(MistakeCodes::DimensionMismatch);
		aboutCode();
		return *this;
	}

	//����������
	for (int j = 0; j < p_m; j++)
		for (int i = 0; i < p_n; i++)
			pointer[i][j] += other.pointer[i][j];

	return *this;
}


//�������� -=
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


//�������� ��������� ������� �� �������
Matrix& Matrix::operator*=(const Matrix& other)
{
	if (p_n != other.p_n || p_m != other.p_m) {
		setCode(MistakeCodes::DimensionMismatch);
		aboutCode();
		return *this;
	}

	//������� ����� �������
	Matrix newMtrx(*this);

	for (int j = 0; j < p_m; j++)
		for (int i = 0; i < p_n; i++)
			newMtrx.pointer[i][j] = 0;

	//��������
	for (int j = 0; j < other.p_m; j++)
		for (int i = 0; i < p_n; i++)
			for (int k = 0; k < other.p_n; k++)
				newMtrx.pointer[i][j] = pointer[i][k] * other.pointer[k][j] + newMtrx.pointer[i][j];

	//���������������
	*this = newMtrx;

	return *this;
}


//�������� ��������� ������� �� �����
Matrix& Matrix::operator*(const int number)
{
	for (int i = 0; i < p_n; i++)
		for (int j = 0; j < p_m; j++)
			pointer[i][j] = number * pointer[i][j];

	return *this;
}


//��������� ������������ � ���� ������ 
void Matrix::aboutCode()
{
	switch (getCode()) {
	case MistakeCodes::NotEnoughMemory:
		cout << "��� ������: 1. ��������: �������� ������." << endl;
		break;
	case MistakeCodes::DimensionMismatch:
		cout << "��� ������: 2. ��������: �������������� ������������ �������." << endl;
		break;
	case MistakeCodes::OutOfUsedMemory:
		cout << "��� ������: 3. ��������: ������ �� ������� ������������ ������." << endl;
		break;
	}
}


//��������� ���� ������
void Matrix::setCode(const MistakeCodes code)
{
	p_code = code;
}
