#include <cstdio>
#include "clienteArchivo.h"
using namespace std;

ClienteArchivo::ClienteArchivo(string nombreArchivo)
   : _nombreArchivo(nombreArchivo) {}

bool ClienteArchivo::crear(const Cliente &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "ab");
   if (pFile == nullptr) return false;

   bool result = fwrite(&reg, sizeof(Cliente), 1, pFile);
   fclose(pFile);
   return result;
}

bool ClienteArchivo::actualizar(int pos, const Cliente &reg) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb+");
   if (pFile == nullptr) return false;

   fseek(pFile, pos * sizeof(Cliente), SEEK_SET);
   bool result = fwrite(&reg, sizeof(Cliente), 1, pFile);
   fclose(pFile);
   return result;
}

Cliente ClienteArchivo::leer(int pos) {
   Cliente reg;
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return reg;

   fseek(pFile, pos * sizeof(Cliente), SEEK_SET);
   fread(&reg, sizeof(Cliente), 1, pFile);
   fclose(pFile);
   return reg;
}

int ClienteArchivo::leerTodos(Cliente vClientes[], int cantidad) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   int result = fread(vClientes, sizeof(Cliente), cantidad, pFile);
   fclose(pFile);
   return result;
}

int ClienteArchivo::getCantidadRegistros() {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return 0;

   fseek(pFile, 0, SEEK_END);
   int cant = ftell(pFile) / sizeof(Cliente);
   fclose(pFile);
   return cant;
}

int ClienteArchivo::buscarPorCuit(const string &cuit) {
   FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
   if (pFile == nullptr) return -1;

   Cliente reg;
   int pos = 0, result = -1;
   while (fread(&reg, sizeof(Cliente), 1, pFile)) {
      if (reg.getCuit() == cuit && !reg.getEliminado()) {
         result = pos;
         break;
      }
      pos++;
   }
   fclose(pFile);
   return result;
}
