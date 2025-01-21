#include "Bitboard.h"
#include <type_traits>

namespace Chess
{
    Bitboard::Bitboard() : m_Board(0)
    {

    }

    Bitboard::Bitboard(uint64_t board) : m_Board(board)
    {

    }

    //Bitboard::Bitboard(const Bitboard &other)
    //{
    //    this->m_Board = other.m_Board;
    //}

    //Bitboard::Bitboard(Bitboard &&other)
    //{
    //    this->m_Board = std::move(other.m_Board);
    //}

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