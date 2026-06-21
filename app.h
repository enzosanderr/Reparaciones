#pragma once
#include "menu.h"
#include "clienteMenu.h"
#include "equipoMenu.h"
#include "empleadoMenu.h"
#include "reparacionMenu.h"
#include "consultaMenu.h"
#include "informeMenu.h"
#include "configuracionMenu.h"

class App : public Menu {
public:
   App();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   ClienteMenu _menuCliente;
   EquipoMenu _menuEquipo;
   EmpleadoMenu _menuEmpleado;
   ReparacionMenu _menuReparacion;
   InformeMenu _menuInforme;
   ConfiguracionMenu _menuConfiguracion;
};
