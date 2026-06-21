#include <iostream>
#include "consultaMenu.h"
using namespace std;

ConsultaMenu::ConsultaMenu() {
   setCantidadOpciones(8);
}

void ConsultaMenu::mostrarOpciones() {
   cout << "=== MENU CONSULTAS Y LISTADOS ===" << endl;
   cout << "1. Listado de clientes (por apellido)" << endl;
   cout << "2. Listado de empleados (por apellido)" << endl;
   cout << "3. Listado de equipos (por fecha de ingreso)" << endl;
   cout << "4. Listado de reparaciones (por fecha de entrega)" << endl;
   cout << "5. Consulta de cliente por CUIT" << endl;
   cout << "6. Consulta de equipos por cliente" << endl;
   cout << "7. Consulta de reparaciones por cliente" << endl;
   cout << "8. Consulta de reparaciones por rango de fechas" << endl;
   cout << "0. Volver al menu principal" << endl;
}

void ConsultaMenu::ejecutarOpcion(int opcion) {
   switch (opcion) {
      case 1: _mgrCliente.listadoPorApellido(); break;
      case 2: _mgrEmpleado.listadoPorApellido(); break;
      case 3: _mgrEquipo.listadoPorFechaIngreso(); break;
      case 4: _mgrReparacion.listadoPorFechaEntrega(); break;
      case 5: _mgrConsulta.consultaClientePorCuit(); break;
      case 6: _mgrConsulta.consultaEquiposPorCliente(); break;
      case 7: _mgrConsulta.consultaReparacionesPorCliente(); break;
      case 8: _mgrConsulta.consultaReparacionesPorRangoFechas(); break;
      case 0: return;
   }
   pausar();
}
