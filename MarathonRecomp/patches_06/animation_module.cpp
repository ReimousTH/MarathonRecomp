#include "animation_module.h"

#pragma STDC FENV_ACCESS ON  // Tell Clang we care about FP environment


#include <utils/xbe.h>
#include <utils/string06.h>
#include <kernel/heap.h>
#include <kernel/xam.h>




PPC_FUNC_IMPL(__imp__sub_825E9228);
PPC_FUNC(sub_825E9228) {

    __imp__sub_825E9228(ctx, base);

    return;
}

PPC_FUNC_IMPL(__imp__sub_82598EE0);
PPC_FUNC(sub_82598EE0) {

    __imp__sub_82598EE0(ctx, base);

    return;
}

PPC_FUNC_IMPL(__imp__sub_82599170);
PPC_FUNC(sub_82599170) {
    __imp__sub_82599170(ctx, base);
    return;
}

struct MotionPlayType {
    xbe<uint32_t> _vft;
    xbe<float> _4;
    xbe<float> _8;
};
struct AnimationCore {
    xbe<uint32_t> _vft;
    char __padding__[0x18];
    xbe<MotionPlayType*, big_endian_tag, uint32_t> _1C;
};
struct BRUH2 {
    xbe<float> _0;
    xbe<float> _4;
    xbe<float> _8;
    xbe<float> _C;
    xbe<float> _10;
    xbe<float> _14;
    xbe<float> _18;
    char __padding__[0x40];
    xbe<AnimationCore*,big_endian_tag,uint32_t> _5C;
};
PPC_FUNC_IMPL(__imp__sub_825963F0);
PPC_FUNC(sub_825963F0) {

    BRUH2* t = (BRUH2*)g_memory.Translate(ctx.r3.u32);
    uint32_t _vft = 0;
    if (t->_5C.raw()) {
        _vft  = t->_5C->_1C->_vft;

        float t1 = (float)t->_18;


        /*
        printf("vft : 0x%x[TimeF[%.15g : %.15g],Time[%.15g or %x + %.15g or %x = %.15g]\n",
            t->_5C->_1C->_4.value(),
            t->_5C->_1C->_8.value(),
            t->_5C->_1C->_vft.value(),
            ctx.f1.f64,
            ctx.f1.u64,
            (double)(float)t->_18,
            0x404,
            ctx.f1.f64 + (double)(float)t->_18
        );
        */


    }

  

    __imp__sub_825963F0(ctx, base);
    return;
}



struct BRUH {
    xbe<uint32_t> _0;
    xbe<float> _4;
    xbe<float> _8;
};
/*
PPC_FUNC_IMPL(__imp__sub_825C0B78);
PPC_FUNC(sub_825C0B78) {

    BRUH* _t = (BRUH*)g_memory.Translate(ctx.r3.u32);
    //__imp__sub_825C0B78(ctx, base);
    

    if (ctx.f1.f64 < (float)_t->_4)
        ctx.f1.f64 = (float)_t->_4;
    if ((float)_t->_8 < ctx.f1.f64)
        ctx.f1.f64 = (float)_t->_8;

    return;

}
*/
PPC_FUNC_IMPL(__imp__sub_825C1650);
PPC_FUNC(sub_825C1650){
    PPCContext _ctx = ctx;
    __imp__sub_825C1650(ctx,base);
  //  ctx.f1.f64 = 0.5;
  
        /*

    PPCRegister temp{};
    PPCRegister temp2{};
    PPCRegister temp3{};

    temp.u32 = PPC_LOAD_U32(_ctx.r3.u32 + 4);
    temp2.u32 = PPC_LOAD_U32(_ctx.r3.u32 + 8);
    temp3.u32 = PPC_LOAD_U32(_ctx.r3.u32 + 0xC);



    printf("sub_825C1650[Time[%.15g or %x : %.15g or %x : %.15g : %.15g or %x] - Result : %.15g]\n",

        temp.f64,
        temp.u32,
        temp2.f64,
        temp2.u32,
        temp3.f64,
        temp3.u32,
        _ctx.f1.f64,
        ctx.f1.f64);
        */
    return;
}
//08.07.2025 (Rei-san) # Animation END Flag FIX test 
PPC_FUNC_IMPL(__imp__sub_8222AFE0);
PPC_FUNC(sub_8222AFE0){
    PPC_FUNC_PROLOGUE();
    PPCContext _ctx = ctx;
    __imp__sub_8222AFE0(ctx, base);
    return;

    PPCRegister temp{};
    PPCRegister temp2{};
    PPCRegister temp3{};


    auto CurAnimID = PPC_LOAD_U32(_ctx.r3.u32 + 0x10);
    auto NexAnimID = _ctx.r4.u32;


  
    temp.u32 = PPC_LOAD_U32(_ctx.r3.u32 + 0x14);
    temp2.u32 = PPC_LOAD_U32(_ctx.r3.u32 + 0x18);
    temp3.u32 = PPC_LOAD_U32(_ctx.r3.u32 + 0xC);
    double unk0x14 = double(temp.f32);
    double unk0x18 = double(temp2.f32);
    double unk0xC = double(temp3.f32);
    auto delta = (float)_ctx.f1.f64;
    //temp solution

/*
    printf("8222AFE0[Anim[%03d:%03d]] - Time[%.15g or %x : %.15g or %x : %.15g or %x] - Result : %3d]\n",
        CurAnimID,
        ctx.r4.u32,
        unk0x14,
        temp.u32,
        unk0x18,
        temp2.u32,
        ctx.f1.f64,
        temp3.u32,
        ctx.r3.u64);
 */
    /*
    if (CurAnimID != NexAnimID) {
      ctx.r3.u32 = 0;
      return;
    }
    auto v5 = 0;
    if (unk0x14 > unk0x18)
    {
        if (unk0x14 <= delta) {
            ctx.r3.u32 = 1;
            return;
        }
        v5 = 0;
        if (delta <= unk0x18) {
            ctx.r3.u32 = 1;
            return;
        }
    }
    /*
    else if (unk0x14 == unk0x18) {
        ctx.r3.u32 = 1;
        return;
    }
    */
 /*
    else
    {
        if (unk0x14 > delta)
        {
            ctx.r3.u32 = 0;
            return;
        }
        v5 = 1;
        if (delta > unk0x18) {
            ctx.r3.u32 = 0;
            return;
        }
    }
    //printf("sub_8222AFE0 (%d, %d) - (%f, %f) - (delta : %f)\n", CurAnimID, NexAnimID, unk0x14, unk0x18,delta);
    ctx.r3.u32 = v5;
    */
  
    return;
  
}

PPC_FUNC_IMPL(__imp__sub_822385E0);
PPC_FUNC(sub_822385E0) {
   // printf("IModelSetAnimationFrameTime : %f\n", ctx.f1.f64);
    __imp__sub_822385E0(ctx, base);
    return;
}




//NPC Animation FrameRate
//No Enemies
//No Player
PPC_FUNC_IMPL(__imp__sub_824C27E0);
PPC_FUNC(sub_824C27E0) {
    __imp__sub_824C27E0(ctx, base);
    return;   
}

//here or
PPC_FUNC_IMPL(__imp__sub_8266DA38);
PPC_FUNC(sub_8266DA38) {
    __imp__sub_8266DA38(ctx, base);
    return;
}
//here
/*
PPC_FUNC_IMPL(__imp__sub_825B3AB0);
PPC_FUNC(sub_825B3AB0) {
    ctx.f1.f64 = double(  float(1.0f / float(ctx.f1.f64)) * (float)ctx.f2.f64);
    return;
}
*/


PPC_FUNC_IMPL(__imp__sub_825B3AB8);
PPC_FUNC(sub_825B3AB8) {

    __imp__sub_825B3AB8(ctx, base);
    return;

    PPC_FUNC_PROLOGUE();
    PPCRegister temp{};
    uint32_t ea{};
    // mflr r12
    ctx.r12.u64 = ctx.lr;
    // stw r12,-8(r1)
    PPC_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
    // stfd f29,-32(r1)
    ctx.fpscr.disableFlushMode();
    PPC_STORE_U64(ctx.r1.u32 + -32, ctx.f29.u64);
    // stfd f30,-24(r1)
    PPC_STORE_U64(ctx.r1.u32 + -24, ctx.f30.u64);
    // stfd f31,-16(r1)
    PPC_STORE_U64(ctx.r1.u32 + -16, ctx.f31.u64);
    // stwu r1,-112(r1)
    ea = -112 + ctx.r1.u32;
    PPC_STORE_U32(ea, ctx.r1.u32);
    ctx.r1.u32 = ea;
    // rlwinm r11,r3,0,11,15
    ctx.r11.u64 = __builtin_rotateleft64(ctx.r3.u32 | (ctx.r3.u64 << 32), 0) & 0x1F0000;
    // fmr f31,f1
    ctx.f31.f64 = ctx.f1.f64;
    // lis r10,4
    ctx.r10.s64 = 262144;
    // fmr f30,f2
    ctx.f30.f64 = ctx.f2.f64;
    // fmr f29,f3
    ctx.f29.f64 = ctx.f3.f64;
    // li r3,0
    ctx.r3.s64 = 0;
    // cmplw cr6,r11,r10
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
    // bgt cr6,0x825b3b90
    if (ctx.cr6.gt) goto loc_825B3B90;
    // beq cr6,0x825b3b64
    if (ctx.cr6.eq) goto loc_825B3B64;
    // lis r10,1
    ctx.r10.s64 = 65536;
    // cmplw cr6,r11,r10
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
    // beq cr6,0x825b3b38
    if (ctx.cr6.eq) goto loc_825B3B38;
    // lis r10,2
    ctx.r10.s64 = 131072;
    // cmplw cr6,r11,r10
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
    // bne cr6,0x825b3bcc
    if (!ctx.cr6.eq) goto loc_825B3BCC;
    // li r3,12
    ctx.r3.s64 = 12;
    // bl 0x82186158
    ctx.lr = 0x825B3B14;
    sub_82186158(ctx, base);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // beq cr6,0x825b3bc8
    if (ctx.cr6.eq) goto loc_825B3BC8;
    // lis r11,-32252
    ctx.r11.s64 = -2113667072;
    // lfs f0,14088(r11)
    ctx.fpscr.disableFlushMode();
    temp.u32 = PPC_LOAD_U32(ctx.r11.u32 + 14088);
    ctx.f0.f64 = double(temp.f32);
    // fdivs f0,f0,f31

    //f31 = 60.0
    //f29 = 42.0
    //f30 = 30.0
    // fdivs f0,f0,f31
   // fdivs f0, f0, f31  (single-precision division: f0 = f0 / f31)
    ctx.f0.f64 = (double)((float)ctx.f0.f64 / (float)ctx.f31.f64);

    // fmuls f2, f0, f29   (single-precision multiply: f2 = f0 * f29)
    ctx.f2.f64 = (double)((float)ctx.f0.f64 * (float)ctx.f29.f64);

    // fmu   f1, f0, f30   (single-precision multiply: f1 = f0 * f30)
    ctx.f1.f64 = (double)((float)ctx.f0.f64 * (float)ctx.f30.f64);

    if (ctx.f1.f64 >= 0.48 && ctx.f1.f64 <= 0.5) {
        printf("GOTEM\n");
    }
    // bl 0x825c0b60
    ctx.lr = 0x825B3B34;
    sub_825C0B60(ctx, base);
    // b 0x825b3bcc
    goto loc_825B3BCC;
loc_825B3B38:
    // li r3,12
    ctx.r3.s64 = 12;
    // bl 0x82186158
    ctx.lr = 0x825B3B40;
    sub_82186158(ctx, base);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // beq cr6,0x825b3bc8
    if (ctx.cr6.eq) goto loc_825B3BC8;
    // lis r11,-32252
    ctx.r11.s64 = -2113667072;
    // lfs f0,14088(r11)
    ctx.fpscr.disableFlushMode();
    temp.u32 = PPC_LOAD_U32(ctx.r11.u32 + 14088);
    ctx.f0.f64 = double(temp.f32);
    // fdivs f0,f0,f31
    ctx.f0.f64 = double(float(ctx.f0.f64) / ctx.f31.f64); //Frame (1.0/60.0)
    // fmuls f2,f0,f29
    ctx.f2.f64 = round(ctx.f0.f64 * ctx.f29.f64 * 1e15) / 1e15; //Frame (1.0/60.0) * 42(example) (frame len?)
    // fmuls f1,f0,f30
    ctx.f1.f64 = round(ctx.f0.f64 * ctx.f30.f64 * 1e15) / 1e15; //Frame (1.0/60.0) * 30(example)
    // bl 0x825c0b00
    ctx.lr = 0x825B3B60;
    sub_825C0B00(ctx, base);
    // b 0x825b3bcc
    goto loc_825B3BCC;
loc_825B3B64:
    // li r3,16
    ctx.r3.s64 = 16;
    // bl 0x82186158
    ctx.lr = 0x825B3B6C;
    sub_82186158(ctx, base);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // beq cr6,0x825b3bc8
    if (ctx.cr6.eq) goto loc_825B3BC8;
    // lis r11,-32252
    ctx.r11.s64 = -2113667072;
    // lfs f0,14088(r11)
    ctx.fpscr.disableFlushMode();
    temp.u32 = PPC_LOAD_U32(ctx.r11.u32 + 14088);
    ctx.f0.f64 = double(temp.f32);
    // fdivs f0,f0,f31
    ctx.f0.f64 = double(float(ctx.f0.f64) / ctx.f31.f64); //Frame (1.0/60.0)
    // fmuls f2,f0,f29
    ctx.f2.f64 = round(ctx.f0.f64 * ctx.f29.f64 * 1e15) / 1e15; //Frame (1.0/60.0) * 42(example) (frame len?)
    // fmuls f1,f0,f30
    ctx.f1.f64 = round(ctx.f0.f64 * ctx.f30.f64 * 1e15) / 1e15; //Frame (1.0/60.0) * 30(example)
    // bl 0x825c0b40
    ctx.lr = 0x825B3B8C;
    sub_825C0B40(ctx, base);
    // b 0x825b3bcc
    goto loc_825B3BCC;
loc_825B3B90:
    // lis r10,8
    ctx.r10.s64 = 524288;
    // cmplw cr6,r11,r10
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
    // bne cr6,0x825b3bcc
    if (!ctx.cr6.eq) goto loc_825B3BCC;
    // li r3,16
    ctx.r3.s64 = 16;
    // bl 0x82186158
    ctx.lr = 0x825B3BA4;
    sub_82186158(ctx, base);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // beq cr6,0x825b3bc8
    if (ctx.cr6.eq) goto loc_825B3BC8;
    // lis r11,-32252
    ctx.r11.s64 = -2113667072;
    // lfs f0,14088(r11)
    ctx.fpscr.disableFlushMode();
    temp.u32 = PPC_LOAD_U32(ctx.r11.u32 + 14088);
    ctx.f0.f64 = double(temp.f32);
    // fdivs f0,f0,f31
    ctx.f0.f64 = double(float(ctx.f0.f64) / ctx.f31.f64); //Frame (1.0/60.0)
    // fmuls f2,f0,f29
    ctx.f2.f64 = round(ctx.f0.f64 * ctx.f29.f64 * 1e15) / 1e15; //Frame (1.0/60.0) * 42(example) (frame len?)
    // fmuls f1,f0,f30
    ctx.f1.f64 = round(ctx.f0.f64 * ctx.f30.f64 * 1e15) / 1e15; //Frame (1.0/60.0) * 30(example)
    // bl 0x825c0ba0
    ctx.lr = 0x825B3BC4;
    sub_825C0BA0(ctx, base);
    // b 0x825b3bcc
    goto loc_825B3BCC;
loc_825B3BC8:
    // li r3,0
    ctx.r3.s64 = 0;
loc_825B3BCC:
    // addi r1,r1,112
    ctx.r1.s64 = ctx.r1.s64 + 112;
    // lwz r12,-8(r1)
    ctx.r12.u64 = PPC_LOAD_U32(ctx.r1.u32 + -8);
    // mtlr r12
    ctx.lr = ctx.r12.u64;
    // lfd f29,-32(r1)
    ctx.fpscr.disableFlushMode();
    ctx.f29.u64 = PPC_LOAD_U64(ctx.r1.u32 + -32);
    // lfd f30,-24(r1)
    ctx.f30.u64 = PPC_LOAD_U64(ctx.r1.u32 + -24);
    // lfd f31,-16(r1)
    ctx.f31.u64 = PPC_LOAD_U64(ctx.r1.u32 + -16);
    // blr 
    return;
}





#pragma pop
