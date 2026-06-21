#include <cstdio>
#include "reparacionArchivo.h"
using namespace std;

ReparacionArchivo::ReparacionArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool ReparacionArchivo::crear(const Reparacion &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "ab");
   if (pFile == nullptr) return false;

   bool result = fwrite(&reg, sizeof(Reparacion), 1, pFile);
   fclose(pFile);
   return result;
}

bool ReparacionArchivo::actualizar(int pos, const Reparacion &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb+");
   if (pFile == nullptr) return false;

   fseek(pFile, pos * sizeof(Reparacion), SEEK_SET);
   bool result = fwrite(&reg, sizeof(Reparacion), 1, pFile);
   fclose(pFile);
   return result;
}

Reparacion ReparacionArchivo::leer(int pos) {
   Reparacion reg;
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return reg;

   fseek(pFile, pos * sizeof(Reparacion), SEEK_SET);
   fread(&reg, sizeof(Reparacion), 1, pFile);
   fclose(pFile);
   return reg;
}

int ReparacionArchivo::leerTodos(Reparacion vReparaciones[], int cantidad) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   int result = fread(vReparaciones, sizeof(Reparacion), cantidad, pFile);
   fclose(pFile);
   return result;
}

int ReparacionArchivo::getCantidadRegistros() {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   fseek(pFile, 0, SEEK_END);
   int cant = ftell(pFile) / sizeof(Reparacion);
   fclose(pFile);
   return cant;
}

int ReparacionArchivo::getNuevoId() {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 1;

   Reparacion reg;
   int maxNro = 0;
   while (fread(&reg, sizeof(Reparacion), 1, pFile)) {
      if (reg.getNroReparacion() > maxNro) {
         maxNro = reg.getNroReparacion();
      }
   }
   fclose(pFile);
   return maxNro + 1;
}

int ReparacionArchivo::buscarPorNumero(int nroReparacion) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return -1;

   Reparacion reg;
   int pos = 0, result = -1;
   while (fread(&reg, sizeof(Reparacion), 1, pFile)) {
      if (reg.getNroReparacion() == nroReparacion && !reg.getEliminado()) {
         result = pos;
         break;
      }
      pos++;
   }
   fclose(pFile);
   return result;
}
