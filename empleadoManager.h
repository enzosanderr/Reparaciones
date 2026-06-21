#pragma once
#include "empleadoArchivo.h"

class EmpleadoManager {
public:
   EmpleadoManager();

   void cargarInicialesSiVacio();

   void alta();
   void baja();
   void modificacion();
   void listado();
   void listadoPorApellido();

private:
   Empleado cargarDatos();
   void cargarCamposEditables(Empleado &e);
   void mostrar(const Empleado &e);
   bool legajoUnico(const std::string &legajo);

   EmpleadoArchivo _repo;
};
