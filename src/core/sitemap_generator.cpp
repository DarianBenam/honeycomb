/** File Name:       sitemap_generator.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Sunday, January 22, 2023 */

#include "../../include/core/sitemap_generator.hpp"
#include "../../include/config/config.hpp"
#include "../../include/core/verbose.hpp"
#include "../../include/xml/xml_attr.hpp"
#include "../../include/xml/xml_node.hpp"
#include <algorithm>
#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

honeycomb::sitemap_generator::sitemap_generator(std::string const& domain,
                                                            std::string const& wwwRootDirectory,
                                                            std::optional<std::string> const& templateDirectory,
                                                            std::string const& fileExtensionsRegex,
                                                            template_engine const& templateEngine)
    : m_domain(domain),
      m_wwwRootDirectory(wwwRootDirectory),
      m_templateDirectory(templateDirectory),
      m_fileExtensionsRegex(fileExtensionsRegex),
      m_templateEngine(templateEngine),
      m_urlSetXmlNode(nullptr)
{

}

honeycomb::sitemap_generator::~sitemap_generator()
{
    delete m_urlSetXmlNode;
}

bool honeycomb::sitemap_generator::generate_sitemap(std::string const& outputXmlFilePath,
                                                                std::string const& linkListFilePath,
                                                                std::string const& ignoreListFilePath,
                                                                bool const& writeIndentation,
                                                                bool const& isVerboseMode)
{
    using std::chrono::time_point;
    using std::chrono::file_clock;
    using std::chrono::system_clock;
    using std::chrono::utc_clock;
    using std::filesystem::absolute;
    using std::filesystem::directory_entry;
    using std::filesystem::exists;
    using std::filesystem::file_time_type;
    using std::filesystem::last_write_time;
    using std::filesystem::path;
    using std::filesystem::recursive_directory_iterator;

    m_urlSetXmlNode = new xml_node("urlset", std::nullopt, false);
    m_urlSetXmlNode->add_attribute("xmlns", SITEMAP_SCHEMA_VERSION_0_9_URL);

    std::regex fileExtensionRegex = std::regex(std::string(m_fileExtensionsRegex));
    std::string templateEngineExtension = get_template_engine_file_extension(m_templateEngine);
    std::vector<std::regex> ignoreList = read_ignore_list(ignoreListFilePath);

    for (directory_entry const& directoryEntry : recursive_directory_iterator(m_wwwRootDirectory))
    {
        if (!directoryEntry.is_regular_file())
        {
            continue;
        }

        path currentFilePath = absolute(directoryEntry.path());

        if (!std::regex_match(currentFilePath.extension().string(), fileExtensionRegex))
        {
            print_verbose_message(verbose_message_type::info, SKIP_TAG, directoryEntry.path().string(), isVerboseMode);
            continue;
        }

        std::string relativeUrl = currentFilePath.string().substr(m_wwwRootDirectory.length());

        std::replace(relativeUrl.begin(), relativeUrl.end(), '\\', '/');

        if (matches_regex_range(relativeUrl, ignoreList))
        {
            print_verbose_message(verbose_message_type::fail, IGNORE_TAG, directoryEntry.path().string(), isVerboseMode);
            continue;
        }

        path equivalentTemplateFile = relativeUrl;
        file_time_type webpageFileLastWriteTime;

        if (m_templateEngine != template_engine::none && m_templateDirectory.has_value())
        {
            equivalentTemplateFile.filename().replace_extension(templateEngineExtension);

            path webpageTemplateFile = m_templateDirectory.value() / equivalentTemplateFile;

            webpageFileLastWriteTime = exists(webpageTemplateFile)
                ? last_write_time(webpageTemplateFile)
                : last_write_time(currentFilePath);
        }
        else
        {
            webpageFileLastWriteTime = last_write_time(currentFilePath);
        }

#ifdef __GNUC__
        time_point fileWriteTimeSystem = file_clock::to_sys(webpageFileLastWriteTime);
#else
        time_point fileWriteTimeSystem = utc_clock::to_sys(file_clock::to_utc(webpageFileLastWriteTime));
#endif

        time_t fileWriteTimeRaw = system_clock::to_time_t(fileWriteTimeSystem);
        char timeBuffer[sizeof "YYYY-MM-DD"] = { '\0' };

#ifdef _WIN32
        struct tm fileWriteTime = {};

        localtime_s(&fileWriteTime, &fileWriteTimeRaw);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d", &fileWriteTime);
#else
        struct tm* fileWriteTime = localtime(&fileWriteTimeRaw);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d", fileWriteTime);
#endif

        std::string webpageLocation = m_domain + relativeUrl;

        xml_node* urlXmlNode = new xml_node("url", std::nullopt, false);
        urlXmlNode->add_child_node(new xml_node("loc", webpageLocation, false));
        urlXmlNode->add_child_node(new xml_node("lastmod", timeBuffer, false));

        m_urlSetXmlNode->add_child_node(urlXmlNode);

        print_verbose_message(verbose_message_type::success, INDEX_TAG, directoryEntry.path().string(), isVerboseMode);
    }

    std::vector<std::tuple<std::string, std::string>> linkList = read_link_list(linkListFilePath);

    for (auto const& [relativeUrl, lastModificationDate] : linkList)
    {
        std::string webpageLocation = m_domain + relativeUrl;

        xml_node* urlXmlNode = new xml_node("url", std::nullopt, false);
        urlXmlNode->add_child_node(new xml_node("loc", webpageLocation, false));

        if (!lastModificationDate.empty())
        {
            urlXmlNode->add_child_node(new xml_node("lastmod", lastModificationDate, false));
        }

        m_urlSetXmlNode->add_child_node(urlXmlNode);
    }

    bool sitemapGenerated = write_xml_to_file(m_urlSetXmlNode, outputXmlFilePath, writeIndentation, isVerboseMode);

    return sitemapGenerated;
}

bool honeycomb::sitemap_generator::matches_regex_range(std::string const& value, std::vector<std::regex> const& regexList)
{
    for (std::regex const& regex : regexList)
    {
        if (std::regex_search(value, regex))
        {
            return true;
        }
    }

    return false;
}

bool honeycomb::sitemap_generator::write_xml_to_file(xml_node* const& parentNode, std::string const& filePath, bool const& writeIndentation, bool const& isVerboseMode)
{
    std::ofstream outputXmlFileStream(filePath);

    if (!outputXmlFileStream)
    {
        return false;
    }

    int initialIndentationDepth = writeIndentation ? 0 : -1;

    outputXmlFileStream << "<?xml version=\"" << XML_VERSION_1_0 << "\" encoding=\"" << ENCODING_UTF_8 << "\"?>\n";
    outputXmlFileStream << parentNode->to_string(initialIndentationDepth, writeIndentation);

    return true;
}
