/// @file

#pragma once

constexpr auto ENGINE_API_VERSION{1};

struct engine_export_t
{
	int version{ENGINE_API_VERSION};
	
	struct InitProps
	{
		const char *sCmdLine{""};

#ifdef _WIN32
		HINSTANCE hInstance{};
#endif
	};

	///
	bool (*Init)(const InitProps &aInitProps);
	
	///
	void (*Shutdown)();
	
	///
	void (*Frame)();
};

using GetEngineAPI = engine_export_t *(*)(int nAPIVersion);