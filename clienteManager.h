#pragma once
#include <string>
#include "clienteArchivo.h"
#include "reparacionArchivo.h"
#include "detalleReparacionArchivo.h"
#include "equipoArchivo.h"

class ClienteManager
{
public:
    ClienteManager();

    void alta();
    void baja();
    void modificacion();
    void menuConsultas();
    void mostrar(const Cliente &c);

private:
    void cargarCamposEditables(Cliente &c);
    Cliente cargarDatos(bool &cancelado);

    void listado();
    void listadoPorApellido();
    void listadoPorTipo();
    void consultaPorCuit();
    void listadoInactivos();
    std::string seleccionarCliente();
    void mostrarReparacionesActivasPorCliente(const std::string& cuit);
    void mostrarParqueEquiposPorCliente(const std::string& cuit);

    ClienteArchivo _repo;
    ReparacionArchivo _repoReparacion;
    DetalleReparacionArchivo _repoDetalle;
    EquipoArchivo _repoEquipo;
};
