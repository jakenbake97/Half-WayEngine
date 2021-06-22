#pragma once

// Windows
#ifdef BE_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN

	// Disable windows' Min and Max to prevent from messing up the std::min and max functions
	#define NOMINMAX

	// Define strict to allow for more portable code and require more care in declaring and using types
	#ifndef STRICT
		#define STRICT
	#endif


	// target Windows 7 or later
	#include <winsdkver.h>
	#include <sdkddkver.h>
	#include <Windows.h>
#endif

#include <CodeAnalysis/Warnings.h>

// Common includes
#pragma warning(push) // This excludes all warnings raised inside External headers
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <cstdint>
#pragma warning(pop)


// Engine includes
#include "Basalt/Core.h"
#include "Basalt/Utility/String.h"
#include "Basalt/Utility/Math.h"
#include "Basalt/Log.h"