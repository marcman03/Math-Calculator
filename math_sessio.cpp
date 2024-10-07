#include "math_sessio.hpp"

bool math_sessio::operand(const token t)
//Pre: Cert
//Post: Retorna un boolea == true si el token t és un operand i retorna un boolea == false si no ho és
{
	if (t.tipus() == token::NULLTOK or t.tipus() == token::CT_ENTERA or t.tipus() == token::CT_RACIONAL or t.tipus() == token::CT_REAL or t.tipus() == token::CT_E or t.tipus() == token::VARIABLE or t.tipus() == token::VAR_PERCENTATGE)
	{
		return true;
	}  
	return false;
}

void math_sessio::analitza_comanda(const list<token> &l) throw(error)
//Pre: Cert
//Post: Retorna error(ErrorSintactic) si la comanda és incorrecte. La comanda és incorrecte quan conté el token BYEBYE i aquest no és l'únic token de la llista, quan conté el token ASSIGNACIO i aquest no és el segon token, el primer no és VARIABLE o la mida de la llista és menor de 3 i quan conté el token DESASSIGNACIO i aquest no és el primer token i el següent i últim token no és VARIABLE 
{
	list<token>::const_iterator p = l.begin();
	list<token>::const_iterator segon = l.begin(); 
	++segon;
	 token primer = *p;
	while (p != l.end()) {
		token t = *p;
		if (t.tipus() == token::BYEBYE) {
			if (l.size() != 1) {
				throw error(SintComandaIncorrecta);
			}
		}
		else if (t.tipus() == token::ASSIGNACIO) {
			if (l.size() <= 2) {
				throw error(SintComandaIncorrecta);
			}
			if (p != segon) {
				throw error(SintComandaIncorrecta);
			}
			if (primer.tipus() != token::VARIABLE) {
				throw error(SintComandaIncorrecta);
			}
		}
		else if (t.tipus() == token::DESASSIGNACIO) {
			if (l.size() != 2) {
				throw error(SintComandaIncorrecta);
			}
			if (p != l.begin()) {
				throw error(SintComandaIncorrecta);
			}
			list<token>::const_iterator aux = p;
			++aux;
			token aux2 = *aux;
			if (aux2.tipus() != token::VARIABLE) {
				throw error(SintComandaIncorrecta);
			}
		}
		++p;
	}
}

math_sessio::math_sessio() throw(error)
//Pre: Cert
//Post: Crea una nova sessió buida
{
	
	expressio e;
	_v.assign("%",e);
	_end = false;
}

// Constructora per còpia, assignació i destructora.
math_sessio::math_sessio(const math_sessio & es) throw(error)
//Pre: Cert
//Post: Crea una còpia de la sessió es
{	
	_v = es._v;
	_end = es._end;
}
math_sessio & math_sessio::operator=(const math_sessio & es) throw(error)
//Pre: Cert
//Post: Retorna una còpia de la sessió es
{	
	_v = es._v;
	_end = es._end;
	return *this;
}
math_sessio::~math_sessio() throw(error)
//Pre: Cert
//Post: Destrueix la sessió
{	
}

void math_sessio::execute(const list<token> & lin, list<token> & lout) throw(error)
//Pre: Cert
//Post: Si la comanda no és correcte retorna error(SintComandaIncorrecta). Si ho és i conté EVALF, avalua la expressió de lin i ho introdueix a lout. Si ho és i conté ASSIGNACIO, avalua la expressió de lin (després del token ASSIGNACIO), assigna a la variable de l'AVL implícit (primer token de lin) l'expressió avaluada i la introdueix a lout. Si ho és i conté DESASSIGNACIO s'elimina la variable de l'AVL implícit (si existeix) i introdueix a lout la variable. Si ho és i conté BYEBYE s'acaba la sessió
{
	if (not _end) {
		analitza_comanda(lin);
		list<token>::const_iterator plin = lin.begin();
		token t = *plin;
		if (lin.size() == 1 and t.tipus() != token::BYEBYE and t.tipus() != token::VARIABLE) {
			expressio e(lin);
			_v.assign("%",e);
			lout = lin;
		} 
		if (t.tipus() == token::VARIABLE) {
			++plin;
			token taux = *plin;
			if (taux.tipus() == token::ASSIGNACIO) {
				list<token> laux = lin;
				laux.pop_front();
				laux.pop_front();
				expressio e(laux);
				apply_all_substitutions(e);
				list<string> lstring;
				e.vars(lstring);
				list<string>::iterator plstring = lstring.begin();
				while (plstring != lstring.end()) {
					string s = *plstring;
					if (t.identificador_variable() == s) {
						throw error(AssigAmbCirculInfinita);
					}
					++plstring;
				}
				e.simplify();
				e.list_of_tokens(lout);
				_v.assign(t.identificador_variable(), e);
				_v.assign("%",e);
			}
			else {
				expressio e(lin);
				apply_all_substitutions(e);
				e.simplify();
				_v.assign("%",e);
				e.list_of_tokens(lout); 
			}
		}
		else if (t.tipus() == token::EVALF) {
			expressio e(lin);
			apply_all_substitutions(e);
			e.simplify();
			_v.assign("%",e);
			e.list_of_tokens(lout);
		}
		else if (t.tipus() == token::DESASSIGNACIO) {
			++plin;
			t = *plin;
			_v.unassign(t.identificador_variable());
			lout.push_back(t);	
		}
		else if (t.tipus() == token::BYEBYE) {
			_end = true;
		}
	}	
}

bool math_sessio::end_of_session() const throw()
//Pre: Cert
//Post: Retorna un boolea == true si la sessió s'ha acabat i retorna un boolea == false si no ha acabat
{
	return _end;
}


void math_sessio::dump(list<string> & l) const throw(error)
//Pre: Cert
//Post: Introdueix a la llista l la llista de variables de l'AVL implícit juntament amb el seu valor d'aquesta manera: identificador de la variable = expressió en forma de llista d'strings
{
	if (not _end) {
		list<string> auxs;
		_v.dump(auxs);
		list<string>::iterator p = auxs.begin();
		while (p != auxs.end()) {
			string s = *p;
			expressio e = _v.valor(s);
			s += " = ";
			list<token> auxt;
			e.list_of_tokens(auxt);
			s += math_io::tostring(auxt);
			l.push_back(s);
			++p;
		}
	}		
}

/* Donada una expressió e, aplica a les seves variables totes les
   substitucions definides per elles. L'expressió resultant només contindrà
   variables per les quals no hi ha substitució definida (no estan en el
   conjunt). Aquest procés s'explica en detall a l'apartat "Procés
   d'avaluació". S'assumeix que no existeix circularitat infinita entre les
   substitucions de les variables que formen part de l'expressió e. */
void math_sessio::apply_all_substitutions(expressio & e) const throw(error)
//Pre: Cert
//Post: Aplica a l'expressió e totes les substitucions de variables pel seu valor dins de l'AVL implícit, si hi són
{
	if (not _end) {
		list<token> l;
		e.list_of_tokens(l);
		list<token>::iterator p = l.begin();
		token t;
		bool canvi = false;
		while (p != l.end() and not canvi) {
			t = *p;
			if (t.tipus() == token::VARIABLE) {
				expressio aux = _v.valor(t.identificador_variable());
				if (not aux) {
					e.apply_substitution(t.identificador_variable(),aux);
					apply_all_substitutions(e);
					canvi = true;
				}
			}
			if (t.tipus() == token::VAR_PERCENTATGE) {
				expressio aux = _v.valor("%");
				if (not aux) {
					e.apply_substitution("%",aux);
					apply_all_substitutions(e);
					canvi = true;
				}
			}
			++p;
		}
	}
}

















