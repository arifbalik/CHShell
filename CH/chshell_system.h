/*
       Copyright (C) 2015  Arif Ahmet Balik
       This program is free software: you can redistribute it and/or modify
       it under the terms of the GNU General Public License as published by
       the Free Software Foundation, either version 3 of the License, or
       (at your option) any later version.
       This program is distributed in the hope that it will be useful,
       but WITHOUT ANY WARRANTY; without even the implied warranty of
       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
       GNU General Public License for more details.
       You should have received a copy of the GNU General Public License
       along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */
#ifndef _CHSHELL_SYSTEM_H
#define _CHSHELL_SYSTEM_H

	extern int ch_system_reboot(int argc, char** argv);
	extern int ch_system_clear(int argc, char** argv);
	extern int ch_system_color(int argc, char** argv);
	extern int ch_system_font(int argc, char** argv);
	
#endif

