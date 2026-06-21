#include <cstring>
#include "equipo.h"
using namespace std;

Equipo::Equipo() : _nroEquipo(0), _tipoEquipo(0), _fechaIngreso(), _eliminado(false) {
   _cuit[0] = '\0';
   _descripcion[0] = '\0';
   _marca[0] = '\0';
}

Equipo::Equipo(int nroEquipo, string cuit, string descripcion,
               string marca, int tipoEquipo, Fecha fechaIngreso)
   : _fechaIngreso(fechaIngreso), _eliminado(false) {
   setNroEquipo(nroEquipo);
   setCuit(cuit);
   setDescripcion(descripcion);
   setMarca(marca);
   setTipoEquipo(tipoEquipo);
}

int Equipo::getNroEquipo() const { return _nroEquipo; }
void Equipo::setNroEquipo(int nroEquipo) { _nroEquipo = nroEquipo; }

string Equipo::getCuit() const { return string(_cuit); }
void Equipo::setCuit(string cuit) {
   strncpy(_cuit, cuit.c_str(), sizeof(_cuit) - 1);
   _cuit[sizeof(_cuit) - 1] = '\0';
}

string Equipo::getDescripcion() const { return string(_descripcion); }
void Equipo::setDescripcion(string descripcion) {
   strncpy(_descripcion, descripcion.c_str(), sizeof(_descripcion) - 1);
   _descripcion[sizeof(_descripcion) - 1] = '\0';
}

string Equipo::getMarca() const { return string(_marca); }
void Equipo::setMarca(string marca) {
   strncpy(_marca, marca.c_str(), sizeof(_marca) - 1);
   _marca[sizeof(_marca) - 1] = '\0';
}

int Equipo::getTipoEquipo() const { return _tipoEquipo; }
void Equipo::setTipoEquipo(int tipoEquipo) { _tipoEquipo = tipoEquipo; }

string Equipo::getTipoEquipoString() const {
   switch (_tipoEquipo) {
      case 1: return "PC escritorio";
      case 2: return "Notebook";
      case 3: return "Impresora";
      case 4: return "Periferico";
      case 5: return "Celular";
      default: return "----";
   }
}

Fecha Equipo::getFechaIngreso() const { return _fechaIngreso; }
void Equipo::setFechaIngreso(Fecha fechaIngreso) { _fechaIngreso = fechaIngreso; }

bool Equipo::getEliminado() const { return _eliminado; }
void Equipo::setEliminado(bool eliminado) { _eliminado = eliminado; }
