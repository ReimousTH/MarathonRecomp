#pragma once

#include <Marathon.inl>
#include <api/stdx/string.h>
#include <Sonicteam/ActorManager.h>

namespace Sonicteam
{
    struct RenderBox
    {
        be<float> w, h, d;
        RenderBox operator*=(float value)
        {
            return
            {
                w = w * value,
                h = h * value,
                d = d * value,
            };
        };
    };


    struct GenerateArea
    {
        MARATHON_INSERT_PADDING(0x40);
        RenderBox Box;

    };
    struct ActiveArea
    {
        MARATHON_INSERT_PADDING(0x18);
        struct AXISBOX {
            MARATHON_INSERT_PADDING(0x10);
            RenderBox Box;
        };
        xpointer<AXISBOX> Area; //0x18
   
    };

    class GameImp : public SoX::MessageReceiver
    {
    public:
        struct PlayerSpawnData
        {
            stdx::string character_start_lua;      
            MARATHON_INSERT_PADDING(4);            
            MARATHON_INSERT_PADDING(0x10);         
            MARATHON_INSERT_PADDING(0x10);         
            MARATHON_INSERT_PADDING(4);            
            stdx::string character_restart_lua;    
            MARATHON_INSERT_PADDING(0x10);         
            MARATHON_INSERT_PADDING(0x10);         
            MARATHON_INSERT_PADDING(0x40);         
            uint8_t isPlayer;                      
            MARATHON_INSERT_PADDING(3);            
            MARATHON_INSERT_PADDING(0xC);                    
            MARATHON_INSERT_PADDING(0x10);         
            MARATHON_INSERT_PADDING(0x10);         
        };
        struct PlayerData
        {
            be<uint32_t> ActorID;
            be<uint32_t> RingCount;
            be<uint32_t> TownRingCount;
            be<uint32_t> LifeCount;
            be<uint32_t> ScoreCount;
            be<float> AliveTime;
            be<float> Time;
            MARATHON_INSERT_PADDING(4);
            be<float> SectionSaveTime;
            be<float> GaugeValue;
            be<uint32_t> MaturityLevel;
            be<float> MaturityValue;
            MARATHON_INSERT_PADDING(4);
            be<uint32_t> ExtendRingCount;
            be<uint32_t> GemIndex;
            uint8_t Extra[0x10];
        };

        MARATHON_INSERT_PADDING(0x2C);
        PlayerSpawnData m_PlayerSpawnData[0xF];
        PlayerData m_PlayerData[4];
        MARATHON_INSERT_PADDING(0x218);
        be<uint32_t> m_PlayerActorID[0xF];
        boost::shared_ptr<Sonicteam::ActorManager> m_ActorManager;
        MARATHON_INSERT_PADDING(0x7C8);
        xpointer<ActiveArea> m_ActiveArea[4];
        xpointer<GenerateArea> m_GenerateArea[4];

    };
}
