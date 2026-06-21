#include "app.h"
#include "empleadoManager.h"

int main() {
   EmpleadoManager().cargarInicialesSiVacio();

   App app;
   app.run();

   return 0;
}
