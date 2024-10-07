#include "expressio.hpp"
#include <cmath>
#include <stack>
using std::stack;
#include <iostream>
using namespace std;


bool expressio::operador(const token t)
//Pre: Cert
//Post: Retorna un boolea == true si el token t és un operador i retorna un boolea == false si no ho és
{
	if (t.tipus() == token::SUMA or t.tipus() == token::RESTA or t.tipus() == token::MULTIPLICACIO or t.tipus() == token::DIVISIO or t.tipus() == token::EXPONENCIACIO or t.tipus() == token::CANVI_DE_SIGNE or t.tipus() == token::SIGNE_POSITIU or t.tipus() == token::SQRT or t.tipus() == token::EXP or t.tipus() == token::LOG or t.tipus() == token::EVALF or t.tipus() == token::OBRIR_PAR or t.tipus() == token::TANCAR_PAR or t.tipus() == token::COMA) {
		return true;
	}
	return false;
}

bool expressio::operand(const token t)
//Pre: Cert
//Post: Retorna un boolea == true si el token t és un operand i retorna un boolea == false si no ho és
{
	if (t.tipus() == token::NULLTOK or t.tipus() == token::CT_ENTERA or t.tipus() == token::CT_RACIONAL or t.tipus() == token::CT_REAL or t.tipus() == token::CT_E or t.tipus() == token::VARIABLE or t.tipus() == token::VAR_PERCENTATGE)
	{
		return true;
	} 
	return false;
}

bool expressio::binari(const token t)
//Pre: Cert
//Post: Retorna un boolea == true si el token t és un operador binari i retorna un boolea == false si no ho és 
{
	if (t.tipus() == token::SUMA or t.tipus() == token::RESTA or t.tipus() == token::MULTIPLICACIO or t.tipus() == token::DIVISIO or t.tipus() == token::EXPONENCIACIO) {
		return true;
	}
	return false;
}

bool expressio::funcio(const token t)
//Pre: Cert
//Post: Retorna un boolea == true si el token t és una funció i retorna un boolea == false si no ho és
{
	if (t.tipus() == token::SQRT or t.tipus() == token::EXP or t.tipus() == token::LOG or t.tipus() == token::EVALF) {
		return true;
	}
	return false;
}

bool expressio::correcte (list<token>::const_iterator a, list<token>::const_iterator b)
//Pre: A != list<token>.end() B != list<token>.end()
//Post: Retorna un boolea == true si el token al que apunta l'iterador a seguit del token al que apunta l'iterador b és correcte matemàticament i retorna un boolea == false si no ho és
{	
	token t = *a;
	token post = *b;
	if (operand(t)) {
		if(operand(post)) {
			return false;
		}
	}
	if (operador(t) and t.tipus() != token::TANCAR_PAR) {
		if (operador(post) and binari(post)) {
			return false;
		}
	}
	if (funcio(t)) {
		if (post.tipus() != token::OBRIR_PAR) {
			return false;
		}
	}
	
	return true;
}

bool expressio::prioritat(const token t1, const token t2)
//Pre: t1 i t2 són operadors
//Post: Retorna un boolea == true si el token t1 té prioritat respecte el token t2 i retorna un boolea == false si no en té
{
	bool prior = false;
	if (not binari(t1)) {
		prior = true;
	}
	else {
		if (binari(t2) or t2.tipus() == token::OBRIR_PAR) {
			if (t1.tipus() == token::EXPONENCIACIO) {
				prior = true;
			}
			else if (t1.tipus() == token::MULTIPLICACIO or t1.tipus() == token::DIVISIO) {
				if (t2.tipus() != token::EXPONENCIACIO and t2.tipus() != token::MULTIPLICACIO and t2.tipus() != token::DIVISIO) {
					prior = true;
				}
			}
			else if (t1.tipus() == token::SUMA or t1.tipus() == token::RESTA) {
				if (t2.tipus() == token::OBRIR_PAR) {
					prior = true;
				}
			}
		}
	}
	return prior;
}

expressio::node* expressio::rec_postordre_simplify(node *n, bool &simp)
//Pre: simp = false
//Post: Retorna un punter al node n després d'aplicar una simplificació a l'expressio on el node n és l'arrel, si es pot.
{
	if (n != nullptr and not simp) {
		n->_esq = rec_postordre_simplify(n->_esq,simp);
		n->_dret = rec_postordre_simplify(n->_dret,simp);
		token t = n->_info;
		token e;
		token d;
		if (n->_esq != nullptr) {
			e = n->_esq->_info;
		}
		if (n->_dret != nullptr) {
			d = n->_dret->_info;
		}
		
		//Regla 0
		if (t.tipus() == token::CT_RACIONAL) {
			if (t.valor_racional().denom() == 1) {
				token aux (n->_info.valor_racional().num());
				n->_info = aux;
				simp = true;
			}
		}
		
		//Regla 1
		if (not simp and operador(t) and binari(t)) {
			if (operand(e) and operand(d)) {
				if (e.tipus() == d.tipus()) {
					if (t.tipus() == token::SUMA) {
						if (e.tipus() == token::CT_ENTERA) {
							token aux (e.valor_enter() + d.valor_enter());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_RACIONAL) {
							token aux (e.valor_racional() + d.valor_racional());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_REAL) {
							token aux (e.valor_real() + d.valor_real());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
					}
					if (not simp and t.tipus() == token::RESTA) {
						if (e.tipus() == token::CT_ENTERA) {
							token aux (e.valor_enter() - d.valor_enter());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_RACIONAL) {
							token aux (e.valor_racional() - d.valor_racional());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_REAL) {
							token aux (e.valor_real() - d.valor_real());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
					}
					if (not simp and t.tipus() == token::MULTIPLICACIO) {
						if (e.tipus() == token::CT_ENTERA) {
							token aux (e.valor_enter() * d.valor_enter());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_RACIONAL) {
							token aux (e.valor_racional() * d.valor_racional());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_REAL) {
							token aux (e.valor_real() * d.valor_real());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
					}
					if (not simp and t.tipus() == token::DIVISIO) {
						if (e.tipus() == token::CT_ENTERA) {
							if (d.valor_enter() == 0) {
								throw error (DivPerZero);
							}
							if (e.valor_enter() % d.valor_enter() != 0) {
								racional r (e.valor_enter(),d.valor_enter());
								token aux(r);
								n->_info = aux;
								destrueix_expressio(n->_esq);
								destrueix_expressio(n->_dret);
								n->_esq = nullptr;
								n->_dret = nullptr;
								simp = true;
							}
							else {
								token aux (e.valor_enter() / d.valor_enter());
								n->_info = aux;
								destrueix_expressio(n->_esq);
								destrueix_expressio(n->_dret);
								n->_esq = nullptr;
								n->_dret = nullptr;
								simp = true;
							}	
						}
						if (not simp and e.tipus() == token::CT_RACIONAL) {
							if (d.valor_racional().num() == 0) {
								throw error (DivPerZero);
							}
							token aux (e.valor_racional() / d.valor_racional());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_REAL) {
							if (d.valor_real() == 0.0) {
								throw error (DivPerZero);
							}
							token aux (e.valor_real() / d.valor_real());
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
					}
				}
				else {
					if (t.tipus() == token::DIVISIO) {
						if (d.tipus() == token::CT_ENTERA) {
							if (d.valor_enter() == 0) {
								throw error (DivPerZero);
							}
						}
						if (d.tipus() == token::CT_REAL) {
							if (d.valor_real() == 0.0) {
								throw error (DivPerZero);
							}
						}
						if (e.tipus() == token::CT_ENTERA and d.tipus() == token::CT_RACIONAL) {
							racional r(e.valor_enter(),1);
							racional res = r / d.valor_racional();
							token aux(res);
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
						if (not simp and e.tipus() == token::CT_RACIONAL and d.tipus() == token::CT_ENTERA) {
							racional r(d.valor_enter(),1);
							racional res = e.valor_racional() / r;
							token aux(res);
							n->_info = aux;
							destrueix_expressio(n->_esq);
							destrueix_expressio(n->_dret);
							n->_esq = nullptr;
							n->_dret = nullptr;
							simp = true;
						}
					}
				}
			}
		}				
		
		
		//Regla 2
		if (not simp and t.tipus() == token::SUMA) {
			//a)
			if (e.tipus() == token::CT_ENTERA) {
				if (e.valor_enter() == 0) {
					node *aux = rec_preordre_copia(n->_dret);
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and e.tipus() == token::CT_REAL) {
				if (e.valor_real() == 0.0) {
					node *aux = rec_preordre_copia(n->_dret);
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and e.tipus() == token::CT_RACIONAL) {
				if (e.valor_racional().num() == 0) {
					node *aux = rec_preordre_copia(n->_dret);
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//b)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n->_dret);
					destrueix_expressio(n->_esq);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if (d.valor_real() == 0.0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n->_dret);
					destrueix_expressio(n->_esq);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				if (d.valor_racional().num() == 0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n->_dret);
					destrueix_expressio(n->_esq);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//c)
			if (not simp and rec_inordre_iguals(n->_esq, n->_dret)) {
				token aux(token::MULTIPLICACIO);
				token aux2(2);
				n->_info = aux;
				destrueix_expressio(n->_esq);
				n->_esq = new node;
				n->_esq->_info = aux2;
				n->_esq->_esq = nullptr;
				n->_esq->_dret = nullptr;
				simp = true;
			}
			//d)
			if (not simp and d.tipus() == token::CANVI_DE_SIGNE) {
				token aux(token::RESTA);
				n->_info = aux;
				node *aux2 = rec_preordre_copia(n->_dret->_dret);
				destrueix_expressio(n->_dret);
				n->_dret = rec_preordre_copia(aux2);
				simp = true;
				destrueix_expressio(aux2);
			}
			//e)
			if (not simp and e.tipus() == token::CANVI_DE_SIGNE) {
				token aux(token::RESTA);
				n->_info = aux;
				node *aux2 = rec_preordre_copia(n->_dret);
				destrueix_expressio(n->_dret);
				n->_dret = rec_preordre_copia(n->_esq->_dret);
				destrueix_expressio(n->_esq);
				n->_esq = rec_preordre_copia(aux2);
				destrueix_expressio(aux2);
				simp = true;
			}
			
			
			if (not simp and e.tipus() == token::MULTIPLICACIO and d.tipus() == token::MULTIPLICACIO) {
				//f)
				if (rec_inordre_iguals(n->_esq->_dret, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//g)
				if (not simp and rec_inordre_iguals(n->_esq->_dret, n->_dret->_esq)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_dret);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_esq);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//h)
				if ( not simp and rec_inordre_iguals(n->_esq->_esq, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_esq);
					n->_esq->_esq = rec_preordre_copia(n->_esq->_dret);
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//i)
				if (not simp and rec_inordre_iguals(n->_esq->_esq, n->_dret->_esq)) {
					destrueix_expressio(n->_esq->_esq);
					n->_esq->_esq = rec_preordre_copia(n->_esq->_dret);
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret= rec_preordre_copia(n->_dret->_dret);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_esq);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//j)
			if (not simp and e.tipus() == token::DIVISIO and d.tipus() == token::DIVISIO){
				if (rec_inordre_iguals(n->_esq->_dret, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}	
			}
			
		}
		
		
		//Regla 3
		if (not simp and t.tipus() == token::RESTA) {
			//a)
			if (e.tipus() == token::CT_ENTERA) {
				if (e.valor_enter() == 0) {
					token aux(token::CANVI_DE_SIGNE);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					n->_esq = nullptr;
					simp = true;
				}
			}
			if (not simp and e.tipus() == token::CT_REAL) {
				if (e.valor_real() == 0.0) {
					token aux(token::CANVI_DE_SIGNE);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					n->_esq = nullptr;
					simp = true;
				}
			}
			if (not simp and e.tipus() == token::CT_RACIONAL) {
				if (e.valor_racional().num() == 0) {
					token aux(token::CANVI_DE_SIGNE);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					n->_esq = nullptr;
					simp = true;
				}
			}
			//b)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if (d.valor_real() == 0.0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				if (d.valor_racional().num() == 0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//c)
			if (not simp and rec_inordre_iguals(n->_esq, n->_dret)) {
				token aux(0);
				n->_info = aux;
				destrueix_expressio(n->_esq);
				destrueix_expressio(n->_dret);
				n->_esq = nullptr;
				n->_dret = nullptr;
				simp = true;
			}
			//d)
			if (not simp and d.tipus() == token::CANVI_DE_SIGNE) {
				token aux(token::SUMA);
				n->_info = aux;
				node *aux2 = rec_preordre_copia(n->_dret->_dret);
				destrueix_expressio(n->_dret);
				n->_dret = rec_preordre_copia(aux2);
				destrueix_expressio(aux2);
				simp = true;
			}
			if (not simp and e.tipus() == token::MULTIPLICACIO and d.tipus() == token::MULTIPLICACIO) {
				//e)
				if (rec_inordre_iguals(n->_esq->_dret, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//f)
				if (not simp and rec_inordre_iguals(n->_esq->_dret, n->_dret->_esq)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_dret);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_esq);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//g)
				if (not simp and rec_inordre_iguals(n->_esq->_esq, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_esq);
					n->_esq->_esq = rec_preordre_copia(n->_esq->_dret);
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//h)
				if (not simp and rec_inordre_iguals(n->_esq->_esq, n->_dret->_esq)) {
					destrueix_expressio(n->_esq->_esq);
					n->_esq->_esq = rec_preordre_copia(n->_esq->_dret);
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret= rec_preordre_copia(n->_dret->_dret);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_esq);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//i)
			if (not simp and e.tipus() == token::DIVISIO and d.tipus() == token::DIVISIO){
				if (rec_inordre_iguals(n->_esq->_dret, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}	
			}
		}	
		
		
		//Regla 4
		//a)
		if (not simp and t.tipus() == token::CANVI_DE_SIGNE) {
			if (d.tipus() == token::CANVI_DE_SIGNE) {
				node *aux = rec_preordre_copia(n->_dret->_dret);
				destrueix_expressio(n);
				n = rec_preordre_copia(aux);
				destrueix_expressio(aux);
				simp = true;
			}
		}	
		//b)
		if (not simp and t.tipus() == token::SIGNE_POSITIU) {
			node *aux = rec_preordre_copia(n->_dret);
			destrueix_expressio(n);
			n = rec_preordre_copia(aux);
			destrueix_expressio(aux);
			simp = true;
		}
		//c)
		if (not simp and t.tipus() == token::CANVI_DE_SIGNE) {
			if (not simp and d.tipus() == token::CT_ENTERA) {
				token aux(-d.valor_enter());
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				token aux(-d.valor_real());
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;	
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				racional aux(-d.valor_racional().num(), d.valor_racional().denom());
				token aux2(aux);
				n->_info = aux2;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
		}	
		
		
		
		
		//Regla 5
		if (not simp and t.tipus() == token::MULTIPLICACIO) {
			//a)
			if (e.tipus() == token::CT_ENTERA) {
				if (e.valor_enter() == 1) {
					node *aux = rec_preordre_copia(n->_dret);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;	
				}
			}
			if (not simp and e.tipus() == token::CT_REAL) {
				if (e.valor_real() == 1.0) {
					node *aux = rec_preordre_copia(n->_dret);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;	
				}
			}
			//b)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 1) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;	
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if (d.valor_real() == 1.0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;	
				}
			}
			//c)
			if (not simp and e.tipus() == token::CT_ENTERA) {
				if (e.valor_enter() == 0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;	
				}
			}
			if (not simp and e.tipus() == token::CT_REAL) {
				if (e.valor_real() == 0.0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;	
				}
			}
			if (not simp and e.tipus() == token::CT_RACIONAL) {
				if (e.valor_racional().num() == 0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;	
				}
			}
			//d)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;	
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if (d.valor_real() == 0.0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;	
				}
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				if (d.valor_racional().num() == 0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;	
				}
			}
			//e)
			if (not simp and rec_inordre_iguals(n->_esq, n->_dret)) {
				token aux(token::EXPONENCIACIO);
				token aux2(2);
				n->_info = aux;
				n->_dret->_info = aux2;
				destrueix_expressio(n->_dret->_esq);
				destrueix_expressio(n->_dret->_dret);
				n->_dret->_esq = nullptr;
				n->_dret->_dret = nullptr;
				simp = true;
			}
			//f)
			if (not simp and d.tipus() == token::CANVI_DE_SIGNE) {
				token aux(token::MULTIPLICACIO);
				n->_info = n->_dret->_info;
				n->_dret->_info = aux;
				n->_dret->_esq = rec_preordre_copia(n->_esq);
				destrueix_expressio(n->_esq);
				n->_esq = nullptr;
				simp = true;
			}
			//g)
			if (not simp and e.tipus() == token::CANVI_DE_SIGNE) {
				token aux(token::MULTIPLICACIO);
				n->_info = n->_esq->_info;
				node *aux2 = rec_preordre_copia(n->_dret);
				destrueix_expressio(n->_dret);
				n->_dret = new node;
				n->_dret->_info = aux;
				n->_dret->_dret = rec_preordre_copia(aux2);
				n->_dret->_esq = rec_preordre_copia(n->_esq->_dret);
				destrueix_expressio(n->_esq);
				n->_esq = nullptr;
				destrueix_expressio(aux2);
				simp = true;
			}
			
			//h)
			if (not simp and d.tipus() == token::DIVISIO) {
				if (n->_dret->_esq->_info.tipus() == token::CT_ENTERA) {
					if (n->_dret->_esq->_info.valor_enter() == 1) {
						n->_info = n->_dret->_info;
						node *aux = rec_preordre_copia(n->_dret->_dret);
						destrueix_expressio(n->_dret);
						n->_dret = rec_preordre_copia(aux);
						destrueix_expressio(aux);
						simp = true;
					}
				}
				if (not simp and n->_dret->_esq->_info.tipus() == token::CT_REAL) {
					if (n->_dret->_esq->_info.valor_real() == 1.0) {
						n->_info = n->_dret->_info;
						node *aux = rec_preordre_copia(n->_dret->_dret);
						destrueix_expressio(n->_dret);
						n->_dret = rec_preordre_copia(aux);
						destrueix_expressio(aux);
						simp = true;
					}
				}
			}		
			//i)
			if (not simp and e.tipus() == token::DIVISIO) {
				if (n->_esq->_esq->_info.tipus() == token::CT_ENTERA) {
					if (n->_esq->_esq->_info.valor_enter() == 1) {
						n->_info = n->_esq->_info;
						node *aux = rec_preordre_copia(n->_dret);
						destrueix_expressio(n->_dret);
						n->_dret = rec_preordre_copia(n->_esq->_dret);
						destrueix_expressio(n->_esq);
						n->_esq = rec_preordre_copia(aux);
						destrueix_expressio(aux);
						simp = true;
					}
				}
				if (not simp and n->_dret->_esq->_info.tipus() == token::CT_REAL) {
					if (n->_dret->_esq->_info.valor_real() == 1.0) {
						n->_info = n->_esq->_info;
						node *aux = rec_preordre_copia(n->_dret);
						destrueix_expressio(n->_dret);
						n->_dret = rec_preordre_copia(n->_esq->_dret);
						destrueix_expressio(n->_esq);
						n->_esq = rec_preordre_copia(aux);
						destrueix_expressio(aux);
						simp = true;
					}
				}	
			}
			if (not simp and e.tipus() == token::EXPONENCIACIO and d.tipus() == token::EXPONENCIACIO) {
				//j)
				if (rec_inordre_iguals(n->_esq->_dret, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//k)
				if (not simp and rec_inordre_iguals(n->_esq->_esq, n->_dret->_esq)) {
					token aux(token::SUMA);
					n->_info = n->_dret->_info;
					n->_dret->_info = aux;
					destrueix_expressio(n->_dret->_esq);
					n->_dret->_esq = rec_preordre_copia(n->_esq->_dret);
					node *aux2 = rec_preordre_copia(n->_esq->_esq);
					destrueix_expressio(n->_esq);
					n->_esq = rec_preordre_copia(aux2);
					destrueix_expressio(aux2);
					simp = true;
				}
			}
			//l)
			if (not simp and e.tipus() == token::EXP and d.tipus() == token::EXP) {
				n->_info = n->_dret->_info;
				node *aux = rec_preordre_copia(n->_esq->_dret);
				destrueix_expressio(n->_esq);
				n->_esq = nullptr;
				token aux2(token::SUMA);
				n->_dret->_info = aux2;
				n->_dret->_esq = rec_preordre_copia(aux);
				destrueix_expressio(aux);
			} 
		}
		
		
		//Regla 6
		if (not simp and t.tipus() == token::DIVISIO) {
			//a)
			if (d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 0) {
					throw error(DivPerZero);
				}
			}
			if (d.tipus() == token::CT_REAL) {
				if (d.valor_real() == 0.0) {
					throw error(DivPerZero);
				}
			}
			if (d.tipus() == token::CT_RACIONAL) {
				if (d.valor_racional().num() == 0) {
					throw error(DivPerZero);
				}
			}
			//b)
			if (e.tipus() == token::CT_ENTERA) {
				if (e.valor_enter() == 0) {
					token aux(0);
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and e.tipus() == token::CT_REAL) {
				if (e.valor_real() == 0.0) {
					token aux(0);
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and e.tipus() == token::CT_RACIONAL) {
				if (e.valor_racional().num() == 0) {
					token aux(0);
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}
			//c)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 1) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if (d.valor_real() == 1.0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//d)
			if (not simp and rec_inordre_iguals(n->_esq, n->_dret)) {
				token aux(1);
				destrueix_expressio(n);
				n = new node;
				n->_info = aux;
				n->_esq = nullptr;
				n->_dret = nullptr;
				simp = true;
			}
			//e)
			if (not simp and d.tipus() == token::CANVI_DE_SIGNE) {
				token aux(token::DIVISIO);
				n->_info = n->_dret->_info;
				n->_dret->_info = aux;
				n->_dret->_esq = rec_preordre_copia(n->_esq);
				destrueix_expressio(n->_esq);
				n->_esq = nullptr;
				simp = true;
			}
			//f)
			if (not simp and d.tipus() == token::DIVISIO) {
				if (n->_dret->_esq->_info.tipus() == token::CT_ENTERA) {
					if (n->_dret->_esq->_info.valor_enter() == 1) {
						token aux(token::MULTIPLICACIO);
						n->_info = aux;
						node *aux2 = rec_preordre_copia(n->_dret->_dret);
						destrueix_expressio(n->_dret);
						n->_dret = rec_preordre_copia(aux2);
						destrueix_expressio(aux2);
						simp = true;
					}
				} 
				if (not simp and n->_dret->_esq->_info.tipus() == token::CT_REAL) {
					if (n->_dret->_esq->_info.valor_real() == 1.0) {
						token aux(token::MULTIPLICACIO);
						n->_info = aux;
						node *aux2 = rec_preordre_copia(n->_dret->_dret);
						destrueix_expressio(n->_dret);
						n->_dret = rec_preordre_copia(aux2);
						destrueix_expressio(aux2);
						simp = true;
					}
				}
			}
			if (not simp and e.tipus() == token::EXPONENCIACIO and d.tipus() == token::EXPONENCIACIO) {
				//g)
				if (rec_inordre_iguals(n->_esq->_dret, n->_dret->_dret)) {
					destrueix_expressio(n->_esq->_dret);
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					n->_esq->_info = n->_info;
					n->_info = n->_dret->_info;
					node *aux = rec_preordre_copia(n->_dret->_dret);
					destrueix_expressio(n->_dret);
					n->_dret = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
				//h)
				if (not simp and rec_inordre_iguals(n->_esq->_esq, n->_dret->_esq)) {
					destrueix_expressio(n->_dret->_esq);
					n->_dret->_esq = rec_preordre_copia(n->_esq->_dret);
					node *aux = rec_preordre_copia(n->_esq->_esq);
					destrueix_expressio(n->_esq);
					n->_esq = rec_preordre_copia(aux);
					n->_info = n->_dret->_info;
					token aux2(token::RESTA);
					n->_dret->_info = aux2;
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//i)
			if (not simp and e.tipus() == token::EXP and d.tipus() == token::EXP) {
				n->_info = n->_dret->_info;
				node *aux = rec_preordre_copia(n->_esq->_dret);
				destrueix_expressio(n->_esq);
				n->_esq = nullptr;
				token aux2(token::RESTA);
				n->_dret->_info = aux2;
				n->_dret->_esq = rec_preordre_copia(aux);
				destrueix_expressio(aux);
			}	
		}
		
		//Regla 7
		if (not simp and t.tipus() == token::EXPONENCIACIO) {
			//a)
			if (d.tipus() != token::CT_ENTERA) {
				if (e.tipus() == token::CT_ENTERA) {
					if (e.valor_enter() < 0) {
						throw error(NegatElevNoEnter);
					}
				}
				if (e.tipus() == token::CT_REAL) {
					if (e.valor_real() < 0.0) {
						throw error(NegatElevNoEnter);
					}
				}
				if (e.tipus() == token::CT_RACIONAL) {
					if (e.valor_racional().num() < 0) {
						throw error(NegatElevNoEnter);
					}
				}
			}
			if (e.tipus() == token::CT_REAL) {
				if (d.tipus() == token::CT_REAL) {
					token aux(pow(e.valor_real(),d.valor_real()));
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}	
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (e.tipus() == token::CT_ENTERA) {
					if (d.valor_enter() >= 0) {
						int enter = pow(e.valor_enter(),d.valor_enter());
						token aux(enter);
						n->_info = aux;
					}
					else {
						int enter = pow(e.valor_enter(),-d.valor_enter());
						racional R(1,enter);
						token aux(R);
						n->_info = aux;
					}	
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
				if (not simp and e.tipus() == token::CT_REAL) {
					token aux(pow(e.valor_real(),d.valor_enter()));
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
				if (not simp and e.tipus() == token::CT_RACIONAL) {
					if (d.valor_enter() >= 0) {
						racional R(pow(e.valor_racional().num(),d.valor_enter()), pow(e.valor_racional().denom(),d.valor_enter()));
						token aux(R);
						n->_info = aux;
					}
					else {
						racional R(pow(e.valor_racional().denom(),-d.valor_enter()), pow(e.valor_racional().num(),-d.valor_enter()));
						token aux(R);
						n->_info = aux;
					}
					destrueix_expressio(n->_esq);
					destrueix_expressio(n->_dret);
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}
			//b)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 0) {
					token aux(1);
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if (d.valor_enter() == 0.0) {
					token aux(1);
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				if (d.valor_racional().num() == 0) {
					token aux(1);
					destrueix_expressio(n);
					n = new node;
					n->_info = aux;
					n->_esq = nullptr;
					n->_dret = nullptr;
					simp = true;
				}
			}
			//c)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if (d.valor_enter() == 1) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if (d.valor_enter() == 1.0) {
					node *aux = rec_preordre_copia(n->_esq);
					destrueix_expressio(n);
					n = rec_preordre_copia(aux);
					destrueix_expressio(aux);
					simp = true;
				}
			}
			//d)
			if (not simp and d.tipus() == token::CANVI_DE_SIGNE) {
				n->_dret->_esq = rec_preordre_copia(n->_esq);
				n->_dret->_info = n->_info;
				token aux(1);
				destrueix_expressio(n->_esq);
				n->_esq = new node;
				n->_esq->_info = aux;
				n->_esq->_esq = nullptr;
				n->_esq->_dret = nullptr;
				token aux2(token::DIVISIO);
				n->_info = aux2;
				simp = true;
			}
			//e)
			if (not simp and e.tipus() == token::EXPONENCIACIO) {
				node *aux = rec_preordre_copia(n->_esq->_dret);
				node *aux2 = rec_preordre_copia(n->_esq->_esq);
				destrueix_expressio(n->_esq);
				n->_esq = rec_preordre_copia(aux2);
				node *aux3 = rec_preordre_copia(n->_dret);
				destrueix_expressio(n->_dret);
				n->_dret = new node;
				token aux4(token::MULTIPLICACIO);
				n->_dret->_info = aux4;
				n->_dret->_esq = rec_preordre_copia(aux);
				n->_dret->_dret = rec_preordre_copia(aux3);
				destrueix_expressio(aux);
				destrueix_expressio(aux2);
				destrueix_expressio(aux3);
				simp = true;
			}
			//f)
			if (not simp and e.tipus() == token::EXP) {
				node *aux = rec_preordre_copia(n->_esq->_dret);
				node *aux2 = rec_preordre_copia(n->_dret);
				n->_info = n->_esq->_info;
				token aux3(token::MULTIPLICACIO);
				destrueix_expressio(n->_esq);
				n->_esq = nullptr;
				destrueix_expressio(n->_dret);
				n->_dret = new node;
				n->_dret->_info = aux3;
				n->_dret->_esq = rec_preordre_copia(aux);
				n->_dret->_dret = rec_preordre_copia(aux2);
				destrueix_expressio(aux);
				destrueix_expressio(aux2);
				simp = true;
			}	
		}
		
		
		//Regla 8
		if (not simp and t.tipus() == token::SQRT) {
			//a)
			if (d.tipus() == token::CT_ENTERA) {
				if(d.valor_enter() < 0) {
					throw error(SqrtDeNegatiu);
				}
			}
			if (d.tipus() == token::CT_REAL) {
				if(d.valor_real() < 0.0) {
					throw error(SqrtDeNegatiu);
				}
			}
			if (d.tipus() == token::CT_RACIONAL) {
				if(d.valor_racional().num() < 0) {
					throw error(SqrtDeNegatiu);
				}
			}
			//b)
			if (d.tipus() == token::CT_ENTERA) {
				if(d.valor_enter() == 0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if(d.valor_real() == 0.0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				if(d.valor_racional().num() == 0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			//c)
			if (not simp and d.tipus() == token::CT_REAL) {
				token aux(sqrt(d.valor_real()));
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			//d)
			if (not simp) {
				token aux(token::EXPONENCIACIO);
				n->_info = aux;
				n->_esq = rec_preordre_copia(n->_dret);
				destrueix_expressio(n->_dret);
				n->_dret = new node;
				racional R (1,2);
				token aux2(R);
				n->_dret->_info = aux2;
				n->_dret->_esq = nullptr;
				n->_dret->_dret = nullptr;
				simp = true;
			}
		}
		
		
		//Regla 9
		if (not simp and t.tipus() == token::EXP) {
			//a)
			if (d.tipus() == token::CT_ENTERA) {
				if(d.valor_enter() == 0) {
					token aux(1);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if(d.valor_real() == 0.0) {
					token aux(1);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				if(d.valor_racional().num() == 0) {
					token aux(1);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			//b)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if(d.valor_enter() == 1) {
					token aux(token::CT_E);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if(d.valor_real() == 1.0) {
					token aux(token::CT_E);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			//c
			if (not simp and d.tipus() == token::LOG) {
				node *aux = rec_preordre_copia(n->_dret->_dret);
				destrueix_expressio(n);
				n = rec_preordre_copia(aux);
				destrueix_expressio(aux);
				simp = true;
			}
		}
		if (not simp and t.tipus() == token::LOG) {
			//d)
			if (d.tipus() == token::CT_ENTERA) {
				if(d.valor_enter() <= 0) {
					throw error(LogDeNoPositiu);
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if(d.valor_real() <= 0.0) {
					throw error(LogDeNoPositiu);
				}
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				if(d.valor_racional().num() <= 0) {
					throw error(LogDeNoPositiu);
				}
			}
			//e)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				if(d.valor_enter() == 1) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			if (not simp and d.tipus() == token::CT_REAL) {
				if(d.valor_real() == 1.0) {
					token aux(0);
					n->_info = aux;
					destrueix_expressio(n->_dret);
					n->_dret = nullptr;
					simp = true;
				}
			}
			//f)
			if (not simp and d.tipus() == token::CT_E) {
				token aux(1);
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			//g)
			if (not simp and d.tipus() == token::EXP) {
				node *aux = rec_preordre_copia(n->_dret->_dret);
				destrueix_expressio(n);
				n = rec_preordre_copia(aux);
				destrueix_expressio(aux);
				simp = true;
			}
			//h)
			if (not simp and d.tipus() == token::MULTIPLICACIO) {
				node *aux = rec_preordre_copia(n->_dret->_esq);
				n->_dret->_info = n->_info;
				destrueix_expressio(n->_dret->_esq);
				n->_dret->_esq = nullptr;
				n->_esq = new node;
				n->_esq->_info = n->_info;
				n->_esq->_esq = nullptr;
				token aux3(token::SUMA);
				n->_info = aux3;
				n->_esq->_dret = rec_preordre_copia(aux);
				simp = true;
			}
			//i)
			if (not simp and d.tipus() == token::DIVISIO) {
				node *aux = rec_preordre_copia(n->_dret->_esq);
				n->_dret->_info = n->_info;
				destrueix_expressio(n->_dret->_esq);
				n->_dret->_esq = nullptr;
				n->_esq = new node;
				n->_esq->_info = n->_info;
				n->_esq->_esq = nullptr;
				token aux3(token::RESTA);
				n->_info = aux3;
				n->_esq->_dret = rec_preordre_copia(aux);
				simp = true;
			}
			//j)
			if (not simp and d.tipus() == token::EXPONENCIACIO) {
				token aux2(token::MULTIPLICACIO);
				n->_dret->_info = n->_info;
				n->_info = aux2;
				n->_esq = rec_preordre_copia(n->_dret->_dret);
				destrueix_expressio(n->_dret->_dret);
				n->_dret->_dret = rec_preordre_copia(n->_dret->_esq);
				destrueix_expressio(n->_dret->_esq);
				n->_dret->_esq = nullptr;
				simp = true;
			}
		}
		//k)
		if (not simp and t.tipus() == token::EXP) {
			if (d.tipus() == token::CT_REAL) {
				token aux(exp(d.valor_real()));
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
		}
		if (not simp and t.tipus() == token::LOG) {
			if (d.tipus() == token::CT_REAL) {
				token aux(log(d.valor_real()));
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
		}
		
		
		//Regla 10
		if (not simp and t.tipus() == token::EVALF) {
			//a)
			if (d.tipus() == token::CT_REAL) {
				n->_info = d;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			//b)
			if (not simp and d.tipus() == token::CT_ENTERA) {
				double real = d.valor_enter();
				token aux(real);
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			if (not simp and d.tipus() == token::CT_RACIONAL) {
				double real = d.valor_racional().num();
				real /= d.valor_racional().denom();
				token aux(real);
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			//c)
			if (not simp and d.tipus() == token::CT_E) {
				//hem de ficar long double????
				double real = 2.718281828;
				token aux(real);
				n->_info = aux;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			//d)
			if (not simp and (d.tipus() == token::VARIABLE or d.tipus() == token::VAR_PERCENTATGE)) {
				//Si no té valor
				n->_info = d;
				destrueix_expressio(n->_dret);
				n->_dret = nullptr;
				simp = true;
			}
			//e)
			if (not simp and operador(d)) {
				if (binari(d)) {
					token aux(n->_dret->_info);
					n->_esq = new node;
					n->_esq->_info = n->_info;
					n->_dret->_info = n->_info;
					n->_info = aux;
					n->_esq->_dret = rec_preordre_copia(n->_dret->_esq);
					destrueix_expressio(n->_dret->_esq);
					n->_esq->_esq = nullptr;
					n->_dret->_esq = nullptr;
					simp = true;
				}
				if (not simp and not binari(d)) {
					if (d.tipus() != token::EVALF) {
						token aux(token::EVALF);
						n->_info = n->_dret->_info;
						n->_dret->_info = aux;
						simp = true;
					}
				}
			}
		}	
	}
	return n;
}

expressio::node* expressio::rec_preordre_copia(node *n)
//Pre: Cert
//Post: Retorna una punter a l'arrel de la copia de l'expressio on n és l'arrel
{	
	node *aux = nullptr;
	if (n != nullptr) {
		aux = new node;
		aux->_info = n->_info;
		aux->_esq = rec_preordre_copia(n->_esq);
		aux->_dret = rec_preordre_copia(n->_dret);
	}
	return aux;
}
 
void expressio::destrueix_expressio(node *n)
//Pre: Cert
//Post: Destrueix l'expressio on n és l'arrel
{
	if (n != nullptr) {
		destrueix_expressio(n->_esq);
		destrueix_expressio(n->_dret);
		delete n;
	}
}

bool expressio::rec_inordre_iguals (node *n, node *m)
//Pre: Cert
//Post: Retorna un boolea == true si l'expressió on n és l'arrel és igual a la expressió on m és l'arrel i retorna un boolea == false si no ho són
{
	bool igual = true;
	if (n == nullptr and m == nullptr) {
		igual = true;
	}
	else if ((n == nullptr and m != nullptr) or (n != nullptr and m == nullptr)) {
		igual = false;
	}
	else if (n != nullptr and m != nullptr){
		if (n->_info != m->_info) {
			igual = false;
		}
		if (igual) {
			igual = rec_inordre_iguals(n->_esq, m->_esq);
		}
		if (igual) {	
			igual = rec_inordre_iguals(n->_dret, m->_dret);
		}	
	}
	return igual;
}

void expressio::rec_inordre_variables(node *n, list<string> & l)
//Pre: Cert
//Post: Recorre tota l'expressió on n és l'arrel i introdueix a la llista l els identificadors de totes les variables
{
	if (n != nullptr) {
		if (n->_info.tipus() == token::VARIABLE or n->_info.tipus() == token::VAR_PERCENTATGE) {
			l.push_front(n->_info.identificador_variable());
		}
		rec_inordre_variables(n->_esq,l);	
		rec_inordre_variables(n->_dret,l);	
	}
}

expressio::node* expressio::rec_inordre_canvi(node *n, const string & v, const expressio & e)
//Pre: Cert
//Post: Retorna un punter al node n després de substituir a l'expressio on n és l'arrel la variable d'identificador == v per l'expressió e. Si la variable no existeix no fa res
{
	if (n != nullptr) {
		if (n->_info.tipus() == token::VARIABLE) {
			if (n->_info.identificador_variable() == v) {
				n = rec_preordre_copia(e._arrel); 
			}
		}
		if (n->_info.tipus() == token::VAR_PERCENTATGE) {
			if ("%" == v) {
				n = rec_preordre_copia(e._arrel);
			}	 
		}
		n->_esq=rec_inordre_canvi(n->_esq,v,e);	
		n->_dret=rec_inordre_canvi(n->_dret,v,e);	
	}
	return n;
}

void expressio::rec_inordre_llista(node *n, node *ant, list<token> & lt)
//Pre: Cert
//Post: Recorre una expressió on n és l'arrel i introduiex a lt la expressió matemàtica amb els parèntesis imprescindibles
{
	if (n != nullptr) {
		token t = n->_info;
		if (ant != nullptr) {
			token tant = ant->_info;
			if (operador(tant) and not funcio(tant)) {
				if (operador(t) and t.tipus() != token::EXPONENCIACIO) {
					if (prioritat(tant,t)) {
						token aux(token::OBRIR_PAR);
						lt.push_back(aux);	
					}
				}		
			}
			if (n == ant->_esq) {
				if (t.tipus() == token::EXPONENCIACIO and tant.tipus() == token::EXPONENCIACIO) {
					token aux(token::OBRIR_PAR);
					lt.push_back(aux);
				}
			}
			if (t.tipus() == token::EXPONENCIACIO and tant.tipus() == token::EXPONENCIACIO) {
				if (n->_esq->_info.tipus() == token::CT_RACIONAL) {
					token aux(token::OBRIR_PAR);
					lt.push_back(aux);
				}
			}
		}
	
		
		rec_inordre_llista(n->_esq,n,lt);
		if (ant != nullptr) {
			token tant = ant->_info;
			if (t.tipus() == token::EXPONENCIACIO and tant.tipus() == token::EXPONENCIACIO) {
				if (n->_esq->_info.tipus() == token::CT_RACIONAL) {
					token aux(token::TANCAR_PAR);
					lt.push_back(aux);
				}
			}
		}
		lt.push_back(t);
		if (funcio(t)) {
			token aux(token::OBRIR_PAR);
			lt.push_back(aux);
		}
		if (t.tipus() ==token::EXPONENCIACIO and n->_dret->_info.tipus() == token::CT_RACIONAL) {
			token aux(token::OBRIR_PAR);
			lt.push_back(aux);
		}
		if (t.tipus() == token::DIVISIO or t.tipus() == token::RESTA) {
			if (operador(n->_dret->_info) and not prioritat(n->_dret->_info,n->_info)) {
				token aux(token::OBRIR_PAR);
				lt.push_back(aux);	
			}	
		}
		
		
		rec_inordre_llista(n->_dret,n,lt);
		if (funcio(t)) {
			token aux(token::TANCAR_PAR);
			lt.push_back(aux);
		}
		if (t.tipus() ==token::EXPONENCIACIO and n->_dret->_info.tipus() == token::CT_RACIONAL) {
			token aux(token::TANCAR_PAR);
			lt.push_back(aux);
		}
		if (t.tipus() == token::DIVISIO or t.tipus() == token::RESTA) {
			if (operador(n->_dret->_info) and not prioritat(n->_dret->_info,n->_info)) {
				token aux(token::TANCAR_PAR);
				lt.push_back(aux);	
			}	
		}
		if (ant != nullptr) {
			token tant = ant->_info;
			if (operador(tant) and not funcio(tant)) {
				if (operador(t) and t.tipus() != token::EXPONENCIACIO) {
					if (prioritat(tant,t)) {
						token aux(token::TANCAR_PAR);
						lt.push_back(aux);	
					}	
				}	
			}
			if (n == ant->_esq) {
				if (t.tipus() == token::EXPONENCIACIO and tant.tipus() == token::EXPONENCIACIO) {
				token aux(token::TANCAR_PAR);
				lt.push_back(aux);
				}
			}	
		}
	}
}

/* Constructora d'una expressió formada per un sol token: un operand. Si
   s'utiliza el valor del token per defecte es construeix la que
   anomenem "expressió buida". Si el tipus del token no és el del token
   per defecte (NULLTOK), ni el d'una CT_ENTERA, CT_RACIONAL, CT_REAL,
   CT_E, VARIABLE o VAR_PERCENTAtGE es produeix un error sintàctic. */
expressio::expressio(const token t) throw(error)
//Pre: Cert
//Post: Crea una expressió d'un únic node, on el node és el node t. Si t no és un operand retorna error(ErrorSintactic)
{
	if (not operand(t)) {
		throw error(ErrorSintactic);
	}	
	_arrel = new node;
	_arrel->_info = t;
	_arrel->_esq = nullptr;
	_arrel->_dret = nullptr;
}

/* Constructora a partir d'una seqüència de tokens. Es produeix un error si
   la seqüència és buida o si no es pot construir l'arbre d'expressió
   corresponent(és a dir, si és sintàcticament incorrecta). */
expressio::expressio(const list<token> & l) throw(error)
//Pre: Cert
//Post: Crea una expressió de la llista de tokens l. Retorna error(ErrorSintactic) si l és buida o no és correcta matemàticament
{
	if (l.size() == 0) {
		throw error(ErrorSintactic); 
	}
	stack<expressio> exp;
	stack<token> op;
	list<token>::const_iterator p = l.begin();
	list<token>::const_iterator post = l.begin();
	post++;	
	while (p != l.end()) {
		token t = *p;
		if (p == l.begin()) {
			if (operador(t) and binari(t)) {
				throw error(ErrorSintactic);
			}
		}
		if (not operand(t) and not operador(t)) {
			throw error(ErrorSintactic); 
		}
		if (post != l.end()) {
			if (not correcte(p,post)) {
				throw error (ErrorSintactic);
			}
		}
		if (operand(t)) {
			exp.push(expressio(t));
		}
		else {
			if (op.size() == 0 and t.tipus() != token::TANCAR_PAR) {
				op.push(t);
			}
			else if (t.tipus() == token::TANCAR_PAR) {
				while (op.top().tipus() != token::OBRIR_PAR) {
					expressio e;
					if (op.size() == 0) {
						throw error(ErrorSintactic); 
					}
					e._arrel->_info = op.top();
					if (exp.size() == 0) {
						throw error(ErrorSintactic); 
					}
					expressio d(exp.top());
					e._arrel->_dret = d._arrel;
					d._arrel = nullptr;
					exp.pop();
					if (binari(op.top())) {
					
						if (exp.size() == 0) {
							throw error(ErrorSintactic); 
						}
						expressio i(exp.top());
						e._arrel->_esq = i._arrel;
						i._arrel = nullptr;
						exp.pop();
					}
					else {
						e._arrel->_esq = nullptr;
					}
					exp.push(e);
					op.pop();
					if (op.size()  == 0) {
						throw error(ErrorSintactic);
					}
					
				}
				if (op.size() != 0) {
					op.pop();
				}
			}
			else if (t.tipus() == token::OBRIR_PAR) {
				op.push(t);
			}
			else {
				if (prioritat(t,op.top())) {
					op.push(t);
				}
				else {
					while (op.size() != 0 and not prioritat(t,op.top())) {
						expressio e;
						
						if (op.size() == 0) {
							throw error(ErrorSintactic); 
						}
						
						e._arrel->_info = op.top();
						
						if (exp.size() == 0) {
							throw error(ErrorSintactic); 
						}
						expressio d(exp.top());
						e._arrel->_dret = d._arrel;
						d._arrel = nullptr;
						exp.pop();
						if (binari(op.top())) {
						
							if (exp.size() == 0) {
								throw error(ErrorSintactic); 
							}
							
							expressio i(exp.top());
							e._arrel->_esq = i._arrel;
							i._arrel = nullptr;
							exp.pop();
						}
						else {
							e._arrel->_esq = nullptr;
						}
						exp.push(e);
						op.pop();
					}	
					op.push(t);
				}
			}
		}
		++post;
		++p;	
	}
	while (op.size() != 0) {
		if (op.top().tipus() == token::OBRIR_PAR) {
			throw error(ErrorSintactic);
		}
		expressio e;
		e._arrel->_info = op.top();
		if (exp.size() == 0) {
			throw error(ErrorSintactic); 
		}

		expressio d(exp.top());
		e._arrel->_dret = d._arrel;
		d._arrel = nullptr;
		exp.pop();
		if (binari(op.top())) {
			if (exp.size() == 0) {
				throw error(ErrorSintactic); 
			}
			expressio i(exp.top());
			e._arrel->_esq = i._arrel;
			i._arrel = nullptr;
			exp.pop();
		}
		else {
			e._arrel->_esq = nullptr;
		}
		exp.push(e);
		op.pop();
	}
	if (exp.size() != 1) {
		throw error(ErrorSintactic);
	}
	_arrel = rec_preordre_copia(exp.top()._arrel);
}	

// Constructora per còpia, assignació i destructora.
expressio::expressio(const expressio & e) throw(error)
//Pre: Cert
//Post: Crea una copia de l'expressió e
{
	_arrel = rec_preordre_copia(e._arrel);
}
expressio & expressio::operator=(const expressio & e) throw(error)
//Pre: Cert
//Post: Retorna una copia de l'expressio e
{
	destrueix_expressio(_arrel);
	_arrel = rec_preordre_copia(e._arrel);
	return *this;
}
expressio::~expressio() throw(error)
{
	destrueix_expressio(_arrel);
}

// Retorna cert si i només si s'aplica a l'expressió buida.
expressio::operator bool() const throw()
//Pre: Cert
//Post: Retorna un boolea == true si l'expressió és buida i retorna un boolea == false si no ho és
{
	if (_arrel->_info.tipus() == token::NULLTOK) {
		return true;
	}
	else {
		return false;
	}
}

/* Operadors d'igualtat i desigualtat. Dues expressions es consideren
   iguals si i només si els seus arbres d'expressió són idèntics. */
bool expressio::operator==(const expressio & e) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si l'expressió e és igual a la expressió implícita i retorna un boolea == false si no ho són
{
	return rec_inordre_iguals(_arrel, e._arrel);
}
bool expressio::operator!=(const expressio & e) const throw()
//Pre: Cert
//Post: Retorna un boolea == true si l'expressió e és diferent a la expressió implícita i retorna un boolea == false si no ho són
{
	return not (*this == e);
}

/* Retorna una llista sense repeticions, en qualsevol ordre, amb
   els noms de les variables de l'expressió. */
void expressio::vars(list<string> & l) const throw(error)
//Pre: Cert
//Post: S'introdueix a la llista l les variables de l'expressió implícita sense repeticions
{
	rec_inordre_variables(_arrel,l);
	l.sort();
	list<string>:: iterator p = l.begin();
	list<string>:: iterator pant = l.begin();
	++p;
	
	while (p != l.end()) {
		if (*p == *pant) {
			p = l.erase(p);
		}
		else {
			++p;
		}
		pant = p;
		--pant;
	}
}

/* Substitueix totes les aparicions de la variable de nom v per
   l'expressió e. Si no existeix la variable v dins de l'expressió a la
   que apliquem aquest mètode l'expressió no es modifica. */
void expressio::apply_substitution(const string & v, const expressio & e) throw(error)
//Pre: Cert
//Post: Substitueix a l'expressió implícita la variable amb identificador == v per l'expressió e
{
	_arrel = rec_inordre_canvi(_arrel,v,e);
}

/* Aplica un pas de simplificació a l'expressió. La subexpressió a
   simplificar es busca seguint el recorregut "left to right" postordre
   explicat a l'apartat "Procés d'avaluació". Es pot produir qualsevol dels
   errors semàntics que apareixen més avall numerats des del 32 al 35. */
void expressio::simplify_one_step() throw(error)
//Pre: Cert
//Post: Aplica una simplificació a l'expressió implícita
{
	bool simp = false;
	_arrel = rec_postordre_simplify(_arrel,simp);
}

/* Aplica successius passos de simplificació com l'anterior fins que
   l'expressió es trobi completament simplificada. Llavors diem que es
   troba en "forma normal". Es pot produir qualsevol dels errors
   semàntics que apareixen més avall numerats des del 32 al 35. */
void expressio::simplify() throw(error)
//Pre: Cert
//Post: Simplifica l'expressió implícita fins que ja no és pot simplificar
{
	bool simp = false;
	bool fora = false;
	while (not fora) {
		_arrel = rec_postordre_simplify(_arrel,simp);
		if (not simp) {
			fora = true;
		}
		else {
			simp = false;
		}
	}
}

/* Converteix l'expressió en la seqüència de tokens lt corresponent: els
   operadors apareixen entre els operands si són infixos, abans si són
   prefixos i els símbols de funció van seguits de parèntesis que tanquen
   els seus arguments separats per comes. S'han d'introduir només aquells
   parèntesis que siguin estrictament necessaris per trencar les regles de
   precedència o associativitat en l'ordre d'aplicació dels operadors. */
void expressio::list_of_tokens(list<token> & lt) throw(error)
//Pre: Cert
//Post: S'introdueix a la llista de tokens lt l'expressió matemàtica de l'expressió implícita amb els parentèsis imprescindibles
{
	rec_inordre_llista(_arrel,nullptr,lt);
}
