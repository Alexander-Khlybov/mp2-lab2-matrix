// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
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
  int GetSize()      { return Size;       } // размер вектора
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
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 1)
        throw
        length_error("Length of vector must be positive");
    Size = s;
    pVector = new ValType[s];
    if ((si < 0) || (si > s - 1))
        throw
        out_of_range("Out of range");
    StartIndex = si;

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
    if ((pos < StartIndex) || (pos >= Size))
        throw
        out_of_range("Out of range");
    return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
int TVector<ValType>::operator==(const TVector &v) const
{
    int tmp = 1
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
    return tmp;
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
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
    if (s < 1)
        throw
        length_error("Matrix size must be positive");
    else if (s > MAX_VECTOR_SIZE)
        throw
        length_error("Matrix size must be less than (MAX_MATRIX_SIZE + 1)");
    for (int i = 0; i < s; i++)
        pVector[i] = TVector<ValType>(s - i, i);
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt)
{
    pVector = new TVector<ValType>[mt.Size];
    for (int i = 0; i < Size; i++)
            pVector[i] = mt.pVector[i];
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
int TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    for (int i = 0; i < Size; i++);
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
        pVector = new TVector<ValType>[mt.Size];
        for (int i = 0; i < Size; i++)
            pVector[i] = mt.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    return mt;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    return mt;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
