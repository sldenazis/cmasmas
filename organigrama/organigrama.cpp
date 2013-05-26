/*  Undav ~ Algoritmos y Programación I
 *
 *       Autor: Santiago López Denazis
 *       Fecha: 2013/04/11
 * Descripción: ejercicio organigrama (https://sites.google.com/site/undavalgo1/assignments/organigrama)
 *
 */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

struct Empleado {
	string legajo;
	string nombre;
	string supervisor;
};

string solicitaFichero(){
	string file_name;

	cout << "Introduzca la ruta del fichero con el que quiere trabajar:" << endl;
	getline(cin,file_name);

	return file_name;
}

int lineasFichero(string fichero){
	/* Recibe el nombre del fichero como parámetro y devuelve la cantidad de líneas (o -1 si no puede leer el fichero)
	 * (pendiente 0: ignorar lineas con comentarios) ¡Hecho!
	 * (pendiente 1: encontrar una mejor forma de contar lineas) */
	const char* c_fichero = fichero.c_str();
	ifstream fileToCount(c_fichero);
	int file_lines = 0;

	if( !fileToCount ){
		cout << "Error al leer el fichero! (lineasFichero)" << endl;
		file_lines = -1;
	} else {
		string linea;
		while(getline(fileToCount,linea)){
			if( linea.substr(0,1) == "#" ){
				continue;
			} else {
				file_lines++;
			}
		}
		fileToCount.close();
	}

	cout << file_lines << endl;
	return file_lines;
}

void obtieneSubordinados( int indice, int cantidad_empleados, Empleado *array_empleados, string legajo){
	cout << array_empleados[indice].nombre << endl;

	for ( int em = 0; em < cantidad_empleados ; em++ ){
		if ( array_empleados[indice].legajo == array_empleados[em].supervisor ){
			obtieneSubordinados( em, cantidad_empleados, array_empleados, array_empleados[em].legajo );
		}
	}
	return;
}

Empleado insertaEmpleado(string registro){
	Empleado empleado;
	stringstream stream_line(registro);
	string columna;
	short num_columna = 0;

	while( getline(stream_line,columna,';') && stream_line != NULL){
		if ( num_columna == 0 ){
			empleado.legajo = columna;
			num_columna++;
		} else if ( num_columna == 1 ){
			empleado.nombre = columna;
			num_columna++;
		} else {
			empleado.supervisor = columna;
			num_columna = 0;
		}
	}

	return empleado;
}

int seleccionaEmpleado( Empleado *array_empleados, int cantidad_empleados ){
	string sel_emp;
	int indice;
	cout << "Lista de empleados:" << endl;

	for ( int em = 0; em < cantidad_empleados; em++ ){
		cout << "\t[" << em << "] " << array_empleados[em].nombre << endl;
	}

	cout << "Ingrese numero de empleado: ";
	getline(cin,sel_emp);
	cout << endl;

	stringstream to_int(sel_emp);
	to_int >> indice;

	return indice;
}

void dumpEmpleados(string fichero){

	int cantidad_empleados = lineasFichero(fichero);

	if ( cantidad_empleados > 0 ){
		Empleado array_empleados[cantidad_empleados];

		// carga de datos
		const char* c_fichero = fichero.c_str();
		ifstream fileEmpleados(c_fichero);

		if ( !fileEmpleados ){
			cout << "Error al leer el fichero! (dumpEmpleados)" << endl;
		} else {
			int pos_array = 0;
			string registro;
			while ( getline(fileEmpleados,registro) ){
				if ( registro.substr(0,1) == "#" ){
					continue;
				} else {
					array_empleados[pos_array] = insertaEmpleado(registro);
					pos_array++;
				}
			}
			/*for ( int em = 0; em < pos_array; em++){
				cout << array_empleados[em].nombre << endl;
			}*/
			int sel_emp = seleccionaEmpleado( array_empleados, cantidad_empleados);
			cout << "Usted seleccionó el empleado '" << array_empleados[sel_emp].nombre << "'." << endl;
			obtieneSubordinados( sel_emp, cantidad_empleados, array_empleados, array_empleados[sel_emp].legajo );

			fileEmpleados.close();
		}
	} else {
		cout << "Error." << endl;
	}

	return;
}

int main(){
	dumpEmpleados( solicitaFichero() );
	return 0;
}
