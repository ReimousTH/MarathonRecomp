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

#include <cstdint>
#include <algorithm>
#include <type_traits>

#include <utils/xbe.h>
#include <utils/string06.h>
#include <utils/vector06.h>






uint32_t read_be32ex(uint8_t* mem, uint32_t addr) {
   
    return (mem[addr] << 24) | (mem[addr + 1] << 16) |
        (mem[addr + 2] << 8) | mem[addr + 3];
}

uint32_t malloc_06(PPCContext& __restrict ctx, uint8_t* base,size_t size) {
    ctx.r3.u32 = size;
    sub_826DFDE0(ctx, base);
    return ctx.r3.u32;
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
       // printf("sub_828B30A8EX %x \n", file_string);
    }
    

    std::string file_path = file_string;
    file_path = file_path.substr(6);  // Remove first 7 characters
    file_path = gamePath + "\\" + file_path; // Prepend with gamePath
   

    if (std::filesystem::exists(file_path)) {
        goto loc_828B310C; // OldFileLoading
    }
   // printf("sub_828B30A8(LoadHandle, IFileHandle): %s -> %s\n", file_string, file_path.c_str());


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


struct RefO {
    xbe<uint32_t> ref_count;
};


//CreateMarathonState
PPC_FUNC_IMPL(__imp__sub_82160B98);
PPC_FUNC(sub_82160B98) {
    __imp__sub_82160B98(ctx, base);
    //Custom 

   
    uint32_t value = *get_ptr(0x82D370A4);
    uint64_t file_system_xenon = (uint64_t)g_memory.Translate(*get_ptr(0x82D370A4));
    vector06<string06>* svector = (vector06<string06>*)(file_system_xenon + 4);
  
    PPCContext cont_copy = ctx;
    
    //0 Xenon
    //1 Win
    //2 common
    //3 game
    //4 mods

    svector->push_back(string06("game:\\")); // 
    svector->push_back(string06("game:\\mods\\")); //
    svector->push_back(string06("game:\\..\\mods\\")); // not sure
    auto str = (*svector)[0].c_str();
    auto str3 = (*svector)[4].c_str();
    // svector->push_back(string06("mods:\\")); //add-root-support 

  /*
    printf("sub_82160B98 : %s \n", str);

    xbe<size_t* __ptr32,size_t* __ptr64> doc_marathon = xbe<size_t * __ptr32, size_t* __ptr64>::from_le_ptr((size_t*)ctx.r3.u32);
    size_t test = *doc_marathon;

    vector06<RefO*>* _vec_arcs = (vector06<RefO*>*)(doc_marathon + 0x5C40);
     */
   
    std::string mod_dir = (const char*)((GetGamePath() / "mods")).u8string().c_str();
   
   

 
  
        for (const auto& entry : std::filesystem::directory_iterator(mod_dir)) {
            // Process win32 archives
            const auto win32_path = entry.path() / "win32/archives";
            if (std::filesystem::exists(win32_path)) {
                for (const auto& entry_win32 : std::filesystem::directory_iterator(win32_path)) {
                    if (entry_win32.is_regular_file() && entry_win32.path().extension() == ".arc") {
                        /*

                        std::string _conv = (const char*)(entry_win32.path().u8string().c_str());
                        _conv = _conv.substr(7);

                        string06* _string_06 = new (g_userHeap.Alloc(sizeof(string06))) string06(_conv.c_str());
                        sxbex(size_t*, __ptr32) _string_06_ptr = (size_t*)_string_06;

                        size_t ret_buffer = (size_t)g_userHeap.Alloc(4);;
                        cont_copy.r3.u32 = (uint32_t)ret_buffer;
                        cont_copy.r4.u32 = (uint32_t)_string_06_ptr.get();
                        cont_copy.r5.u32 = 5;
                        cont_copy.r6.u32 = 1;





                        sub_82583528(cont_copy, base);

                        xbe<RefO*> _refo = *(RefO**)ret_buffer;
                        _refo->ref_count = _refo->ref_count + 1;

                        _vec_arcs->push_back(_refo);

                        g_userHeap.Free(_string_06);
                        g_userHeap.Free((void*)ret_buffer);
                        */
                    }
                }
            }

            // Process xenon archives
            const auto xenon_path = entry.path() / "xenon/archives";
            if (std::filesystem::exists(xenon_path)) {
                for (const auto& entry_xenon : std::filesystem::directory_iterator(xenon_path)) {
                    if (entry_xenon.is_regular_file() && entry_xenon.path().extension() == ".arc") {
                        /*
                        std::string _conv = (const char*)(entry_xenon.path().u8string().c_str());
                        _conv = _conv.substr(7);

                        string06* _string_06 = new (g_userHeap.Alloc(sizeof(string06))) string06(_conv.c_str());
                        sxbex(size_t*, __ptr32) _string_06_ptr = (size_t*)_string_06;

                        size_t ret_buffer = (size_t)g_userHeap.Alloc(4);;
                        cont_copy.r3.u32 = (uint32_t)ret_buffer;
                        cont_copy.r4.u32 = (uint32_t)_string_06_ptr.get();
                        cont_copy.r5.u32 = 5;
                        cont_copy.r6.u32 = 1;


                     


                        sub_82583528(cont_copy, base);

                        xbe<RefO*> _refo = *(RefO**)ret_buffer;
                        _refo->ref_count = 2;

                        g_userHeap.Free(_string_06);
                        g_userHeap.Free((void*)ret_buffer);
                        */
                    }
                }
            }
        }
   
  
    
   
    






    return;
}


//FileSystem (check if file exist) 
PPC_FUNC_IMPL(__imp__sub_825BE438);
PPC_FUNC(sub_825BE438) {

    std::string r4 =  GetCStringFromMemory06(ctx.r4.u32);
    std::string file_path = C06PathToGamePath(r4);

    printf("sub_825BE438:base %lx\n", (uint64_t)g_memory.base);

   
    string06* test_2 = (string06*)g_memory.Translate(ctx.r4.u32);
    const char* test = test_2->c_str();
    string06 test_1 = test;
    const char* test2 = test_1.c_str();



  //  printf("sub_825BE438(exist file[1,2]) : %s:capacity % d\n", test_1.c_str(), 0);


    if (std::filesystem::exists(file_path)) {
       
        ctx.r3.u32 = 1;
    }
    else {
        __imp__sub_825BE438(ctx, base);
    }

   
   
}


//DLC

PPC_FUNC_IMPL(__imp__sub_825B37C0);
PPC_FUNC(sub_825B37C0) {
    PPC_FUNC_PROLOGUE();
    uint32_t ea{};
    // mflr r12
    ctx.r12.u64 = ctx.lr;
    // bl 0x826de8c4
    ctx.lr = 0x825B37C8;
    __savegprlr_27(ctx, base);
    // stwu r1,-1584(r1)
    ea = -1584 + ctx.r1.u32;
    PPC_STORE_U32(ea, ctx.r1.u32);
    ctx.r1.u32 = ea;
    // addi r3,r1,96
    ctx.r3.s64 = ctx.r1.s64 + 96;
    // mr r27,r4
    ctx.r27.u64 = ctx.r4.u64;
    // bl 0x825b2370
    ctx.lr = 0x825B37D8;
    sub_825B2370(ctx, base);
    // lis r11,-32072
    ctx.r11.s64 = -2101870592;
    // addi r9,r1,88
    ctx.r9.s64 = ctx.r1.s64 + 88;
    // addi r8,r1,80
    ctx.r8.s64 = ctx.r1.s64 + 80;
    // li r7,1
    ctx.r7.s64 = 1;
    // li r6,0
    ctx.r6.s64 = 0;
    // li r5,2
    ctx.r5.s64 = 2;
    // lwz r3,-10552(r11)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r11.u32 + -10552);
    // li r4,0
    ctx.r4.s64 = 0;
    // bl 0x826fd5b8
    ctx.lr = 0x825B37FC;
    sub_826FD5B8(ctx, base);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // bne cr6,0x825b3948
    if (!ctx.cr6.eq) goto loc_825B3948;
    // li r7,0
    ctx.r7.s64 = 0;
    // lwz r3,88(r1)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r1.u32 + 88);
    // addi r6,r1,112
    ctx.r6.s64 = ctx.r1.s64 + 112;
    // li r5,308
    ctx.r5.s64 = 308;
    // addi r4,r1,192
    ctx.r4.s64 = ctx.r1.s64 + 192;
    // bl 0x826fd6a0
    ctx.lr = 0x825B381C;
    sub_826FD6A0(ctx, base);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // bne cr6,0x825b3940
    if (!ctx.cr6.eq) goto loc_825B3940;
    // lis r11,-32251
    ctx.r11.s64 = -2113601536;
    // li r30,15
    ctx.r30.s64 = 15;
    // addi r29,r11,-32288
    ctx.r29.s64 = ctx.r11.s64 + -32288;
    // li r31,0
    ctx.r31.s64 = 0;
    // li r28,-1
    ctx.r28.s64 = -1;
loc_825B3838:
    // addi r6,r1,456
    ctx.r6.s64 = ctx.r1.s64 + 456;
    // lwz r5,192(r1)
    ctx.r5.u64 = PPC_LOAD_U32(ctx.r1.u32 + 192);
    // mr r4,r29
    ctx.r4.u64 = ctx.r29.u64;
    // addi r3,r1,512
    ctx.r3.s64 = ctx.r1.s64 + 512;
    // bl 0x826e0998
    ctx.lr = 0x825B384C;
    sub_826E0998(ctx, base);
    // addi r11,r1,512
    ctx.r11.s64 = ctx.r1.s64 + 512;
    // stw r30,152(r1)
    PPC_STORE_U32(ctx.r1.u32 + 152, ctx.r30.u32);
    // stw r31,148(r1)
    PPC_STORE_U32(ctx.r1.u32 + 148, ctx.r31.u32);
    // mr r10,r11
    ctx.r10.u64 = ctx.r11.u64;
    // stb r31,132(r1)
    PPC_STORE_U8(ctx.r1.u32 + 132, ctx.r31.u8);
loc_825B3860:
    // lbz r9,0(r11)
    ctx.r9.u64 = PPC_LOAD_U8(ctx.r11.u32 + 0);
    // addi r11,r11,1
    ctx.r11.s64 = ctx.r11.s64 + 1;
    // cmplwi cr6,r9,0
    ctx.cr6.compare<uint32_t>(ctx.r9.u32, 0, ctx.xer);
    // bne cr6,0x825b3860
    if (!ctx.cr6.eq) goto loc_825B3860;
    // subf r11,r10,r11
    ctx.r11.s64 = ctx.r11.s64 - ctx.r10.s64;
    // addi r4,r1,512
    ctx.r4.s64 = ctx.r1.s64 + 512;
    // addi r11,r11,-1
    ctx.r11.s64 = ctx.r11.s64 + -1;
    // addi r3,r1,128
    ctx.r3.s64 = ctx.r1.s64 + 128;
    // rotlwi r5,r11,0
    ctx.r5.u64 = __builtin_rotateleft32(ctx.r11.u32, 0);
    // bl 0x82161e08
    ctx.lr = 0x825B3888;
    sub_82161E08(ctx, base);
    // addi r11,r1,456
    ctx.r11.s64 = ctx.r1.s64 + 456;
    // stw r30,184(r1)
    PPC_STORE_U32(ctx.r1.u32 + 184, ctx.r30.u32);
    // stw r31,180(r1)
    PPC_STORE_U32(ctx.r1.u32 + 180, ctx.r31.u32);
    // mr r10,r11
    ctx.r10.u64 = ctx.r11.u64;
    // stb r31,164(r1)
    PPC_STORE_U8(ctx.r1.u32 + 164, ctx.r31.u8);
loc_825B389C:
    // lbz r9,0(r11)
    ctx.r9.u64 = PPC_LOAD_U8(ctx.r11.u32 + 0);
    // addi r11,r11,1
    ctx.r11.s64 = ctx.r11.s64 + 1;
    // cmplwi cr6,r9,0
    ctx.cr6.compare<uint32_t>(ctx.r9.u32, 0, ctx.xer);
    // bne cr6,0x825b389c
    if (!ctx.cr6.eq) goto loc_825B389C;
    // subf r11,r10,r11
    ctx.r11.s64 = ctx.r11.s64 - ctx.r10.s64;
    // addi r4,r1,456
    ctx.r4.s64 = ctx.r1.s64 + 456;
    // addi r11,r11,-1
    ctx.r11.s64 = ctx.r11.s64 + -1;
    // addi r3,r1,160
    ctx.r3.s64 = ctx.r1.s64 + 160;
    // rotlwi r5,r11,0
    ctx.r5.u64 = __builtin_rotateleft32(ctx.r11.u32, 0);
    // bl 0x82161e08
    ctx.lr = 0x825B38C4;
    sub_82161E08(ctx, base);
    // addi r4,r1,160
    ctx.r4.s64 = ctx.r1.s64 + 160;
    // addi r3,r1,96
    ctx.r3.s64 = ctx.r1.s64 + 96;
    // bl 0x825b3628
    ctx.lr = 0x825B38D0;
    sub_825B3628(ctx, base);
    // mr r6,r28
    ctx.r6.u64 = ctx.r28.u64;
    // li r5,0
    ctx.r5.s64 = 0;
    // addi r4,r1,128
    ctx.r4.s64 = ctx.r1.s64 + 128;
    // bl 0x82161d10
    ctx.lr = 0x825B38E0;
    sub_82161D10(ctx, base);
    // lwz r11,184(r1)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r1.u32 + 184);
    // cmplwi cr6,r11,16
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 16, ctx.xer);
    // blt cr6,0x825b38f4
    if (ctx.cr6.lt) goto loc_825B38F4;
    // lwz r3,164(r1)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r1.u32 + 164);
    // bl 0x82186190
    ctx.lr = 0x825B38F4;
    sub_82186190(ctx, base);
loc_825B38F4:
    // lwz r11,152(r1)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r1.u32 + 152);
    // stw r30,184(r1)
    PPC_STORE_U32(ctx.r1.u32 + 184, ctx.r30.u32);
    // stw r31,180(r1)
    PPC_STORE_U32(ctx.r1.u32 + 180, ctx.r31.u32);
    // cmplwi cr6,r11,16
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, 16, ctx.xer);
    // stb r31,164(r1)
    PPC_STORE_U8(ctx.r1.u32 + 164, ctx.r31.u8);
    // blt cr6,0x825b3914
    if (ctx.cr6.lt) goto loc_825B3914;
    // lwz r3,132(r1)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r1.u32 + 132);
    // bl 0x82186190
    ctx.lr = 0x825B3914;
    sub_82186190(ctx, base);
loc_825B3914:
    // li r7,0
    ctx.r7.s64 = 0;
    // lwz r3,88(r1)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r1.u32 + 88);
    // addi r6,r1,112
    ctx.r6.s64 = ctx.r1.s64 + 112;
    // stw r30,152(r1)
    PPC_STORE_U32(ctx.r1.u32 + 152, ctx.r30.u32);
    // li r5,308
    ctx.r5.s64 = 308;
    // stw r31,148(r1)
    PPC_STORE_U32(ctx.r1.u32 + 148, ctx.r31.u32);
    // addi r4,r1,192
    ctx.r4.s64 = ctx.r1.s64 + 192;
    // stb r31,132(r1)
    PPC_STORE_U8(ctx.r1.u32 + 132, ctx.r31.u8);
    // bl 0x826fd6a0
    ctx.lr = 0x825B3938;
    sub_826FD6A0(ctx, base);
    // cmplwi cr6,r3,0
    ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
    // beq cr6,0x825b3838
    if (ctx.cr6.eq) goto loc_825B3838;
loc_825B3940:
    // lwz r3,88(r1)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r1.u32 + 88);
    // bl 0x82537280
    ctx.lr = 0x825B3948;
    sub_82537280(ctx, base);
loc_825B3948:
    // cmplwi cr6,r27,0
    ctx.cr6.compare<uint32_t>(ctx.r27.u32, 0, ctx.xer);
    // beq cr6,0x825b39d8
    if (ctx.cr6.eq) goto loc_825B39D8;
    // lwz r9,100(r1)
    ctx.r9.u64 = PPC_LOAD_U32(ctx.r1.u32 + 100);
    // addi r10,r1,96
    ctx.r10.s64 = ctx.r1.s64 + 96;
    // mr r31,r9
    ctx.r31.u64 = ctx.r9.u64;
    // lwz r11,0(r9)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r9.u32 + 0);
    // stw r10,80(r1)
    PPC_STORE_U32(ctx.r1.u32 + 80, ctx.r10.u32);
    // stw r11,84(r1)
    PPC_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
loc_825B3968:
    // cmplwi cr6,r10,0
    ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
    // beq cr6,0x825b397c
    if (ctx.cr6.eq) goto loc_825B397C;
    // addi r9,r1,96
    ctx.r9.s64 = ctx.r1.s64 + 96;
    // cmplw cr6,r10,r9
    ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r9.u32, ctx.xer);
    // beq cr6,0x825b3980
    if (ctx.cr6.eq) goto loc_825B3980;
loc_825B397C:
    // twi 31,r0,22
loc_825B3980:
    // subf r9,r11,r31
    ctx.r9.s64 = ctx.r31.s64 - ctx.r11.s64;
    // cntlzw r9,r9
    ctx.r9.u64 = ctx.r9.u32 == 0 ? 32 : __builtin_clz(ctx.r9.u32);
    // rlwinm r9,r9,27,31,31
    ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 27) & 0x1;
    // cntlzw r9,r9
    ctx.r9.u64 = ctx.r9.u32 == 0 ? 32 : __builtin_clz(ctx.r9.u32);
    // rlwinm r9,r9,27,31,31
    ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 27) & 0x1;
    // cmplwi cr6,r9,0
    ctx.cr6.compare<uint32_t>(ctx.r9.u32, 0, ctx.xer);
    // beq cr6,0x825b39d8
    if (ctx.cr6.eq) goto loc_825B39D8;
    // cmplwi cr6,r10,0
    ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
    // bne cr6,0x825b39a8
    if (!ctx.cr6.eq) goto loc_825B39A8;
    // twi 31,r0,22
loc_825B39A8:
    // lwz r10,4(r10)
    ctx.r10.u64 = PPC_LOAD_U32(ctx.r10.u32 + 4);
    // cmplw cr6,r11,r10
    ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
    // bne cr6,0x825b39b8
    if (!ctx.cr6.eq) goto loc_825B39B8;
    // twi 31,r0,22
loc_825B39B8:
    // addi r4,r11,40
    ctx.r4.s64 = ctx.r11.s64 + 40;
    // mr r3,r27
    ctx.r3.u64 = ctx.r27.u64;
    // bl 0x8217d608
    ctx.lr = 0x825B39C4;
    sub_8217D608(ctx, base);
    // addi r3,r1,80
    ctx.r3.s64 = ctx.r1.s64 + 80;
    // bl 0x825b1b30
    ctx.lr = 0x825B39CC;
    sub_825B1B30(ctx, base);
    // lwz r11,84(r1)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r1.u32 + 84);
    // lwz r10,80(r1)
    ctx.r10.u64 = PPC_LOAD_U32(ctx.r1.u32 + 80);
    // b 0x825b3968
    goto loc_825B3968;
loc_825B39D8:
    // lwz r11,100(r1)
    ctx.r11.u64 = PPC_LOAD_U32(ctx.r1.u32 + 100);
    // addi r10,r1,80
    ctx.r10.s64 = ctx.r1.s64 + 80;
    // addi r4,r1,96
    ctx.r4.s64 = ctx.r1.s64 + 96;
    // addi r3,r1,80
    ctx.r3.s64 = ctx.r1.s64 + 80;
    // lwz r9,0(r11)
    ctx.r9.u64 = PPC_LOAD_U32(ctx.r11.u32 + 0);
    // stw r11,84(r1)
    PPC_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
    // addi r11,r1,96
    ctx.r11.s64 = ctx.r1.s64 + 96;
    // stw r9,116(r1)
    PPC_STORE_U32(ctx.r1.u32 + 116, ctx.r9.u32);
    // addi r9,r1,112
    ctx.r9.s64 = ctx.r1.s64 + 112;
    // stw r11,80(r1)
    PPC_STORE_U32(ctx.r1.u32 + 80, ctx.r11.u32);
    // addi r11,r1,96
    ctx.r11.s64 = ctx.r1.s64 + 96;
    // ld r6,0(r10)
    ctx.r6.u64 = PPC_LOAD_U64(ctx.r10.u32 + 0);
    // stw r11,112(r1)
    PPC_STORE_U32(ctx.r1.u32 + 112, ctx.r11.u32);
    // ld r5,0(r9)
    ctx.r5.u64 = PPC_LOAD_U64(ctx.r9.u32 + 0);
    // bl 0x825b31e8
    ctx.lr = 0x825B3A14;
    sub_825B31E8(ctx, base);
    // lwz r3,100(r1)
    ctx.r3.u64 = PPC_LOAD_U32(ctx.r1.u32 + 100);
    // bl 0x82186190
    ctx.lr = 0x825B3A1C;
    sub_82186190(ctx, base);
    // addi r1,r1,1584
    ctx.r1.s64 = ctx.r1.s64 + 1584;
    // b 0x826de914
    __restgprlr_27(ctx, base);
    return;
}


