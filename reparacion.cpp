#include <cstring>
#include "reparacion.h"
using namespace std;

Reparacion::Reparacion() : _nroReparacion(0), _fechaEntrega(), _eliminado(false) {
   _cuit[0] = '\0';
   _legajo[0] = '\0';
}

Reparacion::Reparacion(int nroReparacion, string cuit, string legajo,
                       Fecha fechaEntrega)
   : _fechaEntrega(fechaEntrega), _eliminado(false) {
   setNroReparacion(nroReparacion);
   setCuit(cuit);
   setLegajo(legajo);
}

int Reparacion::getNroReparacion() const { return _nroReparacion; }
void Reparacion::setNroReparacion(int nroReparacion) { _nroReparacion = nroReparacion; }

string Reparacion::getCuit() const { return string(_cuit); }
void Reparacion::setCuit(string cuit) {
   strncpy(_cuit, cuit.c_str(), sizeof(_cuit) - 1);
   _cuit[sizeof(_cuit) - 1] = '\0';
}

string Reparacion::getLegajo() const { return string(_legajo); }
void Reparacion::setLegajo(string legajo) {
   strncpy(_legajo, legajo.c_str(), sizeof(_legajo) - 1);
   _legajo[sizeof(_legajo) - 1] = '\0';
}

Fecha Reparacion::getFechaEntrega() const { return _fechaEntrega; }
void Reparacion::setFechaEntrega(Fecha fechaEntrega) { _fechaEntrega = fechaEntrega; }

bool Reparacion::getEliminado() const { return _eliminado; }
void Reparacion::setEliminado(bool eliminado) { _eliminado = eliminado; }
