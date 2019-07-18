#pragma once
#ifndef _COLOR_
#define _COLOR_

#include <string>

/*
	PLEASE DON'T TELL THE FBI, I'LL FIX THIS, OKAY?
*/

namespace foreground {
	// ---- //
	// Dark //
	const std::string darkBlack = "\033[30m";
	const std::string darkRed = "\033[31m";
	const std::string darkGreen = "\033[32m";
	const std::string darkYellow = "\033[33m";
	const std::string darkBlue = "\033[34m";
	const std::string darkMagenta = "\033[35m";
	const std::string darkCyan = "\033[36m";
	const std::string darkWhite = "\033[37m";

	// ----- //
	// Light //
	const std::string lightBlack = "\033[90m";
	const std::string lightRed = "\033[91m";
	const std::string lightGreen = "\033[92m";
	const std::string lightYellow = "\033[93m";
	const std::string lightBlue = "\033[94m";
	const std::string lightMagenta = "\033[95m";
	const std::string lightCyan = "\033[96m";
	const std::string lightWhite = "\033[97m";

	// ----- //
	// Extra //
	const std::string reset = "\033[39m";
};

namespace background {
	// ---- //
	// Dark //
	const std::string darkBlack = "\033[40m";
	const std::string darkRed = "\033[41m";
	const std::string darkGreen = "\033[42m";
	const std::string darkYellow = "\033[43m";
	const std::string darkBlue = "\033[44m";
	const std::string darkMagenta = "\033[45m";
	const std::string darkCyan = "\033[46m";
	const std::string darkWhite = "\033[47m";

	// ----- //
	// Light //
	const std::string lightBlack = "\033[100m";
	const std::string lightRed = "\033[101m";
	const std::string lightGreen = "\033[102m";
	const std::string lightYellow = "\033[103m";
	const std::string lightBlue = "\033[104m";
	const std::string lightMagenta = "\033[105m";
	const std::string lightCyan = "\033[106m";
	const std::string lightWhite = "\033[107m";

	// ----- //
	// Extra //
	const std::string reset = "\033[49m";
};

#endif