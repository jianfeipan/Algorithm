#include <string>
#include <string_view>
#include <cassert>
#include <stack>
#include <iostream>
#include <array>

{// no hpc
#include <string>
#include <cassert>
#include <memory>
#include <stack>
#include <stdexcept>
#include <iostream>

class Node{
public:
    virtual ~Node() = default;
    virtual bool evaluate() const = 0;
};

class Literal : public Node{
public:
    explicit Literal(bool value):m_value(value){}
    bool evaluate() const override { return m_value; }
private:
    bool m_value;
};

class Not : public Node{
public:
    Not(std::unique_ptr<Node> child):m_child(std::move(child)){}
    bool evaluate() const override { return !(m_child->evaluate()); }

    private:
    std::unique_ptr<Node> m_child;
};

class And : public Node{
public:
    And(std::unique_ptr<Node> left, std::unique_ptr<Node> right):
        m_left(std::move(left)),
        m_right(std::move(right)) {}

    bool evaluate() const override {
        return m_left->evaluate() && m_right->evaluate();
    }

    private:
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
};

class Or : public Node{
public:
    Or(std::unique_ptr<Node> left, std::unique_ptr<Node> right):
        m_left(std::move(left)),
        m_right(std::move(right)) {}

    bool evaluate() const override {
        return m_left->evaluate() || m_right->evaluate();
    }
private:
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
};

class Expression{
public:
    explicit Expression(const std::string& input){
        root = parse(input);
    }

    bool evaluate(){
        if(!root) return false;
        return root->evaluate();
    }

private:
    std::unique_ptr<Node> root;

    int getPrecedence(char op) const {
        if (op == '!') return 3;
        if (op == '&') return 2;
        if (op == '|') return 1;
        return 0;
    }

    static void applyOperator(std::stack<std::unique_ptr<Node>>& nodes, char op){
        if(op == '!'){ // pop one node
            if(nodes.empty()) throw std::runtime_error("Invalid expression");
            auto child = std::move(nodes.top()); nodes.pop();
            nodes.push(std::make_unique<Not>(std::move(child)));
            return;
        }

        if(nodes.size() < 2) throw std::runtime_error("Invalid expression");
        auto right = std::move(nodes.top()); nodes.pop();
        auto left = std::move(nodes.top()); nodes.pop();

        if(op == '&') nodes.push(std::make_unique<And>(std::move(left), std::move(right)));
        else if(op == '|') nodes.push(std::make_unique<Or>(std::move(left), std::move(right)));
        else throw std::runtime_error("Invalid expression");
    }

    std::unique_ptr<Node> parse(const std::string& input) const{
        std::stack<std::unique_ptr<Node>> nodes;
        std::stack<char> ops;
        
        for(size_t i = 0; i < input.size(); ++i){
            const auto c = input[i];
            if(c == 'T') nodes.push(std::make_unique<Literal>(true));
            else if(c == 'F') nodes.push(std::make_unique<Literal>(false));
            else if(c == '!' || c == '&' || c == '|'){
                // pop operators with higher or equal precedence
                while(!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(c)){
                    const auto op = ops.top(); ops.pop();
                    applyOperator(nodes, op);
                }
                ops.push(c);
            }else if(c == '('){
                ops.push(c);
            }else if(c == ')'){
                // parse back between '(' and ')'
                while(!ops.empty() && ops.top() != '('){
                    const auto op = ops.top(); ops.pop();
                    applyOperator(nodes, op);
                }
                if(ops.empty() || ops.top() != '(') throw std::runtime_error("Mismatched parentheses");
                ops.pop(); // pop '('
            }else{
                throw std::runtime_error("Invalid expression");
            }
        }

        // process remaining operators not in paratheses
        while(!ops.empty()){
            const auto op = ops.top(); ops.pop();
            if(op == '(') throw std::runtime_error("Mismatched parentheses");
            applyOperator(nodes, op);
        }

        if(nodes.size() != 1) throw std::runtime_error("Invalid expression");
        auto result = std::move(nodes.top()); nodes.pop();
        return result;
    }
};
} // no hpc 
/*
优化	     原版	                            HPC 版
求值方式	  建 AST 树 + 虚函数递归	          stack<bool> 边解析边求值，零堆分配
错误处理	  throw std::runtime_error	        Error 枚举返回值，无异常开销
stack 底层	 std::deque（默认）                 std::vector，cache 友好
参数类型	  const std::string&	            std::string_view，避免拷贝
优先级查询	  if-else 链	                     constexpr lookup table，O(1)
Node 类层次	 4 个类 + virtual + unique_ptr	    完全消除
*/
class Expression {
public:
    enum class Error { None, InvalidExpression, MismatchedParentheses };

    // Factory: no exception, returns error code
    static Error create(std::string_view input, Expression& out) {
        Error err = Error::None;
        bool result = false;
        err = evaluate(input, result);
        if (err == Error::None) {
            out.m_result = result;
            out.m_valid = true;
        }
        return err;
    }

    bool evaluate() const { return m_result; }
    bool valid() const { return m_valid; }

    // Direct evaluate without storing — most efficient path
    static Error evaluate(std::string_view input, bool& result) {
        std::stack<char, std::vector<char>> values;// vector<bool> should be avoid
        std::stack<char, std::vector<char>> ops;

        for (size_t i = 0; i < input.size(); ++i) {
            const char c = input[i];
            if (c == 'T')      values.push(true);
            else if (c == 'F') values.push(false);
            else if (c == '!' || c == '&' || c == '|') {
                while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                    const char op = ops.top(); ops.pop();
                    if (!applyOperator(values, op))
                        return Error::InvalidExpression;
                }
                ops.push(c);
            } else if (c == '(') {
                ops.push(c);
            } else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    const char op = ops.top(); ops.pop();
                    if (!applyOperator(values, op))
                        return Error::InvalidExpression;
                }
                if (ops.empty() || ops.top() != '(')
                    return Error::MismatchedParentheses;
                ops.pop();
            } else {
                return Error::InvalidExpression;
            }
        }

        while (!ops.empty()) {
            const char op = ops.top(); ops.pop();
            if (op == '(') return Error::MismatchedParentheses;
            if (!applyOperator(values, op))
                return Error::InvalidExpression;
        }

        if (values.size() != 1) return Error::InvalidExpression;
        result = values.top();
        return Error::None;
    }

private:
    bool m_result = false;
    bool m_valid = false;

    // Lookup table: O(1) precedence
    static constexpr int precedence(char op) {
        // '!' = 33, '&' = 38, '|' = 124
        constexpr auto table = [] {
            std::array<int, 128> t{};
            t['!'] = 3;
            t['&'] = 2;
            t['|'] = 1;
            return t;
        }();
        return (static_cast<unsigned char>(op) < 128) ? table[static_cast<unsigned char>(op)] : 0;
    }

    // Returns false on error (instead of throwing)
    static bool applyOperator(std::stack<bool, std::vector<bool>>& values, char op) {
        if (op == '!') {
            if (values.empty()) return false;
            bool v = values.top(); values.pop();
            values.push(!v);
            return true;
        }
        if (values.size() < 2) return false;
        bool right = values.top(); values.pop();
        bool left  = values.top(); values.pop();
        if (op == '&')      values.push(left && right);
        else if (op == '|') values.push(left || right);
        else return false;
        return true;
    }
};

const char* errorToString(Expression::Error err) {
    switch (err) {
        case Expression::Error::None:                   return "None";
        case Expression::Error::InvalidExpression:      return "Invalid expression";
        case Expression::Error::MismatchedParentheses:  return "Mismatched parentheses";
    }
    return "Unknown";
}

int main() {
    // Test helper: no exception, no heap allocation in hot path
    auto test = [](std::string_view input, bool expected) {
        bool result = false;
        auto err = Expression::evaluate(input, result);
        if (err == Expression::Error::None && result == expected) {
            std::cout << "PASS: \"" << input << "\"\n";
        } else {
            std::cerr << "FAILED: \"" << input
                      << "\" expected=" << expected
                      << " got=" << result
                      << " err=" << errorToString(err) << "\n";
            assert(false);
        }
    };

    test("T", true);
    test("F", false);

    test("!F", true);
    test("!T", false);

    test("T&T", true);
    test("T&F", false);
    test("T|F", true);
    test("F|F", false);

    // with precedence
    test("!T&F", false); // !T is false, false & F is false
    test("!F|F", true);  // !F is true, true | F is true
    test("T&!F", true);  // !F is true, T & true is true
    test("F|!T", false); // !T is false, F | false is false

    // with parentheses
    test("!(T&F)", true);  // T&F is false, !false is true
    test("!(T|F)", false); // T|F is true, !true is false
    test("!(T&!F)", false); // !F is true, T&true is true, !true is false
    test("!(F|!T)", true);  // !T is false, F|false is false, !false is true

    // complex expressions
    test("!(T&F)|T", true);  // !(T&F) is true, true|T is true
    test("!(T|F)&F", false); // !(T|F) is false, false&F is false
    test("!(T&!F)|F", false); // !F is true, T&true is true, !true is false, false|F is false
    test("!(F|!T)&T", true);  // !T is false, F|false is false, !false is true, true&T is true

    // Error cases: no exceptions, just error codes
    auto testError = [](std::string_view input, Expression::Error expectedErr) {
        bool result = false;
        auto err = Expression::evaluate(input, result);
        if (err == expectedErr) {
            std::cout << "PASS (error): \"" << input << "\" -> " << errorToString(err) << "\n";
        } else {
            std::cerr << "FAILED (error): \"" << input
                      << "\" expected=" << errorToString(expectedErr)
                      << " got=" << errorToString(err) << "\n";
            assert(false);
        }
    };

    testError("T&",  Expression::Error::InvalidExpression);
    testError("T|",  Expression::Error::InvalidExpression);
    testError("T^F", Expression::Error::InvalidExpression);
    testError("(T&F", Expression::Error::MismatchedParentheses);
    testError("T&F)", Expression::Error::MismatchedParentheses);

    // Also test the factory create() path
    Expression exp;
    auto err = Expression::create("T&!F", exp);
    assert(err == Expression::Error::None);
    assert(exp.evaluate() == true);

    std::cout << "All tests passed.\n";
}
