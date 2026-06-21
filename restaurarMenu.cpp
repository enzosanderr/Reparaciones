#include <iostream>
#include "restaurarMenu.h"
using namespace std;

RestaurarMenu::RestaurarMenu() {
   setCantidadOpciones(6);
}

void RestaurarMenu::mostrarOpciones() {
   cout << "=== RESTAURAR COPIA DE SEGURIDAD ===" << endl;
   cout << "1. Clientes" << endl;
   cout << "2. Equipos" << endl;
   cout << "3. Empleados" << endl;
   cout << "4. Reparaciones" << endl;
   cout << "5. Detalle de reparaciones" << endl;
   cout << "6. TODOS los archivos" << endl;
   cout << "0. Volver" << endl;
}

void RestaurarMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _manager.restaurarArchivo("clientes.dat"); break;
      case 2: _manager.restaurarArchivo("equipos.dat"); break;
      case 3: _manager.restaurarArchivo("empleados.dat"); break;
      case 4: _manager.restaurarArchivo("reparaciones.dat"); break;
      case 5: _manager.restaurarArchivo("detalleReparaciones.dat"); break;
      case 6: _manager.restaurarTodos(); break;
      case 0: return;
   }
   pausar();
}
