#pragma once
#include "clienteArchivo.h"

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

    ClienteArchivo _repo;
};
