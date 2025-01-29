#pragma once
#include <cstdint>

namespace Chess
{
    /**
     * @brief 64 bit board (uint64_t) wrapper class.
     */
    class Bitboard
    {
    public:
        Bitboard();
        /**
         * @brief Constructor for Bitboard.
         * 
         * @param uint64_t m_Board : a bitboard.
         */
        Bitboard(uint64_t m_Board);
        
        /**
         * @brief Destructor for bitboard.
         */
        ~Bitboard();

        /**
         * @todo Implement Copy & Move constructors.
         * 
         */
        //Bitboard::Bitboard(const Bitboard &other);
        //Bitboard::Bitboard(Bitboard &&other);
        
        /**
         * @brief Sets the given position inside the bitboard to 1.
         *
         * @param const size_t& index
         */
        void Set(const size_t &index);

        /**
         * @brief Sets the given position inside the bitboard to 0.
         *
         * @param const size_t& index
         * 
         * @warning Operation used is XOR 1. Use with caution.
         * 
         * @todo Wrap the reset function around a performance critical bit-test to see whether the provided index value is 1.
         */
        void Reset(const size_t &index);

        /**
         * @brief Clears the bitboard.
         * 
         * @note Sets the uint64_t value to 0.
         */
        void Clear();

        /* Operator overloads */
        uint64_t &Board()
        {
            return m_Board;
        }
    private:
        uint64_t m_Board;
    };
}