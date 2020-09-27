// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{   
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}   

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    TBitField res(MaxPower);
    return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower) return 0;
    if (BitField.GetBit(Elem)) return 1;
        else return 0;
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw logic_error("out_of_range");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw logic_error("out_of_range");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (BitField == s.BitField) return 1;
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) return 1;
    if (BitField != s.BitField) return 1;
    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int  len = MaxPower;
    if (s.MaxPower > len) len = s.MaxPower;
    TSet res(len);
    res.BitField = BitField | s.BitField;
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(MaxPower);
    if (Elem < 0 || Elem >= MaxPower) throw logic_error("out_of_range");
    res.BitField.SetBit(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(MaxPower);
    if (Elem < 0 || Elem >= MaxPower) throw logic_error("out_of_range");
    res.BitField.ClrBit(Elem);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int  len = MaxPower;
    if (s.MaxPower > len) len = s.MaxPower;
    TSet res(len);
    res.BitField = BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(MaxPower);
    res.BitField = ~BitField;
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	char c;
	int k;
	istr >> c;
	while(c != ')')
    {
        istr >> k >> c;
		s.BitField.GetBit(k);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "(";
	bool b = false;
    for (int i = 0; i < s.MaxPower; i++)
    {
		if (s.BitField.GetBit(i))
		{
			if (!b)
			{
				ostr << i;
				b = true;
			}
			else
			{
				ostr << ", " << i;
			}
		}
    }
	ostr << ")";
    return ostr;
}
