#pragma once
#include "menu.h"
#include "clienteManager.h"

class ClienteMenu : public Menu {
public:
   ClienteMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   ClienteManager _manager;
};
