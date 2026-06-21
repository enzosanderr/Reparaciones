#include <iostream>
#include "consultaManager.h"
#include "utils.h"
using namespace std;

ConsultaManager::ConsultaManager()
   : _mgrReparacion(), _repoCliente(), _repoEquipo(), _repoReparacion() {}

void ConsultaManager::consultaClientePorCuit() {
   cout << "\n=== CONSULTA DE CLIENTE POR CUIT ===" << endl;
   string cuit = cargarCadena("Ingrese CUIT: ");

   int pos = _repoCliente.buscarPorCuit(cuit);
   if (pos == -1) {
      cout << "No se encontro un cliente activo con ese CUIT." << endl;
      return;
   }

   Cliente c = _repoCliente.leer(pos);
   cout << "CUIT: " << c.getCuit() << endl;
   cout << "Nombre: " << c.getNombre() << " " << c.getApellido() << endl;
   cout << "Telefono: " << c.getTelefono() << endl;
   cout << "Email: " << c.getEmail() << endl;
   cout << "Direccion: " << c.getDireccion() << endl;
   cout << "Tipo: " << c.getTipoClienteString() << endl;

   cout << "\nEquipos del cliente:" << endl;
   int cant = _repoEquipo.getCantidadRegistros();
   bool hay = false;
   for (int i = 0; i < cant; i++) {
      Equipo e = _repoEquipo.leer(i);
      if (!e.getEliminado() && e.getCuit() == cuit) {
         cout << "  #" << e.getNroEquipo() << " - " << e.getTipoEquipoString()
              << " - " << e.getMarca() << " - " << e.getDescripcion() << endl;
         hay = true;
      }
   }
   if (!hay) cout << "  (sin equipos cargados)" << endl;
}

void ConsultaManager::consultaEquiposPorCliente() {
   cout << "\n=== CONSULTA DE EQUIPOS POR CLIENTE ===" << endl;
   string cuit = cargarCadena("Ingrese CUIT del cliente: ");

   if (_repoCliente.buscarPorCuit(cuit) == -1) {
      cout << "No existe un cliente activo con ese CUIT." << endl;
      return;
   }

   int cant = _repoEquipo.getCantidadRegistros();
   bool hay = false;
   for (int i = 0; i < cant; i++) {
      Equipo e = _repoEquipo.leer(i);
      if (!e.getEliminado() && e.getCuit() == cuit) {
         cout << "  #" << e.getNroEquipo() << " - " << e.getTipoEquipoString()
              << " - " << e.getMarca() << " - " << e.getDescripcion() << endl;
         hay = true;
      }
   }
   if (!hay) cout << "El cliente no tiene equipos activos." << endl;
}

void ConsultaManager::consultaReparacionesPorCliente() {
   cout << "\n=== CONSULTA DE REPARACIONES POR CLIENTE ===" << endl;
   string cuit = cargarCadena("Ingrese CUIT del cliente: ");

   if (_repoCliente.buscarPorCuit(cuit) == -1) {
      cout << "No existe un cliente activo con ese CUIT." << endl;
      return;
   }

   int cant = _repoReparacion.getCantidadRegistros();
   bool hay = false;
   float totalGeneral = 0;
   for (int i = 0; i < cant; i++) {
      Reparacion r = _repoReparacion.leer(i);
      if (!r.getEliminado() && r.getCuit() == cuit) {
         _mgrReparacion.mostrar(r);
         totalGeneral += _mgrReparacion.calcularTotal(r.getNroReparacion());
         hay = true;
      }
   }

   if (!hay) cout << "El cliente no tiene reparaciones activas." << endl;
   else cout << "\n>>> TOTAL ACUMULADO DEL CLIENTE: $" << totalGeneral << endl;
}

void ConsultaManager::consultaReparacionesPorRangoFechas() {

cout << "\n=== CONSULTA DE REPARACIONES POR RANGO DE FECHAS ===" << endl;

    Fecha desde, hasta;
    bool rangoValido = false;

    do {
        desde = cargarFecha("Fecha desde:");
        if (!desde.esValida()) {
            cout << " > ERROR: La fecha 'Desde' es invalida." << endl;
            continue;
        }

        hasta = cargarFecha("Fecha hasta:");
        if (!hasta.esValida()) {
            cout << " > ERROR: La fecha 'Hasta' es invalida." << endl;
            continue;
        }

        // Validaci¢n de Consistencia de Rango
        if (hasta.aNumero() < desde.aNumero()) {
            cout << " > ERROR LOGICO: La fecha 'Hasta' no puede ser anterior a la fecha 'Desde'." << endl;
            cout << "   Por favor, ingrese el rango nuevamente.\n" << endl;
        } else {
            rangoValido = true;
        }
    } while (!rangoValido);

   int cant = _repoReparacion.getCantidadRegistros();
   bool hay = false;
   float totalGeneral = 0;
   for (int i = 0; i < cant; i++) {
      Reparacion r = _repoReparacion.leer(i);
      long f = r.getFechaEntrega().aNumero();
      if (!r.getEliminado() && f >= desde.aNumero() && f <= hasta.aNumero()) {
         _mgrReparacion.mostrar(r);
         totalGeneral += _mgrReparacion.calcularTotal(r.getNroReparacion());
         hay = true;
      }
   }

   if (!hay) cout << "No hay reparaciones en el rango indicado." << endl;
   else cout << "\n>>> TOTAL DEL PERIODO: $" << totalGeneral << endl;
}
