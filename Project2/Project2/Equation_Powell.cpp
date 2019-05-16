#include "Equation.h"

#define DEBUG

System::String ^ Equation::Powell()
{
	System::String^ Result = "Powell: " + this->getSystemString();

	// TODO

#ifdef DEBUG
	// test f(x,y)
	std::cout << this->f(init,name) << std::endl;

	// test f(a1+0.05,0.05)
	std::string tempFormula = this->alterFormula("x", "a1+0.05");
	tempFormula = this->alterFormula(tempFormula, "y", "0.05");
	
	Equation testEqu = *this;
	testEqu.setFormula(tempFormula);

	std::cout << testEqu.formula << std::endl;
#endif // DEBUG

	return Result;
}