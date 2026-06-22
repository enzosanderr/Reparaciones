# Sistema de Gestión de Reparación de Equipamiento Informático

Este proyecto es una aplicación de consola desarrollada como trabajo integrador para la materia Programación II de la universidad. Su objetivo principal es llevar el control integral de los equipos que ingresan a un local de servicio técnico, las reparaciones realizadas sobre ellos y el personal asignado.

## 🛠️ Características Principales

El sistema no depende de motores de bases de datos externas, sino que gestiona su propia persistencia de datos mediante archivos binarios (.dat) de forma nativa. 

Cuenta con los siguientes módulos de gestión:

* **Gestión de Clientes:** Registro completo de los dueños de los equipos (CUIT, nombre, contacto, categorización por particular/empresa). Permite listar, ordenar alfabéticamente, filtrar reparaciones activas y ver el historial del parque de equipos de cada cliente.
* **Gestión de Equipos:** Clasificación por tipo (PC de escritorio, notebook, impresora, periférico o celular) vinculados unívocamente al CUIT de su propietario.
* **Gestión de Empleados:** Control del personal técnico, asignación de carga de trabajo y registro del historial de reparaciones finalizadas por cada empleado.
* **Gestión de Reparaciones:** Es el núcleo del sistema. Permite asignar múltiples equipos de un mismo cliente a una única orden de reparación (número autoincremental), calculando importes individuales y totales. Cuenta con validaciones estrictas para evitar duplicidades o cruces de equipos entre clientes.

> **Nota arquitectónica:** El sistema implementa baja lógica en todas sus entidades principales, replicando la acción en cascada sobre los archivos de detalle para asegurar la integridad de la información sin perder registros físicos.

## 📊 Motor de Informes y Estadísticas

El software incluye un robusto sistema de reportes, filtrables por rangos de fechas personalizados para acotar el período de análisis:
* **Recaudación Mensual y por Cliente:** Desglose de la facturación del taller a lo largo del tiempo y por cliente específico.
* **Reparaciones por Tipo de Equipo:** Estadísticas para identificar qué sectores del parque informático generan mayores ingresos.
* **Productividad por Empleado:** Medición del impacto económico y desempeño de cada técnico operativo.
* **Control de Garantías (Equipos Reincidentes):** Detección automática de equipos físicos que han ingresado dos o más veces al taller, vital para auditorías de calidad.

## 🔐 Administración y Seguridad de Datos

Para garantizar la interoperabilidad y proteger la información, el programa cuenta con un módulo de administración dedicado:
* **Copias de Seguridad (Backups):** Generación manual, individualizada o masiva, de copias de seguridad alojadas en un directorio seguro (backups/).
* **Restauración Protegida:** Sistema de recuperación de datos validado mediante un código numérico de seguridad generado dinámicamente a partir del nombre del archivo, previniendo sobreescrituras accidentales o pérdidas de datos.
* **Exportación a CSV:** Motor de exportación que permite trasladar la información binaria a texto plano para planillas de cálculo (guardados en la carpeta exports/), procesando dinámicamente cálculos complejos como los importes totales en tiempo de exportación.

## 💻 Tecnologías Utilizadas
* **Lenguaje:** C++
* **Entorno de Desarrollo (IDE):** Code::Blocks
* **Estructura de Datos:** Manejo de memoria dinámica, Programación Orientada a Objetos (POO).
* **Persistencia:** Archivos Binarios (.dat) y manipulación de archivos de texto (.csv).

## Diagrama de Clases
[Diagrama de Clases](Diagrama.png)