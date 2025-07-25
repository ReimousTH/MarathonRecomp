#include "inspire_patches.h"
#include <api/Marathon.h>
#include <ui/game_window.h>
#include <os/logger.h>
#include <app.h>
#include <sdl_events.h>

std::string InspirePatches::s_sceneName;

//static SWA::Inspire::CScene* g_pScene;
static bool g_isFirstFrameChecked;
static uint32_t g_eventDispatchCount;

// Sonic's mouth EXPLODES for a single frame in Temple Entrance cutscene. 
// Looks very nasty. Let's hide morph models inbetween certain frames to solve it.
static bool g_loadedMouthExplosionAnimation;
static bool g_hideMorphModels;

// SWA::Inspire::CScene
// PPC_FUNC_IMPL(__imp__sub_82B98D80);
// PPC_FUNC(sub_82B98D80)
// {
//     __imp__sub_82B98D80(ctx, base);

//     g_pScene = (SWA::Inspire::CScene*)g_memory.Translate(ctx.r3.u32);
//     g_isFirstFrameChecked = false;
//     g_eventDispatchCount = 0;
// }

// // ~SWA::Inspire::CScene
// PPC_FUNC_IMPL(__imp__sub_82B98D30);
// PPC_FUNC(sub_82B98D30)
// {
//     __imp__sub_82B98D30(ctx, base);

//     g_pScene = nullptr;
//     InspirePatches::s_sceneName.clear();

//     SDL_User_EvilSonic(App::s_isWerehog);

//     g_loadedMouthExplosionAnimation = false;
//     g_hideMorphModels = false;
// }

// PPC_FUNC_IMPL(__imp__sub_82B9BA98);
// PPC_FUNC(sub_82B9BA98)
// {
//     auto sceneName = (Hedgehog::Base::CSharedString*)g_memory.Translate(ctx.r5.u32);

//     InspirePatches::s_sceneName = sceneName->c_str();

//     __imp__sub_82B9BA98(ctx, base);
// }

void AnimationDataMakeMidAsmHook(PPCRegister& r31, PPCRegister& r29, PPCRegister& r28)
{
    uint8_t* base = g_memory.base;

    if (r28.u32 == 0x222E0 &&
        strcmp(reinterpret_cast<const char*>(base + PPC_LOAD_U32(r31.u32)), "t0_04_SN") == 0 &&
        XXH3_64bits(base + r29.u32, r28.u32) == 0xEC634F0F379F478A)
    {
        g_loadedMouthExplosionAnimation = true;
    }
}

// Hedgehog::Mirage::CSingleMorphElement::Render
// PPC_FUNC_IMPL(__imp__sub_82E32048);
// PPC_FUNC(sub_82E32048)
// {
//     if (!g_hideMorphModels)
//         __imp__sub_82E32048(ctx, base);
// }

//void InspirePatches::DrawDebug()
//{
//    if (!g_pScene)
//    {
//        ImGui::Text("There is no active scene.");
//        return;
//    }
//
//    ImGui::Text("Name: %s", InspirePatches::s_sceneName.c_str());
//    ImGui::Text("Frame: %f", g_pScene->m_pData->Frame.get());
//    ImGui::Text("Cut: %d", g_pScene->m_pData->Cut.get());
//
//    static std::vector<float> g_loggedFrames{};
//
//    ImGui::Separator();
//
//    if (ImGui::Button("Log"))
//        g_loggedFrames.push_back(g_pScene->m_pData->Frame);
//
//    if (ImGui::Button("Clear"))
//        g_loggedFrames.clear();
//
//    if (g_loggedFrames.size())
//    {
//        ImGui::Separator();
//
//        for (auto& frame : g_loggedFrames)
//            ImGui::Text("%f", frame);
//    }
//}
//
//void InspirePatches::Update()
//{
//    if (!g_pScene || !InspirePatches::s_sceneName.size())
//        return;
//
//    g_hideMorphModels = g_loadedMouthExplosionAnimation && g_pScene->m_pData->Frame >= 185.0f &&
//        g_pScene->m_pData->Frame < 195.0f && InspirePatches::s_sceneName == "evrt_t0_04";
//}
