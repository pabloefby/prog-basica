//PIA PROGRAMACION BASICA
//JORGE PABLO FLORES BLANCO 1923061

#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>

using namespace std;

struct {

	int nord; //numero de orden
	char nomdis[40]; //nombre de disfraz
	char codpr[40]; //codigo de producto
	char talla[3]; //talla
	int precio; //precio de disfraz

}datos[50];

void imprimir();

int cont; //guardara los indices de ordenes
int ordnum; //numero de orden maximo
int total=0; //guarda el total de los precios


int main() {
	int i = 0; //el contador de cada orden
	while (1) {
		char op; //opcion para elegir la opcion
		
				//ingresar ordenes
		
		int opo = 1;//mantener el ciclo de preguntar ordenes
		char preg;//preg es para saber si quiere registrar otra orden

		char tal; // tal para seleccionar la talla
		int sig; //se mantiene en bucle si va a opcion default

				//validar codigo de producto
		int codascii, otraval;   //codascii guarda el valor numerico del caracter, otraval valida para salir del while
		int val = 1, codcorr; //val mantiene el do while para que solo sean 4 caracteres, codcorr sigue pidiendo el codigo si es que contiene caracteres no validos
	
		
				//eliminar ordenes
		int borrar; //el indice de cual orden se desea eliminar


				//guardar en archivo
		char conf; //pregunta sobre si desea guardar el archivo, dato a validar sino
		
		system("CLS");

		cout << "------MENU------ \nSeleccione por favor la opcion que desee:"<<endl;
		cout << "1)Ingresar ordenes"<<endl;
		cout << "2)Eliminar ordenes" << endl;
		cout << "3)Mostrar lista de ordenes" << endl;
		cout << "4)Salir del programa" << endl;

		cin >> op;

		switch (op) {
		case '1':

			while (opo == 1) {

				system("CLS");
				cin.ignore();
	
				cout << "Numero de orden " << i+1<<endl; 
				datos[i].nord = i+1;

				cout << "Ingrese el nombre del disfraz: ";
				cin.getline(datos[i].nomdis, 40);

				codcorr = 1; 

				while (codcorr == 1) {
					val = 1;
					do {
						cout << "Ingrese el codigo del disfraz: ";
						cin >> datos[i].codpr;

						if ((strlen(datos[i].codpr)) != 4) {

							cout << "\n[ERROR] El codigo solo puede contener 4 caracteres." <<endl<<endl;
						}
						else {
							val++;
						}

					} while (val == 1);

					otraval = 0;

					for (int k = 0; k < 4; k++) {

						codascii = int(datos[i].codpr[k]);

						if ((codascii > 57) || (codascii < 48)) {

							cout << "\n[ERROR] El codigo solo debe tener numeros." << endl<<endl;
							k = k + 5;
							otraval++;
						}

					}

					if (otraval == 0) {
						codcorr++;
					}

				}

				sig = 1;

				while (sig == 1) {

					cout << "Seleccione una talla: \n1)CH \n2)M \n3)G \n4)XG" << endl;
					cin >> tal;

					switch (tal) {

					case '1':
						strcpy_s(datos[i].talla, "CH");
						sig++;
						break;
					case '2':
						strcpy_s(datos[i].talla, "M");
						sig++;
						break;
					case '3':
						strcpy_s(datos[i].talla, "G");
						sig++;
						break;
					case '4':
						strcpy_s(datos[i].talla, "XG");
						sig++;
						break;
					default:
						cout << "\n[ERROR] No ingreso una opcion correcta, intentelo nuevamente" << endl << endl;
						break;
					}
				}

				do {
					cout << "Ingrese el precio del disfraz: ";
					cin >> datos[i].precio;

					if (datos[i].precio < 0) {

						cout << "\n[ERROR] El precio no puede ser menor que 0" << endl<<endl;
					}
				} while (datos[i].precio < 0);

				total = total + datos[i].precio;
				cout << "\nSubtotal: " << total<<endl<<endl;
				cont = i;
				ordnum = i + 1;
				i++;

				do {
					cout << "Desea agregar otra orden? \n1)Si \n2)No" << endl;
					cin >> preg;

					if ((preg != '1') && (preg != '2')) {
						cout << "\n[ERROR] No ingreso una opcion correcta, intentelo nuevamente"<<endl<<endl;
					}
				} while ((preg != '1') && (preg != '2'));
				
				if (preg == '2') {
					
					opo++;
				}
				
			}

			break;

		case '2':
			system("CLS");

			imprimir();

			do {
				cout << "Ingrese el numero de orden del disfraz que desee eliminar: ";
				cin >> borrar;

				if (borrar < 1 || borrar > ordnum) {
					cout << "\n[ERROR] No existe ese numero de orden, intentelo nuevamente" <<endl<<endl;
				}

			} while ((borrar < 1) || (borrar > ordnum));

			borrar--;

			datos[borrar].nord = 0;
			strcpy_s(datos[borrar].nomdis, "");
			strcpy_s(datos[borrar].codpr, "");
			strcpy_s(datos[borrar].talla, "");
			total = total - datos[borrar].precio;
			datos[borrar].precio = 0;

			break;

		case '3':
			system("CLS");

			imprimir();

			system("pause");

			break;

		case '4':
			system("CLS");

			do {
				cout << "Antes de salir, desea guardar sus ordenes en un archivo? \n1)Si \n2)No" << endl;
				cin >> conf;

				if (conf != '1' && conf != '2') {
					cout << "\n[ERROR]No ha seleccionado una opcion valida, intentelo nuevamente" << endl<<endl;
				}
			} while (conf != '1' && conf != '2');

			if (conf == '1') {

				ofstream archivo;

				archivo.open("Ordenes.txt", ios::out);

				if (archivo.fail()) {

					cout << "\n[ERROR] El archivo no se pudo crear..."<<endl<<endl;
				}
				else {

					for (int p = 0; p <= cont; p++) {

						if (datos[p].nord!=0) {
							archivo << "-----------------------------------" << endl;
							archivo << "Numero de orden " << datos[p].nord << endl;
							archivo << "Nombre del disfraz: " << datos[p].nomdis << endl;
							archivo << "Codigo del disfraz:  " << datos[p].codpr << endl;
							archivo << "Talla: " << datos[p].talla << endl;
							archivo << "Precio: " << datos[p].precio << endl << endl;
						}
					}

					archivo << "PRECIO TOTAL: " << total;

					archivo.close();
				}

			}

			exit(0);
			break;

		default:
			cout << "\n[ERROR]No selecciono una opcion valida, intentelo nuevamente."<<endl<<endl;
			system("pause");
			break;

		}
	
	}
	return 0;
}

void imprimir() {

	for (int j = 0; j <= cont; j++) {

		if (datos[j].nord != 0) {
			cout << "-----------------------------------"<<endl;
			cout << "Numero de orden: " << datos[j].nord << endl;
			cout << "Nombre del disfraz: " << datos[j].nomdis << endl;
			cout << "Codigo del disfraz: " << datos[j].codpr<< endl;
			cout << "Talla: " << datos[j].talla << endl;
			cout << "Precio: " << datos[j].precio << endl << endl;
		}
	}

	cout << "PRECIO TOTAL: " << total<<endl<<endl;
}