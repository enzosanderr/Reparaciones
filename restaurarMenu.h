#pragma once
#include "menu.h"
#include "configuracionManager.h"

class RestaurarMenu : public Menu {
public:
   RestaurarMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   ConfiguracionManager _manager;
};
