#include <cstdio>
#include "detalleReparacionArchivo.h"
using namespace std;

DetalleReparacionArchivo::DetalleReparacionArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool DetalleReparacionArchivo::crear(const DetalleReparacion &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "ab");
   if (pFile == nullptr) return false;

   bool result = fwrite(&reg, sizeof(DetalleReparacion), 1, pFile);
   fclose(pFile);
   return result;
}

bool DetalleReparacionArchivo::actualizar(int pos, const DetalleReparacion &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb+");
   if (pFile == nullptr) return false;

   fseek(pFile, pos * sizeof(DetalleReparacion), SEEK_SET);
   bool result = fwrite(&reg, sizeof(DetalleReparacion), 1, pFile);
   fclose(pFile);
   return result;
}

DetalleReparacion DetalleReparacionArchivo::leer(int pos) {
   DetalleReparacion reg;
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return reg;

   fseek(pFile, pos * sizeof(DetalleReparacion), SEEK_SET);
   fread(&reg, sizeof(DetalleReparacion), 1, pFile);
   fclose(pFile);
   return reg;
}

int DetalleReparacionArchivo::leerTodos(DetalleReparacion vDetalles[], int cantidad) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   int result = fread(vDetalles, sizeof(DetalleReparacion), cantidad, pFile);
   fclose(pFile);
   return result;
}

int DetalleReparacionArchivo::getCantidadRegistros() {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   fseek(pFile, 0, SEEK_END);
   int cant = ftell(pFile) / sizeof(DetalleReparacion);
   fclose(pFile);
   return cant;
}

int DetalleReparacionArchivo::buscarDetalle(int nroReparacion, int nroEquipo) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return -1;

   DetalleReparacion reg;
   int pos = 0, result = -1;
   while (fread(&reg, sizeof(DetalleReparacion), 1, pFile)) {
      if (reg.getNroReparacion() == nroReparacion &&
          reg.getNroEquipo() == nroEquipo &&
          !reg.getEliminado()) {
         result = pos;
         break;
      }
      pos++;
   }
   fclose(pFile);
   return result;
}
