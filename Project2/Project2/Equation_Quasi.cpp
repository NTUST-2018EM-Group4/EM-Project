#include "Equation.h"

#define THRESHOLD 1e-6
#define TIME 100

using namespace std;

System::String ^ Equation::Quasi()
{
	System::String^ Result = "Quasi: " + this->getSystemString();

	stringstream ss;

	// Initial
	Vector X, preX;

	X = this->init;
	preX = X;

	// Initial F(x) F(x-1)
	double Fx = this->f(X, name);
	double preFx = Fx - 1;

	// Initial mimicInvH is Identity Matrix
	Matrix mimicInvH;
	mimicInvH.Data.resize(dim);
	for (int i = 0; i < dim; i++)
	{
		// mimicInvH[i].Data.resize(dim);
		for (int j = 0; j < dim; j++)
		{
			if (i == j)	mimicInvH.Data[i].push_back(1);
			else mimicInvH.Data[i].push_back(0);
		}
	}

	Vector deltaX, g;

	int time = 1;
	while (time++ <= TIME)
	{
		preX = X;
		Vector gradV = this->gradient(preX);
		Matrix gradM;
		gradM.push_back(gradV);

		// stop loop if g(k) = 0
		if (gradV.Norm() == 0) break;

		// cal d(k) = ¡ÐHk * g(k)
		Matrix d = mimicInvH * gradM.trans();
		d = d.trans();
		d = d * -1;

		/*
		// cal a(k) = - (g(k)^T * d(k)) /(d(0)^T * Q * d(0))
		//				|    tempM1   | |       tempM2     |
		Matrix tempM1 = gradM * d.trans();
		Matrix tempM2 = d * this->hessian(X) * d.trans();
		double a = tempM1[0][0] / tempM2[0][0];
		a = a * -1;
		*/

		// cal a(k)
		double tempD, step;
		Vector a;
		a.push_back(1);
		step = a[0];

		Vector tempX = X + a * d[0];
			
		while ((tempD = this->f(tempX, name)) < Fx)
		{
			Fx = tempD;
			a[0] += step;
			tempX = X + Vector(a) * d[0];
		}
		while ((tempD = this->f(tempX, name)) - Fx > THRESHOLD || isnan(tempD))
		{
			a[0] -= step;
			step *= 0.1;
			a[0] += step;
			tempX = X + Vector(a) * d[0];
			while ((tempD = this->f(tempX, name)) < Fx)
			{
				Fx = tempD;
				a[0] += step;
				tempX = X + Vector(a) * d[0];
			}
		}
		a[0] -= step;

		// deltaX = delta x(k) = a(k) * d(k)
		deltaX = d.Data[0] * a;

		// x(k+1) = x(k) + deltaX
		X = preX + deltaX;

		// cal new mimicInvH
		Matrix stepM;
		stepM.push_back(deltaX);
		Matrix newGradM;
		newGradM.push_back(this->gradient(X));

		// ERROR HANDLE : if NaN
		while (isnan(newGradM[0][0]))
		{
			deltaX = deltaX * 0.9;
			X = preX + deltaX;

			newGradM[0] = this->gradient(X);
		}

		// H(k+1) = H(k) + (deltaX * deltaX^T / deltaX^T * deltaG)
		//				   |   tempM1   |   |    tempM2    |

		//				 - (([H(k) * deltaG] * [H(k) * deltaG]^T) / (deltaG^T * H(k) * deltaG^T))
		//				   |	 tempM1    |		tempM1	    |	|          tempM2			|
		Matrix deltaG = newGradM - gradM;
		Matrix tempM1 = stepM.trans() * stepM;
		Matrix tempM2 = stepM * deltaG.trans();

		mimicInvH = mimicInvH + (tempM1 * (1 / tempM2[0][0]));

		tempM1 = mimicInvH * deltaG.trans();
		tempM1 = tempM1 * tempM1.trans();
		tempM2 = deltaG * mimicInvH * deltaG.trans();

		mimicInvH = mimicInvH - (tempM1 * (1 / tempM2[0][0]));

		// stop loop
		if (abs((X - preX).Norm()) <= THRESHOLD) break;

		ss << "------------------------------" << endl;
		mimicInvH.Name = "Hessian(" + to_string(time) + ")";
		ss << mimicInvH.outputStdStr() << endl;
		X.Name = "X" + to_string(time);
		ss << X.outputStdStr() << endl;
	}

	ss << "-----------Result-----------" << endl;
	X.Name = "X" + to_string(time);
	ss << X.outputStdStr() << endl;
	ss << "f(" << X.Name << ") = " << f(X, name) << endl;

	Result += ssTo_String(ss);

	return Result;
}