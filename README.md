# Draw-tft_espi-Line-with-Arrow-at-the-end
Here's a little routine to draw a line and put an arrow at the end on ESP32 with tft_espi.

This little routine can easily replace a tft_espi drawLine call.  It needs a few more parms but they are easy to fill in and need to be there to layout what it is you want to see.  It will drop a line with arrowhead at the end on either a sprite or the base tft layer.  You need to supply the starting and ending x, y and color for the original line as well as the length of the "winglets" and color for the arrow.  To get the arrow at the other end, just reverse the two base line x, y pairs.

You can specify to either just draw the two little "winglet" lines or to draw the back side to make a closed triangle.  If you want it filled, call the standard fill triangle routine from the tft_espi library.  It is easily added to the routine and I may do that soon and reupload.  That's about all there is to it but it makes it so easy to draw a line ending in an arrow.  See the picture for variations of this.  It shows open and closed triangles. I have to credit Andriod CoPilot for the initial info and Windows CoPilot for some polish with a sticky bit of math to find the angle of the basic line then finding the proper angles for the winglets.  However it loses points for not being up to date and knowing that one can now call a routine with either a sprite or a tft target without overloading being needed.  Just code the called subroutine header thus: 
void drawArrowLine(TFT_eSPI* targetPallete, ... ) and it will take either one, happily. That is all demonstrated in the example program.

Enjoy,
Mikey the Midnight Coder

![Line with Arrows](https://github.com/user-attachments/assets/7c956976-7143-45fb-85bd-242da80f2f4a)
