#include <iostream>
#include <iomanip>
#include <sstream>
#include "informeManager.h"
#include "utils.h"
using namespace std;

InformeManager::InformeManager()
    : _mgrReparacion(), _repoCliente(), _repoEmpleado(), _repoEquipo(),
      _repoReparacion(), _repoDetalle() {}

void InformeManager::recaudacionPorPeriodo()
{
    Fecha desde, hasta;

    Fecha fechaActual;
    fechaActual.setFechaActual();

    bool rangoValido = false;

    do
    {
        desde = cargarFecha("Fecha desde:");
        if (!desde.esValida())
        {
            cout << " > ERROR: Fecha 'Desde' invalida." << endl;
            continue;
        }

        hasta = cargarFecha("Fecha hasta:");
        if (!hasta.esValida())
        {
            cout << " > ERROR: Fecha 'Hasta' invalida." << endl;
            continue;
        }

        if(hasta.aNumero() > fechaActual.aNumero())
        {
            cout<<"\n > ERROR: La fecha 'hasta' no puede ser posterior a la fecha actual"<<endl;
            cout<<"\n Fecha Actual: "<<fechaActual.toString()<<endl<<endl;

        }
        else if (hasta.aNumero() < desde.aNumero())
        {
            cout << "\n > ERROR: La fecha 'Desde' debe ser anterior o igual a la fecha 'Hasta'.\n" << endl;
        }
        else
        {
            rangoValido = true;
        }
    }
    while (!rangoValido);

    int cant = _repoReparacion.getCantidadRegistros();

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
        for (int i = 0; i < cant; i++)
        {
            Reparacion r = _repoReparacion.leer(i);
            if (r.getEliminado()) continue;
            long f = r.getFechaEntrega().aNumero();
            if (r.getFechaEntrega().getAnio() == y && r.getFechaEntrega().getMes() == m &&
                    f >= desde.aNumero() && f <= hasta.aNumero())
            {
                subtotal += _mgrReparacion.calcularTotal(r.getNroReparacion());
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
    cout << left << setw(15) << "TOTAL"
         << "$ " << fixed << setprecision(2) << total << endl;
}

void InformeManager::recaudacionPorCliente()
{
    cout << "\n========= INFORME: RECAUDACION POR CLIENTE =========" << endl;

    Fecha desde = cargarFecha("Fecha desde:");
    Fecha hasta = cargarFecha("Fecha hasta:");

    Fecha fechaActual;
    fechaActual.setFechaActual();

    if(hasta.aNumero() > fechaActual.aNumero())
    {
        cout<<"\nERROR: La fecha 'hasta' no puede ser posterior a la fecha actual"<<endl;
        cout<<"\n Fecha Actual: "<<fechaActual.toString()<<endl<<endl;
        return;

    }
    else if (hasta.aNumero() < desde.aNumero())
    {
        cout << "\n > ERROR: La fecha 'Desde' debe ser anterior o igual a la fecha 'Hasta'.\n" << endl;
        return;
    }

    int cantC = _repoCliente.getCantidadRegistros();
    if (cantC == 0)
    {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    cout << "\nRECAUDACION POR CLIENTE ENTRE " << desde.toString()
         << " Y " << hasta.toString() << endl;
    cout << "======================================================================================" << endl;
    cout << left << setw(15) << "CUIT" << setw(20) << "APELLIDO"
         << setw(20) << "NOMBRE" << setw(15) << "TOTAL"
         << "REPARACIONES" << endl;
    cout << "======================================================================================" << endl;

    bool hay = false;
    float totalGeneral = 0;
    int cantR = _repoReparacion.getCantidadRegistros();

    for (int i = 0; i < cantC; i++)
    {
        Cliente c = _repoCliente.leer(i);
        if (c.getEliminado()) continue;

        float totalCliente = 0;
        int cantRep = 0;
        for (int j = 0; j < cantR; j++)
        {
            Reparacion r = _repoReparacion.leer(j);
            long f = r.getFechaEntrega().aNumero();
            if (!r.getEliminado() && r.getCuit() == c.getCuit() &&
                    f >= desde.aNumero() && f <= hasta.aNumero())
            {
                totalCliente += _mgrReparacion.calcularTotal(r.getNroReparacion());
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

    if (!hay)
    {
        cout << "No hubo recaudacion en el periodo." << endl;
        return;
    }
    cout << "======================================================================================" << endl;
    cout << ">>> TOTAL GENERAL: $" << fixed << setprecision(2) << totalGeneral << endl;
}

void InformeManager::reparacionesPorTipoEquipo()
{
    cout << "\n=== INFORME: REPARACIONES POR TIPO DE EQUIPO ===" << endl;
    Fecha desde = cargarFecha("Fecha desde:");
    Fecha hasta = cargarFecha("Fecha hasta:");
    Fecha fechaActual;
    fechaActual.setFechaActual();

    if(hasta.aNumero() > fechaActual.aNumero())
    {
        cout<<"\nERROR: La fecha 'hasta' no puede ser posterior a la fecha actual"<<endl;
        cout<<"\n Fecha Actual: "<<fechaActual.toString()<<endl<<endl;
        return;

    }
    else if (hasta.aNumero() < desde.aNumero())
    {
        cout << "\n > ERROR: La fecha 'Desde' debe ser anterior o igual a la fecha 'Hasta'.\n" << endl;
        return;
    }

    int cantidades[6] = {0};
    float recaudaciones[6] = {0};

    int cantD = _repoDetalle.getCantidadRegistros();
    for (int i = 0; i < cantD; i++)
    {
        DetalleReparacion d = _repoDetalle.leer(i);
        if (d.getEliminado()) continue;

        int posR = _repoReparacion.buscarPorNumero(d.getNroReparacion());
        if (posR == -1) continue;

        Reparacion r = _repoReparacion.leer(posR);
        long f = r.getFechaEntrega().aNumero();
        if (f < desde.aNumero() || f > hasta.aNumero()) continue;

        int posE = _repoEquipo.buscarPorNumero(d.getNroEquipo());
        if (posE == -1) continue;

        Equipo e = _repoEquipo.leer(posE);
        int t = e.getTipoEquipo();
        if (t >= 1 && t <= 5)
        {
            cantidades[t]++;
            recaudaciones[t] += d.getImporte();
        }
    }

    const char *tipos[] = {"", "PC ESCRITORIO", "NOTEBOOK", "IMPRESORA",
                           "PERIFERICO", "CELULAR"
                          };

    cout << "\nREPARACIONES POR TIPO DE EQUIPO ENTRE " << desde.toString()
         << " Y " << hasta.toString() << endl;
    cout << "=============================================================" << endl;
    cout << left << setw(20) << "TIPO" << setw(12) << "CANTIDAD"
         << "RECAUDACION" << endl;
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
}

void InformeManager::productividadEmpleados()
{
    cout << "\n=== INFORME: PRODUCTIVIDAD POR EMPLEADO ===" << endl;
    Fecha desde = cargarFecha("Fecha desde:");
    Fecha hasta = cargarFecha("Fecha hasta:");

    Fecha fechaActual;
    fechaActual.setFechaActual();

    if(hasta.aNumero() > fechaActual.aNumero())
    {
        cout<<"\nERROR: La fecha 'hasta' no puede ser posterior a la fecha actual"<<endl;
        cout<<"\n Fecha Actual: "<<fechaActual.toString()<<endl<<endl;
        return;

    }
    else if (hasta.aNumero() < desde.aNumero())
    {
        cout << "\n > ERROR: La fecha 'Desde' debe ser anterior o igual a la fecha 'Hasta'.\n" << endl;
        return;
    }

    int cantE = _repoEmpleado.getCantidadRegistros();
    if (cantE == 0)
    {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    cout << "\nPRODUCTIVIDAD ENTRE " << desde.toString() << " Y " << hasta.toString() << endl;
    cout << "============================================================================" << endl;
    cout << left << setw(10) << "LEGAJO" << setw(20) << "APELLIDO"
         << setw(20) << "NOMBRE" << setw(8) << "REPS"
         << "FACTURADO" << endl;
    cout << "============================================================================" << endl;

    int cantR = _repoReparacion.getCantidadRegistros();
    for (int i = 0; i < cantE; i++)
    {
        Empleado e = _repoEmpleado.leer(i);
        if (e.getEliminado()) continue;

        int reps = 0;
        float facturado = 0;
        for (int j = 0; j < cantR; j++)
        {
            Reparacion r = _repoReparacion.leer(j);
            long f = r.getFechaEntrega().aNumero();
            if (!r.getEliminado() && r.getLegajo() == e.getLegajo() &&
                    f >= desde.aNumero() && f <= hasta.aNumero())
            {
                reps++;
                facturado += _mgrReparacion.calcularTotal(r.getNroReparacion());
            }
        }

        cout << left << setw(10) << e.getLegajo()
             << setw(20) << e.getApellido()
             << setw(20) << e.getNombre()
             << setw(8) << reps
             << "$ " << fixed << setprecision(2) << facturado << endl;
    }
    cout << "============================================================================" << endl;
}

void InformeManager::equiposReincidentes()
{
    Fecha desde, hasta;

    Fecha fechaActual;
    fechaActual.setFechaActual();

    bool rangoValido = false;

    do
    {
        desde = cargarFecha("Fecha desde:");
        if (!desde.esValida())
        {
            cout << " > ERROR: Fecha 'Desde' invalida." << endl;
            continue;
        }

        hasta = cargarFecha("Fecha hasta:");
        if (!hasta.esValida())
        {
            cout << " > ERROR: Fecha 'Hasta' invalida." << endl;
            continue;
        }

        if(hasta.aNumero() > fechaActual.aNumero())
        {
            cout<<"\nERROR: La fecha 'hasta' no puede ser posterior a la fecha actual"<<endl;
            cout<<"\n Fecha Actual: "<<fechaActual.toString()<<endl<<endl;
            continue;
        }
        else if (hasta.aNumero() < desde.aNumero())
        {
            cout << "\n > ERROR: La fecha 'Desde' debe ser anterior o igual a la fecha 'Hasta'.\n" << endl;
        }
        else
        {
            rangoValido = true;
        }
    }
    while (!rangoValido);

    cout << "\nEQUIPOS REINCIDENTES ENTRE " << desde.toString()
         << " Y " << hasta.toString() << endl;
    cout << "==================================================================" << endl<<endl;

    int cantE = _repoEquipo.getCantidadRegistros();
    int cantD = _repoDetalle.getCantidadRegistros();
    bool hayReincidentes = false;

    for (int i = 0; i < cantE; i++)
    {
        Equipo e = _repoEquipo.leer(i);

        int cantidad = 0;
        ostringstream detalles;
        for (int j = 0; j < cantD; j++)
        {
            DetalleReparacion d = _repoDetalle.leer(j);
            if (d.getEliminado() || d.getNroEquipo() != e.getNroEquipo()) continue;

            int posR = _repoReparacion.buscarPorNumero(d.getNroReparacion());
            if (posR == -1) continue;

            Reparacion r = _repoReparacion.leer(posR);
            long f = r.getFechaEntrega().aNumero();
            if (f < desde.aNumero() || f > hasta.aNumero()) continue;

///HACER QUE EN CADA REPARACION SE MUESTRE QUE EMPLEADO LA REALIZO.

            cantidad++;
            detalles << "    Reparacion #" << r.getNroReparacion()
                     << " - " << r.getFechaEntrega().toString()
                     << " - $" << fixed << setprecision(2) << d.getImporte() << "\n";
        }

        if (cantidad >= 2)
        {
            cout << "Equipo #" << e.getNroEquipo() << " - " << e.getTipoEquipoString()
                 << " - " << e.getMarca() << " - " << e.getDescripcion() << endl<<endl;
            cout << "  Cliente - CUIT:" << e.getCuit()<<endl<<endl;
            cout << "  Cantidad de reparaciones:   " << cantidad << endl;
            cout << detalles.str();
            cout << "------------------------------------------------------------------" << endl;
            hayReincidentes = true;
        }
    }

    if (!hayReincidentes)
    {
        cout << "No hay equipos reincidentes en el periodo." << endl;
    }
}
