#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Monomial
{
	double number;
	map<char, int> variables;

public:
	Monomial(double _number, string _variables = "") : number(_number)
	{
		for (int i = 0; i < _variables.length(); i++)
		{
			variables[_variables[i]]++;
		}
	}

	Monomial operator*(const Monomial& other) const
	{
		// 2xy * 3zy = 6xy^2z
		Monomial result((number * other.number));

		for (const auto& key_value : variables)
		{
			result.variables[key_value.first] = key_value.second;
		}
		for (const auto& key_value : other.variables)
		{
			result.variables[key_value.first] += key_value.second;
		}
		return result;
	}


	void print()
	{
		cout << number;
		for (const auto& key_value : variables)
		{
			cout << " ";
			if (key_value.second != 1)
			{
				cout << key_value.first << "^" << key_value.second;
			}
			else
			{
				cout << key_value.first;
			}
		}
		cout << endl;
	}
};

class Polynomial
{
	vector<Monomial> monomials;

};

int main()
{
	Monomial constant(3, "yoo");
	Monomial monomial(8, "xxxyz");
	Monomial result = constant * monomial;
	monomial.print();
	constant.print();
	result.print();
	Polynomial polynomial;
}