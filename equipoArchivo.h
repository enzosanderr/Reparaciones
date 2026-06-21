#pragma once
#include <string>
#include "equipo.h"

class EquipoArchivo {
public:
   EquipoArchivo(std::string nombreArchivo = "equipos.dat");

   bool crear(const Equipo &reg);
   bool actualizar(int pos, const Equipo &reg);

   Equipo leer(int pos);
   int leerTodos(Equipo vEquipos[], int cantidad);

   int getCantidadRegistros();
   int buscarPorNumero(int nroEquipo);

private:
   std::string _nombreArchivo;
};
