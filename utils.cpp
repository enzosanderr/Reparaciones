#include <iostream>
#include "utils.h"
using namespace std;

static string trim(const string &s) {
   size_t ini = s.find_first_not_of(" \t\r\n");
   if (ini == string::npos) return "";
   size_t fin = s.find_last_not_of(" \t\r\n");
   return s.substr(ini, fin - ini + 1);
}

string cargarCadena() {
   string texto;

   if (cin.peek() == '\n') {
      cin.ignore();
   }

   getline(cin, texto);

   return texto;
}

string cargarCadena(const string &prompt) {
   cout << prompt;
   return cargarCadena();
}

string cargarTexto(const string &prompt, int maxLen) {
   string texto;

   while (true) {
      cout << prompt;
      texto = trim(cargarCadena());

      if (texto.empty()) {
         cout << " > No puede estar vacio." << endl;
      } else if ((int)texto.size() > maxLen) {
         cout << " > Demasiado largo (maximo " << maxLen << " caracteres)." << endl;
      } else {
         return texto;
      }
   }
}

int cargarEntero(const string &prompt) {
   int valor;
   //cout << prompt;

   while (true) {
      cout << prompt;
      if (cin >> valor) {
         return valor;
      }
      cin.clear();
      cin.ignore(10000, '\n');
      cout << " > Debe ingresar un numero valido." << endl;
   }
}

float cargarFloat(const string &prompt) {
   float valor;

   while (true) {
      cout << prompt;
      if (cin >> valor) {
         return valor;
      }
      cin.clear();
      cin.ignore(10000, '\n');
      cout << " > Debe ingresar un numero valido." << endl;
   }
}

Fecha cargarFecha(const string &etiqueta) {
   Fecha f;

   cout << etiqueta << endl;
   do {
      f.setDia(cargarEntero("  Dia: "));
      f.setMes(cargarEntero("  Mes: "));
      f.setAnio(cargarEntero("  Anio: "));

      if (!f.esValida()) {
         cout << " > Fecha invalida (revise el dia segun el mes). Reintente." << endl;
      }
   } while (!f.esValida());

   return f;
}

