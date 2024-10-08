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

enum Type {
    Start,
    While,
    If,
    Print,
    Assignment,

    Expression,
    Variable,
    Number,
};



struct AST{
    Type type;
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
        }
        while(cin >> in){
            deb(in);
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
                // cin >> ast->variable >> equals >> ast->expression1;
                ast->construct();
                body.pb(ast);
            }
        }
    }


    ll operator()(){

        return true;
    }
};

int main() {

    freopen("code.txt", "r", stdin);

    AST ast(Type::Start);
    ast.construct();

    return 0;
}