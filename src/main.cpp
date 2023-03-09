/** File Name:       main.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Thursday, January 19, 2023 */

#include "../include/sitemap_generator.hpp"
#if defined(_DEBUG) && defined(_WIN32)
#define CHECK_MEMORY_LEAKS
#include <crtdbg.h>
#endif
#include <chrono>
#include <iostream>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <cstdlib>

int main(int argc, char* argv[])
{
#if defined(_DEBUG) && defined(_WIN32) && defined(CHECK_MEMORY_LEAKS)
	int debugFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	debugFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	debugFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	debugFlags |= _CRTDBG_LEAK_CHECK_DF;

	_CrtSetDbgFlag(debugFlags);
#endif

	using namespace honeycomb;

	std::cout << "  __    __\n";
	std::cout << " /  \\__/  \\__  Honeycomb Sitemap Generator\n";
	std::cout << " \\__/  \\__/  \\ www.darianbenam.com\n";
	std::cout << "    \\__/  \\__/ v" + std::to_string(MAJOR_VERSION) + '.' + std::to_string(MINOR_VERSION) + '.' + std::to_string(PATCH_VERSION) + '\n';
	std::cout << "       \\__/\n\n";

	app_args_parser args(argc, argv);

	if (!args.contains_multi_character_arg_range(APP_REQUIRED_ARGS, std::size(APP_REQUIRED_ARGS)))
	{
		print_usage();
		return EXIT_FAILURE;
	}

	std::string sitemapXmlFilePath = args.get_multi_character_arg_value(OUTPUT_PATH_ARG_NAME);
	std::string domain = args.get_multi_character_arg_value(DOMAIN_ARG_NAME);
	std::string wwwRootDirectory = args.get_multi_character_arg_value(WWW_ROOT_ARG_NAME);
	std::optional<std::string> templateDirectory = args.try_get_multi_character_arg_value(TEMPLATE_DIRECTORY_ARG_NAME);
	std::string fileExtensionsRegex = args.try_get_multi_character_arg_value(EXTENSION_ARG_NAME).value_or(".htm|.html");
	template_engine templateEngine = get_template_engine_enum_from_string(args.try_get_multi_character_arg_value(TEMPLATE_ENGINE_ARG_NAME));

	bool isOutputFileIndented = args.try_get_single_character_arg_value('i') != std::nullopt;
	bool isVerboseMode = args.try_get_single_character_arg_value('v') != std::nullopt;

	if (isVerboseMode)
	{
		print_verbose_message(verbose_message_type::info, INFO_TAG, "Sitemap XML Path = \"" + sitemapXmlFilePath + "\"");
		print_verbose_message(verbose_message_type::info, INFO_TAG, "Domain = \"" + domain + "\"");
		print_verbose_message(verbose_message_type::info, INFO_TAG, "WWW Root Directory = \"" + wwwRootDirectory + "\"");
		print_verbose_message(verbose_message_type::info, INFO_TAG, "Template Directory = \"" + templateDirectory.value_or("N/A") + "\"");
		print_verbose_message(verbose_message_type::info, INFO_TAG, "File Extensions Regex = \"" + fileExtensionsRegex + "\"");
		print_verbose_message(verbose_message_type::info, INFO_TAG, "Template Engine File Extension = \"" + std::string(get_template_engine_file_extension(templateEngine)) + "\"");
	}

	sitemap_generator sitemapGenerator(domain, wwwRootDirectory, templateDirectory, fileExtensionsRegex, templateEngine);
	bool sitemapGenerated = sitemapGenerator.generate_sitemap(sitemapXmlFilePath, std::string(SITEMAP_LINK_LIST_FILE_PATH), std::string(SITEMAP_IGNORE_LIST_FILE_PATH), isOutputFileIndented, isVerboseMode);

	if (isVerboseMode)
	{
		std::cout << '\n';
	}

	if (!sitemapGenerated)
	{
		std::cerr << "Failed to generate sitemap!\n";
		return EXIT_FAILURE;
	}

	std::cout << "Sitemap generated successfully!\n";
}
