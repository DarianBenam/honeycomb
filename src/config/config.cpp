/** File Name:       config.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Saturday, March 4, 2023 */

#include "../../include/config/config.hpp"
#include <algorithm>
#include <fstream>

bool honeycomb::is_comment_or_empty_line(std::string const& line)
{
    return line.starts_with('#') || line.find_first_not_of(' ') == std::string::npos;
}

std::vector<std::tuple<std::string, std::string>> honeycomb::read_link_list(std::string const& linkListFilePath)
{
    std::vector<std::tuple<std::string, std::string>> linkList;
    std::ifstream linkListFile(linkListFilePath);

    if (linkListFile)
    {
        std::string currentLine;

        while (std::getline(linkListFile, currentLine))
        {
            if (currentLine.starts_with('#') || currentLine.find_first_not_of(' ') == std::string::npos)
            {
                continue;
            }

            size_t firstSpaceIndex = currentLine.find_first_of(' ');

            if (firstSpaceIndex == std::string::npos)
            {
                linkList.push_back(std::tuple(currentLine, ""));
                continue;
            }

            std::string relativeUrl = currentLine.substr(0, firstSpaceIndex);
            std::string lastModificationDate = currentLine.substr(firstSpaceIndex + 1);

            std::replace(relativeUrl.begin(), relativeUrl.end(), '\\', '/');

            linkList.push_back(std::tuple(relativeUrl, lastModificationDate));
        }
    }

    return linkList;
}

std::vector<std::regex> honeycomb::read_ignore_list(std::string const& ignoreListFilePath)
{
    std::vector<std::regex> ignoreList;
    std::ifstream ignoreListFile(ignoreListFilePath);

    if (ignoreListFile)
    {
        std::string currentLine;

        while (std::getline(ignoreListFile, currentLine))
        {
            if (is_comment_or_empty_line(currentLine))
            {
                continue;
            }

            ignoreList.push_back(std::regex(currentLine));
        }
    }

    return ignoreList;
}
