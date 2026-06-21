#include <iostream>
#include "app.h"
using namespace std;

App::App() {
   setCantidadOpciones(7);
}

void App::mostrarOpciones() {
   cout << "=== REPARALO TODO - MENU PRINCIPAL ===" << endl;
   cout << "1. Clientes" << endl;
   cout << "2. Equipos" << endl;
   cout << "3. Empleados" << endl;
   cout << "4. Reparaciones" << endl;
   cout << "5. Consultas y Listados" << endl;
   cout << "6. Informes" << endl;
   cout << "7. Configuracion (Backup / CSV)" << endl;
   cout << "0. Salir" << endl;
}

void App::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _menuCliente.run(); break;
      case 2: _menuEquipo.run(); break;
      case 3: _menuEmpleado.run(); break;
      case 4: _menuReparacion.run(); break;
      case 5: _menuConsulta.run(); break;
      case 6: _menuInforme.run(); break;
      case 7: _menuConfiguracion.run(); break;
      case 0: cout << "Saliendo..." << endl; break;
   }
}
