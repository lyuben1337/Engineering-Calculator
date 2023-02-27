#pragma once
#include "CalcAlgorythm.h"
#include <string>

using namespace System;

ref class Expression {
private:
	String^ expression;
	char* toCharArray();

public:
	Expression();
	String^ get();
	void set(String^ str);
	String^ calculate();
};

