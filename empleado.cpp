#include <cstring>
#include "empleado.h"
using namespace std;

Empleado::Empleado() : _eliminado(false) {
   _legajo[0] = '\0';
   _nombre[0] = '\0';
   _apellido[0] = '\0';
}

Empleado::Empleado(string legajo, string nombre, string apellido)
   : _eliminado(false) {
   setLegajo(legajo);
   setNombre(nombre);
   setApellido(apellido);
}

string Empleado::getLegajo() const { return string(_legajo); }
void Empleado::setLegajo(string legajo) {
   strncpy(_legajo, legajo.c_str(), sizeof(_legajo) - 1);
   _legajo[sizeof(_legajo) - 1] = '\0';
}

string Empleado::getNombre() const { return string(_nombre); }
void Empleado::setNombre(string nombre) {
   strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
   _nombre[sizeof(_nombre) - 1] = '\0';
}

string Empleado::getApellido() const { return string(_apellido); }
void Empleado::setApellido(string apellido) {
   strncpy(_apellido, apellido.c_str(), sizeof(_apellido) - 1);
   _apellido[sizeof(_apellido) - 1] = '\0';
}

bool Empleado::getEliminado() const { return _eliminado; }
void Empleado::setEliminado(bool eliminado) { _eliminado = eliminado; }
