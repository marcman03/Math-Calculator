#include "token.hpp"

token::t::t()
//Pre: Cert
//Post: Inicialitza un racional
//Cost: Cost constant (1)
{
	_r = racional(0,1);
}

token::t::~t()
//Pre: Cert
//Post: Destrueix l'union t
//Cost: Cost constant (1)
{
}

bool token::operador(const token &t)
//Pre: Cert
//Post: Retorna un boolea == true si el token t és un operador i retorna un boolea == false si no ho és  
//Cost: Cost constant (1)
{
	if (t._c == SUMA or t._c == RESTA or t._c == MULTIPLICACIO or t._c == DIVISIO or t._c == EXPONENCIACIO or t._c == CANVI_DE_SIGNE or t._c == SIGNE_POSITIU) {
		return true;
	}
	return false;
}

bool comproba_string(const string & s) 
//Pre: Cert
//Post: Retorna un boolea == true si l'string s és un identificador vàlid per una variable i retorna un boolea == false si no ho és  
//Cost: Cost constant (1)
{
	bool correcte = false;
	if (s.size() != 0) {
		correcte = true;
		for (int i = 0; i < int(s.size()) and correcte; ++i) {
			if (s[i] < 65) {
				correcte = false;
			}
			else if (s[i] > 90 and s[i] < 97) {
				correcte = false;
			}
			else if (s[i] > 122) {
				correcte = false;
			}
			if (s[i] == 95) {
				correcte = true;
			}
		}
		if (s == "unassign" or s == "e" or s == "sqrt" or s == "log" or s == "exp" or s == "evalf") {
			correcte = false;
		}
	}	
	return correcte;
}

token::token(codi cod) throw(error)
//Pre: Cert
//Post: Crea un token copiant el codi cod si cod no és el codi d'un enter,un real, un racional o una variable. Si ho és retorna error(ConstructoraInadequada)  
//Cost: Cost constant (1)
{
	if (cod == CT_ENTERA or  cod == CT_RACIONAL or cod == CT_REAL or cod == VARIABLE) {
		throw error(ConstructoraInadequada);
	}
	_c = cod;
}

token::token(int n) throw(error)
//Pre: Cert
//Post: Crea un token de tipus enter, on el valor de l'enter és n 
//Cost: Cost constant (1)
{
	_t._i = n;
	_c = CT_ENTERA;
}

token::token (const racional & r) throw(error)
//Pre: Cert
//Post: Crea un token de tipus racional, on el valor del racional és r  
//Cost: Cost constant (1)
{
	_t._r = r;
	_c = CT_RACIONAL;
}

token::token(double x) throw(error)
//Pre: Cert
//Post: Crea un token de tipus real, on el valor del real és x  
//Cost: Cost constant (1)
{
	_t._d = x;
	_c = CT_REAL;
}

token::token(const string & var_name) throw(error)
//Pre: Cert
//Post: Crea un token de tipus real, on l'identificador de la variable és var_name, si var_name és un identificador vàlid. Si no ho és retorna error(IdentificadorIncorrecte)   
//Cost: Cost constant (1)
{	
	if(not comproba_string(var_name)) {
		throw error(IdentificadorIncorrecte);
	}	
	string copia = var_name;
	_t._s = new string (copia);
	_c = VARIABLE;
}

// Constructora por còpia, assignació i destructora.
token::token (const token & t) throw(error)
//Pre: Cert
//Post: Crea la còpia del token t  
//Cost: Cost constant (1)
{
	*this = t;
}

token & token::operator=(const token & t) throw(error)
//Pre: Cert
//Post: Retorna la copia del token t 
//Cost: Cost constant (1)
{
	_c = t._c;
	if (_c == CT_ENTERA) {
		_t._i = t._t._i;
	}
	else if (_c == CT_RACIONAL) {
		_t._r = t._t._r;
	}
	else if (_c == CT_REAL) {
		_t._d = t._t._d;
	}
	else if (t._c == VARIABLE) {
		string aux(*(t._t._s));
		delete t._t._s;
		_t._s = new string (aux);
	}
	return *this;
}

token::~token() throw()
//Pre: Cert
//Post:  Destrueix el token
//Cost: Cost constant (1)
{
	if (_c == VARIABLE) {
		delete _t._s;
	}
}

token::codi token::tipus() const throw()
//Pre: Cert
//Post: Retorna el codi del token implícit  
//Cost: Cost constant (1)
{
	return _c;
}

int token::valor_enter() const throw(error)
//Pre: Cert
//Post: Retorna el valor del token si el tipus del token és enter. Si no ho és retorna error(ConsultoraInadequada)
//Cost: Cost constant (1)
{
	if (_c != CT_ENTERA) {
		throw error(ConsultoraInadequada);
	}
	return _t._i;
}

racional token::valor_racional() const throw(error)
//Pre: Cert
//Post: Retorna el valor del token si el tipus del token és racional. Si no ho és retorna error(ConsultoraInadequada)
//Cost: Cost constant (1)
{
	if (_c != CT_RACIONAL) {
		throw error(ConsultoraInadequada);
	}
	return _t._r;
}

double token::valor_real() const throw(error)
//Pre: Cert
//Post: Retorna el valor del token si el tipus del token és real. Si no ho és retorna error(ConsultoraInadequada)
//Cost: Cost constant (1)
{
	if (_c != CT_REAL) {
		throw error(ConsultoraInadequada);
	}
	return _t._d;
}

string token::identificador_variable() const throw(error)
//Pre: Cert
//Post: Retorna el identificador del token si el tipus del token és variable. Si no ho és retorna error(ConsultoraInadequada)
//Cost: Cost constant (1)
{
	if (_c != VARIABLE) {
		throw error(ConsultoraInadequada);
	}	
	return *_t._s;	
}

bool token::operator==(const token & t) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si el token implícit és igual al token t i retorna un boolea == false si no ho són
//Cost: Cost constant (1)
{
	bool iguals = false;
	if (_c == t._c) {
		if (_c == CT_ENTERA) {
			if (_t._i == t._t._i) {
				iguals = true;
			}
		}
		else if (_c == CT_RACIONAL) {
			if (_t._r == t._t._r) {
				iguals = true;
			}
		}
		else if (_c == CT_REAL) {
			if (_t._d == t._t._d) {
				iguals = true;
			}
		}
		else if (_c == VARIABLE) {
			if (*_t._s == *t._t._s) {
				iguals = true;
			}
		}
		else {
			iguals = true;
		}
	}
	return iguals;
}

bool token::operator!=(const token & t) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si el token implícit no és igual al token t i retorna un boolea == false si ho són
//Cost: Cost constant (1)
{
	return not (*this == t);
}

bool token::operator>(const token & t) const throw(error)
//Pre: Cert
//Post: Retorna error(ProcedenciaEntreNoOperadors) si el token implícit o el token t no són operadors. Si ho són retorna un boolea == true si el token implícit té més prioritat que el token t i retorna un boolea == false si no té menys
//Cost: Cost constant (1)
{
	if (not operador(*this)) {
		throw error(PrecedenciaEntreNoOperadors);
	}
	if (not operador(t)) {
		throw error(PrecedenciaEntreNoOperadors);
	}
	bool major = false;
	if (_c == EXPONENCIACIO) {
		if (t._c != EXPONENCIACIO) {
			major = true;
		}
	}
	else if (_c == CANVI_DE_SIGNE or _c == SIGNE_POSITIU) {
		if (t._c == MULTIPLICACIO or t._c == DIVISIO or t._c == SUMA or t._c == RESTA) {
			major = true;
		}
	}
	else if (_c == MULTIPLICACIO or _c == DIVISIO) {
		if (t._c == SUMA or t._c == RESTA) {
			major = true;
		}
	}
	return major;
}

bool token::operator<(const token & t) const throw(error)
//Pre: Cert
//Post: Retorna error(ProcedenciaEntreNoOperadors) si el token implícit o el token t no són operadors. Si ho són retorna un boolea == true si el token implícit té menys prioritat que el token t i retorna un boolea == false si té més prioritat
//Cost: Cost constant (1)
{
	if (not operador(*this)) {
		throw error(PrecedenciaEntreNoOperadors);
	}
	if (not operador(t)) {
		throw error(PrecedenciaEntreNoOperadors);
	}
	bool menor = false;
	if (_c == SUMA or _c == RESTA) {
		if (t._c != SUMA and t._c != RESTA) {
			menor = true;
		}
	}
	else if (_c == MULTIPLICACIO or _c == DIVISIO) {
		if (t._c == CANVI_DE_SIGNE or t._c == SIGNE_POSITIU or t._c == EXPONENCIACIO) {
			menor = true;
		}
	}
	else if (_c == CANVI_DE_SIGNE or _c == SIGNE_POSITIU) {
		if (t._c == EXPONENCIACIO) {
			menor = true;
		}
	}
	return menor;
}





