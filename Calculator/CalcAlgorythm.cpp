#include "CalcAlgorythm.h"

void clean(char* str)
{
	for (int i = 0; str[i]; i++)
	{
		str[i] = '\0';
	}
}
bool isletter(char* s)
{
	for (int i = 0; s[i]; i++)
		if (s[i] >= 97 && s[i] <= 122)
			return 1;
	return 0;
}
int len(char* str)
{
	int res = 0;
	for (int i = 0; str[i]; i++)
	{
		res++;
	}
	return res;
}
bool isoperator(char sym)
{
	switch (sym)
	{
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 1;
	case '/':
		return 1;
	case '^':
		return 1;
	}
	return 0;
}
bool isexponential(char* str, int i)
{ // 2e+10 - str[1] == 'e', str[2] == '+' || '-'
	if (str[i] == 'e' && (str[i + 1] == '+' || str[i + 1] == '-')) return 1;
	if ((str[i] == '+' || str[i] == '-') && str[i - 1] == 'e') return 1;
	return 0;
}
double summator(char* expression)
{
	char numer[256] = "";
	bool plus = 0, minus = 0, first_number_switch = 1, isnegative = 0, firstnumerisnegative = 0;
	double result = 0;
	for (int i = 0; i < len(expression); i++)
	{
		if (expression[i] == '-' && i == 0) // if firstnumer is negative
		{
			for (; expression[i] == '-'; i++)
			{
				if (i % 2 == 0) firstnumerisnegative = 1; // -2 == -2
				else firstnumerisnegative = 0; // --2 == 2
			}
		}
		if (expression[i] == '-' && (expression[i - 1] == '+' || expression[i - 1] == '-')) // if numer is negative (--2/+-3)
		{
			isnegative = 1;
			continue;
		}
		if (isdigit(expression[i])) // copying numer in secondary string
		{
			clean(numer);
			for (int j = 0; isdigit(expression[i]) || expression[i] == '.' || isexponential(expression, i); i++, j++)
			{
				numer[j] = expression[i];
			}
		}
		if (plus)
		{
			if (isnegative)
				result += stod(numer) * (-1);
			else
				result += stod(numer);
		}
		else if (minus)
			if (isnegative)
				result -= stod(numer) * (-1);
			else
				result -= stod(numer);
		if (first_number_switch) // if it is first addition
		{
			if (firstnumerisnegative)
			{
				firstnumerisnegative = 0;
				result = -stod(numer);
			}
			else
				result = stod(numer);
			first_number_switch = 0;
		}
		if (isoperator(expression[i])) // when it is operator we plus or minus
		{
			if (expression[i + 1] == '-') // Seeing minus
				isnegative = 1;
			else isnegative = 0;
			plus = 0, minus = 0;
			switch (expression[i])
			{
			case '+':
				plus = 1;
				break;
			case '-':
				minus = 1;
				break;
			}
		}
	}
	return result;
}
void strcopy(char* str_in, char* str_out, int start_id, int end_id)
{ // copying from str_out to str_in in interval [start_id; end_id]
	int len_in = end_id - start_id + 1; // size of interval
	if (len_in > len(str_out))
	{
		for (int i = start_id, j = 0; str_out[j]; i++, j++)
		{
			str_in[i] = str_out[j];
		}
		for (int i = start_id + len(str_out); str_in[i + len_in - len(str_out) - 1]; i++) // formating string
		{
			str_in[i] = str_in[i + len_in - len(str_out)];
		}
	}
	else if (len_in < len(str_out))
	{

		for (int i = len(str_in); i > end_id; i--)
		{
			str_in[i + len(str_out) - len_in] = str_in[i];
		}

		for (int i = start_id, j = 0; str_out[j]; i++, j++) // formating string
		{
			str_in[i] = str_out[j];
		}
	}
	else if (len_in = len(str_out))
	{
		for (int i = start_id, j = 0; str_out[j]; i++, j++) // just copying
		{
			str_in[i] = str_out[j];
		}
	}
}
void multiplication(char* expression)
{
	bool multiplication = 0, division = 0, first_numer = 1, isnegative = 0, power = 0, firstnumerisnegative = 0;
	char numer[256] = "";
	double result = 0;
	int k = 0;
	for (int i = 0, j = 0; i < len(expression); i++)
	{
		if (expression[i] == '-' && i == 0) // if first numer is negative
		{
			for (; expression[i] == '-'; i++)
			{
				if (i % 2 == 0) firstnumerisnegative = 1; // -2 == -2
				else firstnumerisnegative = 0; // --2 == 2
			}
		}
		if (expression[i] == '-' && isoperator(expression[i - 1])) // if numer is negative(--2 / +-3)
		{
			isnegative = 1;
			continue;
		}
		if (isdigit(expression[i])) // copying numer in secondary string
		{
			clean(numer);
			for (int j = 0; isdigit(expression[i]) || expression[i] == '.' || isexponential(expression, i); i++, j++)
			{
				numer[j] = expression[i];
			}
		}
		if (multiplication)
		{
			result *= stod(numer);
			if (isnegative)
				result *= -1;
		}
		if (division)
		{
			result /= stod(numer);
			if (isnegative)
				result *= -1;
			if (stod(numer) == 0)
				result = 0;
		}
		if (power)
		{
			result = pow(result, stod(numer));
			if (isnegative)
				result = 1 / result;
		}
		if (first_numer) //if it is first multiplier
		{
			result = 1;
			if (firstnumerisnegative)
			{
				firstnumerisnegative = 0;
				result = -1;
			}
			result *= stod(numer);
			first_numer = 0;
		}
		if ((isoperator(expression[i]) && i != 0) || expression[i] == '\0') // when it is operator we multiply or divide
		{
			if (expression[i + 1] == '-') // Seeing minus
				isnegative = 1;
			else isnegative = 0;
			multiplication = 0, division = 0, power = 0;
			switch (expression[i])
			{
			case '*':
				multiplication = 1;
				break;
			case '/':
				division = 1;
				break;
			case '^':
				power = 1;
				break;
			default: // when it is + or -
				char buff[100] = ""; // buff string for copiyng digits
				sprintf_s(buff, precision, result); // copiyng our result (convertating from string to double)
				strcopy(expression, buff, j, i - 1); // replacement a monom to result of this monom
				if (i - j > len(buff))  // index correction if (res > monom) 
				{
					int temp = (i - j) - len(buff);
					i -= temp;
				}
				else if (i - j < len(buff)) // index correction if (res > monom)
				{
					int temp = len(buff) - (i - j);
					i += temp;
				}
				result = 0;
				j = i + 1; // index of new monom starting
				first_numer = 1;
				break;
			}
			clean(numer);
		}
	}
	clean(numer);
}
bool isletter(char s)
{ // for functions
	if (s >= 97 && s <= 122)
		return 1;
	return 0;
}
bool compare_str(char* str1, const char* str2)
{ // ("abc" == "abc") = 1, ("abc" == "1231") = 0
	for (int i = 0; str1[i] && str2[i]; i++)
		if (str1[i] != str2[i]) return 0;
	return 1;
}
double function_calc(char* function, double value)
{
	if (compare_str(function, "sin"))
		return sin(value);
	if (compare_str(function, "cos"))
		return cos(value);
	if (compare_str(function, "tg"))
	{
		if (tan(value) == tan(acos(-1) / 2))
		{
			return 0;
		}
		return tan(value);
	}
	if (compare_str(function, "ctg"))
	{
		if (tan(value) == 0)
		{
			return 0;
		}
		return 1 / tan(value);
	}
	if (compare_str(function, "ln"))
	{
		if (value <= 0)
		{
			;
			return 0;
		}
		return log(value);
	}
	if (compare_str(function, "exp"))
		return exp(value);
	if (compare_str(function, "sqrt"))
	{
		if (value < 0)
		{
			return 0;
		}
		return sqrt(value);
	}
	if (compare_str(function, "abs"))
		return fabs(value);
	if (compare_str(function, "arcsin"))
	{
		if (value >= -1 && value <= 1)
			return asin(value);
		return 0;
	}
	if (compare_str(function, "arccos"))
	{
		if (value >= -1 && value <= 1)
			return acos(value);
		return 0;
	}
	if (compare_str(function, "arctg"))
		return atan(value);

	return 0;
}
void defuntction(char* expression)
{
	char function[16] = ""; // name of function
	char numer[256] = "";
	for (int i = 0, j = 0; i < len(expression); i++)
	{
		if (isdigit(expression[i]) || isoperator(expression[i]) || expression[i] == '.' || isexponential(expression, i))
			continue;
		clean(function);
		clean(numer);
		if (isletter(expression[i])) // start of function name
		{
			j = i;
			for (int j = 0; !isdigit(expression[i]) && expression[i] != '-'; j++, i++)
			{
				function[j] = expression[i]; // copiyng function name
			}
		}
		numer[0] = expression[i];
		i++;
		for (int j = 1; isdigit(expression[i]) || expression[i] == '.' || isexponential(expression, i); j++, i++)
		{
			numer[j] = expression[i]; // copiyng function parameter
		}
		char buff[100] = "";
		sprintf_s(buff, precision, function_calc(function, stod(numer))); // to_string
		strcopy(expression, buff, j, i - 1);
		if (i - j > len(buff)) // index correction
		{
			int temp = (i - j) - len(buff);
			i -= temp;
		}
		else if (i - j < len(buff)) // index correction
		{
			int temp = len(buff) - (i - j);
			i += temp;
		}
	}
}
void calc_bracets(char* expression)
{
	char polynom[2048] = "";
	int open_bracet_id = 0, close_bracet_id = 0; // start and end of polynom
	for (int i = 0; expression[i]; i++) // cycle ends when there are no bracets
	{
		if (expression[i] == '(') // beginning of the polynom
		{
			open_bracet_id = i;
			i++, clean(polynom);
			for (int j = 0; expression[i] != ')'; j++, i++) // copiyng polynom
			{
				if (expression[i] == '(') // when polynom in polynom
				{
					open_bracet_id = i, i++, j = 0, clean(polynom);
				}
				polynom[j] = expression[i];
			}
			close_bracet_id = i;
			defuntction(polynom);
			multiplication(polynom);
			char buff[100] = "";
			sprintf_s(buff, precision, summator(polynom)); // to_string
			strcopy(expression, buff, open_bracet_id, close_bracet_id);
			i = -1; //beacuse next iteration i++
		}
	}
}