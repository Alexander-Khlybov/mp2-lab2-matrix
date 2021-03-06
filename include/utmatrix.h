﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size + StartIndex; } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  int operator==(const TVector &v) const;  // сравнение
  int operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << "\t";
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 1)
        throw
        length_error("Length of vector must be positive");
    else if (s > MAX_VECTOR_SIZE)
        throw
        length_error("length of vector must be less than (MAX_VECTOR_SIZE + 1)");
    if ((si < 0) || (si >= s))
        throw
        out_of_range("StartIndex must be >=0 and < Size");
    Size = s - si;
    StartIndex = si;

    pVector = new ValType[Size];
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)
        pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[]pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if ((pos < 0) || (pos >= (Size + StartIndex)))
        throw
        out_of_range("Out of range");
    else if (pos < StartIndex)
        throw
        exception("This element is empty by definition. You cannot change it.");
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
int TVector<ValType>::operator==(const TVector &v) const
{
    int tmp = 1;
    if (this != &v)
    {
        if (Size != v.Size)
            tmp = 0;
        else if (StartIndex != v.StartIndex)
            tmp = 0;
        else
            for (int i = 0; i < Size; i++)
                if (pVector[i] != v.pVector[i])
                {
                    tmp = 0;
                    break;
                }
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
int TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this != &v)
    {
        Size = v.Size;
        StartIndex = v.StartIndex;
        delete[]pVector;
        pVector = new ValType[Size];
        for (int i = 0; i < Size; i++)
            pVector[i] = v.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector tmp(*this);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] += val;
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector tmp(*this);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] -= val;
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector tmp(*this);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] *= val;
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw
        exception("You can not fold two vectors of non equal size.");
    TVector tmp(*this);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] += v.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw
        exception("You can not subtract two vectors of non equal size.");
    TVector tmp(*this);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] -= v.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw
        exception("You can not find the dot product of vectors with different sizes.");
    TVector tmp(*this);
    ValType sum = 0;
    for (int i = 0; i < Size; i++)
        sum += pVector[i] * v.pVector[i];
    return sum;
} /*-------------------------------------------------------------------------*/

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  int operator==(const TMatrix &mt) const;      // сравнение
  int operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
      for (int i = 0; i < mt.Size; i++)
      {
          for (int j = 0; j < i; j++)
              out << "\t";
          out << mt.pVector[i] << endl;
      }
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >((s <= MAX_MATRIX_SIZE) ? s : -1, 0)
{
    for (int i = 0; i < s; i++)
    {
        pVector[i] = TVector<ValType>(s, i);
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt)
{
    Size = mt.Size;
    StartIndex = mt.StartIndex;
    pVector = new TVector<ValType>[Size];
    for (int i = 0; i < Size; i++)
        pVector[i] = mt.pVector[i];
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
int TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (Size != mt.Size)
        return 0;
    for (int i = 0; i < Size; i++)
        if (pVector[i] != mt.pVector[i])
            return 0;
    return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
int TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this != &mt)
    {
        delete[]pVector;
        Size = mt.Size;
        StartIndex = mt.StartIndex;
        pVector = new TVector<ValType>[Size];
        for (int i = 0; i < Size; i++)
            pVector[i] = mt.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw
        exception("You can not fold matrices of non equal sizes.");
    TMatrix<ValType> tmp(*this);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = tmp.pVector[i] + mt.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw
        exception("You can not subtract matrices of non equal sizes.");
    TMatrix<ValType> tmp(*this);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = tmp.pVector[i] - mt.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif 
