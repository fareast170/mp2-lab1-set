// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp) {
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower) {
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {
}

TSet::operator TBitField() {
    return BitField;
}

// получить макс. к-во эл-тов 
int TSet::GetMaxPower(void) const {
    return MaxPower;
}

// элемент множества?
int TSet::IsMember(const int Elem) const {
    return BitField.GetBit(Elem);
}

// включение элемента множества
void TSet::InsElem(const int Elem) {
    BitField.SetBit(Elem);
}

// исключение элемента множества
void TSet::DelElem(const int Elem) {
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

// присваивание
TSet& TSet::operator=(const TSet &s) {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

// сравнение
int TSet::operator==(const TSet &s) const {
    return BitField == s.BitField;
}

// сравнение
int TSet::operator!=(const TSet &s) const {
    return BitField != s.BitField;
}

// объединение
TSet TSet::operator+(const TSet &s) {
    return BitField | s.BitField;
}

// объединение с элементом
TSet TSet::operator+(const int Elem) {
    TSet tmp(BitField);
    tmp.InsElem(Elem);
    return tmp;
}

// разность с элементом
TSet TSet::operator-(const int Elem) {
    TSet tmp(BitField);
    tmp.DelElem(Elem);
    return tmp;
}

// пересечение
TSet TSet::operator*(const TSet &s) {
    return BitField & s.BitField;
}

// дополнение
TSet TSet::operator~(void) {
    return ~BitField;
}

// перегрузка ввода/вывода

// ввод
istream &operator>>(istream &istr, TSet &s) {
    int i = 0;
    istr >> i;
    while ((i >= 0) && (i < s.MaxPower)) {
        s.InsElem(i);
        istr >> i;
    }
    return istr;
}

// вывод
ostream& operator<<(ostream &ostr, const TSet &s) {
    ostr << "{";
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            ostr << i << ", ";
        }
    }
    ostr << "}";
    return ostr;
}
