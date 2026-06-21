#pragma once
#include <string>
#include "empleadoArchivo.h"
#include "reparacionArchivo.h"

class EmpleadoManager {
public:
    EmpleadoManager();

    void cargarInicialesSiVacio();
    void alta();
    void baja();
    void modificacion();
    void menuConsultas();

    bool empleadoTieneTareasPendientes(const std::string &legajo);
    int contarTareasPendientes(const std::string &legajo);

private:
    void listado();
    void listadoPorApellido();
    void listadoInactivos();
    void consultaPorLegajo();
    void informeCargaTrabajo();
    void historialReparacionesFinalizadas();

    Empleado cargarDatos(bool &cancelado);
    void cargarCamposEditables(Empleado &e);
    void mostrar(const Empleado &e);
    std::string seleccionarEmpleado();

    EmpleadoArchivo _repo;
};
