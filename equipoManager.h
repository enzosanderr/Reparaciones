#pragma once
#include "equipoArchivo.h"
#include "clienteArchivo.h"

class EquipoManager {
public:
   EquipoManager();

   void alta();
   void baja();
   void modificacion();
   void listado();
   void listadoPorFechaIngreso();
   int contarEquiposPorCuit(const std::string &cuit);

private:
   bool cargarCamposEditables(Equipo &e);
   void mostrar(const Equipo &e);
   bool nroEquipoUnico(int nro);
   bool clienteExiste(const std::string &cuit);
   int seleccionarEquipo();
   bool equipoEnReparacionActiva(int nroEquipo);
   int buscarPorCuit();

   EquipoArchivo _repo;
   ClienteArchivo _repoCliente;
};
