#include <iostream>
#include "mini_test.h"

#include "DiccString.hpp"


/**
 * Esto es una clase sin operador asignacion. Sirve para testear
 * que estan utilizando el constructor por copia al asignar los elementos
 * de la coleccion.
 */
class Punto
{
  public:

    Punto(int x, int y)
      : x_(x), y_(y)
    {}

    Punto(const Punto& otro)
      : x_(otro.x_), y_(otro.y_)
    {}

    bool operator == (const Punto& otro){
    	return (this->x_ == otro.x_) && (this->y_ == otro.y_);
    }

    friend std::ostream& operator << (std::ostream& os, const Punto& punto);

  private:

    int x_, y_;

    Punto& operator = (const Punto&);
};

std::ostream& operator << (std::ostream& os, const Punto& punto)
{
  return os << "(" << punto.x_ << "," << punto.y_ << ")";
}

// ========================================================================== //


//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
}


//Chequea que definido funcione bien si el diccionario esta vacio
void test_definido_dicc_vacio() {
	DiccString<int> d;
	ASSERT(!d.Definido("a"));
	ASSERT(!d.Definido("m"));
	ASSERT(!d.Definido("z"));
	ASSERT(!d.Definido("aaaaa"));
	ASSERT(!d.Definido("hola"));
	ASSERT(!d.Definido("chau"));
	ASSERT(!d.Definido("zzzzz"));
}


//Chequea si definir y definido funcionan bien con palabras sin prefijos en comun
void test_definir_definido() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("chau") );

	d.Definir("chau",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("chau") );
	ASSERT( !d.Definido("pepe") );

	d.Definir("pepe",22);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("chau") );
	ASSERT( d.Definido("pepe") );
}


//cheque que al definir no se definan tambien sus prefijos
void test_definir_no_definine_los_prefigos() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("h") );
	ASSERT( !d.Definido("ho") );
	ASSERT( !d.Definido("hol") );
	ASSERT( !d.Definido("chau") );
	ASSERT(d.Claves().cardinal() == 1);
}


//Chequea si definir y definido funcionan bien con palabras con prefijos en comun
void test_definir_definido_con_prefijos_en_comun() {
	DiccString<int> d;
	ASSERT( !d.Definido("casona") );
	d.Definir("casa",22);
	ASSERT( d.Definido("casa") );
	ASSERT( !d.Definido("casona") );

	d.Definir("casona",42);
	ASSERT( d.Definido("casona") );
	ASSERT( d.Definido("casa") );
	ASSERT( !d.Definido("cono") );

	d.Definir("cono",6);
	ASSERT( d.Definido("casona") );
	ASSERT( d.Definido("casa") );
	ASSERT( d.Definido("cono") );
	ASSERT( !d.Definido("c") );

	d.Definir("c",100);
	ASSERT( d.Definido("casona") );
	ASSERT( d.Definido("casa") );
	ASSERT( d.Definido("cono") );
	ASSERT( d.Definido("c") );

	ASSERT( !d.Definido("ca") );
	ASSERT( !d.Definido("cas") );
	ASSERT( !d.Definido("caso") );
	ASSERT( !d.Definido("cason") );
	ASSERT( !d.Definido("co") );
	ASSERT( !d.Definido("con") );
}


//cheque que Claves funcione bien
void test_claves() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);

	d.Definir("hola",42);
	ASSERT(d.Claves().cardinal() == 1);
	d.Definir("casa",22);
	ASSERT(d.Claves().cardinal() == 2);

	d.Definir("cono",6);
	ASSERT(d.Claves().cardinal() == 3);
	d.Definir("c",100);
	ASSERT(d.Claves().cardinal() == 4);
	d.Definir("chau",13);
	ASSERT(d.Claves().cardinal() == 5);
	d.Definir("pepe",22);
	ASSERT(d.Claves().cardinal() == 6);
	d.Definir("casona",42);
	ASSERT(d.Claves().cardinal() == 7);

	ASSERT(d.Claves().pertenece("hola"));
	ASSERT(d.Claves().pertenece("casa"));
	ASSERT(d.Claves().pertenece("cono"));
	ASSERT(d.Claves().pertenece("c"));
	ASSERT(d.Claves().pertenece("chau"));
	ASSERT(d.Claves().pertenece("pepe"));
	ASSERT(d.Claves().pertenece("casona"));
}



//cheque que obtener funcione bien independientemente de si las claves tiene prefijos en comun (que no rescriban el significado)
void test_obtener() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
	d.Definir("cono",6);
	d.Definir("c",100);
	d.Definir("chau",13);
	d.Definir("pepe",2);
	d.Definir("casona",422);

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );
	ASSERT( d.Obtener("cono") == 6 );
	ASSERT( d.Obtener("c") == 100 );
	ASSERT( d.Obtener("chau") == 13 );
	ASSERT( d.Obtener("pepe") == 2 );
	ASSERT( d.Obtener("casona") == 422 );
}




//Chequea que se pueda redefinir el significado de una clave
void test_redefinir_obtener() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Obtener("hola") == 42 );
	d.Definir("hola", 100);
	ASSERT( d.Obtener("hola") == 100 );
	d.Definir("hola",4);
	ASSERT( d.Obtener("hola") == 4 );
}



//Cheque que funcione bien el cnstrutor por copia
void test_constructor_copia()
{
  DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
	d.Definir("cono",6);
	ASSERT(d.Claves().cardinal() == 3);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casa") );
	ASSERT( d.Definido("cono") );


	DiccString<int> d2(d);
	//Se chequea que se genere bien la copia
	ASSERT(d2.Claves().cardinal() == 3);
	ASSERT( d2.Definido("hola") );
	ASSERT( d2.Definido("casa") );
	ASSERT( d2.Definido("cono") );

	//Se chequea que el dicc original siga igual
	ASSERT(d.Claves().cardinal() == 3);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casa") );
	ASSERT( d.Definido("cono") );

	//Se agregan una clave a d y se quechea que no se agregue a d2
	//Se agregan dos claves a d2 y se quechea que no se agreguen a d
	d.Definir("casona",2);

	d2.Definir("camion",100);
	d2.Definir("c",600);

	ASSERT(d.Claves().cardinal() == 4);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casa") );
	ASSERT( d.Definido("cono") );
	ASSERT( d.Definido("casona") );
	ASSERT( !d.Definido("camion") );
	ASSERT( !d.Definido("c") );

	ASSERT(d2.Claves().cardinal() == 5);
	ASSERT( d2.Definido("hola") );
	ASSERT( d2.Definido("casa") );
	ASSERT( d2.Definido("cono") );
	ASSERT( !d2.Definido("casona") );
	ASSERT( d2.Definido("camion") );
	ASSERT( d2.Definido("c") );
}

//Cheque que funcione bien el construtor por copia
void test_constructor_copia2()
{
  DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
	d.Definir("cono",6);

  DiccString<int> d2(d);

	d.Definir("casona",2);
	d2.Definir("camion",100);
	d2.Definir("c",600);

	//Chequeo que los dicc sean independientes entre si
	ASSERT(d.Claves().cardinal() == 4);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casa") );
	ASSERT( d.Definido("cono") );
	ASSERT( d.Definido("casona") );
	ASSERT( !d.Definido("camion") );
	ASSERT( !d.Definido("c") );

	ASSERT(d2.Claves().cardinal() == 5);
	ASSERT( d2.Definido("hola") );
	ASSERT( d2.Definido("casa") );
	ASSERT( d2.Definido("cono") );
	ASSERT( !d2.Definido("casona") );
	ASSERT( d2.Definido("camion") );
	ASSERT( d2.Definido("c") );

	//se modifican una definicion de d, pero no en d2
	d.Definir("hola",300);
	ASSERT( d.Obtener("hola") == 300 );
	ASSERT( !(d2.Obtener("hola") == 300 ));
	ASSERT( d2.Obtener("hola") == 42 );

	//se modifican una definicion de d2, pero no en d
	d2.Definir("casa",57);
	ASSERT( d2.Obtener("casa") == 57 );
	ASSERT( !(d.Obtener("casa") == 57 ));
	ASSERT( d.Obtener("casa") == 22 );
}



//chequea que el definir funcione bien si la clase de los significados no tiene operador =
void test_definir_sin_asignacion()
{
	DiccString<Punto> d;
	d.Definir("hola",Punto(2,3));
	ASSERT( d.Definido("hola") );
	ASSERT( d.Obtener("hola") == Punto(2,3) );
	d.Definir("casa",Punto(100,4));
	ASSERT( d.Definido("casa") );
	ASSERT( d.Obtener("casa") == Punto(100,4));
	d.Definir("chau",Punto(57,3));
	ASSERT( d.Definido("chau") );
	ASSERT( d.Obtener("chau") == Punto(57,3) );
	d.Definir("chau",Punto(570,30));
	ASSERT( d.Definido("chau") );
	ASSERT( d.Obtener("chau") == Punto(570,30) );
}


//Se chequea que funcion la clase cuando el significado es una estructura compeja como un trie
void test_trie_con_significado_tries() {
	DiccString<int> d2;
	d2.Definir("hola",42);
	d2.Definir("casa",22);
	d2.Definir("cono",6);
	ASSERT( d2.Definido("hola") );
	ASSERT( d2.Definido("casa") );
	ASSERT( d2.Definido("cono") );

	DiccString<int> d3;
	d3.Definir("c",100);
	d3.Definir("chau",13);
	d3.Definir("pepe",2);
	d3.Definir("casona",422);
	ASSERT( d3.Definido("c") );
	ASSERT( d3.Definido("chau") );
	ASSERT( d3.Definido("pepe") );
	ASSERT( d3.Definido("casona") );

	DiccString<DiccString<int> > d;
	d.Definir("dicc",d2);
	d.Definir("trie",d3);

	ASSERT( (d.Obtener("dicc")).Obtener("hola") == 42 );
	ASSERT( (d.Obtener("dicc")).Obtener("casa") == 22 );
	ASSERT( (d.Obtener("dicc")).Obtener("cono") == 6 );

	ASSERT( (d.Obtener("trie")).Obtener("c") == 100 );
	ASSERT( (d.Obtener("trie")).Obtener("chau") == 13);
	ASSERT( (d.Obtener("trie")).Obtener("pepe") == 2 );
	ASSERT( (d.Obtener("trie")).Obtener("casona") == 422 );
}


//Se chequea que funcione copiar  cuando el significado es una estructura compeja como un trie
void test_copiar_trie_con_significado_tries() {
	DiccString<int> d2;
	d2.Definir("hola",42);
	d2.Definir("casa",22);
	d2.Definir("cono",6);

	DiccString<DiccString<int> > d;
	d.Definir("dicc",d2);

	//Se copia d
	DiccString<DiccString<int> > d3(d);

	//Se agrega un elemento a d3 y se verifica que todo este funcionando
	DiccString<int> d4;
	d4.Definir("c",100);
	d4.Definir("chau",13);
	d4.Definir("pepe",2);

	d3.Definir("trie",d4);

	ASSERT(d3.Definido("dicc"));
	ASSERT(d3.Definido("trie"));

	ASSERT( (d3.Obtener("dicc")).Obtener("hola") == 42 );
	ASSERT( (d3.Obtener("dicc")).Obtener("casa") == 22 );
	ASSERT( (d3.Obtener("dicc")).Obtener("cono") == 6 );

	ASSERT( (d3.Obtener("trie")).Obtener("c") == 100 );
	ASSERT( (d3.Obtener("trie")).Obtener("chau") == 13);
	ASSERT( (d3.Obtener("trie")).Obtener("pepe") == 2 );

	//Se chequea que d no se modifico
	ASSERT(d.Definido("dicc"));
	ASSERT(!d.Definido("trie"));
	ASSERT( (d.Obtener("dicc")).Obtener("hola") == 42 );
	ASSERT( (d.Obtener("dicc")).Obtener("casa") == 22 );
	ASSERT( (d.Obtener("dicc")).Obtener("cono") == 6 );
}


//Chequea si el borrado funciona bien si se borra la unica clave del diccionario
void test_dicc_vacio_con_definir_y_borrar() {
	DiccString<int> d;
	ASSERT( !d.Definido("hola") );

	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );

	d.Borrar("hola");
	ASSERT( !d.Definido("hola") );
	ASSERT(d.Claves().cardinal() == 0);
}

//Chequea el funcionamiento del borrar
void test_dicc_borrar() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casona",13);
	d.Definir("casa",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casa") );
	ASSERT( d.Definido("casona") );
	ASSERT(d.Claves().cardinal() == 3);

	d.Borrar("casa");
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casa") );
	ASSERT( d.Definido("casona") );

	d.Definir("casa",13);
	d.Borrar("casona");
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casa") );
	ASSERT( !d.Definido("casona") );

	d.Definir("c",1300);
	d.Borrar("casa");
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("c") );
	ASSERT( !d.Definido("casona") );
	ASSERT( !d.Definido("casa") );
	ASSERT(d.Claves().cardinal() == 2);
	d.Borrar("c");
	ASSERT(d.Claves().cardinal() == 1);
	d.Borrar("hola");
	ASSERT(d.Claves().cardinal() == 0);
}



int main() {
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_definido_dicc_vacio);
	RUN_TEST(test_definir_definido);
	RUN_TEST(test_definir_no_definine_los_prefigos);
	RUN_TEST(test_definir_definido_con_prefijos_en_comun);
	RUN_TEST(test_claves);
	RUN_TEST(test_obtener);
	RUN_TEST(test_redefinir_obtener);
	RUN_TEST(test_constructor_copia);
	RUN_TEST(test_constructor_copia2);
	RUN_TEST(test_definir_sin_asignacion);
	RUN_TEST(test_trie_con_significado_tries);
	RUN_TEST(test_dicc_vacio_con_definir_y_borrar);
	RUN_TEST(test_dicc_borrar);
	return 0;

}

