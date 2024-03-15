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
            symbol_kind = Symbol::Kind::NonPrintable;
            break;
        case 9:
            symbol_kind = Symbol::Kind::Tab;
            return;
        case 10:
            symbol_kind = Symbol::Kind::NewLine;
            return;
        case 13:
            symbol_kind = Symbol::Kind::CarriageReturn;
            return;
        case 32:
            symbol_kind = Symbol::Kind::Space;
            break;
        case 33:
            symbol_kind = Symbol::Kind::Exclamation;
            break;
        case 34:
            symbol_kind = Symbol::Kind::DoubleQuote;
            break;
        case 35:
            symbol_kind = Symbol::Kind::HashTag;
            break;
        case 36:
            symbol_kind = Symbol::Kind::Dollar;
            break;
        case 37:
            symbol_kind = Symbol::Kind::Precent;
            break;
        case 38:
            symbol_kind = Symbol::Kind::Ampersand;
            break;
        case 39:
            symbol_kind = Symbol::Kind::SingleQuote;
            break;
        case 40:
            symbol_kind = Symbol::Kind::LParen;
            break;
        case 41:
            symbol_kind = Symbol::Kind::RParen;
            break;
        case 42:
            symbol_kind = Symbol::Kind::Asterisk;
            break;
        case 43:
            symbol_kind = Symbol::Kind::Plus;
            break;
        case 44:
            symbol_kind = Symbol::Kind::Comma;
            break;
        case 45:
            symbol_kind = Symbol::Kind::Dash;
            break;
        case 46:
            symbol_kind = Symbol::Kind::Dot;
            break;
        case 47:
            symbol_kind = Symbol::Kind::FSlash;
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
            symbol_kind = Symbol::Kind::Digit;
            break;
        case 58:
            symbol_kind = Symbol::Kind::Colon;
            break;
        case 59:
            symbol_kind = Symbol::Kind::SemiColon;
            break;
        case 60:
            symbol_kind = Symbol::Kind::LT;
            break;
        case 61:
            symbol_kind = Symbol::Kind::EQ;
            break;
        case 62:
            symbol_kind = Symbol::Kind::GT;
            break;
        case 63:
            symbol_kind = Symbol::Kind::Question;
            break;
        case 64:
            symbol_kind = Symbol::Kind::At;
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
            symbol_kind = Symbol::Kind::UpperCase;
            break;
        case 91:
            symbol_kind = Symbol::Kind::LBracket;
            break;
        case 92:
            symbol_kind = Symbol::Kind::BSlash;
            break;
        case 93:
            symbol_kind = Symbol::Kind::RBracket;
            break;
        case 94:
            symbol_kind = Symbol::Kind::Circumflex;
            break;
        case 95:
            symbol_kind = Symbol::Kind::UnderScore;
            break;
        case 96:
            symbol_kind = Symbol::Kind::BackTick;
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
            symbol_kind = Symbol::Kind::LowerCase;
            break;
        case 123:
            symbol_kind = Symbol::Kind::LBrace;
            break;
        case 124:
            symbol_kind = Symbol::Kind::Pipe;
            break;
        case 125:
            symbol_kind = Symbol::Kind::RBrace;
            break;
        case 126:
            symbol_kind = Symbol::Kind::Tilde;
            break;
        case 127:
            symbol_kind = Symbol::Kind::Delete;
            break;
        default:
            symbol_kind = Symbol::Kind::NonPrintable;
            break;
    }
}

syntrix::Symbol::Kind syntrix::Symbol::get_symbol_kind() {
    return symbol_kind;
}

static std::string escaped_byte(uint8_t c) {
    return std::format("\\{}", static_cast<unsigned int>(c));
}

std::string syntrix::Symbol::to_string()
{
    std::string result;
    switch (symbol_kind) {
        case NonPrintable:
            result += escaped_byte(literal);
            break;
        case LowerCase:
        case UpperCase:
        case Digit:
        case UnderScore:
            result += static_cast<char>(literal);
            break;
        case Space:
            result += "Space";
            break;
        case CarriageReturn:
            result += "CarriageReturn";
            break;
        case NewLine:
            result += "NewLine\n";
            break;
        case Tab:
            result += "Tab";
            break;
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

    return result;
}
