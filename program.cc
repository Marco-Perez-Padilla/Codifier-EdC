/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Estructura de Computadores
** Curso: 2º
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 07/11/2024

** Archivo program.cc: Implementación de los metodos de lectura y escritura del fichero de entrada y salida
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      07/11/2024 - Creacion del codigo
**      08/11/2024 - Adicion de comentarios
**/


#include <cstdio> // std::remove
#include <map>
#include <fstream>

#include "program.h"
#include "detections.h"

/**
 * @brief Public constructor of Program class
 * @param string name of the file to be read
 */
Program::Program (const std::string& file) {
  Read(file);
}


/**
 * @brief Simple method to add lines in the vector of strings
 * @param string to be added
 */
void Program::AddLine (std::string& line) {
  lines_.push_back(line);
}


/**
 * @brief Method that, given a string in form: R[0-15], picks up only its decimal part as an int number
 * @param string register to be processed
 * @return Register decimal number
 */
int Program::RegisterConvert (std::string& reg) {
  if (reg.size() == 2) {
    return reg[1];
  } else if (reg.size() > 2) {
    std::string string_regd = std::to_string(reg[1]) + std::to_string(reg[2]);
    return std::stoi(string_regd);
  } 
  return -1;
}


/**
 * @brief Read method to process the file. It also converts it to binary while reading
 * @param string file to be read and codified
 */
void Program::Read (const std::string& file) {
  std::ifstream infile(file);

  std::string line;
  int line_number {1};
  
  // Mapping the position of the labels and their names
  std::map<std::string, int> label_positions;

  while (std::getline(infile, line)) {
    std::smatch result;

    // Detecting a jump
    if (Detection::DetectJump(line, result)) {
      std::string kind_of_jump = result[1].str();
      std::string label_name = result[2].str(); 
      std::string result_jump;

      if (kind_of_jump == "jmp") {
        result_jump = "010000";
      } else if (kind_of_jump == "jz") {
        result_jump = "010001";
      } else if (kind_of_jump == "jnz") {
        result_jump = "010010";
      }

      // Result will be opcode + the name of the label
      result_jump += label_name;
      line = result_jump;
    }
    
    // Detecting start of labels and adding them to the map
    std::regex label_pattern(R"(^(\w+):\s*)");  
    if (std::regex_search(line, result, label_pattern)) {
      std::string label_name = result[1].str();
      label_positions[label_name] = line_number;  
      continue; // In order not to add a blank line to lines_
    }
  
    // Detecting load immediates
    if (Detection::DetectImmediate(line, result)) {
      std::string load_immediate = "0001";
      std::string constant = result[2].str(); 
      std::string reg = result[3].str(); 

      int imm = std::stoi(constant);
      int regd = RegisterConvert (reg);
      
      // Converting to binary
      constant = std::bitset<8>(imm).to_string();
      reg = std::bitset<4>(regd).to_string();

      // Result
      std::string result_immediate = load_immediate + constant + reg;

      line = result_immediate;
    }

    // Detecting ALU operations
    if (Detection::DetectArithmeticLogic(line, result)) {
      std::string kind_of_operation = result[1].str();
      std::string reg_1 = result[2].str(); 
      std::string reg_2 = result[3].str(); 
      std::string reg_3 = result[4].str(); 

      // Getting decimal register number
      int reg_1d = RegisterConvert (reg_1);
      int reg_2d = RegisterConvert (reg_2);
      int reg_3d = RegisterConvert (reg_3);

      // Converting to binary
      reg_1 = std::bitset<4>(reg_1d).to_string();
      reg_2 = std::bitset<4>(reg_2d).to_string();
      reg_3 = std::bitset<4>(reg_3d).to_string();

      // A switch would be cleaner, by using an enum, but "not", "and" and "or" are reserved words in C++
      if (kind_of_operation == "eq") {
        kind_of_operation = "1000";
      } else if (kind_of_operation == "not") {
        kind_of_operation = "1001";
      } else if (kind_of_operation == "add") {
        kind_of_operation = "1010";
      } else if (kind_of_operation == "sub") {
        kind_of_operation = "1011";
      } else if (kind_of_operation == "and") {
        kind_of_operation = "1100";
      } else if (kind_of_operation == "or") {
        kind_of_operation = "1101";
      } else if (kind_of_operation == "negA") {
        kind_of_operation = "1110";
      } else if (kind_of_operation == "negB") {
        kind_of_operation = "1111";
      }

      // Result
      std::string result_arithmetic = kind_of_operation + reg_1 + reg_2 + reg_3;

      line = result_arithmetic;
    }

    // Detecting nop's
    if (Detection::DetectNoOperation(line, result)) {
      std::string result_no_op = "0000000000000000";
      line = result_no_op;
    }

    AddLine(line);
    ++line_number;
  }

  // Dealing with label names, and counting the total of lines
  int count {0};
  for (std::string& line : getLines()) {  
    std::smatch result;
    // If a label is detected, then:
    if (Detection::DetectLabel (line, result)) {
      // Get its name
      std::string label_name = result[1].str();
      // If it's on the map
      if (label_positions.find(label_name) != label_positions.end()) {
        // Adjusting line for it to shows as the given format.
        int label_line = label_positions[label_name] - 1 ;  
        std::string label_line_binary = std::bitset<10>(label_line).to_string();  
        // Replacing since the position 1 of the result until the length of the name by its binary position
        line.replace(result.position(1), label_name.length(), label_line_binary);
      }
    }
    ++count;
  }
  // While count is less than 1024, add 0's
  while (count < 1024) {
    std::string addition = "0000000000000000";
    lines_.push_back(addition);
    ++count;
  }
}


/**
 * @brief Method that writes in an output file the result, in binary
 */
void Program::Write(const std::string& out) {
  std::ofstream outfile (out);
  std::vector<std::string> total_lines = getLines();

  for (long unsigned int i {0}; i < total_lines.size(); ++i) {
    outfile << total_lines[i];
    // Add new lines until the final line
    if (i < lines_.size() - 1) { 
      outfile << std::endl;
    }
  }
  outfile.close();
}


/**
 * @brief Formats the binary output, placing "_" each 4 characters
 * @param string input file (the binary file)
 * @param string output file formatted
 */
void Program::Format(const std::string& in, const std::string& out) {
  std::ifstream infile(in);
  std::ofstream outfile(out);
  
  std::string line;
  int count {1};

  while (std::getline(infile, line)) {
    std::string formatted_line;
    for (long unsigned int i {0}; i < line.length(); i += 4) {
      formatted_line += line.substr(i, 4);
      if (i + 4 < line.length()) {
        formatted_line += "_";
      }
    }
    outfile << formatted_line;
    if (count < 1024) {
      outfile << std::endl;
    }
    ++count;
  }

  infile.close();
  outfile.close();

  // Deleting the binary file
  std::remove(in.c_str());
}
