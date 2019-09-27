#pragma once
#include<iostream>
using namespace std;
class Ficha {
private:
	wchar_t simbolo; 
public:
	Ficha(wchar_t = ' ');
	~Ficha();
	wchar_t getSimbolo();
	void setSimbolo(wchar_t);
};