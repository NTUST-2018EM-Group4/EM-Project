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

	// b > a�A�k�b�϶����׸��j
	if (c - b > b - a)
	{
		// x4�w���b�k�b�϶�
		x = b + RESPHI * (c - b);
	}

	// b <= a�A���b�϶����׸��j
	else
	{
		// x4�w���b���b�϶�
		x = b - RESPHI * (b - a);
	}

	// �P�_�O�_�F�즬�ı���
	if (abs(c - a) < tau * (abs(b) + abs(x)))
	{
		// �F�즬�ı���A���϶����ת��@�b�@�����p���I��X
		return (c + a) / 2;
	}

	// ���F�즬�ı���A�~��j�M 
	std::vector<std::string> xName;
	xName.push_back(name);

	Vector xVec;
	xVec.Data.push_back(x);

	Vector oriVec;
	oriVec.Data.push_back(b);

	// x4�I���禡�Ȧp�Ϥ�f4b�ҥܮ�
	if (this->f(xVec,xName) < this->f(oriVec,xName))
	{
		// b > a�A�k�b�϶����׸��j
		if (c - b > b - a)
		{
			// �Hb�Ax�Ac�@���s�T�I�A�~��j�M
			return this->goldenSearch(name, b, x, c, tau);
		}
		// b <= a�A���b�϶����׸��j
		else
		{
			// �Ha�Ax�Ab�@���s�T�I�A�~��j�M
			return this->goldenSearch(name, a, x, b, tau);
		}
	}
	// x4�I���禡�Ȧp�Ϥ�f4a�ҥܮ�
	else
	{
		// b > a�A�k�b�϶����׸��j
		if (c - b > b - a)
		{
			// �Ha�Ab�Ax�@���s�T�I�A�~��j�M
			return this->goldenSearch(name, a, b, x, tau);
		}
		// b <= a�A���b�϶����׸��j
		else
		{
			// �Hx�Ab�Ac�@���s�T�I�A�~��j�M
			return this->goldenSearch(name, x, b, c, tau);
		}
	}
}