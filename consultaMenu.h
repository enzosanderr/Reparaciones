#pragma once
#include "menu.h"
#include "clienteManager.h"
#include "empleadoManager.h"
#include "equipoManager.h"
#include "reparacionManager.h"
#include "consultaManager.h"

class ConsultaMenu : public Menu {
public:
   ConsultaMenu();
   void mostrarOpciones() override;
   void ejecutarOpcion(int opcion) override;

private:
   ClienteManager _mgrCliente;
   EmpleadoManager _mgrEmpleado;
   EquipoManager _mgrEquipo;
   ReparacionManager _mgrReparacion;
   ConsultaManager _mgrConsulta;
};
