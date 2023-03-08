/** File Name:       sitemap_generator.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Sunday, January 22, 2023 */

#pragma once

#include "template_engine.hpp"
#include "../xml/xml_node.hpp"
#include <optional>
#include <regex>
#include <string>
#include <vector>

namespace honeycomb
{
    class sitemap_generator final
    {
        std::string m_sitemapXmlFilePath;
        std::string m_domain;
        std::string m_wwwRootDirectory;
        std::optional<std::string> m_templateDirectory;
        std::string m_fileExtensionsRegex;

        template_engine m_templateEngine;

        xml_node* m_urlSetXmlNode;

    public:
        sitemap_generator(std::string const& domain,
                          std::string const& wwwRootDirectory,
                          std::optional<std::string> const& templateDirectory,
                          std::string const& fileExtensionsRegex,
                          template_engine const& templateEngine);

        ~sitemap_generator();

        bool generate_sitemap(std::string const& outputXmlFilePath,
                              std::string const& linkListFilePath,
                              std::string const& ignoreListFilePath,
                              bool const& writeIndentation,
                              bool const& isVerboseMode);

    private:
        bool matches_regex_range(std::string const& value, std::vector<std::regex> const& regexList);

        bool write_xml_to_file(xml_node* const& parentNode, std::string const& filePath, bool const& writeIndentation, bool const& isVerboseMode);
    };
}
