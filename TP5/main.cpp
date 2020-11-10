#include "func.h"
#include <iomanip>


#define M_PI 3.14159265358979323846

int main(int argc, char** argv) {

	vector<float> vec{0, 0, 0, 1};
	Polynome polyFunc(vec);
	cout << right << setw(15) << "27^(1/3) = " << polyFunc.inverse(27) << endl;

	Trigo tanFunc("tan");
	cout << right << setw(15) << "4 * atan(1) = " << tanFunc.inverse(1) * 4 << endl;


	Fonction* ptrFunc1;
	ptrFunc1 = tanFunc.derivee();
	cout << right << setw(15) << "tan'(pi/4) = " << (*ptrFunc1)(M_PI / 4) << endl;

	Fonction* ptrFunc2;
	ptrFunc2 = (*ptrFunc1).derivee();
	cout << right << setw(15) << "tan''(pi/4) = " << (*ptrFunc2)(M_PI / 4) << endl;

	delete ptrFunc1;
	delete ptrFunc2;
	//exit
	return 0;
}