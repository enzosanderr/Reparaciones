#include <iostream>
#include "configuracionMenu.h"
using namespace std;

ConfiguracionMenu::ConfiguracionMenu() {
   setCantidadOpciones(3);
}

void ConfiguracionMenu::mostrarOpciones() {
   cout << "=== MENU CONFIGURACION ===" << endl;
   cout << "1. Realizar copia de seguridad" << endl;
   cout << "2. Restaurar copia de seguridad" << endl;
   cout << "3. Exportar datos a CSV" << endl;
   cout << "0. Volver al menu principal" << endl;
}

void ConfiguracionMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _menuBackup.run(); break;
      case 2: _menuRestaurar.run(); break;
      case 3: _menuExportar.run(); break;
      case 0: cout << "Volviendo al menu principal..." << endl; break;
   }
}
