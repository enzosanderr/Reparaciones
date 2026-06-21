#pragma once
#include <string>
#include "detalleReparacion.h"

class DetalleReparacionArchivo {
public:
   DetalleReparacionArchivo(std::string nombreArchivo = "detalleReparaciones.dat");

   bool crear(const DetalleReparacion &reg);
   bool actualizar(int pos, const DetalleReparacion &reg);

   DetalleReparacion leer(int pos);
   int leerTodos(DetalleReparacion vDetalles[], int cantidad);

   int getCantidadRegistros();
   int buscarDetalle(int nroReparacion, int nroEquipo);

private:
   std::string _nombreArchivo;
};
