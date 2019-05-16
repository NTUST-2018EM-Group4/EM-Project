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

	// b > a�A�k�b�϶����׸��j
	if (para.end - para.init > para.init - para.begin)
	{
		// x4�w���b�k�b�϶�
		x = para.init + RESPHI * (para.end - para.init);
	}

	// b <= a�A���b�϶����׸��j
	else
	{
		// x4�w���b���b�϶�
		x = para.init - RESPHI * (para.init - para.begin);
	}

	// �P�_�O�_�F�즬�ı���
	if (abs(para.end - para.begin) < tau * (abs(para.init) + abs(x)))
	{
		// �F�즬�ı���A���϶����ת��@�b�@�����p���I��X
		return (para.end + para.begin) / 2;
	}
	std::vector<Parameter> x4Para;
	x4Para.push_back(Parameter(para.name, x));

	std::vector<Parameter> paras;
	paras.push_back(para);
	// ���F�즬�ı���A�~��j�M 

	// x4�I���禡�Ȧp�Ϥ�f4b�ҥܮ�
	if (this->f(x4Para) < this->f(paras))
	{
		// b > a�A�k�b�϶����׸��j
		if (para.end - para.init > para.init - para.begin)
		{
			// �Hx2�Ax4�Ax3�@���s�T�I�A�~��j�M
			return this->goldenSearch(Parameter(para.name, para.init, x, para.end), tau);
		}
		// b <= a�A���b�϶����׸��j
		else
		{
			// �Hx1�Ax4�Ax2�@���s�T�I�A�~��j�M
			return this->goldenSearch(Parameter(para.name, para.begin, x, para.init), tau);
		}
	}
	// x4�I���禡�Ȧp�Ϥ�f4a�ҥܮ�
	else
	{
		// b > a�A�k�b�϶����׸��j
		if (para.end - para.init > para.init - para.begin)
		{
			// �Hx1�Ax2�Ax4�@���s�T�I�A�~��j�M
			return this->goldenSearch(Parameter(para.name, para.begin, para.init, x), tau);
		}
		// b <= a�A���b�϶����׸��j
		else
		{
			// �Hx4�Ax2�Ax3�@���s�T�I�A�~��j�M
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