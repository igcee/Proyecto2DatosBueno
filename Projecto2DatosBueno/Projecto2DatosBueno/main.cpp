#include <iostream>
#include <fstream>
#include <string>
#include "crud_paises.h"
#include "crud_ciudades.h"
#include "crud_habitaciones.h"
#include "crud_especialidades.h"
#include "crud_tratamientos.h"
#include "crud_diagnostico.h"
#include "crud_medicos.h"
#include "crud_citas.h"
#include "crud_pacientes.h"
#include "crud_hospitalizaciones.h"
#include "reportes.h"
using namespace std;

int main() {
	ArbolPais arbolilloPaises;
	ArbolCiudad arbolilloCiudades;
	ArbolPacientes arbolilloPacientes;
	ArbolMedicos arbolilloMedicos;
	ArbolEspecialidad arbolilloEsp;
	ArbolCitas arbolilloCitas;
	ArbolHabitaciones arbolilloHab;
	ArbolHospitalizaciones arbolilloHosp;
	ArbolDiagnostico arbolilloDiag;
	ArbolTratamiento arbolilloTrata;

	reportes rep;

	arbolilloPaises.leerArchivo("Paises.csv");
	arbolilloCiudades.leerArchivo("Ciudades.csv", arbolilloPaises);
	arbolilloPacientes.leerArchivo("Pacientes.csv", arbolilloCiudades);
	arbolilloEsp.leerArchivo("Especialidades.csv");
	arbolilloMedicos.leerArchivo("Medicos.csv", arbolilloEsp);
	arbolilloCitas.leerArchivo("Citas.csv", arbolilloPacientes, arbolilloMedicos);
	arbolilloHab.leerArchivo("Habitaciones.csv");
	arbolilloHosp.leerArchivo("Hospitalizaciones.csv", arbolilloPacientes, arbolilloHab, arbolilloMedicos);
	arbolilloDiag.leerArchivo("Diagnostico.csv");
	arbolilloTrata.leerArchivo("Tratamiento.csv");



	int opcionPrincipal = -1;
	while (opcionPrincipal != 5) {

		cout << endl;
		cout << " ===== MENU PRINCIPAL ===== " << endl;
		cout << "1. Insertar" << endl;
		cout << "2. Buscar" << endl;
		cout << "3. Modificar" << endl;
		cout << "4. Reportes" << endl;
		cout << "5. Salir" << endl;
		cin >> opcionPrincipal;
		cin.ignore();
		cout << endl;

		if (opcionPrincipal == 1) { // insertar
			int opcionInsertar = -1;
			while (opcionInsertar != 0) {
				cout << endl;
				cout << " ===== OPCIONES DE INSERTAR =====" << endl;
				cout << "1. Pais" << endl;
				cout << "2. Ciudad" << endl;
				cout << "3. Pacientes" << endl;
				cout << "4. Medicos" << endl;
				cout << "5. Especialidades" << endl;
				cout << "6. Citas" << endl;
				cout << "7. Habitaciones" << endl;
				cout << "8. Hospitalizacion" << endl;
				cout << "9. Diagnostico" << endl;
				cout << "10. Tratamiento" << endl;
				cout << "0. Volver" << endl;
				cout << "Opcion: ";
				cin >> opcionInsertar;
				cin.ignore(); // para el enter

				if (opcionInsertar == 1) {
					string codigopais, nombrepais;
					cout << "Codigo de pais: ";
					getline(cin, codigopais);
					cout << "Nombre de pais:";
					getline(cin, nombrepais);
					int codigopaisint = stoi(codigopais);
					arbolilloPaises.InsertarPais(codigopaisint, nombrepais);

				}
				else if (opcionInsertar == 2) {
					string codigopais, codigociudad, nombreciudad;
					cout << "Codigo de pais de la ciudad: ";
					getline(cin, codigopais);
					cout << "Codigo de ciudad: ";
					getline(cin, codigociudad);
					cout << "Nombre de ciudad:";
					getline(cin, nombreciudad);
					int codpint = stoi(codigopais);
					int codcint = stoi(codigociudad);
					arbolilloCiudades.InsertarCiudad(codpint, codcint, nombreciudad, arbolilloPaises);
				}
				else if (opcionInsertar == 3) {
					string id, nombre, fecha, telefono, codpais, codciudad, correo;
					cout << "Id paciente: ";
					getline(cin, id);
					cout << "Nombre: ";
					getline(cin, nombre);
					cout << "Fecha de nacimiento (aaaa-mm-dd): ";
					getline(cin, fecha);
					cout << "Telefono: ";
					getline(cin, telefono);
					cout << "Codigo de pais: ";
					getline(cin, codpais);
					cout << "Codigo de ciudad: ";
					getline(cin, codciudad);
					cout << "Correo: ";
					getline(cin, correo);
					int idint = stoi(id);
					int codpaisint = stoi(codpais);
					int codciudadint = stoi(codciudad);
					arbolilloPacientes.InsertarPaciente(idint, nombre, fecha, telefono, correo, codpaisint, codciudadint, arbolilloCiudades);
				}
				else if (opcionInsertar == 4) {
					string id, nombre, telefono, correo, idesp;
					cout << "Id medico: ";
					getline(cin, id);
					cout << "Nombre: ";
					getline(cin, nombre);
					cout << "Telefono: ";
					getline(cin, telefono);
					cout << "Correo: ";
					getline(cin, correo);
					cout << "Id especialidad: ";
					getline(cin, idesp);
					int idint = stoi(id);
					int idespint = stoi(idesp);
					arbolilloMedicos.InsertarMedico(idint, nombre, telefono, correo, idespint, arbolilloEsp);
				}
				else if (opcionInsertar == 5) {
					string id, nombre, descripcion;
					cout << "Id especialidad: ";
					getline(cin, id);
					cout << "Nombre: ";
					getline(cin, nombre);
					cout << "Descripcion: ";
					getline(cin, descripcion);
					int idint = stoi(id);
					arbolilloEsp.InsertarEspecialidad(idint, nombre, descripcion);
				}
				else if (opcionInsertar == 6) {
					string id, idpac, idmed, idesp, fecha, hora, motivo, estado;
					cout << "Id cita: ";
					getline(cin, id);
					cout << "Id paciente: ";
					getline(cin, idpac);
					cout << "Id medico: ";
					getline(cin, idmed);
					cout << "Id especialidad: ";
					getline(cin, idesp);
					cout << "Fecha (aaaa-mm-dd): ";
					getline(cin, fecha);
					cout << "Hora (hh:mm): ";
					getline(cin, hora);
					cout << "Motivo: ";
					getline(cin, motivo);
					cout << "Estado (0 pendiente, 1 confirmada): ";
					getline(cin, estado);
					int idint = stoi(id);
					int idpacint = stoi(idpac);
					int idmedint = stoi(idmed);
					int idespint = stoi(idesp);
					int estint = stoi(estado);
					arbolilloCitas.InsertarCita(idint, idpacint, idmedint, idespint, fecha, hora, motivo, estint, arbolilloPacientes, arbolilloMedicos);
				}
				else if (opcionInsertar == 7) {
					string id, numero, piso, tipo, estado;
					cout << "Id habitacion: ";
					getline(cin, id);
					cout << "Numero: ";
					getline(cin, numero);
					cout << "Piso: ";
					getline(cin, piso);
					cout << "Tipo (1 individual, 2 compartida, 3 UCI): ";
					getline(cin, tipo);
					cout << "Estado (0 disponible, 1 ocupada): ";
					getline(cin, estado);
					int idint = stoi(id);
					int numint = stoi(numero);
					//int pisoint = stoi(piso);
					int tipoint = stoi(tipo);
					int estadoint = stoi(estado);
					arbolilloHab.InsertarHabitacion(idint, numint, piso, tipoint, estadoint);
				}
				else if (opcionInsertar == 8) {
					string id, idpac, idhab, idmed, fechaingreso, fechasalida, motivo;
					cout << "Id hospitalizacion: ";
					getline(cin, id);
					cout << "Id paciente: ";
					getline(cin, idpac);
					cout << "Id habitacion: ";
					getline(cin, idhab);
					cout << "Id medico: ";
					getline(cin, idmed);
					cout << "Fecha de ingreso (aaaa-mm-dd): ";
					getline(cin, fechaingreso);
					cout << "Fecha de salida (0000 si no tiene): ";
					getline(cin, fechasalida);
					cout << "Motivo: ";
					getline(cin, motivo);
					int idint = stoi(id);
					int idpacint = stoi(idpac);
					int idhabint = stoi(idhab);
					int idmedint = stoi(idmed);
					arbolilloHosp.InsertarHospitalizacion(idint, idpacint, idhabint, idmedint, fechaingreso, fechasalida, motivo, arbolilloPacientes, arbolilloHab, arbolilloMedicos);
				}
				else if (opcionInsertar == 9) {
					string iddiag, nombrediag, descdiag;
					cout << "Id de diagnostico: ";
					getline(cin, iddiag);
					cout << "Nombre de diagnostico:";
					getline(cin, nombrediag);
					cout << "Descripcion de diagnostico:";
					getline(cin, descdiag);
					//int iddiagint = stoi(iddiag);
					arbolilloDiag.InsertarDiagnostico(iddiag, nombrediag, descdiag);

				}
				else if (opcionInsertar == 10) {
					string idtrata, nombretrata, desctrata, costotrata;
					cout << "Id de tratamiento: ";
					getline(cin, idtrata);
					cout << "Nombre de tratamiento:";
					getline(cin, nombretrata);
					cout << "Descripcion de tratamiento:";
					getline(cin, desctrata);
					cout << "Costo de tratamiento:";
					getline(cin, costotrata);
					int idtrataint = stoi(idtrata);
					double costotratadouble = stod(costotrata);
					arbolilloTrata.InsertarTratamiento(idtrataint, nombretrata, desctrata, costotratadouble);

				}
				else if (opcionInsertar == 0) {
					cout << "Volviendo al menu principal " << endl;

				}
				else {
					cout << "Opcion invalida" << endl;
				}

			}
		}

		else if (opcionPrincipal == 2)
		{
			int opcionBuscar = -1;

			while (opcionBuscar != 0)
			{
				cout << "===== Buscar =====" << endl;
				cout << "1. Pais" << endl;
				cout << "2. Ciudad" << endl;
				cout << "3. Pacientes" << endl;
				cout << "4. Medicos" << endl;
				cout << "5. Especialidades" << endl;
				cout << "6. Citas" << endl;
				cout << "7. Habitaciones" << endl;
				cout << "8. Hospitalizacion" << endl;
				cout << "9. Diagnostico" << endl;
				cout << "10. Tratamiento" << endl;
				cout << "0. Volver" << endl;
				cout << "Opcion: ";
				cin >> opcionBuscar;
				cin.ignore();

				if (opcionBuscar == 1)
				{
					string codigo;
					cout << "Codigo de pais: ";
					getline(cin, codigo);
					int codigoint = stoi(codigo);
					arbolilloPaises.BuscarMostrar(codigoint);
				}
				else if (opcionBuscar == 2)
				{
					string codpais, codciudad;
					cout << "Codigo de pais: ";
					getline(cin, codpais);
					cout << "Codigo de ciudad: ";
					getline(cin, codciudad);
					int codpint = stoi(codpais);
					int codcint = stoi(codciudad);
					arbolilloCiudades.BuscarMostrar(codpint, codcint, arbolilloPaises);
				}
				else if (opcionBuscar == 3)
				{

					string codpais, codciudad, id;
					cout << "Codigo de pais: ";
					getline(cin, codpais);
					cout << "Codigo de ciudad: ";
					getline(cin, codciudad);
					cout << "Id paciente: ";
					getline(cin, id);
					int codpaisint = stoi(codpais);
					int codciudadint = stoi(codciudad);
					int idint = stoi(id);
					arbolilloPacientes.BuscarMostrar(codpaisint, codciudadint, idint, arbolilloCiudades);

				}
				else if (opcionBuscar == 4)
				{

					string idesp, id;
					cout << "Id especialidad: ";
					getline(cin, idesp);
					cout << "Id medico: ";
					getline(cin, id);
					int idespint = stoi(idesp);
					int idint = stoi(id);
					arbolilloMedicos.BuscarMostrar(idespint, idint, arbolilloEsp);

				}
				else if (opcionBuscar == 5)
				{

					string id;
					cout << "Id especialidad: ";
					getline(cin, id);
					int idint = stoi(id);
					arbolilloEsp.BuscarMostrar(idint);

				}
				else if (opcionBuscar == 6)
				{
					string idpac, idmed, id;
					cout << "Id paciente: ";
					getline(cin, idpac);
					cout << "Id medico: ";
					getline(cin, idmed);
					cout << "Id cita: ";
					getline(cin, id);
					int idpacint = stoi(idpac);
					int idmedint = stoi(idmed);
					int idint = stoi(id);
					arbolilloCitas.BuscarMostrar(idpacint, idmedint, idint, arbolilloPacientes, arbolilloMedicos);
				}
				else if (opcionBuscar == 7)
				{

					string id;
					cout << "Id habitacion: ";
					getline(cin, id);
					int idint = stoi(id);
					arbolilloHab.BuscarMostrar(idint);

				}
				else if (opcionBuscar == 8)
				{
					string idpac, idhab, id;
					cout << "Id paciente: ";
					getline(cin, idpac);
					cout << "Id habitacion: ";
					getline(cin, idhab);
					cout << "Id hospitalizacion: ";
					getline(cin, id);
					int idpacint = stoi(idpac);
					int idhabint = stoi(idhab);
					int idint = stoi(id);
					arbolilloHosp.BuscarMostrar(idpacint, idhabint, idint, arbolilloPacientes, arbolilloHab);
				}
				else if (opcionBuscar == 9)
				{
					string iddiag;
					cout << "Id de diagnostico: ";
					getline(cin, iddiag);
					//int iddiagint = stoi(iddiag);
					arbolilloDiag.BuscarMostrar(iddiag);
				}
				else if (opcionBuscar == 10) {
					string idtrata;
					cout << "Id de tratamiento: ";
					getline(cin, idtrata);
					int idtrataint = stoi(idtrata);
					arbolilloTrata.BuscarMostrar(idtrataint);


				}


				else if (opcionBuscar == 0)
				{
					cout << "Volviendo al menu principal" << endl;
				}
				else
				{
					cout << "Opcion invalida." << endl;
				}
			}

		}
		else if (opcionPrincipal == 3) { // modificar
			int opcionModificar = -1;

			while (opcionModificar != 0)
			{
				cout << "===== Modificar =====" << endl;
				cout << "1. Pais" << endl;
				cout << "2. Ciudad" << endl;
				cout << "3. Pacientes" << endl;
				cout << "4. Medicos" << endl;
				cout << "5. Especialidades" << endl;
				cout << "6. Citas" << endl;
				cout << "7. Habitaciones" << endl;
				cout << "8. Hospitalizacion" << endl;
				cout << "9. Diagnostico" << endl;
				cout << "10. Tratamiento" << endl;
				cout << "0. Volver" << endl;
				cout << "Opcion: ";
				cin >> opcionModificar;
				cin.ignore();

				if (opcionModificar == 1)
				{
					string codigo, nombre;
					cout << "Codigo de pais: ";
					getline(cin, codigo);
					cout << "Nuevo nombre: ";
					getline(cin, nombre);
					int codigoint = stoi(codigo);
					arbolilloPaises.ModificarPais(codigoint, nombre);
				}
				else if (opcionModificar == 2)
				{
					string codpais, codciudad, nombre;
					cout << "Codigo de pais: ";
					getline(cin, codpais);
					cout << "Codigo de ciudad: ";
					getline(cin, codciudad);
					cout << "Nuevo nombre: ";
					getline(cin, nombre);
					int codpint = stoi(codpais);
					int codcint = stoi(codciudad);
					arbolilloCiudades.ModificarCiudad(codpint, codcint, nombre, arbolilloPaises);
				}
				else if (opcionModificar == 3)
				{

					string codpais, codciudad, idpaciente, telefono, correo;
					cout << "Codigo de pais: ";
					getline(cin, codpais);
					cout << "Codigo de ciudad: ";
					getline(cin, codciudad);
					cout << "Id de paciente: ";
					getline(cin, idpaciente);
					cout << "Nuevo telefono: ";
					getline(cin, telefono);
					cout << "Nuevo correo: ";
					getline(cin, correo);
					int codpaisint = stoi(codpais);
					int codciudadint = stoi(codciudad);
					int idpacienteint = stoi(idpaciente);
					arbolilloPacientes.ModificarPaciente(codpaisint, codciudadint, idpacienteint, telefono, correo, arbolilloCiudades);

				}
				else if (opcionModificar == 4)
				{

					string idesp, idmed, telefono, correo;
					cout << "Id especialidad: ";
					getline(cin, idesp);
					cout << "Id medico: ";
					getline(cin, idmed);
					cout << "Nuevo telefono: ";
					getline(cin, telefono);
					cout << "Nuevo correo: ";
					getline(cin, correo);
					int idespint = stoi(idesp);
					int idmedint = stoi(idmed);
					arbolilloMedicos.ModificarMedico(idespint, idmedint, telefono, correo, arbolilloEsp);

				}
				else if (opcionModificar == 5)
				{

					string idesp, nuevadesc;
					cout << "Id especialidad: ";
					getline(cin, idesp);
					cout << "Nueva descripcion: ";
					getline(cin, nuevadesc);
					int idespint = stoi(idesp);
					arbolilloEsp.ModificarEspecialidad(idespint, nuevadesc);

				}
				else if (opcionModificar == 6)
				{
					string idpac, idmed, idcita, motivo, estado;
					cout << "Id paciente: ";
					getline(cin, idpac);
					cout << "Id medico: ";
					getline(cin, idmed);
					cout << "Id cita: ";
					getline(cin, idcita);
					cout << "Nuevo motivo: ";
					getline(cin, motivo);
					cout << "Nuevo estado: ";
					getline(cin, estado);
					int idpacint = stoi(idpac);
					int idmedint = stoi(idmed);
					int idcitaint = stoi(idcita);
					int estint = stoi(estado);
					arbolilloCitas.ModificarCita(idpacint, idmedint, idcitaint, motivo, estint, arbolilloPacientes, arbolilloMedicos);
				}
				else if (opcionModificar == 7)
				{
					string idhab, estado;
					cout << "Id habitacion: ";
					getline(cin, idhab);
					cout << "Nuevo estado: ";
					getline(cin, estado);
					int idhabint = stoi(idhab);
					int estadoint = stoi(estado);
					arbolilloHab.ModificarHab(idhabint, estadoint);

				}
				else if (opcionModificar == 8)
				{
					string idpac, idhab, idhosp, motivo;
					cout << "Id paciente: ";
					getline(cin, idpac);
					cout << "Id habitacion: ";
					getline(cin, idhab);
					cout << "Id hospitalizacion: ";
					getline(cin, idhosp);
					cout << "Nuevo motivo: ";
					getline(cin, motivo);
					int idpacint = stoi(idpac);
					int idhabint = stoi(idhab);
					int idhospint = stoi(idhosp);
					arbolilloHosp.ModificarHosp(idpacint, idhabint, idhospint, motivo, arbolilloPacientes, arbolilloHab);
				}
				else if (opcionModificar == 9)
				{
					string iddiag, desc;
					cout << "Id de diagnostico: ";
					getline(cin, iddiag);
					cout << "Nueva descripcion: ";
					getline(cin, desc);
					//int iddiagint = stoi(iddiag);
					arbolilloDiag.ModificarDiag(iddiag, desc);
				}
				else if (opcionModificar == 10) {
					string idtrata, nom, desc, costo;
					cout << "Id de tratamiento: ";
					getline(cin, idtrata);
					cout << "Nuevo nombre: ";
					getline(cin, nom);
					cout << "Nueva descripcion: ";
					getline(cin, desc);
					cout << "Nuevo costo: ";
					getline(cin, costo);
					int idtrataint = stoi(idtrata);
					double costoint = stod(costo); // es double, no int, poner stod en lugar de stoi
					arbolilloTrata.ModificarTratamiento(idtrataint, nom, desc, costoint);


				}


				else if (opcionModificar == 0)
				{
					cout << "Volviendo al menu principal" << endl;
				}
				else
				{
					cout << "Opcion invalida." << endl;
				}
			}


		}

		else if (opcionPrincipal == 4) { // reportes
			int opcionReporte = -1;
			while (opcionReporte != 0) {
				cout << "===== Reportes =====" << endl;
				cout << "1. Lista de todos los paises" << endl;
				cout << "2. Lista de ciudades de un pais" << endl;
				cout << "3. Lista de todos los pacientes" << endl;
				cout << "4. Lista de todas las especialidades" << endl;
				cout << "5. Lista de habitaciones disponibles" << endl;
				cout << "6. Lista de habitaciones ocupadas" << endl;
				cout << "7. Lista de todas las hospitalizaciones" << endl;
				cout << "8. Lista de las hospitalizaciones de un medico" << endl;
				cout << "9. Lista de todos los medicos" << endl;
				cout << "10. Lista de los medicos de una especialidad" << endl;
				cout << "11. Lista de citas de una fecha" << endl;
				cout << "12. Lista de citas de una especialidad" << endl;
				cout << "13. Lista de citas de un medico" << endl;
				cout << "14. Lista de pacientes de un pais" << endl;
				cout << "15. Lista de pacientes de una ciudad de un pais" << endl;
				cout << "16. Lista de citas de un paciente" << endl;
				cout << "17. Lista de todos los diagnosticos" << endl;
				cout << "18. Lista de todos los tratamientos" << endl;
				cout << "0. Volver" << endl;
				cout << "Opcion: ";
				cin >> opcionReporte;
				cin.ignore();

				if (opcionReporte == 1) {
					rep.ReporteTodosPaises(arbolilloPaises);

				}
				else if (opcionReporte == 2) {
					string codp;
					cout << "Codigo de pais: " << endl;
					getline(cin, codp);
					int codpint = stoi(codp);
					rep.ReporteTodasCiudadesDePais(arbolilloCiudades, arbolilloPaises, codpint);
				}
				else if (opcionReporte == 3) {
					rep.ReporteTodosPacientes(arbolilloPacientes);

				}
				else if (opcionReporte == 4) {
					rep.ReporteTodasEspecialidades(arbolilloEsp);

				}
				else if (opcionReporte == 5) {
					rep.ReporteHabitaciones(arbolilloHab, 0);

				}
				else if (opcionReporte == 6) {
					rep.ReporteHabitaciones(arbolilloHab, 1);

				}
				else if (opcionReporte == 7) {
					rep.ReporteTodasHospitalizaciones(arbolilloHosp);
				}
				else if (opcionReporte == 8) {
					string idmed;
					cout << "Id de medico: ";
					getline(cin, idmed);
					int idmedint = stoi(idmed);
					rep.ReporteHospitalizacionesPorMedico(arbolilloHosp, arbolilloMedicos, idmedint);
				}
				else if (opcionReporte == 9) {
					rep.ReporteTodosMedicos(arbolilloMedicos);

				}
				else if (opcionReporte == 10) {
					string idesp;
					cout << "Id de especialidad: ";
					getline(cin, idesp);
					int idespint = stoi(idesp);
					rep.ReporteMedicosPorEspecialidad(arbolilloMedicos, arbolilloEsp, idespint);

				}
				else if (opcionReporte == 11) {
					string fecha;
					cout << "Fecha (dd/mm/aaaa): ";
					getline(cin, fecha);
					//rep.ReporteCitasPorFecha(arbolilloCitas, fecha);
				}
				else if (opcionReporte == 12) {
					string idesp;
					cout << "Id de especialidad: ";
					getline(cin, idesp);
					int idespint = stoi(idesp);
					//rep.ReporteCitasPorEspecialidad(arbolilloCitas, arbolilloEsp, idespint);

				}
				else if (opcionReporte == 13) {
					string idmed;
					cout << "Id de medico: ";
					getline(cin, idmed);
					int idmedint = stoi(idmed);
					//rep.ReporteCitasPorMedico(arbolilloCitas, arbolilloMedicos, idmedint|);

				}
				else if (opcionReporte == 14) {
					string codpais;
					cout << "Codigo de pais: ";
					getline(cin, codpais);
					int codpaisint = stoi(codpais);
					rep.ReportePacientesPorPais(arbolilloPacientes, arbolilloPaises, codpaisint);
				}
				else if (opcionReporte == 15) {
					string codpais, codciudad;
					cout << "Codigo de pais: ";
					getline(cin, codpais);
					cout << "Codigo de ciudad: ";
					getline(cin, codciudad);
					int codpaisint = stoi(codpais);
					int codciudadint = stoi(codciudad);
					//rep.ReportePacientesPorCiudad(arbolilloPacientes, arbolilloCiudades, arbolilloPaises, codpaisint, codciudadint);
				}
				else if (opcionReporte == 16) {
					string idpac;
					cout << "Id de paciente: ";
					getline(cin, idpac);
					int idpacint = stoi(idpac);
					//rep.ReporteCitasPorPaciente(arbolilloCitas, arbolilloPacientes, idpacint);
				}
				else if (opcionReporte == 17) {
					rep.ReporteTodosDiagnosticos(arbolilloDiag);
				}
				else if (opcionReporte == 18) {
					rep.ReporteTodosTratamientos(arbolilloTrata);
				}
				else if (opcionReporte == 0) {
					cout << "Volviendo al menu principal" << endl;

				}
				else {
					cout << "Opcion invalida." << endl;
				}

			}



		}
	}
}


