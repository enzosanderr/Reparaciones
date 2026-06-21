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

private:
   bool cargarCamposEditables(Equipo &e);
   void mostrar(const Equipo &e);
   bool nroEquipoUnico(int nro);
   bool clienteExiste(const std::string &cuit);

   EquipoArchivo _repo;
   ClienteArchivo _repoCliente;
};
