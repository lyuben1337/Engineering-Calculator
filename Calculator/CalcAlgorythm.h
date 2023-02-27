#pragma once

#include <string>
#include <cmath>
#include <iomanip>
#include <windows.h>

using namespace std;


static char precision[5] = "%.3f";


void clean(char* str);
bool isletter(char* s);
int len(char* str);
bool isoperator(char sym);
bool isexponential(char* str, int i);
double summator(char* expression);
void strcopy(char* str_in, char* str_out, int start_id, int end_id);
void multiplication(char* expression);
bool isletter(char s);
bool compare_str(char* str1, const char* str2);
double function_calc(char* function, double value);
void defuntction(char* expression);
void calc_bracets(char* expression);
