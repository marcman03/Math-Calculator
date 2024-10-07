#include "racional.hpp"

int mcd(int n1, int n2)
//Pre: Cert
//Post: Retorna el màxim comú divisor de n1 i n2
//Cost: Cost logarítmic log(min(n1,n2))
{
	if (n2 != 0) {
		return mcd(n2, n1%n2);
	}
	else {
		return n1;
	}
}

int mcm(int n1, int n2)
//Pre: Cert
//Post: Retorna el mínim comú múltiple
//Cost: Cost logarítmic log(min(n1,n2))
{
	int max = std::max(n1,n2);
	int min = std::min(n1,n2);
	int aux = (max/mcd(max,min))*min;
	return aux;
	
}

racional::racional (int n, int d) throw(error)
//Pre: Cert
//Post: Retorna el racional simplificat del racional on n és el numerador i d és el denominador del racional no simplificat. Si d == 0 retorna error(DenominadorZero)
//Cost: Cost constant (1)
{
	if (d != 0) {
		if (d < 0) {
			d = d*-1;
			n = n*-1;
		}
		int m = mcd(n,d);
		if (m < 0) {
			m = m*-1;
		}
		if (m != 1) {
			n = n/m;
			d = d/m;
		}
		_num = n;
		_den = d;
	}
	else {
		throw error(DenominadorZero);
	}
}  

// Constructora per còpia, assignació i destructora.
racional::racional(const racional & r) throw(error)
//Pre: Cert
//Post: Crea la còpia del racional r
//Cost: Cost constant (1)
{
	_num = r._num;
	_den = r._den;
}

racional & racional::operator=(const racional & r) throw(error)
//Pre: Cert
//Post: Retorna la còpia del racional r
//Cost: Cost constant (1)
{
	_num = r._num;
	_den = r._den;
	return *this;
}

racional::~racional() throw()
//Pre: Cert
//Post: Destrueix el racional
//Cost: Cost constant (1)
{
}

int racional::num() const throw()
//Pre: Cert
//Post: Retorna el numerador del racional implícit
//Cost: Cost constant (1)
{
	return _num;
}

int racional::denom() const throw()
//Pre: Cert
//Post: Retorna el denominador del racional implícit
//Cost: Cost constant (1)
{
	return _den;
}

int racional::part_entera() const throw()
//Pre: Cert
//Post: Retorna la part entera del racional implícit 
//Cost: Cost constant (1)
{
 	int entera = _num/_den;
	if (_num < 0 and _num % _den != 0) {
		entera += -1;
	}
	return entera;
}

racional racional::residu() const throw()
//Pre: Cert
//Post: Retorna el residu del racional implícit
//Cost: Cost constant (1)
{
	racional entera (part_entera(), 1);
	racional res = *this - entera;
	return res;
}

racional racional::operator+(const racional & r) const throw(error)
//Pre: Cert
//Post: Retorna el racional simplificat de la suma del racional implícit més el racional r 
//Cost: Cost constant (1)
{
	int n,d;
	if (_den == r._den) {
		n = _num + r._num;
		d = _den;
	}
	else {
		int aux = mcm(_den,r._den);
		n = _num*(aux/_den)+r._num*(aux/r._den);
		d = aux;
	}
	racional res(n,d);
	return res;
}

racional racional::operator-(const racional & r) const throw(error)
//Pre: Cert
//Post: Retorna el racional simplificat de la resta del racional implícit menys el racional r   
//Cost: Cost constant (1)
{
	int n,d;
	if (_den == r._den) {
		n = _num - r._num;
		d = _den;
	}
	else {
		int aux = mcm(_den,r._den);
		n = _num*(aux/_den)-r._num*(aux/r._den);
		d = aux;
	}
	racional res(n,d);
	return res;
}

racional racional::operator*(const racional & r) const throw(error)
//Pre: Cert
//Post: Retorna el racional simplificat de la multiplicació del racional implícit per el racional r  
//Cost: Cost constant (1)
{
	int n = _num * r._num;
	int d = _den * r._den;
	racional res(n,d);
	return res;
}

racional racional::operator/(const racional & r) const throw(error)
//Pre: Cert
//Post: Retorna el racional simplificat de la divisió del racional implícit entre el racional r   
//Cost: Cost constant (1)
{
	int n = _num * r._den;
	int d = _den * r._num;
	racional res(n,d);
	return res;
}

bool racional::operator==(const racional & r) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si el racional implicit és igual al racional r i retorna un boolea == false si no ho són   
//Cost: Cost constant (1)
{
	bool igual = false;
	if (_num == r._num and _den == r._den) {
		igual = true;
	}
	return igual;
}

bool racional::operator!=(const racional & r) const throw()
//Pre: Cert
//Post: Retorna un boolea == false si el racional implicit és igual al racional r i retorna un boolea == true si no ho són 
//Cost: Cost constant (1)
{
	return not (*this==r);
}

bool racional::operator<(const racional & r) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si el racional implícit és menor que el racional r i retorna un boolea == false si el racional implícit és major o igual que el racional r  
//Cost: Cost constant (1)
{
	if (_num < 0 and r._num >= 0) {
		return true;
	}
	if (_num >= 0 and r._num < 0) {
		return false;
	}
	if (_num < 0 and r._num < 0) {
		racional copia1 (_num*-1, _den);
		racional copia2 (r._num*-1, r._den);
		return (copia1 > copia2);
	}
	long aux = mcm(_den,r._den);
	long n1 = _num * aux/_den;
	long n2 = r._num * aux/r._den;
	return (n1 < n2);
}

bool racional::operator<=(const racional & r) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si el racional implícit és menor o igual que el racional r i retorna un boolea == false si el racional implícit és major que el racional r  
//Cost: Cost constant (1)
{
	return not (*this > r);
}

bool racional::operator>(const racional & r) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si el racional implícit és major que el racional r i retorna un boolea == false si el racional implícit és menor o igual que el racional r  
//Cost: Cost constant (1)
{
	
	if (_num < 0 and r._num >= 0) {
		return false;
	}
	if (_num >= 0 and r._num < 0) {
		return true;
	}
	if (_num < 0 and r._num < 0) {
		racional copia1 (_num*-1, _den);
		racional copia2 (r._num*-1, r._den);
		return (copia1 < copia2);
	}
	bool igual = false;
	long aux = mcm(_den,r._den);
	long n1 = _num * aux/_den;
	long n2 = r._num * aux/r._den;
	if (n1 > n2) {
		igual = true;
	}
	return igual;
}

bool racional::operator>=(const racional & r) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si el racional implícit és major o igual que el racional r i retorna un boolea == false si el racional implícit és menor que el racional r  
//Cost: Cost constant (1)
{
	return not (*this < r);
}	
