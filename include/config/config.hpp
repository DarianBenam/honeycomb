/** File Name:       config.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Sunday, January 29, 2023 */

#pragma once

#include "../args/app_args_parser.hpp"
#include <cstdint>
#include <regex>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace honeycomb
{
	constexpr int16_t MAJOR_VERSION = 1;
	constexpr int16_t MINOR_VERSION = 0;
	constexpr int16_t PATCH_VERSION = 0;

	constexpr std::string_view SITEMAP_LINK_LIST_FILE_PATH = ".honeycomblinklist";
	constexpr std::string_view SITEMAP_IGNORE_LIST_FILE_PATH = ".honeycombignorelist";

	constexpr const char* APP_REQUIRED_ARGS[] =
	{
		OUTPUT_PATH_ARG_NAME,
		DOMAIN_ARG_NAME,
		WWW_ROOT_ARG_NAME
	};

	bool is_comment_or_empty_line(std::string const& line);

	std::vector<std::tuple<std::string, std::string>> read_link_list(std::string const& linkListFilePath);

	std::vector<std::regex> read_ignore_list(std::string const& ignoreListFilePath);
};
