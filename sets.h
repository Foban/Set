#ifndef SETS_H
#define SETS_H

#include<iostream>
using namespace std;

class Set{
public:
	Set();
	Set(int *, int);
	Set(const Set &);
	void In_set(int *, int);
	void Recontain();
	int &operator[](int );
	void operator +=(const Set &);
	void operator -=(const Set &);
	void operator *=(const Set &);
	bool operator == (const Set &);
	Set & operator = (const Set &);
	Set & operator + (const Set &);
	Set & operator - (const Set &);
	Set & operator * (const Set &);
	friend ostream & operator << (ostream &, const Set &);
	friend istream & operator >> (istream &, Set &);
	~Set();
private:
	int *elements;
	int length;
};

#endif