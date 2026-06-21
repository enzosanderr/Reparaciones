#pragma once
#include <string>
#include "reparacion.h"

class ReparacionArchivo {
public:
   ReparacionArchivo(std::string nombreArchivo = "reparaciones.dat");

   bool crear(const Reparacion &reg);
   bool actualizar(int pos, const Reparacion &reg);

   Reparacion leer(int pos);
   int leerTodos(Reparacion vReparaciones[], int cantidad);

   int getCantidadRegistros();
   int getNuevoId();
   int buscarPorNumero(int nroReparacion);

private:
   std::string _nombreArchivo;
};
