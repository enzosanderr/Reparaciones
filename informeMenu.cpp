#include <iostream>
#include "informeMenu.h"
using namespace std;

InformeMenu::InformeMenu() {
   setCantidadOpciones(5);
}

void InformeMenu::mostrarOpciones() {
   cout << "=== MENU INFORMES (POR RANGO DE FECHAS) ===" << endl;
   cout << "1. Recaudacion total del taller" << endl;
   cout << "2. Recaudacion detallada por cliente" << endl;
   cout << "3. Estadistica de reparaciones por tipo de equipo" << endl;
   cout << "4. Productividad y facturacion por empleado" << endl;
   cout << "5. Alerta de equipos reincidentes" << endl;
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
