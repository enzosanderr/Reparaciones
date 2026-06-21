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
    void listado();
    void listadoPorFechaEntrega();

    void mostrar(const Reparacion &r);
    float calcularTotal(int nroReparacion);

private:
    int contarEquiposDeReparacion(int nroReparacion);
    void mostrarEquiposDeCliente(const std::string &cuit);
    int cargarDetalles(int nroReparacion, const std::string &cuit);
    float pedirImporte();
    void agregarDetalle(int nroReparacion, int nroEquipo, float importe);
    bool detalleYaCargado(int nroReparacion, int nroEquipo);
    bool equipoPerteneceACliente(int nroEquipo, const std::string &cuit);
    void modificarDetalles(const Reparacion &r);
    std::string getNombreEstado(int estado);
    void listarPorEstado();
    int seleccionarReparacion();
    int buscarPorId();
    int buscarPorCuit();
    int seleccionarDeUltimasDiez();
    bool equipoTieneReparacionAbierta(int nroEquipo);
    void limpiarDetallesHuerfanos(int nroReparacion);

    ReparacionArchivo _repo;
    DetalleReparacionArchivo _repoDetalle;
    ClienteArchivo _repoCliente;
    EmpleadoArchivo _repoEmpleado;
    EquipoArchivo _repoEquipo;
};
