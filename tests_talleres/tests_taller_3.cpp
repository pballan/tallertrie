#include <iostream>
#include "Conjunto.hpp"

#include "mini_test.h"


void test_insertar_pertenece() {
	Conjunto<int> c;
	c.insertar(42);
	ASSERT( c.pertenece(42) );
	c.insertar(43);
	c.insertar(44);
	c.insertar(45);
	c.insertar(46);
	ASSERT( c.pertenece(45) );
}

void test_cardinal_insertar() {
	Conjunto<int> c;
	c.insertar(42);
	ASSERT( c.cardinal() == 1 );
	c.insertar(43);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	ASSERT( c.cardinal() == 5 );
}

void test_cardinal_remover_1() {

	Conjunto<int> c;

	c.remover(1);

	/*Remover de elementos ausentes no debe restar cardinal*/
	ASSERT( c.cardinal() == 0 );
}

void test_cardinal_remover_2() {

	Conjunto<int> c;
	
	c.insertar(2);
	c.insertar(3);
	c.insertar(11);

	ASSERT( c.cardinal() == 3 );

	c.remover(2);
	c.remover(3);

	ASSERT( c.cardinal() == 1 );

	c.remover(111);

	/*Inserts y removes sucesivos deben mantener coherencia de cardinal*/
	ASSERT( c.cardinal() == 1 );
}

void test_remover() {
 	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(44);
 	c.insertar(104);
 	c.insertar(450);
 	c.insertar(-46);
 	c.insertar(-460);
 	c.insertar(130);
 	c.insertar(43);

 	// cout << c << endl;

	bool pertenencia;

	c.remover(44);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& c.pertenece(450) && c.pertenece(-46) && c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

 	// cout << c << endl;

 	c.remover(-46);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& c.pertenece(450) && !c.pertenece(-46) && c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

 	// cout << c << endl;

 	c.remover(130);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& c.pertenece(450) && !c.pertenece(-46) && c.pertenece(-460)
				&& !c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

 	// cout << c << endl;

 	c.remover(450);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& !c.pertenece(450) && !c.pertenece(-46) && c.pertenece(-460)
				&& !c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

 	// cout << c << endl;

 	c.remover(42);
	pertenencia = !c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& !c.pertenece(450) && !c.pertenece(-46) && c.pertenece(-460)
				&& !c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

	// cout << c << endl;

}

void test_maximo_1() {
	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(43);
 	c.insertar(104);
 	c.insertar(450);
 	c.insertar(-46);
 	c.insertar(-460);
 	c.insertar(1460);
 	ASSERT( c.maximo() == 1460 );
}

void test_maximo_2() {
	Conjunto<int> c;

 	c.insertar(100);
 	c.insertar(101);
 	c.insertar(102);

 	ASSERT( c.maximo() == 102 );

 	c.insertar(103);
 	c.remover(103);

 	/*Que el maximo se mantenga actualizado*/
 	ASSERT( c.maximo() == 102 );
}

void test_minimo_1() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(43);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	c.insertar(-460);
	c.insertar(1460);
	ASSERT( c.minimo() == -460 );
}

void test_minimo_2() {
	Conjunto<int> c;

 	c.insertar(100);
 	c.insertar(101);
 	c.insertar(102);

 	ASSERT( c.minimo() == 100 );

 	c.insertar(1);
 	c.remover(1);

 	/*Que el minimo se mantenga actualizado*/
 	ASSERT( c.minimo() == 100 );
}
void test_min_max_unico() {

	Conjunto<int> c;

 	c.insertar(1);

 	ASSERT( c.maximo() == c.minimo() );

 	c.insertar(2);

	ASSERT(  c.maximo() != c.minimo() );
}

void test_min_max() {
	Conjunto<int> c;

 	c.insertar(-1);
 	c.insertar(1);
 	c.insertar(300);

 	ASSERT( c.maximo() == 300 );
 	ASSERT( c.minimo() == -1 );

 	c.insertar(457);
 	c.remover(-1);

 	ASSERT( c.maximo() == 457 );
 	ASSERT( c.minimo() == 1 );

 	c.remover(-1);

 	ASSERT( c.maximo() == 457 );
 	ASSERT( c.minimo() == 1 );

 	c.insertar(500000);
 	c.remover(1);

 	ASSERT( c.maximo() == 500000 );
 	ASSERT( c.minimo() == 300 );
}

int main() {

	RUN_TEST(test_insertar_pertenece);

	RUN_TEST(test_cardinal_insertar);
	RUN_TEST(test_cardinal_remover_1);
	RUN_TEST(test_cardinal_remover_2);

	RUN_TEST(test_remover);

	RUN_TEST(test_maximo_1);
	RUN_TEST(test_maximo_2);
	
	RUN_TEST(test_minimo_1);
	RUN_TEST(test_minimo_2);

	RUN_TEST(test_min_max_unico);
	RUN_TEST(test_min_max);

	return 0;

}
