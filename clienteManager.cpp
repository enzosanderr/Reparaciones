#include <iostream>
#include "clienteManager.h"
#include "utils.h"
using namespace std;

ClienteManager::ClienteManager() : _repo() {}

bool ClienteManager::cuitUnico(const string &cuit) {
   return _repo.buscarPorCuit(cuit) == -1;
}

void ClienteManager::cargarCamposEditables(Cliente &c) {
   c.setNombre(cargarTexto("Nombre: ", 19));
   c.setApellido(cargarTexto("Apellido: ", 19));
   c.setTelefono(cargarTexto("Telefono: ", 19));

   string email;
   do {
      email = cargarTexto("Email: ", 39);
      if (email.find('@') == string::npos) cout << " > El email debe contener @." << endl;
   } while (email.find('@') == string::npos);
   c.setEmail(email);

   c.setDireccion(cargarTexto("Direccion: ", 49));

   int tipo;
   do {
      tipo = cargarEntero("Tipo de cliente (1=Particular, 2=Empresa): ");
      if (tipo != 1 && tipo != 2) cout << " > Solo 1 o 2." << endl;
   } while (tipo != 1 && tipo != 2);
   c.setTipoCliente(tipo);
}

Cliente ClienteManager::cargarDatos() {
   Cliente c;
   string cuit;

   do {
      cuit = cargarTexto("CUIT: ", 14);
      if (!cuitUnico(cuit)) cout << " > El CUIT ya existe." << endl;
   } while (!cuitUnico(cuit));
   c.setCuit(cuit);

   cargarCamposEditables(c);
   return c;
}

void ClienteManager::mostrar(const Cliente &c) {
   cout << "CUIT: " << c.getCuit() << endl;
   cout << "Nombre: " << c.getNombre() << " " << c.getApellido() << endl;
   cout << "Telefono: " << c.getTelefono() << endl;
   cout << "Email: " << c.getEmail() << endl;
   cout << "Direccion: " << c.getDireccion() << endl;
   cout << "Tipo: " << c.getTipoClienteString() << endl;
   cout << "-----------------------------------" << endl;
}

void ClienteManager::alta() {
   cout << "\n=== ALTA DE CLIENTE ===" << endl;
   Cliente c = cargarDatos();
   if (_repo.crear(c)) cout << "\nCliente guardado exitosamente." << endl;
   else cout << "\nError al guardar el cliente." << endl;
}

void ClienteManager::baja() {
   cout << "\n=== BAJA DE CLIENTE ===" << endl;
   string cuit = cargarCadena("Ingrese CUIT del cliente a dar de baja: ");

   int pos = _repo.buscarPorCuit(cuit);
   if (pos == -1) {
      cout << "\nCliente no encontrado o ya esta eliminado." << endl;
      return;
   }

   Cliente c = _repo.leer(pos);
   c.setEliminado(true);
   if (_repo.actualizar(pos, c)) cout << "\nCliente dado de baja exitosamente." << endl;
   else cout << "\nError al dar de baja el cliente." << endl;
}

void ClienteManager::modificacion() {
   cout << "\n=== MODIFICACION DE CLIENTE ===" << endl;
   string cuit = cargarCadena("Ingrese CUIT del cliente a modificar: ");

   int pos = _repo.buscarPorCuit(cuit);
   if (pos == -1) {
      cout << "\nCliente no encontrado o esta eliminado." << endl;
      return;
   }

   Cliente c = _repo.leer(pos);
   cout << "\nCliente actual:" << endl;
   mostrar(c);

   cout << "\nIngrese los nuevos datos:" << endl;
   cargarCamposEditables(c);

   if (_repo.actualizar(pos, c)) cout << "\nCliente modificado exitosamente." << endl;
   else cout << "\nError al modificar el cliente." << endl;
}

void ClienteManager::listado() {
   cout << "\n=== LISTADO DE CLIENTES ===" << endl;
   int cantidad = _repo.getCantidadRegistros();
   if (cantidad == 0) {
      cout << "No hay clientes registrados." << endl;
      return;
   }

   bool hay = false;
   for (int i = 0; i < cantidad; i++) {
      Cliente c = _repo.leer(i);
      if (!c.getEliminado()) {
         mostrar(c);
         hay = true;
      }
   }
   if (!hay) cout << "No hay clientes activos." << endl;
}

void ClienteManager::listadoPorApellido() {
   cout << "\n=== LISTADO DE CLIENTES (ORDENADO POR APELLIDO) ===" << endl;
   int cantidad = _repo.getCantidadRegistros();
   if (cantidad == 0) {
      cout << "No hay clientes registrados." << endl;
      return;
   }

   Cliente *v = new Cliente[cantidad];
   _repo.leerTodos(v, cantidad);

   for (int i = 0; i < cantidad - 1; i++) {
      int min = i;
      for (int j = i + 1; j < cantidad; j++) {
         if (v[j].getApellido() < v[min].getApellido()) min = j;
      }
      if (min != i) {
         Cliente tmp = v[i];
         v[i] = v[min];
         v[min] = tmp;
      }
   }

   bool hay = false;
   for (int i = 0; i < cantidad; i++) {
      if (!v[i].getEliminado()) {
         mostrar(v[i]);
         hay = true;
      }
   }
   if (!hay) cout << "No hay clientes activos." << endl;

   delete[] v;
}
