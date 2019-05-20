#include "Equation.h"

#define TIME 50 // N
#define THRESHOLD 1e-6

using namespace std;

System::String ^ Equation::Conjuate()
{
	System::String^ Result = "Conjuate: " + this->getSystemString();

	stringstream ss;

	double preFx, Fx, beta;

	Vector preX, X;
	Vector preS, S;
	
	Matrix gradM, preGradM;
	
	// Choose X0
	X = this->init;
	X.Name = "X0";
	// Store Value f(X0)
	Fx = this->f(X, this->name);

	ss << "------------------------------" << endl;
	ss << X.outputStdStr() << endl;

	// initial S
	S = this->gradient(X) * -1;
	preS = S;
	gradM.Data.clear();
	gradM.Data.push_back(this->gradient(X));
	gradM.Name = "S0";

	for (int time = 0; time < TIME; time++)
	{
		ss << "------------------------------" << endl;
		ss << "i = " << time << endl;

		// Find alpha
		Equation tempEqu = *this;
		double maxBegin = INT16_MIN;
		double minEnd = INT16_MAX;
		vector<Equation> list;

		Vector alpha;
		alpha.Name = "a" + std::to_string(time);

		// Create alter equation
		for (int k = 0; k < dim; k++)
		{
			// ex.val = 0.5+(a*1)
			std::string val = "";

			if (X.Data[k] < 0) val += "(0" + std::to_string(X.Data[k]) + ")";
			else val += std::to_string(X.Data[k]);

			val += "+(" + alpha.Name + "*";

			if (S.Data[k] < 0) val += "(0" + std::to_string(S.Data[k]) + ")";
			else val += std::to_string(S.Data[k]);

			val += ")";
			// alter
			tempEqu.setFormula(tempEqu.alterFormula(name[k], val));
			// save this equation
			list.push_back(Equation(val, 1));

			// if this dim is used
			if (S.Data[k] != 0)
			{
				// determine interval

				double intervalFix = X.Data[k] / S.Data[k];
				double tempBegin, tempEnd;

				switch (k)
				{
				case 0:
					tempBegin = (xInterval[0] - X.Data[k]) / S.Data[k];
					tempEnd = (xInterval[1] - X.Data[k]) / S.Data[k];
					break;
				case 1:
					tempBegin = (yInterval[0] - X.Data[k]) / S.Data[k];
					tempEnd = (yInterval[1] - X.Data[k]) / S.Data[k];
					break;
				default:
					break;
				}

				if (S.Data[k] < 0) std::swap(tempBegin, tempEnd);

				if (tempBegin > maxBegin) maxBegin = tempBegin;
				if (tempEnd < minEnd) minEnd = tempEnd;
			}
		}
		
		// Calculate alpha
		alpha.Data.clear();
		Matrix tempG, tempS, tempM, h;
		vector<Vector> t;
		t.clear();
		t.push_back(this->gradient(X));
		tempG = Matrix("G", t);
		t.clear();
		t.push_back(preS);
		tempS = Matrix("S", t);
		tempS = tempS.trans();	//轉直的
		
		tempM = tempG * tempS;	//1*2 * 2*1
		double tempDouble = -tempM[0][0];
		h = this->hessian(X);
		tempM = tempS.trans() * h * tempS;
		tempDouble /= tempM[0][0];
		alpha.Data.push_back(tempDouble);
		
		// Calculate newX
		Vector newX;
		newX.Name = "X" + std::to_string(time + 1);
		newX.Data.clear();

		for (int k = 0; k < dim; k++)
		{
			newX.Data.push_back(list[k].f(alpha.Data[0], alpha.Name));
		}
		
		//  Calculate beta
		t.clear();
		t.push_back(this->gradient(newX));
		tempG = Matrix("G", t);
		t.clear();
		t.push_back(preS);
		tempS = Matrix("S", t);
		tempS = tempS.trans();	//轉直的

		tempM = tempG * tempS;	//1*2 * 2*1
		tempDouble = -tempM[0][0];
		h = this->hessian(X);
		tempM = tempS.trans() * h * tempS;
		tempDouble /= tempM[0][0];
		beta = tempDouble;
		
		S = this->gradient(newX) * -1;
		S = S + preS * beta;
		S.Name = "S" + to_string(time);

		//output
		if (time != 0)
			ss << "beta = [" << beta << "]" << endl;
		ss << S.outputStdStr() << endl;
		ss << alpha.outputStdStr() << endl;
		ss << newX.outputStdStr() << endl;

		Fx = this->f(X, this->name);

		// function not decreasing
		if (abs(Fx - preFx) <= THRESHOLD && time != 0) break;

		// continue loop
		
		preX = X;
		X = newX;

		preGradM = gradM;
		preS = S;
		preFx = Fx;
	}

	ss << "-----------Result-----------" << endl;
	ss << X.outputStdStr() << endl;
	ss << "f(" << X.Name << ") = " << Fx << endl;
	
	Result += ssTo_String(ss);

	return Result;
}