#ifndef XORSHIFT_H
#define XORSHIFT_H


class XorShift
{
    int _Seed;
public:
    XorShift(int);
    int GetRandomNumber(unsigned, unsigned);
    int GetRandomNumber();

};

#endif // XORSHIFT_H
