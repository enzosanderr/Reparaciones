#include "detalleReparacion.h"

DetalleReparacion::DetalleReparacion()
   : _nroReparacion(0), _nroEquipo(0), _importe(0), _eliminado(false) {}

DetalleReparacion::DetalleReparacion(int nroReparacion, int nroEquipo, float importe)
   : _nroReparacion(nroReparacion), _nroEquipo(nroEquipo), _importe(importe),
     _eliminado(false) {}

int DetalleReparacion::getNroReparacion() const { return _nroReparacion; }
void DetalleReparacion::setNroReparacion(int nroReparacion) { _nroReparacion = nroReparacion; }

int DetalleReparacion::getNroEquipo() const { return _nroEquipo; }
void DetalleReparacion::setNroEquipo(int nroEquipo) { _nroEquipo = nroEquipo; }

float DetalleReparacion::getImporte() const { return _importe; }
void DetalleReparacion::setImporte(float importe) { _importe = importe; }

bool DetalleReparacion::getEliminado() const { return _eliminado; }
void DetalleReparacion::setEliminado(bool eliminado) { _eliminado = eliminado; }
