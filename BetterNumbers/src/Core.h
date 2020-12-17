#pragma once

#ifdef BETTERNUMBERS_EXPORTS
	#define BN_API __declspec(dllexport)
#else
	#define BN_API __declspec(dllimport)
#endif