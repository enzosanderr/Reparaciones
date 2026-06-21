#include <iostream>
#include "backupMenu.h"
using namespace std;

BackupMenu::BackupMenu() {
   setCantidadOpciones(6);
}

void BackupMenu::mostrarOpciones() {
   cout << "=== REALIZAR COPIA DE SEGURIDAD ===" << endl;
   cout << "1. Clientes" << endl;
   cout << "2. Equipos" << endl;
   cout << "3. Empleados" << endl;
   cout << "4. Reparaciones" << endl;
   cout << "5. Detalle de reparaciones" << endl;
   cout << "6. TODOS los archivos" << endl;
   cout << "0. Volver" << endl;
}

void BackupMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _manager.backupArchivo("clientes.dat"); break;
      case 2: _manager.backupArchivo("equipos.dat"); break;
      case 3: _manager.backupArchivo("empleados.dat"); break;
      case 4: _manager.backupArchivo("reparaciones.dat"); break;
      case 5: _manager.backupArchivo("detalleReparaciones.dat"); break;
      case 6: _manager.backupTodos(); break;
      case 0: return;
   }
}
