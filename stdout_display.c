/*-----------------------------------------------------------------------------
 * Name:    stdout_display.c
 * Purpose: STDOUT Display Template
 * Rev.:    1.00
 *-----------------------------------------------------------------------------*/

/* Copyright (c) 2013 - 2015 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include "Board_GLCD.h"
#include "GLCD_Config.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

/**
  Initialize stdout

  \return          0 on success, or -1 on error.
*/
int stdout_init (void) {

  GLCD_Initialize         ();                /* Initialize the grapic LCD     */
  GLCD_SetBackgroundColor (GLCD_COLOR_BLACK);/* Set background color to white */
  GLCD_SetForegroundColor (GLCD_COLOR_GREEN); /* Set foreground color to blue  */
  GLCD_ClearScreen        ();                /* Clear the grapic LCD          */
  GLCD_SetFont            (&GLCD_Font_6x8);  /* Set active font               */

  return (0);
}


/**
  Put a character to the stdout

  \param[in]   ch  Character to output
  \return          The character written, or -1 on write error.
*/
int stdout_putchar (int ch) {
	static int ln  = 0;
  static int col = 0;
	
  if (ch == 0x0A) {           /* Line Feed */
    col = 0;
    ln ++;
    if (ln >= (GLCD_HEIGHT / 8)) {
      ln = (GLCD_HEIGHT / 8) - 1;
      GLCD_VScroll (8);
    }
  } else if (ch == 0x0D) {    /* Carriage Return */
    col = 0;
  } else if (ch == 0x08) {    /* Backspace */
    if (col) 
      col --;
  } else {
    GLCD_DrawChar (6*col++, 8*ln, (int32_t)ch);
  }

  return (ch);
}
