#pragma once
#include "Pack.h"

namespace ProtobufStruct
{
    enum class ProtobufStructType
    {
        VARINT = 0,
        FIX64 = 1,
        LENGTH = 2,
        // 3,4 was deprecated
        FIX32 = 5
    };
};

class Protobuf
{
private:
    enum class Type
    {
        VARINT,
        BIN,
        BIN_EX,
        LPBYTE_EX,
        TREE,
        FIX32,
        FIX64
    };
    struct VarInt
    {
        byte *VarInt;
        int Length = 0;
    };
    struct BinData
    {
        uint32_t Length;
        VarInt LengthEx;
        byte *Bin;
    };
    struct Tree
    {
        VarInt Field;
        Type Type;
        void *Data;

        std::vector<Tree> *Child;
        VarInt *Length;
    };
    struct LinkList
    {
        Tree *BaseTree;
        LinkList *Superior = nullptr;
    };
    LinkList *List;

public:
    Protobuf()
    {
        List = new LinkList;
        List->BaseTree = new Tree;
        List->BaseTree->Child = new std::vector<Tree>;
    };
    ~Protobuf()
    {
        delete List->BaseTree->Child;
        delete List->BaseTree;
        delete List;
    }

private:
    VarInt Int2Varint(uint64_t l);
    void Int2Varint(uint64_t l, VarInt *VarInt);
    inline VarInt GetField(uint32_t Field, ProtobufStruct::ProtobufStructType ProtobufStructType) { return Int2Varint(Field << 3 | static_cast<int>(ProtobufStructType)); }
    inline void GetField(uint32_t Field, ProtobufStruct::ProtobufStructType ProtobufStructType, VarInt &OutField) { Int2Varint(Field << 3 | static_cast<int>(ProtobufStructType), &OutField); }
    inline void SetVarint(::Pack *Pack, VarInt *VarInt) { Pack->SetBin_(VarInt->VarInt, VarInt->Length); }

    uint32_t Calculate(Tree *Tree);
    void Recurse(::Pack *Pack, Tree *Tree);

public:
    void WriteVarint(const uint32_t Field, const uint64_t l);
    void WriteFix32(const uint32_t Field, const int32_t i);
    void WriteFix64(const uint32_t Field, const int64_t l);
    void WriteStr(const uint32_t Field, const char8_t *str);
    void WriteStr_(const uint32_t Field, char8_t *str);
    void WriteBin(const uint32_t Field, const byte *bin, uint32_t Length);
    void WriteBin_(const uint32_t Field, byte *bin, uint32_t Length);
    void WriteBin(const uint32_t Field, const LPBYTE bin);
    void WriteBin_(const uint32_t Field, const LPBYTE bin);
    void StepIn(const uint32_t Field);
    void StepOut();
    LPBYTE Pack();
    uint32_t Pack(byte *&Bin);
};

class UnProtobuf
{
private:
    struct LinkList
    {
        ::UnPack UnPack;
        LinkList *Superior = nullptr;
    };
    LinkList *List;

public:
    UnProtobuf(const LPBYTE bin)
    {
        List = new LinkList{bin};
    };
    UnProtobuf(const byte *bin, const uint32_t Length)
    {
        List = new LinkList{UnPack(bin, Length)};
    };
    ~UnProtobuf()
    {
        delete List;
    }

private:
    long long int GetVarint();
    void SkipField(ProtobufStruct::ProtobufStructType type);
    ProtobufStruct::ProtobufStructType SkipToField(const byte Field);

public:
    byte GetField();
    void StepIn(const byte Field);
    void StepOut();
    bool IsEnd();
    long long int GetVarint(const byte Field);
    char8_t *GetStr(const byte Field);
    uint32_t GetBin(byte *&bin, const byte Field);
    LPBYTE GetBin(const byte Field);
    template <typename T>
    typename std::enable_if<std::is_same<int, T>::value || std::is_same<uint32_t, T>::value || std::is_same<float, T>::value, void>::type
    GetFix32(T &digital, const byte Field)
    {
        switch (SkipToField(Field))
        {
        case ProtobufStruct::ProtobufStructType::FIX32:
            digital = List->UnPack.GetInt();
            break;
        default:
            throw "Not FIX32 type";
            break;
        }
    };
};
