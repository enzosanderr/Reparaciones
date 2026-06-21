#pragma once
#include "menu.h"
#include "equipoManager.h"

class EquipoMenu : public Menu {
public:
   EquipoMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   EquipoManager _manager;
};
