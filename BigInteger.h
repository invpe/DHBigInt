#ifndef _BIG_INT_
#define _BIG_INT_

//https://github.com/Wholanz/Encrypt-BigInteger/blob/master/%E6%BA%90%E4%BB%A3%E7%A0%81/cpp%E6%96%87%E4%BB%B6/main.cpp

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

int CHAR_TO_DIGIT(char x);

char DIGIT_TO_CHAR(int x);




class BigIntegerError : public runtime_error{
public:	
	BigIntegerError(const string& msg = " ") :runtime_error(msg) {
	}
};



class BigInteger{

private:
	string str_int;
	static const string legalDigit;

public:
	BigInteger(const string& str="0");
	BigInteger(const char* pstr);
	BigInteger(const BigInteger& b);

public:

	const string& GetInteger()const{
		return str_int;
	}

public:

	bool isLegal();

	bool isZero();

	void simplifyZero();

private:

	int cmp(const BigInteger& b) const;

	BigInteger addPos(const BigInteger& b) const;

	BigInteger subPos(const BigInteger& b) const;
	
	BigInteger mulPos(const BigInteger& b) const;
	
	BigInteger divPos(const BigInteger& b) const;

	BigInteger modPos(const BigInteger& b) const;

	BigInteger pow(const BigInteger& b) const;

public:

	BigInteger powMod(const BigInteger& b, const BigInteger& m) const;

public:

	BigInteger operator = (const BigInteger& b);

	BigInteger operator = (const string& str);

	BigInteger operator - ()const;


	friend BigInteger operator + (const BigInteger& b1, const BigInteger& b2) ;

	friend BigInteger operator - (const BigInteger& b1, const BigInteger& b2) ;

	friend BigInteger operator * (const BigInteger& b1, const BigInteger& b2) ;

	friend BigInteger operator / (const BigInteger& b1, const BigInteger& b2) ;

	friend BigInteger operator % (const BigInteger& b1, const BigInteger& b2) ;
	
	friend BigInteger operator ^ (const BigInteger& b1, const BigInteger& b2) ;

	friend ostream & operator << (ostream & os, BigInteger& b);

	friend istream & operator >> (istream & is, BigInteger& b);

};

BigInteger operator + (const BigInteger& b1, const BigInteger& b2);

BigInteger operator - (const BigInteger& b1, const BigInteger& b2);

BigInteger operator * (const BigInteger& b1, const BigInteger& b2);

BigInteger operator / (const BigInteger& b1, const BigInteger& b2);

BigInteger operator % (const BigInteger& b1, const BigInteger& b2);

BigInteger operator ^ (const BigInteger& b1, const BigInteger& b2);

ostream & operator << (ostream & os, BigInteger& b);

istream & operator >> (istream & is, BigInteger& b);


#endif