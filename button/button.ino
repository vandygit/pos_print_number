#include <SoftwareSerial.h>
SoftwareSerial mser(11, 10); // RX, TX

void setup() {
  byte cutstr_set[]= {29,86,65,0};     // Продвинуть и обрезать 
  Serial.begin(19200);
  mser.begin(19200);
  randomSeed(analogRead(0));
  pinMode(5, INPUT); // Емкостной датчик
  pinMode(3, INPUT_PULLUP); // Кнопка
  Serial.println("Инициализация");
  mser.println("Initializations...");
  delay(1000);
  mser.println("OK. Ready");
  mser.write(cutstr_set,4); // отрезаем
}


byte logo1[] = {28,112,1,0}; // Печать логотипа 1
byte logo2[] = {28,112,2,0}; // Печать логотипа 2
byte logo3[] = {28,112,3,0}; // Печать логотипа 3
byte logo4[] = {28,112,4,0}; // Печать логотипа 4
byte logo5[] = {28,112,5,0}; // Печать логотипа 5
byte mzstr[] = {27,51,0};     // Межстрочный интервал = 0
byte cutstr[]= {29,86,65,0};     // Продвинуть и обрезать 


char cp866[] = "\217\340\250\242\245\342"; // текст "Привет" в кодировке CP-866.

char mydigits[10][11][7] = {{" *****","*******","**   **","**   **","**   **","**   **","**   **","**   **","**   **","*******"," *****"},{"  *"," **","***"," **"," **"," **"," **"," **"," **"," **","****"},{" *****","*******","**   **","     **","    **","   **","  **"," **","**","*******","*******"},{" *****","*******","**   **","     **","   ***","   ****","     **","     **","**   **","*******"," *****"},{"     *","    **","   ***","  ****"," ** **","**  **","*******","*******","   ***","   ***","   ***"},{"*******","*******","**","**","******","*******","     **","     **","**   **","*******"," *****"},{" *****","*******","**   **","**","******","*******","**   **","**   **","**   **","*******"," *****"},{"*******","*******","     **","     **","    **","   **","  **","  **","  **","  **","  **"},{" *****","*******","**   **","**   **"," *****","*******","**   **","**   **","**   **","*******"," *****"},{" *****","*******","**   **","**   **","**   **","*******"," ******","     **","**   **","*******"," *****"}};

int x = 0;
byte i=0;
byte j=0;
int pos1=0;   // первая цифра (десяток) в очереди
int pos2=0;   // вторая цифра (десяток) в очереди
long gnum = 1; // порядковый номер печати чека в очереди
String gnumstr = "";
String pos1str = "";
String pos2str = "";
bool flag = false;
uint32_t btnTimer = 0;


void loop() {
  // читаем инвертированное значение для удобства

  // КНОПКА НАЖАТА
  bool btnState = !digitalRead(3); // КНОПКА НАЖАТА
  if (btnState && !flag && millis() - btnTimer > 100) {
    btnTimer = millis();
    Serial.println("press and print logo1");
    
    mser.write(mzstr,3); // Устанавливаем межстрочный интервал 0
    mser.write(logo1,4); // Печатаем Лого1
    mser.print("                                              ");
    flag = true;
  }
  
  // КНОПКА ОТПУЩЕНА
  if (!btnState && flag) {   // КНОПКА ОТПУЩЕНА
    flag = false;
    btnTimer = millis();
    Serial.println("release");
  
    gnumstr = String(gnum);
    if (gnumstr.length() == 1) gnumstr = "0" + gnumstr;

    pos1str = gnumstr.charAt(0);
    pos2str = gnumstr.charAt(1);

    mser.println(pos1str + pos2str);
    
    pos1 = pos1str.toInt();
    pos2 = pos2str.toInt();

    

    
    for (i = 0; i < 11; i++) { //  цикл перебор строк 

       mser.print("       "); // печатаем слева 7 пробела
              
       for (j = 0; j < 7; j++) {  // цикл столбцы - символы в строке 1го символа
          if ( mydigits[pos1][i][j] == '*') { mser.write(char(254)); mser.write(char(254));}
          else { mser.write(char(32)); mser.write(char(32));}
       }
       
       mser.print("      "); // печатаем 6 пробелп между символами
        
       for (j = 0; j < 7; j++) {  // цикл столбцы - символы в строке 2го символа
          if ( mydigits[pos2][i][j] == '*')  { mser.write(char(254)); mser.write(char(254));}
          else { mser.write(char(32)); mser.write(char(32));}
       }
       
       mser.println(); // переводим строку для печати следующей строки
    }
    
    
    mser.println("________________________________________________");
    mser.write(logo2,4); // Печатаем Лого2
    mser.write(cutstr,4); // отрезаем
 
   gnum++; //Увеличиваем на 1 номер в очереди
   if (gnum == 100) gnum = 1; // если номер ==100 то  начинаем с 1
    
  }
  
 
}
