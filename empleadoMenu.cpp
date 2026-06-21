#include <iostream>
#include "empleadoMenu.h"
using namespace std;

EmpleadoMenu::EmpleadoMenu() {
   setCantidadOpciones(4);
}

void EmpleadoMenu::mostrarOpciones() {
   cout << "=== MENU EMPLEADOS ===" << endl;
   cout << "1. Alta de empleado" << endl;
   cout << "2. Baja de empleado" << endl;
   cout << "3. Modificacion de empleado" << endl;
   cout << "4. Consultas y Listados" << endl;
   cout << "0. Volver al menu principal" << endl;
}

void EmpleadoMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _manager.alta(); break;
      case 2: _manager.baja(); break;
      case 3: _manager.modificacion(); break;
      case 4: _manager.menuConsultas(); break;
      case 0: return;
   }
}
