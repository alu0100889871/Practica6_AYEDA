#include<iostream>
#include<queue>
#include"../NodoABB/NodoABB.hpp"

using namespace std;

#ifndef ARBOLBINARIO_HPP_
#define ARBOLBINARIO_HPP_

template<class Clave>
class ABB {
	NodoBB<Clave>* root_; //raíz (nodo superior del árbol)
public:
	ABB() :
		root_(NULL) 
		{};
	~ABB(void);
	NodoBB<Clave>* search(NodoBB<Clave>* clave, int& comparations);
	void insert(NodoBB<Clave>* clave, int& comparations);
	void eliminar(NodoBB<Clave>* clave);
	ostream& write(ostream& os);

};

template<class Clave>
ABB<Clave>::~ABB(void) {}

//Buscamos en el árbol la clave de forma recursiva

template<class Clave>
NodoBB<Clave>* ABB<Clave>::search(NodoBB<Clave>* clave, int& comparations_) {
	if (root_ == NULL)
		return NULL;
	else
		root_->search(clave, comparations_);
}

//Mostrar por pantalla el nivel del árbol

template<class Clave>
ostream& ABB<Clave>::write(ostream& os) {
	queue<NodoBB<Clave>*> cola;
	int nivel = 0;
	if (root_ != NULL) {
		cola.push(root_);
		cout << "Nivel " << nivel << ":";
		while (!cola.empty()) {
			NodoBB<Clave>* nodo = cola.front();
			cola.pop();
			if (nodo->get_nivel() != nivel) {
				nivel++;
				os << endl;
				cout << "Nivel " << nivel << ":";

			}
			nodo->write(cout);
			if (nodo->get_izquierdo() != NULL)
				cola.push(nodo->get_izquierdo());
			if (nodo->get_derecho() != NULL)
				cola.push(nodo->get_derecho());

		}
		os << endl;
		os << endl;
	}
	return os;
}

//Insertar un nodo en el arbol (por la raíz)

template<class Clave>
void ABB<Clave>::insert(NodoBB<Clave>* clave, int& comparations_) {
	if (root_ == NULL) {
		root_ = clave;

	} else
		root_->insert(clave, comparations_);

}

//Eliminar

template<class Clave>
void ABB<Clave>::eliminar(NodoBB<Clave>* clave) {
	int comparations = 0;
	if (root_ == NULL)
		cerr << "Raíz Nula" << endl;

	else {
		clave = search(clave, comparations);
		if (clave != NULL) {
			if (clave != root_)
				root_->eliminar(clave);
			else
				root_->eliminar(root_);
		}
	}

}
#endif /* ARBOLBINARIO_HPP_ */

