/*
 * =====================================================================================
 *
 *       Filename: xmlparagraphleaf.hpp
 *        Created: 12/22/2018 07:38:04
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#pragma once
#include <vector>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <tinyxml2.h>
#include "strf.hpp"
#include "fflerror.hpp"

constexpr int LEAF_UTF8GROUP = 0;
constexpr int LEAF_IMAGE     = 1;
constexpr int LEAF_EMOJI     = 2;

struct xmlLeafData
{
    struct _currData
    {
    } currData;

    struct _accuData
    {
    } accuData;
};

class XMLParagraphLeaf
{
    private:
        friend class XMLParapragh;

    private:
        const tinyxml2::XMLNode *m_node;

    private:
        int m_type;

    private:
        uint64_t m_U64Key;

    private:
        std::vector<int> m_UTF8CharOff;

    private:
        int m_event;

    public:
        explicit XMLParagraphLeaf(tinyxml2::XMLNode *);

    public:
        int Type() const
        {
            return m_type;
        }

        const tinyxml2::XMLNode *xmlNode() const
        {
            return m_node;
        }

        tinyxml2::XMLNode *xmlNode()
        {
            return const_cast<tinyxml2::XMLNode *>(static_cast<const XMLParagraphLeaf *>(this)->xmlNode());
        }

        int length() const
        {
            if(Type() == LEAF_UTF8GROUP){
                return (int)(utf8CharOffRef().size());
            }
            return 1;
        }

        const std::vector<int> &utf8CharOffRef() const
        {
            if(Type() != LEAF_UTF8GROUP){
                throw fflerror("leaf is not an utf8 string");
            }

            if(m_UTF8CharOff.empty()){
                throw fflerror("utf8 token off doesn't initialized");
            }

            return m_UTF8CharOff;
        }

        std::vector<int> &utf8CharOffRef()
        {
            return const_cast<std::vector<int> &>(static_cast<const XMLParagraphLeaf *>(this)->utf8CharOffRef());
        }

        const char *UTF8Text() const
        {
            if(Type() != LEAF_UTF8GROUP){
                return nullptr;
            }
            return xmlNode()->Value();
        }

        uint64_t ImageU64Key() const
        {
            if(Type() != LEAF_IMAGE){
                throw fflerror("leaf is not an image");
            }
            return m_U64Key;
        }

        uint32_t emojiU32Key() const
        {
            if(Type() != LEAF_EMOJI){
                throw fflerror("leaf is not an emoji");
            }
            return m_U64Key;
        }

        uint32_t peekUTF8Code(int) const;

    public:
        int markEvent(int);

    public:
        std::optional<uint32_t>   Color() const;
        std::optional<uint32_t> BGColor() const;

    public:
        std::optional<uint8_t> font()      const;
        std::optional<uint8_t> fontSize()  const;
        std::optional<uint8_t> fontStyle() const;

    public:
        const xmlLeafData *leafData() const
        {
            return reinterpret_cast<xmlLeafData *>(m_node->GetUserData());
        }

        const char *hasEvent() const
        {
            if(Type() == LEAF_UTF8GROUP){
                if(auto par = m_node->Parent(); par && par->ToElement() && (std::strcmp(par->ToElement()->Name(), "event") == 0)){
                    if(const auto *value = par->ToElement()->Attribute("id"); value){
                        return value;
                    }
                    return "";
                }
            }
            return nullptr;
        }
};
