#pragma once
#include <string>

class DetalleReparacion {
public:
   DetalleReparacion();
   DetalleReparacion(int nroReparacion, int nroEquipo, float importe, const char* falla);

   int getNroReparacion() const;
   void setNroReparacion(int nroReparacion);

   int getNroEquipo() const;
   void setNroEquipo(int nroEquipo);

   float getImporte() const;
   void setImporte(float importe);

    const char* getDetalleFalla() const;
    void setDetalleFalla(const char* falla);

   bool getEliminado() const;
   void setEliminado(bool eliminado);

private:
   int _nroReparacion;
   int _nroEquipo;
   float _importe;
   char _detalleFalla[100];
   bool _eliminado;
};
