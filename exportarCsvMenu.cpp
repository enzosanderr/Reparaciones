#include <iostream>
#include "exportarCsvMenu.h"
using namespace std;

ExportarCsvMenu::ExportarCsvMenu() {
   setCantidadOpciones(6);
}

void ExportarCsvMenu::mostrarOpciones() {
   cout << "=== EXPORTAR ARCHIVOS CSV ===" << endl;
   cout << "1. Clientes" << endl;
   cout << "2. Equipos" << endl;
   cout << "3. Empleados" << endl;
   cout << "4. Reparaciones" << endl;
   cout << "5. Detalle de reparaciones" << endl;
   cout << "6. TODOS los archivos" << endl;
   cout << "0. Volver" << endl;
}

void ExportarCsvMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _manager.exportarClientesCSV(); break;
      case 2: _manager.exportarEquiposCSV(); break;
      case 3: _manager.exportarEmpleadosCSV(); break;
      case 4: _manager.exportarReparacionesCSV(); break;
      case 5: _manager.exportarDetalleReparacionesCSV(); break;
      case 6: _manager.exportarTodosCSV(); break;
      case 0: return;
   }
   pausar();
}
