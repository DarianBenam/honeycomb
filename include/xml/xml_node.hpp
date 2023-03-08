/** File Name:       xml_node.hpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Thursday, January 24, 2023 */

#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace honeycomb
{
	class xml_node
	{
		friend class sitemap_generator;

		std::unordered_map<std::string, std::string> m_attributesMap;

		std::string m_name;
		std::optional<std::string> m_innerValue;

		bool m_isSelfClosing;

		std::vector<xml_node*> m_childNodesVector;

	public:
		xml_node(std::string const& name, std::optional<std::string> const& innerValue, bool const& isSelfClosing);

		~xml_node();

		std::optional<std::string> get_inner_value() const;

		bool get_is_self_closing() const;

		void add_attribute(std::string const& attrKey, std::string const& attrValue);

		void add_attribute(std::string const& attrKey, std::string_view const& attrValue);

		void add_child_node(xml_node* const& xmlNode);

		std::string to_string(bool const& writeIndentation) const;

	private:
		std::string to_string(int const& depth, bool const& writeIndentation) const;
	};
}
