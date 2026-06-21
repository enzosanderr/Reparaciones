#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include "configuracionManager.h"
#include "utils.h"

//portabilidad
#ifdef _WIN32
    #include <direct.h>  //Para Windows
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h> // Para Linux / macOS
    #define MKDIR(dir) mkdir(dir, 0777)
#endif

using namespace std;

ConfiguracionManager::ConfiguracionManager()
   : _repoCliente(), _repoEquipo(), _repoEmpleado(),
     _repoReparacion(), _repoDetalle() {}

void ConfiguracionManager::asegurarCarpeta(const string &nombre) {
    MKDIR(nombre.c_str());
}

bool ConfiguracionManager::copiarArchivo(const string &origen, const string &destino) {
   FILE *src = fopen(origen.c_str(), "rb");
   if (src == nullptr) return false;

   FILE *dst = fopen(destino.c_str(), "wb");
   if (dst == nullptr) {
      fclose(src);
      return false;
   }

   char buffer[4096];
   size_t leidos;
   while ((leidos = fread(buffer, 1, sizeof(buffer), src)) > 0) {
      fwrite(buffer, 1, leidos, dst);
   }

   fclose(src);
   fclose(dst);
   return true;
}

string ConfiguracionManager::rutaBackup(const string &nombreDat) {
   string base = nombreDat;
   size_t p = base.rfind(".dat");
   if (p != string::npos) base = base.substr(0, p);
   return "backups/" + base + ".bkp";
}

int ConfiguracionManager::generarCodigoConfirmacion(const string &nombre) {
   int codigo = 10000;
   for (size_t i = 0; i < nombre.size(); i++) {
      codigo += (int)nombre[i] * (int)(i + 1);
   }
   return codigo % 90000 + 10000;
}

void ConfiguracionManager::backupArchivo(const string &nombreDat) {
   asegurarCarpeta("backups");
   string destino = rutaBackup(nombreDat);

   if (copiarArchivo(nombreDat, destino)) {
      cout << "Backup OK: " << nombreDat << " -> " << destino << endl;
   } else {
      cout << "ERROR al hacer backup de: " << nombreDat << endl;
   }
}

void ConfiguracionManager::backupTodos() {
   cout << "\nRealizando backup de todos los archivos..." << endl;
   backupArchivo("clientes.dat");
   backupArchivo("equipos.dat");
   backupArchivo("empleados.dat");
   backupArchivo("reparaciones.dat");
   backupArchivo("detalleReparaciones.dat");
   cout << "Backup completo." << endl;
}

void ConfiguracionManager::restaurarArchivo(const string &nombreDat) {
   string origen = rutaBackup(nombreDat);

   FILE *test = fopen(origen.c_str(), "rb");
   if (test == nullptr) {
      cout << "No existe backup para: " << nombreDat << " (" << origen << ")" << endl;
      return;
   }
   fclose(test);

   int esperado = generarCodigoConfirmacion(nombreDat);
   cout << "\nATENCION: Restaurar SOBREESCRIBIRA " << nombreDat << "." << endl;
   int ingresado = cargarEntero("Para continuar ingrese el codigo " + to_string(esperado) + ": ");

   if (ingresado != esperado) {
      cout << "Codigo incorrecto. Restauracion cancelada." << endl;
      return;
   }

   if (copiarArchivo(origen, nombreDat)) {
      cout << "Restauracion OK: " << origen << " -> " << nombreDat << endl;
   } else {
      cout << "ERROR al restaurar." << endl;
   }
}

void ConfiguracionManager::restaurarTodos() {
   int esperado = generarCodigoConfirmacion("TODOS");
   cout << "\nATENCION: Restaurar TODO sobreescribira los archivos .dat actuales." << endl;
   int ingresado = cargarEntero("Para continuar ingrese el codigo " + to_string(esperado) + ": ");

   if (ingresado != esperado) {
      cout << "Codigo incorrecto. Restauracion cancelada." << endl;
      return;
   }

   const string archivos[] = {"clientes.dat", "equipos.dat", "empleados.dat",
                              "reparaciones.dat", "detalleReparaciones.dat"};

   //validacion de existencia de backups
   for (int i = 0; i < 5; i++) {
      string origen = rutaBackup(archivos[i]);
      FILE *test = fopen(origen.c_str(), "rb");
      if (test == nullptr) {
         cout << "ERROR CRITICO: Falta el archivo de respaldo: " << archivos[i] << endl;
         cout << "Restauracion abortada para proteger la integridad de los datos actuales." << endl;
         return;
      }
      fclose(test);
   }

  //restauracion
   for (int i = 0; i < 5; i++) {
      string origen = rutaBackup(archivos[i]);
      if (copiarArchivo(origen, archivos[i])) {
         cout << "Restauracion OK: " << archivos[i] << endl;
      } else {
         cout << "ERROR critico al sobreescribir de: " << archivos[i] << endl;
      }
   }
   cout << "Restauracion completa." << endl;
}


void ConfiguracionManager::exportarClientesCSV() {
   asegurarCarpeta("exports");
   ofstream csv("exports/clientes.csv");
   if (!csv) {
      cout << "ERROR al crear exports/clientes.csv" << endl;
      return;
   }

   csv << "cuit;nombre;apellido;telefono;email;direccion;tipoCliente" << endl;
   int cant = _repoCliente.getCantidadRegistros();
   int exportados = 0;
   for (int i = 0; i < cant; i++) {
      Cliente c = _repoCliente.leer(i);
      if (c.getEliminado()) continue;
      csv << c.getCuit() << ";" << c.getNombre() << ";" << c.getApellido() << ";"
          << c.getTelefono() << ";" << c.getEmail() << ";" << c.getDireccion() << ";"
          << c.getTipoClienteString() << endl;
      exportados++;
   }
   cout << "Exportados " << exportados << " clientes a exports/clientes.csv" << endl;
}

void ConfiguracionManager::exportarEquiposCSV() {
   asegurarCarpeta("exports");
   ofstream csv("exports/equipos.csv");
   if (!csv) {
      cout << "ERROR al crear exports/equipos.csv" << endl;
      return;
   }

   csv << "nroEquipo;cuitCliente;descripcion;marca;tipoEquipo;fechaIngreso" << endl;
   int cant = _repoEquipo.getCantidadRegistros();
   int exportados = 0;
   for (int i = 0; i < cant; i++) {
      Equipo e = _repoEquipo.leer(i);
      if (e.getEliminado()) continue;
      csv << e.getNroEquipo() << ";" << e.getCuit() << ";" << e.getDescripcion() << ";"
          << e.getMarca() << ";" << e.getTipoEquipoString() << ";"
          << e.getFechaIngreso().toString() << endl;
      exportados++;
   }
   cout << "Exportados " << exportados << " equipos a exports/equipos.csv" << endl;
}

void ConfiguracionManager::exportarEmpleadosCSV() {
   asegurarCarpeta("exports");
   ofstream csv("exports/empleados.csv");
   if (!csv) {
      cout << "ERROR al crear exports/empleados.csv" << endl;
      return;
   }

   csv << "legajo;nombre;apellido" << endl;
   int cant = _repoEmpleado.getCantidadRegistros();
   int exportados = 0;
   for (int i = 0; i < cant; i++) {
      Empleado e = _repoEmpleado.leer(i);
      if (e.getEliminado()) continue;
      csv << e.getLegajo() << ";" << e.getNombre() << ";" << e.getApellido() << endl;
      exportados++;
   }
   cout << "Exportados " << exportados << " empleados a exports/empleados.csv" << endl;
}


void ConfiguracionManager::exportarReparacionesCSV() {
   asegurarCarpeta("exports");
   ofstream csv("exports/reparaciones.csv");
   if (!csv) {
      cout << "ERROR al crear exports/reparaciones.csv" << endl;
      return;
   }

   int cant = _repoReparacion.getCantidadRegistros();
   int cantD = _repoDetalle.getCantidadRegistros();

   DetalleReparacion* vDetalles = new DetalleReparacion[cantD];
   if (vDetalles == nullptr) {
       cout << "ERROR: Sin memoria RAM para optimizar la exportacion de reparaciones." << endl;
       return;
   }

   _repoDetalle.leerTodos(vDetalles, cantD);

   csv << "nroReparacion;cuitCliente;legajoEmpleado;fechaEntrega;cantidadEquipos;importeTotal" << endl;
   int exportados = 0;
   for (int i = 0; i < cant; i++) {
      Reparacion r = _repoReparacion.leer(i);
      if (r.getEliminado()) continue;

      int cantEquipos = 0;
      float total = 0;


      for (int j = 0; j < cantD; j++) {
         DetalleReparacion d = vDetalles[j];
         if (d.getNroReparacion() == r.getNroReparacion() && !d.getEliminado()) {
            cantEquipos++;
            total += d.getImporte();
         }
      }

      csv << r.getNroReparacion() << ";" << r.getCuit() << ";" << r.getLegajo() << ";"
          << r.getFechaEntrega().toString() << ";" << cantEquipos << ";"
          << fixed << setprecision(2) << total << endl;
      exportados++;
   }

   delete[] vDetalles;
   cout << "Exportadas " << exportados << " reparaciones a exports/reparaciones.csv" << endl;
}

void ConfiguracionManager::exportarDetalleReparacionesCSV() {
   asegurarCarpeta("exports");
   ofstream csv("exports/detalleReparaciones.csv");
   if (!csv) {
      cout << "ERROR al crear exports/detalleReparaciones.csv" << endl;
      return;
   }

   csv << "nroReparacion;nroEquipo;importe" << endl;
   int cant = _repoDetalle.getCantidadRegistros();
   int exportados = 0;
   for (int i = 0; i < cant; i++) {
      DetalleReparacion d = _repoDetalle.leer(i);
      if (d.getEliminado()) continue;
      csv << d.getNroReparacion() << ";" << d.getNroEquipo() << ";"
          << fixed << setprecision(2) << d.getImporte() << endl;
      exportados++;
   }
   cout << "Exportados " << exportados << " detalles a exports/detalleReparaciones.csv" << endl;
}


void ConfiguracionManager::exportarTodosCSV() {
   cout << "\nExportando todos los archivos a CSV..." << endl;
   exportarClientesCSV();
   exportarEquiposCSV();
   exportarEmpleadosCSV();
   exportarReparacionesCSV();
   exportarDetalleReparacionesCSV();
   cout << "Exportacion completa." << endl;
}
