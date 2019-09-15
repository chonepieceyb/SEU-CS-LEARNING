#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
class HugeInteger
{
	friend std::ostream& operator <<(std::ostream&output, HugeInteger&x);
	friend std::istream& operator >> (std::istream&input, HugeInteger&x);
private:
	int integer[40];
	int SIZE;
public:
	HugeInteger( int = 0);
	HugeInteger(const char*);
	HugeInteger operator +(const HugeInteger&);
	HugeInteger operator +(int);
	HugeInteger operator +(const char*);
	HugeInteger operator -(const HugeInteger&);
	HugeInteger operator -(int);
	HugeInteger operator -(const char*);
	bool operator ==(const HugeInteger&);
	bool operator !=(const HugeInteger&);
	bool operator >(const HugeInteger&);
	bool operator <(const HugeInteger&);
	bool operator >=(const HugeInteger&);
	bool operator <=(const HugeInteger&);
	bool isZero();
};
#endif
