/*
===========================================================================
Copyright (C) 2021 BlackPhrase

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

/// @file

#pragma once

/// Loads a module by its file name
void *Sys_LoadLibrary(const char *sName);

/// Gets an export func from the loaded module
void *Sys_GetExport(void *pLib, const char *sName);

/// Unloads the loaded module by its pointer
void Sys_FreeLibrary(void *pLib);