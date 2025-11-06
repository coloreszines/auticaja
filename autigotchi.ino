#include <OLED_I2C.h>
OLED myOLED(SDA, SCL);
extern uint8_t SmallFont[];

unsigned long lastMessageTime = 0;
unsigned long messageInterval = 60000; // 1 minuto entre mensajes
int currentMessage = 0;

// frases rotativas
String frases[] = {
  "no soy error",
  "soy algoritmo sensible",
  "mi energia es valida",
  "la diferencia no se corrige",
  "mi percepcion es precisa",
  "mi silencio tambien habla",
  "necesitas un descanso visual?",
  "recuerda hidratarte",
  "pensar distinto es don estructural",
  "la calma tambien es accion"
};
const int numFrases = sizeof(frases) / sizeof(frases[0]);

void setup() {
  myOLED.begin();
  myOLED.setFont(SmallFont);

  // introducción pausada
  myOLED.clrScr();
  myOLED.print("🛡 autiii v0.3", CENTER, 10);
  myOLED.print("sistema afectivo", CENTER, 25);
  myOLED.print("de combate", CENTER, 35);
  myOLED.update();
  delay(3500);

  myOLED.clrScr();
  myOLED.print("no soy error", CENTER, 25);
  myOLED.print("soy algoritmo sensible", CENTER, 35);
  myOLED.update();
  delay(3500);
}

void loop() {
  myOLED.clrScr();

  // hora simbólica basada en millis (puede sustituirse con RTC)
  int hour = (millis() / 3600000) % 24;

  String estado = "";
  String modoMensaje = "";

  if (hour >= 6 && hour < 12) {
    estado = "🌞 modo claro";
    modoMensaje = "mi energia es valida";
  } else if (hour >= 12 && hour < 18) {
    estado = "🌤 modo activo";
    modoMensaje = "la diferencia no se corrige";
  } else if (hour >= 18 && hour < 22) {
    estado = "🌒 modo suave";
    modoMensaje = "mi percepcion es precisa";
  } else {
    estado = "🌙 modo descanso";
    modoMensaje = "mi silencio tb habla";
  }

  // mostrar el modo siempre arriba
  myOLED.print(estado, CENTER, 5);
  myOLED.print(modoMensaje, CENTER, 20);

  // mostrar mensaje rotativo abajo cada minuto
  unsigned long currentTime = millis();
  if (currentTime - lastMessageTime > messageInterval) {
    lastMessageTime = currentTime;
    currentMessage = (currentMessage + 1) % numFrases; // siguiente frase
  }

  myOLED.print(frases[currentMessage], CENTER, 40);
  myOLED.update();

  delay(1000); // refresca cada segundo
}
