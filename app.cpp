#include <iostream>
#include "app.h"
using namespace std;

App::App() {
   setCantidadOpciones(6);
}

void App::mostrarOpciones() {
    cout << "=== REPARALO TODO - MENU PRINCIPAL ===" << endl<<endl;
    cout << "1. Clientes" << endl;
    cout << "2. Equipos" << endl;
    cout << "3. Empleados" << endl;
    cout << "4. Reparaciones" << endl;
    cout << "5. Informes" << endl;
    cout << "6. Configuracion (Backup / CSV)" << endl;
    cout << "0. Salir" << endl;
}

void App::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1: _menuCliente.run(); break;
        case 2: _menuEquipo.run(); break;
        case 3: _menuEmpleado.run(); break;
        case 4: _menuReparacion.run(); break;
        case 5: _menuInforme.run(); break;
        case 6: _menuConfiguracion.run(); break;
        case 0: cout << "Saliendo..." << endl; break;
    }
}
