/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Estructura de Computadores
** Curso: 2º
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 07/11/2024

** Archivo detections.cc: Implementación de los metodos de deteccion de expresiones regulares
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      07/11/2024 - Creacion del codigo
**/

#ifndef Label_H
#define Label_H

#include <iostream>
#include <regex>

struct Detection {
  static bool DetectLabel (const std::string&, std::smatch&);
  static bool DetectJump (const std::string&, std::smatch&);
  static bool DetectNoOperation (const std::string&, std::smatch&);
  static bool DetectArithmeticLogic (const std::string&, std::smatch&);
  static bool DetectImmediate (const std::string&, std::smatch&);
};
#endif