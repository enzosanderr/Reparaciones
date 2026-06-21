#pragma once
#include <string>
#include "cliente.h"

class ClienteArchivo {
public:
   ClienteArchivo(std::string nombreArchivo = "clientes.dat");

   bool crear(const Cliente &reg);
   bool actualizar(int pos, const Cliente &reg);

   Cliente leer(int pos);
   int leerTodos(Cliente vClientes[], int cantidad);

   int getCantidadRegistros();
   int buscarPorCuit(const std::string &cuit);

private:
   std::string _nombreArchivo;
};
