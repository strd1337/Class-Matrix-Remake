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
    //коды ошибок
    enum class MistakeCodes {
        normal,                                                 //нет ошибок
        NotEnoughMemory,                                        //нехватка памяти
        DimensionMismatch,                                      //несоответствие размерностей
        OutOfUsedMemory                                         //выход за пределы используемой памяти
    };

    //конструкторы
    Matrix();									                //конструктор по умолчанию
    explicit Matrix(int);						                //конструктор с одним параметром
    explicit Matrix(int, int);					                //конструктор с двумя параметрами
    Matrix(const Matrix&);					                    //конструктор копирования
    ~Matrix();									                //деструктор

    //методы
    int getMN(int, int);						                //получения числа из матрицы
    void setMN(int, int, int);			                        //изменение числа матрицы
    void print(const char*);				                    //печать матрицы
    Matrix & operator = (const Matrix&);		                //оператор присваивания
    Matrix & operator += (const Matrix&);		                //оператор +=
    Matrix & operator -= (const Matrix&);		                //оператор -=
    Matrix & operator *= (const Matrix&);		                //оператор *=
    Matrix & operator * (const int);			                //оператор умножения матрицу на число
    MistakeCodes getCode() { return p_code; };                  //получение кода ошибки
    void setCode(const MistakeCodes);                           //установка кода ошибки
    void aboutCode();                                           //сообщение пользователю о коде ошибки 

private:
    int** pointer;								                //указатель на матрицу
    int p_n;									                //кол-во строк
    int p_m;									                //кол-во столбцов
    MistakeCodes p_code = MistakeCodes::normal;                 //код ошибки
};
