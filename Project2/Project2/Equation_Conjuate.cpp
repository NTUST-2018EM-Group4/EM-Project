#include "Equation.h"

#define TIME 100
#define THRESHOLD 1e-6
using namespace std;

System::String ^ Equation::Conjuate()
{
	System::String^ Result = "Conjuate: " + this->getSystemString();
	double preFx, beta, alpha;
	Vector preX, preS, S, X;
	
	Matrix gradient, preGradient;
	
	//step 1
	preX = this->init;
	preFx = this->f(preX, this->name);
	//step 2 if
	S = this->gradient() * -1;
	vector<Vector> vectorT;
	vectorT.push_back(S);
	gradient = Matrix("g", vectorT);

	for (int time = 0; time < TIME; time++)
	{
		//step 2 else
		//get beta
		Matrix matrixTemp = gradient.trans() * gradient;
		beta = matrixTemp[0][0];
		matrixTemp = preGradient.trans() * preGradient;
		beta /= matrixTemp[0][0];

		S = S * -1 + preS * beta;
		
		//step 2 endif
		//get alpha
		
		//todo

		X = preX + S * alpha;

		//step 3
		if (abs(this->f(X,this->name) - preFx) <= THRESHOLD)
			break;

		//store X,S
		preFx = this->f(X, this->name);
		preS = S;
		preX = X;
	}

	return Result;
}