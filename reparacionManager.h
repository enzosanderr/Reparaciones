#pragma once
#include <string>
#include "reparacionArchivo.h"
#include "detalleReparacionArchivo.h"
#include "clienteArchivo.h"
#include "empleadoArchivo.h"
#include "equipoArchivo.h"

class ReparacionManager
{
public:
    ReparacionManager();

    void alta();
    void baja();
    void modificacion();
    void menuConsultas();

    void mostrar(const Reparacion &r);
    float calcularTotal(int nroReparacion);
    bool equipoTieneReparacionAbierta(int nroEquipo);

private:
    void listado();
    void listadoPorFechaEntrega();
    void consultaPorId();
    void consultaPorCliente();
    void consultaPorNumeroEquipo();
    void consultaPorRangoFechas();
    void listadoInactivos();

    int contarEquiposDeReparacion(int nroReparacion);
    void mostrarEquiposDeCliente(const std::string &cuit);
    int cargarDetalles(int nroReparacion, const std::string &cuit);
    float pedirImporte();
    void agregarDetalle(int nroReparacion, int nroEquipo, float importe, const char* falla);
    bool detalleYaCargado(int nroReparacion, int nroEquipo);
    bool equipoPerteneceACliente(int nroEquipo, const std::string &cuit);
    void modificarDetalles(const Reparacion &r);
    std::string getNombreEstado(int estado);
    int seleccionarReparacion(int filtroEstado = 0);
    int buscarPorCuit(int filtroEstado = 0);
    std::string asignarTecnico();

    ReparacionArchivo _repo;
    DetalleReparacionArchivo _repoDetalle;
    ClienteArchivo _repoCliente;
    EmpleadoArchivo _repoEmpleado;
    EquipoArchivo _repoEquipo;
};
