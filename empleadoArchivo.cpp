#include <cstdio>
#include "empleadoArchivo.h"
using namespace std;

EmpleadoArchivo::EmpleadoArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool EmpleadoArchivo::crear(const Empleado &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "ab");
   if (pFile == nullptr) return false;

   bool result = fwrite(&reg, sizeof(Empleado), 1, pFile);
   fclose(pFile);
   return result;
}

bool EmpleadoArchivo::actualizar(int pos, const Empleado &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb+");
   if (pFile == nullptr) return false;

   fseek(pFile, pos * sizeof(Empleado), SEEK_SET);
   bool result = fwrite(&reg, sizeof(Empleado), 1, pFile);
   fclose(pFile);
   return result;
}

Empleado EmpleadoArchivo::leer(int pos) {
   Empleado reg;
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return reg;

   fseek(pFile, pos * sizeof(Empleado), SEEK_SET);
   fread(&reg, sizeof(Empleado), 1, pFile);
   fclose(pFile);
   return reg;
}

int EmpleadoArchivo::leerTodos(Empleado vEmpleados[], int cantidad) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   int result = fread(vEmpleados, sizeof(Empleado), cantidad, pFile);
   fclose(pFile);
   return result;
}

int EmpleadoArchivo::getCantidadRegistros() {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   fseek(pFile, 0, SEEK_END);
   int cant = ftell(pFile) / sizeof(Empleado);
   fclose(pFile);
   return cant;
}

int EmpleadoArchivo::buscarPorLegajo(const string &legajo) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return -1;

   Empleado reg;
   int pos = 0, result = -1;
   while (fread(&reg, sizeof(Empleado), 1, pFile)) {
      if (reg.getLegajo() == legajo && !reg.getEliminado()) {
         result = pos;
         break;
      }
      pos++;
   }
   fclose(pFile);
   return result;
}
