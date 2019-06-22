/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

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

#include <cstdlib>

#include "engine/IEngine.h"

engine_export_t *gpEngine{nullptr}:

int main(int argc, char **argv)
{
	if(!gpEngine->Init())
		return EXIT_FAILURE;

    // main game loop
	while( 1 )
	{
		gpEngine->Frame();
	};

	// never gets here
	return EXIT_SUCCESS;
};

#ifdef _WIN32
/*
==================
WinMain

==================
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// should never get a previous instance in Win32
    if ( hPrevInstance )
        return 0;

	g_wv.hInstance = hInstance; // TODO
	Q_strncpyz( sys_cmdline, lpCmdLine, sizeof( sys_cmdline ) );
	
	return main(__argc, __argv);
};
#endif