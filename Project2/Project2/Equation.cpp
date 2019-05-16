#include "Equation.h"

//#define DEBUG
#define OPSIZE 6

// Supported operator array
const std::string op[OPSIZE + 6] = { "+", "-", "*", "^", "(", ")", "sin", "cos" ,"tan", "sec", "csc", "cot"};

// Exception Constructor
Equation::Equation()
{
	formula = "";
	postFormula.resize(0);
}

Equation::Equation(std::string formula, int dim)
{
	this->dim = dim;
	this->formula = formula;
	this->postFormula = inToPostfix();
}

// 1D Constructor
Equation::Equation(std::string formula, std::string nameX, double initX, double beginX, double endX)
{
	this->formula = formula;
	this->dim = 1;
	this->name.push_back(nameX);
	this->init.Data.push_back(initX);
	this->xInterval[0] = beginX;
	this->xInterval[1] = endX;
	this->postFormula = inToPostfix();
}

// 2D Constructor
Equation::Equation(std::string formula, std::string nameX, double initX, double beginX, double endX, std::string nameY, double initY, double beginY, double endY)
{
	this->formula = formula;
	this->dim = 2;
	this->name.push_back(nameX);
	this->init.Data.push_back(initX);
	this->xInterval[0] = beginX;
	this->xInterval[1] = endX;
	this->name.push_back(nameY);
	this->init.Data.push_back(initY);
	this->yInterval[0] = beginY;
	this->yInterval[1] = endY;
	this->postFormula = inToPostfix();
}

// Set Formula and reset postfixArr
void Equation::setFormula(std::string formula)
{
	this->formula = formula;
	this->postFormula = inToPostfix();
}

// Return Formula (std::string)
std::string Equation::getString()
{
	return this->formula;
}

// Return Formula and NewLine (System::String)
System::String ^ Equation::getSystemString()
{
	System::String^ Formula = gcnew System::String(formula.c_str());
	Formula += System::Environment::NewLine;
	return Formula;
}

// Normalization Formula and convert to Postfix
// ex. x^2+x-2*x^0.5 -> x ^ 2 + x - 2 * x ^ 0.5
std::vector<std::string> Equation::inToPostfix()
{
	std::string temp = "";
	for (int i = 0; i < formula.length(); i++)
	{
		bool isOP = false;
		for (int j = 0; j < OPSIZE; j++)
		{
			if (formula[i] == op[j][0])
			{
				isOP = true;
				break;
			}
		}

		if (isOP)
		{
			temp = temp + " " + formula[i] + " ";
		}
		else
		{
			temp += formula[i];
		}
	}
	if (temp.size() != 0)
	{
		if (temp[0] == ' ') temp.erase(temp.begin());
		if (temp[temp.length() - 1] == ' ') temp.erase(temp.end());
		while (true) {
			std::string::size_type pos(0);
			if ((pos = temp.find("  ")) != std::string::npos)
				temp.replace(pos, 2, " ");
			else break;
		}
	}

	std::stringstream normalFormula(temp);

	// operator stack
	std::stack<std::string> opStack;

	// store temp node string
	std::string nodeString;

	// reset postformula
	postFormula.clear();

	// infix to postfix
	while (normalFormula >> nodeString)
	{
		if (nodeString == "(")
		{
			opStack.push(nodeString);
		}
		else if (nodeString == "+"		\
			|| nodeString == "-"		\
			|| nodeString == "*"		\
			|| nodeString == "^"		\
			|| nodeString == "sin"		\
			|| nodeString == "cos"		\
			|| nodeString == "tan"		\
			|| nodeString == "sec"		\
			|| nodeString == "csc"		\
			|| nodeString == "cot")
		{
			if (!opStack.empty())
			{
				while (priority(opStack.top()) >= priority(nodeString))
				{
					postFormula.push_back(opStack.top());
					opStack.pop();
					if (opStack.empty()) break;
				}
			}
			opStack.push(nodeString); // push in stack
		}
		else if (nodeString == ")")
		{
			while (opStack.top() != "(")
			{
				// 遇 ) 輸出至 (
				postFormula.push_back(opStack.top());
				opStack.pop();
			}
			opStack.pop();  // 不輸出 (
		}
		else
		{
			// 運算元直接輸出
			if (nodeString != " " && nodeString != "")
			{
				postFormula.push_back(nodeString);
			}
		}
	}
	while (!opStack.empty())
	{
		postFormula.push_back(opStack.top());
		opStack.pop();
	}

	return postFormula;
}

// Use for alter Variable to formula
// ex. the variable "key" in equation change into "str"
std::string Equation::alterFormula(std::string key, std::string str)
{
	// insert blank between operator
	std::string result = "";
	for (int i = 0; i < formula.length(); i++)
	{
		bool isOP = false;
		for (int j = 0; j < OPSIZE; j++)
		{
			if (formula[i] == op[j][0])
			{
				isOP = true;
				break;
			}
		}

		if (isOP)
		{
			result = result + " " + formula[i] + " ";
		}
		else
		{
			result += formula[i];
		}
	}
	if (result.size() != 0)
	{
		if (result[0] == ' ') result.erase(result.begin());
		if (result[result.length() - 1] == ' ') result.erase(result.end());
		while (true) {
			std::string::size_type pos(0);
			if ((pos = result.find("  ")) != std::string::npos)
				result.replace(pos, 2, " ");
			else break;
		}
	}
	// backup the normalFormula
	std::stringstream normalFormula(result);

	// store result node string
	std::string nodeString;

	// reset result string
	result = "";

	// alter variable name to formula
	while (normalFormula >> nodeString)
	{
		if (nodeString == key)
		{
			nodeString = "(" + str + ")";
		}

		result += nodeString;
	}
	return result;
}

std::string Equation::alterFormula(std::string customFormula, std::string key, std::string str)
{
	Equation temp = *this;
	temp.formula = customFormula;
	return temp.alterFormula(key, str);
}

// Get total value by parameters' value
double Equation::f(Vector vec, std::vector<std::string> name)
{
	std::vector<std::string> temp = postFormula;
	for (int i = 0; i < temp.size(); i++)
	{
#ifdef DEBUG
		std::cout << temp[i] << " ";
#endif // DEBUG

		for (int j = 0; j < name.size(); j++)
		{
			if (temp[i] == name[j])
			{
				temp[i] = std::to_string(vec.Data[j]);
				break;
			}
		}
	}
#ifdef DEBUG
	std::cout << std::endl;
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << temp[i] << " ";
	}
	std::cout << std::endl;
#endif // DEBUG

	Equation tempEqu = *this;
	tempEqu.postFormula = temp;

	return tempEqu.f();
}

double Equation::f(double val, std::string name)
{
	std::vector<std::string> temp = postFormula;
	for (int i = 0; i < temp.size(); i++)
	{
#ifdef DEBUG
		std::cout << temp[i] << " ";
#endif // DEBUG

		for (int j = 0; j < name.size(); j++)
		{
			if (temp[i] == name)
			{
				temp[i] = std::to_string(val);
				break;
			}
		}
	}
#ifdef DEBUG
	std::cout << std::endl;
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << temp[i] << " ";
	}
	std::cout << std::endl;
#endif // DEBUG

	// store temp value
	std::stack<double> calStack;

	try
	{
		// postfix calculate
		for (int i = 0; i < temp.size(); i++)
		{
			// if detect binary operator
			if (temp[i] == "+" || temp[i] == "-" || temp[i] == "*" || temp[i] == "^")
			{
				// pop two value
				double b = calStack.top();
				calStack.pop();
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(cal(a, b, temp[i][0]));
			}
			// if detect sin
			else if (temp[i] == "sin")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(sin(a));
			}
			// if detect cos
			else if (temp[i] == "cos")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(cos(a));
			}
			// if detect tan
			else if (temp[i] == "tan")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(tan(a));
			}
			// if detect csc
			else if (temp[i] == "csc")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(1 / sin(a));
			}
			// if detect sec
			else if (temp[i] == "sec")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(1 / cos(a));
			}
			// if detect cot
			else if (temp[i] == "cot")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(1 / tan(a));
			}
			// not operator push value into stack 
			else
			{
				calStack.push(std::stod(temp[i]));
			}
		}

		// Avoid empty stack
		if (calStack.empty()) throw "---Formula is empty---";

		// pop final calculate result vector 
		double result = calStack.top();
		calStack.pop();

		// output
		return result;
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR" << std::endl;
		return 0.0;
	}
	catch (const char* ERRMSG)
	{
		std::cout << ERRMSG << std::endl;
		return 0.0;
	}
}

// Default Calculate
double Equation::f()
{
	// store temp value
	std::stack<double> calStack;

	try
	{
		for (int i = 0; i < this->postFormula.size(); i++)
		{
			// if detect binary operator
			if (this->postFormula[i] == "+" || this->postFormula[i] == "-" || this->postFormula[i] == "*" || this->postFormula[i] == "^")
			{
				// pop two value
				double b = calStack.top();
				calStack.pop();
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(cal(a, b, this->postFormula[i][0]));
			}
			// if detect sin
			else if (this->postFormula[i] == "sin")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(sin(a));
			}
			// if detect cos
			else if (this->postFormula[i] == "cos")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(cos(a));
			}
			// if detect tan
			else if (this->postFormula[i] == "tan")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(tan(a));
			}
			// if detect csc
			else if (this->postFormula[i] == "csc")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(1 / sin(a));
			}
			// if detect sec
			else if (this->postFormula[i] == "sec")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(1 / cos(a));
			}
			// if detect cot
			else if (this->postFormula[i] == "cot")
			{
				// pop value
				double a = calStack.top();
				calStack.pop();

				// push calculated result
				calStack.push(1 / tan(a));
			}
			// not operator push value into stack 
			else
			{
				calStack.push(std::stod(this->postFormula[i]));
			}
		}

		// Avoid empty stack
		if (calStack.empty()) throw "---Formula is empty---";

		// pop final calculate result vector 
		double result = calStack.top();
		calStack.pop();

		// output
		return result;
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR" << std::endl;
		return 0.0;
	}
	catch (const char* ERRMSG)
	{
		std::cout << ERRMSG << std::endl;
		return 0.0;
	}

}

// Use for infix to postfix
int priority(std::string op)
{
	switch (op[0])
	{
	case '+': case '-':
		return 1;
	case '*':
		return 2;
	case '^': case 's': case 'c':
		return 3;
	default:
		return 0;
	}
}

// Easy Calculate function
double cal(double a, double b, char op)
{
	switch (op)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '^':
		return pow(a, b);
		break;
	default:
		throw "Error in cal(double a, double b, char op): Not support op";
		break;
	}
}

System::String ^ ssTo_String(std::stringstream& ss)
{
	System::String^ Str = gcnew System::String("");
	std::string s;
	while (getline(ss, s))
	{
		Str = Str + gcnew System::String(s.c_str()) +System::Environment::NewLine;
	}

	return Str;
}
