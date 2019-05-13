#include <iostream>
#include <string>
#include <vector>
#include "Term.h"
#include "Node.h"
//#define DEBUG
using namespace std;

int getVarsIndex(string& s, int index)
{
	for (int i = index; i < s.length(); i++)
	{
		if (s[i] != '+' && s[i] != '-' && s[i] != '*' \
			&& s[i] != '^' && s[i] > '9')
			return i;
	}
	return -1;
}

/*void createNode(string buf, Node& n)
{
	if (buf == "+" && buf == "-" && buf == "*" && buf == "^")
	{
	}
	else if (buf == "cos" && buf == "sin")
	{
	}
	else if ('0' <= buf[0] && buf[0] <= '9')
	{
		//num
	}
	else
	{
		//vars
	}
	return;
}
*/
/*
int main()
{
	string buf;
	Node root;
	cin >> buf;		//operator
	root.type = 2;	//+-
	root.Operator = buf;

	while (cin >> buf)
	{
		if (buf == "\n")
			break;
		else
		{
			createNode(buf, root);
		}
	}
	cin >> buf;
	return 0;
}*/


int main()
{
	string buf;
	vector<string> stringTerm;
	vector<Term> poly;
	double lo, hi;
	cin >> buf;

	//split input from "+-"
	for (int i = 0; i < buf.size()+1; i++)
	{
		if (buf[i] == '+' || buf[i] == '-' || buf[i] == 0)
		{
			string temp = buf.substr(0, i);
			if (temp != "")
				stringTerm.push_back(temp);
			buf.erase(0, i);
			i = 0;
		}
	}

#ifdef DEBUG
	cout << "split" << endl;
	for (int i = 0; i < stringTerm.size(); i++)
	{
		cout << stringTerm[i] << " ";
	}
	cout << endl;
#endif // DEBUG

	//get polynomial
	for (int i = 0; i < stringTerm.size(); i++)
	{
		int index, index1, count;
		double Coef = 0;
		string Name;
		double Exp;
		vector<Variable> tempVars;

		//constant
		if (getVarsIndex(stringTerm[i], 0) == -1)	//not found variable
		{
			Coef = stod(stringTerm[i]);
			Term Const(Coef);
			poly.push_back(Const);
		}
		//variable
		else
		{
			//normaliztion
			for (int j = 0; j < stringTerm[i].length(); j++)
			{
				index = getVarsIndex(stringTerm[i], j);
				if (index == -1)
					break;
				if (index == 0 || stringTerm[i][index - 1] != '*')
				{
					stringTerm[i].insert(index, "1*");
					index += 2;
					j = index;
				}
				if (stringTerm[i][index + 1] != '^')
				{
					stringTerm[i].insert(index + 1, "^1");
					j = index + 2;
				}
			}
#ifdef DEBUG
			//cout << "normalization" << endl;
			//cout << stringTerm[i] << endl;
#endif // DEBUG

			//get coef
			index = stringTerm[i].find('*');
			Coef = stod(stringTerm[i].substr(0, index));
			stringTerm[i].erase(0, index + 1);	//+1 to erase '*'
			//get vars
			for (int j = 0; j < stringTerm[i].length(); j++)
			{
				index = stringTerm[i].find('^');
				index1 = stringTerm[i].find('*');
				Name = stringTerm[i].substr(0, index);
				count = (index1 == string::npos) ? 50 : index1 - index;	//50可替換成任意很大的數
				Exp = stod(stringTerm[i].substr(index + 1, count));	//+1 to skip ^	// pos is within bounds, pos+count is not, returns [pos, size())
				stringTerm[i].erase(0, index + count + 1);	//+1 to erase '^'
				Variable Vars(Name,Exp);
				tempVars.push_back(Vars);
			}
			Term temp(Coef, tempVars);
			poly.push_back(temp);
#ifdef DEBUG
			cout << "final" << endl;
			cout << Coef;
			for (int j = 0; j < temp.vars.size(); j++)
			{
				cout << "*" << temp.vars[j].name << "^" << temp.vars[j].exp;
			}
			cout << endl;
#endif // DEBUG

		}
	}

	//golden


	//reset
	stringTerm.clear();

	cin >> buf;
	return 0;
}