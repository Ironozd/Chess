#include <gtest/gtest.h>
#include "../../src/ChessComponents/Bitboard.h"
#include <bitset>

/**
 * @brief Runtime test for Bitboard::SetImpl
 */
TEST(BitboardTests_CompileTests, BasicTests) {
    Chess::Bitboard Board;
    int SuccessCounter = 0;

    {
        SCOPED_TRACE("Chess::Bitboard::SetImpl Basic Start");
        Board.Set(4);
        uint64_t comparison = 0;
        comparison |= ((uint64_t)1 << 4);
        ASSERT_EQ(Board.Board(), comparison);
        std::cout << "Chess::Bitboard::SetImpl Basic Done.\n";
        SuccessCounter++;
    }

    {
        SCOPED_TRACE("Chess::Bitboard::ResetImpl Basic Start");
        Board.Reset(4);
        ASSERT_EQ(Board.Board(), ((uint64_t)0));
        std::cout << "Chess::Bitboard::ResetImpl Basic Done.\n";
        SuccessCounter++;
    }

    EXPECT_EQ(SuccessCounter, 2);
}

/**
 * @todo Create Advanced tests creating and comparing a variation of values, processes, and results.
 */