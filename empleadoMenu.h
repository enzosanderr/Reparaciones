#pragma once
#include "menu.h"
#include "empleadoManager.h"

class EmpleadoMenu : public Menu {
public:
   EmpleadoMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   EmpleadoManager _manager;
};
