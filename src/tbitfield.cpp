// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) {
    if (len <= 0) {
        throw "ERROR";
    }

    BitLen = len;
    MemLen = BitLen / 32 + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

// конструктор копирования 
TBitField::TBitField(const TBitField &bf) {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[] pMem;
}

// индекс Мем для бита n
int TBitField::GetMemIndex(const int n) const {
    return n / 32;
}

// битовая маска для бита n
TELEM TBitField::GetMemMask(const int n) const {
    return 1 << n % 32;
}

// доступ к битам битового поля

// получить длину (к-во битов)
int TBitField::GetLength(void) const {
    return BitLen;
}

// установить бит
void TBitField::SetBit(const int n) {
    if ((n < 0) || (n >= BitLen)) {
        throw "Error";
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

// очистить бит
void TBitField::ClrBit(const int n) {
    if ((n < 0) || (n >= BitLen)) {
        throw "Error";
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

// получить значение бита
int TBitField::GetBit(const int n) const {
    if ((n < 0) || (n >= BitLen)) {
        throw "Error";
    }
    return GetMemMask(n) & pMem[GetMemIndex(n)];
}

// битовые операции

// присваивание
TBitField& TBitField::operator=(const TBitField &bf) {
    if (bf.MemLen != MemLen) {
        delete[] pMem;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    BitLen = bf.BitLen;
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

// сравнение
int TBitField::operator==(const TBitField &bf) const {
    int res = 1;
    if (BitLen != bf.BitLen)
        res = 0;
    else {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i])
                res = 0;
        }
        for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
            if (GetBit(i) != bf.GetBit(i))
                res = 0;
        }

    }
    return res;
}

// сравнение
int TBitField::operator!=(const TBitField &bf) const {
    int res = 1;
    if (&bf == this) {
        res = 0;
    }
    return res;
}

// операция "или"
TBitField TBitField::operator|(const TBitField &bf) {
    int len = BitLen;
    if (bf.BitLen > len) {
        len = bf.BitLen;
    }

    TBitField temp(len);
    for (int i = 0; i < MemLen; i++) {
        temp.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        temp.pMem[i] |= bf.pMem[i];
    }

    return temp;
}

// операция "и"
TBitField TBitField::operator&(const TBitField &bf) {
    int len = BitLen;
    if (bf.BitLen > len) {
        len = bf.BitLen;
    }

    TBitField temp(len);
    for (int i = 0; i < MemLen; i++) {
        temp.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        temp.pMem[i] &= bf.pMem[i];
    }

    return temp;
}

// отрицание
TBitField TBitField::operator~(void) {
    int len = BitLen;
    TBitField temp(len);
    for (int i = 0; i < MemLen - 1; i++) {
        temp.pMem[i] = ~pMem[i];
    }

    for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
        if (!GetBit(i)) {
            temp.SetBit(i);
        }
    }
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) {
    TELEM bit;
    for (int i = 0; i < bf.BitLen; i++) {
        istr >> bit;
        if (i / 32 == 0) {
            bf.pMem[bf.GetMemIndex(i / 32)] |= bit;
        }
        else {
            bf.pMem[bf.GetMemIndex(i / 32)] <<= 1;
            bf.pMem[bf.GetMemIndex(i / 32)] |= bit;
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) {
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i)) {
            ostr << 1;
        }
        else {
            ostr << 0;
        }
    }
    return ostr;
}
