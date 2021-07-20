/// @file

#include "Engine.hpp"
#include "engine/IEngine.h"
#include "qcommon/qcommon.h"

#ifdef _WIN32
#	include "qcommon/win/win_local.h"

#	define EXPORT [[dllexport]]
#elif defined(__unix__)
#	define EXPORT [[visibility("default")]]
#endif

#define C_EXPORT extern "C" EXPORT

namespace
{

bool Engine_Init(const engine_export_t::InitProps &aInitProps)
{
#ifdef _WIN32
	g_wv.hInstance = hInstance;
#endif

	// done before Com/Sys_Init since we need this for error output
	Sys_CreateConsole();

#ifdef _WIN32
	// no abort/retry/fail errors
	SetErrorMode( SEM_FAILCRITICALERRORS );
#endif

	// get the initial time base
	Sys_Milliseconds();
	
#if 0
	// if we find the CD, add a +set cddir xxx command line
	Sys_ScanForCD();
#endif

	Sys_InitStreamThread();

	Com_Init(aInitProps.sCmdLine); // sys_cmdline
	NET_Init();

#ifdef _WIN32
	char cwd[MAX_OSPATH];
	_getcwd (cwd, sizeof(cwd));
	Com_Printf("Working directory: %s\n", cwd);
#endif

	// hide the early console since we've reached the point where we
	// have a working graphics subsystems
	if ( !com_dedicated->integer && !com_viewlog->integer )
		Sys_ShowConsole( 0, qfalse );
	
#ifdef __UNIX__
	Sys_ConsoleInputInit();

	fcntl(0, F_SETFL, fcntl (0, F_GETFL, 0) | FNDELAY);
	
#	ifdef DEDICATED
		// init here for dedicated, as we don't have GLimp_Init
		InitSig();
#	endif
#endif
	
	return true;
};

void Engine_Frame()
{
#ifdef _WIN32
	static int totalMsec, countMsec;
	int startTime, endTime;
	
	// if not running as a game client, sleep a bit
	if ( g_wv.isMinimized || ( com_dedicated && com_dedicated->integer ) )
		Sleep( 5 );

	// set low precision every frame, because some system calls
	// reset it arbitrarily
//		_controlfp( _PC_24, _MCW_PC );
//    _controlfp( -1, _MCW_EM  ); // no exceptions, even if some crappy
							// syscall turns them back on!

	startTime = Sys_Milliseconds();

	// make sure mouse and joystick are only called once a frame
	IN_Frame();
#endif

#ifdef __linux__
    Sys_ConfigureFPU();
#endif

	// run the game
	Com_Frame();

#ifdef _WIN32
	endTime = Sys_Milliseconds();
	totalMsec += endTime - startTime;
	countMsec++;
#endif
};

engine_export_t gEngine =
{
	Engine_Init,
	Com_Shutdown,
	Engine_Frame
};

}; // namespace

C_EXPORT engine_export_t *GetEngineAPI(int nAPIVersion)
{
	if(nAPIVersion == ENGINE_API_VERSION)
		return &gEngine;
	
	return nullptr;
};