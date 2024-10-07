#include "variables.hpp"
#include <iostream>
using namespace std;

variables::node* variables::rec_preordre_copia(node *n)
//Pre: Cert
//Post: Retorna un punter a l'arrel de la copia de l'AVL on n és l'arrel
//Cost: Cost linial O(N)
{	
	node *aux = nullptr;
	if (n != nullptr) {
		aux = new node;
		aux->_k = n->_k;
		aux->_v = n->_v;
		aux->_h = n->_h;
		aux->_esq = rec_preordre_copia(n->_esq);
		aux->_dret = rec_preordre_copia(n->_dret);
	}
	return aux;
}

void variables::destrueix_expressio(node *n)
//Pre: Cert
//Post: Destrueix l'AVL on n és l'arrel
//Cost: Cost linial O(N)
{
	if (n != nullptr) {
		destrueix_expressio(n->_esq);
		destrueix_expressio(n->_dret);
		delete n;
	}
}

int variables::altura (node *n)
//Pre: Cert
//Post: Retorna l'altura del node n
//Cost: Cost constant O(1)
{
	if (n == nullptr) {
		return 0;
	}
	return n->_h;
}

int variables::factor_equilibri (node *n)
//Pre: Cert
//Post: Retorna el factor d'equilibri del node n
//Cost: Cost constant O(1)
{
	if (n == 0) {
		return 0;
	}
	return altura(n->_esq) - altura(n->_dret);
}

variables::node* variables::rotacio_dreta(node *n)
//Pre: Cert
//Post: Retorna un punter a l'arrel de l'AVL on n és l'arrel després de fer una rotació a la dreta
//Cost: Cost constant O(1) 
{
	node *e = n->_esq;
	node *d = e->_dret;
	
	e->_dret = n;
	n->_esq = d;
	
	n->_h = std::max(altura(n->_esq),altura(n->_dret))+1;
	e->_h = std::max(altura(e->_esq),altura(e->_dret))+1;
	
	return e;
}

variables::node* variables::rotacio_esquerra(node *n) 
//Pre: Cert
//Post: Retorna un punter a l'arrel de l'AVL on n és l'arrel després de fer una rotació a l'esquerre
//Cost: Cost constant O(1) 
{
	node *d = n->_dret;
	node *e = d->_esq;
	
	d->_esq = n;
	n->_dret = e;
	
	n->_h = std::max(altura(n->_esq),altura(n->_dret))+1;
	d->_h = std::max(altura(d->_esq),altura(d->_dret))+1;
	
	return d;
}
variables::node* variables::assigna_bst(node *n, const string & v, const expressio & e)
//Pre: Cert
//Post: Retorna un punter a l'arrel de l'AVL on n és l'arrel després d'introduir la variable amb identificador == v i l'expressió e i balancejar l'arbre si cal.
//Cost: Cost logarítmic O(logN) 
{
	if (n == nullptr) {
		node *aux = new node;
		aux->_k = v;
		aux->_v = e;
		aux->_h = 1;
		aux->_esq = nullptr;
		aux->_dret = nullptr;
		return aux;
	}
	else if (v < n->_k) {
		n->_esq = assigna_bst(n->_esq,v,e);
	}
	else if (v > n->_k) {
		n->_dret = assigna_bst(n->_dret,v,e);
	}
	else {
		n->_v = e;
		return n;
	}
	
	n->_h = std::max(altura(n->_esq),altura(n->_dret))+1;
	
	int fe = factor_equilibri(n);
	
	if (fe > 1 and v < n->_esq->_k) {
		return rotacio_dreta(n);
	}
	if (fe < -1 and v > n->_dret->_k) {
		return rotacio_esquerra(n);
	}
	if (fe > 1 and v > n->_esq->_k) {
		n->_esq = rotacio_esquerra(n->_esq);
		return rotacio_dreta(n);
	}
	if (fe < -1 and v < n->_dret->_k) {
		n->_dret = rotacio_dreta(n->_dret);
		return rotacio_esquerra(n);
	}
	
	return n;
}

variables::node* variables::unassign_bst(node *n, const string & v)
//Pre: Cert
//Post: Retorna un punter a l'arrel de l'AVL on n és l'arrel després d'eliminar la variable amb identificador == v si existeix.
//Cost: Cost logarítmic O(logN) 
{
	node *p = n;
	if (n != nullptr) {
		if (v < n->_k) {
			n->_esq = unassign_bst(n->_esq,v);
		}
		else if (v > n->_k) {
			n->_dret = unassign_bst(n->_dret,v);
		}
		else {
			n = ajunta(n->_esq, n->_dret);
			delete(p);
		}	
	}
	if (n != nullptr) {
		n->_h = std::max(altura(n->_esq),altura(n->_dret))+1;	
		
		int fe = factor_equilibri(n);
	
		if (fe > 1 and factor_equilibri(n->_esq) >= 0) {
			return rotacio_dreta(n);
		}
		if (fe < -1 and factor_equilibri(n->_dret) <= 0) {
			return rotacio_esquerra(n);
		}
		if (fe > 1 and factor_equilibri(n->_esq) < 0) {
			n->_esq = rotacio_esquerra(n->_esq);
			return rotacio_dreta(n);
		}
		if (fe < -1 and factor_equilibri(n->_dret) > 0) {
			n->_dret = rotacio_dreta(n->_dret);
			return rotacio_esquerra(n);
		}
	}
	
	return n;
}

variables::node* variables::ajunta(node *e, node *d)
//Pre: Cert
//Post: Retorna un punter al node amb la clau més gran del subarbre e, ficant al seu fill dret el subarbre d. Si e és igual a null retorna d i si d és igual a null retorna e
//Cost: Cost linial O(e._h)  
{
	if (e == nullptr) {
		return d;
	}
	if (d == nullptr) {
		return e;
	}
	node *p = elimina_maxim(e);
	p->_dret = d;
	return p;
}

variables::node* variables::elimina_maxim(node *p) 
//Pre: Cert
//Post: Retorna un punter al node amb la clau més gran, deprés de posar al fill dret de l'anterior el fill esquerre del node amb la clau més gran i de posar al fill esquerre del node amb la clau més gran el node original.
//Cost: Cost linial O(p._h) 
{
	node *p_orig = p, *pare = nullptr;
	while (p->_dret != nullptr) {
		pare = p;
		p = p->_dret;
	}
	if (pare != nullptr) {
		pare->_dret = p->_esq;
		p->_esq = p_orig;
	}
	return p;
}

variables::node* variables::valor_bst(node *n, const string & lv)
//Pre: Cert
//Post: Retorna un punter al node on _k == lv. Si no hi ha cap node així retrona un punter a null
//Cost: Cost logarítmic O(log(N)) 
{
	if (n == nullptr or n->_k == lv) {
		return n;
	}
	else {
		if (lv < n->_k) {
			return valor_bst(n->_esq, lv);
		}
		else {
			return valor_bst(n->_dret, lv);
		}
	}
}

void variables::rec_inordre (node *n, list<string> & l)
//Pre: Cert
//Post: Recorre l'AVL on n és l'arrel i introdueix a la llista l el nom de la variable de cada node
//Cost: Cost linial O(N) 
{
	if (n != nullptr) {
		rec_inordre(n->_esq,l);
		l.push_front(n->_k);	
		rec_inordre(n->_dret,l);	
	}
}
// Construeix un conjunt de variables buit.
variables::variables() throw(error)
//Pre: Cert
//Post: Crea un AVL buit
//Cost: Cost constant O(1) 
{
	_arrel = nullptr;
}

// Constructora per còpia, assignació i destructora.
variables::variables(const variables & v) throw(error)
//Pre: Cert
//Post: Crea una copia de l'AVL v 
//Cost: Cost linial O(N)
{
	_arrel = rec_preordre_copia(v._arrel);
	
}
variables & variables::operator=(const variables & v) throw(error)
//Pre: Cert
//Post: Retorna una copia de l'AVL v 
//Cost: Cost linial O(N)
{
	destrueix_expressio(_arrel);
	_arrel = rec_preordre_copia(v._arrel);
	return *this;
}

variables::~variables() throw(error)
//Pre: Cert
//Post: Destrueix l'AVl de variables
//Cost: Cost linial O(N)
{
	destrueix_expressio(_arrel);
}

void variables::assign(const string & v, const expressio & e) throw(error)
//Pre: Cert
//Post: Afegeix a l'AVl implícit la variable amb identificador == v i el seu valor == e. Si la variable ja existia es canvia el seu valor.
//Cost: Cost logarítmic O(log(N))
{
	_arrel = assigna_bst(_arrel,v,e);
}

void variables::unassign(const string & v) throw()
//Pre: Cert
//Post: Elimina de l'AVl implícit la variable amb identificador == v
//Cost: Cost logarítmic O(log(N))
{
	_arrel = unassign_bst(_arrel,v);
}

expressio variables::valor(const string & lv) const throw(error)
//Pre: Cert
//Post: Retorna l'expressió associat a la variable amb identificador == lv de l'AVL implícit. SI no existeix aquesta variable a l'AVL retorna l'expressió buida
//Cost: Cost logarítmic O(log(N))
{
	node *n = valor_bst(_arrel,lv);
	if (n == nullptr) {
		token t;
		expressio e(t);
		return e;
	}
	else {
		return n->_v;
	}
}

void variables::dump(list<string> & l) const throw(error)
//Pre: Cert
//Post: Introdueix a la llista l totes les variables de l'AVL implícit
//Cost: Cost logarítmic O(log(N))
{
	rec_inordre(_arrel,l);
}
