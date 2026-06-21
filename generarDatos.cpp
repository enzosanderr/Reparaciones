#include <iostream>
#include <cstdio>
#include "generarDatos.h"

using namespace std;

GeneradorDatos::GeneradorDatos()
    : _repoCliente(), _repoEmpleado(), _repoEquipo(), _repoReparacion(), _repoDetalle() {}

void GeneradorDatos::limpiarArchivos()
{
    FILE *f;
    f = fopen("clientes.dat", "wb"); if(f) fclose(f);
    f = fopen("empleados.dat", "wb"); if(f) fclose(f);
    f = fopen("equipos.dat", "wb"); if(f) fclose(f);
    f = fopen("reparaciones.dat", "wb"); if(f) fclose(f);
    f = fopen("detalleReparaciones.dat", "wb"); if(f) fclose(f);

    cout << " >> Archivos reseteados. Iniciando carga manual de 40 ordenes (A¤o 2026)..." << endl;
}

void GeneradorDatos::sembrarClientes()
{
    _repoCliente.crear(Cliente("20111111112", "Juan", "Gomez", "341100001", "juan@mail.com", "Av. Pellegrini 120", 1));
    _repoCliente.crear(Cliente("30222222223", "Smart Fit", "Sucursal Centro", "341100002", "info@smartfit.com", "Corrientes 500", 2));
    _repoCliente.crear(Cliente("27333333334", "Maria", "Rodriguez", "341100003", "maria@mail.com", "Bv. Orono 450", 1));
    _repoCliente.crear(Cliente("20444444445", "Carlos", "Lopez", "341100004", "carlos@mail.com", "San Martin 900", 1));
    _repoCliente.crear(Cliente("27555555556", "Ana", "Martinez", "341100005", "ana@mail.com", "Mendoza 320", 1));
    _repoCliente.crear(Cliente("30666666667", "Rosario Digital", "SRL", "341100006", "contacto@rosariodigital.com", "Urquiza 2010", 2));
    _repoCliente.crear(Cliente("20777777778", "Diego", "Garcia", "341100007", "diego@mail.com", "Santa Fe 800", 1));
    _repoCliente.crear(Cliente("27888888889", "Sofia", "Romero", "341100008", "sofia@mail.com", "San Juan 1100", 1));
    _repoCliente.crear(Cliente("30999999990", "Movil-TR", "SH", "341100009", "admin@moviltr.com", "Rondeau 400", 2));
    _repoCliente.crear(Cliente("20101010101", "Pablo", "Fernandez", "341100010", "pablo@mail.com", "Av. Alberdi 500", 1));
    _repoCliente.crear(Cliente("27111111111", "Laura", "Torres", "341100011", "laura@mail.com", "Cordoba 1500", 1));
    _repoCliente.crear(Cliente("20121212121", "Martin", "Sosa", "341100012", "martin@mail.com", "Rioja 1000", 1));
    _repoCliente.crear(Cliente("27131313131", "Lucia", "Perez", "341100013", "lucia@mail.com", "San Luis 1200", 1));
    _repoCliente.crear(Cliente("20141414141", "Esteban", "Quito", "341100014", "esteban@mail.com", "Laprida 800", 1));

    Cliente cBaja("27151515151", "Usuario", "Eliminado", "341000000", "baja@mail.com", "Falsa 123", 1);
    cBaja.setEliminado(true);
    _repoCliente.crear(cBaja);
}

void GeneradorDatos::sembrarEmpleados()
{
    _repoEmpleado.crear(Empleado("101", "Agustin Nahuel", "Parada"));
    _repoEmpleado.crear(Empleado("102", "Luz", "Campagnale"));
    _repoEmpleado.crear(Empleado("103", "Enzo Gabriel", "Sander"));
    _repoEmpleado.crear(Empleado("104", "Claudio Andres", "Arce"));
}

void GeneradorDatos::sembrarEquipos()
{
    // 20 Equipos con descripciones fisicas logicas segun el tipo (1 PC, 2 Note, 3 Imp, 4 Perif, 5 Cel)
    _repoEquipo.crear(Equipo(1, "20111111112", "Gabinete negro, panel frontal rayado", "Dell", 1, Fecha(2, 1, 2026)));
    _repoEquipo.crear(Equipo(2, "20111111112", "Mouse inalambrico blanco, sin receptor USB", "Logitech", 4, Fecha(2, 1, 2026)));
    _repoEquipo.crear(Equipo(3, "30222222223", "Gris plata, abolladura en esquina superior", "Lenovo", 2, Fecha(10, 1, 2026)));
    _repoEquipo.crear(Equipo(4, "27333333334", "Color azul, con funda de silicona transparente", "Samsung", 5, Fecha(15, 1, 2026)));
    _repoEquipo.crear(Equipo(5, "20444444445", "Negra, bandeja de papel trasera rota", "Epson", 3, Fecha(20, 1, 2026)));
    _repoEquipo.crear(Equipo(6, "27555555556", "Verde oscuro, con templado astillado", "Motorola", 5, Fecha(5, 2, 2026)));
    _repoEquipo.crear(Equipo(7, "30666666667", "Gabinete blanco, sin tapa lateral", "HP", 1, Fecha(12, 2, 2026)));
    _repoEquipo.crear(Equipo(8, "20777777778", "Negra mate, le falta la tecla ESC", "Asus", 2, Fecha(18, 2, 2026)));
    _repoEquipo.crear(Equipo(9, "27888888889", "Auriculares rojos, almohadillas muy gastadas", "HyperX", 4, Fecha(1, 3, 2026)));
    _repoEquipo.crear(Equipo(10, "30999999990", "Gris espacial, tapa trasera de vidrio trizada", "Apple", 5, Fecha(8, 3, 2026)));
    _repoEquipo.crear(Equipo(11, "20101010101", "Blanca, con manchas de tinta magenta en carcasa", "Brother", 3, Fecha(15, 3, 2026)));
    _repoEquipo.crear(Equipo(12, "27111111111", "Roja, faltan tornillos en la base", "Acer", 2, Fecha(22, 3, 2026)));
    _repoEquipo.crear(Equipo(13, "20121212121", "Gabinete gris viejo, boton encendido hundido", "Generica", 1, Fecha(5, 4, 2026)));
    _repoEquipo.crear(Equipo(14, "27131313131", "Celeste, tapa muy rayada", "Samsung", 5, Fecha(10, 4, 2026)));
    _repoEquipo.crear(Equipo(15, "20141414141", "Teclado mecanico negro, cable mallado deshilachado", "Redragon", 4, Fecha(15, 4, 2026)));
    _repoEquipo.crear(Equipo(16, "30222222223", "Gabinete SFF negro, marcas de uso normales", "Dell", 1, Fecha(2, 5, 2026)));
    _repoEquipo.crear(Equipo(17, "30222222223", "Plateada, falta una goma antideslizante abajo", "HP", 2, Fecha(10, 5, 2026)));
    _repoEquipo.crear(Equipo(18, "20444444445", "Negro, tapa trasera levantada", "Motorola", 5, Fecha(15, 5, 2026)));
    _repoEquipo.crear(Equipo(19, "30666666667", "Gris claro, sin cable USB ni de corriente", "Epson", 3, Fecha(1, 6, 2026)));

    // Equipo 20: Baja l¢gica
    Equipo eqBaja(20, "27151515151", "Carcasa inferior rajada y bisagras expuestas", "Lenovo", 2, Fecha(5, 6, 2026));
    eqBaja.setEliminado(true);
    _repoEquipo.crear(eqBaja);
}

void GeneradorDatos::sembrarReparacionesYDetalles()
{
    // ==========================================
    // MES: ENERO 2026 (1001 a 1007)
    // ==========================================
    Reparacion r1(1001, "20111111112", "101", Fecha(2, 1, 2026), Fecha(5, 1, 2026)); r1.setEstado(3);
    _repoReparacion.crear(r1);
    _repoDetalle.crear(DetalleReparacion(1001, 1, 25000, "Cambio de fuente ATX"));
    _repoDetalle.crear(DetalleReparacion(1001, 2, 8000, "Soldadura de switch click izquierdo"));

    Reparacion r2(1002, "30222222223", "102", Fecha(10, 1, 2026), Fecha(14, 1, 2026)); r2.setEstado(3);
    _repoReparacion.crear(r2);
    _repoDetalle.crear(DetalleReparacion(1002, 3, 60000, "Cambio de modulo de pantalla completo"));

    Reparacion r3(1003, "27333333334", "103", Fecha(15, 1, 2026), Fecha(18, 1, 2026)); r3.setEstado(3);
    _repoReparacion.crear(r3);
    _repoDetalle.crear(DetalleReparacion(1003, 4, 30000, "Cambio de bateria interna original"));

    Reparacion r4(1004, "20444444445", "104", Fecha(20, 1, 2026), Fecha(25, 1, 2026)); r4.setEstado(3);
    _repoReparacion.crear(r4);
    _repoDetalle.crear(DetalleReparacion(1004, 5, 22000, "Cambio de rodillo de arrastre de papel"));

    Reparacion r5(1005, "27555555556", "101", Fecha(22, 1, 2026), Fecha(26, 1, 2026)); r5.setEstado(3);
    _repoReparacion.crear(r5);
    _repoDetalle.crear(DetalleReparacion(1005, 6, 18000, "Cambio de flex de carga"));

    Reparacion r6(1006, "30666666667", "102", Fecha(25, 1, 2026), Fecha(28, 1, 2026)); r6.setEstado(3);
    _repoReparacion.crear(r6);
    _repoDetalle.crear(DetalleReparacion(1006, 7, 15000, "Mantenimiento y cambio de pasta termica"));

    Reparacion r7(1007, "20777777778", "103", Fecha(28, 1, 2026), Fecha(31, 1, 2026)); r7.setEstado(3);
    _repoReparacion.crear(r7);
    _repoDetalle.crear(DetalleReparacion(1007, 8, 35000, "Reconstruccion de bisagra izquierda"));

    // ==========================================
    // MES: FEBRERO 2026 (1008 a 1014)
    // ==========================================
    Reparacion r8(1008, "27888888889", "104", Fecha(2, 2, 2026), Fecha(5, 2, 2026)); r8.setEstado(3);
    _repoReparacion.crear(r8);
    _repoDetalle.crear(DetalleReparacion(1008, 9, 12000, "Soldadura de jack 3.5mm nuevo"));

    Reparacion r9(1009, "30999999990", "101", Fecha(5, 2, 2026), Fecha(10, 2, 2026)); r9.setEstado(3);
    _repoReparacion.crear(r9);
    _repoDetalle.crear(DetalleReparacion(1009, 10, 85000, "Reemplazo de tapa trasera y modulo de camaras"));

    Reparacion r10(1010, "20101010101", "102", Fecha(10, 2, 2026), Fecha(14, 2, 2026)); r10.setEstado(3);
    _repoReparacion.crear(r10);
    _repoDetalle.crear(DetalleReparacion(1010, 11, 25000, "Destape profundo de cabezales con ultrasonido"));

    Reparacion r11(1011, "27111111111", "103", Fecha(15, 2, 2026), Fecha(18, 2, 2026)); r11.setEstado(3);
    _repoReparacion.crear(r11);
    _repoDetalle.crear(DetalleReparacion(1011, 12, 40000, "Cambio de teclado completo"));

    Reparacion r12(1012, "20121212121", "104", Fecha(18, 2, 2026), Fecha(22, 2, 2026)); r12.setEstado(3);
    _repoReparacion.crear(r12);
    _repoDetalle.crear(DetalleReparacion(1012, 13, 14000, "Limpieza de contactos de memoria RAM y placa"));

    Reparacion r13(1013, "27131313131", "101", Fecha(22, 2, 2026), Fecha(25, 2, 2026)); r13.setEstado(3);
    _repoReparacion.crear(r13);
    _repoDetalle.crear(DetalleReparacion(1013, 14, 65000, "Cambio de modulo OLED"));

    // Reincidencia del equipo 1
    Reparacion r14(1014, "20111111112", "102", Fecha(26, 2, 2026), Fecha(28, 2, 2026)); r14.setEstado(3);
    _repoReparacion.crear(r14);
    _repoDetalle.crear(DetalleReparacion(1014, 1, 45000, "Instalacion de disco SSD 500GB y SO"));

    // ==========================================
    // MES: MARZO 2026 (1015 a 1022)
    // ==========================================
    Reparacion r15(1015, "20141414141", "103", Fecha(2, 3, 2026), Fecha(5, 3, 2026)); r15.setEstado(3);
    _repoReparacion.crear(r15);
    _repoDetalle.crear(DetalleReparacion(1015, 15, 18000, "Cambio de cable USB mallado"));

    Reparacion r16(1016, "30222222223", "104", Fecha(6, 3, 2026), Fecha(10, 3, 2026)); r16.setEstado(3);
    _repoReparacion.crear(r16);
    _repoDetalle.crear(DetalleReparacion(1016, 16, 35000, "Ampliacion de memoria RAM 16GB"));

    Reparacion r17(1017, "30222222223", "101", Fecha(12, 3, 2026), Fecha(16, 3, 2026)); r17.setEstado(3);
    _repoReparacion.crear(r17);
    _repoDetalle.crear(DetalleReparacion(1017, 17, 28000, "Reparacion de cooler interno y mantenimiento"));

    Reparacion r18(1018, "20444444445", "102", Fecha(18, 3, 2026), Fecha(20, 3, 2026)); r18.setEstado(3);
    _repoReparacion.crear(r18);
    _repoDetalle.crear(DetalleReparacion(1018, 18, 20000, "Bano quimico y resoldado de conectores"));

    // Reincidencia del equipo 4
    Reparacion r19(1019, "27333333334", "103", Fecha(22, 3, 2026), Fecha(24, 3, 2026)); r19.setEstado(3);
    _repoReparacion.crear(r19);
    _repoDetalle.crear(DetalleReparacion(1019, 4, 12000, "Colocacion de vidrio templado nuevo"));

    Reparacion r20(1020, "30666666667", "104", Fecha(25, 3, 2026), Fecha(28, 3, 2026)); r20.setEstado(3);
    _repoReparacion.crear(r20);
    _repoDetalle.crear(DetalleReparacion(1020, 19, 21000, "Cambio de engranaje traccion de papel"));

    Reparacion r21(1021, "20111111112", "101", Fecha(29, 3, 2026), Fecha(31, 3, 2026)); r21.setEstado(3);
    _repoReparacion.crear(r21);
    _repoDetalle.crear(DetalleReparacion(1021, 2, 10000, "Limpieza de sensor optico"));

    Reparacion r22(1022, "27555555556", "102", Fecha(30, 3, 2026), Fecha(2, 4, 2026)); r22.setEstado(3);
    _repoReparacion.crear(r22);
    _repoDetalle.crear(DetalleReparacion(1022, 6, 45000, "Cambio de placa secundaria inferior"));

    // ==========================================
    // MES: ABRIL 2026 (1023 a 1030)
    // ==========================================
    Reparacion r23(1023, "20777777778", "103", Fecha(5, 4, 2026), Fecha(8, 4, 2026)); r23.setEstado(3);
    _repoReparacion.crear(r23);
    _repoDetalle.crear(DetalleReparacion(1023, 8, 15000, "Reinstalacion de Windows y Drivers"));

    Reparacion r24(1024, "27888888889", "104", Fecha(10, 4, 2026), Fecha(14, 4, 2026)); r24.setEstado(3);
    _repoReparacion.crear(r24);
    _repoDetalle.crear(DetalleReparacion(1024, 9, 9000, "Cambio de potenciometro de volumen"));

    Reparacion r25(1025, "30999999990", "101", Fecha(15, 4, 2026), Fecha(18, 4, 2026)); r25.setEstado(3);
    _repoReparacion.crear(r25);
    _repoDetalle.crear(DetalleReparacion(1025, 10, 30000, "Reemplazo de bateria interna"));

    Reparacion r26(1026, "20101010101", "102", Fecha(20, 4, 2026), Fecha(24, 4, 2026)); r26.setEstado(3);
    _repoReparacion.crear(r26);
    _repoDetalle.crear(DetalleReparacion(1026, 11, 26000, "Reseteo de contador de almohadillas"));

    Reparacion r27(1027, "27111111111", "103", Fecha(22, 4, 2026), Fecha(26, 4, 2026)); r27.setEstado(3);
    _repoReparacion.crear(r27);
    _repoDetalle.crear(DetalleReparacion(1027, 12, 19000, "Cambio de pin de carga DC-IN"));

    Reparacion r28(1028, "20121212121", "104", Fecha(25, 4, 2026), Fecha(28, 4, 2026)); r28.setEstado(3);
    _repoReparacion.crear(r28);
    _repoDetalle.crear(DetalleReparacion(1028, 13, 22000, "Cambio de pila BIOS y configuracion"));

    Reparacion r29(1029, "27131313131", "101", Fecha(26, 4, 2026), Fecha(29, 4, 2026)); r29.setEstado(3);
    _repoReparacion.crear(r29);
    _repoDetalle.crear(DetalleReparacion(1029, 14, 18000, "Cambio de tapa trasera original"));

    Reparacion r30(1030, "20141414141", "102", Fecha(28, 4, 2026), Fecha(2, 5, 2026)); r30.setEstado(3);
    _repoReparacion.crear(r30);
    _repoDetalle.crear(DetalleReparacion(1030, 15, 12000, "Limpieza de switches mecanicos"));

    // ==========================================
    // MES: MAYO 2026 (1031 a 1037)
    // ==========================================
    // Reincidencia equipo 3
    Reparacion r31(1031, "30222222223", "103", Fecha(5, 5, 2026), Fecha(8, 5, 2026)); r31.setEstado(3);
    _repoReparacion.crear(r31);
    _repoDetalle.crear(DetalleReparacion(1031, 3, 25000, "Cambio de disco HDD a SSD 240GB"));

    Reparacion r32(1032, "30222222223", "104", Fecha(10, 5, 2026), Fecha(14, 5, 2026)); r32.setEstado(3);
    _repoReparacion.crear(r32);
    _repoDetalle.crear(DetalleReparacion(1032, 16, 15000, "Formateo e instalacion de ofimatica"));

    // Reincidencia de equipo 18
    Reparacion r33(1033, "20444444445", "101", Fecha(15, 5, 2026), Fecha(18, 5, 2026)); r33.setEstado(3);
    _repoReparacion.crear(r33);
    _repoDetalle.crear(DetalleReparacion(1033, 18, 38000, "Cambio de bateria original"));

    Reparacion r34(1034, "30666666667", "102", Fecha(20, 5, 2026), Fecha(25, 5, 2026)); r34.setEstado(3);
    _repoReparacion.crear(r34);
    _repoDetalle.crear(DetalleReparacion(1034, 19, 15000, "Reparacion de placa logica"));

    // EN PROCESO (Estado 2)
    Reparacion r35(1035, "20777777778", "103", Fecha(22, 5, 2026), Fecha(30, 5, 2026)); r35.setEstado(2);
    _repoReparacion.crear(r35);
    _repoDetalle.crear(DetalleReparacion(1035, 8, 45000, "Reballing de chip de video"));

    // EN PROCESO (Estado 2)
    Reparacion r36(1036, "27888888889", "104", Fecha(26, 5, 2026), Fecha(4, 6, 2026)); r36.setEstado(2);
    _repoReparacion.crear(r36);
    _repoDetalle.crear(DetalleReparacion(1036, 9, 12000, "Cambio de vincha superior"));

    // ==========================================
    // MES: JUNIO 2026 (1037 a 1040)
    // ==========================================
    // EN PROCESO (Estado 2)
    Reparacion r37(1037, "30999999990", "101", Fecha(2, 6, 2026), Fecha(10, 6, 2026)); r37.setEstado(2);
    _repoReparacion.crear(r37);
    _repoDetalle.crear(DetalleReparacion(1037, 10, 55000, "Cambio de modulo de pantalla"));

    // SIN INICIAR (Estado 1)
    Reparacion r38(1038, "20101010101", "102", Fecha(5, 6, 2026), Fecha(12, 6, 2026)); r38.setEstado(1);
    _repoReparacion.crear(r38);
    _repoDetalle.crear(DetalleReparacion(1038, 11, 25000, "Revision de error general"));

    // SIN INICIAR (Estado 1)
    Reparacion r39(1039, "27111111111", "103", Fecha(8, 6, 2026), Fecha(14, 6, 2026)); r39.setEstado(1);
    _repoReparacion.crear(r39);
    _repoDetalle.crear(DetalleReparacion(1039, 12, 10000, "Diagnostico de disco duro"));

    // BAJA LOGICA (Anulada)
    Reparacion r40(1040, "27151515151", "104", Fecha(1, 6, 2026), Fecha(5, 6, 2026)); r40.setEstado(1); r40.setEliminado(true);
    _repoReparacion.crear(r40);
    DetalleReparacion d40(1040, 20, 0, "Presupuesto rechazado, se devuelve equipo"); d40.setEliminado(true);
    _repoDetalle.crear(d40);
}

void GeneradorDatos::sembrarTodo()
{
    cout << "\n=== INICIANDO CARGA MANUAL CONTROLADA (SOLO 2026) ===" << endl;

    limpiarArchivos();
    sembrarClientes();
    sembrarEmpleados();
    sembrarEquipos();
    sembrarReparacionesYDetalles();

    cout << "=== BBDD GENERADA CON EXITO ===" << endl;
    cout << "Datos exactos listos para auditar listados e informes de la cursada." << endl << endl;
}
