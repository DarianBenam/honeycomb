/** File Name:       file_system.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Tuesday, March 14, 2023 */

#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace honeycomb
{
    /** @brief Checks a range of file system paths if they exist or not.
     *  @param tagPathPairList Vector of tuples where the first value represents a unique tag identifying the path and the second value represents
     *                         the path to be checked.
     *  @param printWarnMessage States whether to print a verbose warn message to the output stream on each occurrence that a path does not
                                exist or not.
     *  @returns True if all paths exist. False otherwise. */
    bool path_range_exists(std::vector<std::tuple<std::string, std::string>> const& tagPathPairList, bool const& printWarnMessage);
}
