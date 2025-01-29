#include "Bitboard.h"


namespace Chess
{
    Bitboard::Bitboard() : m_Board(0)
    {

    }

    Bitboard::Bitboard(uint64_t board) : m_Board(board)
    {

    }

    Bitboard::~Bitboard()
    {

    }

    void Bitboard::Set(const size_t& index)
    {
        m_Board |= (uint64_t)1 << index;
    }
    
    void Bitboard::Reset(const size_t& index)
    {
        m_Board ^= (uint64_t)1 << index;
    }
    
    void Bitboard::Clear()
    {
        m_Board = 0;
    }
}