#include "Board.h"
#include "../Core/Logger.h"

namespace Chess
{
    /**
     * @brief TEMPORARY FUNCTION to display bits.
     *
     * @tparam T
     * @param bits
     *
     * @warning TEMPORARY FUNCTION, NOT PERFORMANCE CRITICAL.
     * @todo Modify spdlog to support std::bit
     */
    template <typename T>
    void display_bits(T bits)
    {
        int bits_size = static_cast<int>(sizeof(bits) * 8);
        for (int i = bits_size - 1; i >= 0; i--)
        {
            std::cout << ((bits >> i) & 1);
        }
        std::cout << std::endl;
    }

    Board::Board(const std::string_view &startFen)
    {
        Populate(startFen);
        LOG_INFO("::Board:: created with fen: {0}", startFen);
    }

    Board::Board(const Board &other)
    {
        this->m_Components = other.m_Components;
    }

    Board::Board(Board &&other) noexcept
    {
        this->m_Components = other.m_Components;
    }

    Board::~Board()
    {
        LOG_INFO("::Board:: deleted.");
    }

    bool Board::Populate(const FenString &fen)
    {
        std::deque<FenString> parsed = fen.Split(" ");

        PopulateLayout(parsed[0]);

        for (int i = 0; i < 12; i++)
        {
            display_bits(m_Components.m_Layout[i].Board());
        }
        return false; // not fully implemented
    }

    /**
     * @todo Consider providing compiler the most frequent entries for better optimization.
     */
    const size_t Board::RetrieveSet(const char &character) const
    {
        switch (character)
        {
        case 'p':
            return 0;
        case 'r':
            return 1;
        case 'q':
            return 2;
        case 'k':
            return 3;
        case 'n':
            return 4;
        case 'b':
            return 5;
        case 'P':
            return 6;
        case 'R':
            return 7;
        case 'Q':
            return 8;
        case 'K':
            return 9;
        case 'N':
            return 10;
        case 'B':
            return 11;
        default:
            LOG_CRITICAL("::RetrieveSet:: Unkown charachter reached, returning -1.");
            return -1;
        }
    }

    void Board::PopulateLayout(const FenString &fen)
    {
        ClearLayout();
        std::deque<FenString> parsed = fen.Split("/");

        size_t index = 0;
        for (size_t i = parsed.size(); i-- > 0;)
        {
            for (int j = 0; j < parsed[i].Size(); j++)
            {
                char piece = parsed[i].Data()[j];
                if ((piece >= 'a' && piece <= 'z') || (piece >= 'A' && piece <= 'Z')) // Performance-critcal isDigit.
                {
                    const size_t layoutIndex = RetrieveSet(piece);
                    m_Components.m_Layout[layoutIndex].Set(index);
                    index++;
                }
                else
                {
                    index += static_cast<size_t>(piece - '0'); // Performance-critical conversion to size_t
                }
            }
        }
    }

    void Board::ClearLayout()
    {
        for (auto &layout : m_Components.m_Layout)
        {
            layout.Clear();
        }
    }
}