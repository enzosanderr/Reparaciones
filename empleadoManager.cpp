#include <iostream>
#include "empleadoManager.h"
#include "reparacionManager.h"
#include "utils.h"
using namespace std;

EmpleadoManager::EmpleadoManager() : _repo() {}

void EmpleadoManager::cargarInicialesSiVacio()
{
    if (_repo.getCantidadRegistros() != 0) return;

    _repo.crear(Empleado("123", "Agustin Nahuel", "Parada"));
    _repo.crear(Empleado("1234", "Luz", "Campagnale"));
    _repo.crear(Empleado("12345", "Enzo Gabriel", "Sander"));
    _repo.crear(Empleado("123456", "Claudio Andres", "Arce"));
}

bool EmpleadoManager::legajoUnico(const string &legajo)
{
    return _repo.buscarPorLegajo(legajo) == -1;
}

void EmpleadoManager::cargarCamposEditables(Empleado &e)
{
    e.setNombre(cargarTexto("Nombre: ", 19));
    e.setApellido(cargarTexto("Apellido: ", 19));
}

Empleado EmpleadoManager::cargarDatos()
{
    Empleado e;
    string legajo;

    do
    {
        legajo = cargarTexto("Legajo: ", 9);
        if (!legajoUnico(legajo)) cout << " > El legajo ya existe." << endl;
    }
    while (!legajoUnico(legajo));
    e.setLegajo(legajo);

    cargarCamposEditables(e);
    return e;
}

void EmpleadoManager::mostrar(const Empleado &e)
{
    cout << "Legajo: " << e.getLegajo() << endl;
    cout << "Nombre: " << e.getNombre() << " " << e.getApellido() << endl;
    cout << "-----------------------------------" << endl;
}

void EmpleadoManager::alta()
{
    cout << "\n=== ALTA DE EMPLEADO ===" << endl;
    Empleado e = cargarDatos();
    if (_repo.crear(e)) cout << "\nEmpleado guardado exitosamente." << endl;
    else cout << "\nError al guardar el empleado." << endl;
}


void EmpleadoManager::baja()
{
    system("cls");
    cout << "=== BAJA DE EMPLEADO ===" << endl;

    string legajo = cargarTexto("Ingrese el legajo del empleado (o '0' para cancelar): ", 9);
    if (legajo == "0") return;

    int pos = _repo.buscarPorLegajo(legajo);
    if (pos == -1)
    {
        cout << " > ERROR: El empleado con legajo " << legajo << " no existe." << endl;
        system("pause");
        return;
    }

    Empleado emp = _repo.leer(pos);

    if (emp.getEliminado())
    {
        cout << " > El empleado ya se encuentra dado de baja." << endl;
        system("pause");
        return;
    }

    //verificacion de reparaciones activas
    if (empleadoTieneTareasPendientes(legajo))
    {
        cout << " > ERROR: No se puede dar de baja." << endl;
        cout << "   El empleado tiene reparaciones activas (Sin iniciar o En proceso)." << endl;
        system("pause");
        return;
    }

    // confirmacion
    system("cls");
    cout << "=== CONFIRMACION DE BAJA ===" << endl;
    mostrar(emp);
    cout << "--------------------------------------------------" << endl;

    int confirmar = cargarEntero("¨Confirma la baja logica de este empleado? (1=Si, 0=No): ");
    if (confirmar != 1)
    {
        cout << " >> Operacion cancelada." << endl;
        system("pause");
        return;
    }

    emp.setEliminado(true);
    if (_repo.actualizar(pos, emp))
    {
        cout << "\n>>> EXITO: Empleado dado de baja correctamente." << endl;
    }
    else
    {
        cout << "\n > ERROR: No se pudo actualizar el archivo en disco." << endl;
    }
    system("pause");
}


void EmpleadoManager::modificacion()
{
    cout << "\n=== MODIFICACION DE EMPLEADO ===" << endl;
    string legajo = cargarCadena("Ingrese legajo del empleado a modificar: ");

    int pos = _repo.buscarPorLegajo(legajo);
    if (pos == -1)
    {
        cout << "\nEmpleado no encontrado o esta eliminado." << endl;
        return;
    }

    Empleado e = _repo.leer(pos);
    cout << "\nEmpleado actual:" << endl;
    mostrar(e);

    cout << "\nIngrese los nuevos datos:" << endl;
    cargarCamposEditables(e);

    if (_repo.actualizar(pos, e)) cout << "\nEmpleado modificado exitosamente." << endl;
    else cout << "\nError al modificar el empleado." << endl;
}

void EmpleadoManager::listado()
{
    cout << "\n=== LISTADO DE EMPLEADOS ===" << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    bool hay = false;
    for (int i = 0; i < cantidad; i++)
    {
        Empleado e = _repo.leer(i);
        if (!e.getEliminado())
        {
            mostrar(e);
            hay = true;
        }
    }
    if (!hay) cout << "No hay empleados activos." << endl;
}

void EmpleadoManager::listadoPorApellido()
{
    cout << "\n=== LISTADO DE EMPLEADOS (ORDENADO POR APELLIDO) ===" << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    Empleado *v = new Empleado[cantidad];
    _repo.leerTodos(v, cantidad);

    for (int i = 0; i < cantidad - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < cantidad; j++)
        {
            if (v[j].getApellido() < v[min].getApellido()) min = j;
        }
        if (min != i)
        {
            Empleado tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }

    bool hay = false;
    for (int i = 0; i < cantidad; i++)
    {
        if (!v[i].getEliminado())
        {
            mostrar(v[i]);
            hay = true;
        }
    }
    if (!hay) cout << "No hay empleados activos." << endl;

    delete[] v;
}


bool EmpleadoManager::empleadoTieneTareasPendientes(const string &legajo)
{
    ReparacionArchivo repoRep;
    int cant = repoRep.getCantidadRegistros();

    for (int i = 0; i < cant; i++)
    {
        Reparacion r = repoRep.leer(i);

        if (!r.getEliminado() && r.getLegajo() == legajo)
        {
            if (r.getEstado() == 1 || r.getEstado() == 2)
            {
                return true;
            }
        }
    }
    return false; //empleado libre
}

int EmpleadoManager::contarTareasPendientes(const std::string &legajo)
{
    ReparacionArchivo repoRep;
    int cant = repoRep.getCantidadRegistros();
    int contador = 0;

    for (int i = 0; i < cant; i++)
    {
        Reparacion r = repoRep.leer(i);
        if (!r.getEliminado() && r.getLegajo() == legajo && (r.getEstado() == 1 || r.getEstado() == 2))
        {
            contador++;
        }
    }
    return contador;
}
