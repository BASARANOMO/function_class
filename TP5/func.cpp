#include "func.h"

Fonction::~Fonction() {
	cout << "~Fonction" << endl;
}

float Fonction::inverse(float y) const {
	float xPrev = 1.0;
	float xCurr;
	float delta = 1.0;
	int i = 1;
	while ((delta > 1e-5) && (i < 100)) {
		xCurr = xPrev + (y - (*this)(xPrev)) / (*(this)->derivee())(xPrev);
		delta = abs(xCurr - xPrev);
		xPrev = xCurr;
		i++;
	}
	return xPrev;
}

Polynome::Polynome(vector<float> vecCoeffs) {
	vector<float>::const_iterator it = vecCoeffs.begin();
	for (; it != vecCoeffs.end(); ++it) {
		coeffs.push_back(*it);
	}
}

Polynome::~Polynome() {
	cout << "~Polynome" << endl;
}

float Polynome::operator() (float x) const {
	float res = 0;
	int i = 0;
	vector<float>::const_iterator it = coeffs.begin();
	for (; it != coeffs.end(); ++it) {
		res += (*it) * pow(x, i);
		i++;
	}
	return res;
}

Fonction* Polynome::derivee() const {
	vector<float> newCoeffs;
	if (coeffs.size() <= 1) {
		newCoeffs.push_back(0);
		return new Polynome(newCoeffs);
	}

	vector<float>::const_iterator it = coeffs.begin();
	++it;
	int i = 1;
	for (; it != coeffs.end(); ++it) {
		newCoeffs.push_back((*it) * i);
		i++;
	}
	return new Polynome(newCoeffs);
}

Fonction* Polynome::clone() const {
	return new Polynome(*this);
}

Affine::Affine(float a, float b) : Polynome() {
	coeffA = a;
	coeffB = b;
}

Affine::~Affine() {
	cout << "~Affine" << endl;
}

float Affine::operator() (float x) const {
	return (coeffA * x + coeffB);
}

Fonction* Affine::derivee() const {
	vector<float> newCoeffs;
	newCoeffs.push_back(coeffA);
	return new Polynome(newCoeffs);
}

Fonction* Affine::clone() const {
	return new Affine(*this);
}

Trigo::Trigo(string str) {
	trigoType = str;
	TrigoFuncTab["sin"] = sin;
	TrigoFuncTab["cos"] = cos;
	TrigoFuncTab["tan"] = tan;
}

Trigo::Trigo(const Trigo& trigoFunc) {
	trigoType = trigoFunc.trigoType;
	TrigoFuncTab["sin"] = sin;
	TrigoFuncTab["cos"] = cos;
	TrigoFuncTab["tan"] = tan;
}

Trigo::~Trigo() {
	TrigoFuncTab.clear();
	cout << "~Trigo" << endl;
}

float Trigo::operator() (float x) const {
	return TrigoFuncTab.at(trigoType)((float)x);
}

Fonction* Trigo::derivee() const {
	return new Derivee(this);
}

Fonction* Trigo::clone() const {
	return new Trigo(*this);
}

Derivee::Derivee(const Fonction* fonc) {

	integrale = fonc->clone();
}

Derivee::~Derivee() {
	delete integrale;
	cout << "~Derivee" << endl;
}

float Derivee::operator() (float x) const {
	float epsilon = 0.01;
	return ((*integrale)(x + epsilon) - (*integrale)(x - epsilon)) / (2 * epsilon);
}

Fonction* Derivee::derivee() const {
	return new Derivee(this);
}

Fonction* Derivee::clone() const {
	return new Derivee(this->integrale);
}