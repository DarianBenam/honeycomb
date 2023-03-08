/** File Name:       app_args_parser.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Friday, January 27, 2023 */

#include "../../include/args/app_args_parser.hpp"
#include <cstdint>
#include <vector>

honeycomb::app_args_parser::app_args_parser(int argc, char* argv[])
    : m_multiCharacterArgs({}),
      m_multiCharacterArgsCount(0),
      m_singleCharacterFlagArgs({}),
      m_singleCharacterFlagArgsCount(0)
{
    parse_args(argc, argv);
}

size_t honeycomb::app_args_parser::get_single_character_flag_args_count() const
{
    return m_singleCharacterFlagArgsCount;
}

size_t honeycomb::app_args_parser::get_multi_character_args_count() const
{
    return m_multiCharacterArgsCount;
}

bool honeycomb::app_args_parser::get_single_character_arg_value(char const& argName) const
{
    return m_singleCharacterFlagArgs.at(argName);
}

std::optional<bool> honeycomb::app_args_parser::try_get_single_character_arg_value(char const& argName) const
{
    if (m_singleCharacterFlagArgs.contains(argName))
    {
        return m_singleCharacterFlagArgs.at(argName);
    }

    return std::nullopt;
}

std::string honeycomb::app_args_parser::get_multi_character_arg_value(std::string const& argName) const
{
    return m_multiCharacterArgs.at(argName);
}

std::optional<std::string> honeycomb::app_args_parser::try_get_multi_character_arg_value(std::string const& argName) const
{
    if (m_multiCharacterArgs.contains(argName))
    {
        return m_multiCharacterArgs.at(argName);
    }

    return std::nullopt;
}

bool honeycomb::app_args_parser::contains_multi_character_arg_range(const char* const args[], size_t const& argsSize)
{
    for (size_t i = 0; i < argsSize; ++i)
    {
        if (!m_multiCharacterArgs.contains(args[i]))
        {
            return false;
        }
    }

    return true;
}

void honeycomb::app_args_parser::parse_args(int argc, char* argv[])
{
    if (argc <= 1)
    {
        return;
    }

    std::vector<std::string> argTokens(argv, argv + argc);

    std::string currentArgKey;
    std::string currentArgValue;

    for (std::string const& argToken : argTokens)
    {
        if (argToken.starts_with("--"))
        {
            if (currentArgKey.length() > 0)
            {
                currentArgKey.erase(0, 2);
            }

            m_multiCharacterArgs[currentArgKey] = currentArgValue;
            currentArgValue = {};
            currentArgKey = argToken;

            if (!m_multiCharacterArgs.contains(currentArgKey))
            {
                ++m_multiCharacterArgsCount;
            }

            continue;
        }

        if (argToken.starts_with('-'))
        {
            for (int i = 1; i < argToken.length(); ++i)
            {
                char flag = argToken[i];

                if (isalpha(flag) && !m_singleCharacterFlagArgs.contains(flag))
                {
                    m_singleCharacterFlagArgs[flag] = true;
                    ++m_singleCharacterFlagArgsCount;
                }
            }

            continue;
        }

        if (currentArgValue.length() > 0)
        {
            currentArgValue += ' ';
        }

        currentArgValue += argToken;
    }

    if (currentArgKey.length() > 0)
    {
        currentArgKey.erase(0, 2);
        m_multiCharacterArgs[currentArgKey] = currentArgValue;
    }
}
