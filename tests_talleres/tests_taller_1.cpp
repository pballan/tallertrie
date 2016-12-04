#include "Pila.h"
#include "mini_test.h"

// para compilar:$ g++ -g tests.cpp Pila.cpp -o Pila
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./Pila

void test_vacia_1() {
  Pila p;
  ASSERT_EQ(p.tamanio(), 0);
}

void test_vacia_2() {
  Pila p;

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  p.desapilar();

  ASSERT_EQ(p.tamanio(), 0);
}

void test_apilar() {
  Pila p;

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  ASSERT_EQ(p.tamanio(), 1);
  ASSERT_EQ(p.tope().id, 654321);
}

void test_desapilar() {
  Pila p;

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  ElemPila e2;
  e2.id = 123456;
  e2.nombre = "Product2";
  e2.descripcion = "It's awesome too!";
  p.apilar(e2);

  p.desapilar();

  p.desapilar();

  ASSERT_EQ(p.tamanio(), 0);

}

void test_apilar_desapilar() {
  Pila p;

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  ElemPila e2;
  e2.id = 123456;
  e2.nombre = "Product2";
  e2.descripcion = "It's awesome too!";
  p.apilar(e2);

  p.desapilar();

  ElemPila e3;
  e3.id = 987564;
  e3.nombre = "Product3";
  e3.descripcion = "It's awesome too!";
  p.apilar(e3);

  p.desapilar();
  p.desapilar();

  ASSERT_EQ(p.tamanio(), 0);

}

void test_tamanio() {
  Pila p;

  ASSERT_EQ(p.tamanio(), 0);

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  ElemPila e2;
  e2.id = 123456;
  e2.nombre = "Product2";
  e2.descripcion = "It's awesome too!";
  p.apilar(e2);

  ASSERT_EQ(p.tamanio(), 2);
}


void test_tope() {
  Pila p;

  ASSERT_EQ(p.tamanio(), 0);

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  ElemPila e2;
  e2.id = 123456;
  e2.nombre = "Product2";
  e2.descripcion = "It's awesome too!";
  p.apilar(e2);

  ASSERT_EQ(p.tope().id, 123456);

}

void test_copia() {
  Pila p, q;

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  ElemPila e2;
  e2.id = 123456;
  e2.nombre = "Product2";
  e2.descripcion = "It's awesome too!";
  p.apilar(e2);
  
  q = p;

  p.tope().id = 0;
  
//   cout << q << endl;
//   cout << p << endl;
  
  ASSERT_EQ(q.tope().id, 123456);
  ASSERT_EQ(p.tope().id, 0);
  
  p.desapilar();
  q.desapilar();
  
  ASSERT_EQ(q.tope().id, 654321);
  ASSERT_EQ(p.tope().id, 654321);
  
  p.desapilar();
  q.desapilar();
  
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(q.tamanio(), 0);
  
}

void test_constructor_copia() {
  Pila p;

  ElemPila e1;
  e1.id = 654321;
  e1.nombre = "Product1";
  e1.descripcion = "It's awesome!";
  p.apilar(e1);

  ElemPila e2;
  e2.id = 123456;
  e2.nombre = "Product2";
  e2.descripcion = "It's awesome too!";
  p.apilar(e2);
  
  Pila q(p);
  
  cout << q << endl;
  cout << p << endl;
  
  p.tope().id = 0;
  
  ASSERT_EQ(q.tope().id, 123456);
  ASSERT_EQ(p.tope().id, 0);
  
  p.desapilar();
  q.desapilar();
  
  ASSERT_EQ(q.tope().id, 654321);
  ASSERT_EQ(p.tope().id, 654321);
  
  p.desapilar();
  q.desapilar();
  
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT_EQ(q.tamanio(), 0);
  
}

int main() {
  RUN_TEST(test_vacia_1);
  RUN_TEST(test_vacia_2);
  RUN_TEST(test_apilar);
  RUN_TEST(test_desapilar);
  RUN_TEST(test_apilar_desapilar);
  RUN_TEST(test_tamanio);
  RUN_TEST(test_tope);
  RUN_TEST(test_copia);
  //RUN_TEST(test_constructor_copia);
  return 0;
}
