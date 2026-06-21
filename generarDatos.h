#pragma once
#include "clienteArchivo.h"
#include "empleadoArchivo.h"
#include "equipoArchivo.h"
#include "reparacionArchivo.h"
#include "detalleReparacionArchivo.h"

class GeneradorDatos
{
public:
    GeneradorDatos();

    // M‚todo principal que ejecutaremos desde el main
    void sembrarTodo();

private:
    // M‚todos de limpieza y carga divididos para mantener el orden
    void limpiarArchivos();
    void sembrarClientes();
    void sembrarEmpleados();
    void sembrarEquipos();
    void sembrarReparacionesYDetalles();

    ClienteArchivo _repoCliente;
    EmpleadoArchivo _repoEmpleado;
    EquipoArchivo _repoEquipo;
    ReparacionArchivo _repoReparacion;
    DetalleReparacionArchivo _repoDetalle;
};
