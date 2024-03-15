#ifndef SYNTRIX_SYMBOL_HEADER
#define SYNTRIX_SYMBOL_HEADER
#include <cstdint>
#include <string>

namespace syntrix
{

class Symbol
{
public:
    enum Value : uint8_t
    {
        NonPrintable,
        LowerCase,
        UpperCase,
        WhiteSpace,
        Digit,
        Exclamation,
        DoubleQuote,
        HashTag,
        Dollar,
        Precent,
        Ampersand,
        SingleQuote,
        RParen,
        LParen,
        Asterisk,
        Plus,
        Comma,
        Dash,
        Dot,
        FSlash,
        Colon,
        SemiColon,
        LT,
        EQ,
        GT,
        Question,
        At,
        LBracket,
        BSlash,
        RBracket,
        Circumflex,
        UnderScore,
        BackTick,
        LBrace,
        Pipe,
        RBrace,
        Tilde,
        Delete
    };

    Symbol() = default;
    Symbol(uint8_t byte);

    std::string to_string();

private:
    Value value;
    uint8_t literal;
};

} // namespace syntrix
#endif
