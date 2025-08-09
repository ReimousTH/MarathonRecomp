#pragma once

namespace Sonicteam::SoX
{
 

    class TMessage
    {
    public:

        //For easy Reciever
        template <typename T>
        T GetAt(size_t at)
        {
            return *reinterpret_cast<be<T>*>((size_t)this + at);
        }
        template <typename T>
        void SetAt(size_t at,T value)
        {
           // GetAt(at) = value;
        }

    };

    class MessageReceiver
    {
    public:
        xpointer<void> m_pVftable;
    };
}
