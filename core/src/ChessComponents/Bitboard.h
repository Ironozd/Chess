#pragma once
#include <cstdint>

namespace Chess
{
    /**
     * @brief  CRTP design using interface class for Bitboard to
     * support compile-time initializations of bitboards. Mainly
     * designed for future possibility of enhanced integrations.
     * (Pre-calculations of chess attacks on bitboard etc.).
     * 
     * @tparam Derived -- Bitboard class
     */
    template <typename Derived>
    class BitboardInterface
    {
    public:
        constexpr void Set(const size_t &index)
        {
            Self()->SetImpl(index);
        }
        constexpr void Reset(const size_t &index)
        {
            Self()->ResetImpl(index);
        }
        constexpr void Clear()
        {
            Self()->ClearImpl();
        }

    private:
        constexpr Derived *Self() { return static_cast<Derived *>(this); }
    };

    /**
     * @brief 64 bit board (uint64_t) wrapper class.
     */
    class Bitboard : public BitboardInterface<Bitboard>
    {
    public:
        constexpr Bitboard() : m_Board(0) {}

        /**
         * @brief Constructor for Bitboard.
         *
         * @param uint64_t m_Board : a bitboard.
         */
        constexpr Bitboard(uint64_t board) : m_Board(board) {}

        /**
         * @brief Sets the given position inside the bitboard to 1.
         *
         * @param const size_t& index
         */
        constexpr void SetImpl(const uint64_t &index)
        {
            m_Board |= (uint64_t)1 << index;
        }

        /**
         * @brief Sets the given position inside the bitboard to 0.
         *
         * @param const size_t& index
         *
         * @warning Operation used is XOR 1. Use with caution.
         *
         * @todo Wrap the reset function around a performance critical bit-test to see whether the provided index value is 1.
         */
        constexpr void ResetImpl(const uint64_t &index)
        {
            m_Board ^= (uint64_t)1 << index;
        }

        /**
         * @brief Clears the bitboard.
         *
         * @note Sets the uint64_t value to 0.
         */
        constexpr void ClearImpl()
        {
            m_Board = 0;
        }

        /**
         * @brief Get memory block of the board.
         *
         * @return constexpr uint64_t&
         */
        constexpr uint64_t &Board()
        {
            return m_Board;
        }

    private:
        uint64_t m_Board;
    };
}