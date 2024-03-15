#include "symbol.h"

#include <format>

syntrix::Symbol::Symbol(uint8_t byte) : literal{byte}
{
    switch (byte) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 11:
        case 12:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
            value = Value::NonPrintable;
            break;
        case 9:
        case 10:
        case 13:
        case 32:
            value = Value::WhiteSpace;
            break;
        case 33:
            value = Value::Exclamation;
            break;
        case 34:
            value = Value::DoubleQuote;
            break;
        case 35:
            value = Value::HashTag;
            break;
        case 36:
            value = Value::Dollar;
            break;
        case 37:
            value = Value::Precent;
            break;
        case 38:
            value = Value::Ampersand;
            break;
        case 39:
            value = Value::SingleQuote;
            break;
        case 40:
            value = Value::LParen;
            break;
        case 41:
            value = Value::RParen;
            break;
        case 42:
            value = Value::Asterisk;
            break;
        case 43:
            value = Value::Plus;
            break;
        case 44:
            value = Value::Comma;
            break;
        case 45:
            value = Value::Dash;
            break;
        case 46:
            value = Value::Dot;
            break;
        case 47:
            value = Value::FSlash;
            break;
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
            value = Value::Digit;
            break;
        case 58:
            value = Value::Colon;
            break;
        case 59:
            value = Value::SemiColon;
            break;
        case 60:
            value = Value::LT;
            break;
        case 61:
            value = Value::EQ;
            break;
        case 62:
            value = Value::GT;
            break;
        case 63:
            value = Value::Question;
            break;
        case 64:
            value = Value::At;
            break;
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
            value = Value::UpperCase;
            break;
        case 91:
            value = Value::LBracket;
            break;
        case 92:
            value = Value::BSlash;
            break;
        case 93:
            value = Value::RBracket;
            break;
        case 94:
            value = Value::Circumflex;
            break;
        case 95:
            value = Value::UnderScore;
            break;
        case 96:
            value = Value::BackTick;
            break;
        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
        case 110:
        case 111:
        case 112:
        case 113:
        case 114:
        case 115:
        case 116:
        case 117:
        case 118:
        case 119:
        case 120:
        case 121:
        case 122:
            value = Value::LowerCase;
            break;
        case 123:
            value = Value::LBrace;
            break;
        case 124:
            value = Value::Pipe;
            break;
        case 125:
            value = Value::RBrace;
            break;
        case 126:
            value = Value::Tilde;
            break;
        case 127:
            value = Value::Delete;
            break;
        default:
            value = Value::NonPrintable;
            break;
    }
}

std::string whitespace_styling = "\x1b[48;5;15m\x1b[38;5;16m";
std::string wrapper_styling = "\x1b[38;5;33m";
std::string raw_styling = "\x1b[38;5;196m";
std::string semicolon_styling = "\x1b[38;5;177m";
std::string misc_symbol_styling = "\x1b[38;5;51m";
std::string clear = "\x1b[0m";

std::string syntrix::Symbol::to_string()
{
    std::string result{};
    bool need_style_clear = false;
    // prestyling
    switch (value) {
        case WhiteSpace:
            result += whitespace_styling;
            need_style_clear = true;
            break;
        case RParen:
        case LParen:
        case RBrace:
        case LBrace:
        case RBracket:
        case LBracket:
            result += wrapper_styling;
            need_style_clear = true;
            break;
        case NonPrintable:
            result += raw_styling;
            need_style_clear = true;
            break;
        case SemiColon:
            result += semicolon_styling;
            need_style_clear = true;
            break;
        case LowerCase:
        case UpperCase:
        case Digit:
            break;
        case Exclamation:
        case DoubleQuote:
        case HashTag:
        case Dollar:
        case Precent:
        case Ampersand:
        case SingleQuote:
        case Asterisk:
        case Plus:
        case Comma:
        case Dash:
        case Dot:
        case FSlash:
        case Colon:
        case LT:
        case EQ:
        case GT:
        case Question:
        case At:
        case BSlash:
        case Circumflex:
        case UnderScore:
        case BackTick:
        case Pipe:
        case Tilde:
        case Delete:
            result += misc_symbol_styling;
            need_style_clear = true;
            break;
    }

    switch (value) {
        case NonPrintable:
            result += std::format("\\{}", static_cast<unsigned int>(value));
            break;
        case LowerCase:
        case UpperCase:
        case Digit:
        case UnderScore:
            result += static_cast<char>(literal);
            break;
        case WhiteSpace:
        {
            if (literal == 9) {
                result += "t";
            } else if (literal == 32) {
                result += " ";
            } else if (literal == 10) {
                result += "n" + clear + "\n";
                need_style_clear = false;
            } else {
                result += "r";
            }
            break;
        }
        case Exclamation:
            result += "Bang";
            break;
        case DoubleQuote:
            result += "DoubleQuote";
            break;
        case HashTag:
            result += "HashTag";
            break;
        case Dollar:
            result += "DollarSign";
            break;
        case Precent:
            result += "Precent";
            break;
        case Ampersand:
            result += "Ampersand";
            break;
        case SingleQuote:
            result += "SingleQuote";
            break;
        case RParen:
            result += "RP";
            break;
        case LParen:
            result += "LP";
            break;
        case Asterisk:
            result += "Asterisk";
            break;
        case Plus:
            result += "Plus";
            break;
        case Comma:
            result += "Comma";
            break;
        case Dash:
            result += "Dash";
            break;
        case Dot:
            result += "Dot";
            break;
        case FSlash:
            result += "FSlash";
            break;
        case Colon:
            result += "Colon";
            break;
        case SemiColon:
            result += "SemiColon";
            break;
        case LT:
            result += "LT";
            break;
        case EQ:
            result += "EQ";
            break;
        case GT:
            result += "GT";
            break;
        case Question:
            result += "QuestionMark";
            break;
        case At:
            result += "At";
            break;
        case LBracket:
            result += "LBracket";
            break;
        case BSlash:
            result += "BSlash";
            break;
        case RBracket:
            result += "RBracket";
            break;
        case Circumflex:
            result += "Circumflex";
            break;
        case BackTick:
            result += "BackTick";
            break;
        case LBrace:
            result += "LBrace";
            break;
        case Pipe:
            result += "Pipe";
            break;
        case RBrace:
            result += "RBrace";
            break;
        case Tilde:
            result += "Tilde";
            break;
        case Delete:
            result += "Delete";
            break;
    }

    // post-styling
    if (need_style_clear) {
        result += clear;
    }
    return result;
}
