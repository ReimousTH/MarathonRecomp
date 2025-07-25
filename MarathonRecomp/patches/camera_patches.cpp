#include <api/Marathon.h>
#include <ui/game_window.h>
#include <user/config.h>
#include <gpu/video.h>
#include "camera_patches.h"
#include "aspect_ratio_patches.h"

//void CameraAspectRatioMidAsmHook(PPCRegister& r30, PPCRegister& r31)
//{
//    r30.u32 = 0;
//
//    auto camera = (SWA::CCamera*)g_memory.Translate(r31.u32);
//
//    // Dynamically adjust horizontal aspect ratio to window dimensions.
//    camera->m_HorzAspectRatio = g_aspectRatio;
//}
//
//float AdjustFieldOfView(float fieldOfView, float aspectRatio)
//{
//    if (Config::AspectRatio == EAspectRatio::OriginalNarrow)
//    {
//        // Replicate the original incorrect field of view formula if requested.
//        fieldOfView *= NARROW_ASPECT_RATIO;
//    }
//    else if (aspectRatio < WIDE_ASPECT_RATIO)
//    {
//        // Use proper VERT+ otherwise for narrow aspect ratios.
//        fieldOfView = 2.0 * atan(tan(0.5 * fieldOfView) / aspectRatio * WIDE_ASPECT_RATIO);
//    }
//
//    return fieldOfView;
//}
//
//void CameraFieldOfViewMidAsmHook(PPCRegister& r31, PPCRegister& f31)
//{
//    auto camera = (SWA::CCamera*)g_memory.Translate(r31.u32);
//
//    f31.f64 = AdjustFieldOfView(f31.f64, camera->m_HorzAspectRatio);
//}

// PPC_FUNC_IMPL(__imp__sub_824697B0);
// PPC_FUNC(sub_824697B0)
// {
//     auto pCamera = (SWA::CCamera*)g_memory.Translate(ctx.r3.u32);

//     pCamera->m_InvertX = Config::HorizontalCamera == ECameraRotationMode::Reverse;
//     pCamera->m_InvertY = Config::VerticalCamera == ECameraRotationMode::Reverse;

//     __imp__sub_824697B0(ctx, base);
// }

// // SWA::CCamera::UpdateSerial
// PPC_FUNC_IMPL(__imp__sub_82467890);
// PPC_FUNC(sub_82467890)
// {
//     if (g_needsResize)
//     {
//         // Recompute the projection matrix for one frame to fix stretching on pause menu.
//         auto r3 = ctx.r3;
//         auto r4 = ctx.r4;
//         sub_82468E38(ctx, base);
//         ctx.r3 = r3;
//         ctx.r4 = r4;
//     }

//     __imp__sub_82467890(ctx, base);
// }
