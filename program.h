/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Estructura de Computadores
** Curso: 2º
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 07/11/2024

** Archivo program.h: Declaracion de los metodos de lectura y escritura del fichero de entrada y salida
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      07/11/2024 - Creacion del codigo
**/

#ifndef PROGRAM_H
#define PROGRAM_H


#include <iostream>
#include <regex>
#include <string>

class Program {
 private:
  std::vector<std::string> lines_;
  void Read (const std::string&);
 public:
  //Constructor
  Program(const std::string&);
  //Getter
  std::vector<std::string>& getLines () {return lines_;}
  //Methods
  int RegisterConvert (std::string&);
  void AddLine (std::string&);
  //Write methods
  void Write(const std::string&);
  void Format(const std::string&, const std::string&);
};

#endif