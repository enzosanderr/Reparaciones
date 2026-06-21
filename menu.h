#pragma once

class Menu {
public:
   Menu();
   void run();

   virtual void mostrarOpciones() = 0;
   int seleccionarOpcion();
   virtual void ejecutarOpcion(int opcion) = 0;

protected:
   void setCantidadOpciones(int cantidad);
   int getCantidadOpciones();
   void pausar();

private:
   int _cantidadOpciones;
};
