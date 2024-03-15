#ifndef SYNTRIX_SYMBOL_HEADER
#define SYNTRIX_SYMBOL_HEADER
#include <cstdint>
#include <string>

namespace syntrix
{

class Symbol
{
public:
    enum Kind : uint8_t
    {
        NonPrintable,
        LowerCase,
        UpperCase,
        Space,          // ws
        NewLine,        // ws
        CarriageReturn, // ws
        Tab,            // ws
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

    Symbol::Kind get_symbol_kind();

private:
    Kind symbol_kind;
    uint8_t literal;
};

} // namespace syntrix
#endif
