#include <TFT_eSPI.h> // Ensure you have TFT_eSPI configured for your display
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library
TFT_eSprite mySprite = TFT_eSprite(&tft);
#define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))
/***************************************************************************/
void setup()
/***************************************************************************/
{
  Serial.begin(115200); delay(2000);

  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  ledcAttach(TFT_BL, 5000, 8);  // PWM timer automatically assigned.
  ledcWrite(TFT_BL, 200);       // Turn the display on bigly.

  int *a = 0;
  a = (int*)mySprite.createSprite(tft.width(), tft.height());
  if (a == 0) {
    Serial.println("mySprite creation failed.  Cannot continue.");
    while (1);
  }
  Serial.printf("Create mySprite returned: %p\r\n", a);
}
/***************************************************************************/
void loop()
/***************************************************************************/
{
  //Note: PI / 6 is 30º and is a very natural looking angle for the arrow
  //       winglets.
  tft.fillScreen(TFT_BLACK);
  drawArrowLine(&tft, 50, 50, 200, 120, TFT_RED, 12, PI / 6, TFT_WHITE, true);
  drawArrowLine(&tft, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_GREEN, 12, PI / 6, TFT_WHITE, true);
  drawArrowLine(&tft, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_BLUE, 12, PI / 6, TFT_YELLOW, false);
  drawArrowLine(&tft, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_RED, 12, PI / 6, TFT_WHITE, true);
  drawArrowLine(&tft, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_PURPLE, 12, PI / 6, TFT_YELLOW, false);
  drawArrowLine(&tft, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_RED, 12, PI / 6, TFT_WHITE, true);
  delay(10000);

  mySprite.fillSprite(RGB565(25,25,25));
  drawArrowLine(&mySprite, 50, 50, 200, 120, TFT_RED, 12, PI / 6, TFT_WHITE, true);
  drawArrowLine(&mySprite, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_GREEN, 12, PI / 6, TFT_WHITE, true);
  drawArrowLine(&mySprite, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_BLUE, 12, PI / 6, TFT_YELLOW, false);
  drawArrowLine(&mySprite, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_RED, 12, PI / 6, TFT_WHITE, true);
  drawArrowLine(&mySprite, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_PURPLE, 12, PI / 6, TFT_YELLOW, false);
  drawArrowLine(&mySprite, random(tft.width()), random(tft.height()),
                random(tft.width()), random(tft.height()),
                TFT_RED, 12, PI / 6, TFT_WHITE, true);
  mySprite.pushSprite(0, 0);
  delay(10000);
}
/***************************************************************************/
void drawArrowLine(TFT_eSPI* targetPallete,
                   // Line start and end x & y
                   int x0, int y0, int x1, int y1,
                   // Line color
                   uint16_t lineColor,
                   // Length of the little winglets to make the arrow
                   int arrowLength,
                   // Angle away from the line for the two winglets
                   float arrowAngle,
                   // Color of the 2 or 3 arrow builder lines
                   uint16_t arrowColor,
                   // Do or do not draw back (3rd) line on arrow
                   bool doBackLine)
/***************************************************************************/
{
  static float angle;
  static int x2, y2, x3, y3;

  // Draw main line
  targetPallete->drawLine(x0, y0, x1, y1, lineColor);
  // Determine the angle of the original line.
  angle = atan2(y1 - y0, x1 - x0);

  // Calculate arrowhead lines length and angles
  // The arrowhead lines angles are based off of the original line angle.
  x2 = x1 - arrowLength * cos(angle - arrowAngle);
  y2 = y1 - arrowLength * sin(angle - arrowAngle);
  x3 = x1 - arrowLength * cos(angle + arrowAngle);
  y3 = y1 - arrowLength * sin(angle + arrowAngle);

  // Draw arrowhead
  targetPallete->drawLine(x1, y1, x2, y2, arrowColor);
  targetPallete->drawLine(x1, y1, x3, y3, arrowColor);
  // Do you want th0.0.e back line (3rd line) to complete the arrow?
  if (doBackLine) targetPallete->drawLine(x2, y2, x3, y3, arrowColor);
}
