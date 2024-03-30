/* Copyright 2021 Dennis Kruyt (dennis@kruyt.org)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define RGB_MATRIX_LED_COUNT 51
#define USB_SUSPEND_WAKEUP_DELAY 0

#define TAPPING_TERM 170
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define PERMISSIVE_HOLD

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 130 // Limit to vendor-recommended value
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
#    define ENABLE_RGB_MATRIX_SOLID_COLOR
#endif
