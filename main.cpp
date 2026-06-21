#include "app.h"
#include "empleadoManager.h"
#include "generarDatos.h"

int main() {
   EmpleadoManager().cargarInicialesSiVacio();

     //GeneradorDatos seeder;
     //seeder.sembrarTodo();

   App app;
   app.run();

   return 0;
}
