Programa complementario a la práctica 2 de la asignatura de Estructura de Computadores.

En ésta práctica se diseña un procesador capaz de ejecutar pequeños programas. Para ello, disponemos de una ALU, señales de control y memorias. Dependiendo del Opcode, cada instrucción realizará una acción diferente en función de las señales de control.
Para la lectura humana, programaremos con un pseudo-ensamblador con etiquetas propio.

El propósito de éste código es:
  - Dado un programa con las instrucciones definidas, convertirlo automáticamente a lenguaje máquina para luego usar el fichero generado en Verilog.
A tener en cuenta:
  - El código tiene nulo control de errores, pues está pensado para uso particular y puntual.
  - El código acepta un mínimo formateo considerando espacios al principio de la línea.
  - En la misma línea de una etiqueta no puede haber otra instrucción. Si la hubiera, ésta debe ser escrita en la línea inmediata a dicha etiqueta.
  - El código es ineficaz, ya que recorre el fichero un total de tres veces.
