#pragma once

class DetalleReparacion {
public:
   DetalleReparacion();
   DetalleReparacion(int nroReparacion, int nroEquipo, float importe);

   int getNroReparacion() const;
   void setNroReparacion(int nroReparacion);

   int getNroEquipo() const;
   void setNroEquipo(int nroEquipo);

   float getImporte() const;
   void setImporte(float importe);

   bool getEliminado() const;
   void setEliminado(bool eliminado);

private:
   int _nroReparacion;
   int _nroEquipo;
   float _importe;
   bool _eliminado;
};
