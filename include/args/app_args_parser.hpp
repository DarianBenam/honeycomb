/** File Name:       app_args_parser.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Friday, January 27, 2023 */

#pragma once

#include <string>
#include <optional>
#include <unordered_map>

namespace honeycomb
{
    constexpr char OUTPUT_PATH_ARG_NAME[] = "outputpath";
    constexpr char DOMAIN_ARG_NAME[] = "domain";
    constexpr char EXTENSION_ARG_NAME[] = "ext";
    constexpr char WWW_ROOT_ARG_NAME[] = "wwwroot";
    constexpr char TEMPLATE_DIRECTORY_ARG_NAME[] = "templatedir";
    constexpr char TEMPLATE_ENGINE_ARG_NAME[] = "engine";
    constexpr char LINK_LIST_FILE_PATH_ARG_NAME[] = "llpath";
    constexpr char IGNORE_LIST_FILE_PATH_ARG_NAME[] = "ilpath";

    class app_args_parser
    {
        std::unordered_map<char, bool> m_singleCharacterFlagArgs;
        size_t m_singleCharacterFlagArgsCount;

        std::unordered_map<std::string, std::string> m_multiCharacterArgs;
        size_t m_multiCharacterArgsCount;

    public:
        app_args_parser(int argc, char* argv[]);

        size_t get_single_character_flag_args_count() const;

        size_t get_multi_character_args_count() const;

        bool get_single_character_arg_value(char const& argName) const;

        std::optional<bool> try_get_single_character_arg_value(char const& argName) const;

        std::string get_multi_character_arg_value(std::string const& argName) const;

        std::optional<std::string> try_get_multi_character_arg_value(std::string const& argName) const;

        bool contains_multi_character_arg_range(const char* const args[], size_t const& argsSize);

    private:
        void parse_args(int argc, char* argv[]);
    };
};
