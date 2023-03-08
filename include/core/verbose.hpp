/** File Name:       verbose.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Friday, March 3, 2023 */

#pragma once

#include <string>

namespace honeycomb
{
    enum class verbose_message_type
    {
        success,
        fail,
        info,
        warn
    };

    constexpr const char* const IGNORE_TAG = "ignore";
    constexpr const char* const INDEX_TAG = "index";
    constexpr const char* const INFO_TAG = "info";
    constexpr const char* const SKIP_TAG = "skip";

    constexpr const char* const get_verbose_message_type_ansi_color(verbose_message_type type)
    {
        switch (type)
        {
            case verbose_message_type::success: return "\u001b[42;1m";
            case verbose_message_type::fail:    return "\u001b[41;1m";
            case verbose_message_type::info:    return "\u001b[44;1m";
            case verbose_message_type::warn:    return "\u001b[43m";
            default:                            return "\u001b[0m";
        }
    }

    void print_verbose_message(verbose_message_type type, std::string const& tag, std::string const& message, bool printMessage = true);
}
