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

                //TODO: funciones auxiliares

                Nodo* raiz;
                Conj<string> claves;
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
    //this->raiz = NULL;
    //Conj<string> conj(d.claves);
    //while(conj.cardinal()>0){
        //this->Definir(conj.minimo(),d.Obtener(conj.minimo()));
        //conj.remover(conj.minimo());
    //}
}

template <typename T>
DiccString<T>::~DiccString(){
    //cout << "DESTRUCTOR" << endl;

	int ini = claves.cardinal();
    for(int i=0; i < ini; i++){
        string aux = claves.minimo();
        this->Borrar(aux);
    }

    delete raiz;
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    //cout << "DEFINIR" << endl;
    Nodo* aux;

    if (this->raiz == NULL){

        Nodo* nuevo = new Nodo();

        this->raiz = nuevo;

    }
    aux = this->raiz;

    int largo = clave.length();

    if (!Definido(clave)){

        for (int i = 0; i < largo; i++){

            if (aux->siguientes[int(clave[i])] == NULL){

                Nodo* nuevo = new Nodo();

                aux->siguientes[int(clave[i])] = nuevo;

                aux = aux->siguientes[int(clave[i])];
            }else{

                aux = aux->siguientes[int(clave[i])];
            }
        }

        aux->definicion = new T(significado);
        this->claves.insertar(clave);

    }else{

        aux = raiz;
        for(unsigned int i=0; i < clave.length(); i++){
             aux = aux->siguientes[int(clave[i])];
        }
        delete aux->definicion;
        aux->definicion = new T(significado);


    }
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{

    /*Nodo* aux;
    aux = this->raiz;

    if (aux == NULL)
        return false;

    int largo = clave.length();

    for (int i = 0; i < largo; i++){
        aux = aux->siguientes[int(clave[i])];
        cout << "letra: " << clave[i] << endl;
        if (aux == NULL){
            return false;
        }
    }

    return (aux != NULL);*/
    return (this->claves.pertenece(clave));

}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {

    Nodo* aux;
    aux = this->raiz;

    int largo = clave.length();

    if (Definido(clave)){

        for (int i = 0; i < largo ; i++){
                aux = aux->siguientes[int(clave[i])];

        }

    }
    return *(aux->definicion);
}

template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {

    //TODO
    assert(false);
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {
  
    Nodo* aux;
    aux = raiz;
    Nodo* ultimoNodo;
    Nodo* ultimoNodoAnterior = NULL;
    int ultimoIndice;
    int j = 0;
    int largo = clave.length();
    int cant = 0;
    int cantiddad = 0;


    Nodo* aBorrar;

    if(claves.cardinal() == 1){
        ultimoNodo = raiz->siguientes[clave[0]];
        j = 0;


        for (int i = 1; i < largo; i++){

                aBorrar = ultimoNodo;
                ultimoNodo = ultimoNodo->siguientes[int(clave[i])];

                delete aBorrar;

            }
            delete ultimoNodo;
            raiz->siguientes[clave[0]] = NULL;

    } else {
        //cout << endl << "SE BORRA " << clave << endl;
        while (j < 256){

            if (aux->siguientes[j] != NULL)
                cant++;
            j++;
        }

        j = 0;
        if (cant>1){
            ultimoNodo = aux;
            ultimoIndice = 0;
        }

        cant = 0;
        for (int i = 0; i < largo; i++){
            j = 0;

            while (j < 256){

                if (aux->siguientes[j] != NULL){
                    cant++;
                    //cout << endl << "Tiene " << char(j) << " - " << cant;
                }
                j++;
            }

            if (cant>1 || aux->definicion != NULL){
                ultimoNodoAnterior = aux;
                ultimoNodo = aux->siguientes[int(clave[i])];
                ultimoIndice = i;
                //cout << "letra del nodo que quedo: " << clave[i] << " con " << cant << endl;
            }

            cant = 0;

            if(aux->siguientes[int(clave[i])] != NULL){
                aux = aux->siguientes[int(clave[i])];
            } else {
                break;
            }
        }

        if (ultimoNodo == raiz){
            ultimoNodo = ultimoNodo->siguientes[int(clave[0])];
            ultimoIndice = 0;
        }




        //Si es palabra cortada de otra larga
        //cout << "Ultimo Indice" << ultimoIndice;
        j = 0;
        int cantidad = 0;
        while (j < 256){
            if (aux->siguientes[j] != NULL) cantidad++;
            j++;
        }
        if(ultimoIndice == clave.length()-1 || (cantidad > 0 && ultimoIndice == 0)){
            ultimoIndice = clave.length();
            delete aux->definicion;
            aux->definicion = NULL;
            if(cantidad == 0) delete aux;
        } else {
        //----------------------------------------------------------------------
            cantidad = 0;
            if(ultimoNodoAnterior != NULL){
                 ultimoNodoAnterior->siguientes[int(clave[ultimoIndice])] = NULL;
            }

            for (int i = ultimoIndice+1; i < largo; i++){
                //cout << endl << "Entro piola estamos en letra " << clave[i];
                j = 0;
                aBorrar = ultimoNodo;
                ultimoNodo = ultimoNodo->siguientes[int(clave[i])];

                cantidad = 0;
                while (j < 256){
                  //if (aBorrar->siguientes[j] != NULL) cout << endl << "Borrando: " << char(j) << endl;
                     j++;
                  }

                delete aBorrar;


                //if()

                //ultimoNodo = ultimoNodo->siguientes[int(clave[i])];
                //      aux->siguientes[int(clave[i])] = NULL;
                //delete aux->definicion;
                //delete aux;
                //aux->definicion = NULL;
            }
            delete ultimoNodo;
        }
    }
    claves.remover(clave);

    j = 0;
    while (j < 256){

            if (raiz->siguientes[j] != NULL) cantiddad++;
                j++;
    }

    //cout << endl << "La raiz tiene: " << cantiddad << endl;

}

#endif
