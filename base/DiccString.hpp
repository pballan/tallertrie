#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();

                /**
                CONSTRUCTOR POR COPIA
                * Construye un diccionario por copia.
                **/
                DiccString(const DiccString<T>&);


                /**
                DESTRUCTOR
                **/
                ~DiccString();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
				-- Versión modificable y no modificable
                **/
				        const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);


                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<string>& Claves() const;

        private:

                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
						            siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
						            delete [] siguientes;
                    }
                };

                bool masDeDosClaves_o_defAntes_o_esRaiz(DiccString<T>::Nodo* a);

                Nodo* raiz;
                Conj<string> claves;
};


template <typename T>
DiccString<T>::DiccString(){
  raiz = new Nodo();
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
  Conj<string> conjAux = Conj<string>(d.Claves());
  raiz = new Nodo();

  while (conjAux.cardinal() > 0){
    Definir(conjAux.minimo(),d.Obtener(conjAux.minimo()));
    conjAux.remover(conjAux.minimo());
  }

}

template <typename T>
DiccString<T>::~DiccString(){

  while (claves.cardinal() > 0) {
    Borrar(claves.minimo());
  }
  delete raiz;
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){

  Nodo* aux;
  aux = this->raiz;
  int largo = clave.length();

  for (int i = 0; i < largo; i++) {
    if (aux->siguientes[int(clave[i])] == NULL){
      Nodo* nuevo = new Nodo();
      aux->siguientes[int(clave[i])] = nuevo;
      aux = aux->siguientes[int(clave[i])];
    }else{
      aux = aux->siguientes[int(clave[i])];
    }
  }

  if (aux->definicion != NULL){
    delete aux->definicion;
    aux->definicion = NULL;
  }

  aux->definicion = new T(significado);
  this->claves.insertar(clave);

}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
  return (claves.pertenece(clave));
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {


  Nodo* aux;
  aux = this->raiz;
  int largo = clave.length();
  for (int i = 0; i < largo; i++) {
      aux = aux->siguientes[int(clave[i])];
  }

  return *aux->definicion;
}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
  Nodo* aux;
  aux = this->raiz;
  int largo = clave.length();
  for (int i = 0; i < largo; i++) {
      aux = aux->siguientes[int(clave[i])];
  }

  return *aux->definicion;
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{

    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {

  Nodo* ultimoNodo;
  int ultimoIndice = 0;
  int largo = clave.length();
  Nodo* aux = this->raiz;
  Nodo* aBorrar;

  for (int i = 0; i < largo; i++) {
    if (masDeDosClaves_o_defAntes_o_esRaiz(aux)){
      ultimoNodo = aux->siguientes[int(clave[i])];
      ultimoIndice = i+1;
    }
    aux = aux->siguientes[int(clave[i])];
  }

  for (int i = ultimoIndice; i < largo; i++) {
    aBorrar = ultimoNodo;
    ultimoNodo = ultimoNodo->siguientes[int(clave[i])];
    delete aBorrar;
  }

  delete ultimoNodo->siguientes[int(clave[largo])];

  claves.remover(clave);

}


template <typename T>
bool DiccString<T>::masDeDosClaves_o_defAntes_o_esRaiz(Nodo* nodo){
  int i = 0;
  int cant = 0;
  Nodo* aux = nodo;
  bool definidoAntes = false;
  while (i < 256){
    if (aux->siguientes[i] != NULL)cant++;
    if (aux->definicion != NULL) definidoAntes = true;
    if (aux == raiz) definidoAntes = true;
    i++;
  }
  return ((cant > 1) || definidoAntes);
}
















#endif
