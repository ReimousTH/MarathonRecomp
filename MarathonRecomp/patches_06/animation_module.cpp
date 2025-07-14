#include "animation_module.h"
#pragma STDC FENV_ACCESS ON  // Tell Clang we care about FP environment


PPC_FUNC_IMPL(__imp__sub_825E9228);
PPC_FUNC(sub_825E9228) {

    ctx.r3.u32 = 1;
    return;
}

PPC_FUNC_IMPL(__imp__sub_82598EE0);
PPC_FUNC(sub_82598EE0) {

    PPC_FUNC_PROLOGUE();
    uint32_t ea{};
    // mflr r12
    ctx.r12.u64 = ctx.lr;
    // stw r12,-8(r1)
    PPC_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
    // std r30,-24(r1)
    PPC_STORE_U64(ctx.r1.u32 + -24, ctx.r30.u64);
    // std r31,-16(r1)
    PPC_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
    // stfd f30,-40(r1)
    ctx.fpscr.disableFlushMode();
    PPC_STORE_U64(ctx.r1.u32 + -40, ctx.f30.u64);
    // stfd f31,-32(r1)
    PPC_STORE_U64(ctx.r1.u32 + -32, ctx.f31.u64);
    // stwu r1,-144(r1)
    ea = -144 + ctx.r1.u32;
    PPC_STORE_U32(ea, ctx.r1.u32);
    ctx.r1.u32 = ea;
    // mr r31,r3
    ctx.r31.u64 = ctx.r3.u64;
    // fmr f30,f1
    ctx.f30.f64 = ctx.f1.f64;
    // fmr f31,f2
    ctx.f31.f64 = ctx.f2.f64;
    // mr r7,r8
    ctx.r7.u64 = ctx.r8.u64;
    // mr r30,r9
    ctx.r30.u64 = ctx.r9.u64;
    // lwz r3,92(r31)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r31.u32 + 92);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // beq cr6,0x82598f64
    if (ctx.cr6.eq) goto loc_82598F64;
    // lis r11,-32159
    ctx.r11.s64 = -2107572224;
    // addi r11,r11,23904
    ctx.r11.s64 = ctx.r11.s64 + 23904;
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // beq cr6,0x82598f64
    if (ctx.cr6.eq) goto loc_82598F64;
    // lwz r8,52(r31)
    ctx.r8.u64 = PPC_LOAD_U32(ctx.r31.u32 + 52);
    // cmplwi cr6,r8,0
    ctx.cr6.compare<uint32_t>(ctx.r8.u32, 0, ctx.xer);
    // beq cr6,0x82598f4c
    if (ctx.cr6.eq) goto loc_82598F4C;
    // lwz r11,56(r31)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r31.u32 + 56);
    // subf r11,r8,r11
    ctx.r11.s64 = ctx.r11.s64 - ctx.r8.s64;
    // srawi r11,r11,3
    ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x7) != 0);
    ctx.r11.s64 = ctx.r11.s32 >> 3;
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // bne cr6,0x82598f50
    if (!ctx.cr6.eq) goto loc_82598F50;
loc_82598F4C:
    printf("loc_82598F4C : twi 31,r0,22\n");
    // twi 31,r0,22
loc_82598F50:
    // lwz r5,0(r5)
    ctx.r5.u64 = PPC_LOAD_U32(ctx.r5.u32 + 0);
    // fmr f1,f31
    ctx.fpscr.disableFlushMode();
    ctx.f1.f64 = ctx.f31.f64;
    // lwz r4,0(r4)
    ctx.r4.u64 = PPC_LOAD_U32(ctx.r4.u32 + 0);
    // bl 0x825c1b58
    ctx.lr = 0x82598F60;
    sub_825C1B58(ctx, base);
    // fmr f31,f1
    ctx.fpscr.disableFlushMode();
    ctx.f31.f64 = ctx.f1.f64;
loc_82598F64:
    // lwz r11,100(r31)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r31.u32 + 100);
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // beq cr6,0x82598fa8
     goto loc_82598FA8;
    // lis r11,-32159
    ctx.r11.s64 = -2107572224;
    // addi r11,r11,23904
    ctx.r11.s64 = ctx.r11.s64 + 23904;
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // beq cr6,0x82598fa8
    if (ctx.cr6.eq) goto loc_82598FA8;
    // fcmpu cr6,f30,f31
    ctx.fpscr.disableFlushMode();
    ctx.cr6.compare(ctx.f30.f64, ctx.f31.f64);
    // beq cr6,0x82598fa8
    if (ctx.cr6.eq) goto loc_82598FA8;
    // mr r4,r30
    ctx.r4.u64 = ctx.r30.u64;
    // addi r3,r1,80
    ctx.r3.s64 = ctx.r1.s64 + 80;
    // bl 0x825b4a48
    ctx.lr = 0x82598F94;
    sub_825B4A48(ctx, base);
    // addi r6,r1,80
    ctx.r6.s64 = ctx.r1.s64 + 80;
    // lwz r3,100(r31)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r31.u32 + 100);
    // fmr f2,f31
    ctx.fpscr.disableFlushMode();
    ctx.f2.f64 = ctx.f31.f64;
    // fmr f1,f30
    ctx.f1.f64 = ctx.f30.f64;
    // bl 0x825c1dd8
    ctx.lr = 0x82598FA8;
    sub_825C1DD8(ctx, base);
loc_82598FA8:
    // fmr f1,f31
    ctx.fpscr.disableFlushMode();
    ctx.f1.f64 = ctx.f31.f64;
    // addi r1,r1,144
    ctx.r1.s64 = ctx.r1.s64 + 144;
    // lwz r12,-8(r1)
    ctx.r12.u64 = PPC_LOAD_U32(ctx.r1.u32 + -8);
    // mtlr r12
    ctx.lr = ctx.r12.u64;
    // lfd f30,-40(r1)
    ctx.f30.u64 = PPC_LOAD_U64(ctx.r1.u32 + -40);
    // lfd f31,-32(r1)
    ctx.f31.u64 = PPC_LOAD_U64(ctx.r1.u32 + -32);
    // ld r30,-24(r1)
    ctx.r30.u64 = PPC_LOAD_U64(ctx.r1.u32 + -24);
    // ld r31,-16(r1)
    ctx.r31.u64 = PPC_LOAD_U64(ctx.r1.u32 + -16);
    // blr 

    return;
}

PPC_FUNC_IMPL(__imp__sub_82599170);
PPC_FUNC(sub_82599170) {

    PPC_FUNC_PROLOGUE();
    // lwz r11,36(r3)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r3.u32 + 36);
    // addi r9,r3,80
    ctx.r9.s64 = ctx.r3.s64 + 80;
    // lwz r8,40(r3)
    ctx.r8.u64 = PPC_LOAD_U32(ctx.r3.u32 + 40);
    // addi r4,r3,44
    ctx.r4.s64 = ctx.r3.s64 + 44;
    // addi r5,r11,100
    ctx.r5.s64 = ctx.r11.s64 + 100;
    // fadds f2,f1,f2
    ctx.fpscr.disableFlushMode();
   
    //fesetround(FE_TOWARDZERO);    // Set new mode (FE_TONEAREST, FE_UPWARD, etc.)

    ctx.f2.f64 = (float(ctx.f1.f64) + float(ctx.f2.f64));
    ctx.f1.f64 = float(ctx.f2.f64);
    // b 0x82598ee0
    sub_82598EE0(ctx, base);
    return;
}
PPC_FUNC_IMPL(__imp__sub_825963F0);
PPC_FUNC(sub_825963F0) {

  
    PPC_FUNC_PROLOGUE();
    PPCRegister temp{};
    uint32_t ea{};
    // mflr r12
    ctx.r12.u64 = ctx.lr;
    // stw r12,-8(r1)
    PPC_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
    // std r31,-16(r1)
    PPC_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
    // stwu r1,-96(r1)
    ea = -96 + ctx.r1.u32;
    PPC_STORE_U32(ea, ctx.r1.u32);
    ctx.r1.u32 = ea;
    // mr r31,r3
    ctx.r31.u64 = ctx.r3.u64;
    // fmr f2,f1
    ctx.fpscr.disableFlushMode();
    ctx.f2.f64 = ctx.f1.f64;
    // lwz r4,20(r31)
    ctx.r4.u64 = PPC_LOAD_U32(ctx.r31.u32 + 20);
    // cntlzw r11,r4
    ctx.r11.u64 = ctx.r4.u32 == 0 ? 32 : __builtin_clz(ctx.r4.u32);
    // rlwinm r11,r11,27,31,31
    ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x1;
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // bne cr6,0x82596444
    if (!ctx.cr6.eq) goto loc_82596444;
    // lis r11,-32256
    ctx.r11.s64 = -2113929216;
    // lfs f0,3544(r11)
    temp.u32 = PPC_LOAD_U32(ctx.r11.u32 + 3544);
    ctx.f0.f64 = double(temp.f32);
    // fcmpu cr6,f2,f0
    ctx.cr6.compare(ctx.f2.f64, ctx.f0.f64);
    // beq cr6,0x82596444
    if (ctx.cr6.eq) goto loc_82596444;
    // lwz r11,0(r31)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r31.u32 + 0);
    // lfs f1,24(r31)
    temp.u32 = PPC_LOAD_U32(ctx.r31.u32 + 24);
    ctx.f1.f64 = double(temp.f32);
    // lwz r11,40(r11)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r11.u32 + 40);
    // mtctr r11
    ctx.ctr.u64 = ctx.r11.u64;
    // bctrl 
    ctx.lr = 0x82596440;
    PPC_CALL_INDIRECT_FUNC(ctx.ctr.u32);
    // stfs f1,24(r31)
    ctx.fpscr.disableFlushMode();
    temp.f32 = float(ctx.f1.f64);
    PPC_STORE_U32(ctx.r31.u32 + 24, temp.u32);
loc_82596444:
    // addi r1,r1,96
    ctx.r1.s64 = ctx.r1.s64 + 96;
    // lwz r12,-8(r1)
    ctx.r12.u64 = PPC_LOAD_U32(ctx.r1.u32 + -8);
    // mtlr r12
    ctx.lr = ctx.r12.u64;
    // ld r31,-16(r1)
    ctx.r31.u64 = PPC_LOAD_U64(ctx.r1.u32 + -16);
    // blr 
    return;
}


PPC_FUNC_IMPL(__imp__sub_825C0B78);
PPC_FUNC(sub_825C0B78) {
    PPC_FUNC_PROLOGUE();
    PPCRegister temp{};
    // lfs f0,4(r3)
    ctx.fpscr.disableFlushMode();
    temp.u32 = PPC_LOAD_U32(ctx.r3.u32 + 4);
    ctx.f0.f64 = double(temp.f32);
    // fcmpu cr6,f1,f0
    ctx.cr6.compare(ctx.f1.f64, ctx.f0.f64);
    // bge cr6,0x825c0b88
    if (ctx.cr6.gt) goto loc_825C0B88;
    // fmr f1,f0
    ctx.f1.f64 = ctx.f0.f64;
loc_825C0B88:
    // lfs f0,8(r3)
    ctx.fpscr.disableFlushMode();
    temp.u32 = PPC_LOAD_U32(ctx.r3.u32 + 8);
    ctx.f0.f64 = double(temp.f32);
    // fcmpu cr6,f0,f1
    ctx.cr6.compare(ctx.f0.f64, ctx.f1.f64);
    // bgelr cr6
    if (ctx.cr6.gt) return; //-> bgt
    // fmr f1,f0
    ctx.f1.f64 = ctx.f0.f64;
    // blr 
    return;
}

//08.07.2025 (Rei-san) # Animation END Flag FIX test 
PPC_FUNC_IMPL(__imp__sub_8222AFE0);
PPC_FUNC(sub_8222AFE0){
    PPC_FUNC_PROLOGUE();


    PPCRegister temp{};
    PPCRegister temp2{};


    auto CurAnimID = PPC_LOAD_U32(ctx.r3.u32 + 0x10);
    auto NexAnimID = ctx.r4.u32;



    temp.u32 = PPC_LOAD_U32(ctx.r3.u32 + 0x14);
    temp2.u32 = PPC_LOAD_U32(ctx.r3.u32 + 0x18);
    float unk0x14 = temp.f32;
    float unk0x18 = temp2.f32;
    float delta = (float)ctx.f1.f64;
    //temp solution
 
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
  

    printf("sub_8222AFE0 (%d, %d) - (%f, %f) - (delta : %f)\n", CurAnimID, NexAnimID, unk0x14, unk0x18,delta);
    ctx.r3.u32 = v5;
    return;
  
}

PPC_FUNC_IMPL(__imp__sub_822385E0);
PPC_FUNC(sub_822385E0) {
   // printf("IModelSetAnimationFrameTime : %f\n", ctx.f1.f64);
    __imp__sub_822385E0(ctx, base);
}

PPC_FUNC_IMPL(__imp__sub_825B3AB8);
PPC_FUNC(sub_825B3AB8){

    printf(" sub_825B3AB8 ctx.r3.u32 : %x\n", ctx.r3.u32);

    /*
    ctx.r3.u32 = 0x80000; //Mirror Animation Always
    ctx.r3.u32 = 0x40000; //Repeat Animation Always
    ctx.r3.u32 = 0x10000; //Repeat_NO Animation Always
    */
    if (ctx.r3.u32 & 0x20000 != 0) {
        ctx.r3.u32 = 0x40000; //Const Repeat-> Repeat
    }
  
    __imp__sub_825B3AB8(ctx, base);
}


//NPC Animation FrameRate
//No Enemies
//No Player
PPC_FUNC_IMPL(__imp__sub_824C27E0);
PPC_FUNC(sub_824C27E0) {
    return;
//    __imp__sub_824C27E0(ctx,base);
}


#pragma pop
