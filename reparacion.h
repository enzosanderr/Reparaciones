#pragma once
#include <string>
#include "fecha.h"

class Reparacion {
public:
   Reparacion();
   Reparacion(int nroReparacion, std::string cuit, std::string legajo,
               Fecha fechaIngreso, Fecha fechaEntrega);

   int getNroReparacion() const;
   void setNroReparacion(int nroReparacion);

   std::string getCuit() const;
   void setCuit(std::string cuit);

   std::string getLegajo() const;
   void setLegajo(std::string legajo);

   void setFechaIngreso(Fecha fechaIngreso);
   Fecha getFechaIngreso() const;

   Fecha getFechaEntrega() const;
   void setFechaEntrega(Fecha fechaEntrega);

    int getEstado() const;
    void setEstado(int estado);

   bool getEliminado() const;
   void setEliminado(bool eliminado);

private:
   int _nroReparacion;
   char _cuit[15];
   char _legajo[10];
   Fecha _fechaIngreso;
   Fecha _fechaEntrega;
   int _estado;
   bool _eliminado;
};
