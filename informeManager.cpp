#include <iostream>
#include <iomanip>
#include <sstream>
#include "informeManager.h"
#include "utils.h"
using namespace std;

InformeManager::InformeManager()
    : _mgrReparacion(), _repoCliente(), _repoEmpleado(), _repoEquipo(),
      _repoReparacion(), _repoDetalle() {}

bool InformeManager::pedirRangoFechas(Fecha &desde, Fecha &hasta)
{
    Fecha fechaActual;
    fechaActual.setFechaActual();
    bool rangoValido = false;

    cout << "\n---(Presione '0' en cualquier campo numerico para cancelar)---" << endl<<endl;

    do
    {
        desde = cargarFecha("Fecha DESDE:",true); //aborta al presionar 0
        if (desde.getDia() == 0 || desde.getMes() == 0 || desde.getAnio() == 0) return false;

        if (!desde.esValida())
        {
            cout << " > ERROR: La fecha 'Desde' ingresada no existe en el calendario.\n" << endl;
            continue;
        }

        hasta = cargarFecha("Fecha HASTA:",true); //aborta al presionar 0
        if (hasta.getDia() == 0 || hasta.getMes() == 0 || hasta.getAnio() == 0) return false;

        if (!hasta.esValida())
        {
            cout << " > ERROR: La fecha 'Hasta' ingresada no existe en el calendario.\n" << endl;
            continue;
        }

        if(hasta.aNumero() > fechaActual.aNumero())
        {
            cout << "\n > ERROR DE AUDITORIA: La fecha 'Hasta' no puede ser posterior a la fecha de hoy." << endl;
            cout << "   Fecha actual del taller: " << fechaActual.toString() << "\n" << endl<< endl;
        }
        else if (hasta.aNumero() < desde.aNumero())
        {
            cout << "\n > ERROR: La fecha 'Desde' no puede ser posterior a la fecha 'Hasta'.\n" << endl<<endl;
        }
        else
        {
            rangoValido = true;
        }
    }
    while (!rangoValido);

    return true;
}

void InformeManager::recaudacionPorPeriodo()
{
    cout << "\n========= INFORME: RECAUDACION MENSUAL =========" << endl;
    Fecha desde, hasta;
    if (!pedirRangoFechas(desde, hasta)) return;

    int cantR = _repoReparacion.getCantidadRegistros();
    int cantD = _repoDetalle.getCantidadRegistros();
    if (cantR == 0 || cantD == 0)
    {
        cout << "Faltan registros en el sistema para procesar el informe." << endl;
        return;
    }

    //carga
    Reparacion* vReparaciones = new Reparacion[cantR];
    if (vReparaciones == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria para cargar las reparaciones." << endl;
        return;
    }

    _repoReparacion.leerTodos(vReparaciones, cantR);

    DetalleReparacion* vDetalles = new DetalleReparacion[cantD];

    if (vDetalles == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria para cargar los detalles." << endl;
        delete[] vReparaciones;
        return;
    }
    _repoDetalle.leerTodos(vDetalles, cantD);

    cout << "\nRECAUDACION ENTRE " << desde.toString() << " Y " << hasta.toString() << endl;
    cout << "=============================================================" << endl;
    cout << left << setw(15) << "PERIODO" << "RECAUDACION" << endl;
    cout << "=============================================================" << endl;

    float total = 0;
    int y = desde.getAnio();
    int m = desde.getMes();

    while (y < hasta.getAnio() || (y == hasta.getAnio() && m <= hasta.getMes()))
    {
        float subtotal = 0;
        for (int i = 0; i < cantR; i++)
        {
            Reparacion r = vReparaciones[i];

            if (r.getEliminado() || r.getEstado() != 3) continue;

            long f = r.getFechaEntrega().aNumero();
            if (r.getFechaEntrega().getAnio() == y && r.getFechaEntrega().getMes() == m &&
                f >= desde.aNumero() && f <= hasta.aNumero())
            {
                //calculo
                float totalRep = 0;
                for (int d = 0; d < cantD; d++) {
                    if (!vDetalles[d].getEliminado() && vDetalles[d].getNroReparacion() == r.getNroReparacion()) {
                        totalRep += vDetalles[d].getImporte();
                    }
                }
                subtotal += totalRep;
            }
        }

        ostringstream periodo;
        periodo << (m < 10 ? "0" : "") << m << "/" << y;
        cout << left << setw(15) << periodo.str()
             << "$ " << fixed << setprecision(2) << subtotal << endl;
        total += subtotal;

        m++;
        if (m > 12)
        {
            m = 1;
            y++;
        }
    }

    cout << "=============================================================" << endl;
    cout << left << setw(15) << "TOTAL" << "$ " << fixed << setprecision(2) << total << endl;

    delete[] vReparaciones;
    delete[] vDetalles;
}

void InformeManager::recaudacionPorCliente()
{
    cout << "\n========= INFORME: RECAUDACION POR CLIENTE =========" << endl;
    Fecha desde, hasta;
    if (!pedirRangoFechas(desde, hasta)) return;

    int cantC = _repoCliente.getCantidadRegistros();
    int cantR = _repoReparacion.getCantidadRegistros();
    int cantD = _repoDetalle.getCantidadRegistros();

    if (cantC == 0 || cantR == 0 || cantD == 0)
    {
        cout << "Faltan registros en el sistema para emitir el informe." << endl;
        return;
    }

    //carga
    Cliente* vClientes = new Cliente[cantC];
    if (vClientes == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria." << endl;
        return;
    }
    _repoCliente.leerTodos(vClientes, cantC);

    Reparacion* vReparaciones = new Reparacion[cantR];
    if (vReparaciones == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria." << endl;
        delete[] vClientes;
        return;
    }
    _repoReparacion.leerTodos(vReparaciones, cantR);

    DetalleReparacion* vDetalles = new DetalleReparacion[cantD];
    if (vDetalles == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria." << endl;
        delete[] vClientes;
        delete[] vReparaciones;
        return;
    }
    _repoDetalle.leerTodos(vDetalles, cantD);

    cout << "\nRECAUDACION POR CLIENTE ENTRE " << desde.toString() << " Y " << hasta.toString() << endl;
    cout << "======================================================================================" << endl;
    cout << left << setw(15) << "CUIT" << setw(20) << "APELLIDO"
         << setw(20) << "NOMBRE" << setw(15) << "TOTAL ($)"
         << "REPARACIONES" << endl;
    cout << "======================================================================================" << endl;

    bool hay = false;
    float totalGeneral = 0;

    for (int i = 0; i < cantC; i++)
    {
        Cliente c = vClientes[i];
        if (c.getEliminado()) continue;

        float totalCliente = 0;
        int cantRep = 0;

        for (int j = 0; j < cantR; j++)
        {
            Reparacion r = vReparaciones[j];
            long f = r.getFechaEntrega().aNumero();

            //calculo
            if (!r.getEliminado() && r.getEstado() == 3 && r.getCuit() == c.getCuit() &&
                f >= desde.aNumero() && f <= hasta.aNumero())
            {
                float totalRep = 0;
                for (int d = 0; d < cantD; d++) {
                    if (!vDetalles[d].getEliminado() && vDetalles[d].getNroReparacion() == r.getNroReparacion()) {
                        totalRep += vDetalles[d].getImporte();
                    }
                }
                totalCliente += totalRep;
                cantRep++;
            }
        }

        if (cantRep > 0)
        {
            cout << left << setw(15) << c.getCuit()
                 << setw(20) << c.getApellido()
                 << setw(20) << c.getNombre()
                 << "$ " << left << setw(13) << fixed << setprecision(2) << totalCliente
                 << cantRep << endl;
            totalGeneral += totalCliente;
            hay = true;
        }
    }

    if (!hay) cout << "No hubo recaudacion de clientes en el periodo." << endl;
    else
    {
        cout << "======================================================================================" << endl;
        cout << ">>> TOTAL GENERAL: $" << fixed << setprecision(2) << totalGeneral << endl;
    }

    delete[] vClientes;
    delete[] vReparaciones;
    delete[] vDetalles;
}

void InformeManager::reparacionesPorTipoEquipo()
{
    cout << "\n=== INFORME: REPARACIONES POR TIPO DE EQUIPO ===" << endl;
    Fecha desde, hasta;
    if (!pedirRangoFechas(desde, hasta)) return;

    int cantE = _repoEquipo.getCantidadRegistros();
    int cantR = _repoReparacion.getCantidadRegistros();
    int cantD = _repoDetalle.getCantidadRegistros();

    if (cantE == 0 || cantR == 0 || cantD == 0) return;

    //carga
    Equipo* vEquipos = new Equipo[cantE];
    if (vEquipos == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria." << endl;
        return;
    }
    _repoEquipo.leerTodos(vEquipos, cantE);

    Reparacion* vReparaciones = new Reparacion[cantR];
    if (vReparaciones == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria." << endl;
        delete[] vEquipos;
        return;
    }
    _repoReparacion.leerTodos(vReparaciones, cantR);

    DetalleReparacion* vDetalles = new DetalleReparacion[cantD];
    if (vDetalles == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria." << endl;
        delete[] vEquipos;
        delete[] vReparaciones;
        return;
    }
    _repoDetalle.leerTodos(vDetalles, cantD);

    int cantidades[6] = {0};
    float recaudaciones[6] = {0};

    for (int i = 0; i < cantD; i++)
    {
        DetalleReparacion d = vDetalles[i];
        if (d.getEliminado()) continue;

        //busqueda de reparacion
        int posR = -1;
        for (int k = 0; k < cantR; k++) {
            if (vReparaciones[k].getNroReparacion() == d.getNroReparacion()) { posR = k; break; }
        }
        if (posR == -1) continue;

        Reparacion r = vReparaciones[posR];

        if (r.getEliminado() || r.getEstado() != 3) continue;

        long f = r.getFechaEntrega().aNumero();
        if (f < desde.aNumero() || f > hasta.aNumero()) continue;

        //busqueda de equipo
        int posE = -1;
        for (int k = 0; k < cantE; k++) {
            if (vEquipos[k].getNroEquipo() == d.getNroEquipo()) { posE = k; break; }
        }
        if (posE == -1) continue;

        Equipo e = vEquipos[posE];
        int t = e.getTipoEquipo();
        if (t >= 1 && t <= 5)
        {
            cantidades[t]++;
            recaudaciones[t] += d.getImporte();
        }
    }

    const char *tipos[] = {"", "PC ESCRITORIO", "NOTEBOOK", "IMPRESORA", "PERIFERICO", "CELULAR"};

    cout << "\nREPARACIONES POR TIPO DE EQUIPO ENTRE " << desde.toString() << " Y " << hasta.toString() << endl;
    cout << "=============================================================" << endl;
    cout << left << setw(20) << "TIPO" << setw(12) << "CANTIDAD" << "RECAUDACION" << endl;
    cout << "=============================================================" << endl;

    int totalCant = 0;
    float totalRec = 0;
    for (int t = 1; t <= 5; t++)
    {
        cout << left << setw(20) << tipos[t]
             << setw(12) << cantidades[t]
             << "$ " << fixed << setprecision(2) << recaudaciones[t] << endl;
        totalCant += cantidades[t];
        totalRec += recaudaciones[t];
    }
    cout << "=============================================================" << endl;
    cout << left << setw(20) << "TOTAL"
         << setw(12) << totalCant
         << "$ " << fixed << setprecision(2) << totalRec << endl;

    delete[] vEquipos;
    delete[] vReparaciones;
    delete[] vDetalles;
}

void InformeManager::productividadEmpleados()
{
    cout << "\n=== INFORME: PRODUCTIVIDAD POR EMPLEADO ===" << endl;
    Fecha desde, hasta;
    if (!pedirRangoFechas(desde, hasta)) return;

    int cantEmp = _repoEmpleado.getCantidadRegistros();
    int cantR = _repoReparacion.getCantidadRegistros();
    int cantD = _repoDetalle.getCantidadRegistros();

    if (cantEmp == 0 || cantR == 0 || cantD == 0) return;

    //carga
    Empleado* vEmpleados = new Empleado[cantEmp];
    if (vEmpleados == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria para empleados." << endl;
        return;
    }
    _repoEmpleado.leerTodos(vEmpleados, cantEmp);

    Reparacion* vReparaciones = new Reparacion[cantR];
    if (vReparaciones == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria para reparaciones." << endl;
        delete[] vEmpleados;
        return;
    }
    _repoReparacion.leerTodos(vReparaciones, cantR);

    DetalleReparacion* vDetalles = new DetalleReparacion[cantD];
    if (vDetalles == nullptr)
    {
        cout << " > ERROR CRITICO: No se pudo obtener memoria para detalles." << endl;
        delete[] vEmpleados;
        delete[] vReparaciones;
        return;
    }
    _repoDetalle.leerTodos(vDetalles, cantD);

    cout << "\nPRODUCTIVIDAD ENTRE " << desde.toString() << " Y " << hasta.toString() << endl;
    cout << "============================================================================" << endl;
    cout << left << setw(10) << "LEGAJO" << setw(20) << "APELLIDO"
         << setw(20) << "NOMBRE" << setw(8) << "REPS"
         << "FACTURADO" << endl;
    cout << "============================================================================" << endl;

    for (int i = 0; i < cantEmp; i++)
    {
        Empleado e = vEmpleados[i];
        if (e.getEliminado()) continue;

        int reps = 0;
        float facturado = 0;
        for (int j = 0; j < cantR; j++)
        {
            Reparacion r = vReparaciones[j];
            long f = r.getFechaEntrega().aNumero();

            //calculo
            if (!r.getEliminado() && r.getEstado() == 3 && r.getLegajo() == e.getLegajo() &&
                f >= desde.aNumero() && f <= hasta.aNumero())
            {
                reps++;
                float totalRep = 0;
                for (int d = 0; d < cantD; d++) {
                    if (!vDetalles[d].getEliminado() && vDetalles[d].getNroReparacion() == r.getNroReparacion()) {
                        totalRep += vDetalles[d].getImporte();
                    }
                }
                facturado += totalRep;
            }
        }

        cout << left << setw(10) << e.getLegajo()
             << setw(20) << e.getApellido()
             << setw(20) << e.getNombre()
             << setw(8) << reps
             << "$ " << fixed << setprecision(2) << facturado << endl;
    }
    cout << "============================================================================" << endl;

    delete[] vEmpleados;
    delete[] vReparaciones;
    delete[] vDetalles;
}

void InformeManager::equiposReincidentes()
{
    cout << "\n=== INFORME: EQUIPOS REINCIDENTES ===" << endl;
    Fecha desde, hasta;
    if (!pedirRangoFechas(desde, hasta)) return;

    int cantE = _repoEquipo.getCantidadRegistros();
    int cantD = _repoDetalle.getCantidadRegistros();
    int cantR = _repoReparacion.getCantidadRegistros();
    int cantEmp = _repoEmpleado.getCantidadRegistros();

    if (cantE == 0 || cantD == 0 || cantR == 0) return;

    //carga
    Equipo* vEquipos = new Equipo[cantE];
    if (vEquipos == nullptr) {
        cout << " > ERROR CRITICO: Sin memoria para Equipos." << endl;
        return;
    }
    _repoEquipo.leerTodos(vEquipos, cantE);

    DetalleReparacion* vDetalles = new DetalleReparacion[cantD];
    if (vDetalles == nullptr) {
        cout << " > ERROR CRITICO: Sin memoria para Detalles." << endl;
        delete[] vEquipos;
        return;
    }
    _repoDetalle.leerTodos(vDetalles, cantD);

    Reparacion* vReparaciones = new Reparacion[cantR];
    if (vReparaciones == nullptr) {
        cout << " > ERROR CRITICO: Sin memoria para Reparaciones." << endl;
        delete[] vEquipos;
        delete[] vDetalles;
        return;
    }
    _repoReparacion.leerTodos(vReparaciones, cantR);

    Empleado* vEmpleados = new Empleado[cantEmp];
    if (vEmpleados == nullptr) {
        cout << " > ERROR CRITICO: Sin memoria para Empleados." << endl;
        delete[] vEquipos;
        delete[] vDetalles;
        delete[] vReparaciones;
        return;
    }
    _repoEmpleado.leerTodos(vEmpleados, cantEmp);


    cout << "\nEQUIPOS REINCIDENTES ENTRE " << desde.toString() << " Y " << hasta.toString() << endl;
    cout << "==================================================================" << endl << endl;

    bool hayReincidentes = false;

    for (int i = 0; i < cantE; i++)
    {
        Equipo e = vEquipos[i];

        int cantidad = 0;
        ostringstream detalles;

        //calculo
        for (int j = 0; j < cantD; j++)
        {
            DetalleReparacion d = vDetalles[j];
            if (d.getEliminado() || d.getNroEquipo() != e.getNroEquipo()) continue;

            int posR = -1;
            for (int k = 0; k < cantR; k++) {
                if (vReparaciones[k].getNroReparacion() == d.getNroReparacion()) { posR = k; break; }
            }
            if (posR == -1) continue;

            Reparacion r = vReparaciones[posR];

            if (r.getEliminado() || r.getEstado() != 3) continue;

            long f = r.getFechaEntrega().aNumero();
            if (f < desde.aNumero() || f > hasta.aNumero()) continue;

            //empleado
            string nombreTecnico = "Desconocido";
            for (int k = 0; k < cantEmp; k++) {
                if (vEmpleados[k].getLegajo() == r.getLegajo()) {
                    nombreTecnico = vEmpleados[k].getNombre() + " " + vEmpleados[k].getApellido();
                    break;
                }
            }

            cantidad++;
            detalles << "    Reparacion #" << r.getNroReparacion()
                     << " - Fecha: " << r.getFechaEntrega().toString()
                     << " - Tecnico: " << nombreTecnico
                     << " - Importe: $" << fixed << setprecision(2) << d.getImporte() << "\n";
        }

        if (cantidad >= 2)
        {
            cout << "Equipo #" << e.getNroEquipo() << " - " << e.getTipoEquipoString()
                 << " - " << e.getMarca() << " - " << e.getDescripcion() << endl << endl;
            cout << "  Cliente - CUIT: " << e.getCuit() << endl << endl;
            cout << "  Cantidad de reparaciones finalizadas:   " << cantidad << endl;
            cout << detalles.str();
            cout << "\n-----------------------------------------------------------------------------------------------" << endl;
            hayReincidentes = true;
        }
    }

    if (!hayReincidentes) cout << "No hay equipos reincidentes registrados en el periodo solicitado." << endl;

    delete[] vEquipos;
    delete[] vDetalles;
    delete[] vReparaciones;
    delete[] vEmpleados;
}
