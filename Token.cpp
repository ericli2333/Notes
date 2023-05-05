#include <bits/stdc++.h>

using namespace std;

class Lexer {
    enum class TypeForWord {
        Words, Integer, Operator, Blank, Eof
    };

    enum class TypeForToken {
        Identifier, Integer, Operator,
    };

    struct Token {
        TypeForToken type;
        string value;

        Token() : type(TypeForToken::Identifier) {};
    };

private:
    vector<Token> tokens;

    static TypeForWord whichType(char tmp) {
        if (tmp == ' ' || tmp == '\n' || tmp == '\t' || tmp == '\r') {
            return TypeForWord::Blank;
        } else if (tmp >= '0' && tmp <= '9') {
            return TypeForWord::Integer;
        } else if (tmp == '*' || tmp == '/' || tmp == '+' || tmp == '=' ||tmp == '-') {
            return TypeForWord::Operator;
        } else if ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')) {
            return TypeForWord::Words;
        } else if (tmp == EOF || tmp == 26) {
            return TypeForWord::Eof;
        } else throw std::exception();
    }

public:
    void input();
    void output();
};

void Lexer::input() {
    char tmp;
    TypeForWord typeForWord;
    Token thisToken;
    enum class
            Status {
        empty, firstOfIdentifier, firstOfInteger
    };
    Status status = Status::empty;
    do{
        tmp = (char) getchar();
        try {
            typeForWord = whichType(tmp);

        }
        catch (std::exception &) {
            cerr << "Unexpected Input";
            exit(-1);
        }
        switch (typeForWord) {
            case TypeForWord::Words:
                if (status == Status::empty) {
                    status = Status::firstOfIdentifier;
                    thisToken.value += tmp;
                    thisToken.type = TypeForToken::Identifier;
                } else if (status == Status::firstOfIdentifier) {
                    thisToken.value += tmp;
                    break;
                } else {
                    cerr << "Invalid Integer";
                    exit(-1);
                }
                break;
            case TypeForWord::Integer:
                if (status == Status::empty) {
                    status = Status::firstOfInteger;
                    thisToken.value += tmp;
                    thisToken.type = TypeForToken::Integer;
                } else {
                    thisToken.value += tmp;
                }
                break;
            case TypeForWord::Operator:
                thisToken.value += tmp;
                thisToken.type = TypeForToken::Operator;
                tokens.push_back(thisToken);
                thisToken = Token();
                status = Status::empty;
                break;
            case TypeForWord::Blank:
                if (status == Status::empty) {
                    break;
                }
                else {
                    tokens.push_back(thisToken);
                    thisToken = Token();
                    status = Status::empty;
                }
                break;
            case TypeForWord::Eof:
                if (status != Status::empty) {
                    tokens.push_back(thisToken);
                    return;
                }
                break;
            default:
                break;
        }
    }while (tmp != EOF) ;
}

void Lexer::output() {
    for (auto t: this->tokens) {
        switch (t.type) {
            case TypeForToken::Operator:
                cout << t.value << endl;
                break;
            case TypeForToken::Identifier :
                cout << "identifier" << ' ' << t.value << endl;
                break;
            default:
                cout << "integer" << ' ' << t.value << endl;
                break;
        }
    }
    cout << "endofinput";
}

Lexer lexer;

int main() {
    lexer.input();
    lexer.output();
    return 0;
}
