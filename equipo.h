#pragma once
#include <string>
#include "fecha.h"

class Equipo {
public:
   Equipo();
   Equipo(int nroEquipo, std::string cuit, std::string descripcion,
          std::string marca, int tipoEquipo, Fecha fechaIngreso);

   int getNroEquipo() const;
   void setNroEquipo(int nroEquipo);

   std::string getCuit() const;
   void setCuit(std::string cuit);

   std::string getDescripcion() const;
   void setDescripcion(std::string descripcion);

   std::string getMarca() const;
   void setMarca(std::string marca);

   int getTipoEquipo() const;
   void setTipoEquipo(int tipoEquipo);
   std::string getTipoEquipoString() const;

   Fecha getFechaIngreso() const;
   void setFechaIngreso(Fecha fechaIngreso);

   bool getEliminado() const;
   void setEliminado(bool eliminado);

private:
   int _nroEquipo;
   char _cuit[15];
   char _descripcion[50];
   char _marca[30];
   int _tipoEquipo;
   Fecha _fechaIngreso;
   bool _eliminado;
};
