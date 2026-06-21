#pragma once
#include <string>
#include "fecha.h"

class Reparacion {
public:
   Reparacion();
   Reparacion(int nroReparacion, std::string cuit, std::string legajo,
              Fecha fechaEntrega);

   int getNroReparacion() const;
   void setNroReparacion(int nroReparacion);

   std::string getCuit() const;
   void setCuit(std::string cuit);

   std::string getLegajo() const;
   void setLegajo(std::string legajo);

   Fecha getFechaEntrega() const;
   void setFechaEntrega(Fecha fechaEntrega);

   bool getEliminado() const;
   void setEliminado(bool eliminado);

private:
   int _nroReparacion;
   char _cuit[15];
   char _legajo[10];
   Fecha _fechaEntrega;
   bool _eliminado;
};
