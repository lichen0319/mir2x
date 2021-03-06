/*
 * =====================================================================================
 *
 *       Filename: tritexbutton.hpp
 *        Created: 08/26/2016 13:20:23
 *    Description: button with three texture, it has a position shift when
 *                 state changes.
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
#include <array>
#include "pngtexdb.hpp"
#include "sdldevice.hpp"
#include "buttonbase.hpp"

class TritexButton: public ButtonBase
{
    private:
        uint32_t m_texID[3];

    public:
        TritexButton(
                int nX,
                int nY,

                const uint32_t (&rstvTexID)[3],

                const std::function<void()> &fnOnOver  = nullptr,
                const std::function<void()> &fnOnClick = nullptr,

                int nOffXOnOver  = 0,
                int nOffYOnOver  = 0,
                int nOffXOnClick = 0,
                int nOffYOnClick = 0,

                bool    bOnClickDone = true,
                Widget *pwidget      = nullptr,
                bool    bFreewidget  = false)
            : ButtonBase
              {
                  nX, 
                  nY,
                  0,
                  0,

                  fnOnOver,
                  fnOnClick,

                  nOffXOnOver,
                  nOffYOnOver,
                  nOffXOnClick,
                  nOffYOnClick,

                  bOnClickDone,
                  pwidget,
                  bFreewidget,
              }
            , m_texID
              {
                  rstvTexID[0],
                  rstvTexID[1],
                  rstvTexID[2],
              }
        {
            int nW = 0;
            int nH = 0;
            for(int nState = 0; nState < 3; ++nState){
                if(m_texID[nState]){
                    extern PNGTexDB *g_progUseDB;
                    if(auto pTexture = g_progUseDB->Retrieve(m_texID[nState])){
                        int nCurrW, nCurrH;
                        if(!SDL_QueryTexture(pTexture, nullptr, nullptr, &nCurrW, &nCurrH)){
                            nW = (std::max<int>)(nCurrW, nW);
                            nH = (std::max<int>)(nCurrH, nH);
                        }
                    }
                }
            }

            // we allow buttons without any valid texture, in that case some extra work
            // can be done for special drawing
            m_w = nW;
            m_h = nH;
        }

        // use one specified texture ID
        TritexButton(
                int nX,
                int nY,

                uint32_t nBaseTexID,

                const std::function<void()> &fnOnOver  = [](){},
                const std::function<void()> &fnOnClick = [](){},

                int nOffXOnOver  = 0,
                int nOffYOnOver  = 0,
                int nOffXOnClick = 0,
                int nOffYOnClick = 0,

                bool    bOnClickDone = true,
                Widget *pwidget      = nullptr,
                bool    bFreewidget  = false)
            : TritexButton
              {
                  nX,
                  nY,

                  {
                      nBaseTexID + 0,
                      nBaseTexID + 1,
                      nBaseTexID + 2,
                  },

                  fnOnOver,
                  fnOnClick,

                  nOffXOnOver,
                  nOffYOnOver,
                  nOffXOnClick,
                  nOffYOnClick,

                  bOnClickDone,
                  pwidget,
                  bFreewidget
              }
        {}

    public:
        void drawEx(int,        // dst x on the screen coordinate
                int,            // dst y on the screen coordinate
                int,            // src x on the widget, take top-left as origin
                int,            // src y on the widget, take top-left as origin
                int,            // size to draw
                int) override;  // size to draw
};
