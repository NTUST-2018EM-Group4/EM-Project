#include "Equation.h"

// #define DEBUG_TESTDATA
// #define DEBUG

#define PHI  ((1 + sqrt(5)) / 2)  // 1.618...
#define RESPHI  (2 - PHI)			// 0.382...
#define THRESHOLD 1e-8

System::String ^ Equation::Powell()
{
	System::String^ Result = "Powell: " + this->getSystemString();

#ifdef DEBUG_TESTDATA
	// test f(x,y)
	std::cout << this->f(init,name) << std::endl;

	// test f(a1+0.05,0.05)
	std::string tempFormula = this->alterFormula("x", "a+0.5");
	tempFormula = this->alterFormula(tempFormula, "y", "0.5");
	
	Equation testEqu = *this;
	testEqu.setFormula(tempFormula);

	std::cout << testEqu.formula << std::endl;
	std::cout << testEqu.goldenSearch("a", xInterval[0] - 0.5, ((xInterval[1] - xInterval[0]) / 2) - 0.5, xInterval[1] - 0.5, THRESHOLD)<< std::endl;
#endif // DEBUG_TESTDATA

	std::stringstream ss;
	// Initial
	std::vector<Vector> X(dim + 2);
	std::vector<Vector> S;
	std::vector<Vector> A(dim + 1);

	X[0] = init;
	X[0].Name = "X1";

	// Create unit vector
	for (int i = 0; i < dim; i++)
	{
		Vector tempVec;
		tempVec.Name = "S" + std::to_string(i + 1);
		for (int j = 0; j < dim; j++)
		{
			if (i == j)
			{
				tempVec.Data.push_back(1);
			}
			else
			{
				tempVec.Data.push_back(0);
			}
		}
		S.push_back(tempVec);
	}

#ifdef DEBUG
	double tempX0 = f(X[0], name);
#endif // DEBUG


	int j = 0;
	do
	{
		ss << "------------------------------" << std::endl;
		
		j++;
		ss << "j = " << j << std::endl;

		ss << X[0].outputStdStr() << std::endl;

		for (int i = 1; i <= dim + 1; i++)
		{
			ss << "i = " << i << std::endl;

			if (i == dim + 1)
			{
				Vector newS;
				for (int k = 0; k < dim; k++)
				{
					if (k == 0)
					{
						newS = S[k] * A[k].Data[k];
					}
					else
					{
						newS = newS + S[k] * A[k].Data[0];
					}
				}
				newS.Name = "S" + std::to_string(dim + 1);
				S.push_back(newS);
			}

			Equation tempEqu = *this;
			double maxBegin = INT16_MIN;
			double minEnd = INT16_MAX;
			std::vector<Equation> list;

			Vector alpha;
			alpha.Name = "a" + std::to_string(i);

			// Create alter equation
			for (int k = 0; k < dim; k++)
			{

				// ex.val = 0.5+(a*1)
				std::string val = "";

				if (X[i - 1].Data[k] < 0) val += "(0" + std::to_string(X[i - 1].Data[k]) + ")";
				else val += std::to_string(X[i - 1].Data[k]);

				val += "+(" + alpha.Name + "*";

				if (S[i - 1].Data[k] < 0) val += "(0" + std::to_string(S[i - 1].Data[k]) + ")";
				else val += std::to_string(S[i - 1].Data[k]);

				val += ")";
				// alter
				tempEqu.setFormula(tempEqu.alterFormula(name[k], val));
				// save this equation
				list.push_back(Equation(val, 1));

				// if this dim is used
				if (S[i - 1].Data[k] != 0)
				{
					// determine interval

					double intervalFix = X[i - 1].Data[k] / S[i - 1].Data[k];

					double tempBegin;
					double tempEnd;

					switch (k)
					{
					case 0:
						tempBegin = (xInterval[0] - X[i - 1].Data[k]) / S[i - 1].Data[k];
						tempEnd = (xInterval[1] - X[i - 1].Data[k]) / S[i - 1].Data[k];
						break;
					case 1:
						tempBegin = (yInterval[0] - X[i - 1].Data[k]) / S[i - 1].Data[k];
						tempEnd = (yInterval[1] - X[i - 1].Data[k]) / S[i - 1].Data[k];
						break;
					default:
						break;
					}

					if (S[i - 1].Data[k] < 0) std::swap(tempBegin, tempEnd);

					if (tempBegin > maxBegin) maxBegin = tempBegin;
					if (tempEnd < minEnd) minEnd = tempEnd;
				}
			}

			// Calculate alpha by Golden Section Search
			alpha.Data.push_back(tempEqu.goldenSearch(alpha.Name, maxBegin, (maxBegin + minEnd) / 2, minEnd, THRESHOLD));

			A[i - 1] = alpha;

			Vector newX;
			newX.Name = "X" + std::to_string(i + 1);

			for (int k = 0; k < dim; k++)
			{
				newX.Data.push_back(list[k].f(alpha.Data[0], alpha.Name));
			}
			X[i] = newX;

#ifdef DEBUG
			double tempXi = f(X[i], name);
#endif // DEBUG

			ss << X[i].outputStdStr() << std::endl;
		}

		ss << std::endl;
		ss << A[dim].outputStdStr() << std::endl;
		ss << S[dim].outputStdStr() << std::endl;

#ifdef DEBUG
		double test = f(X[dim + 1], name);
		double test2 = f(X[dim], name);
#endif // DEBUG

		if (abs(f(X[dim + 1], name) - f(X[dim], name)) > THRESHOLD)
		{
			Vector temp = X[dim + 1];
			temp.Name = "X1";
			X.clear();
			X.resize(dim + 2);
			X[0] = temp;

			S.erase(S.begin());
		}
		else
		{
			ss << "-----------Result-----------" << std::endl;
			ss << X[dim + 1].outputStdStr() << std::endl;
			ss << "f(" << X[dim + 1].Name << ") = " << f(X[dim + 1], name) << std::endl;
			break;
		}
	} while (true);

	Result += ssTo_String(ss);

	return Result;
}

// Golden section search.
// @author Darran Zhang @ codelast.com
// @param a  The left bound of current bounds.
// @param b  An interior point between (a, c).
// @param c  The right bound of current bounds.
// @param tau The error tolerance to judge the convergence, recommended value is e^0.5, where e is is the required absolute precision of f(x).
double Equation::goldenSearch(std::string name, double a, double b, double c, double tau)
{
	double x;
	double phi = PHI;

	// b > a，右半區間長度較大
	if (c - b > b - a)
	{
		// x4安插在右半區間
		x = b + RESPHI * (c - b);
	}

	// b <= a，左半區間長度較大
	else
	{
		// x4安插在左半區間
		x = b - RESPHI * (b - a);
	}

	// 判斷是否達到收斂條件
	if (abs(c - a) < tau * (abs(b) + abs(x)))
	{
		// 達到收斂條件，取區間長度的一半作為極小值點輸出
		return (c + a) / 2;
	}

	// 未達到收斂條件，繼續搜尋 
	
#ifdef DEBUG
	double fx = this->f(x, name);
	double fb = this->f(b, name);
#endif // DEBUG


	// x4點的函式值如圖中f4b所示時
	if (this->f(x, name) < this->f(b, name))
	{
		// b > a，右半區間長度較大
		if (c - b > b - a)
		{
			// 以b，x，c作為新三點，繼續搜尋
			return this->goldenSearch(name, b, x, c, tau);
		}
		// b <= a，左半區間長度較大
		else
		{
			// 以a，x，b作為新三點，繼續搜尋
			return this->goldenSearch(name, a, x, b, tau);
		}
	}
	// x4點的函式值如圖中f4a所示時
	else
	{
		// b > a，右半區間長度較大
		if (c - b > b - a)
		{
			// 以a，b，x作為新三點，繼續搜尋
			return this->goldenSearch(name, a, b, x, tau);
		}
		// b <= a，左半區間長度較大
		else
		{
			// 以x，b，c作為新三點，繼續搜尋
			return this->goldenSearch(name, x, b, c, tau);
		}
	}
}