#include <iostream>
#include <iomanip>
#include "empleadoManager.h"
#include "reparacionManager.h"
#include "utils.h"
using namespace std;

EmpleadoManager::EmpleadoManager() : _repo() {}

void EmpleadoManager::cargarInicialesSiVacio()
{
    if (_repo.getCantidadRegistros() != 0) return;

    _repo.crear(Empleado("101", "Agustin Nahuel", "Parada"));
    _repo.crear(Empleado("102", "Luz", "Campagnale"));
    _repo.crear(Empleado("103", "Enzo Gabriel", "Sander"));
    _repo.crear(Empleado("104", "Claudio Andres", "Arce"));
}


void EmpleadoManager::cargarCamposEditables(Empleado &e)
{
    e.setNombre(cargarTexto("Nombre: ", 19));
    e.setApellido(cargarTexto("Apellido: ", 19));
}

Empleado EmpleadoManager::cargarDatos(bool &cancelado)
{
    Empleado e;
    string legajo;
    bool legajoValido = false;
    cancelado = false;

    do
    {
        legajo = cargarTexto("Legajo (o '0' para cancelar): ", 9);

        if (legajo == "0")
        {
            cancelado = true;
            return e;
        }

        int pos = _repo.buscarPorLegajo(legajo);

        if (pos == -1)
        {
            legajoValido = true;
        }
        else
        {
            //verificacion legajo borrado
            Empleado empExistente = _repo.leer(pos);

            if (empExistente.getEliminado())
            {
                cout << "\n > AVISO: Este Legajo pertenece a un empleado dado de baja." << endl;
                int reactivar = cargarEntero("¨Desea RESTAURAR y reactivar a este empleado ahora? (1=Si, 0=No): ");

                if (reactivar == 1)
                {
                    empExistente.setEliminado(false);
                    if (_repo.actualizar(pos, empExistente))
                    {
                        cout << " >> Empleado restaurado con exito. Proceda a actualizar sus datos." << endl;
                        e = empExistente;
                        legajoValido = true;
                    }
                    else
                    {
                        cout << " > ERROR: No se pudo actualizar el archivo." << endl;
                    }
                }
                else
                {
                    cout << "Debe ingresar un Legajo diferente o presionar '0' para salir.\n" << endl;
                }
            }
            else
            {
                cout << " > ERROR: El Legajo ya pertenece a un empleado ACTIVO." << endl;
            }
        }
    }
    while (!legajoValido);

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
    system("cls");
    cout << "\n=== ALTA DE EMPLEADO ===" << endl<<endl;

    bool cancelado = false;
    Empleado e = cargarDatos(cancelado);

    if (cancelado)
    {
        cout << "\n>> Alta de empleado cancelada por el usuario." << endl;
        system("pause");
        return;
    }

    int pos = _repo.buscarPorLegajo(e.getLegajo());
    bool exito = false;

    if (pos != -1)
    {
        //empleado restaurado
        exito = _repo.actualizar(pos, e);
    }
    else
    {
        //empleado nuevo
        e.setEliminado(false);
        exito = _repo.crear(e);
    }

    if (exito) cout << "\n>>> EXITO: Empleado registrado correctamente." << endl;
    else cout << "\n > ERROR: No se pudo escribir en el archivo." << endl;

    system("pause");
}


void EmpleadoManager::baja()
{
    system("cls");
    cout << "=== BAJA DE EMPLEADO ===" << endl<<endl;

    string legajo = seleccionarEmpleado();
    if (legajo == "0") return;

    int pos = _repo.buscarPorLegajo(legajo);
    if (pos == -1)
    {
        cout << "\n > ERROR: El empleado con legajo " << legajo << " no existe en el sistema." << endl;
        system("pause");
        return;
    }

    Empleado emp = _repo.leer(pos);

    if (emp.getEliminado())
    {
        cout << "\n > ERROR: El empleado ya se encuentra dado de baja." << endl;
        system("pause");
        return;
    }

    if (empleadoTieneTareasPendientes(legajo))
    {
        cout << " > ERROR: No se puede dar de baja." << endl;
        cout << "   El empleado tiene reparaciones activas (Sin iniciar o En proceso)." << endl;
        system("pause");
        return;
    }

    system("cls");
    cout << "=== CONFIRMACION DE BAJA ===" << endl<<endl;
    mostrar(emp);
    cout << "--------------------------------------------------" << endl;

    int confirmar = cargarEntero("¨Confirma la baja de este empleado? (1=Si, 0=No): ");
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
    string legajo = seleccionarEmpleado();
    if (legajo == "0") return;

    int pos = _repo.buscarPorLegajo(legajo);
    if (pos == -1) return;

    Empleado e = _repo.leer(pos);


    if (e.getEliminado())
    {
        cout << "\n > ERROR: El empleado seleccionado se encuentra dado de baja." << endl;
        cout << "   Por motivos de auditoria, los datos de ex-empleados no pueden ser modificados." << endl;
        system("pause");
        return;
    }

    int opcion;
    do
    {
        system("cls");
        cout << "=== MODIFICAR EMPLEADO: " << e.getNombre() << " " << e.getApellido() << " ===" << endl;
        mostrar(e);
        cout << "--------------------------------------------------" << endl;
        cout << "1. Modificar Nombre" << endl;
        cout << "2. Modificar Apellido" << endl;
        cout << "0. Volver al menu anterior" << endl;

        opcion = cargarEntero("\nSeleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            e.setNombre(cargarTexto("Nuevo nombre: ", 19));
            break;
        case 2:
            e.setApellido(cargarTexto("Nuevo apellido: ", 19));
            break;
        case 0:
            break;
        default:
            cout << "Opcion incorrecta." << endl;
            system("pause");
        }

        if (opcion == 1 || opcion == 2)
        {
            if (_repo.actualizar(pos, e)) cout << " >> Datos actualizados." << endl;
            system("pause");
        }
    }
    while (opcion != 0);
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

string EmpleadoManager::seleccionarEmpleado()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== SELECCIONAR EMPLEADO ===" << endl<<endl;
        cout << "1. Ingresar Legajo del empleado" << endl;
        cout << "2. Listar todos los empleados activos" << endl;
        cout << "0. Cancelar" << endl;
        opcion = cargarEntero("\nSeleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            return cargarTexto("Ingrese el Legajo: ", 9);

        case 2:
        {
            listado();
            string legajo = cargarTexto("\nIngrese el Legajo seleccionado (o '0' para cancelar): ", 9);
            if (legajo == "0") break;

            int pos = _repo.buscarPorLegajo(legajo);
            if (pos != -1 && !_repo.leer(pos).getEliminado())
            {
                return legajo;
            }
            cout << " > Legajo invalido o empleado no encontrado." << endl;
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

void EmpleadoManager::menuConsultas()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== CONSULTAS Y LISTADOS: EMPLEADOS ===" << endl << endl;
        cout << "1. Listado ordenado por Apellido" << endl;
        cout << "2. Consulta individual por Legajo" << endl;
        cout << "3. Ver informe de carga de trabajo (Resumen + Detalles)" << endl;
        cout << "4. Historial de reparaciones finalizadas por Tecnico" << endl;
        cout << "5. Ver historial de empleados inactivos (Bajas)" << endl;
        cout << "0. Volver al menu anterior" << endl;

        opcion = cargarEntero("\nSeleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            system("cls");
            listadoPorApellido();
            system("pause");
            break;
        case 2:
            system("cls");
            consultaPorLegajo();
            system("pause");
            break;
        case 3:
            system("cls");
            informeCargaTrabajo();
            system("pause");
            break;
        case 4:
            system("cls");
            historialReparacionesFinalizadas();
            system("pause");
            break;
        case 5:
            system("cls");
            listadoInactivos();
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << " > Opcion incorrecta." << endl;
            system("pause");
        }
    } while (opcion != 0);
}

void EmpleadoManager::listadoPorApellido()
{
    cout << "\n=== LISTADO DE EMPLEADOS (ORDENADO POR APELLIDO) ===" << endl<<endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    Empleado *v = new Empleado[cantidad];
    if (v == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria para ordenar el listado." << endl;
        return;
    }
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
            //mostrar(v[i]);
            cout << "Empleado: " << v[i].getApellido() << " " << v[i].getNombre() << endl;
            cout << "Legajo: " << v[i].getLegajo() << endl;
            cout << "-----------------------------------" << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay empleados activos." << endl;

    delete[] v;
}

void EmpleadoManager::consultaPorLegajo()
{
    cout << "=== CONSULTA DE EMPLEADO POR LEGAJO ===" << endl << endl;
    string legajo = cargarTexto("Ingrese el Legajo a consultar: ", 9);

    int pos = _repo.buscarPorLegajo(legajo);
    if (pos == -1)
    {
        cout << "\n > El Legajo ingresado no corresponde a ningun empleado." << endl;
        return;
    }

    Empleado e = _repo.leer(pos);
    cout << "\n--- DATOS DEL REGISTRO ---" << endl;
    mostrar(e);
    if (e.getEliminado())
    {
        cout << "ESTADO: [INACTIVO / DADO DE BAJA]" << endl;
    }
    else
    {
        cout << "ESTADO: [ACTIVO]" << endl;
    }
}

void EmpleadoManager::informeCargaTrabajo()
{
    cout << "=== INFORME OPERATIVO: CARGA DE TRABAJO DE TECNICOS ===" << endl << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    cout << left << setw(12) << "LEGAJO"
         << left << setw(35) << "NOMBRE COMPLETO"
         << right << setw(18) << "TAREAS PENDIENTES" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    bool hayTecnicos = false;
    for (int i = 0; i < cantidad; i++)
    {
        Empleado e = _repo.leer(i);
        if (!e.getEliminado())
        {
            string nombreCompleto = e.getNombre() + " " + e.getApellido();
            int tareas = contarTareasPendientes(e.getLegajo());

            cout << left << setw(12) << e.getLegajo()
                 << left << setw(30) << nombreCompleto
                 << right << setw(10) << tareas << " orden(es)" << endl;
            hayTecnicos = true;
        }
    }
    cout << "----------------------------------------------------------------------" << endl;
    if (!hayTecnicos) {
        cout << "No hay tecnicos activos registrados." << endl;
        return;
    }

    int verDetalle = cargarEntero("\n¨Desea ver el detalle de tareas de un tecnico en particular? (1=Si, 0=No): ");
    if (verDetalle == 1)
    {
        string legajo = cargarTexto("\nIngrese el legajo del tecnico: ", 9);
        int pos = _repo.buscarPorLegajo(legajo);
        if (pos == -1 || _repo.leer(pos).getEliminado())
        {
            cout << " > ERROR: El legajo no corresponde a un empleado activo." << endl;
            return;
        }

        system("cls");
        Empleado emp = _repo.leer(pos);
        cout << "=== TAREAS PENDIENTES: " << emp.getNombre() << " " << emp.getApellido() << " (Legajo: " << legajo << ") ===" << endl << endl;

        ReparacionArchivo repoRep;
        int cantRep = repoRep.getCantidadRegistros();
        bool hayTareas = false;

        for (int i = 0; i < cantRep; i++)
        {
            Reparacion r = repoRep.leer(i);
            if (!r.getEliminado() && r.getLegajo() == legajo && (r.getEstado() == 1 || r.getEstado() == 2))
            {
                cout << "  [*] Orden #" << r.getNroReparacion()
                     << " | Ingreso: " << r.getFechaIngreso().toString()
                     << " | Estado: " << (r.getEstado() == 1 ? "Sin iniciar" : "En proceso") << endl;
                hayTareas = true;
            }
        }
        if (!hayTareas) cout << "  (Este tecnico no registra tareas pendientes en el taller actualmente)" << endl;
    }
}

void EmpleadoManager::listadoInactivos()
{
    cout << "=== HISTORIAL DE EMPLEADOS DADOS DE BAJA ===" << endl << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay registros en el archivo." << endl;
        return;
    }

    bool hayInactivos = false;
    for (int i = 0; i < cantidad; i++)
    {
        Empleado e = _repo.leer(i);
        if (e.getEliminado())
        {
            mostrar(e);
            hayInactivos = true;
        }
    }
    if (!hayInactivos) cout << "No se encontraron empleados inactivos en el sistema." << endl;
}

void EmpleadoManager::historialReparacionesFinalizadas()
{
    cout << "=== HISTORIAL DE REPARACIONES FINALIZADAS POR TECNICO ===" << endl << endl;
    string legajo = cargarTexto("Ingrese el legajo del tecnico: ", 9);

    int pos = _repo.buscarPorLegajo(legajo);
    if (pos == -1 || _repo.leer(pos).getEliminado())
    {
        cout << " > ERROR: El legajo no corresponde a un empleado activo." << endl;
        return;
    }

    Empleado emp = _repo.leer(pos);

    Fecha desde, hasta;
    bool rangoValido = false;
    do {
        desde = cargarFecha("Fecha desde (F. Entrega):");
        if (!desde.esValida()) {
            cout << " > ERROR: La fecha 'Desde' es invalida." << endl;
            continue;
        }

        hasta = cargarFecha("Fecha hasta (F. Entrega):");
        if (!hasta.esValida()) {
            cout << " > ERROR: La fecha 'Hasta' es invalida." << endl;
            continue;
        }

        if (hasta.aNumero() < desde.aNumero()) {
            cout << " > ERROR LOGICO: La fecha 'Hasta' no puede ser anterior a la fecha 'Desde'.\n" << endl;
        } else {
            rangoValido = true;
        }
    } while (!rangoValido);

    system("cls");
    cout << "=== TRABAJOS ENTREGADOS POR: " << emp.getNombre() << " " << emp.getApellido() << " ===" << endl;
    cout << "Periodo analizado: " << desde.toString() << " hasta " << hasta.toString() << endl;
    cout << "----------------------------------------------------------------------" << endl;

    ReparacionArchivo repoRep;
    int cant = repoRep.getCantidadRegistros();
    bool hayRegistros = false;

    for (int i = 0; i < cant; i++)
    {
        Reparacion r = repoRep.leer(i);
        long f = r.getFechaEntrega().aNumero();

        //filtros
        if (!r.getEliminado() && r.getLegajo() == legajo && r.getEstado() == 3 && f >= desde.aNumero() && f <= hasta.aNumero())
        {
            cout << "  [v] Orden #" << r.getNroReparacion()
                 << " | Entregado el: " << r.getFechaEntrega().toString() << endl;
            hayRegistros = true;
        }
    }

    if (!hayRegistros)
    {
        cout << "No se encontraron ordenes terminadas para este tecnico en el periodo indicado." << endl;
    }
    cout << "----------------------------------------------------------------------" << endl;
}
