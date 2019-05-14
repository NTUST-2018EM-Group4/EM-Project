#include "Equation.h"

Equation::Equation()
{
	formula = "";
	postFormula.resize(0);
}

Equation::Equation(std::string formula)
{
	this->formula = formula;
	this->postFormula = inToPostfix();
}

// Normalization Formula and convert to Postfix
// ex. x^2+x-2*x^0.5 -> x ^ 2 + x - 2 * x ^ 0.5
std::vector<std::string> Equation::inToPostfix()
{
	std::string op[OPSIZE + 2] = { "+", "-", "*", "^", "(", ")", "sin", "cos" };
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

System::String ^ Equation::FormulaOutputStr()
{
	System::String^ Formula = gcnew System::String(formula.c_str());
	Formula += System::Environment::NewLine;
	return Formula;
}

double Equation::Calculate()
{
	// TODO
	return 0.0;
}

System::String ^ Equation::Powell()
{
	// TODO
	return this->FormulaOutputStr();
}

System::String ^ Equation::Newton()
{
	// TODO
	return this->FormulaOutputStr();
}

System::String ^ Equation::Step()
{
	// TODO
	return this->FormulaOutputStr();
}

System::String ^ Equation::Quasi()
{
	// TODO
	return this->FormulaOutputStr();
}

System::String ^ Equation::Conjuate()
{
	// TODO
	return this->FormulaOutputStr();
}


int priority(System::String^ op)
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

int priority(std::string op)
{
	System::String^ temp = gcnew System::String(op.c_str());
	return priority(temp);
}