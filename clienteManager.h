#pragma once
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

private:
    void listado();
    void listadoPorApellido();
    void listadoInactivos();
    void consultaPorCuit();
    Cliente cargarDatos(bool &cancelado);
    void cargarCamposEditables(Cliente &c);
    void mostrar(const Cliente &c);
    bool cuitUnico(const std::string &cuit);
    std::string seleccionarCliente();
    void mostrarReparacionesActivasPorCliente(const std::string& cuit);
    void mostrarParqueEquiposPorCliente(const std::string& cuit);

    ClienteArchivo _repo;
    ReparacionArchivo _repoReparacion;
    DetalleReparacionArchivo _repoDetalle;
    EquipoArchivo _repoEquipo;
};
