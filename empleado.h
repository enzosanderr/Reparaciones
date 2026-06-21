#pragma once
#include <string>

class Empleado {
public:
   Empleado();
   Empleado(std::string legajo, std::string nombre, std::string apellido);

   std::string getLegajo() const;
   void setLegajo(std::string legajo);

   std::string getNombre() const;
   void setNombre(std::string nombre);

   std::string getApellido() const;
   void setApellido(std::string apellido);

   bool getEliminado() const;
   void setEliminado(bool eliminado);

private:
   char _legajo[10];
   char _nombre[20];
   char _apellido[20];
   bool _eliminado;
};
