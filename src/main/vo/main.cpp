#include<cstdio>
#include<iostream>
#include<stdlib.h>
#include <iomanip>
#include <limits.h>

#include"ArbolBinario/ArbolBinario.hpp"
#include"NodoABB/NodoABB.hpp"
#include"DNI/DNI.hpp"

//Modo demostración

void demos(ABB<DNI> arbol) {
	int opcion = 1;
	NodoBB<DNI>* nodo;
	int dni;
	int tamanio = 0;
	int comparations = 0;
	while (opcion != 0 && tamanio <= 20) {
		cout << "[0] Salir" << endl;
		cout << "[1] Insertar" << endl;
		cout << "[2] Eliminar" << endl;
		cin >> opcion;
		switch (opcion) {
		case 0:
			cout << "Programa finalizado" << endl;
			break;
		case 1:
			cout << "Introduce un DNI para insertarlo en el árbol: ";
			cin >> dni;
			nodo = new NodoBB<DNI>(dni);
			arbol.insert(nodo, comparations);
			tamanio++;
			break;
		case 2:
			cout << "Introduce el DNI que quieres eliminar: ";
			cin >> dni;
			nodo = new NodoBB<DNI>(dni);
			arbol.eliminar(nodo);
			tamanio--;
			break;
		}
		arbol.write(cout);
		if (tamanio > 20)
			cout << "No hay más espacio en el árbol" << endl;

	}

}

//Modo estadística

void estadistica(ABB<DNI> arbol) {
	int N = 0;
	int pruebas = 0;
	int minimo = INT_MAX;
	int maximo = INT_MIN;
	int acumulado = 0;
	cout << "Introduce el tamaño: ";
	cin >> N;
	cout << "Introduce el número de pruebas: ";
	cin >> pruebas;
	cout << "		  N      Pruebas    Mínimo    Medio       Máximo" << endl;
	cout << "		 -----------------------------------------------" << endl;
	srand(time(NULL)); //inicializamos generador de números aleatios
	vector<DNI> bancopruebas(2 * N, 0);
	for (int i = 0; i < 2 * N; i++) {
		bancopruebas[i] = rand() % 40000000 + 30000000;

	}
	//Búsqueda
	int comparations = 0;
	for (int i = 0; i < N; i++) {
		NodoBB<DNI>* nodo = new NodoBB<DNI>(bancopruebas[i]);
		arbol.insert(nodo, comparations);
	}
	comparations = 0;
	for (int i = 0; i < pruebas; i++) {
		int x = rand() % N;
		NodoBB<DNI>* nodo = new NodoBB<DNI>(bancopruebas[x]);
		arbol.search(nodo, comparations);
		acumulado += comparations;
		if (comparations < minimo)
			minimo = comparations;
		if (comparations > maximo)
			maximo = comparations;
		comparations = 0;
	}
	float media = float(acumulado) / pruebas;
	cout << "Búsqueda" << std::setw(11) << N << std::setw(10) << pruebas << std::setw(10) << minimo << std::setw(11) << media << std::setw(11) << maximo << endl;
	
	//Inserción
	minimo = INT_MAX;
	maximo = INT_MIN;
	acumulado = 0;
	for (int i = 0; i < pruebas; i++) {
		int x = rand() % N + N;
		NodoBB<DNI>* nodo = new NodoBB<DNI>(bancopruebas[x]);
		arbol.search(nodo, comparations);
		acumulado += comparations;
		if (comparations < minimo)
			minimo = comparations;
		if (comparations > maximo)
			maximo = comparations;
		comparations = 0;
	}

	media = float(acumulado) / pruebas;
	cout << "Inserción" << std::setw(10) << N << std::setw(10) << pruebas << std::setw(10) << minimo << std::setw(11) << media << std::setw(11) << maximo << endl;
	arbol.write(cout);
}

//Modo comportamiento

void comportamiento(ABB<DNI> arbol) {
	int tamanios[4];
	tamanios[0] = 10;
	tamanios[1] = 100;
	tamanios[2] = 1000;
	tamanios[3] = 10000;
	int npruebas;
	cout << "Introduce el número de pruebas: ";
	cin >> npruebas;
	cout << "		 	     TAMAÑO                  " << endl;
	cout << setw(19) << 10 << std::setw(9) << 100 << std::setw(9) << 1000 << std::setw(9) << 10000 << endl;
	
	//Búsqueda
	
	cout << "Búsqueda" << std::setw(11);
	for (int j = 0; j < 4; j++) {
		int suma = 0;
		int comparations = 0;
		vector<DNI> v(tamanios[j], 0);
		srand(time(NULL));
		for (int i = 0; i < v.size(); i++)
			v[i] = rand() % 40000000 + 30000000;

		for (int i = 0; i < tamanios[j]; i++) {
			NodoBB<DNI>* nodo = new NodoBB<DNI>(v[i]);
			arbol.insert(nodo, comparations);
		}
		comparations = 0;
		srand(time(NULL));
		for (int k = 0; k < npruebas; k++) { 
			int x = rand() % tamanios[j];

			NodoBB<DNI>* nodo = new NodoBB<DNI>(v[x]);
			arbol.search(nodo, comparations);
			suma += comparations;
			comparations = 0;
		}
		cout << float(suma) / npruebas << std::setw(9); //media de comparaciones con el número de pruebas
	}
	
	//Insercción
	
	cout << endl;
	cout << "Inserción" << std::setw(10);

	for (int j = 0; j < 4; j++) {
		int suma = 0;
		int comparations = 0;
		vector<DNI> v(2 * tamanios[j], 0);
		srand(time(NULL));
		for (int i = 0; i < v.size(); i++)
			v[i] = rand() % 40000000 + 30000000;

		for (int i = 0; i < tamanios[j]; i++) {
			NodoBB<DNI>* nodo = new NodoBB<DNI>(v[i]);
			arbol.insert(nodo, comparations);
		}
		comparations = 0;
		srand(time(NULL));
		for (int k = 0; k < npruebas; k++) {
			int x = rand() % tamanios[j] + tamanios[j];
			NodoBB<DNI>* nodo = new NodoBB<DNI>(v[x]);
			arbol.search(nodo, comparations);
			suma += comparations;
			comparations = 0;
		}
		cout << float(suma) / npruebas << std::setw(9); //media de comparaciones con el número de pruebas

	}
	cout << endl;
}

int main(void) {
	ABB<DNI> arbol;
	int opcion = 0;
	cout << "Elige un modo:" << endl;
	cout << "1. Demostración" << endl;
	cout << "2. Estadística" << endl;
	cout << "3. Comportamiento" << endl;
	cin >> opcion;
	switch (opcion) {
	case 1:
		demos(arbol);
		break;
	case 2:
		estadistica(arbol);
		break;
	case 3:
		comportamiento(arbol);
		break;
	}
}

