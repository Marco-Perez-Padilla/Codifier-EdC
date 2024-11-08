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

#include <iostream>
#include <regex>

#include "detections.h"

bool Detection::DetectArithmeticLogic (const std::string& line, std::smatch& result) {
  std::regex pattern (R"(^\s*(add|sub|and|or|not|negA|negB|eq)\s(R(?:1[0-5]|[0-9]))\s(R(?:1[0-5]|[0-9]))\s(R(?:1[0-5]|[0-9]))\b)");
  return std::regex_search(line, result, pattern);
}

bool Detection::DetectImmediate (const std::string& line, std::smatch& result) {
  std::regex pattern (R"(^\s*(li)\s([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\s(R(?:1[0-5]|[0-9]))\b)");
  return std::regex_search(line, result, pattern);
}

bool Detection::DetectJump (const std::string& line, std::smatch& result) {
  std::regex pattern (R"(^\s*(jmp|jz|jnz)\s(\w+))");
  return std::regex_search(line, result, pattern);
}


bool Detection::DetectLabel (const std::string& line, std::smatch& result) {
  std::regex pattern (R"(([A-aZ-z]+)\b)");
  return std::regex_search(line, result, pattern);
}

bool Detection::DetectNoOperation (const std::string& line, std::smatch& result) {
  std::regex pattern (R"(^\s*(nop)\b)");
  return std::regex_search(line, result, pattern);
}