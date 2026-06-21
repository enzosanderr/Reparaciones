#pragma once
#include "menu.h"
#include "reparacionManager.h"

class ReparacionMenu : public Menu {
public:
   ReparacionMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   ReparacionManager _manager;
};
