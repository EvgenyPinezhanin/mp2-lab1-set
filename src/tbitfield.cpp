// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 0) throw exception("invalid_argument");
  BitLen = len;
  MemLen = (len + sizeof(TELEM)*8 - 1)/(sizeof(TELEM)*8);
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = 0;
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n >= BitLen) throw exception("out_of_range");
  return n / (sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n >= BitLen) throw exception("out_of_range");
  TELEM res = 1;
  int k = n % (sizeof(TELEM)*8);
  res = res << k;
  return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= BitLen) throw exception("out_of_range");
  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= BitLen) throw exception("out_of_range");
  pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n >= BitLen) throw exception("out_of_range");
  int res;
  if (pMem[GetMemIndex(n)] & GetMemMask(n)) res = 1;
    else res = 0;
  return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this != &bf)
  {
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen) return 0;
  for (int i = 0; i < MemLen - 1; i++)
  {
	if (pMem[i] != bf.pMem[i]) return 0;
  }
  int k = bf.BitLen % (sizeof(TELEM)*8);
  for (int i = 0; i < k; i++)
  {
    if (GetBit(sizeof(TELEM)*8*(MemLen - 1) + i) != bf.GetBit(sizeof(TELEM)*8*(MemLen - 1) + i)) return 0;
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen) return 1;
  int b = 0;
  for (int i = 0; i < MemLen - 1; i++)
  {
    if (pMem[i] != bf.pMem[i]) return 1;
  }
  int k = bf.BitLen % (sizeof(TELEM)*8);
  for (int i = 0; i < k; i++)
  {
    if (GetBit(sizeof(TELEM)*8*(MemLen - 1) + i) != bf.GetBit(sizeof(TELEM)*8*(MemLen - 1) + i)) return 1;
  }
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int k = BitLen;
  if (bf.BitLen > BitLen)
  {
    k = bf.BitLen;
  }
  TBitField res(k);
  for (int i = 0; i < MemLen; i++)
    res.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    res.pMem[i] |= bf.pMem[i];
  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int k = BitLen;
  if (bf.BitLen > BitLen)
  {
    k = bf.BitLen;
  }
  TBitField res(k);
  for (int i = 0; i < MemLen; i++)
    res.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    res.pMem[i] &= bf.pMem[i];
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(BitLen);
  for (int i = 0; i < MemLen - 1; i++)
  {
    res.pMem[i] = ~pMem[i];
  }
  int z = BitLen % (sizeof(TELEM)*8);
  int a = sizeof(TELEM)*8*(MemLen - 1);
  for (int i = 0; i < z; i++)
  {
    if (!GetBit(a + i)) res.SetBit(a + i);
      else res.ClrBit(a + i);
  }
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  TELEM k;
  for (int i = 0; i < bf.BitLen; i++)
  {
    istr >> k;
    if (k != 0) bf.SetBit(i);
      else bf.ClrBit(i);
    
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
  {
    ostr << bf.GetBit(i) << " ";
  }
  ostr << endl;

  return ostr;
}
