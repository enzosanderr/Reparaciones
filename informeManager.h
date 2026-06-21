#pragma once
#include "reparacionManager.h"
#include "clienteArchivo.h"
#include "empleadoArchivo.h"
#include "equipoArchivo.h"
#include "reparacionArchivo.h"
#include "detalleReparacionArchivo.h"

class InformeManager {
public:
   InformeManager();

   void recaudacionPorPeriodo();
   void recaudacionPorCliente();
   void reparacionesPorTipoEquipo();
   void productividadEmpleados();
   void equiposReincidentes();

private:
   ReparacionManager _mgrReparacion;
   ClienteArchivo _repoCliente;
   EmpleadoArchivo _repoEmpleado;
   EquipoArchivo _repoEquipo;
   ReparacionArchivo _repoReparacion;
   DetalleReparacionArchivo _repoDetalle;
};
