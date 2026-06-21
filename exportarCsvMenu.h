#pragma once
#include "menu.h"
#include "configuracionManager.h"

class ExportarCsvMenu : public Menu {
public:
   ExportarCsvMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   ConfiguracionManager _manager;
};
