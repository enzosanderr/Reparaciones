#include "detalleReparacion.h"
#include <cstring>

DetalleReparacion::DetalleReparacion()
    : _nroReparacion(0), _nroEquipo(0), _importe(0), _eliminado(false)
{
    strcpy(_detalleFalla, "");
}

DetalleReparacion::DetalleReparacion(int nroReparacion, int nroEquipo, float importe, const char* falla)
    : _nroReparacion(nroReparacion), _nroEquipo(nroEquipo), _importe(importe), _eliminado(false)
{
    strcpy(_detalleFalla, falla);
}

int DetalleReparacion::getNroReparacion() const
{
    return _nroReparacion;
}
void DetalleReparacion::setNroReparacion(int nroReparacion)
{
    _nroReparacion = nroReparacion;
}

int DetalleReparacion::getNroEquipo() const
{
    return _nroEquipo;
}
void DetalleReparacion::setNroEquipo(int nroEquipo)
{
    _nroEquipo = nroEquipo;
}

float DetalleReparacion::getImporte() const
{
    return _importe;
}
void DetalleReparacion::setImporte(float importe)
{
    _importe = importe;
}

    const char* DetalleReparacion::getDetalleFalla() const
    {
        return _detalleFalla;
    }

    void DetalleReparacion::setDetalleFalla(const char* falla)
    {
        strcpy(_detalleFalla, falla);
    }

    bool DetalleReparacion::getEliminado() const
    {
        return _eliminado;
    }
    void DetalleReparacion::setEliminado(bool eliminado)
    {
        _eliminado = eliminado;
    }
