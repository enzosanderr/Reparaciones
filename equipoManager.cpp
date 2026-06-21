#include <iostream>
#include "equipoManager.h"
#include "utils.h"
#include "clienteManager.h"
#include "reparacionArchivo.h"
#include "detalleReparacionArchivo.h"

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
        if (cuit == "0")
        {
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
    system("cls");
    cout << "=== BAJA DE EQUIPO ===" << endl<<endl;

    int nroEquipo = seleccionarEquipo();
    if (nroEquipo <= 0) return;

    int pos = _repo.buscarPorNumero(nroEquipo);
    if (pos == -1)
    {
        cout << " > ERROR: El equipo #" << nroEquipo << " no se encontro en el sistema." << endl;
        system("pause");
        return;
    }

    Equipo e = _repo.leer(pos);

    if (e.getEliminado())
    {
        cout << " > El equipo ya se encuentra dado de baja." << endl;
        system("pause");
        return;
    }

    //verificacion equipo en taller
    if (equipoEnReparacionActiva(nroEquipo))
    {
        cout << " > ERROR: No se puede eliminar el equipo. Actualmente se encuentra en el taller" << endl;
        cout << "   asociado a una orden de reparacion abierta o en proceso." << endl;
        system("pause");
        return;
    }

    //confirmacion
    system("cls");
    cout << "=== CONFIRMACION DE BAJA ===" << endl;

    mostrar(e);
    cout << "--------------------------------------------------" << endl;

    int confirmar = cargarEntero("¨Confirma la baja de este equipo? (1=Si, 0=No): ");
    if (confirmar != 1)
    {
        cout << " >> Operacion cancelada." << endl;
        system("pause");
        return;
    }

    e.setEliminado(true);
    if (_repo.actualizar(pos, e))
    {
        cout << "\n>>> EXITO: Equipo #" << nroEquipo << " dado de baja correctamente." << endl;
    }
    else
    {
        cout << "\n > ERROR: No se pudo actualizar el registro en el disco." << endl;
    }
    system("pause");
}

void EquipoManager::modificacion()
{
    cout << "\n=== MODIFICACION DE EQUIPO ===" << endl;

    int nro = seleccionarEquipo();
    if (nro <= 0) return;

    int pos = _repo.buscarPorNumero(nro);
    if (pos == -1) return;

    Equipo e = _repo.leer(pos);

    int opcion;
    do
    {
        system("cls");
        cout << "=== MODIFICAR EQUIPO #" << e.getNroEquipo() << " ===" << endl;
        mostrar(e);
        cout << "--------------------------------------------------" << endl;
        cout << "1. Modificar CUIT Cliente" << endl;
        cout << "2. Modificar Descripcion" << endl;
        cout << "3. Modificar Marca y Modelo" << endl;
        cout << "4. Modificar Tipo de Equipo" << endl;
        cout << "5. Modificar Fecha de Ingreso" << endl;
        cout << "0. Volver al menu anterior" << endl;

        opcion = cargarEntero("\nSeleccione una opcion a modificar: ");

        switch (opcion)
        {
        case 1:
        {
            string nuevoCuit = cargarTexto("Ingrese el nuevo CUIT: ", 14);
            if (_repoCliente.buscarPorCuit(nuevoCuit) == -1)
            {
                cout << " > ERROR: El cliente no existe o esta dado de baja." << endl;
            }
            else
            {
                e.setCuit(nuevoCuit);
                if (_repo.actualizar(pos, e)) cout << " >> CUIT modificado exitosamente." << endl;
                else cout << " > ERROR: No se pudo actualizar en el disco." << endl;
            }
            system("pause");
            break;
        }
        case 2:
        {
            string nuevaDesc = cargarTexto("Nueva descripcion: ", 49);
            e.setDescripcion(nuevaDesc);
            if (_repo.actualizar(pos, e)) cout << " >> Descripcion modificada." << endl;
            system("pause");
            break;
        }
        case 3:
        {
            string nuevaMarca = cargarTexto("Nueva marca y modelo: ", 29);
            e.setMarca(nuevaMarca);
            if (_repo.actualizar(pos, e)) cout << " >> Marca modificada." << endl;
            system("pause");
            break;
        }
        case 4:
        {
            int nuevoTipo;
            do
            {
                nuevoTipo = cargarEntero("Nuevo Tipo (1=PC, 2=Notebook, 3=Impresora, 4=Periferico, 5=Celular): ");
                if(nuevoTipo < 1 || nuevoTipo > 5) cout << " > Solo 1 a 5." << endl;
            }
            while (nuevoTipo < 1 || nuevoTipo > 5);

            e.setTipoEquipo(nuevoTipo);
            if (_repo.actualizar(pos, e)) cout << " >> Tipo de equipo modificado." << endl;
            system("pause");
            break;
        }
        case 5:
        {
            Fecha nuevaFecha;
            Fecha hoy;
            hoy.setFechaActual();
            bool fechaOk = false;
            do
            {
                nuevaFecha = cargarFecha("Nueva fecha de ingreso:");
                if (!nuevaFecha.esValida()) cout << " > Fecha invalida." << endl;
                else if (nuevaFecha.aNumero() > hoy.aNumero()) cout << " > No puede ser fecha futura." << endl;
                else fechaOk = true;
            }
            while (!fechaOk);

            e.setFechaIngreso(nuevaFecha);
            if (_repo.actualizar(pos, e)) cout << " >> Fecha modificada." << endl;
            system("pause");
            break;
        }
        case 0:
            break;
        default:
            cout << " > Opcion incorrecta." << endl;
            system("pause");
            break;
        }
    }
    while (opcion != 0);
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

int EquipoManager::contarEquiposPorCuit(const string &cuit)
{
    int cant = _repo.getCantidadRegistros();
    int contador = 0;

    for (int i = 0; i < cant; i++)
    {
        Equipo eq = _repo.leer(i);
        if (!eq.getEliminado() && eq.getCuit() == cuit)
        {
            contador++;
        }
    }
    return contador;
}

int EquipoManager::seleccionarEquipo()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== SELECCIONAR EQUIPO ===" << endl<<endl;
        cout << "1. Ingresar ID de equipo directamente" << endl;
        cout << "2. Buscar por CUIT del Cliente" << endl;
        cout << "3. Listar todos los equipos activos" << endl;
        cout << "0. Cancelar" << endl<<endl;

        opcion = cargarEntero("\nSeleccione una opcion de busqueda: ");

        switch (opcion)
        {
        case 1:
        {
            int id = cargarEntero("Ingrese el ID del equipo: ");
            int pos = _repo.buscarPorNumero(id);
            if (pos != -1)
            {
                Equipo e = _repo.leer(pos);
                if(!e.getEliminado()) return id;
            }
            cout << " > El ID ingresado no corresponde a un equipo activo." << endl;
            system("pause");
            break;
        }
        case 2:
        {
            int idEncontrado = buscarPorCuit();
            if (idEncontrado > 0) return idEncontrado;
            break;
        }
        case 3:
        {
            listado();
            int id = cargarEntero("\nIngrese ID del equipo seleccionado (0 para cancelar): ");
            if (id == 0) break;

            int pos = _repo.buscarPorNumero(id);
            if (pos != -1 && !_repo.leer(pos).getEliminado()) return id;

            cout << " > ID invalido o equipo eliminado." << endl;
            system("pause");
            break;
        }
        case 0:
            return 0;
        default:
            cout << " > Opcion incorrecta." << endl;
            system("pause");
            break;
        }
    }
    while (opcion != 0);

    return 0;
}

bool EquipoManager::equipoEnReparacionActiva(int nroEquipo)
{
    DetalleReparacionArchivo repoDetalle;
    ReparacionArchivo repoRep;

    int cantDetalles = repoDetalle.getCantidadRegistros();

    for (int i = 0; i < cantDetalles; i++)
    {
        DetalleReparacion d = repoDetalle.leer(i);

        if (d.getNroEquipo() == nroEquipo && !d.getEliminado())
        {

            int posReparacion = repoRep.buscarPorNumero(d.getNroReparacion());

            if (posReparacion != -1)
            {
                Reparacion rep = repoRep.leer(posReparacion);

                if (rep.getEstado() == 1 || rep.getEstado() == 2)
                {
                    return true; //equipo en taller
                }
            }
        }
    }
    return false;
}

int EquipoManager::buscarPorCuit()
{
    string cuit;
    int opcion = 1;

    while (opcion == 1)
    {
        system("cls");
        cout << "=== BUSCAR EQUIPOS POR CUIT ===" << endl;
        cuit = cargarTexto("Ingrese el CUIT del cliente (o '0' para cancelar): ", 14);

        if (cuit == "0") return 0;

        int cantidad = _repo.getCantidadRegistros();
        int coincidencias = 0;
        int ultimoId = -1;

        system("cls");
        cout << "=== EQUIPOS ENCONTRADOS PARA EL CUIT: " << cuit << " ===" << endl;
        cout << "----------------------------------------------------------------------" << endl;

        //listado de coincidencias
        for (int i = 0; i < cantidad; i++)
        {
            Equipo e = _repo.leer(i);
            if (!e.getEliminado() && e.getCuit() == cuit)
            {
                cout << " ID: #" << e.getNroEquipo() << " | " << e.getTipoEquipoString()
                     << " - " << e.getMarca() << endl;
                coincidencias++;
                ultimoId = e.getNroEquipo();
            }
        }
        cout << "----------------------------------------------------------------------" << endl;

        //no hay equipos asignados a ese cuit
        if (coincidencias == 0)
        {
            cout << "\n > No se encontraron equipos activos para el CUIT: " << cuit << endl;
            cout << "1. Intentar con otro CUIT" << endl;
            cout << "0. Volver atras" << endl;
            opcion = cargarEntero("\nSeleccione una opcion: ");
            if (opcion == 0) return 0;
            continue;
        }

        //un solo equipo asociado
        if (coincidencias == 1)
        {
            cout << "\n> Se encontro un unico equipo. Seleccionando ID: #" << ultimoId << endl;
            system("pause");
            return ultimoId;
        }

        //varios equipos
        int idSeleccionado = cargarEntero("\nIngrese el ID del equipo que desea seleccionar (0 para cancelar): ");
        if (idSeleccionado == 0) return 0;

        int posValidar = _repo.buscarPorNumero(idSeleccionado);
        if (posValidar != -1)
        {
            Equipo eq = _repo.leer(posValidar);
            if (eq.getCuit() == cuit && !eq.getEliminado())
            {
                return idSeleccionado;
            }
        }

        cout << "\n > ERROR: El ID ingresado no corresponde a ninguna de las opciones listadas." << endl;
        system("pause");
    }

    return 0;
}

