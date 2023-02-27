#include "Expression.h"

Expression::Expression() {
	this->expression = "";
}

String^ Expression::get() {
	return this->expression;
}

void Expression::set(String^ str) {
	this->expression = str;
}

char* Expression::toCharArray() {
	int size = this->expression->Length;
	char* result = new char[size];
	for (int i = 0; i < size; i++) {
		result[i] = (char)this->expression[i];
	}
	result[size] = '\0';
	return result;
}

String^ Expression::calculate() {
	
	char* exp = toCharArray();

	calc_bracets(exp);// calc_brackets
	defuntction(exp);// calc_functions
	multiplication(exp); //calc_monoms

	float result = summator(exp);

	return result.ToString();
}
