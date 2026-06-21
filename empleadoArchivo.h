#pragma once
#include <string>
#include "empleado.h"

class EmpleadoArchivo {
public:
   EmpleadoArchivo(std::string nombreArchivo = "empleados.dat");

   bool crear(const Empleado &reg);
   bool actualizar(int pos, const Empleado &reg);

   Empleado leer(int pos);
   int leerTodos(Empleado vEmpleados[], int cantidad);

   int getCantidadRegistros();
   int buscarPorLegajo(const std::string &legajo);

private:
   std::string _nombreArchivo;
};
