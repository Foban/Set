#include "sets.h"
#include<iostream>
#include<conio.h>

using namespace std;

Set::Set():
elements(0),length(0)
{}

Set::Set(int *ar, int size){
	elements = new int[size];
	bool fl = true;
	length = size;
	for(int i = 0; i < size; ++i){
		for(int n = 0; n < i && fl; ++n)
			if(ar[i] == elements[n]){
				fl = false;
				--length;
			}
		if(fl)elements[i] = ar[i];
		fl = true;
	}
	if(size != length) Recontain();
}

Set::Set(const Set & set){
	elements = new int[set.length];
	for(int i = 0; i < set.length; ++i)
		elements[i] = set.elements[i];
	length = set.length;
}

Set::~Set(){
	delete [] elements;
}

void Set::In_set(int *ar, int size){
	delete [] elements;
	elements = new int[size];
	bool fl = true;
	length = size;
	for(int i = 0; i < size; ++i){
		for(int n = 0; n < i && fl; ++n)
			if(ar[i] == elements[n]){
				fl = false;
				--length;
			}
		if(fl)elements[i] = ar[i];
		fl = true;
	}
	if(size != length) Recontain();
}

void Set::Recontain(){
	int *sets_elements = new int [length];
	for(int i = 0; i < length; ++i)
		sets_elements[i] = elements[i];
	delete [] elements;
	elements = sets_elements;
}

void Set::operator+=(const Set &other){
	*this = *this + other;
}

void Set::operator-=(const Set &other){
	*this = *this - other;
}

void Set::operator*=(const Set &other){
	*this = *this * other;
}

bool Set::operator == (const Set &other){
	if(this != &other){
		bool fl = false;
		for(int i = 0; i < length; ++i){
			for(int n = 0; n < other.length && !fl; ++n)
				if(elements[i] == other.elements[n]) fl = true;
			if(!fl) return false;
			fl = false;
		}
		return true;
	}
	return true;
}

Set & Set::operator=(const Set &other){
	if(this != &other)
	{
		int *new_elements = new int[other.length];
		for(int i = 0; i < other.length; ++i)
			new_elements[i] = other.elements[i];
		delete [] elements;
		elements = new_elements;
		length = other.length;
	}
	return *this;
}

Set & Set::operator+(const Set &other){
	if(this != &other)
	{
		int p = 0;
		bool fl = true;
		for(int n = 0; n < other.length; ++n){
			for(int i = 0; i < length && fl; ++i)
			{
				if(elements[i] == other.elements[n])
					fl = false;
			}
			if(fl) ++p;
			fl = true;
		}
		Set *new_set;
		new_set = new Set;
		if(!p) return *new_set;
		new_set->length = length + p;
		new_set->elements = new int[new_set->length];
		for(int i = 0; i < length; ++i)
			new_set->elements[i] = elements[i];

		p=0;
		fl = true;
		for(int n = 0; n < other.length && p != new_set->length; ++n){
			for(int i = 0; i < length && fl; ++i)
			{
				if(elements[i] == other.elements[n])
					fl = false;
			}
			if(fl){
				new_set->elements[length + p] = other.elements[n];
				++p;
			}
			fl = true;
		}

		return *new_set;
	}
	else
		return *this;
}

Set & Set::operator-(const Set &other){
	Set *new_set;
	new_set = new Set;
	if(this != &other){
		int p = length;
		bool fl = true;
		for(int i = 0; i < length; ++i){
			for(int n = 0; n < other.length && fl; ++n)
				if(elements[i] == other.elements[n])
					fl = false;
			if(!fl) --p;
			fl = true;
		}
		if(!p) return *new_set;
		new_set->length = p;
		new_set->elements = new int [new_set->length];
		
		p = 0;
		for(int i = 0; i < length && p != new_set->length; ++i){
			for(int n = 0; n < other.length && fl; ++n)
				if(elements[i] == other.elements[n])
					fl = false;
			if(fl){
				new_set->elements[p] = elements[i];
				++p;
			}
			fl = true;
		}
	}
	return *new_set;
}

Set & Set::operator*(const Set &other){
	if(this != &other){
		int p = 0;
		bool fl = true;
		for(int n = 0; n < other.length; ++n){
			for(int i = 0; i < length && fl; ++i)
			{
				if(elements[i] == other.elements[n])
					fl = false;
			}
			if(!fl) ++p;
			fl = true;
		}
		Set *new_set;
		new_set = new Set;
		if(!p) return *new_set;
		new_set->length = p;
		new_set->elements = new int[new_set->length];

		p=0;
		fl = true;
		for(int n = 0; n < other.length && p != new_set->length; ++n){
			for(int i = 0; i < length && fl; ++i)
			{
				if(elements[i] == other.elements[n])
					fl = false;
			}
			if(!fl){
				new_set->elements[p] = other.elements[n];
				++p;
			}
			fl = true;
		}

		return *new_set;
	}
	else return *this;
}

int & Set::operator[](int i){
	if(i < length && i > (-1)){
		return elements[i];
	}
	else throw -1;
}

ostream & operator << (ostream &out, const Set &set ){
	out << '{'; 
	for(int i = 0; i < set.length-1; ++i)
		out << set.elements[i] << ", ";
	if(set.length) out << set.elements[set.length-1];
	out << '}';
	return out;
}
istream & operator >> (istream & in, Set &set){
	int *ar, length;
	in >> length;
	ar = new int [length];
	for(int i = 0; i < length; ++i){
		in >> ar[i];
	}
	set.In_set(ar, length);
	delete [] ar;
	return in;
}
