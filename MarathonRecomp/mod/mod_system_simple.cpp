#include "mod_system_simple.h"


#include <cstdio>
#include <stdafx.h>
#include <kernel/memory.h>
#include <string>
#include <xex.h>
#include <kernel/function.h>
#include <kernel/memory.h>
#include <kernel/heap.h>
#include <kernel/xam.h>
#include <kernel/io/file_system.h>
#include <user/config.h>
#include <user/paths.h>
#include <user/registry.h>
#include <kernel/xdbf.h>

#include <cpu/guest_thread.h>


uint32_t read_be32ex(uint8_t* mem, uint32_t addr) {
    return (mem[addr] << 24) | (mem[addr + 1] << 16) |
        (mem[addr + 2] << 8) | mem[addr + 3];
}


std::string GetCStringFromMemory06(uint32_t reg) {
    auto* xenon_file_handle = (uint8_t*)g_memory.Translate(reg);
    uint32_t std_str_size = read_be32ex(xenon_file_handle, 0x18);

    const char* file_string;
    if (std_str_size >= 0x10) {
        uint32_t string_ptr = read_be32ex(xenon_file_handle, 4);
        file_string = (const char*)g_memory.Translate(string_ptr);
    }
    else {
        file_string = (const char*)(xenon_file_handle + 4);
    }
    return std::string(file_string);

}

std::string C06PathToGamePath(std::string file_string) {
    std::string file_path = file_string.substr(6); 
    return (const char*)(GetGamePath() / "game").u8string().c_str() + std::string("\\") + file_path;
}



//LoadHandle (process to load/search Handle from .arc)
PPC_FUNC_IMPL(__imp__sub_828B30A8);
PPC_FUNC(sub_828B30A8) {
    PPC_FUNC_PROLOGUE();
    uint32_t ea{};
    // mflr r12
    ctx.r12.u64 = ctx.lr;
    // bl 0x826de8cc
    ctx.lr = 0x828B30B0;
    __savegprlr_29(ctx, base);
    // stwu r1,-144(r1)
    ea = -144 + ctx.r1.u32;
    PPC_STORE_U32(ea, ctx.r1.u32);
    ctx.r1.u32 = ea;
    // mr r31,r3
    ctx.r31.u64 = ctx.r3.u64;
    // lbz r11,36(r31)
    ctx.r11.u64 = PPC_LOAD_U8(ctx.r31.u32 + 36);
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // bne cr6,0x828b3168
    if (!ctx.cr6.eq) goto loc_828B3168;
    // lis r30,-32045
    ctx.r30.s64 = -2100101120;
    // li r29,0
    ctx.r29.s64 = 0;
    // lwz r3,26384(r30)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r30.u32 + 26384);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // bne cr6,0x828b30e0
    if (!ctx.cr6.eq) goto loc_828B30E0;
    // bl 0x82163d20
    ctx.lr = 0x828B30DC;
    sub_82163D20(ctx, base);
    // stw r3,26384(r30)
    PPC_STORE_U32(ctx.r30.u32 + 26384, ctx.r3.u32);
loc_828B30E0:
    // addi r30,r31,8
    ctx.r30.s64 = ctx.r31.s64 + 8;
    // addi r5,r1,80
    ctx.r5.s64 = ctx.r1.s64 + 80;
    // mr r4,r30
    ctx.r4.u64 = ctx.r30.u64;
    // bl 0x82583680
    ctx.lr = 0x828B30F0;
    sub_82583680(ctx, base);
    // clrlwi r11,r3,24
    ctx.r11.u64 = ctx.r3.u32 & 0xFF;
    // mr r3,r31
    ctx.r3.u64 = ctx.r31.u64;
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // beq cr6,0x828b310c


    std::string gamePath = (const char*)(GetGamePath() / "game").u8string().c_str();
   

    auto xenon_file_handle = (uint8_t*)g_memory.Translate(ctx.r31.u32);
    auto xenon_file_handle_32 = (uint32_t)g_memory.Translate(ctx.r31.u32);
    auto std_str_size = read_be32ex(xenon_file_handle, 8+0x18);
    const char* file_string = (const char*)g_memory.Translate(xenon_file_handle_32 + 8 + 4);

    if (std_str_size >= 0x10) {
        file_string  = (const char*)g_memory.Translate(read_be32ex(xenon_file_handle, 8 + 4));
    }
    else
    {
        printf("sub_828B30A8EX %x \n", file_string);
    }
    std::string file_path = file_string;
    file_path = file_path.substr(6);  // Remove first 7 characters
    file_path = gamePath + "\\" + file_path; // Prepend with gamePath
   

    if (std::filesystem::exists(file_path)) {
        goto loc_828B310C; // OldFileLoading
    }
    printf("sub_828B30A8(LoadHandle, IFileHandle): %s -> %s\n", file_string, file_path.c_str());


    if (ctx.cr6.eq) goto loc_828B310C;
    // addi r4,r1,80
    ctx.r4.s64 = ctx.r1.s64 + 80;
    // bl 0x828b2bf8
    ctx.lr = 0x828B3108;
    sub_828B2BF8(ctx, base); //LoadFileFromArc
    // b 0x828b3114
    goto loc_828B3114; //
loc_828B310C:
    // mr r4,r30
    ctx.r4.u64 = ctx.r30.u64;
    // bl 0x828b2b18
    ctx.lr = 0x828B3114;
    sub_828B2B18(ctx, base); // OldFileLoading
loc_828B3114:
    // lwz r4,48(r31)
    ctx.r4.u64 = PPC_LOAD_U32(ctx.r31.u32 + 48);
    // cmplwi cr6,r4,0
    ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
    // beq cr6,0x828b315c
    if (ctx.cr6.eq) goto loc_828B315C;
    // lis r11,-32159
    ctx.r11.s64 = -2107572224;
    // addi r11,r11,23904
    ctx.r11.s64 = ctx.r11.s64 + 23904;
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // beq cr6,0x828b315c
    if (ctx.cr6.eq) goto loc_828B315C;
    // addi r3,r31,52
    ctx.r3.s64 = ctx.r31.s64 + 52;
    // lwz r11,0(r3)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r3.u32 + 0);
    // cntlzw r11,r11
    ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
    // rlwinm r11,r11,27,31,31
    ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x1;
    // cmplwi cr6,r11,0
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
    // bne cr6,0x828b3158
    if (!ctx.cr6.eq) goto loc_828B3158;
    // ld r5,40(r31)
    ctx.r5.u64 = PPC_LOAD_U64(ctx.r31.u32 + 40);
    // bl 0x828b3048
    ctx.lr = 0x828B3150;
    sub_828B3048(ctx, base);
    // mr r29,r3
    ctx.r29.u64 = ctx.r3.u64;
    // b 0x828b315c
    goto loc_828B315C;
loc_828B3158:
    // li r29,1
    ctx.r29.s64 = 1;
loc_828B315C:
    // li r11,1
    ctx.r11.s64 = 1;
    // stb r29,37(r31)
    PPC_STORE_U8(ctx.r31.u32 + 37, ctx.r29.u8);
    // stb r11,36(r31)
    PPC_STORE_U8(ctx.r31.u32 + 36, ctx.r11.u8);
loc_828B3168:
    // lbz r3,37(r31)
    ctx.r3.u64 = PPC_LOAD_U8(ctx.r31.u32 + 37);
    // addi r1,r1,144
    ctx.r1.s64 = ctx.r1.s64 + 144;
    // b 0x826de91c
    __restgprlr_29(ctx, base);
    return;
}




//FileSystem (check if file exist)
PPC_FUNC_IMPL(__imp__sub_825BE438);
PPC_FUNC(sub_825BE438) {

    std::string r4 =  GetCStringFromMemory06(ctx.r4.u32);
    std::string file_path = C06PathToGamePath(r4);

    printf("sub_825BE438(exist file[1,2]) : %s", file_path.c_str());

    if (std::filesystem::exists(file_path)) {
       
        ctx.r3.u32 = 1;
    }
    else {
        __imp__sub_825BE438(ctx, base);
    }

   
   
}




