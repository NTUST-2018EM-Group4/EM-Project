#include "Equation.h"

#define PHI  (1 + sqrt(5)) / 2  // 0.618...
#define RESPHI  2 - PHI			// 0.382...
#define THRESHOLD 1e-8

// Golden section search.
// @author Darran Zhang @ codelast.com
// @param x1  The left bound of current bounds.
// @param x2  An interior point between (x1, x3).
// @param x3  The right bound of current bounds.
// @param tau The error tolerance to judge the convergence, recommended value is e^0.5, where e is is the required absolute precision of f(x).
double Equation::goldenSearch(Parameter para, double tau)
{
	double x;

	// b > a，右半區間長度較大
	if (para.end - para.init > para.init - para.begin)
	{
		// x4安插在右半區間
		x = para.init + RESPHI * (para.end - para.init);
	}

	// b <= a，左半區間長度較大
	else
	{
		// x4安插在左半區間
		x = para.init - RESPHI * (para.init - para.begin);
	}

	// 判斷是否達到收斂條件
	if (abs(para.end - para.begin) < tau * (abs(para.init) + abs(x)))
	{
		// 達到收斂條件，取區間長度的一半作為極小值點輸出
		return (para.end + para.begin) / 2;
	}
	std::vector<Parameter> x4Para;
	x4Para.push_back(Parameter(para.name, x));

	std::vector<Parameter> paras;
	paras.push_back(para);
	// 未達到收斂條件，繼續搜尋 

	// x4點的函式值如圖中f4b所示時
	if (this->f(x4Para) < this->f(paras))
	{
		// b > a，右半區間長度較大
		if (para.end - para.init > para.init - para.begin)
		{
			// 以x2，x4，x3作為新三點，繼續搜尋
			return this->goldenSearch(Parameter(para.name, para.init, x, para.end), tau);
		}
		// b <= a，左半區間長度較大
		else
		{
			// 以x1，x4，x2作為新三點，繼續搜尋
			return this->goldenSearch(Parameter(para.name, para.begin, x, para.init), tau);
		}
	}
	// x4點的函式值如圖中f4a所示時
	else
	{
		// b > a，右半區間長度較大
		if (para.end - para.init > para.init - para.begin)
		{
			// 以x1，x2，x4作為新三點，繼續搜尋
			return this->goldenSearch(Parameter(para.name, para.begin, para.init, x), tau);
		}
		// b <= a，左半區間長度較大
		else
		{
			// 以x4，x2，x3作為新三點，繼續搜尋
			return this->goldenSearch(Parameter(para.name, x, para.init, para.end), tau);
		}
	}
}

System::String ^ Equation::Powell(std::vector<Parameter> paras)
{
	System::String^ Result = "Powell: " + this->getSystemString();

	// initial unit vector
	std::vector<Vec> S = createUnitVectors(paras.size());
	std::vector<Vec> X;

	int j = 0;

	bool flag = true;
	do
	{
		j++;
		Result = Result + "j = " + j.ToString() + SYSENDL;

		Vec Xtemp;
		Xtemp.list = paras;

		X.push_back(Xtemp);

		for (int i = 1; i <= paras.size(); i++)
		{
			Result = Result + "i = " + i.ToString() + SYSENDL;
			Xtemp = X[i - 1] + (S[i - 1] * "a");
			Equation temp(this->formula, Xtemp.list);

			std::vector<Parameter> tempParas;


			for (int dim = 0; dim < S[i - 1].list.size(); dim++)
			{
				if (S[i - 1].list[dim].init != 0)
				{
					double intervalFix = X[i - 1].list[dim].init / S[i - 1].list[dim].init;

					Parameter temp = paras[i - 1];
					temp.begin = temp.begin - intervalFix;
					temp.end = temp.end - intervalFix;

					tempParas.push_back(temp);
				}
			}

			double maxBegin = INT16_MIN;
			double minEnd = INT16_MAX;
			for (int k = 0; k < tempParas.size(); k++)
			{
				if (tempParas[k].begin > maxBegin) maxBegin = tempParas[k].begin;
				if (tempParas[k].end < minEnd) minEnd = tempParas[k].end;
			}

			double a = temp.goldenSearch(Parameter("a", (maxBegin + minEnd) / 2, maxBegin, minEnd), pow(THRESHOLD, 0.5));



		}
	} while (flag);

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