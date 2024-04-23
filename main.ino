#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int currentScreen = 1; // Variable para controlar la pantalla actual
int state; // variable para controlar el nivel 1 de estado
float Ilim;
int Tlim;

int read_LCD_buttons() {
  int valor_ADC = analogRead(0);
  if (valor_ADC > 1000) return btnNONE;
  if (valor_ADC < 50)   return btnRIGHT;
  if (valor_ADC < 195)  return btnUP;
  if (valor_ADC < 380)  return btnDOWN;
  if (valor_ADC < 555)  return btnLEFT;
  if (valor_ADC < 790)  return btnSELECT;
  return btnNONE;
}

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  if (currentScreen == 1) {
    //Inicio
    lcd.setCursor(0, 0);
    lcd.print("> Monitorear");
    lcd.setCursor(0, 1);
    lcd.print("  Programar");
  } else if (currentScreen == 2) {
    //Inicio
    lcd.setCursor(0, 0);
    lcd.print("  Monitorear");
    lcd.setCursor(0, 1);
    lcd.print("> Programar");
  } else if (currentScreen == 3) {
    //Monitorear
    lcd.setCursor(0, 0);
    lcd.print("Monitor");
    lcd.setCursor(0, 1);
    lcd.print("I=");
    lcd.print(Ilim);
    lcd.setCursor(7,1);
    lcd.print("T=");
    lcd.print(Tlim);
  } else if (currentScreen == 4) {
    //Programar
    ///Select Corriente
    lcd.setCursor(0, 0);
    lcd.print("> Corriente Limite ");
    lcd.setCursor(0, 1);
    lcd.print("  Tiempo Arranque");
  } else if (currentScreen == 5) {
    //Programar 
    ///Select Tiempo
    lcd.setCursor(0, 0);
    lcd.print("  Corriente Limite ");
    lcd.setCursor(0, 1);
    lcd.print("> Tiempo Arranque");
  } else if (currentScreen == 6) {
    //Programar 
    ///Select Corriente
    ////Modificar Corriente
    lcd.setCursor(0, 0);
    lcd.print("Corriente Limite ");
    lcd.setCursor(0, 1);
    lcd.print("I=");
    lcd.print(Ilim);
  } else if (currentScreen == 7) {
    //Programar 
    ///Select Tiempo
    ////Modificar Tiempo
    lcd.setCursor(0, 0);
    lcd.print("Tiempo Arranque ");
    lcd.setCursor(0, 1);
    lcd.print("t(ms)=");
    lcd.print(Tlim);
  }

  int boton = read_LCD_buttons();

  switch (boton) {
    case btnUP:
      if(currentScreen == 2){
        currentScreen = 1;
      }
      if(currentScreen == 5){
        currentScreen = 4;
      }
      if(currentScreen == 6){
        Ilim += 0.1;
      }
      if(currentScreen == 7){
        Tlim += 100;
      }
      lcd.clear();
      delay(200);
      break;
    case btnDOWN:
      if(currentScreen == 1){
        currentScreen = 2;
      }
      if(currentScreen == 4){
        currentScreen = 5;
      }
      if(currentScreen == 6){
        Ilim -= 0.1;
      }
      if(currentScreen == 7){
        Tlim -= 100;
      }
      lcd.clear();
      delay(200);
      break;
    case btnRIGHT:
      //Desde Home a Monitorear o Programar
      switch (currentScreen) {
        case 1:
          currentScreen = 3;
          state = 1;
          break;
        case 2:
          currentScreen = 4;
          state = 1;
          break;
        case 4:
          if (state == 1) {
            currentScreen = 6;
            state = 2;
            break;
          }
          break;
        case 5:
          if (state == 1) {
            currentScreen = 7;
            state = 2;
            break;
          }
          break;
      }
      lcd.clear();
      delay(200);
      break;
    case btnLEFT:
      if(currentScreen == 3 || currentScreen == 4 || currentScreen == 5){
        currentScreen = 1;
        state = 0;
      }
      if(currentScreen == 6 || currentScreen == 7){
        currentScreen = 4;
        state = 1;
      }
      lcd.clear();
      delay(200);
      break;
  }
}