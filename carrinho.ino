#include <Ultrasonic.h>

/**
 * Motor A
 */
#define M1_SPEED 5 
#define M1_IN1 3
#define M1_IN2 4

/**
 * Motor B
 */
#define M2_SPEED 6
#define M2_IN1 8
#define M2_IN2 7

/**
 * Sensor Ultrason
 */
#define ULTRASON_TRIGGER 10
#define ULTRASON_ECHO 11

#define POT_SPEED A0

Ultrasonic ultrasonic(ULTRASON_TRIGGER, ULTRASON_ECHO);

const int DISTANCIA_MINIMA = 20;

bool andando = false;
bool obstaculo = false;

void setup() {

	pinMode(POT_SPEED, INPUT);
  	
  	pinMode(M1_SPEED, OUTPUT);
  	pinMode(M1_IN1, OUTPUT);
  	pinMode(M1_IN2, OUTPUT);

  	pinMode(M2_SPEED, OUTPUT);
  	pinMode(M2_IN1, OUTPUT);
  	pinMode(M2_IN2, OUTPUT);

  	pinMode(ULTRASON_TRIGGER, OUTPUT);
  	pinMode(ULTRASON_ECHO, INPUT);

  	parar();
}

void loop() {

	velocidade();

	distancia();

	if (obstaculo) {

		parar();

	 	traz();
	 	delay(500);
	 	esquerda();
	 	delay(500);
	}

	frente();
}

void distancia() {
	float distancia = ultrasonic.Ranging(CM);

	obstaculo = distancia < DISTANCIA_MINIMA;

	delay(250);
}

void velocidade() {

	int velocidade = map(analogRead(POT_SPEED), 0, 1024, 0, 200);

	analogWrite(M1_SPEED, velocidade);
	analogWrite(M2_SPEED, velocidade);
}

void parar() {

	andando = false;

	m1_parar();
	m2_parar();
}

void frente() {

	andando = true;

	m1_frente();
	m2_frente();
}

void traz() {

	andando = false;

	m1_traz();
	m2_traz();
}

void esquerda() {

	andando = false;

	m1_traz();
	m2_frente();
}

void direita() {

	andando = false;

	m1_frente();
	m2_traz();
}

void m1_frente() {
	digitalWrite(M1_IN1, HIGH);
	digitalWrite(M1_IN2, LOW);
}

void m2_frente() {
	digitalWrite(M2_IN1, HIGH);
	digitalWrite(M2_IN2, LOW);
}

void m1_traz() {
	digitalWrite(M1_IN1, LOW);
	digitalWrite(M1_IN2, HIGH);
}

void m2_traz() {
	digitalWrite(M2_IN1, LOW);
	digitalWrite(M2_IN2, HIGH);
}

void m1_parar() {
	digitalWrite(M1_IN1, LOW);
	digitalWrite(M1_IN2, LOW);
}

void m2_parar() {
	digitalWrite(M2_IN1, LOW);
	digitalWrite(M2_IN2, LOW);
}