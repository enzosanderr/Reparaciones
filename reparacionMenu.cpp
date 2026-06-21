#include <iostream>
#include "reparacionMenu.h"
using namespace std;

ReparacionMenu::ReparacionMenu() {
    setCantidadOpciones(4);
}

void ReparacionMenu::mostrarOpciones() {
    cout << "=== MENU REPARACIONES ===" << endl;
    cout << "1. Alta de reparacion" << endl;
    cout << "2. Baja / Anulacion" << endl;
    cout << "3. Modificacion / Actualizar Estado" << endl;
    cout << "4. Consultas y Listados" << endl; // 🟢 Apuntando al nuevo formato
    cout << "0. Volver al menu principal" << endl;
}

void ReparacionMenu::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1: _manager.alta(); break;
        case 2: _manager.baja(); break;
        case 3: _manager.modificacion(); break;
        case 4: _manager.menuConsultas(); break; // 🟢 Llama al submenú integrado
        case 0: return;
    }
}
