#pragma once
#include <string>
#include "fecha.h"

std::string cargarCadena();
std::string cargarCadena(const std::string &prompt);
std::string cargarTexto(const std::string &prompt, int maxLen);
int cargarEntero(const std::string &prompt);
float cargarFloat(const std::string &prompt);
Fecha cargarFecha(const std::string &etiqueta);
