#ifndef NODOABB_HPP_
#define NODOABB_HPP_

#include<iostream>
#include<queue>

using namespace std;

template<class Clave>
class NodoBB {
	Clave dato_;
	int nivel_;
	NodoBB<Clave>* izquierdo_;
	NodoBB<Clave>* derecho_;
	NodoBB<Clave>* padre_;
public:
	NodoBB(Clave dato) :
		izquierdo_(NULL), derecho_(NULL), padre_(NULL), dato_(dato), nivel_(0) 
		{}
	NodoBB(void) :
		izquierdo_(NULL), derecho_(NULL), padre_(NULL), dato_(0), nivel_(0) 
		{}
	~NodoBB(void);
	NodoBB<Clave>* search(NodoBB<Clave>* clave, int& comparations);
	void insert(NodoBB<Clave>* clave, int& comparations);
	void eliminar(NodoBB<Clave>*& clave);
	NodoBB<Clave>* get_izquierdo(void) {
		return izquierdo_;
	}
	NodoBB<Clave>* get_derecho(void) {
		return derecho_;
	}
	NodoBB<Clave>* get_padre(void) {
		return padre_;
	}
	Clave get_dato(void) {
		return dato_;
	}
	int get_nivel(void) {
		return nivel_;
	}

	void cero_hijos(NodoBB<Clave>*& clave);
	void un_hijo(NodoBB<Clave>*& clave);
	void dos_hijos(NodoBB<Clave>* clave);
	void reducir_nivel_rama(NodoBB<Clave>* clave);

	ostream& write(ostream& os);
};

//Destructor

template<class Clave>
NodoBB<Clave>::~NodoBB(void) {
	if (izquierdo_ != NULL) {
		delete izquierdo_;
		izquierdo_ = NULL;
	}
	if (derecho_ != NULL) {
		delete derecho_;
		derecho_ = NULL;
	}
	if (padre_ != NULL) {
		delete padre_;
		padre_ = NULL;
	}

}

//Mostrar el dato que haya en un nivel específico

template<class Clave>
ostream& NodoBB<Clave>::write(ostream& os) {
	os << "[" << dato_ << "] ";
	return os;

}

//Búsqueda de un nodo especifíco, si es menos que ese nodo vamos a buscarlo a su hijo hizquiedo, si no al derecho

template<class Clave>
NodoBB<Clave>* NodoBB<Clave>::search(NodoBB<Clave>* clave, int& comparations) {
	comparations++;
	if (clave == NULL) {
		cerr << "ERROR: Nodo nulo" << endl;
		return NULL;
	} else if (clave->dato_ == dato_)
		return this;
	else if (clave->dato_ < dato_) {
		if (izquierdo_ == NULL)
			return NULL;
		else
			izquierdo_->search(clave, comparations);

	} else if (clave->dato_ > dato_) {
		if (derecho_ == NULL)
			return NULL;

		else
			derecho_->search(clave, comparations);

	}
}

//Insertar un nodo, añadimos un nuevo nivel si es menor a la izquierda, si es mayor a la derecha

template<class Clave>
void NodoBB<Clave>::insert(NodoBB<Clave>* clave, int& comparations) {
	clave->nivel_++;

	if (clave == NULL)
		cerr << "ERROR: Nodo nulo" << endl;
	else if (clave->dato_ < dato_) {
		if (izquierdo_ == NULL) {
			izquierdo_ = clave;
			clave->padre_ = this;
		} else
			izquierdo_->insert(clave, comparations);

	} else if (clave->dato_ > dato_) {
		if (derecho_ == NULL) {
			derecho_ = clave;
			clave->padre_ = this;
		} else
			derecho_->insert(clave, comparations);

	}
}

//Eliminamos nodo

template<class Clave>
void NodoBB<Clave>::eliminar(NodoBB<Clave>*& clave) {
	if (clave == NULL)
		cerr << "ERROR: Nodo nulo" << endl;

	else if (clave->izquierdo_ == NULL && clave->derecho_ == NULL) // si no tiene hijos vamos al método cero_hijos
		cero_hijos(clave);

	else if ((clave->izquierdo_ != NULL && clave->derecho_ == NULL) || (clave->izquierdo_ == NULL && clave->derecho_ != NULL)) //si el padre tiene un hijo
		un_hijo(clave);

	else
		dos_hijos(clave);

}

//Cuando eliminamos un nodo y no tenía hijos vamos a este método

template<class Clave>
void NodoBB<Clave>::cero_hijos(NodoBB<Clave>*& clave) {
	if (clave->padre_ != NULL) {
		if (clave->dato_ < clave->padre_->dato_) //miramos lado izquierdo para eliminar
			clave->padre_->izquierdo_ = NULL;
		else if (clave->dato_ > clave->padre_->dato_) //miramos lado derecho para eliminar
			clave->padre_->derecho_ = NULL;
		clave->padre_ = NULL;
	}
	delete clave;
	clave = NULL;
}

//Cuando eliminamos un nodo y tiene un hijo va a este método

template<class Clave>
void NodoBB<Clave>::un_hijo(NodoBB<Clave>*& clave) {
	if (clave->padre_ != NULL) { //si el padre no es nulo
		if (clave->izquierdo_ != NULL && clave->derecho_ == NULL) { //miramos si tiene el nodo en la izquierda
			clave->izquierdo_->padre_ = clave->padre_;
			if (clave == clave->padre_->izquierdo_)
				clave->padre_->izquierdo_ = clave->izquierdo_;
			else
				clave->padre_->derecho_ = clave->izquierdo_;
			reducir_nivel_rama(clave->izquierdo_);
			clave->padre_ = NULL;
			clave->izquierdo_ = NULL;
			delete clave;
			clave = NULL;
		} else if (clave->izquierdo_ == NULL && clave->derecho_ != NULL) { //miramos si tiene el nodo en la derecha

			clave->derecho_->padre_ = clave->padre_;
			if (clave == clave->padre_->derecho_)
				clave->padre_->derecho_ = clave->derecho_;
			else
				clave->padre_->izquierdo_ = clave->derecho_;
			reducir_nivel_rama(clave->derecho_);
			clave->padre_ = NULL;
			clave->derecho_ = NULL;
		}
		delete clave;
		clave = NULL;
	} else {
		if (clave->izquierdo_ != NULL)
			clave = clave->izquierdo_;
		else if (clave->derecho_ != NULL)
			clave = clave->derecho_;
			
		reducir_nivel_rama(clave);
		clave->padre_ = NULL;
	}

}

//Cuando eliminamos un nodo y tiene dos hijo va a este método

template<class Clave>
void NodoBB<Clave>::dos_hijos(NodoBB<Clave>* clave) {
	NodoBB<Clave>* aux = clave;
	clave = clave->izquierdo_;
	while (clave->derecho_ != NULL)
		clave = clave->derecho_;
	Clave dato = clave->dato_;
	if (clave->izquierdo_ == NULL && clave->derecho_ == NULL)
		cero_hijos(clave);
	else
		un_hijo(clave);
	aux->dato_ = dato;

}

//Reducimos el nivel de la rama eliminando hijos

template<class Clave>
void NodoBB<Clave>::reducir_nivel_rama(NodoBB<Clave>* clave) {
	queue<NodoBB<Clave>*> cola;
	cola.push(clave);
	while (!cola.empty()) {
		NodoBB<Clave>* nodo = cola.front();
		cola.pop();
		nodo->nivel_--;
		if (nodo->get_izquierdo() != NULL)
			cola.push(nodo->get_izquierdo());
		if (nodo->get_derecho() != NULL)
			cola.push(nodo->get_derecho());

	}
}

#endif /* NODOABB_HPP_ */

