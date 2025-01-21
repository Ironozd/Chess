#pragma once
#include <cstdint>

namespace Chess
{
    class Bitboard
    {
    public:
        Bitboard();
        Bitboard(uint64_t m_Board);

        // Bitboard(const Bitboard &other);
        // Bitboard(Bitboard &&other);

        ~Bitboard();

        void Set(const size_t &index);
        void Reset(const size_t &index);

        void Clear();

        uint64_t &Board()
        {
            return m_Board;
        }

    private:
        uint64_t m_Board;
    };
}