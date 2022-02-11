#include <Windows.h>	
#include <math.h>   					
#include <iomanip> 
#include <iostream>	 
#include <new>
#include <ctime>


using namespace std;


class Matrix
{ 
public: 
    //���� ������
    enum class MistakeCodes {
        normal,                                                 //��� ������
        NotEnoughMemory,                                        //�������� ������
        DimensionMismatch,                                      //�������������� ������������
        OutOfUsedMemory                                         //����� �� ������� ������������ ������
    };

    //������������
    Matrix();									                //����������� �� ���������
    explicit Matrix(int);						                //����������� � ����� ����������
    explicit Matrix(int, int);					                //����������� � ����� �����������
    Matrix(const Matrix&);					                    //����������� �����������
    ~Matrix();									                //����������

    //������
    int getMN(int, int);						                //��������� ����� �� �������
    void setMN(int, int, int);			                        //��������� ����� �������
    void print(const char*);				                    //������ �������
    Matrix & operator = (const Matrix&);		                //�������� ������������
    Matrix & operator += (const Matrix&);		                //�������� +=
    Matrix & operator -= (const Matrix&);		                //�������� -=
    Matrix & operator *= (const Matrix&);		                //�������� *=
    Matrix & operator * (const int);			                //�������� ��������� ������� �� �����
    MistakeCodes getCode() { return p_code; };                  //��������� ���� ������
    void setCode(const MistakeCodes);                           //��������� ���� ������
    void aboutCode();                                           //��������� ������������ � ���� ������ 

private:
    int** pointer;								                //��������� �� �������
    int p_n;									                //���-�� �����
    int p_m;									                //���-�� ��������
    MistakeCodes p_code = MistakeCodes::normal;                 //��� ������
};
