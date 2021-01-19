#pragma once
#include<string>
using std::string;
class Error {
private:
	int numError;
public:
	Error(int);
	string ejecutar();
	~Error();
};

