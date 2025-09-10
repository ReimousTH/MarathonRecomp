#pragma once

#include <Marathon.inl>

#include <Sonicteam/SoX/IResource2.h>
#include <Sonicteam/SoX/LinkNode.h>

namespace Sonicteam::SoX
{
    class ArcHandleMgr;
    struct ArcFileEntry
    {
        xpointer<void*> pOffset;
        be<uint32_t> uCompressedSize;
        bool IsCompressed;
        be<uint32_t> uDecompressedSize;
    };

    struct size_t_24_be {
        unsigned char bytes[3];
        size_t to_size_t() const {
            return (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
        }
        void from_size_t(size_t value) {
            bytes[2] = static_cast<char>((value >> 16) & 0xFF);
            bytes[1] = static_cast<char>((value >> 8) & 0xFF);
            bytes[0] = static_cast<char>(value & 0xFF);
        }
        operator size_t() const { return to_size_t(); }
        size_t_24_be& operator=(size_t value) { from_size_t(value); return *this; }
    };

    struct ArcFileEntryRaw
    {
        enum EntyType :byte 
        {
            File,
            Directory
        };
         
        struct EntryInfo
        {
            EntyType Type;
            size_t_24_be NameOffset;
        };

        EntryInfo EntryInfo;
        xpointer<void> pEntryOffset;
        be<uint32_t> EntryCompressedSize; 
        be<uint32_t> EntryDecompressedSize;
    };

    struct ArcFileHeader
    {
        union Signature
        {
            char csig[4];
            be<uint32_t> usig;
        } Signature;
        xpointer<void> pEntriesOffset;
        be<uint32_t> uEntriesLength;
        xpointer<void> pEntriesDataOffset;
        char Metadata[0x10];
    };

    class ArcFile
    {
        struct Vftable :RefCountObject::Vftable
        {
            be<uint32_t> Destroy;
        };
        xpointer<Vftable> m_pVftable;
        xpointer<void> m_pFile;
        xpointer<ArcFileEntryRaw> m_pFileEntry;
        be<uint32_t> m_FileEntySize;
        xpointer<void> m_pFileStringTable;
        be<uint32_t> m_RootEntry;
    };

    class ArcHandle:IResource2<ArcHandle,ArcHandleMgr>
    {
    public:
        LinkNode<ArcHandle> m_lnHandle;
        ArcFile m_ArcFile;
        xpointer<void> m_pBuffer; //ptr to file (in memory)
        be<uint32_t> m_BufferSize; //guess??
        bool IsFixedArchive;
        bool IsDownloadContent;
        MARATHON_INSERT_PADDING(2);
        stdx::string m_FilePath; //  game:\xenon\archives\cache.arc
        be<uint32_t> m_Handle; //do we have XHandle to simulate HANDLE type?
    };
}
