#include "Equation.h"

#define TIME 50
#define THRESHOLD 1e-6
// #define DEBUG

using namespace std;

System::String ^ Equation::Steep()
{
	System::String^ Result = "Steep: " + this->getSystemString();

	vector<double> gradient;
	Vector Gradient;
	vector<Vector> t;
	Matrix G, hessian, matrixT, lamda;
	stringstream ss;
	for (int time = 0; time < TIME; time++)
	{
		//reset
		gradient.clear();
		t.clear();

		Gradient = this->gradient();	//get gradient

		//stopping check
		if (Gradient.Norm() <= THRESHOLD)
			break;

		Gradient = Gradient * -1;	//search direction = - gradient
		t.push_back(Gradient);
		G = Matrix("gradient", t);
		G = G.trans();	//轉直的
		hessian = this->hessian();	//get hessian
		matrixT = G.trans() * hessian * G;
		lamda = (G.trans() * G) * matrixT.inverse();	//get lamda
		t.clear();
		t.push_back(this->init);
		matrixT = Matrix("temp", t);
		G = G.trans();	//轉回來
		matrixT = matrixT + lamda * G;
		this->init = matrixT.Data[0];

		//output
		ss << "------------------------------" << endl;
		ss << "i = " << time << endl
			<< "h = " << G.outputStdStr() << endl
			<< "lambda = " << lamda.outputStdStr() << endl
			<< "X = " << matrixT.outputStdStr() << endl;
		
#ifdef DEBUG
		cout << "i = " << time << endl
			<< "h" << G.outputStdStr() << endl
			<< "lambda" << lamda.outputStdStr() << endl
			<< "X" << matrixT.outputStdStr() << endl;
#endif // DEBUG
	}

	//output
	ss << "-----------Result-----------" << endl;
	ss << "[";
	for (int i = 0; i < this->name.size(); i++)
	{
		if (i == 0)
			ss << this->name[i];
		else
			ss << "," << this->name[i];
	}
	ss << "]" << this->init.outputStdStr() << endl
		<< "min = " << this->f(this->init, this->name);
	Result += ssTo_String(ss);
	
	return Result;
}