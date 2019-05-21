#include "Equation.h"
#define TIME 50
#define THRESHOLD 1e-5
using namespace std;

System::String ^ Equation::Newton()
{
	System::String^ Result = "Newton: " + this->getSystemString();

	Matrix hessian, gradient, X, nextX;
	vector<Vector> t;
	int flag;
	stringstream ss;

	for (int time = 0; time < TIME; time++)
	{
		
		
		//X
		t.clear();	//reset
		t.push_back(init);
		X = Matrix("X", t);
		X = X.trans();	//轉直的
		//gradient
		t.clear();	//reset
		t.push_back(this->gradient());
		gradient = Matrix("gradient", t);
		gradient = gradient.trans();	//轉直的

		hessian = this->hessian();	//get hessian
		hessian.Name = "";
		//output
		ss << "------------------------------" << endl;
		ss << "i = " << time << endl
			<< "Hessian" << hessian.outputStdStr() << endl;

		//hessian inverse
		hessian = hessian.inverse();
		hessian.Name = "";
		ss << "Hessian inverse" << hessian.outputStdStr() << endl;	//output

		nextX = X - hessian * gradient;	//nextX = X + deltaX(- hessian * gradient)
		nextX = nextX.trans();	//轉橫的
		//set X into boundary
		nextX[0][0] = (XhasRadical && nextX[0][0] < xInterval[0]) ? xInterval[0] + THRESHOLD : nextX[0][0];
		if (dim > 1 && YhasRadical)
		{
			nextX[0][1] = (nextX[0][1] < yInterval[0]) ? yInterval[0] + THRESHOLD : nextX[0][1];
		}

		X = X.trans();	//轉橫的
		init = nextX[0];
		nextX.Name = "";
		ss << "X" << nextX.outputStdStr() << endl;	//output
		//stopping check
		for (int i = 0; i < dim; i++)
		{
			if (0 < X[0][i] - nextX[0][i] && X[0][i] - nextX[0][i] < THRESHOLD)
				++flag;
		}
		if (flag == dim)
			break;
		flag = 0;
	}

	// output
	ss << "-----------Result-----------" << endl;
	ss << "[";
	for (int i = 0; i < dim; i++)
	{
		if (i == 0)
			ss << name[i];
		else
			ss << "," << name[i];
	}
	ss << "]" << init.outputStdStr() << endl
		<< "min = " << this->f(init, name);
	Result += ssTo_String(ss);

	return Result;
}