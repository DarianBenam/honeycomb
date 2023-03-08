/** File Name:       xml_node.cpp
 *  Author:          Darian Benam <darian@darianbenam.com>
 *  Date Created:    Thursday, January 19, 2023 */

#include "../../include/xml/xml_exception.hpp"
#include "../../include/xml/xml_node.hpp"
#include <iostream>

honeycomb::xml_node::xml_node(std::string const& name, std::optional<std::string> const& innerValue, bool const& isSelfClosing = false)
	: m_name(name), m_innerValue(innerValue), m_isSelfClosing(isSelfClosing)
{

}

honeycomb::xml_node::~xml_node()
{
	for (xml_node* const& xmlNode : m_childNodesVector)
	{
		delete xmlNode;
	}
}

std::optional<std::string> honeycomb::xml_node::get_inner_value() const
{
	return m_innerValue;
}

bool honeycomb::xml_node::get_is_self_closing() const
{
	return m_isSelfClosing;
}

void honeycomb::xml_node::add_attribute(std::string const& attrKey, std::string const& attrValue)
{
	m_attributesMap[attrKey] = attrValue;
}

void honeycomb::xml_node::add_attribute(std::string const& attrKey, std::string_view const& attrValue)
{
	m_attributesMap[attrKey] = attrValue;
}

void honeycomb::xml_node::add_child_node(xml_node* const& xmlNode)
{
	if (get_is_self_closing())
	{
		throw xml_exception("Cannot add a child node to a self closing XML node.");
	}

	if (xmlNode == nullptr)
	{
		return;
	}

	m_childNodesVector.push_back(xmlNode);
}

std::string honeycomb::xml_node::to_string(bool const& writeIndentation = true) const
{
	return to_string(0, writeIndentation);
}

std::string honeycomb::xml_node::to_string(int const& depth, bool const& writeIndentation) const
{
	int indentationRepeatCount = writeIndentation
		? depth < 0
			? 0
			: depth
		: 0;

	std::string xmlNode;
	std::string indentation(indentationRepeatCount, '\t');

	if (writeIndentation)
	{
		xmlNode += indentation;
	}

	xmlNode += "<" + m_name;

	if (m_attributesMap.size() > 0)
	{
		for (auto const& [attrKey, attrValue] : m_attributesMap)
		{
			xmlNode += " " + attrKey + "=\"" + attrValue + "\"";
		}
	}

	if (m_isSelfClosing)
	{
		xmlNode += "/>";

		if (writeIndentation)
		{
			xmlNode += '\n';
		}
	}
	else
	{
		xmlNode += '>';

		if (!m_innerValue.has_value() && writeIndentation)
		{
			xmlNode += '\n';
		}

		if (m_childNodesVector.size() > 0)
		{
			for (xml_node* const& childXmlNode : m_childNodesVector)
			{
				xmlNode += childXmlNode->to_string(depth + 1, writeIndentation);
			}
		}
		else if (m_innerValue.has_value())
		{
			xmlNode += m_innerValue.value();
		}

		if (!m_innerValue.has_value())
		{
			xmlNode += indentation;
		}

		xmlNode += "</" + m_name + ">";

		if (writeIndentation)
		{
			xmlNode += '\n';
		}
	}

	return xmlNode;
}
