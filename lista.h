#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"

using namespace std;

template <typename Dato>

class Lista{

	private:
		Nodo<Dato>* primero;
		int longitud;
	public:
		Lista();
		~Lista();
		Lista(Lista&);
		Lista& operator=(Lista&);
		bool vacia();
		void alta(Dato d, int pos = -1);
		Dato consultar(int pos);
		void baja(int pos);
		int obtener_tamanio();
		void ordenar(bool (Dato::*funcion_comparacion)(const Dato&) = NULL);
		void print(ostream& out = std::cout);
		void filtrar(bool (Dato::*funcion_verificacion)());

	private:
		void swap(int pos, int otra_pos);
		bool comparar_elementos(int pos, int otra_pos, bool(Dato::*funcion_comparacion)(const Dato&));
		Nodo<Dato>* obtener_nodo(int pos);	

};

template <typename Dato>
Lista<Dato>::Lista(){
	primero = NULL;
	longitud = 0;
}

template <typename Dato>
Lista<Dato>::~Lista(){
	while(!vacia())
		baja(1);
}

template <typename Dato>
Lista<Dato>::Lista(Lista& copiada){
	operator=(copiada);
}


template <typename Dato>
Lista<Dato>& Lista<Dato>::operator=(Lista<Dato>& copiada){
	for(int i =1; i<=copiada.longitud; i++){
		alta(copiada.consultar(i));
	}
	return *this;
}


template <typename Dato>
bool Lista<Dato>::vacia(){
	return (primero == 0);
}



template <typename Dato>
void Lista<Dato>::baja(int pos){
	Nodo<Dato>* borrar = primero;	
	if(pos == 1){
		primero = primero->obtener_siguiente();
	}else{
		Nodo<Dato>* anterior = obtener_nodo(pos-1);
		borrar = anterior->obtener_siguiente();
		anterior->asignar_siguiente(borrar->obtener_siguiente());
	}

	delete borrar;
	longitud--;
}


template <typename Dato>
void Lista<Dato>::alta(Dato d, int pos){
	if(pos < 1){
		pos = longitud+1;
	}
	Nodo<Dato>* nuevo = new Nodo<Dato>(d);
	if(pos == 1){
		nuevo->asignar_siguiente(primero);
		primero = nuevo;
	}else{
		Nodo<Dato>* anterior = obtener_nodo(pos - 1);
		nuevo->asignar_siguiente(anterior->obtener_siguiente());
		anterior->asignar_siguiente(nuevo);
	}
	longitud++;
}

template <typename Dato>
Dato Lista<Dato>::consultar(int pos){
	Nodo<Dato>* aux = obtener_nodo(pos);
	return aux->obtener_dato();
}



template <typename Dato>
int Lista<Dato>::obtener_tamanio(){
	return longitud;
}


template <typename Dato>
Nodo<Dato>* Lista<Dato>::obtener_nodo(int pos){
	Nodo<Dato>* aux = primero;
	int i =1;
	while(i<pos){
		aux = aux->obtener_siguiente();
		i++;
	}
	return aux;
}


template <typename Dato>
bool Lista<Dato>::comparar_elementos(int pos, int otra_pos, bool(Dato::*funcion_comparacion)(const Dato&)){
	if(funcion_comparacion != NULL)
		return (consultar(pos).*funcion_comparacion)(consultar(otra_pos));
	return ( consultar(pos) < consultar(otra_pos));

}


template <typename Dato>
void Lista<Dato>::swap(int pos, int otra_pos){

	Dato aux = consultar(pos);
	obtener_nodo(pos)->asignar_dato(consultar(otra_pos));
	obtener_nodo(otra_pos)->asignar_dato(aux);
}


template <typename Dato>
void Lista<Dato>::ordenar(bool(Dato::*funcion_comparacion)(const Dato&)){
	for(int i = 1; i <= longitud; i++){
		for(int j = 1; j<= longitud -i; j++){
			if(comparar_elementos(j, j+1, funcion_comparacion))
				swap(j, j+1);
		}
	}
}

template <typename Dato>
void Lista<Dato>::print(ostream& out){
	Dato aux;	
	for(int i = 1; i<=longitud; i++){
		aux = consultar(i);
		out<<aux<<endl;
	}

}


//si lo verificado es true, se queda en la lista. Si no, se da de baja de la lista. 
template <typename Dato>
void Lista<Dato>::filtrar(bool(Dato::*funcion_verificacion)()){
	int i = 1;
	while(i <= longitud){
		if(!((consultar(i)).*funcion_verificacion)())
			baja(i);
		else 
			i++;
	}
}


#endif //LISTA_H
