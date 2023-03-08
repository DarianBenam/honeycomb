/** File Name:       xml_exception.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Tuesday, March 7, 2023 */

#include "../../include/xml/xml_exception.hpp"

honeycomb::xml_exception::xml_exception(const char* const& message)
    : std::runtime_error(message)
{

}
