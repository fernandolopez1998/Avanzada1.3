#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "FID3Lib.h"

using namespace FID3Lib;

int main()
{
	
	std::vector<std::string> vectorJugadores;
	FID3 objetoFID3 = FID3(); 
	//FID3 objetoFID3 = FID3( 0.8, 0.1 ); //FID3(thetarR, thetaN)

	//---------------
	// Inserta Clases
	//---------------
	objetoFID3.agregaClase("Y");
	objetoFID3.agregaClase("N");

	//-----------------------------------------------------------------------
	// Lee documento(input) con elementos(jugadores) y sus clases resultantes
	// e ingresa estos datos de entrenamiento
    //-----------------------------------------------------------------------
	
	std::ifstream ip("data.csv");
	if (!ip.is_open()) std::cout << "ERROR: No se pudo abrir el archivo" << std::endl;
	//temperature
	std::string hot_s;
	std::string mild_s;
	std::string cold_s;
	double temp_hot;
	double temp_mild;
	double temp_cold;
	//wind 
	std::string weak_s;
	std::string strong_s;
	double wind_weak;
	double wind_strong;
	//traffic jam
	std::string short_s;
	std::string long_s;
	double traffic_short;
	double traffic_long;
	//clase
	std::string clase;
	Elemento elemento = Elemento();
	std::map<std::string, double> fuzzyTypes;
	while (ip.good())
	{
		getline(ip, hot_s, ',');
		getline(ip, mild_s, ',');
		getline(ip, cold_s, ',');
		getline(ip, weak_s, ',');
		getline(ip, strong_s, ',');
		getline(ip, long_s, ',');
		getline(ip, short_s, ',');
		getline(ip, clase, '\n');

		temp_hot = stod(hot_s);
		temp_mild = stod(mild_s);
		temp_cold = stod(cold_s);
		wind_weak = stod(weak_s);
		wind_strong = stod(strong_s);
		traffic_long = stod(long_s);
		traffic_short = stod(short_s);
		
		//---------
		// Elemento
		//---------
		elemento.setClase(clase);
		//Temperature
		fuzzyTypes = { {"hot",temp_hot}, {"mild",temp_mild}, {"cold",temp_cold} };
		elemento.setValoresDifusos(AtributoDifuso("Temperature", fuzzyTypes));
		//Wind
		fuzzyTypes = { {"weak",wind_weak}, {"strong",wind_strong} };
		elemento.setValoresDifusos(AtributoDifuso("Wind", fuzzyTypes));
		//TrafficJam
		fuzzyTypes = { {"long",traffic_long}, {"short",traffic_short} };
		elemento.setValoresDifusos(AtributoDifuso("TrafficJam", fuzzyTypes));
		
		objetoFID3.agregaElemento(elemento);
		
		elemento.clear();
		//std::cout << "--------------" << std::endl;
	}
	ip.close();

	//--------------------------------------------------------------------------
	// Genera arbol FID3 (con los datos de entrenamiento previamente ingresados)
	//--------------------------------------------------------------------------

	objetoFID3.generaArbolFID3(); //lo crea en memoria principal

	//----------------------------------------------------------------------
	// Clasificacion del arbol
	//----------------------------------------------------------------------

	// 
	Elemento jugador = Elemento();
	std::vector<Elemento> equipo = { elemento, elemento };
	objetoFID3.recorreArbolFID3(elemento);
	for (int i = 0; i < equipo.size(); i++) {
		// FALTA IMPLEMENTAR
		// Escribir un archivo
	}
	
	std::cout << "Libreria FID3" << std::endl;
}
