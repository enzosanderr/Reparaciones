#pragma once
#include "reparacionManager.h"
#include "clienteArchivo.h"
#include "equipoArchivo.h"
#include "reparacionArchivo.h"

class ConsultaManager {
public:
   ConsultaManager();

   void consultaClientePorCuit();
   void consultaEquiposPorCliente();
   void consultaReparacionesPorCliente();
   void consultaReparacionesPorRangoFechas();

private:
   ReparacionManager _mgrReparacion;
   ClienteArchivo _repoCliente;
   EquipoArchivo _repoEquipo;
   ReparacionArchivo _repoReparacion;
};
