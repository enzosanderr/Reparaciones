#pragma once
#include "menu.h"
#include "informeManager.h"

class InformeMenu : public Menu {
public:
   InformeMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   InformeManager _manager;
};
