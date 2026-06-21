#include <iostream>
#include "clienteManager.h"
#include "reparacionManager.h"
#include "equipoArchivo.h"
#include "utils.h"
using namespace std;

ClienteManager::ClienteManager() : _repo() {}

bool ClienteManager::cuitUnico(const string &cuit)
{
    return _repo.buscarPorCuit(cuit) == -1;
}

void ClienteManager::cargarCamposEditables(Cliente &c)
{
    c.setNombre(cargarTexto("Nombre: ", 19));
    c.setApellido(cargarTexto("Apellido: ", 19));
    c.setTelefono(cargarTexto("Telefono: ", 19));

    string email;
    do
    {
        email = cargarTexto("Email: ", 39);
        if (email.find('@') == string::npos) cout << " > El email debe contener @." << endl;
    }
    while (email.find('@') == string::npos);
    c.setEmail(email);

    c.setDireccion(cargarTexto("Direccion: ", 49));

    int tipo;
    do
    {
        tipo = cargarEntero("Tipo de cliente (1=Particular, 2=Empresa): ");
        if (tipo != 1 && tipo != 2) cout << " > Solo 1 o 2." << endl;
    }
    while (tipo != 1 && tipo != 2);
    c.setTipoCliente(tipo);
}

Cliente ClienteManager::cargarDatos()
{
    Cliente c;
    string cuit;

    do
    {
        cuit = cargarTexto("CUIT: ", 14);
        if (!cuitUnico(cuit)) cout << " > El CUIT ya existe." << endl;
    }
    while (!cuitUnico(cuit));
    c.setCuit(cuit);

    cargarCamposEditables(c);
    return c;
}

void ClienteManager::mostrar(const Cliente &c)
{
    cout << "CUIT: " << c.getCuit() << endl;
    cout << "Nombre: " << c.getNombre() << " " << c.getApellido() << endl;
    cout << "Telefono: " << c.getTelefono() << endl;
    cout << "Email: " << c.getEmail() << endl;
    cout << "Direccion: " << c.getDireccion() << endl;
    cout << "Tipo: " << c.getTipoClienteString() << endl;
    cout << "-----------------------------------" << endl;
}

void ClienteManager::alta()
{
    cout << "\n=== ALTA DE CLIENTE ===" << endl;
    Cliente c = cargarDatos();
    if (_repo.crear(c)) cout << "\nCliente guardado exitosamente." << endl;
    else cout << "\nError al guardar el cliente." << endl;
}

void ClienteManager::baja()
{
    system("cls");
    cout << "=== BAJA DE CLIENTE ===" << endl;

    string cuit = seleccionarCliente();
    if (cuit == "0") return;

    int pos = _repo.buscarPorCuit(cuit);
    if (pos == -1)
    {
        cout << "\n > ERROR: El cliente con CUIT " << cuit << " no existe en el sistema." << endl;
        system("pause");
        return;
    }

    Cliente c = _repo.leer(pos);
    if (c.getEliminado())
    {
        cout << "\n > ERROR: El cliente con CUIT " << cuit << " ya se encuentra dado de baja." << endl;
        system("pause");
        return;
    }

    //verificacion reparaciones activas
    ReparacionArchivo repoRep;
    int cantReparaciones = repoRep.getCantidadRegistros();

    for (int i = 0; i < cantReparaciones; i++)
    {
        Reparacion r = repoRep.leer(i);
        if (!r.getEliminado() && r.getCuit() == cuit)
        {
            if (r.getEstado() == 1 || r.getEstado() == 2)
            {
                cout << " > ERROR: No se puede eliminar el cliente." << endl;
                cout << "   Tiene la Reparacion #" << r.getNroReparacion() << " activa en el taller." << endl;
                system("pause");
                return;
            }
        }
    }

    //confirmacion
    system("cls");
    cout << "=== CONFIRMACION DE BAJA ===" << endl;
    mostrar(c);
    cout << "-----------------------------------------------------------------------------" << endl;

    EquipoArchivo repoEq;
    int cantEquipos = repoEq.getCantidadRegistros();
    int equiposAfectados = 0;

    for (int i = 0; i < cantEquipos; i++)
    {
        Equipo eq = repoEq.leer(i);
        if (!eq.getEliminado() && eq.getCuit() == cuit)
        {
            if (equiposAfectados == 0)
            {
                cout << "ADVERTENCIA: Se daran de baja los siguientes equipos asociados al cliente:" << endl;
            }
            cout << "  - Equipo #" << eq.getNroEquipo() << " | " << eq.getTipoEquipoString()
                 << " (" << eq.getMarca() << ")" << endl;
            equiposAfectados++;
        }
    }

    if (equiposAfectados == 0)
    {
        cout << "(El cliente no tiene equipos asociados en este momento)." << endl;
    }
    else
    {
        cout << "\nATENCION: La baja de este cliente provocara la eliminacion de "
             << equiposAfectados << " equipo(s)." << endl;
    }
    cout << "-----------------------------------------------------------------------------" << endl;


    int confirmar = cargarEntero("¨Confirma la baja de este cliente? (1=Si, 0=No): ");
    if (confirmar != 1)
    {
        cout << " >> Operacion cancelada." << endl;
        system("pause");
        return;
    }

    //baja
    c.setEliminado(true);
    if (!_repo.actualizar(pos, c))
    {
        cout << "\n > ERROR: No se pudo guardar la baja en el disco." << endl;
        system("pause");
        return;
    }

    //baja de equipos asociados
    int equiposBorrados = 0;
    int erroresBorrando = 0;

    for (int i = 0; i < cantEquipos; i++)
    {
        Equipo eq = repoEq.leer(i);
        if (!eq.getEliminado() && eq.getCuit() == cuit)
        {
            eq.setEliminado(true);

            if (repoEq.actualizar(i, eq))
            {
                equiposBorrados++;
            }
            else
            {
                erroresBorrando++;
            }
        }
    }

    cout << "\n>>> EXITO: Cliente CUIT " << cuit << " dado de baja." << endl;
    if (equiposBorrados > 0)
    {
        cout << "    Se eliminaron " << equiposBorrados << " equipo(s) asociado(s)." << endl;
    }
    if (erroresBorrando > 0)
    {
        cout << "    ADVERTENCIA: Hubo fallos al eliminar " << erroresBorrando << " equipo(s)." << endl;
    }

    system("pause");

}



void ClienteManager::modificacion()
{
    string cuit = seleccionarCliente();
    if (cuit == "0") return;

    int pos = _repo.buscarPorCuit(cuit);
    Cliente c = _repo.leer(pos);

    int opcion;
    do
    {
        system("cls");
        cout << "=== MODIFICAR CLIENTE: " << c.getNombre() << " " << c.getApellido() << " ===" << endl;
        mostrar(c);
        cout << "--------------------------------------------------" << endl;
        cout << "1. Modificar Nombre" << endl;
        cout << "2. Modificar Apellido" << endl;
        cout << "3. Modificar Telefono" << endl;
        cout << "0. Volver al menu anterior" << endl;

        opcion = cargarEntero("\nSeleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            c.setNombre(cargarTexto("Nuevo nombre: ", 29));
            break;
        case 2:
            c.setApellido(cargarTexto("Nuevo apellido: ", 29));
            break;
        case 3:
            c.setTelefono(cargarTexto("Nuevo telefono: ", 19));
            break;
        case 0:
            break;
        default:
            cout << "Opcion incorrecta." << endl;
        }

        if (opcion >= 1 && opcion <= 3)
        {
            if (_repo.actualizar(pos, c)) cout << " >> Datos actualizados." << endl;
            system("pause");
        }
    }
    while (opcion != 0);
}

void ClienteManager::listado()
{
    cout << "\n=== LISTADO DE CLIENTES ===" << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    bool hay = false;
    for (int i = 0; i < cantidad; i++)
    {
        Cliente c = _repo.leer(i);
        if (!c.getEliminado())
        {
            mostrar(c);
            hay = true;
        }
    }
    if (!hay) cout << "No hay clientes activos." << endl;
}

void ClienteManager::listadoPorApellido()
{
    cout << "\n=== LISTADO DE CLIENTES (ORDENADO POR APELLIDO) ===" << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    Cliente *v = new Cliente[cantidad];
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
            Cliente tmp = v[i];
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
    if (!hay) cout << "No hay clientes activos." << endl;

    delete[] v;
}

string ClienteManager::seleccionarCliente()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== SELECCIONAR CLIENTE ===" << endl<<endl;
        cout << "1. Ingresar CUIT del cliente" << endl;
        cout << "2. Listar todos los clientes activos" << endl;
        cout << "0. Cancelar" << endl;
        opcion = cargarEntero("\nSeleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            return cargarTexto("Ingrese el CUIT del cliente: ", 14);

        case 2:
        {
            listado();
            string cuit = cargarTexto("\nIngrese el CUIT del cliente seleccionado (o '0' para cancelar): ", 14);
            if (cuit == "0") break;

            if (_repo.buscarPorCuit(cuit) != -1 && !_repo.leer(_repo.buscarPorCuit(cuit)).getEliminado())
            {
                return cuit;
            }
            cout << " > CUIT invalido o cliente no encontrado." << endl;
            system("pause");
            break;
        }
        case 0:
            return "0";
        default:
            cout << " > Opcion incorrecta." << endl;
            system("pause");
        }
    }
    while (opcion != 0);

    return "0";
}

