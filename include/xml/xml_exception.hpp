/** File Name:       xml_exception.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Tuesday, March 7, 2023 */

#pragma once

#include <stdexcept>

namespace honeycomb
{
    class xml_exception : public std::runtime_error
    {
    public:
        xml_exception(const char* const& message);
    };
}
