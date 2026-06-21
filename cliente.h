#pragma once
#include <string>

class Cliente {
public:
   Cliente();
   Cliente(std::string cuit, std::string nombre, std::string apellido,
           std::string telefono, std::string email, std::string direccion,
           int tipoCliente);

   std::string getCuit() const;
   void setCuit(std::string cuit);

   std::string getNombre() const;
   void setNombre(std::string nombre);

   std::string getApellido() const;
   void setApellido(std::string apellido);

   std::string getTelefono() const;
   void setTelefono(std::string telefono);

   std::string getEmail() const;
   void setEmail(std::string email);

   std::string getDireccion() const;
   void setDireccion(std::string direccion);

   int getTipoCliente() const;
   void setTipoCliente(int tipoCliente);
   std::string getTipoClienteString() const;

   bool getEliminado() const;
   void setEliminado(bool eliminado);

private:
   char _cuit[15];
   char _nombre[20];
   char _apellido[20];
   char _telefono[20];
   char _email[40];
   char _direccion[50];
   int _tipoCliente;
   bool _eliminado;
};
