char gato[3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
String coordenada;
int fila, columna;
bool turno = 0; // 0=jugador "o", 1=jugador "x"
bool yaGano=0; // 0=nadie ha ganado. 1=alguien ya ganó
char quienGano; // cuando alguien gane, aquí se guarda el jugador (x/o)

void setup() {
  Serial.begin(9600);
  while(!Serial) {} // ciclo infinito para esperar a que esté lista la comunicación
}
//------------------------------------
void loop() {
  dibujarGato();
  preguntarCoord();
  verificaOcupado();
  turnos();
  revisarGanador();
  anunciarGanador();
} // TERMINA FUNCIÓN LOOP
//------------------------------------

// FUNCIÓN PARA DIBUJAR EL TABLERO DE GATO
void dibujarGato() {
  Serial.print("\n-------\n");
  for(int i=0; i<=2; i++) { // filas
      Serial.print("|");
      for(int j=0; j<=2; j++) { // columnas
        Serial.print(gato[i][j]);
        Serial.print("|");
      }
      Serial.print("\n-------\n");
  }
}

// FUNCIÓN PARA PREGUNTAR COORDENADA
void preguntarCoord() {
  Serial.println("Escriba la coordenada:");
  while(!Serial.available()) {}
  coordenada = Serial.readString();
  fila = coordenada.substring(0,1).toInt();
  columna = coordenada.substring(2,3).toInt();
  if (fila < 0 || fila > 2 || columna <0 || columna > 2) {
    Serial.print("Fuera de rango. ");
    preguntarCoord();
  }
}

// VERIFICA SI LA CELDA ESTÁ OCUPADA
void verificaOcupado() {
  while(gato[fila][columna] != ' ') { // VERIFICA SI HAY UN CARACTER DIFERENTE DEL ESPACIO
    Serial.print("Celda ocupada. ");
    preguntarCoord(); // vuelve a preguntar
  }
}

// REVISA DE QUIÉN ES EL TURNO Y COLOCA LA LETRA
void turnos() {
if (turno) {
  gato[fila][columna] = 'x';
} else {
  gato[fila][columna] = 'o';
}
turno = !turno; // intercambiamos el turno
}

// REVISAR SI ALGUIEN GANÓ
void revisarGanador() {
  for (int i=0; i<=2; i++) { // reviso fila por fila
    if (gato[i][0] != ' ' && gato[i][0] == gato[i][1] && gato[i][1] == gato[i][2]) {
      yaGano = 1;
      quienGano = gato[i][0];
    }
  }
  for (int j=0; j<=2; j++) { // reviso columna por columna
    if (gato[0][j] != ' ' && gato[0][j] == gato[1][j] && gato[1][j] == gato[2][j]) {
      yaGano = 1;
      quienGano = gato[0][j];
    }
  }
  if (gato[0][0] != ' ' && gato[0][0] == gato[1][1] && gato[1][1] == gato[2][2]) { // diagonal
    yaGano = 1;
    quienGano = gato[0][0];
  }
  if (gato[0][2] != ' ' && gato[0][2] == gato[1][1] && gato[1][1] == gato[2][0]) { // otra diagonal
    yaGano = 1;
    quienGano = gato[0][2];
  }
}

// FUNCIÓN PARA ANUNCIAR GANADOR SI ES QUE ALGUIEN GANÓ
void anunciarGanador() {
if (yaGano) {
    Serial.print("\nFIN DEL JUEGO. GANADOR: ");
    Serial.print(quienGano);
    dibujarGato();
    for(int i=0; i<=2; i++) { // borramos el contenido para jugar otra vez
      for(int j=0; j<=2; j++) {
        gato[i][j] = ' ';
      }
    }
    Serial.println("Presione una tecla para continuar.\n");
    yaGano = 0; // resetea el estado
    turno = !turno; // cambia el turno
    while(!Serial.available()) {}
    coordenada=Serial.readString(); // para que no se quede guardado nada en el "buffer"
  }
}
