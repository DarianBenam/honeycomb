/** File Name:       template_engine.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Tuesday, January 24, 2023 */

#pragma once

#include <optional>
#include <string>

namespace honeycomb
{
    enum class template_engine
    {
        none,
        twig
    };

    constexpr template_engine get_template_engine_enum_from_string(std::optional<std::string> const& templateEngineName)
    {
        if (templateEngineName.has_value())
        {
            if (templateEngineName.value() == "twig")
            {
                return template_engine::twig;
            }
        }

        return template_engine::none;
    }

    constexpr std::string get_template_engine_file_extension(template_engine const& templateEngine)
    {
        switch (templateEngine)
        {
            case template_engine::twig: return ".twig";
            default:                    return "";
        }
    }
}
