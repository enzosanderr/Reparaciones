#pragma once
#include "clienteArchivo.h"

class ClienteManager {
public:
   ClienteManager();

   void alta();
   void baja();
   void modificacion();
   void listado();
   void listadoPorApellido();

private:
   Cliente cargarDatos();
   void cargarCamposEditables(Cliente &c);
   void mostrar(const Cliente &c);
   bool cuitUnico(const std::string &cuit);

   ClienteArchivo _repo;
};
