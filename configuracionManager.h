#pragma once
#include <string>
#include "clienteArchivo.h"
#include "equipoArchivo.h"
#include "empleadoArchivo.h"
#include "reparacionArchivo.h"
#include "detalleReparacionArchivo.h"

class ConfiguracionManager {
public:
   ConfiguracionManager();

   void backupArchivo(const std::string &nombreDat);
   void backupTodos();
   void restaurarArchivo(const std::string &nombreDat);
   void restaurarTodos();

   void exportarClientesCSV();
   void exportarEquiposCSV();
   void exportarEmpleadosCSV();
   void exportarReparacionesCSV();
   void exportarDetalleReparacionesCSV();
   void exportarTodosCSV();

private:
   bool copiarArchivo(const std::string &origen, const std::string &destino);
   void asegurarCarpeta(const std::string &nombre);
   std::string rutaBackup(const std::string &nombreDat);
   int generarCodigoConfirmacion(const std::string &nombre);

   ClienteArchivo _repoCliente;
   EquipoArchivo _repoEquipo;
   EmpleadoArchivo _repoEmpleado;
   ReparacionArchivo _repoReparacion;
   DetalleReparacionArchivo _repoDetalle;
};
