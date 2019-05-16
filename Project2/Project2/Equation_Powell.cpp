#include "Equation.h"

// #define DEBUG_TESTDATA
#define PHI  ((1 + sqrt(5)) / 2)  // 0.618...
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

	// TODO

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
	std::vector<std::string> xName;
	xName.push_back(name);

	Vector xVec;
	xVec.Data.push_back(x);

	Vector oriVec;
	oriVec.Data.push_back(b);

	// x4點的函式值如圖中f4b所示時
	if (this->f(xVec,xName) < this->f(oriVec,xName))
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