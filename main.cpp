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
            for(auto &c : "+-*/"){
                if(c == in[0] || c == in.back()) throw("busigt");
            }
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
                variables[variable] = 0;
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
            }else{
                throw("naah");
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
        throw("ahop");
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

    void print(){
        if(type == Type::While || type == Type::If || type == Type::Start){
            if(type != Type::Start){
                cout << (type == Type::While?"while(":"if(");
                expression1->print();
                cout << compare;
                expression2->print();
                cout << "){\n";
            }
            for(auto ast : body){
                ast->print();
            }
            if(type != Type::Start) cout << "}\n";
            return;
        }
        if(type == Type::Expression){
            expression1->print();
            if(op == Operator::Addition) cout << '+';
            else if(op == Operator::Subtraction) cout << '-';
            else if(op == Operator::Multiplication) cout << '*';
            else if(op == Operator::Division) cout << '/';
            expression2->print();
        }
        if(type == Type::Number) cout << value;
        if(type == Type::Variable) cout << variable;
        if(type == Type::Print){
            cout << "cout << ";
            expression1->print();
            cout << " << endl;\n";
        }
        if(type == Type::Assignment){
            cout << variable << " = ";
            expression1->print();
            cout << ";\n";
        }
    }
};

int main() {

    string filename = "fib.txt";
    freopen(filename.c_str(), "r", stdin);

    AST ast(Type::Start);
    try{
        ast.construct();
        ast.run();
    }catch(exception e){
        cout << "Could not compile because: ";
        exit(0);
    }
    fclose(stdin);
    freopen("code.cpp", "w", stdout);

    cout << "#include <bits/stdc++.h>\nusing namespace std;\n#define ll long long\nll ";

    string toAdd;
    for(auto &[k, v] : variables){
        toAdd+=k+',';
    }
    toAdd.back() = ';';
    cout << toAdd << "\n\nint main() {\n";
    ast.print();
    cout << "   return 0;\n}";
    cout << endl;

    system(("g++ code.cpp -o " + filename.substr(0, filename.length()-4)).c_str());
    fclose(stdout);
    remove("code.cpp");

    return 0;
}