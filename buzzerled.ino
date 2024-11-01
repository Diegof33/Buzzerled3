// Buzzer
const int buzzerPin = 12;    // Pino do buzzer

// LED
const int ledPin = 8;       // Pino do LED

// Sensor ultrassônico frontal
const int trigPinFrente = 5;     // Pino TRIG do sensor frontal
const int echoPinFrente = 4;     // Pino ECHO do sensor frontal

// Sensor ultrassônico traseiro
const int trigPinTras = 3;      // Pino TRIG do sensor traseiro
const int echoPinTras = 2;      // Pino ECHO do sensor traseiro


bool alarmeAtivado = false; // Estado do alarme

void setup() {
  // Configurar os pinos como saídas ou entradas
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPinFrente, OUTPUT);
  pinMode(echoPinFrente, INPUT);
  pinMode(trigPinTras, OUTPUT);
  pinMode(echoPinTras, INPUT);

  // Inicializar o buzzer e o LED como desligados
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600); // Inicializar comunicação serial
}

void loop() {
  // Obter as distâncias dos dois sensores
  long distanciaFrente = medirDistancia(trigPinFrente, echoPinFrente);
  long distanciaTras = medirDistancia(trigPinTras, echoPinTras);

  // Exibir as distâncias no monitor serial
  Serial.print("Distância Frente: ");
  Serial.print(distanciaFrente);
  Serial.println(" cm");

  Serial.print("Distância Traseira: ");
  Serial.print(distanciaTras);
  Serial.println(" cm");

  // Verificar as distâncias dos dois sensores e ativar/desativar o alarme
  if (distanciaFrente <= 25 || distanciaTras <= 25) {
    ativarAlarme();
  } else {
    desativarAlarme();
  }

  delay(100);  // Pequeno atraso para evitar leituras rápidas
}

// Função para medir a distância usando um sensor ultrassônico
long medirDistancia(int trigPin, int echoPin) {
  // Enviar um pulso de 10 µs para o pino TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Ler o tempo do pulso ECHO
  long duracao = pulseIn(echoPin, HIGH);
  // Converter o tempo em distância (em cm)
  long distancia = duracao * 0.034 / 2;

  return distancia;
}

// Função para ativar o alarme
void ativarAlarme() {
  if (!alarmeAtivado) {
    Serial.println("Alarme ativado: Distância crítica!");
    digitalWrite(buzzerPin, HIGH);  // Liga o buzzer
    digitalWrite(ledPin, HIGH);     // Liga o LED
    alarmeAtivado = true;
  }
}

// Função para desativar o alarme
void desativarAlarme() {
  if (alarmeAtivado) {
    Serial.println("Alarme desativado: Distância segura.");
    digitalWrite(buzzerPin, LOW);   // Desliga o buzzer
    digitalWrite(ledPin, LOW);      // Desliga o LED
    alarmeAtivado = false;
  }
}
