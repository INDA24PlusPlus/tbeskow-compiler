#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define INF ((ll)(1e9+7))
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define deb(x) cout << #x << " = " << (x) << endl;
#define deb2(x, y) cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl
#define pb push_back
#define F first
#define S second
#define LSOne(S) ((S) & (-S))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vpii> vvpii;
typedef vector<vpl> vvpl;

map<string, ll> variables;

enum Type{
    Start,
    While,
    If,
    Print,
    Assignment,

    Expression,
    Variable,
    Number,
};

enum Operator{
    Addition,
    Subtraction,
    Multiplication,
    Division
};

struct AST{
    Type type;
    Operator op;
    ll value;
    string variable, compare;
    AST *expression1, *expression2;
    vector<AST*> body;
    AST(Type type) : type(type){}

    void construct(string in = ""){
        if(type == Type::While || type == Type::If){
            cin >> in >> compare;
            expression1 = new AST(Type::Expression);
            expression1->construct(in);
            cin >> in; 
            expression2 = new AST(Type::Expression);
            expression2->construct(in);
            if(compare == ">" || compare == ">="){
                compare[0] = '<';
                swap(expression1, expression2);
            }
        }
        if(type == Type::Expression){
            for(int i = ((ll)in.size())-1;i>=0;i--){
                if(in[i] == '+' || in[i] == '-'){
                    op = (in[i] == '+') ? Operator::Addition : Operator::Subtraction;
                    expression1 = new AST(Type::Expression);
                    expression1->construct(in.substr(0, i));
                    expression2 = new AST(Type::Expression);
                    expression2->construct(in.substr(i+1));
                    return;
                }
            }
            for(int i = ((ll)in.size())-1;i>=0;i--){
                if(in[i] == '*' || in[i] == '/'){
                    op = (in[i] == '*') ? Operator::Multiplication : Operator::Division;
                    expression1 = new AST(Type::Expression);
                    expression1->construct(in.substr(0, i));
                    expression2 = new AST(Type::Expression);
                    expression2->construct(in.substr(i+1));
                    return;
                }
            }
            try{
                value = stoi(in);
                type = Type::Number;
            }catch(exception e){
                type = Type::Variable;
                variable = in;
            }
            return;
        }
        if(type == Type::Assignment){
            cin >> in;
            expression1 = new AST(Type::Expression);
            expression1->construct(in);
            return;
        }
        if(type == Type::Print){
            cin >> in;
            expression1 = new AST(Type::Expression);
            expression1->construct(in);
            return;
        }
        while(cin >> in){
            if(in == "{") continue;
            if(in == "}") break;

            if(in == "while"){
                AST *ast = new AST(Type::While);
                ast->construct();
                body.pb(ast);
            }else if(in == "if"){
                AST *ast = new AST(Type::If);
                ast->construct();
                body.pb(ast);
            }else if(in == "int"){
                AST *ast = new AST(Type::Assignment);
                string equals;
                cin >> ast->variable >> equals;
                ast->construct();
                body.pb(ast);
            }else if(in == "print"){
                AST *ast = new AST(Type::Print);
                ast->construct();
                body.pb(ast);
            }
        }
    }

    ll operator()(){
        if(type == Type::Start) return 1;
        if(type == Type::Number) return value;
        if(type == Type::Variable) return variables[variable];
        ll a = expression1->operator()();
        ll b = expression2->operator()();
        if(type == Type::Expression){
            if(op == Operator::Addition) return a+b;
            if(op == Operator::Subtraction) return a-b;
            if(op == Operator::Multiplication) return a*b;
            if(op == Operator::Division) return a/b;
        }
        if(type == Type::While || type == Type::If){
            if(compare == "<") return a < b;
            if(compare == "<=") return a <= b;
            if(compare == "==") return a == b;
            if(compare == "!=") return a != b;
        }
        return 1;
    }

    void run(){
        if(type == Type::While || type == Type::If || type == Type::Start){
            while(operator()()){
                for(auto ast : body){
                    ast->run();
                }
                if(type != Type::While) break;
            }
            return;
        }
        if(type == Type::Print) cout << expression1->operator()() << endl;
        if(type == Type::Assignment){
            ll val = expression1->operator()();
            variables[variable] = val;
        }
    }
};

int main() {

    freopen("fib.txt", "r", stdin);

    AST ast(Type::Start);
    ast.construct();
    ast.run();

    return 0;
}