#pragma once

#define SSINGLETON(CLASS) SINGLETON(CLASS,Sonicteam::System::CreateStatic)
#define FSSINGLETON(CLASS,P1,P2) FSINGLETON(CLASS,Sonicteam::System::CreateStatic)
#define SSINGLETON_INSTANCE(CLASS) (&(SINGLETON(CLASS,Sonicteam::System::CreateStatic)::getInstance()))
#define SINGLETON(CLASS,CREATOR) Sonicteam::System::Singleton<CLASS,CREATOR<CLASS>>
#define FSINGLETON(CLASS,CREATOR) Sonicteam::System::FixedSingleton<CLASS,CREATOR<CLASS>>

#include <cstddef>
#include <utility>
#include <Marathon.inl>
#include <kernel/memory.h>


namespace Sonicteam::System
{
    template <typename T, typename Creator>
    class Singleton {
    public:

        Singleton() {
        }

        ~Singleton() {
        }
    private:
        static T* m_instance;

    public:


        static T& getInstance() {
            if (m_instance == 0) {
                m_instance = Creator::Create();
            }
            return *m_instance;
        }
        static T& getInstance(void* address) {
            m_instance = (T*)address;
            return *m_instance;
        }
        //singleton address,Create Function
        //saddress:82D3B264,CreatorFunction: 82581F00
        static T& getInstance(void** saddress, void* CreatorFunction) {
            auto base = g_memory.base;
            if (*(uint32_t*)(base + (uint32_t)saddress) == 0) {
                *(be<uint32_t>*)(base + (uint32_t)saddress) = GuestToHostFunction<uint32_t>(CreatorFunction);
            }
            if (!m_instance) m_instance = (T*)(*(xpointer<T>*)(base + (uint32_t)saddress)).get();
            return *m_instance;
        }
        static T& getInstanceQuick()
        {
            return *m_instance;
        }


        static void cleanup() {
            if (m_instance != 0) {
                delete m_instance;
                m_instance = 0;
            }
        }
    };


    // Specialized Singleton with hardcoded address/creator
    template <typename T, typename Creator, uint32_t saddress, uint32_t creatorFunc>
    class FixedSingleton : public Singleton<T, Creator> {
    public:
        static T& getInstance() {
            auto base = g_memory.base;
            if (*(uint32_t*)(base + saddress) == 0) {
                *(be<uint32_t>*)(base + saddress) = GuestToHostFunction<uint32_t>(CreatorFunction);
            }
            if (!m_instance) m_instance = (T*)(*(xpointer<T>*)(base + saddress)).get();
            return *m_instance;
        }
    };


    template <typename T, typename Creator>
    T* Sonicteam::System::Singleton<T, Creator>::m_instance = 0;

};
