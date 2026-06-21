#include <sstream>
#include <chrono>
#include "fecha.h"

Fecha::Fecha() : _dia(1), _mes(1), _anio(2000) {}

Fecha::Fecha(int dia, int mes, int anio) : _dia(dia), _mes(mes), _anio(anio) {}

int Fecha::getDia() const { return _dia; }
void Fecha::setDia(int dia) { _dia = dia; }

int Fecha::getMes() const { return _mes; }
void Fecha::setMes(int mes) { _mes = mes; }

int Fecha::getAnio() const { return _anio; }
void Fecha::setAnio(int anio) { _anio = anio; }

bool Fecha::esValida() const {
   if (_anio <= 0 || _mes < 1 || _mes > 12) return false;

   int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   int maxDia = dias[_mes];

   bool bisiesto = (_anio % 4 == 0 && _anio % 100 != 0) || (_anio % 400 == 0);
   if (_mes == 2 && bisiesto) maxDia = 29;

   return _dia >= 1 && _dia <= maxDia;
}

long Fecha::aNumero() const {
   return (long)_anio * 10000L + (long)_mes * 100L + (long)_dia;
}

std::string Fecha::toString() const {
   std::ostringstream os;
   os << _dia << "/" << _mes << "/" << _anio;
   return os.str();
}


///sacado del proyecto de Brian
void Fecha::setFechaActual() {
    // Obtener la fecha actual del sistema
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&now_c);

    // Asignar los valores a la fecha
    _dia = localTime->tm_mday;
    _mes = localTime->tm_mon + 1; // tm_mon va de 0 a 11
    _anio = localTime->tm_year + 1900; // tm_year es el número de años desde 1900
}
