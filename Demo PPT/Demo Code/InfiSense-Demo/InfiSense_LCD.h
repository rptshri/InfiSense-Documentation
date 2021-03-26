#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

long int prevMillis = 0;
long int currMillis = 0;
long int endMillis = 0;
long int sampleStartTime = 0;
long int sampleEndTime = 0;


int currentScreen = 0;

void LcdDisplayInit()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("!!Hello!!");
  lcd.setCursor(1, 1);
  lcd.print("LCD attached..");
  Serial.println("LCD Attached");
}

void setScreenZero()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("!!Hello!!");
  lcd.setCursor(1, 1);
  lcd.print("Screen Zero");
}

void setScreenOne()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("!!Hello!!");
  lcd.setCursor(1, 1);
  lcd.print("Screen One");
}

void setScreenTwo()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("!!Hello!!");
  lcd.setCursor(1, 1);
  lcd.print("Screen Two");
}

void setScreenThree()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("!!Hello!!");
  lcd.setCursor(1, 1);
  lcd.print("Screen Three");
}

void setScreenFour()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("!!Hello!!");
  lcd.setCursor(1, 1);
  lcd.print("Screen Four");
}

void Screen_update(int screenNumber);
void updateLcdDisplay(int _screens, long _screenChangeTime)
{
  
  currMillis = millis();
//  Serial.println(currMillis);
//  Serial.println(prevMillis);

  if (currMillis - prevMillis >= _screenChangeTime) //Maintenance Routine
  {
    Serial.println("Update LCD");
    Screen_update(currentScreen);
    currentScreen++;
    if (currentScreen >= _screens)
      currentScreen = 0;
    prevMillis = currMillis;
  }
//  Serial.println("Out");
}

void Screen_update(int screenNumber)
{
  switch (screenNumber)
  {
    case 0:
      setScreenZero();
      break;
    case 1:
      setScreenOne();
      break;
    case 2:
      setScreenTwo();
      break;
    case 3:
      setScreenThree();
      break;
    case 4:
      setScreenFour();
      break;
    default:
      setScreenZero();
      break;
  }
}
