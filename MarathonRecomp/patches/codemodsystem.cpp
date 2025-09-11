#include <api/Marathon.h>
#include <user/config.h>
#include <user/paths.h>
#include <kernel/heap.h>

#define MARARHON_CODE_SYSTEM_MOD_DIR "mods//"

PPC_FUNC_IMPL(__imp__sub_82160B98);
PPC_FUNC(sub_82160B98)
{
    auto pDocState = (Sonicteam::DocMarathonState*)(base + ctx.r3.u32);
    __imp__sub_82160B98(ctx, base);
    struct ArcHandeMgrCreationParam :Sonicteam::SoX::IResourceMgrCreationParam
    {
        enum Folder :uint32_t
        {
            Folder_Xenon,
            Folder_Win32,
            Folder_Common
        };
        be<uint32_t> m_Folder;
        bool IsSave;
    };

    guest_stack_var<ArcHandeMgrCreationParam> _param;
    _param->IsSave = true;
    _param->m_Folder = ArcHandeMgrCreationParam::Folder_Win32;


    auto pArcMgr = (Sonicteam::SoX::ArcHandleMgr*)Sonicteam::SoX::ArcHandleMgr::GetInstance();
    auto pArc = pArcMgr->CreateResource(*_param.get());
    pArc->m_ResourceName = "archives/system.arc";
    pArc->Initialize(0, 0);
    
} 
