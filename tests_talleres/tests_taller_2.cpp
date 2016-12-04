#include "Pila.h"
#include "mini_test.h"
#include "TiposBasicos.h"

// para compilar:
//   $ g++ -g tests.cpp -o tests
// para ejecutar con valgrind:
//   $ valgrind --leak-check=full -v ./tests

// ========================================================================== //

template<typename T>
std::string to_s(const T& m) {
 	std::ostringstream os;
	os << m;
	return os.str();
}

// ========================================================================== //

/**
 * Esto es una clase sin operador asignación. Sirve para testear
 * que estén utilizando el constructor por copia al asignar los elementos
 * de la colección.
 */
class Punto
{
  public:

    Punto(aed2::Nat x, aed2::Nat y)
      : x_(x), y_(y)
    {}

    Punto(const Punto& otro)
      : x_(otro.x_), y_(otro.y_)
    {}

    friend std::ostream& operator << (std::ostream& os, const Punto& punto);

  private:

    aed2::Nat x_, y_;

    Punto& operator = (const Punto&);
};

std::ostream& operator << (std::ostream& os, const Punto& punto)
{
  return os << "(" << punto.x_ << "," << punto.y_ << ")";
}

// ========================================================================== //

void test_vacia_1()
{
  Pila<aed2::Nat> p;
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(to_s(p), "[]");
}

void test_vacia_2()
{
  Pila<aed2::Nat> p;

  p.apilar(1);

  p.desapilar();

  ASSERT_EQ(p.tamanio(), 0);
  
  ASSERT( p.esVacia() );
}

void test_apilar()
{
  Pila<aed2::Nat> p;

  p.apilar(1);

  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(to_s(p), "[1]");

  p.apilar(2);

  ASSERT_EQ(p.tamanio(), 2);
  ASSERT_EQ(to_s(p), "[2, 1]");
}

void test_tope_1()
{
  Pila<aed2::Nat> p;

  p.apilar(1);

  ASSERT_EQ(p.tope(), 1);

  p.apilar(2);

  ASSERT_EQ(p.tope(), 2);
}

void test_tope_2()
{
  Pila<aed2::Nat> p;

  p.apilar(1);

  ASSERT_EQ(p.tope(), 1);

  p.apilar(20);

  ASSERT_EQ(p.tope(), 20);

  p.desapilar();

  ASSERT_EQ(p.tope(), 1);
}

void test_desapilar()
{
  Pila<aed2::Nat> p;

  p.apilar(1);
  p.apilar(2);

  p.desapilar();

  ASSERT_EQ(p.tope(), 1);
  ASSERT_EQ(p.tamanio(), 1);

  p.desapilar();

  ASSERT_EQ(p.tamanio(), 0);
}

void test_apilar_desapilar()
{
  Pila<aed2::Nat> p;

  p.apilar(1);

  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(p.tope(), 1);

  p.apilar(2000);
  p.desapilar();

  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(p.tope(), 1);

  p.apilar(3000);
  p.desapilar();

  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(p.tope(), 1);
}

void test_constructor_copia()
{
  Pila<aed2::Nat> p;

  p.apilar(1);
  p.apilar(2);
  
  Pila<aed2::Nat> q(p);

  //cout << "p: " << p << endl;
  //cout << "q: " << q << endl;

  p.tope() = 3;
  
  //cout << "p: " << p << endl;
  //cout << "q: " << q << endl;
  
  ASSERT_EQ(q.tope(), 2);
  ASSERT_EQ(p.tope(), 3);
  
  p.desapilar();
  q.desapilar();

  //cout << "p: " << p << endl;
  //cout << "q: " << q << endl;

  ASSERT_EQ(q.tope(), 1);
  ASSERT_EQ(p.tope(), 1);
  
  p.desapilar();
  q.desapilar();
  
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(q.tamanio(), 0);
}

void test_asignacion()
{
  Pila<aed2::Nat> p;

  p.apilar(1);
  p.apilar(2);
  
  Pila<aed2::Nat> q;

  q.apilar(4);
  q.apilar(5);

  //cout << "p: " << p << endl;
  //cout << "q: " << q << endl;

  q = p;

  //cout << "p: " << p << endl;
  //cout << "q: " << q << endl;

  p.tope() = 3;
  
  //cout << "p: " << p << endl;
  //cout << "q: " << q << endl;
  
  ASSERT_EQ(q.tope(), 2);
  ASSERT_EQ(p.tope(), 3);
  
  p.desapilar();
  q.desapilar();

  //cout << "p: " << p << endl;
  //cout << "q: " << q << endl;

  ASSERT_EQ(q.tope(), 1);
  ASSERT_EQ(p.tope(), 1);
  
  p.desapilar();
  q.desapilar();
  
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(q.tamanio(), 0);
}

void copiar_sin_asignacion()
{
  Pila<Punto> pp;

  pp.apilar(Punto(1, 0));

  ASSERT_EQ(to_s(pp), "[(1,0)]");

  pp.apilar(Punto(3, 2));

  ASSERT_EQ(to_s(pp), "[(3,2), (1,0)]");
}

void pila_de_pilas()
{
  Pila<Pila<aed2::Nat> > pp;

  {
    Pila<aed2::Nat> p;
    p.apilar(1);
    p.apilar(2);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 1);
  ASSERT_EQ(to_s(pp), "[[2, 1]]");

  {
    Pila<aed2::Nat> p;
    p.apilar(3);
    p.apilar(4);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 2);
  ASSERT_EQ(to_s(pp), "[[4, 3], [2, 1]]");

  {
    Pila<aed2::Nat> p;
    p.apilar(5);
    p.apilar(6);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 3);
  ASSERT_EQ(to_s(pp), "[[6, 5], [4, 3], [2, 1]]");
}

void copiar_pila_de_pilas()
{

  // Esto es una copia de pila_de_pilas

  Pila<Pila<aed2::Nat> > pp;

  {
    Pila<aed2::Nat> p;
    p.apilar(1);
    p.apilar(2);

    pp.apilar(p);
  }

  {
    Pila<aed2::Nat> p;
    p.apilar(3);
    p.apilar(4);

    pp.apilar(p);
  }

  {
    Pila<aed2::Nat> p;
    p.apilar(5);
    p.apilar(6);

    pp.apilar(p);
  }

  // Esto es nuevo

  Pila<Pila<aed2::Nat> > pp2( pp );

  ASSERT_EQ(pp.tamanio(), 3);
  ASSERT_EQ(to_s(pp), "[[6, 5], [4, 3], [2, 1]]");

  ASSERT_EQ(pp2.tamanio(), 3);
  ASSERT_EQ(to_s(pp2), "[[6, 5], [4, 3], [2, 1]]");

  {
    Pila<aed2::Nat> p;
    p.apilar(7);
    p.apilar(8);

    pp.apilar(p);
  }

  ASSERT_EQ(pp.tamanio(), 4);
  ASSERT_EQ(to_s(pp), "[[8, 7], [6, 5], [4, 3], [2, 1]]");

  ASSERT_EQ(pp2.tamanio(), 3);
  ASSERT_EQ(to_s(pp2), "[[6, 5], [4, 3], [2, 1]]");
}

int main()
{
  RUN_TEST(test_vacia_1);
  RUN_TEST(test_vacia_2);
  
  RUN_TEST(test_apilar);

  RUN_TEST(test_tope_1);
  RUN_TEST(test_tope_2);

  RUN_TEST(test_desapilar);
  
  RUN_TEST(test_apilar_desapilar);

  RUN_TEST(test_constructor_copia);
  RUN_TEST(test_asignacion);
  RUN_TEST(copiar_sin_asignacion);
  RUN_TEST(pila_de_pilas);
  RUN_TEST(copiar_pila_de_pilas);

  return 0;
}
