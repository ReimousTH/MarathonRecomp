#pragma once

#include <Marathon.h>
#include <Sonicteam/Player/State/Machine2.h>
#include <stdx/vector.h>
#include <Sonicteam/Player/IPlugIn.h>

namespace Sonicteam::Player
{
    //xbox vector
    struct  _vector
    {
        union
        {
            struct
            {
                be<float> x, y, z, w;
            };

            be<float> _f[4];
        };
        _vector(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f): x(x), y(y), z(z), w(w)
        {
        }
    };

    typedef _vector XMVECTOR;

    #pragma pack(push, 1)
    class __declspec(align(1)) Object : public Actor
    {
        struct ObjectPlayerUpgrade {
            unsigned int global_flag;
            unsigned int equip_flag;
        };
        //Start template for all message
        class TObjectMessage:SoX::TMessage
        {
            be<uint32_t> m_MessageID;
            enum Message :uint32_t
            {
                MESSAGE_CHAOSDRIVE_TYPE_A_GET   = 0x11033,
                MESSAGE_POWERCORE_TYPE_A_GET   = 0x11034,
                MESSAGE_CHAOSDRIVE_TYPE_B_GET = 0x11035,
                MESSAGE_POWERCORE_TYPE_B_GET = 0x11036,
            };
        };
        //More Message ...

    public:
        stdx::string m_PlayerLUA;
        stdx::string m_PlayerPKG;
        be<uint32_t> m_CameramanActorID;
        xpointer<uint32_t> m_Cameraman;
        be<uint32_t> m_PlayerIndex;
        be<uint32_t> m_PlayerControllerIndex;
        XMVECTOR m_SpawnRotation;
        XMVECTOR m_SpawnPosition;
        be<uint32_t> m_SpawnRing;
        xpointer<uint32_t> m_SpawnSource; // REF_TYPE(RefCountObject)
        uint8_t m_IsPlayer;
        uint8_t m_IsPosture;
        uint8_t m_IsAI;
        MARATHON_INSERT_PADDING(1);
        xpointer<uint32_t> m_RootFrame; // REF_TYPE(RefCountObject) 
        xpointer<uint32_t> m_PackageBinary; // REF_TYPE(RefCountObject)
        boost::shared_ptr<uint32_t> m_PlayerModel;
        boost::shared_ptr<uint32_t> m_PlayerPosture;
        boost::shared_ptr<State::IMachine> m_spStateMachine;
        boost::shared_ptr<uint32_t> m_PlayerGravity;
        boost::shared_ptr<uint32_t> m_PlayerImpulse;
        be<uint32_t> m_LastSetupModule;
        be<uint32_t> m_NextSetupModule;
        boost::shared_ptr<IGauge> m_spGauge;
        MARATHON_INSERT_PADDING(0x8);
        stdx::vector<boost::shared_ptr<Sonicteam::Player::IPlugIn>> m_PlayerPlugins;
        MARATHON_INSERT_PADDING(0x58);
        be<float> m_PlayerDelta;
        MARATHON_INSERT_PADDING(0x48);
        stdx::vector<ObjectPlayerUpgrade> m_PlayerUpgrade;
        stdx::string m_PlayerName;
        MARATHON_INSERT_PADDING(0x134);

        template <typename T>
        inline T* GetGauge();

		template <typename T = Player::IPlugIn>
		inline T* GetPlugin(const char* v_name);

        template <typename T = State::IMachine>
        inline T* GetMachine();


    };
    #pragma pack(pop) 
 
}

#include <Sonicteam/Player/Object.inl>
