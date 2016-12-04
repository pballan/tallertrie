#include <iostream>
#include <fstream>

#define TAM_TABLA_INI 100
#define UMBRAL_FC	  0.75


#include "DiccHashCerrado.hpp"
#include "mini_test.h"



using namespace std;
using namespace aed2;

void test_Definido () {

	DiccHashCerrado<int> dh;

	ASSERT( not dh.Definido("") );
	ASSERT( not dh.Definido(" ") );
	ASSERT( not dh.Definido("hola") );

	dh.Definir("hola", 100);
	ASSERT( dh.Definido("hola") );
	ASSERT( not dh.Definido("holas") );
	ASSERT( not dh.Definido("hol") );
}

void test_Definir () {

	DiccHashCerrado<char> dhc;
	ASSERT( not dhc.Definido("") );

	dhc.Definir("a",'a');
	dhc.Definir("ab",'a');

	ASSERT( not dhc.Definido("") );
	ASSERT( dhc.Definido("a") );
	ASSERT( dhc.Definido("ab") );
	ASSERT( not dhc.Definido("abc") );
	ASSERT( not dhc.Definido("ab ") );
	ASSERT( not dhc.Definido(" ab") );
}

void test_String_Vacio () {

	DiccHashCerrado<char> dhc;
	ASSERT( not dhc.Definido("") );

	dhc.Definir("",'a');
	ASSERT( dhc.Definido("") );
	ASSERT( not dhc.Definido(" ") );

	ASSERT( dhc.Significado("") == 'a' );

	dhc.Borrar("");
	ASSERT( not dhc.Definido("") );
}

void test_Significado () {

	DiccHashCerrado<char> dhc;
	ASSERT( not dhc.Definido("a") );

	dhc.Definir("a",'a');
	dhc.Definir("ab",'a');

	ASSERT( dhc.Significado("a") == 'a' );
	ASSERT( dhc.Significado("a") != 'b' );
}

void test_Borrar () {

	DiccHashCerrado<int> dhi;

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	ASSERT( dhi.Definido("juanca") );
	ASSERT( dhi.Definido("moncho")  );

	dhi.Borrar("juanca");

	ASSERT( not dhi.Definido("juanca") );

	dhi.Borrar("moncho");

	ASSERT( not dhi.Definido("moncho") );
}

void test_CantClaves () {

	DiccHashCerrado<int> dhi;

	ASSERT( dhi.CantClaves() == 0 );

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Definir("moncho",56);

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Borrar("juanca");

	ASSERT( dhi.CantClaves() == 1 );

	dhi.Borrar("moncho");

	ASSERT( dhi.CantClaves() == 0 );
}

void test_claves(){
	DiccHashCerrado<int> dhi;
	Lista<String> claves;

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 0 );

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Definir("moncho",56);

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Borrar("juanca");

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 1 );

	dhi.Borrar("moncho");

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 0 );
}


void test_colisiones_unif(){

	DiccHashCerrado<int> dh;

	char delim = '\n';
	std::string archnom = "../../../data/uniforme.txt";

	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin,str,delim) && archin.good()){

		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		if (val == 50) break;
	}
	archin.close();

	cout << endl;
	cout << "Cantidad de elementos definidos: ";
	cout << dh.CantClaves() << endl;
	ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
	ASSERT(dh.colisiones() < 20);
}

void test_colisiones_gauss(){

	DiccHashCerrado<int> dh;

	char delim = '\n';
	std::string archnom = "../../../data/gauss.txt";

	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin,str,delim) && archin.good()){

		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		if (val == 50) break;
	}
	archin.close();

	cout << endl;
	cout << "Cantidad de elementos definidos: ";
	cout << dh.CantClaves() << endl;
	ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
	ASSERT(dh.colisiones() < 30);
}

void test_colisiones_libretas(){

	DiccHashCerrado<int> dh;

	char delim = '\n';
	std::string archnom = "../../../data/libretas.txt";


	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin,str,delim) && archin.good()){

		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		if (val == 50) break;
	}
	archin.close();

	cout << endl;
	cout << "Cantidad de elementos definidos: ";
	cout << dh.CantClaves() << endl;
	ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
	ASSERT(dh.colisiones() < 26);
}


void test_redimensionado(){

	DiccHashCerrado<int> dh;

	std::string archnom = "../../../data/uniforme.txt";
//	std::string archnom = "../../../data/gauss.txt";
//	std::string archnom = "../../../data/libretas.txt";

	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin,str) && archin.good()){

		dh.Definir(str, val);
		val++;
	}
	archin.close();

	ASSERT_EQ(dh.CantClaves(),val);

	Nat eval = 0;
	archin.open(archnom.c_str());
	while(getline(archin,str) && archin.good()){

		ASSERT(dh.Definido(str));
		ASSERT_EQ(dh.Significado(str),eval);
		eval++;
	}
	archin.close();

	ASSERT_EQ(eval,val);
}


int main() {

	RUN_TEST(test_Definido);
	RUN_TEST(test_Definir);
	RUN_TEST(test_String_Vacio);
	RUN_TEST(test_Significado);
	RUN_TEST(test_Borrar);
	RUN_TEST(test_CantClaves);
	RUN_TEST(test_claves);

	RUN_TEST(test_redimensionado);
	RUN_TEST(test_colisiones_unif);
	RUN_TEST(test_colisiones_gauss);
	RUN_TEST(test_colisiones_libretas);

	return 0;
}

