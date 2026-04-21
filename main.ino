char board[3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
String coordenada;
int fila, columna;
bool turno = 0; // 0=jugador "o", 1=jugador "x"
bool isGameOver=0; // 0=nadie ha ganado. 1=alguien ya ganó
char quienGano; // cuando alguien gane, aquí se guarda el jugador (x/o)
int moveCount; // cantidad de turnos jugados
void setup() {
  Serial.begin(9600);
  while(!Serial) {} // ciclo infinito para esperar a que esté lista la comunicación
}
//------------------------------------
void loop() {
  renderBoard();
  requestMove();
  verificaOcupado();
  turnos();
  checkWinner();
  anunciarGanador();

  // REVISAR TABLILLA LLENA
  if(moveCount == 9 && !isGameOver){
    Serial.println("\nGAME OVER. Nadie Ganó");
    renderBoard();
    reset();
  }
} // TERMINA FUNCIÓN LOOP
//------------------------------------

// FUNCIÓN PARA DIBUJAR EL TABLERO DE GATO
void renderBoard() {
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
void requestMove() {
  Serial.println("Escriba la coordenada:");
  while(Serial.available() < 2) {}
  fila = Serial.parseInt();
  columna = Serial.parseInt();
}

// VERIFICA SI LA CELDA ESTÁ OCUPADA
void verificaOcupado() {
  while(gato[fila][columna] != ' ') { // VERIFICA SI HAY UN CARACTER DIFERENTE DEL ESPACIO
    Serial.print("Celda ocupada. ");
    requestMove(); // vuelve a preguntar
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
moveCount++;
}

// REVISAR SI ALGUIEN GANÓ
void checkWinner() {
  for (int i=0; i<=2; i++) { // reviso fila por fila
    if (gato[i][0] != ' ' && gato[i][0] == gato[i][1] && gato[i][1] == gato[i][2]) {
      isGameOver = 1;
      quienGano = gato[i][0];
    }
  }
  for (int j=0; j<=2; j++) { // reviso columna por columna
    if (gato[0][j] != ' ' && gato[0][j] == gato[1][j] && gato[1][j] == gato[2][j]) {
      isGameOver = 1;
      quienGano = gato[0][j];
    }
  }
  if (gato[0][0] != ' ' && gato[0][0] == gato[1][1] && gato[1][1] == gato[2][2]) { // diagonal
    isGameOver = 1;
    quienGano = gato[0][0];
  }
  if (gato[0][2] != ' ' && gato[0][2] == gato[1][1] && gato[1][1] == gato[2][0]) { // otra diagonal
    isGameOver = 1;
    quienGano = gato[0][2];
  }
}


// FUNCIÓN PARA ANUNCIAR GANADOR SI ES QUE ALGUIEN GANÓ
void anunciarGanador() {
if (isGameOver) {
    Serial.print("\nFIN DEL JUEGO. GANADOR: ");
    Serial.print(quienGano);

    delay(500);
    renderBoard();

    Serial.println("Presione una tecla para continuar.\n");
    delay(2000);

    while(Serial.available() == 0){}

    while(Serial.available() > 0) {
      Serial.read();
    }

    reset();
  }
}

void reset() {
  delay(500);
  for(int i=0; i<=2; i++) { // borramos el contenido para jugar otra vez
        for(int j=0; j<=2; j++) {
          gato[i][j] = ' ';
        }
      }

    moveCount = 0;
    isGameOver = 0; // resetea el estado
    turno = 0;

  Serial.println("\n--- SISTEMA REINICIADO ---");
  Serial.println("Listo para una nueva partida.\n");
}