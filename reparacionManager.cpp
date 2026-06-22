#include <iostream>
#include <iomanip>
#include "reparacionManager.h"
#include "utils.h"
#include "clienteManager.h"
#include "equipoManager.h"
#include "empleadoManager.h"
#include "menu.h"

using namespace std;

ReparacionManager::ReparacionManager()
    : _repo(), _repoDetalle(), _repoCliente(), _repoEmpleado(), _repoEquipo() {}

float ReparacionManager::calcularTotal(int nroReparacion)
{
    int cant = _repoDetalle.getCantidadRegistros();
    float total = 0;
    for (int i = 0; i < cant; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);
        if (d.getNroReparacion() == nroReparacion && !d.getEliminado())
        {
            total += d.getImporte();
        }
    }
    return total;
}

int ReparacionManager::contarEquiposDeReparacion(int nroReparacion)
{
    int cant = _repoDetalle.getCantidadRegistros();
    int cantidad = 0;
    for (int i = 0; i < cant; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);
        if (d.getNroReparacion() == nroReparacion && !d.getEliminado())
        {
            cantidad++;
        }
    }
    return cantidad;
}

void ReparacionManager::mostrarEquiposDeCliente(const string &cuit)
{
    int cant = _repoEquipo.getCantidadRegistros();
    int equiposDisponibles = 0;
    bool hay = false;

    cout << "\nEquipos del cliente " << cuit << ":" << endl;
    for (int i = 0; i < cant; i++)
    {
        Equipo e = _repoEquipo.leer(i);
        if (!e.getEliminado() && e.getCuit() == cuit)
        {
            hay = true;
            bool enReparacion = equipoTieneReparacionAbierta(e.getNroEquipo());

            cout << "  #" << e.getNroEquipo() << " - " << e.getTipoEquipoString()
                 << " - " << e.getMarca() << " - " << e.getDescripcion() << (enReparacion ? " [EN REPARACION]" : " [DISPONIBLE]") << endl;

            if (!enReparacion)
            {
                equiposDisponibles++;
            }
        }

    }
    if (!hay)
    {
        cout << "  (sin equipos cargados)" << endl;
    }
    else if (equiposDisponibles == 0)
    {
        cout << "\nATENCION: Todos los equipos de este cliente se encuentran actualmente en reparacion." << endl;
    }

}


float ReparacionManager::pedirImporte()
{
    float importe;
    do
    {
        importe = cargarFloat("Importe: ");
        if (importe <= 0) cout << " > El importe debe ser mayor a 0." << endl;
    }
    while (importe <= 0);
    return importe;
}

void ReparacionManager::agregarDetalle(int nroReparacion, int nroEquipo, float importe, const char* falla)
{
    DetalleReparacion d(nroReparacion, nroEquipo, importe,falla);
    _repoDetalle.crear(d);
}

bool ReparacionManager::detalleYaCargado(int nroReparacion, int nroEquipo)
{
    return _repoDetalle.buscarDetalle(nroReparacion, nroEquipo) != -1;
}

bool ReparacionManager::equipoPerteneceACliente(int nroEquipo, const string &cuit)
{
    int pos = _repoEquipo.buscarPorNumero(nroEquipo);
    if (pos == -1) return false;
    Equipo e = _repoEquipo.leer(pos);
    return e.getCuit() == cuit;
}

void ReparacionManager::mostrar(const Reparacion &r)
{
    cout << "Reparacion #" << r.getNroReparacion() << endl<<endl;


    int posC = _repoCliente.buscarPorCuit(r.getCuit());
    if (posC != -1)
    {
        Cliente c = _repoCliente.leer(posC);
        cout << "Cliente: " << r.getCuit() << " - " << c.getNombre() << " " << c.getApellido() << endl;
    }
    else
    {
        cout << "Cliente: " << r.getCuit() << " (no encontrado)" << endl;
    }


    int posE = _repoEmpleado.buscarPorLegajo(r.getLegajo());
    if (posE != -1)
    {
        Empleado e = _repoEmpleado.leer(posE);
        cout << "Atendio: " << r.getLegajo() << " - " << e.getNombre() << " " << e.getApellido() << endl;
    }
    else
    {
        cout << "Atendio: " << r.getLegajo() << " (no encontrado)" << endl;
    }

    cout << "Fecha de ingreso: " << r.getFechaIngreso().toString() << endl;
    cout << "Fecha de entrega: " << r.getFechaEntrega().toString() << endl;

    cout << "\nEstado actual:    " << getNombreEstado(r.getEstado()) << endl;

    cout << "\nEquipos reparados:" << endl;
    int cantD = _repoDetalle.getCantidadRegistros();
    float total = 0;
    bool hay = false;
    for (int i = 0; i < cantD; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);
        if (d.getNroReparacion() == r.getNroReparacion() && !d.getEliminado())
        {
            cout << "  - Equipo #" << d.getNroEquipo();
            int posEq = _repoEquipo.buscarPorNumero(d.getNroEquipo());
            if (posEq != -1)
            {
                Equipo eq = _repoEquipo.leer(posEq);
                cout << " (" << eq.getTipoEquipoString() << " - " << eq.getDescripcion() << ")";
            }
            cout << " - Importe: $" << d.getImporte() << endl;
            cout << "    Falla/Trabajo: " << d.getDetalleFalla() << endl << endl;

            total += d.getImporte();
            hay = true;
        }
    }
    if (!hay) cout << "  (sin equipos cargados)" << endl;
    cout << "\nTOTAL: $" << total << endl;
    //cout << "\n----------------------------------------------------------------------\n" << endl;
    cout << "\n======================================================================\n" << endl;
}

int ReparacionManager::cargarDetalles(int nroReparacion, const string &cuit)
{
    int cargados = 0;
    EquipoManager mgrEquipo;

    system("cls");
    cout << "\n=== CARGA DE EQUIPOS A REPARAR ===" << endl;

    int cantEquipos = mgrEquipo.contarEquiposPorCuit(cuit);

    if (cantEquipos == 0)
    {
        cout << "\n > AVISO: El cliente CUIT " << cuit << " no tiene equipos registrados." << endl;
        int opcion = cargarEntero("\nDesea registrar un NUEVO EQUIPO ahora mismo? (1=Si, 0=Cancelar): ");

        if (opcion == 1)
        {
            mgrEquipo.alta();

            if (mgrEquipo.contarEquiposPorCuit(cuit) == 0)
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }


    cout << "(Ingrese 0 como numero de equipo para finalizar)" << endl<<endl;

    while (true)
    {
        mostrarEquiposDeCliente(cuit);
        int nroEquipo = cargarEntero("\nNumero de equipo a reparar (0 para finalizar): ");


        if (nroEquipo == 0)
        {
            if (cargados == 0)
            {

                int confirmar = cargarEntero("No ha cargado equipos. ¨Desea CANCELAR la carga? (1=Si, 0=No): ");
                if (confirmar == 1) return -1;
                else continue;
            }
            break;
        }

        int posEquipo = _repoEquipo.buscarPorNumero(nroEquipo);


        if (posEquipo == -1)
        {
            cout << "\n > El equipo #" << nroEquipo << " no esta registrado en el sistema." << endl;
            int opcion = cargarEntero("\nDesea dar de alta un NUEVO equipo para este cliente ahora mismo? (1=Si, 0=No): ");
            if (opcion == 1)
            {
                mgrEquipo.alta();
                cout << "\nPor favor, vuelva a ingresar el numero del equipo reci‚n creado." << endl;
            }
            continue;
        }


        Equipo eq = _repoEquipo.leer(posEquipo);


        if (eq.getEliminado())
        {
            cout << " > ERROR: El equipo seleccionado se encuentra marcado como eliminado." << endl;
            continue;
        }



        //validacion de pertenencia
        if (eq.getCuit() != cuit)
        {
            cout << " > ERROR: Este equipo le pertenece al cliente CUIT " << eq.getCuit() << endl;
            cout << "   No se puede cargar en la orden del cliente actual." << endl;
            continue;
        }

        //validacion de estado
        if (equipoTieneReparacionAbierta(nroEquipo))
        {
            cout << " > ERROR: El equipo #" << nroEquipo << " ya se encuentra en el taller" << endl;
            cout << "   con una orden de reparacion abierta o en proceso actualmente." << endl;
            system("pause");
            continue;
        }

        //validacion equipo cargado repetido
        if (detalleYaCargado(nroReparacion, nroEquipo))
        {
            cout << " > ERROR: Este equipo ya fue asignado a esta misma orden de trabajo." << endl;
            continue;
        }


        float importe = pedirImporte();
        string falla = cargarTexto("Describa la falla o trabajo a realizar: ", 99);

        agregarDetalle(nroReparacion, nroEquipo, importe, falla.c_str());
        cargados++;
        cout << " >> Equipo #" << nroEquipo << " agregado correctamente al detalle." << endl<<endl;
        system("pause");
    }

    return cargados;
}

void ReparacionManager::alta()
{
    cout << "\n=== ALTA DE REPARACION ===" << endl;

    //empleados
    if (_repoEmpleado.getCantidadRegistros() == 0)
    {
        cout << " > ERROR CRITICO: No hay empleados registrados en el sistema." << endl;
        cout << "   Debe registrar al menos un tecnico antes de recibir reparaciones." << endl;
        return;
    }

    //cliente
    string cuit;
    int posCliente = -1;
    ClienteManager mgrCliente;


    while (posCliente == -1)
    {
        cuit = cargarTexto("CUIT del cliente (o '0' para cancelar): ", 14);
        if (cuit == "0")
        {
            cout << "\n>> Operacion cancelada por el usuario." << endl;
            return;
        }

        posCliente = _repoCliente.buscarPorCuit(cuit);

        if (posCliente == -1)
        {
            cout << "\n > El cliente con CUIT " << cuit << " no esta registrado en el sistema." << endl;
            int opcion = cargarEntero("Desea dar de alta un NUEVO cliente ahora mismo? (1=Si, 0=No): ");
            if (opcion == 1)
            {
                mgrCliente.alta();
                cout << "\nPor favor, reingrese el CUIT del cliente recien creado para verificarlo." << endl;
            }
            else
            {
                cout << "Debe ingresar un CUIT valido para continuar." << endl;
            }
        }
        else
        {

            Cliente c = _repoCliente.leer(posCliente);
            if (c.getEliminado())
            {
                cout << " > El cliente asociado a este CUIT se encuentra dado de baja logica." << endl;
                int opcion = cargarEntero("\n Desea restaurar (reactivar) a este cliente? (1=Si, 0=No): ");
                if (opcion == 1)
                {
                    c.setEliminado(false);
                    _repoCliente.actualizar(posCliente, c);
                    cout << " >> Cliente reactivado exitosamente." << endl;
                }
                else
                {
                    posCliente = -1;
                }
            }
        }
    }

    //empleado
    string legajo = asignarTecnico();

    if (legajo == "0")
    {
        cout << "\n>> Alta de reparacion cancelada por el usuario." << endl;
        system("pause");
        return;
    }


    int nro = _repo.getNuevoId();
    cout << "\nNumero de orden de reparacion asignado: " << nro << endl;

    //carga de detalles
    int cargados = cargarDetalles(nro, cuit);

    if (cargados == -1)
    {
        cout << "\n>>> Alta cancelada por el usuario. No se guardo ninguna reparacion." << endl;
        system("pause");
        return;
    }


    //fechs
    if (cargados > 0)
    {
        Fecha fe;
        Fecha fechaActual;
        fechaActual.setFechaActual();

        bool fechaValida = false;
        do
        {
            fe = cargarFecha("Fecha estimada de entrega:");

            if (!fe.esValida())
            {
                cout << " > ERROR: La fecha ingresada es invalida a nivel calendario." << endl;
            }

            else if (fe.aNumero() < fechaActual.aNumero())
            {
                cout << " > ERROR: No puede ingresar una fecha estimada de entrega en el pasado." << endl;
                cout << "   Fecha de hoy: " << fechaActual.toString() << endl;
            }
            else
            {
                fechaValida = true;
            }
        }
        while (!fechaValida);

        //estado inicial de la reparacion
        int estadoInicial = 1;

        cout << "\n=== FLUJO DE TRABAJO ===" << endl;
        int iniciarYa = cargarEntero("¨Va a comenzar a trabajar en esta reparacion ahora mismo? (1=Si, 0=No): ");

        if (iniciarYa == 1)
        {
            estadoInicial = 2;
            cout << " >> La orden se registrara directamente 'En proceso'." << endl;
        }



        Reparacion r(nro, cuit, legajo,fechaActual, fe);
        r.setEstado(estadoInicial);

        if (_repo.crear(r))
        {
            cout << "\n>>> EXITO: La Reparacion #" << nro << " se ha guardado en disco con "
                 << cargados << " equipo(s) en su detalle." << endl;
            system("pause");
        }
        else
        {
            cout << "\n>>> ERROR CRITICO: No se pudo escribir en el archivo reparaciones" << endl;
            system("pause");
        }
    }
    else
    {
        cout << "\n>>> Alta cancelada. No se genero ningun registro en el archivo." << endl;
        system("pause");
    }
}

void ReparacionManager::baja()
{
    cout << "\n=== BAJA DE REPARACION ===" << endl;

    int nro = seleccionarReparacion(0);
    if (nro <= 0)
    {
        cout << " >> Operacion cancelada." << endl;
        return;
    }

    int pos = _repo.buscarPorNumero(nro);
    if (pos == -1)
    {
        cout << "\n > La reparacion #" << nro << " no existe en el sistema." << endl;
        system("pause");
        return;
    }

    Reparacion r = _repo.leer(pos);

    //no permitite borrar reparaciones finalizadas ni en proceso
    if (r.getEstado() == 2 || r.getEstado() == 3)
    {
        cout << "\n > ERROR: No se puede dar de baja." << endl;

        if (r.getEstado() == 2)
        {
            cout << "   Estado actual: EN PROCESO" << endl;
        }
        else
        {
            cout << "   Estado actual: TERMINADA" << endl;
        }

        cout << "   Solo se pueden anular reparaciones 'Sin Iniciar'." << endl;
        system("pause");
        return;
    }

    if (r.getEliminado())
    {
        cout << "\n > La reparacion ya se encuentra dada de baja." << endl;
        system("pause");
        return;
    }

    system("cls");

    mostrar(r);

    int confirmar = cargarEntero("Confirma la baja de esta orden? (1=Si, 0=No): ");
    if (confirmar != 1)
    {
        cout << " >> Operacion cancelada." << endl;
        system("pause");
        return;
    }

    r.setEliminado(true);
    if (!_repo.actualizar(pos, r))
    {
        cout << "\n > ERROR: No se pudo registrar la baja en el archivo." << endl;
        system("pause");
        return;
    }


    int cantD = _repoDetalle.getCantidadRegistros();
    int detallesBorrados = 0;
    int erroresDetalle = 0;

    for (int i = 0; i < cantD; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);
        if (d.getNroReparacion() == nro && !d.getEliminado())
        {
            d.setEliminado(true);
            if (_repoDetalle.actualizar(i, d))
            {
                detallesBorrados++;
            }
            else
            {
                erroresDetalle++;
            }
        }
    }

    cout << "\n>>> EXITO: Reparacion #" << nro << " dada de baja." << endl;
    cout << "    Se eliminaron " << detallesBorrados << " detalle(s) asociado(s)." << endl;

    if (erroresDetalle > 0)
    {
        cout << "    ADVERTENCIA: Hubo fallos al eliminar " << erroresDetalle << " detalle(s)." << endl;
    }

    system("pause");
}

void ReparacionManager::listarEquiposDeLaReparacion(int nroReparacion)
{
    cout << "\n--- Equipos cargados en esta orden ---" << endl;
    int cantD = _repoDetalle.getCantidadRegistros();
    bool hay = false;

    for (int i = 0; i < cantD; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);
        if (d.getNroReparacion() == nroReparacion && !d.getEliminado())
        {
            //busqueda y muestra de equipos
            int posEq = _repoEquipo.buscarPorNumero(d.getNroEquipo());
            if (posEq != -1)
            {
                Equipo eq = _repoEquipo.leer(posEq);
                cout << "  ID Equipo: #" << eq.getNroEquipo()
                     << " | " << eq.getTipoEquipoString() << " " << eq.getMarca()
                     << " | Importe: $" << d.getImporte() << endl;
                hay = true;
            }
        }
    }
    if (!hay) cout << "  (No hay equipos cargados actualmente)" << endl;
    cout << "--------------------------------------" << endl;
}

void ReparacionManager::modificarDetalles(const Reparacion &r)
{
    int opcion;

    do
    {
        system("cls");
        cout << "\n=== DETALLES DE LA REPARACION #" << r.getNroReparacion() << " ===" << endl<<endl;
        cout << "1. Agregar equipo al detalle" << endl;
        cout << "2. Modificar importe de un equipo" << endl;
        cout << "3. Quitar equipo del detalle" << endl;
        cout << "4. Ver detalles actuales" << endl;
        cout << "5. Editar descripcion de falla de un equipo" << endl;
        cout << "0. Terminar modificacion de detalles" << endl;
        opcion = cargarEntero("Seleccione una opcion: ");

        if (opcion == 1)
        {
            mostrarEquiposDeCliente(r.getCuit());

            int nroEquipo = cargarEntero("\nNumero de equipo a agregar (0 para cancelar): ");
            if (nroEquipo == 0) continue;

            //verifica si existe
            if (_repoEquipo.buscarPorNumero(nroEquipo) == -1)
            {
                cout << "El equipo no existe o esta eliminado." << endl;
                system("pause");
                continue;
            }
            //verifica cliente
            if (!equipoPerteneceACliente(nroEquipo, r.getCuit()))
            {
                cout << "El equipo no pertenece al cliente de la reparacion." << endl;
                system("pause");
                continue;
            }
            //verifica repeticion
            if (detalleYaCargado(r.getNroReparacion(), nroEquipo))
            {
                cout << "Ese equipo ya esta en el detalle." << endl;
                system("pause");
                continue;
            }
            float importe = pedirImporte();

            string falla = cargarTexto("Describa la falla o trabajo a realizar: ", 99);

            agregarDetalle(r.getNroReparacion(), nroEquipo, importe, falla.c_str());
            cout << "Equipo agregado." << endl;
            system("pause");
        }
        else if (opcion == 2)
        {
            listarEquiposDeLaReparacion(r.getNroReparacion());

            int nroEquipo = cargarEntero("\nNumero de equipo cuyo importe desea modificar (0 para cancelar): ");
            if (nroEquipo == 0) continue;

            int posDetalle = _repoDetalle.buscarDetalle(r.getNroReparacion(), nroEquipo);
            if (posDetalle == -1)
            {
                cout << " > ERROR: Ese equipo no esta en el detalle de esta orden." << endl;
                system("pause");
                continue;
            }
            DetalleReparacion d = _repoDetalle.leer(posDetalle);

            cout << "Importe actual: $" << d.getImporte() << endl;

            d.setImporte(pedirImporte());
            _repoDetalle.actualizar(posDetalle, d);

            cout << " >> Importe modificado exitosamente." << endl;
            system("pause");
        }
        else if (opcion == 3)
        {

            listarEquiposDeLaReparacion(r.getNroReparacion());

            int nroEquipo = cargarEntero("\nNumero de equipo a quitar del detalle (0 para cancelar): ");
            if (nroEquipo == 0) continue;

            int posDetalle = _repoDetalle.buscarDetalle(r.getNroReparacion(), nroEquipo);

            if (posDetalle == -1)
            {
                cout << " > ERROR: Ese equipo no esta en el detalle de esta orden." << endl;
                system("pause");
                continue;
            }

            if (contarEquiposDeReparacion(r.getNroReparacion()) <= 1)
            {
                cout << " > ERROR: No se puede quitar. La orden de reparacion debe tener al menos un equipo." << endl;
                system("pause");
                continue;
            }

            DetalleReparacion d = _repoDetalle.leer(posDetalle);
            d.setEliminado(true);
            _repoDetalle.actualizar(posDetalle, d);

            cout << " >> Equipo quitado del detalle correctamente." << endl;
            system("pause");
        }
        else if (opcion == 4)
        {
            system("cls");
            mostrar(r);
            system("pause");
        }
        else if (opcion == 5)
        {

            listarEquiposDeLaReparacion(r.getNroReparacion());

            int nroEquipo = cargarEntero("\nNumero de equipo cuya falla desea modificar (0 para cancelar): ");
            if (nroEquipo == 0) continue;

            int posDetalle = _repoDetalle.buscarDetalle(r.getNroReparacion(), nroEquipo);

            if (posDetalle == -1)
            {
                cout << " > ERROR: Ese equipo no esta asignado al detalle de esta orden." << endl;
                system("pause");
                continue;
            }

            DetalleReparacion d = _repoDetalle.leer(posDetalle);

            cout << "Falla actual: " << d.getDetalleFalla() << endl << endl;

            string nuevaFalla = cargarTexto("Ingrese la nueva descripcion de la falla: ", 99);

            d.setDetalleFalla(nuevaFalla.c_str());

            if (_repoDetalle.actualizar(posDetalle, d))
            {
                cout << " >> Exito: Descripcion de falla modificada en el disco." << endl;
            }
            else
            {
                cout << " > ERROR: No se pudo actualizar el archivo de detalles." << endl;
            }
            system("pause");
        }
    }

    while (opcion != 0);
}

void ReparacionManager::modificacion()
{
    cout << "\n===  MODIFICACION DE REPARACION ===" << endl;

    int nro = seleccionarReparacion();

    if(nro <= 0 ) return;

    int pos = _repo.buscarPorNumero(nro);
    if (pos == -1)
    {
        cout << " > La reparacion no existe en el archivo." << endl;
        system("pause");
        return;
    }

    Reparacion r = _repo.leer(pos);

    if (r.getEliminado())
    {
        cout << " > ERROR: La reparacion seleccionada se encuentra eliminada (Baja Logica)." << endl;
        system("pause");
        return;
    }

    // Estado 3 = TERMINADA
    if (r.getEstado() == 3)
    {
        cout << "\n > ERROR: Esta orden ya fue entregada y cerrada." << endl;
        cout << "   Por seguridad y auditoria, su historial es de solo lectura y no puede modificarse." << endl;
        system("pause");
        return;
    }

    string nombreCliente = "(No encontrado)";
    int posC = _repoCliente.buscarPorCuit(r.getCuit());
    if (posC != -1)
    {
        Cliente c = _repoCliente.leer(posC);
        nombreCliente = c.getNombre() + " " + c.getApellido();
    }

    int opcion;
    do
    {
        system("cls");
        cout << "=== MODIFICAR REPARACION #" << r.getNroReparacion() << " ===" << endl;
        cout << "Cliente Titular (No modificable): " << r.getCuit() << " - " << nombreCliente << endl;
        cout << "Fecha de Ingreso (No modificable): " << r.getFechaIngreso().toString() << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Modificar Legajo Empleado (Actual:   " << r.getLegajo() << " )" << endl;
        cout << "2. Modificar Fecha de Entrega (Actual:   " << r.getFechaEntrega().toString() << " )" << endl;
        cout << "3. Cambiar Estado de la Reparacion (Actual: " << getNombreEstado(r.getEstado()) << " )" << endl;
        cout << "4. Modificar Equipos/Importes del Detalle" << endl;
        cout << "0. Volver al menu anterior" << endl;

        opcion = cargarEntero("\nSeleccione una opcion: ");

        switch (opcion)
        {
        case 1:
        {
            string nuevoLegajo = cargarTexto("Ingrese el nuevo Legajo: ", 9);

            if (_repoEmpleado.buscarPorLegajo(nuevoLegajo) == -1)
            {
                cout << " > ERROR: El empleado no existe o esta dado de baja." << endl;
            }
            else
            {
                r.setLegajo(nuevoLegajo);

                if (_repo.actualizar(pos, r))
                {
                    cout << " >> Legajo modificado exitosamente en el archivo." << endl;
                }
                else
                {
                    cout << " > ERROR: No se pudo actualizar el Legajo en el disco." << endl;
                }
            }
            system("pause");
            break;
        }

        case 2:
        {
            Fecha nuevaFecha;
            Fecha hoy;
            hoy.setFechaActual();
            bool fechaValida = false;

            do
            {
                nuevaFecha = cargarFecha("Ingrese la NUEVA fecha de entrega:");

                if (!nuevaFecha.esValida())
                {
                    cout << " > ERROR: La fecha ingresada no existe en el calendario." << endl;
                }
                else if (nuevaFecha.aNumero() < r.getFechaIngreso().aNumero())
                {
                    cout << " > ERROR: La fecha de entrega no puede ser anterior a la fecha de ingreso." << endl;
                    cout << "    Fecha de ingreso de esta orden: " << r.getFechaIngreso().toString() << endl;
                }
                else
                {
                    fechaValida = true;
                }
            }
            while (!fechaValida);

            if (nuevaFecha.aNumero() > hoy.aNumero())
            {
                //fecha reprogramada
                r.setEstado(2);
                cout << " >> Fecha reprogramada. La orden se mantiene [EN PROCESO]." << endl;
            }
            else
            {
                cout << "\n> AVISO: La fecha ingresada coincide con el dia de hoy o es anterior." << endl<< endl;

                int terminarYa = cargarEntero(" El trabajo ya fue FINALIZADO y entregado con exito? (1=Si [TERMINADA], 0=No [EN PROCESO]): ");

                if (terminarYa == 1)
                {
                    r.setEstado(3);
                    cout << " >> La orden se actualizo a estado [TERMINADA]." << endl;
                }
                else
                {
                    r.setEstado(2);
                    cout << " >> La orden permanecera [EN PROCESO] mientras se termina el trabajo." << endl;
                }
            }

            if (_repo.actualizar(pos, r))
            {
                cout << " >> Cambios guardados exitosamente en el archivo." << endl;
            }
            else
            {
                cout << " > ERROR: No se pudo guardar la nueva fecha en el archivo." << endl;
            }
            system("pause");
            break;
        }

        case 3:
        {
            cout << "\n--- CAMBIAR ESTADO DE TRABAJO ---" << endl;
            cout << "1. Sin iniciar" << endl;
            cout << "2. En proceso" << endl;
            cout << "3. Terminada" << endl;
            int nuevoEstado = cargarEntero("Seleccione el nuevo estado: ");

            if(nuevoEstado < 1 || nuevoEstado > 3)
            {
                cout << " > ERROR: Seleccion de estado invalida." << endl;
            }
            else
            {
                r.setEstado(nuevoEstado);
                if (_repo.actualizar(pos, r))
                {
                    cout << " >> Estado actualizado exitosamente a: " << getNombreEstado(nuevoEstado) << endl;
                }
                else
                {
                    cout << " > ERROR: No se pudo guardar el nuevo estado en el disco." << endl;
                }
            }
            system("pause");
            break;
        }

        case 4:
            modificarDetalles(r);
            r = _repo.leer(pos);
            break;

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

string ReparacionManager::getNombreEstado(int estado)
{
    switch(estado)
    {
    case 1:
        return "Sin iniciar";
    case 2:
        return "En proceso";
    case 3:
        return "Terminada";
    default:
        return "Desconocido";
    }
}


int ReparacionManager::seleccionarReparacion(int filtroEstado)
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== SELECCIONAR ORDEN DE REPARACION ===" << endl;
        cout << "1. Buscar ingresando el ID directamente" << endl;
        cout << "2. Buscar por CUIT de Cliente" << endl;
        cout << "0. Cancelar operacion" << endl;
        opcion = cargarEntero("\nSeleccione una opcion de busqueda: ");

        switch (opcion)
        {
        case 1:
        {
            int id = cargarEntero("Ingrese el ID de la reparacion: ");

            if (_repo.buscarPorNumero(id) != -1) return id;

            cout << " > El ID ingresado no corresponde a una reparacion activa." << endl;
            system("pause");
            break;
        }
        case 2:
        {
            int idEncontrado = buscarPorCuit(filtroEstado);
            if (idEncontrado > 0) return idEncontrado;
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



int ReparacionManager::buscarPorCuit(int filtroEstado)
{
    string cuit;
    int opcion = 1;

    while (opcion == 1)
    {
        system("cls");
        cout << "=== BUSCAR REPARACION POR CUIT ===" << endl;
        cuit = cargarTexto("Ingrese el CUIT del cliente (o '0' para cancelar): ", 14);

        if (cuit == "0") return 0;

        int cantidad = _repo.getCantidadRegistros();
        int coincidencias = 0;
        int ultimoIdEncontrado = -1;

        for (int i = 0; i < cantidad; i++)
        {
            Reparacion r = _repo.leer(i);

            if (!r.getEliminado() && r.getCuit() == cuit && (filtroEstado == 0 || r.getEstado() == filtroEstado))
            {
                coincidencias++;
                ultimoIdEncontrado = r.getNroReparacion();
            }
        }

        if (coincidencias == 1)
        {
            cout << "\n> Se encontro una unica reparacion activa. Seleccionando ID: #" << ultimoIdEncontrado << endl;
            system("pause");
            return ultimoIdEncontrado;
        }


        if (coincidencias == 0)
        {
            cout << "\n > No se encontraron reparaciones activas para el CUIT: " << cuit << endl;
            cout << "1. Intentar con otro CUIT" << endl;
            cout << "0. Volver atras" << endl;
            opcion = cargarEntero("\nSeleccione una opcion: ");
            if (opcion == 0) return 0;
            continue;
        }


        system("cls");
        cout << "=== REPARACIONES ENCONTRADAS PARA EL CUIT: " << cuit << " ===" << endl;
        cout << "----------------------------------------------------------------------" << endl;

        for (int i = 0; i < cantidad; i++)
        {
            Reparacion r = _repo.leer(i);

            if (!r.getEliminado() && r.getCuit() == cuit && (filtroEstado == 0 || r.getEstado() == filtroEstado))
            {
                cout << " ID Orden: #" << r.getNroReparacion()
                     << " | Ingreso: " << r.getFechaIngreso().toString()
                     << " | Estado: " << getNombreEstado(r.getEstado()) << endl;
            }
        }
        cout << "----------------------------------------------------------------------" << endl;

        int idSeleccionado = cargarEntero("\nIngrese el ID de la orden que desea seleccionar (0 para cancelar): ");
        if (idSeleccionado == 0) return 0;

        int posValidar = _repo.buscarPorNumero(idSeleccionado);
        if (posValidar != -1)
        {
            Reparacion rValidar = _repo.leer(posValidar);
            if (rValidar.getCuit() == cuit && !rValidar.getEliminado())
            {
                return idSeleccionado;
            }
        }

        cout << "\n > ERROR: El ID ingresado no corresponde a ninguna de las opciones listadas." << endl;
        system("pause");
    }

    return 0;
}


bool ReparacionManager::equipoTieneReparacionAbierta(int nroEquipo)
{
    int cantDetalles = _repoDetalle.getCantidadRegistros();

    for (int i = 0; i < cantDetalles; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);

        if (d.getNroEquipo() == nroEquipo && !d.getEliminado())
        {

            int posReparacion = _repo.buscarPorNumero(d.getNroReparacion());

            if (posReparacion != -1)
            {
                Reparacion rep = _repo.leer(posReparacion);

                if (rep.getEstado() == 1 || rep.getEstado() == 2)
                {
                    return true;
                }
            }
        }
    }
    return false; //equipo libre para cargar
}

void ReparacionManager::listado()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== MENU DE LISTADOS DE REPARACIONES ===" << endl<<endl;
        cout << "1. Listar TODAS las reparaciones activas" << endl;
        cout << "2. Listar reparaciones: SIN INICIAR" << endl;
        cout << "3. Listar reparaciones: EN PROCESO" << endl;
        cout << "4. Listar reparaciones: TERMINADAS" << endl;
        cout << "0. Volver al menu anterior" << endl;

        opcion = cargarEntero("\nSeleccione una opcion de listado: ");

        if (opcion == 0) break;

        if (opcion < 1 || opcion > 4)
        {
            cout << " > Opcion incorrecta." << endl<<endl;
            system("pause");
            continue;
        }

        int cantidad = _repo.getCantidadRegistros();
        if (cantidad == 0)
        {
            cout << "\nNo hay reparaciones registradas en el sistema." << endl<<endl;
            system("pause");
            continue;
        }

        system("cls");

        if (opcion == 1)
        {
            cout << "=== LISTADO DE TODAS LAS REPARACIONES ACTIVAS ===\n" << endl;
        }
        else
        {
            cout << "=== LISTADO DE REPARACIONES [" << getNombreEstado(opcion - 1) << "] ===\n" << endl;
        }

        bool hay = false;
        for (int i = 0; i < cantidad; i++)
        {
            Reparacion r = _repo.leer(i);
            if (!r.getEliminado())
            {

                if (opcion == 1 || r.getEstado() == (opcion - 1))
                {
                    mostrar(r);
                    hay = true;
                }
            }
        }

        if (!hay)
        {
            if (opcion == 1) cout << "No hay reparaciones activas." << endl<<endl;
            else cout << "No hay reparaciones en estado: " << getNombreEstado(opcion - 1) << endl<<endl;
        }

        system("pause");

    }
    while (opcion != 0);
}

void ReparacionManager::listadoPorFechaEntrega()
{
    cout << "\n=== LISTADO DE REPARACIONES (ORDENADO POR FECHA DE ENTREGA) ===" << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay reparaciones registradas." << endl;
        return;
    }

    Reparacion *v = new Reparacion[cantidad];
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
            if (v[j].getFechaEntrega().aNumero() < v[min].getFechaEntrega().aNumero()) min = j;
        }
        if (min != i)
        {
            Reparacion tmp = v[i];
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
    if (!hay) cout << "No hay reparaciones activas." << endl;

    delete[] v;
}


string ReparacionManager::asignarTecnico()
{
    system("cls");
    cout << "=== SELECCION DE TECNICO ===" << endl<<endl;
    cout << "Legajo\t\tNombre\t\tTareas Activas" << endl;
    cout << "------------------------------------------" << endl;

    EmpleadoManager mgrEmp;
    int cant = _repoEmpleado.getCantidadRegistros();

    for(int i = 0; i < cant; i++)
    {
        Empleado e = _repoEmpleado.leer(i);
        if(!e.getEliminado())
        {
            int tareas = mgrEmp.contarTareasPendientes(e.getLegajo());

            string nombreCompleto = e.getNombre() + " " + e.getApellido();

            cout << left << setw(10) << e.getLegajo()
                 << left << setw(25) << nombreCompleto
                 << right << setw(10) << tareas << endl;
        }
    }
    cout << "------------------------------------------" << endl;

    string legajo;
    bool encontrado = false;
    while (!encontrado)
    {
        legajo = cargarTexto("Ingrese legajo del tecnico (o '0' para cancelar): ", 9);
        if (legajo == "0") return "0";

        int pos = _repoEmpleado.buscarPorLegajo(legajo);
        if (pos != -1)
        {
            Empleado emp = _repoEmpleado.leer(pos);
            if (!emp.getEliminado()) encontrado = true;
            else cout << " > Error: Empleado dado de baja." << endl;
        }
        else
        {
            cout << " > Error: Legajo no encontrado." << endl;
        }
    }

    return legajo;
}

void ReparacionManager::menuConsultas()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== CONSULTAS Y LISTADOS: REPARACIONES ===" << endl << endl;
        cout << "1. Listado general ordenado por Fecha de Entrega" << endl;
        cout << "2. Consulta individual por Numero de Orden (ID)" << endl;
        cout << "3. Consulta de reparaciones por Cliente (CUIT)" << endl;
        cout << "4. Buscar reparaciones por Numero de Equipo" << endl;
        cout << "5. Filtrar reparaciones por Estado" << endl;
        cout << "6. Buscar reparaciones por Rango de Fechas" << endl;
        cout << "7. Ver historial de reparaciones anuladas (Bajas)" << endl;
        cout << "0. Volver al menu anterior" << endl;

        opcion = cargarEntero("\nSeleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            system("cls");
            listadoPorFechaEntrega();
            system("pause");
            break;
        case 2:
            system("cls");
            consultaPorId();
            system("pause");
            break;
        case 3:
            system("cls");
            consultaPorCliente();
            system("pause");
            break;
        case 4:
            system("cls");
            consultaPorNumeroEquipo();
            system("pause");
            break;
        case 5:
            listado();
            break;
        case 6:
            system("cls");
            consultaPorRangoFechas();
            system("pause");
            break;
        case 7:
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
    }
    while (opcion != 0);
}


void ReparacionManager::consultaPorCliente()
{
    cout << "=== CONSULTA DE REPARACIONES POR CLIENTE ===" << endl << endl;

    int id = buscarPorCuit();

    if (id > 0)
    {
        int pos = _repo.buscarPorNumero(id);
        if (pos != -1)
        {
            system("cls");
            cout << "=== DETALLE DE LA ORDEN DE REPARACION ===" << endl << endl;
            mostrar(_repo.leer(pos));
        }
    }
}

void ReparacionManager::consultaPorRangoFechas()
{
    cout << "=== CONSULTA POR RANGO DE FECHAS (INGRESO) ===" << endl << endl;
    cout << "Ingrese la fecha de INICIO del periodo:" << endl;

    Fecha fechaInicio = cargarFecha("");

    if (!fechaInicio.esValida())
    {
        cout << " > Fecha invalida." << endl;
        return;
    }

    cout << "\nIngrese la fecha de FIN del periodo:" << endl;

    Fecha fechaFin = cargarFecha("");

    if (!fechaFin.esValida() || fechaFin.aNumero() < fechaInicio.aNumero())
    {
        cout << " > Fecha invalida o anterior a la fecha de inicio." << endl;
        return;
    }

    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0) return;

    system("cls");
    cout << "=== REPARACIONES INGRESADAS ENTRE " << fechaInicio.toString() << " Y " << fechaFin.toString() << " ===" << endl << endl;

    bool hayRegistros = false;
    for (int i = 0; i < cantidad; i++)
    {
        Reparacion r = _repo.leer(i);
        if (!r.getEliminado())
        {
            if (r.getFechaIngreso().aNumero() >= fechaInicio.aNumero() &&
                    r.getFechaIngreso().aNumero() <= fechaFin.aNumero())
            {
                mostrar(r);
                hayRegistros = true;
            }
        }
    }

    if (!hayRegistros)
    {
        cout << "No se registraron ingresos de equipos en ese periodo de tiempo." << endl;
    }
}

void ReparacionManager::listadoInactivos()
{
    cout << "=== HISTORIAL DE REPARACIONES ANULADAS ===" << endl << endl;
    int cantidad = _repo.getCantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay registros en el archivo." << endl;
        return;
    }

    bool hayInactivos = false;
    for (int i = 0; i < cantidad; i++)
    {
        Reparacion r = _repo.leer(i);
        if (r.getEliminado())
        {
            mostrar(r);
            hayInactivos = true;
        }
    }
    if (!hayInactivos) cout << "No hay registro de reparaciones anuladas." << endl;
}


void ReparacionManager::consultaPorId()
{
    cout << "=== CONSULTA DE REPARACION POR ID ===" << endl << endl;
    int nro = cargarEntero("Ingrese el ID (Nro Reparacion) a buscar: ");

    int pos = _repo.buscarPorNumero(nro);
    if (pos == -1)
    {
        cout << " > No se encontro ninguna reparacion con ese ID." << endl;
        return;
    }

    Reparacion r = _repo.leer(pos);
    if (r.getEliminado())
    {
        cout << " > La reparacion con ese ID se encuentra dada de baja." << endl;
        return;
    }

    system("cls");
    cout << "=== DETALLE COMPLETO DE LA ORDEN ===" << endl << endl;
    mostrar(r);
}

void ReparacionManager::consultaPorNumeroEquipo()
{
    cout << "=== BUSCAR REPARACIONES POR NUMERO DE EQUIPO ===" << endl << endl;
    int nroEquipo = cargarEntero("Ingrese el numero de equipo a rastrear: ");

    int posEq = _repoEquipo.buscarPorNumero(nroEquipo);
    if (posEq == -1)
    {
        cout << "\n > El equipo #" << nroEquipo << " no esta registrado en el sistema." << endl;
        return;
    }

    Equipo eq = _repoEquipo.leer(posEq);
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Equipo:       #" << eq.getNroEquipo() << " - [" << eq.getTipoEquipoString() << "] " << eq.getMarca() << endl;
    cout << "Descripcion:  " << eq.getDescripcion() << endl;
    cout << "======================================================================" << endl;

    int cantD = _repoDetalle.getCantidadRegistros();
    bool hayHistorial = false;
    cout << "\nHistorial de Ordenes de Trabajo asociadas a este equipo:" << endl<< endl;


    for (int i = 0; i < cantD; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);
        if (!d.getEliminado() && d.getNroEquipo() == nroEquipo)
        {

            int posRep = _repo.buscarPorNumero(d.getNroReparacion());
            if (posRep != -1)
            {
                Reparacion r = _repo.leer(posRep);
                if (!r.getEliminado())
                {
                    hayHistorial = true;
                    cout << "  [*] Orden #" << r.getNroReparacion()
                         << " | Ingreso: " << r.getFechaIngreso().toString()
                         << " | Estado: " << getNombreEstado(r.getEstado()) << endl;
                    cout << "      Trabajo asignado: " << d.getDetalleFalla() << endl;
                    cout << "      Costo facturado:  $" << d.getImporte() << endl;
                    cout << "  --------------------------------------------------------------------" << endl;
                }
            }
        }
    }

    if (!hayHistorial)
    {
        cout << "  (Este equipo no registra ninguna orden de reparacion en el sistema)" << endl;
    }
}


