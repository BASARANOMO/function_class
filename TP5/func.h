#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <map>

using namespace std;

typedef float (*PtrFun)(float);

class Fonction {
public:
	virtual ~Fonction();
	virtual float operator() (float x) const = 0;
	virtual Fonction* derivee() const = 0;
	float inverse(float y) const;
	virtual Fonction* clone() const = 0;
};

class Polynome : public Fonction {
private:
	vector<float> coeffs;  // coeff1 + coeff2 * x + coeff3 * x^2 + ... + coeffn * x^(n-1) + ...

public:
	Polynome() {};
	Polynome(vector<float>);
	~Polynome();  // virtual
	float operator() (float x) const;
	Fonction* derivee() const;
	Fonction* clone() const;
};

class Affine : public Polynome {
private:
	float coeffA;
	float coeffB;

public:
	Affine(float, float);
	~Affine();  // virtual
	float operator() (float x) const;
	Fonction* derivee() const;
	Fonction* clone() const;
};

class Trigo : public Fonction {
private:
	string trigoType;
	map<string, PtrFun> TrigoFuncTab;
public:
	Trigo(string);
	Trigo(const Trigo&);
	~Trigo();  // virtual
	float operator() (float x) const;
	Fonction* derivee() const;
	Fonction* clone() const;
};


class Derivee : public Fonction {
private:
	Fonction* integrale;
public:
	Derivee(Fonction*);
	~Derivee();
	float operator() (float x) const;
	Fonction* derivee() const;
	Fonction* clone() const;
};