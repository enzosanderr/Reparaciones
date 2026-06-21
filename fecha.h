#pragma once
#include <string>

class Fecha {
public:
   Fecha();
   Fecha(int dia, int mes, int anio);

   int getDia() const;
   void setDia(int dia);

   int getMes() const;
   void setMes(int mes);

   int getAnio() const;
   void setAnio(int anio);

   bool esValida() const;
   long aNumero() const;
   std::string toString() const;

    void setFechaActual(); // Método para cargar la fecha actual del sistema

private:
   int _dia;
   int _mes;
   int _anio;
};
