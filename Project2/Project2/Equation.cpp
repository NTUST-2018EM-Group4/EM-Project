#include "Equation.h"
#define DEBUG

// Supported operator array
const std::string op[OPSIZE + 2] = { "+", "-", "*", "^", "(", ")", "sin", "cos" };

// Exception Constructor
Equation::Equation()
{
	formula = "";
	postFormula.resize(0);
}

// Default Constructor
Equation::Equation(std::string formula)
{
	this->formula = formula;
	this->postFormula = inToPostfix();
}

// Use for alter Variable to formula
// ex. f(a1+0.05) 
Equation::Equation(std::string formula, std::vector<Parameter> paras)
{
	// insert blank between operator
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
	}
	// backup the normalFormula
	std::stringstream normalFormula(temp);

	// store temp node string
	std::string nodeString;
	
	// reset temp string
	temp = "";

	// alter variable name to formula
	while (normalFormula >> nodeString)
	{
		for (int i = 0; i < paras.size(); i++)
		{
			if (nodeString == paras[i].name)
			{
				nodeString = "(" + paras[i].formula + ")";
				break;
			}
		}
		temp += nodeString;
	}

	this->formula = temp;
	this->postFormula = inToPostfix();
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
	}

	std::stringstream normalFormula(temp);

	// operator stack
	std::stack<std::string> opStack;

	// store temp node string
	std::string nodeString;

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
			|| nodeString == "cos")
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

// Output Formula String
System::String ^ Equation::FormulaOutputStr()
{
	System::String^ Formula = gcnew System::String(formula.c_str());
	Formula += System::Environment::NewLine;
	return Formula;
}

// Get total value by parameters' value
double Equation::f(std::vector<Parameter> paras)
{
	std::vector<std::string> temp = postFormula;
	for (int i = 0; i < temp.size(); i++)
	{
#ifdef DEBUG
		std::cout << temp[i] << " ";
#endif // DEBUG

		for (int j = 0; j < paras.size(); j++)
		{
			if (temp[i] == paras[j].name)
			{
				temp[i] = std::to_string(paras[j].init);
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
	}
	catch (const char* ERRMSG)
	{
		std::cout << ERRMSG << std::endl;
	}
}

System::String ^ Equation::Powell(std::vector<Parameter> paras)
{
	System::String^ Result = "Powell: " + this->FormulaOutputStr();

	// TODO

#ifdef DEBUG
	// test f(x,y)
	std::cout << this->f(paras) << std::endl;

	// test f(a1+0.05,0.05)
	std::vector<Parameter> testParas;
	testParas.push_back(Parameter("x", "a1+0.05"));
	testParas.push_back(Parameter("y", "0.05"));
	Equation testEqu(formula, testParas);
	std::cout << testEqu.formula << std::endl;
#endif // DEBUG

	return Result;
}

System::String ^ Equation::Newton(std::vector<Parameter> paras)
{
	System::String^ Result = "Newton: " + this->FormulaOutputStr();

	// TODO

	return Result;
}

System::String ^ Equation::Steep(std::vector<Parameter> paras)
{
	System::String^ Result = "Steep: " + this->FormulaOutputStr();

	// TODO

	return Result;
}

System::String ^ Equation::Quasi(std::vector<Parameter> paras)
{
	System::String^ Result = "Quasi: " + this->FormulaOutputStr();

	// TODO

	return Result;
}

System::String ^ Equation::Conjuate(std::vector<Parameter> paras)
{
	System::String^ Result = "Conjuate: " + this->FormulaOutputStr();

	// TODO

	return Result;
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
