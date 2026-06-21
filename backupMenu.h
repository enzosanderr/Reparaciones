#pragma once
#include "menu.h"
#include "configuracionManager.h"

class BackupMenu : public Menu {
public:
   BackupMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   ConfiguracionManager _manager;
};
