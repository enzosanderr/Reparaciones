#include <cstring>
#include "cliente.h"
using namespace std;

Cliente::Cliente() : _tipoCliente(0), _eliminado(false) {
   _cuit[0] = '\0';
   _nombre[0] = '\0';
   _apellido[0] = '\0';
   _telefono[0] = '\0';
   _email[0] = '\0';
   _direccion[0] = '\0';
}

Cliente::Cliente(string cuit, string nombre, string apellido,
                 string telefono, string email, string direccion,
                 int tipoCliente)
   : _eliminado(false) {
   setCuit(cuit);
   setNombre(nombre);
   setApellido(apellido);
   setTelefono(telefono);
   setEmail(email);
   setDireccion(direccion);
   setTipoCliente(tipoCliente);
}

string Cliente::getCuit() const { return string(_cuit); }
void Cliente::setCuit(string cuit) {
   strncpy(_cuit, cuit.c_str(), sizeof(_cuit) - 1);
   _cuit[sizeof(_cuit) - 1] = '\0';
}

string Cliente::getNombre() const { return string(_nombre); }
void Cliente::setNombre(string nombre) {
   strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
   _nombre[sizeof(_nombre) - 1] = '\0';
}

string Cliente::getApellido() const { return string(_apellido); }
void Cliente::setApellido(string apellido) {
   strncpy(_apellido, apellido.c_str(), sizeof(_apellido) - 1);
   _apellido[sizeof(_apellido) - 1] = '\0';
}

string Cliente::getTelefono() const { return string(_telefono); }
void Cliente::setTelefono(string telefono) {
   strncpy(_telefono, telefono.c_str(), sizeof(_telefono) - 1);
   _telefono[sizeof(_telefono) - 1] = '\0';
}

string Cliente::getEmail() const { return string(_email); }
void Cliente::setEmail(string email) {
   strncpy(_email, email.c_str(), sizeof(_email) - 1);
   _email[sizeof(_email) - 1] = '\0';
}

string Cliente::getDireccion() const { return string(_direccion); }
void Cliente::setDireccion(string direccion) {
   strncpy(_direccion, direccion.c_str(), sizeof(_direccion) - 1);
   _direccion[sizeof(_direccion) - 1] = '\0';
}

int Cliente::getTipoCliente() const { return _tipoCliente; }
void Cliente::setTipoCliente(int tipoCliente) { _tipoCliente = tipoCliente; }

string Cliente::getTipoClienteString() const {
   return _tipoCliente == 1 ? "Particular" : "Empresa";
}

bool Cliente::getEliminado() const { return _eliminado; }
void Cliente::setEliminado(bool eliminado) { _eliminado = eliminado; }
