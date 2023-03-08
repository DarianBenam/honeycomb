/** File Name:       arg_fns.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Sunday, January 29, 2023 */

#include "../../include/config/config.hpp"
#include "../../include/args/arg_fns.hpp"

#include <iostream>

void honeycomb::print_usage()
{
	std::cerr << "Usage:";

	for (const char* const& arg : APP_REQUIRED_ARGS)
	{
		std::cerr << " --" << arg << " [...]";
	}

	std::cerr << '\n';
}
