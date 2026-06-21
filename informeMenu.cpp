#include <iostream>
#include "informeMenu.h"
using namespace std;

InformeMenu::InformeMenu() {
   setCantidadOpciones(5);
}

void InformeMenu::mostrarOpciones() {
   cout << "=== MENU INFORMES ===" << endl;
   cout << "1. Recaudacion mensual (por periodo)" << endl;
   cout << "2. Recaudacion por cliente" << endl;
   cout << "3. Reparaciones por tipo de equipo" << endl;
   cout << "4. Productividad por empleado" << endl;
   cout << "5. Equipos reincidentes" << endl;
   cout << "0. Volver al menu principal" << endl;
}

void InformeMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _manager.recaudacionPorPeriodo(); break;
      case 2: _manager.recaudacionPorCliente(); break;
      case 3: _manager.reparacionesPorTipoEquipo(); break;
      case 4: _manager.productividadEmpleados(); break;
      case 5: _manager.equiposReincidentes(); break;
      case 0: return;
   }
   pausar();
}
