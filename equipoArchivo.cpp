#include <cstdio>
#include "equipoArchivo.h"
using namespace std;

EquipoArchivo::EquipoArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool EquipoArchivo::crear(const Equipo &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "ab");
   if (pFile == nullptr) return false;

   bool result = fwrite(&reg, sizeof(Equipo), 1, pFile);
   fclose(pFile);
   return result;
}

bool EquipoArchivo::actualizar(int pos, const Equipo &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb+");
   if (pFile == nullptr) return false;

   fseek(pFile, pos * sizeof(Equipo), SEEK_SET);
   bool result = fwrite(&reg, sizeof(Equipo), 1, pFile);
   fclose(pFile);
   return result;
}

Equipo EquipoArchivo::leer(int pos) {
   Equipo reg;
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return reg;

   fseek(pFile, pos * sizeof(Equipo), SEEK_SET);
   fread(&reg, sizeof(Equipo), 1, pFile);
   fclose(pFile);
   return reg;
}

int EquipoArchivo::leerTodos(Equipo vEquipos[], int cantidad) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   int result = fread(vEquipos, sizeof(Equipo), cantidad, pFile);
   fclose(pFile);
   return result;
}

int EquipoArchivo::getCantidadRegistros() {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   fseek(pFile, 0, SEEK_END);
   int cant = ftell(pFile) / sizeof(Equipo);
   fclose(pFile);
   return cant;
}

int EquipoArchivo::buscarPorNumero(int nroEquipo) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return -1;

   Equipo reg;
   int pos = 0, result = -1;
   while (fread(&reg, sizeof(Equipo), 1, pFile)) {
      if (reg.getNroEquipo() == nroEquipo && !reg.getEliminado()) {
         result = pos;
         break;
      }
      pos++;
   }
   fclose(pFile);
   return result;
}

int EquipoArchivo::getNuevoId() {

    FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr) return 1;

    Equipo reg;
    int maxNro = 0;

    while (fread(&reg, sizeof(Equipo), 1, pFile)) {
        if (reg.getNroEquipo() > maxNro) {
            maxNro = reg.getNroEquipo();
        }
    }

    fclose(pFile);

    return maxNro + 1;
}
