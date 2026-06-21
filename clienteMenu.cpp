#include <iostream>
#include "clienteMenu.h"
using namespace std;

ClienteMenu::ClienteMenu() {
   setCantidadOpciones(4);
}

void ClienteMenu::mostrarOpciones() {
    cout << "=== MENU CLIENTES ===" << endl;
    cout << "1. Alta de cliente" << endl;
    cout << "2. Baja de cliente" << endl;
    cout << "3. Modificacion de cliente" << endl;
    cout << "4. Consultas y Listados" << endl;
    cout << "0. Volver al menu principal" << endl;
}

void ClienteMenu::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1: _manager.alta(); break;
        case 2: _manager.baja(); break;
        case 3: _manager.modificacion(); break;
        case 4: _manager.menuConsultas(); break;
        case 0: return;
    }
   pausar();
}
