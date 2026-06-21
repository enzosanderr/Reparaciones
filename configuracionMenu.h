#pragma once
#include "menu.h"
#include "backupMenu.h"
#include "restaurarMenu.h"
#include "exportarCsvMenu.h"

class ConfiguracionMenu : public Menu {
public:
   ConfiguracionMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   BackupMenu _menuBackup;
   RestaurarMenu _menuRestaurar;
   ExportarCsvMenu _menuExportar;
};
