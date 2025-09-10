#include <api/Marathon.h>
#include <user/config.h>
#include <user/paths.h>
#include <kernel/heap.h>

#define MARARHON_CODE_SYSTEM_MOD_DIR "mods//"

PPC_FUNC_IMPL(__imp__sub_82160B98);
PPC_FUNC(sub_82160B98)
{
    auto pDocState = (Sonicteam::DocMarathonState*)(base + ctx.r3.u32);
    auto pArc =  (Sonicteam::SoX::ArcHandle*)Sonicteam::SoX::ArcHandleMgr::GetInstance()->CreateResource();
    pArc->m_ResourceName = "game:\\test.arc";


    __imp__sub_82160B98(ctx, base);
    
} 
