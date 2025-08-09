#include <api/Marathon.h>
#include <cpu/guest_stack_var.h>
#include <os/logger.h>
#include <user/config.h>
#include <app.h>
#include <stdx/vector.h>

// Sonicteam::Player::State::TailsContext::Update
PPC_FUNC_IMPL(__imp__sub_8221A7D8);
PPC_FUNC(sub_8221A7D8)
{
    if (!Config::TailsGauge)
    {
        __imp__sub_8221A7D8(ctx, base);
        return;
    }

    auto pTailsContext = (Sonicteam::Player::State::TailsContext*)(base + ctx.r3.u32);
    auto pPlayer = pTailsContext->m_pScore->m_pPlayer;

    if (auto pGauge = pPlayer->GetGauge<Sonicteam::Player::SonicGauge>())
    {
        pGauge->m_Maximum = 100.0f;
        pGauge->m_Value = (100.0f / pTailsContext->m_FlightDuration) * pTailsContext->m_FlightTime;
    }

    auto pState = pPlayer->GetMachine<Sonicteam::Player::State::Machine2>()->m_pState;
    auto pGameImp = App::s_pApp->m_pDoc->GetDocMode<Sonicteam::GameMode>()->m_pGameImp;

    auto maturityValue = 1.0f;

    // Set maturity value if the current state is Sonicteam::Player::State::TailsFlight.
    if (pState->m_pVftable.ptr == 0x82005404)
        maturityValue = (1.0f / pTailsContext->m_FlightLimit) * pState->m_Time;

    for (int i = 0; i < 4; i++)
    {
        if (pGameImp->m_PlayerData[i].ActorID == pPlayer->m_ActorID.get())
            pGameImp->m_PlayerData[i].MaturityValue = maturityValue;
    }

    __imp__sub_8221A7D8(ctx, base);
}

// Sonicteam::Player::State::*Context IDynamicLink::Init
PPC_FUNC_IMPL(__imp__sub_8220F330);
PPC_FUNC(sub_8220F330)
{
    if (!Config::TailsGauge)
    {
        __imp__sub_8220F330(ctx, base);
        return;
    }

    auto pDynamicLink = (Sonicteam::Player::IDynamicLink*)(base + ctx.r3.u32);
    auto spPlugin = (boost::shared_ptr<Sonicteam::Player::IPlugIn>*)(base + ctx.r4.u32);

    // If this call is from TailsContext and this plugin is Sonicteam::Player::Score, set up the action gauge.
    // This is typically set up by OpenGauge in Lua, but we can't do this here.
    if (pDynamicLink->m_pVftable.ptr == 0x8200B7F4 && spPlugin->get()->m_Name == "score")
    {
        auto pScore = (Sonicteam::Player::Score*)spPlugin->get();
        auto pSonicGauge = GuestToHostFunction<Sonicteam::Player::SonicGauge*>(sub_8223F208, g_userHeap.Alloc(sizeof(Sonicteam::Player::SonicGauge)));

        guest_stack_var<boost::shared_ptr<Sonicteam::Player::IGauge>> spSonicGauge;

        // Make shared pointer.
        GuestToHostFunction<void>(sub_821BEAB0, spSonicGauge.get(), pSonicGauge);

        // Add gauge plugin to player.
        GuestToHostFunction<void>(sub_821BECE0, pScore->m_pPlayer.get(), spSonicGauge.get(), 1);

        pScore->m_pPlayer->m_spGauge = *spSonicGauge.get();
    }

    __imp__sub_8220F330(ctx, base);
}


bool MidairMachSpeedControl1()
{
    return Config::MidairControlForMachSpeed;
}

bool MidairMachSpeedControl2()
{
    return Config::MidairControlForMachSpeed;
}

bool MidairSnowboardControl1()
{
    return Config::MidairControlForSnowboards;
}

bool MidairSnowboardControl2()
{
    return Config::MidairControlForSnowboards;
}

bool MidairSnowboardControl3()
{
    return Config::MidairControlForSnowboards;
}



////////////////////////////////////////////////////////
/////////////   Sonic Gauge Restoration ////////////////
////////////////////////////////////////////////////////

const Sonicteam::Player::State::SonicContext::GemsS gemConversionTable[] = {
    Sonicteam::Player::State::SonicContext::GemsS::SBlue,   
    Sonicteam::Player::State::SonicContext::GemsS::SRed,    
    Sonicteam::Player::State::SonicContext::GemsS::SGreen,  
    Sonicteam::Player::State::SonicContext::GemsS::SPurple, 
    Sonicteam::Player::State::SonicContext::GemsS::SSky,    
    Sonicteam::Player::State::SonicContext::GemsS::SWhite,  
    Sonicteam::Player::State::SonicContext::GemsS::SYellow, 
    Sonicteam::Player::State::SonicContext::GemsS::SSuper   
};
const Sonicteam::Player::State::SonicContext::GemsS gemConversionTable2[] = {
    Sonicteam::Player::State::SonicContext::GemsS::SNone,
    Sonicteam::Player::State::SonicContext::GemsS::SBlue,
    Sonicteam::Player::State::SonicContext::GemsS::SRed,
    Sonicteam::Player::State::SonicContext::GemsS::SGreen,
    Sonicteam::Player::State::SonicContext::GemsS::SPurple,
    Sonicteam::Player::State::SonicContext::GemsS::SSky,
    Sonicteam::Player::State::SonicContext::GemsS::SWhite,
    Sonicteam::Player::State::SonicContext::GemsS::SYellow,
    Sonicteam::Player::State::SonicContext::GemsS::SSuper
};


const float c_maturity_max = 100.0;
const float c_maturity_level_max = 3.0;
const float c_maturity_point = 3.0;

class SonicGaugeEX :public Sonicteam::Player::SonicGauge
{
public:

    be<float> m_MNone;
    be<float> m_MGreen;
    be<float> m_MBlue;
    be<float> m_MWhite;
    be<float> m_MSky;
    be<float> m_MYellow;
    be<float> m_MSuper;
    be<float> m_MRed;
    be<float> m_MPurple;

    be<float> m_MAXMNone;
    be<float> m_MAXMGreen;
    be<float> m_MAXMBlue;
    be<float> m_MAXMWhite;
    be<float> m_MAXMSky;
    be<float> m_MAXMYellow;
    be<float> m_MAXMSuper;
    be<float> m_MAXMRed;
    be<float> m_MAXMPurple;

    //Level Drain
    be<float> m_MDNone1;
    be<float> m_MDNone2;
    be<float> m_MDNone3;
    be<float> m_MDGreen1;
    be<float> m_MDGreen2;
    be<float> m_MDGreen3;
    be<float> m_MDBlue1;
    be<float> m_MDBlue2;
    be<float> m_MDBlue3;
    be<float> m_MDWhite1;
    be<float> m_MDWhite2;
    be<float> m_MDWhite3;
    be<float> m_MDSky1;
    be<float> m_MDSky2;
    be<float> m_MDSky3;
    be<float> m_MDYellow1;
    be<float> m_MDYellow2;
    be<float> m_MDYellow3;
    be<float> m_MDSuper1;
    be<float> m_MDSuper2;
    be<float> m_MDSuper3;
    be<float> m_MDRed1;
    be<float> m_MDRed2;
    be<float> m_MDRed3;
    be<float> m_MDPurple1;
    be<float> m_MDPurple2;
    be<float> m_MDPurple3;


    bool Initialized;

    be<float>& GetMLevel(Sonicteam::Player::State::SonicContext::GemsS gem)
    {
        return (&m_MNone)[gem];
    }
    be<float>& GetMMax(Sonicteam::Player::State::SonicContext::GemsS gem)
    {
        return (&m_MAXMNone)[gem];
    }


};





Sonicteam::GameImp::PlayerData* GetPlayerData(Sonicteam::Player::Object* pPlayer)
{
    auto pGameImp = App::s_pApp->m_pDoc->GetDocMode<Sonicteam::GameMode>()->m_pGameImp;
    for (int i = 0; i < 4; i++)
    {
        if (pGameImp->m_PlayerData[i].ActorID == pPlayer->m_ActorID.get())
        {
            return  &pGameImp->m_PlayerData[i];
        }
    }
    return 0;
}


uint8_t ExtraGetMaturityLevelToPlayer(Sonicteam::GameImp::PlayerData* pPlayerData, uint32_t index)
{
    uint8_t byte = pPlayerData->Extra[index / 4];
    uint8_t shift = (index % 4) * 2;              
    return (byte >> shift) & 0x03;                
}
float ExtraGetGemDrainValueMaturity(SonicGaugeEX* gauge, Sonicteam::GameImp::PlayerData* pPlayerData, uint32_t index)
{
    auto level = ExtraGetMaturityLevelToPlayer(pPlayerData, index);
    if (index == 0) return 0;

    if (level > 0)
        return (&gauge->m_MDNone1)[(index * 3) + (level - 1)];
    else
        return (&gauge->m_Green)[index - 1];

}

void ExtraAddMaturityLevelToPlayer(Sonicteam::GameImp::PlayerData* pPlayerData, uint32_t index)
{
    uint8_t& byte = pPlayerData->Extra[index / 4];
    uint8_t shift = (index % 4) * 2;          
    uint8_t mask = 0x03 << shift;                
    uint8_t level = (byte & mask) >> shift;      

    if (level < 0x03) 
    {
        byte = (byte & ~mask) | ((level + 1) << shift); 
    }
}

float ExtraGetMaturityMeterToPlayer(Sonicteam::GameImp::PlayerData* pPlayerData, uint32_t index)
{
    return (float)(pPlayerData->Extra[4 + index]) / 100.0;
}
void ExtraSetMaturityMeterToPlayer(Sonicteam::GameImp::PlayerData* pPlayerData, uint32_t index,float value)
{
    uint8_t& byte = pPlayerData->Extra[4 + index];
    byte = value * 100.0;
}



void ExtraAddMaturityToPlayer(Sonicteam::Player::Object* pPlayer, float value)
{
    auto pPlayerData = GetPlayerData(pPlayer);
    if ((uint32_t)pPlayer->m_spGauge.get() <= (uint32_t)g_memory.base)
        return;

    auto IGauge = pPlayer->GetGauge<Sonicteam::Player::IPlugIn>();
    if (IGauge->m_pVftable.ptr.get() == 0x8200D4D8)
    {
        auto GaugeEX = pPlayer->GetGauge<SonicGaugeEX>();
        auto pSonicC = pPlayer->GetMachine<Sonicteam::Player::State::Machine2>()->GetContext<Sonicteam::Player::State::SonicContext>();
        auto pIndex = pSonicC->m_CurrentGemSprite.get();
        auto& pValue = GaugeEX->GetMLevel(pIndex);
        auto& pValueMax = GaugeEX->GetMMax(pIndex);
        pValue = pValue + ((1.0 / pValueMax) * value);
        if (pValue >= 1.0)
        {   
            pValue = 0.0;
            ExtraAddMaturityLevelToPlayer(pPlayerData, pIndex);
        }
        ExtraSetMaturityMeterToPlayer(pPlayerData, pIndex, pValue.get());
    }
    else
    {
        pPlayerData->MaturityValue = pPlayerData->MaturityValue + value;

        if (pPlayerData->MaturityValue >= 1.0)
        {
            pPlayerData->MaturityValue = 0.0;
            pPlayerData->MaturityLevel = pPlayerData->MaturityValue + 1;

        }
    }
}


//Check Gauge Drain
//SonicTeam::Player::SonicGauge (IVariable), IVariable::Init(REF_TYPE(SonicTeam::LuaSystem))
PPC_FUNC_IMPL(__imp__sub_82217FC0);
PPC_FUNC(sub_82217FC0) {

    if (!Config::SonicGauge)
    {
        __imp__sub_82217FC0(ctx, base);
        return;
    }

    auto context = (Sonicteam::Player::State::SonicContext*)g_memory.Translate(ctx.r3.u32);
    auto gauge = context->m_Gauge.get();
    using enum Sonicteam::Player::State::SonicContext::Gems;
    auto gem_id = (Sonicteam::Player::State::SonicContext::Gems)(ctx.r4.u32);

    size_t index = gemConversionTable[gem_id - 1] - 1;
    auto drain = (&gauge->m_Green)[index].get();

    auto pPlayerData = GetPlayerData(context->m_pScore->m_pPlayer.get());
    drain = ExtraGetGemDrainValueMaturity((SonicGaugeEX*)gauge, pPlayerData, index + 1);
    

    switch (gem_id) 
    {
        case Yellow:
            if (context->m_ThunderGuard) break;
        case Blue:
        case Green:
        case Sky:
        case White:
        case Super: 
        {
        
            if (gauge->m_Value >= drain)
            {
                ctx.r3.u64 = 1;
                return;
            }
            break;
        }
        case Red:
        case Purple:
            if (context->m_24A == 0) 
            {
                ctx.r3.u64 = 1;
                return;
            }
            break;
    }
    ctx.r3.u64 = 0;
    return;

}
//Gauge Drain
PPC_FUNC_IMPL(__imp__sub_82218068);
PPC_FUNC(sub_82218068) {

    if (!Config::SonicGauge)
    {
        __imp__sub_82217FC0(ctx, base);
        return;
    }

    auto context = (Sonicteam::Player::State::SonicContext*)g_memory.Translate(ctx.r3.u32);
    auto gauge = context->m_Gauge.get();

    using enum Sonicteam::Player::State::SonicContext::Gems;
    auto gem_id = (Sonicteam::Player::State::SonicContext::Gems)(ctx.r4.u32);
    double delta = ctx.f1.f64;
    uint32_t index = gemConversionTable[gem_id - 1] - 1;
    auto drain = (&gauge->m_Green)[index].get();

    auto pPlayerData = GetPlayerData(context->m_pScore->m_pPlayer.get());
    drain = ExtraGetGemDrainValueMaturity((SonicGaugeEX*)gauge,pPlayerData, index + 1);


    switch (gem_id) 
    {
    case Blue:
        case Green:
        case Yellow:
        case Sky:
        case White:
        case Super:
        {
 
            gauge->m_Value = gauge->m_Value.get() - drain;
            gauge->m_GroundedTime = 0.0;
            break;
        }
        case Red:
        case Purple:
        {
            gauge->m_Value = gauge->m_Value.get() - drain * delta;
            gauge->m_GroundedTime = 0.0;
            if (gauge->m_Value <= 0)
            {
                gauge->m_Value = 0.0;
                context->m_Shrink = 0;
                context->m_SlowTime = 0;
                context->m_24A = 1;

            }
            break;
        }
    }
}


PPC_FUNC_IMPL(__imp__sub_8223F360);
PPC_FUNC(sub_8223F360)
{

    auto IVariable = ctx.r3.u32;
    auto RefTypeLuaSystem = ctx.r4.u32;
    __imp__sub_8223F360(ctx, base);
    if (!Config::SonicGauge)
        return;

    auto gauge = (Sonicteam::Player::SonicGauge*)g_memory.Translate(IVariable - 0x20);
    auto buffer = g_userHeap.Alloc<stdx::string>();

    // if (gauge->m_Gem == 0.0) if m_Gem not intitialized by __imp__sub_8223F360
    *buffer = "c_gauge_green";
    if (gauge->m_Green.get() == 0.0)
        gauge->m_Green = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));

    *buffer = "c_gauge_red";
    if (gauge->m_Red.get()== 0.0)
        gauge->m_Red = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));

    *buffer = "c_gauge_blue";
    if (gauge->m_Blue.get() == 0.0)
        gauge->m_Blue = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));

    *buffer = "c_gauge_white";
    if (gauge->m_White.get() == 0.0)
        gauge->m_White = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));

    *buffer = "c_gauge_sky";
    if (gauge->m_Sky.get() == 0.0)
        gauge->m_Sky = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));

    *buffer = "c_gauge_yellow";
    if (gauge->m_Yellow.get() == 0.0)
        gauge->m_Yellow = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));

    *buffer = "c_gauge_purple";
    if (gauge->m_Purple.get() == 0.0)
        gauge->m_Purple = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));

    *buffer = "c_gauge_super";
    if (gauge->m_Super.get() == 0.0)
        gauge->m_Super = GuestToHostFunction<float>(sub_821EA350, RefTypeLuaSystem, g_memory.MapVirtual(buffer));


    buffer->~string();
    g_userHeap.Free(buffer);

    /* For Testing
    gauge->m_Green = 10;
    gauge->m_Blue = 20;
    gauge->m_White = 40;
    gauge->m_Sky = 60;
    gauge->m_Yellow = 80;
    gauge->m_Super = 100;
    gauge->m_Red = 20;
    gauge->m_Purple = 40;
    */
}
 




void SonicGaugeRestorationGaugeGemSpriteResetFix(PPCRegister& r_GameImp) {

    if (!Config::SonicGauge)
    {
        return;
    }
    Sonicteam::GameImp* pGameImp = (Sonicteam::GameImp*)g_memory.Translate(r_GameImp.u32);
    for (int i = 0; i < 4; i++)
        pGameImp->m_PlayerData[i].GemIndex = 0;
}




void SonicGaugeRestorationGaugeFlagFix(PPCRegister& r_gauge, PPCRegister& r_context) {

    if (!Config::SonicGauge || !r_gauge.u32)
        return;




    auto pGauge = (SonicGaugeEX*)g_memory.Translate(r_gauge.u32);
    auto PContext = (Sonicteam::Player::State::SonicContext*)g_memory.Translate(r_context.u32);
    auto pPlayer = PContext->m_pScore->m_pPlayer;
    if ((uint32_t)(static_cast<Sonicteam::Player::IPlugIn*>(pGauge)->m_pVftable.get()) != 0x8200D4D8) // != SonicGauge 
        return;





    auto pPlayerData = GetPlayerData(PContext->m_pScore->m_pPlayer);
    if (!pPlayerData) return;

    if (!pGauge->Initialized)
    {
        pGauge->Initialized = true;
        for (int i = 0; i < 9; i++)
            (&pGauge->m_MNone)[i] = ExtraGetMaturityMeterToPlayer(pPlayerData, i);
    }

    auto pIndex = PContext->m_CurrentGemSprite.get();
    pPlayerData->MaturityLevel = ExtraGetMaturityLevelToPlayer(pPlayerData, pIndex);

    if (pPlayerData->MaturityLevel == 3)
        pPlayerData->MaturityValue = 1;
    else
        pPlayerData->MaturityValue = pGauge->GetMLevel(pIndex);


    auto weapons = PContext->m_pScore->m_pPlayer->GetPlugin<Sonicteam::Player::Weapon::SonicWeapons>("sonic_weapons");
    if (PContext->m_Tornado != 0 || PContext->m_CurrentAnimation == 0xCB || PContext->m_CurrentAnimation == 0xCC || PContext->m_CurrentAnimation == 0x46 || PContext->m_CurrentAnimation == 0xCE ||  weapons->m_GunDrive.Entity != 0)
    {
        pGauge->m_GroundedFlags = 1; // Lock game
    }
    else
    {
        using enum Sonicteam::Player::State::SonicContext::Gems;
        if ((PContext->m_Input.get() & 0x10000) != 0) {
            PContext->m_24A = 0;
        }
            
        if ((PContext->m_Input.get() & 0x20000) != 0 && (PContext->m_CurrentGem == Red || PContext->m_CurrentGem == Purple))
        {
            pGauge->m_GroundedFlags = 1; 
            if (PContext->m_24A) 
            {
                pGauge->m_GroundedFlags = 0;
                PContext->m_Shrink = 0;
                PContext->m_SlowTime = 0;
            }
        }
        else if ((PContext->m_PostureFlags.get() & Sonicteam::Player::State::CommonContext::CC_GROUND) != 0 || PContext->m_24A)
        {
            pGauge->m_GroundedFlags = 0;

        }
    }

}





void SonicGaugeMaturityExMoreMem(PPCRegister& r3)
{
    if (!Config::SonicGauge)
    {
        return;
    }
    r3.u32 = sizeof(SonicGaugeEX);
}

void SonicGaugeMaturityExMoreMemZERO(PPCRegister& r3, PPCRegister& p_player)
{
    if (!Config::SonicGauge)
    {
        return;
    }
    auto pPlayer = (Sonicteam::Player::Object*)g_memory.Translate(p_player.u32);
    auto pGauge = (SonicGaugeEX*)(g_memory.Translate(r3.u32));
    ZeroMemory(pGauge, sizeof(SonicGaugeEX));
    pGauge->m_MAXMNone = 10.0;
    pGauge->m_MAXMGreen = 10.0;
    pGauge->m_MAXMBlue = 10.0;
    pGauge->m_MAXMWhite = 10.0;
    pGauge->m_MAXMSky = 10.0;
    pGauge->m_MAXMYellow = 10.0;
    pGauge->m_MAXMSuper = 10.0;
    pGauge->m_MAXMRed = 10.0;
    pGauge->m_MAXMPurple = 10.0;
    pGauge->Initialized = false;


    pGauge->m_MDNone1 = 8.0;
    pGauge->m_MDNone2 = 5.0;
    pGauge->m_MDNone3 = 1.0;

    pGauge->m_MDGreen1 = 8.0;
    pGauge->m_MDGreen2 = 5.0;
    pGauge->m_MDGreen3 = 1.0;

    pGauge->m_MDBlue1 = 8.0;
    pGauge->m_MDBlue2 = 5.0;
    pGauge->m_MDBlue3 = 1.0;

    pGauge->m_MDWhite1 = 8.0;
    pGauge->m_MDWhite2 = 5.0;
    pGauge->m_MDWhite3 = 1.0;


    pGauge->m_MDSky1 = 8.0;
    pGauge->m_MDSky2 = 5.0;
    pGauge->m_MDSky3 = 1.0;


    pGauge->m_MDYellow1 = 8.0;
    pGauge->m_MDYellow2 = 5.0;
    pGauge->m_MDYellow3 = 1.0;

    pGauge->m_MDSuper1 = 8.0;
    pGauge->m_MDSuper2 = 5.0;
    pGauge->m_MDSuper3 = 1.0;

    pGauge->m_MDRed1 = 8.0;
    pGauge->m_MDRed2 = 5.0;
    pGauge->m_MDRed3 = 1.0;

    pGauge->m_MDPurple1 = 8.0;
    pGauge->m_MDPurple2 = 5.0;
    pGauge->m_MDPurple3 = 1.0;

}


//Sonic Gauge Restoration (EXTREME)
PPC_FUNC_IMPL(__imp__sub_82198C08);
PPC_FUNC(sub_82198C08)
{

    if (!Config::SonicGauge)
    {
        __imp__sub_82198C08(ctx, base);
        return;
    }
    auto pPlayer = (Sonicteam::Player::Object*)(base + ctx.r3.u32);
 //   pPlayer->GetGauge<Sonicteam::Player::SonicGaugeEX>();
    ExtraAddMaturityToPlayer(pPlayer, c_maturity_point); 
    __imp__sub_82198C08(ctx, base);
}



