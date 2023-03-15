/** File Name:       file_system.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Tuesday, March 14, 2023 */

#include "../../include/io/file_system.hpp"
#include "../../include/core/verbose.hpp"
#include <filesystem>

bool honeycomb::path_range_exists(std::vector<std::tuple<std::string, std::string>> const& tagPathPairList, bool const& printWarnMessage)
{
	bool allPathsExist = true;

	for (auto const& [tag, path] : tagPathPairList)
	{
		if (std::filesystem::exists(path))
		{
			continue;
		}

		if (!printWarnMessage)
		{
			return false;
		}

		allPathsExist = false;
		print_verbose_message(verbose_message_type::warn, WARN_TAG, "Path does not exist: \"" + path + "\" (" + tag + ")", printWarnMessage);
	}

    return allPathsExist;
}
