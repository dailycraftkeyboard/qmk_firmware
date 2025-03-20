/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 MakotoKurauchi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define QUICK_TAP_TERM 0

#define SERIAL_SLAVE_BUFFER_LENGTH  ((MATRIX_ROWS)/2)
#define SERIAL_MASTER_BUFFER_LENGTH ((MATRIX_ROWS)/2)

/* Select hand configuration */
#define MASTER_LEFT

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }

#define DIODE_DIRECTION COL2ROW

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN B5
#endif

#define DEBUG_ENABLE