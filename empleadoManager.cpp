#include <iostream>
#include "empleadoManager.h"
#include "utils.h"
using namespace std;

EmpleadoManager::EmpleadoManager() : _repo() {}

void EmpleadoManager::cargarInicialesSiVacio() {
   if (_repo.getCantidadRegistros() != 0) return;

   _repo.crear(Empleado("23971", "Agustin Nahuel", "Parada"));
   _repo.crear(Empleado("28047", "Luz", "Campagnale"));
   _repo.crear(Empleado("32335", "Enzo Gabriel", "Sander"));
   _repo.crear(Empleado("31950", "Claudio Andres", "Arce"));
}

bool EmpleadoManager::legajoUnico(const string &legajo) {
   return _repo.buscarPorLegajo(legajo) == -1;
}

void EmpleadoManager::cargarCamposEditables(Empleado &e) {
   e.setNombre(cargarTexto("Nombre: ", 19));
   e.setApellido(cargarTexto("Apellido: ", 19));
}

Empleado EmpleadoManager::cargarDatos() {
   Empleado e;
   string legajo;

   do {
      legajo = cargarTexto("Legajo: ", 9);
      if (!legajoUnico(legajo)) cout << " > El legajo ya existe." << endl;
   } while (!legajoUnico(legajo));
   e.setLegajo(legajo);

   cargarCamposEditables(e);
   return e;
}

void EmpleadoManager::mostrar(const Empleado &e) {
   cout << "Legajo: " << e.getLegajo() << endl;
   cout << "Nombre: " << e.getNombre() << " " << e.getApellido() << endl;
   cout << "-----------------------------------" << endl;
}

void EmpleadoManager::alta() {
   cout << "\n=== ALTA DE EMPLEADO ===" << endl;
   Empleado e = cargarDatos();
   if (_repo.crear(e)) cout << "\nEmpleado guardado exitosamente." << endl;
   else cout << "\nError al guardar el empleado." << endl;
}

void EmpleadoManager::baja() {
   cout << "\n=== BAJA DE EMPLEADO ===" << endl;
   string legajo = cargarCadena("Ingrese legajo del empleado a dar de baja: ");

   int pos = _repo.buscarPorLegajo(legajo);
   if (pos == -1) {
      cout << "\nEmpleado no encontrado o ya esta eliminado." << endl;
      return;
   }

   Empleado e = _repo.leer(pos);
   e.setEliminado(true);
   if (_repo.actualizar(pos, e)) cout << "\nEmpleado dado de baja exitosamente." << endl;
   else cout << "\nError al dar de baja el empleado." << endl;
}

void EmpleadoManager::modificacion() {
   cout << "\n=== MODIFICACION DE EMPLEADO ===" << endl;
   string legajo = cargarCadena("Ingrese legajo del empleado a modificar: ");

   int pos = _repo.buscarPorLegajo(legajo);
   if (pos == -1) {
      cout << "\nEmpleado no encontrado o esta eliminado." << endl;
      return;
   }

   Empleado e = _repo.leer(pos);
   cout << "\nEmpleado actual:" << endl;
   mostrar(e);

   cout << "\nIngrese los nuevos datos:" << endl;
   cargarCamposEditables(e);

   if (_repo.actualizar(pos, e)) cout << "\nEmpleado modificado exitosamente." << endl;
   else cout << "\nError al modificar el empleado." << endl;
}

void EmpleadoManager::listado() {
   cout << "\n=== LISTADO DE EMPLEADOS ===" << endl;
   int cantidad = _repo.getCantidadRegistros();
   if (cantidad == 0) {
      cout << "No hay empleados registrados." << endl;
      return;
   }

   bool hay = false;
   for (int i = 0; i < cantidad; i++) {
      Empleado e = _repo.leer(i);
      if (!e.getEliminado()) {
         mostrar(e);
         hay = true;
      }
   }
   if (!hay) cout << "No hay empleados activos." << endl;
}

void EmpleadoManager::listadoPorApellido() {
   cout << "\n=== LISTADO DE EMPLEADOS (ORDENADO POR APELLIDO) ===" << endl;
   int cantidad = _repo.getCantidadRegistros();
   if (cantidad == 0) {
      cout << "No hay empleados registrados." << endl;
      return;
   }

   Empleado *v = new Empleado[cantidad];
   _repo.leerTodos(v, cantidad);

   for (int i = 0; i < cantidad - 1; i++) {
      int min = i;
      for (int j = i + 1; j < cantidad; j++) {
         if (v[j].getApellido() < v[min].getApellido()) min = j;
      }
      if (min != i) {
         Empleado tmp = v[i];
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
   if (!hay) cout << "No hay empleados activos." << endl;

   delete[] v;
}
