#include <iostream>
#include "equipoMenu.h"
using namespace std;

EquipoMenu::EquipoMenu() {
   setCantidadOpciones(4);
}

void EquipoMenu::mostrarOpciones() {
   cout << "=== MENU EQUIPOS ===" << endl;
   cout << "1. Alta de equipo" << endl;
   cout << "2. Baja de equipo" << endl;
   cout << "3. Modificacion de equipo" << endl;
   cout << "4. Listado de equipos" << endl;
   cout << "0. Volver al menu principal" << endl;
}

void EquipoMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _manager.alta(); break;
      case 2: _manager.baja(); break;
      case 3: _manager.modificacion(); break;
      case 4: _manager.listado(); break;
      case 0: return;
   }
   pausar();
}
