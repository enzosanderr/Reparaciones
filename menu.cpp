#include <iostream>
#include <cstdlib>
#include "menu.h"
using namespace std;

Menu::Menu() {
   setCantidadOpciones(0);
}

void Menu::run() {
   int opcion;

   do {
      system("cls");
      mostrarOpciones();
      opcion = seleccionarOpcion();
      ejecutarOpcion(opcion);
   } while (opcion != 0);
}

void Menu::pausar() {
   cin.ignore(10000, '\n');
   cout << endl << "Presione una tecla para continuar...";
   cin.get();
}

int Menu::seleccionarOpcion() {
   int opcion;

   do {
      cout << "Ingrese opcion: ";
      cin >> opcion;

      if (cin.fail()) {
         cin.clear();
         cin.ignore(10000, '\n');
         opcion = -1;
         cout << " > Opcion no correcta..." << endl;
      } else if (opcion < 0 || opcion > getCantidadOpciones()) {
         cout << " > Opcion no correcta..." << endl;
      }
   } while (opcion < 0 || opcion > getCantidadOpciones());

   return opcion;
}

void Menu::setCantidadOpciones(int cantidad) {
   _cantidadOpciones = cantidad;
}

int Menu::getCantidadOpciones() {
   return _cantidadOpciones;
}
