const int MAX_LEVEL  = 100;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;

int velocity = 1000;

const int BuzzerPin = 12;

void initializeBuzzer() {
  pinMode(BuzzerPin, OUTPUT);
  noTone(BuzzerPin); // Certifique-se de que o buzzer esteja inicialmente desligado
}

void beep(int frequency, int duration) {
  tone(BuzzerPin, frequency, duration);
  delay(duration);
  noTone(BuzzerPin);
}

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  initializeBuzzer(); // Inicialize o buzzer

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void loop() {
  if (level == 1)
    generate_sequence(); // Gere uma sequência;

  if (digitalRead(A4) == LOW || level != 1) // Se o botão de início for pressionado ou você estiver ganhando
  {
    show_sequence(); // Mostre a sequência
    get_sequence(); // Aguarde a sua sequência
  }
}

void show_sequence() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  for (int i = 0; i < level; i++) {
    digitalWrite(sequence[i], HIGH);
    beep(1000, 300); // Beep no buzzer a 1000 Hz por 300 ms
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
}

void get_sequence() {
  int flag = 0; // Essa bandeira indica se a sequência está correta

  for (int i = 0; i < level; i++) {
    flag = 0;
    while (flag == 0) {
      if (digitalRead(A0) == LOW) {
        digitalWrite(5, HIGH);
        your_sequence[i] = 5;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(5, LOW);
      }

      if (digitalRead(A1) == LOW) {
        digitalWrite(4, HIGH);
        your_sequence[i] = 4;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(4, LOW);
      }

      if (digitalRead(A2) == LOW) {
        digitalWrite(3, HIGH);
        your_sequence[i] = 3;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(3, LOW);
      }

      if (digitalRead(A3) == LOW) {
        digitalWrite(2, HIGH);
        your_sequence[i] = 2;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(2, LOW);
      }
    }
  }
  right_sequence();
}

void generate_sequence() {
  randomSeed(millis()); // Dessa forma é realmente aleatório!!!

  for (int i = 0; i < MAX_LEVEL; i++) {
    sequence[i] = random(2, 6);
  }
}

void wrong_sequence() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    beep(500, 250); // Beep no buzzer a 500 Hz por 250 ms
    delay(250);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(250);
  }
  level = 1;
  velocity = 1000;
}

void right_sequence() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(250);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  beep(1000, 500); // Beep no buzzer a 1000 Hz por 500 ms
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(500);

  if (level < MAX_LEVEL)
    level++;
}
