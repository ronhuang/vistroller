/*******************************************************
 *
 * uOLED-160-GMD1 Driver for Arduino
 * Code: Oscar Gonzalez
 * August 2007
 *
 * www.bricogeek.com
 *
 *******************************************************/



#define OLED_BAUDRATE                   9600

#define OLED_RESETPIN                   10

#define OLED_INITDELAYMS                5000



// Initialisation routine

#define OLED_DETECT_BAUDRATE            0x55



// Drawing routines

#define OLED_CLEAR                      0x45

#define OLED_BKGCOLOR                   0x4B

#define OLED_COPYPASTE                  0x63



#define OLED_LINE                       0x4C

#define OLED_CIRCLE                     0x43

#define OLED_TRIANGLE                   0x47

#define OLED_POLYGON                    0x67

#define OLED_CIRCLEFILL                 0x69

#define OLED_PUTPIXEL                   0x50

#define OLED_READPIXEL                  0x52

#define OLED_RECTANGLE                  0x72

#define OLED_PAINTAREA                  0x70



// Text properties

#define OLED_SETFONTSIZE                0x46

#define OLED_FONT5X7                    0x01

#define OLED_FONT8X8                    0x02

#define OLED_FONT8X12                   0x03

#define OLED_TEXTFORMATED               0x54

#define OLED_TEXTOPAQUE                 0x4F


// OLED Control

#define OLED_COMMAND_CONTROL            0x59

#define OLED_COMMAND_DISPLAY            0x01

#define OLED_COMMAND_CONTRAST           0x02

#define OLED_COMMAND_POWER              0x03



#define OLED_ACK                        0x06  // Ok

#define OLED_NAK                        0x15  // Error

#define OLED_IMAGE                      0x49
#define OLED_USD                        0x40
#define OLED_SECTOR1                    0x10
#define OLED_SECTOR2                    0x000000


void OLED_ResetDisplay()

{

  digitalWrite(OLED_RESETPIN, LOW);

  delay(20);

  digitalWrite(OLED_RESETPIN, HIGH);

  delay(20);



}



char OLED_GetResponse()

{

  byte incomingByte = OLED_ACK;



  // Wait for data avaliable

  while (!Serial.available()) {
    delay(1);
  }



  // Read incoming byte

  incomingByte = Serial.read();



  return incomingByte;

}



// Initialise OLED display. You must first activate a Serial comunication!

void OLED_Init()

{

  // First reset display

  OLED_ResetDisplay();



  delay(OLED_INITDELAYMS);                       // Wait for init

  // Autodetect baudrate

  Serial.print(OLED_DETECT_BAUDRATE, BYTE);

  OLED_GetResponse();



}



// Get 16bits value from RGB (0 to 63, 565 format)

int GetRGB(int red, int green, int blue)

{



  char text[255];



  int outR = ((red * 31) / 255);

  int outG = ((green * 63) / 255);

  int outB = ((blue * 31) / 255);



  return (outR << 11) | (outG << 5) | outB;

}



void OLED_Clear()

{



  Serial.print(OLED_CLEAR, BYTE); // Pixel write

  delay(20);

  OLED_GetResponse();



}



void OLED_PutPixel(char x, char y, int color)

{



  // Putpixel

  Serial.print(OLED_PUTPIXEL, BYTE); // Pixel write

  Serial.print(x, BYTE);   // x

  Serial.print(y, BYTE);



  // Color

  Serial.print((color >> 8) & 0xFF, BYTE);      // MSB

  Serial.print(color & 0xFF, BYTE);        // LSB



  OLED_GetResponse();



}



void OLED_DrawLine(char x1, char y1, char x2, char y2, int color)

{



  // Line drawing

  Serial.print(OLED_LINE, BYTE); // Line



  Serial.print(x1, BYTE);  // x1

  Serial.print(y1, BYTE);      // y1

  Serial.print(x2, BYTE);  // x2

  Serial.print(y2, BYTE);      // y2



  // Color

  Serial.print((color >> 8) & 0xFF, BYTE);      // MSB

  Serial.print(color & 0xFF, BYTE);        // LSB



  OLED_GetResponse();



}



void OLED_DrawRectangle(char x, char y, char width, char height, int color)

{



  //int color = 0xFFFF;



  // Rectangle drawing

  Serial.print(OLED_RECTANGLE, BYTE);



  Serial.print(x, BYTE);           // x1

  Serial.print(y, BYTE);       // y1



  Serial.print(x+width-1, BYTE);     // x2

  Serial.print(y+height-1, BYTE);        // y1



  // Color

  Serial.print((color >> 8) & 0xFF, BYTE);      // MSB

  Serial.print(color & 0xFF, BYTE);        // LSB


  OLED_GetResponse();

}



void OLED_DrawCircle(char x, char y, char radius, int color)

{

  Serial.print(OLED_CIRCLE, BYTE);



  Serial.print(x, BYTE);   // x

  Serial.print(y, BYTE);   // y

  Serial.print(radius, BYTE);  // radius



  // Color

  Serial.print((color >> 8) & 0xFF, BYTE);      // MSB

  Serial.print(color & 0xFF, BYTE);        // LSB



  OLED_GetResponse();



}



void OLED_DrawTriangle(char x1, char y1, char x2, char y2, char x3, char y3, int color)

{
  Serial.print(OLED_TRIANGLE, BYTE);

  Serial.print(x1, BYTE);
  Serial.print(y1, BYTE);

  Serial.print(x2, BYTE);
  Serial.print(y2, BYTE);

  Serial.print(x3, BYTE);
  Serial.print(y3, BYTE);

  // Color
  Serial.print((color >> 8) & 0xFF, BYTE);
  Serial.print(color & 0xFF, BYTE);

  OLED_GetResponse();
}



static void DrawPolygon(int color, byte count, ...)

{
  va_list vl;
  byte x, y, i;

  Serial.print(OLED_POLYGON, BYTE);
  Serial.print(count, BYTE);

  va_start(vl, count);

  for (i = 0; i < count; i++) {
    x = (byte)va_arg(vl, int);
    y = (byte)va_arg(vl, int);

    Serial.print(x, BYTE);
    Serial.print(y, BYTE);
  }

  va_end(vl);

  // Color
  Serial.print((color >> 8) & 0xFF, BYTE);
  Serial.print(color & 0xFF, BYTE);

  OLED_GetResponse();
}



void OLED_DrawPolygon(byte x1, byte y1, byte x2, byte y2, byte x3, byte y3,
                      byte x4, byte y4, byte x5, byte y5,
                      int color)

{
  DrawPolygon(color, 5, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
}



/*

 Change font format:

 FontType can be:

 OLED_FONT5X7

 OLED_FONT8X8

 OLED_FONT8X12

 */

void OLED_SetFontSize(char FontType)

{

  Serial.print(OLED_SETFONTSIZE, BYTE);

  Serial.print(FontType, BYTE);



  OLED_GetResponse();

}



void OLED_DrawText(char column, char row, char font_size, const char *mytext, int color)

{

  //char mytext[] = "Arkanoid by pK";



  Serial.print(0x73, BYTE); // s (Formated text)



  //Serial.print(column); // column



  // Adjust to center of the screen (26 Columns at font size 0)

  int newCol = 13 - (strlen(mytext)/2);

  //Serial.print(newCol); // column

  Serial.print(column, BYTE); // column



  Serial.print(row, BYTE); // row

  Serial.print(font_size, BYTE); // font size (0 = 5x7 font, 1 = 8x8 font, 2 = 8x12 font)



  // Color

  Serial.print((color >> 8) & 0xFF, BYTE);      // MSB

  Serial.print(color & 0xFF, BYTE);        // LSB



  for (int i=0 ; i<strlen(mytext) ; i++)

  {

    Serial.print(mytext[i], BYTE); // character to write

  }

  Serial.print(0x00, BYTE); // string terminator (always 0x00)



  OLED_GetResponse();



}



void OLED_DrawSingleChar(char column, char row, char font_size, char MyChar, int color)

{



  Serial.print(OLED_TEXTFORMATED, BYTE); // T (Formated)



  Serial.print(MyChar, BYTE);

  Serial.print(column, BYTE);

  Serial.print(row, BYTE);



  // Color

  Serial.print((color >> 8) & 0xFF, BYTE);      // MSB

  Serial.print(color & 0xFF, BYTE);    // LSB



  OLED_GetResponse();



}

//========== Added by Eric ============

//==== Set text transparency    (Eric)
void OLED_SetTextTrans(char FontTrans){

  Serial.print(OLED_TEXTOPAQUE, BYTE);
  Serial.print(FontTrans, BYTE);

  OLED_GetResponse();
}

//==== Set PenSize    (Eric)
void OLED_PenSize(char PenSize){

  Serial.print(OLED_PAINTAREA, BYTE);
  Serial.print(PenSize, BYTE);

  OLED_GetResponse();
}

//==== Show SD image   (Eric)
void OLED_ShowImage(char PosX, char PosY, char Width, char Height, char colourMode, char SectorHi, char SectorMid, char SectorLo){


    Serial.print(OLED_USD, BYTE);
    Serial.print(OLED_IMAGE, BYTE);
    Serial.print(PosX, BYTE);
    Serial.print(PosY, BYTE);
    Serial.print(Width, BYTE);
    Serial.print(Height, BYTE);
    Serial.print(colourMode, BYTE);
    Serial.print(SectorHi, BYTE);
    Serial.print(SectorMid, BYTE);
    Serial.print(SectorLo, BYTE);


  OLED_GetResponse();
}

//==== Change BackGround color  (Eric)
void OLED_Background(int color){

    Serial.print(OLED_BKGCOLOR, BYTE);

     // Color
    Serial.print((color >> 8) & 0xFF, BYTE);      // MSB

    Serial.print(color & 0xFF, BYTE);        // LSB

    OLED_GetResponse();
}
