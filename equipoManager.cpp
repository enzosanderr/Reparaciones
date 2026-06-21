#include <iostream>
#include "equipoManager.h"
#include "utils.h"
#include "clienteManager.h"

using namespace std;

EquipoManager::EquipoManager() : _repo(), _repoCliente() {}

bool EquipoManager::nroEquipoUnico(int nro)
{
    return _repo.buscarPorNumero(nro) == -1;
}

bool EquipoManager::clienteExiste(const string &cuit)
{
    return _repoCliente.buscarPorCuit(cuit) != -1;
}

bool EquipoManager::cargarCamposEditables(Equipo &e)
{
    string cuit;
    bool existe = false;
    ClienteManager mgrCliente;

    do
    {
        cuit = cargarTexto("CUIT del cliente propietario (o '0' para volver): ", 14);
        if (cuit == "0") {
            return false;
        }

        existe = clienteExiste(cuit);

        if (!existe)
        {
            cout << "\n > El cliente con CUIT " << cuit << " no esta registrado en el sistema." << endl;
            int opcion = cargarEntero("¨Desea dar de alta un NUEVO cliente ahora mismo? (1=Si, 0=No): ");

            if (opcion == 1)
            {
                mgrCliente.alta();
                cout << "\nPor favor, reingrese el CUIT del cliente recien creado para verificarlo." << endl;
            }
            else
            {
                cout << "Debe ingresar un CUIT valido o presionar '0' para cancelar la operacion.\n" << endl;
            }
        }
    }
    while (!existe);

    e.setCuit(cuit);

    e.setDescripcion(cargarTexto("Descripcion del Equipo: ", 49));
    e.setMarca(cargarTexto("Marca y modelo: ", 29));

    int tipo;
    do
    {
        tipo = cargarEntero("Tipo (1=PC escritorio, 2=Notebook, 3=Impresora, 4=Periferico, 5=Celular): ");
        if (tipo < 1 || tipo > 5) cout << " > Solo 1 a 5." << endl;
    }
    while (tipo < 1 || tipo > 5);
    e.setTipoEquipo(tipo);

    //fecha con validaciones

    Fecha fe;
    Fecha fechaActual;
    fechaActual.setFechaActual();
    bool fechaValida = false;

    do
    {
        fe = cargarFecha("Fecha de ingreso del equipo al taller:");

        if (!fe.esValida())
        {
            cout << " > ERROR: La fecha ingresada es invalida a nivel calendario." << endl;
        }
        //validacion fecha futura
        else if (fe.aNumero() > fechaActual.aNumero())
        {
            cout << " > ERROR LOGICO: La fecha de ingreso no puede ser en el futuro." << endl;
            cout << "   La fecha del sistema de hoy es: " << fechaActual.toString() << endl;
        }
        else
        {
            fechaValida = true;
        }
    }
    while (!fechaValida);

    e.setFechaIngreso(fe);

    return true;
}

void EquipoManager::mostrar(const Equipo &e)
{
    cout << "Numero: " << e.getNroEquipo() << endl;

    int posC = _repoCliente.buscarPorCuit(e.getCuit());
    if (posC != -1)
    {
        Cliente c = _repoCliente.leer(posC);
        cout << "Cliente: " << e.getCuit() << " - " << c.getNombre() << " " << c.getApellido() << endl;
    }
    else
    {
        cout << "Cliente: " << e.getCuit() << " (no encontrado)" << endl;
    }

    cout << "Descripcion: " << e.getDescripcion() << endl;
    cout << "Marca y modelo: " << e.getMarca() << endl;
    cout << "Tipo: " << e.getTipoEquipoString() << endl;
    cout << "Fecha de ingreso: " << e.getFechaIngreso().toString() << endl;
    cout << "-----------------------------------" << endl;
}

void EquipoManager::alta()
{
    system("cls");
    cout << "\n=== ALTA DE NUEVO EQUIPO ===" << endl;

    Equipo e;

    int nuevoId = _repo.getNuevoId();
    e.setNroEquipo(nuevoId);

    cout << "Numero de equipo asignado automaticamente: #" << nuevoId << endl << endl;

    if (!cargarCamposEditables(e))
    {
        cout << "\n>> Alta de equipo cancelada por el usuario." << endl;
        return;
    }

    e.setEliminado(false);

    if (_repo.crear(e))
    {
        cout << "\n>> EXITO: Equipo #" << nuevoId << " registrado correctamente." << endl;
    }
    else
    {
        cout << "\n>> ERROR: No se pudo guardar el equipo en el disco." << endl;
    }
    system("pause");
}



void EquipoManager::baja()
{
    cout << "\n=== BAJA DE EQUIPO ===" << endl;
    int nro = cargarEntero("Ingrese numero de equipo a dar de baja: ");

    int pos = _repo.buscarPorNumero(nro);
    if (pos == -1)
    {
        cout << "\nEquipo no encontrado o ya esta eliminado." << endl;
        return;
    }

    Equipo e = _repo.leer(pos);
    e.setEliminado(true);
    if (_repo.actualizar(pos, e)) cout << "\nEquipo dado de baja exitosamente." << endl;
    else cout << "\nError al dar de baja el equipo." << endl;
}

void EquipoManager::modificacion()
{
    cout << "\n=== MODIFICACION DE EQUIPO ===" << endl;
    int nro = cargarEntero("Ingrese numero de equipo a modificar: ");

    int pos = _repo.buscarPorNumero(nro);
    if (pos == -1)
    {
        cout << "\nEquipo no encontrado o esta eliminado." << endl;
        return;
    }

    Equipo e = _repo.leer(pos);
    cout << "\nEquipo actual:" << endl;
    mostrar(e);

    cout << "\nIngrese los nuevos datos:" << endl;
    cargarCamposEditables(e);

    if (_repo.actualizar(pos, e)) cout << "\nEquipo modificado exitosamente." << endl;
    else cout << "\nError al modificar el equipo." << endl;
}

void EquipoManager::listado()
{
    cout << "\n=== LISTADO DE EQUIPOS ===" << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay equipos registrados." << endl;
        return;
    }

    bool hay = false;
    for (int i = 0; i < cantidad; i++)
    {
        Equipo e = _repo.leer(i);
        if (!e.getEliminado())
        {
            mostrar(e);
            hay = true;
        }
    }
    if (!hay) cout << "No hay equipos activos." << endl;
}

void EquipoManager::listadoPorFechaIngreso()
{
    cout << "\n=== LISTADO DE EQUIPOS (ORDENADO POR FECHA DE INGRESO) ===" << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay equipos registrados." << endl;
        return;
    }

    Equipo *v = new Equipo[cantidad];
    _repo.leerTodos(v, cantidad);

    for (int i = 0; i < cantidad - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < cantidad; j++)
        {
            if (v[j].getFechaIngreso().aNumero() < v[min].getFechaIngreso().aNumero()) min = j;
        }
        if (min != i)
        {
            Equipo tmp = v[i];
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
    if (!hay) cout << "No hay equipos activos." << endl;

    delete[] v;
}
