/*
 * =====================================================================================
 *
 *       Filename: memorypn.cpp
 *        Created: 05/24/2016 19:14:52
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

#include "memorypn.hpp"
#include "monoserver.hpp"

MemoryPN::MemoryPN()
    : MemoryChunkPN<64, 256, 4>()
{
    extern MemoryPN *g_memoryPN;
    if(g_memoryPN){
        extern MonoServer *g_monoServer;
        g_monoServer->addLog(LOGTYPE_WARNING, "one global memory pool instance please");
        g_monoServer->Restart();
    }
}
