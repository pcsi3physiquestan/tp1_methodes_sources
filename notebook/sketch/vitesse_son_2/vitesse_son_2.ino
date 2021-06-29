// Ce programme peut fonctionner avec l'IDE Arduino/Tinkercad ou un programme Python adapté.
// Ce programme permet de mesurer plusieurs fois un temps de vol d'un signal ultrasons pour une distance d donnée.
// Il renvoie sur le port série les mesures de temps de vol directement.
// On peut imaginer modifier la distance de l'obstacle dans le temps mais attention :
// la mesure de temps n'est pas envoyée et la période d'échantillonage est relativement lente (0.5ms au moins + le temps de de vol)

const byte TRIGGER_PIN = 2;  // Pin où est branché la borne TRIG du détecteur
const byte ECHO_PIN = 3;  // Pin où est branché la borne ECHO du détecteur
const byte LED_PIN = 4;  // Pin où est branché la LED signalant la réception de donnée (Facultatif)

const unsigned long MEASURE_TIMEOUT = 25000UL;  // Timeout pour l'attente de l'écho

const int N_MEASURE_MAX = 5000;  // Nombre d'échantillons maximum

bool isPython = false;  // Pour adapter le programme à l'IDE Arduino et à un programme Python.
int n_ech;


void setup() {
  Serial.begin(115200);  // On ouvre la communication série
  // On prépare les PINs du détecteur
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  // On éteint la LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if(Serial.available()){  // L'arduino reçoit quelque chose.
    digitalWrite(LED_PIN, HIGH);  // Annonce que la communication est en cours
    delay(100);
    // Les lignes suivantes permettent de recevoir le nombre d'échantillon.
    // Il n'est pas nécessaire de comprendre les détails. La condition if sert à adapter la réception à l'IDE et à Python
    int type = Serial.peek();
    if(type == 80){  // Communication avec Python
      isPython = true;
      Serial.read();
      receive_int(n_ech);  // On récupère le nombre d'échantillons
    } else {  // Communication avec IDE/Tinkercad
      n_ech = Serial.parseInt();  // On récupère le nombre d'échantillons
      while(Serial.available()){Serial.read();}  // On vide le buffer
    }
    if (n_ech > 0) {
      n_ech = min (n_ech, N_MEASURE_MAX);
      for (int i=0; i<n_ech; i++) {
        long mesure = mesureT();  // On réalise la mesure du temps de vol.
        Serial.print(mesure);
        if (i < n_ech - 1) {
          Serial.print(",");
        }
        delay(100);
      }
    }
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }
}

long mesureT(){
  // Réalise la mesure du temps de vol
  // Les trois lignes suivantes génère l'impulsation émise
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  // On mesure le temps de vol
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  return measure;
}


void receive_int(int &ampl){ // Programme qui permet de recevoir un nombre entier depuis le programme Python
  char *c;        
  c = (char *)&ampl;
  while (Serial.available()==0) {};
  *(c+1)=Serial.read();
  while (Serial.available()==0) {};
  *c=Serial.read();
}
