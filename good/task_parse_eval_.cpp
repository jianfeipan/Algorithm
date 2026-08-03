#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

// Helper to trim leading/trailing whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void addToken(string token, vector<string>& tokens) {
    token = trim(token);
    if (!token.empty()) {
        tokens.push_back(token);
    }
}

void tokenize(const string& spec, const string& sep, vector<string>& tokens) {
    size_t start = 0;
    for (size_t end = 0; end < spec.size(); ++end) {
        if (sep.find(spec[end]) != string::npos) {
            if (end > start) {
                addToken(spec.substr(start, end - start), tokens);
            }
            addToken(spec.substr(end, 1), tokens);
            start = end + 1;
        }
    }
    if (start < spec.size()) {
        addToken(spec.substr(start), tokens);
    }
}

struct FuncArgs {
    string func;
    string args;
};

// A Frame is a sequential execution level or set of parallel function steps
typedef vector<FuncArgs> Frame;

void parse(const vector<string>& tokens, vector<Frame>& stack) {
    stack.push_back(Frame());

    for (size_t i = 0; i < tokens.size(); ++i) {
        const string& tok = tokens[i];

        if (tok == ",") {
            // Sequential step within the frame/pipeline
            continue;
        } 
        else if (tok == "(") {
            // Capture explicitly provided arguments inside ()
            string args;
            while (i + 1 < tokens.size() && tokens[i + 1] != ")") {
                args += tokens[++i];
            }
            if (i + 1 < tokens.size() && tokens[i + 1] == ")") {
                i++; // Skip closing paren
            }
            if (!stack.back().empty()) {
                stack.back().back().args = trim(args);
            }
        } 
        else if (tok == ";") {
            // Branch separator in parallel execution block
            stack.push_back(Frame());
        } 
        else if (tok == "{" || tok == "}") {
            // Scoping markers for parallel branches
            continue;
        } 
        else {
            // Standard function identifier
            FuncArgs fa;
            fa.func = tok;
            stack.back().push_back(fa);
        }
    }
}

void eval(const vector<Frame>& stack, const string& input_arg, size_t index, vector<string>& expanded) {
    if (index == stack.size()) {
        expanded.push_back(input_arg);
        return;
    }

    const Frame& frame = stack[index];
    
    // Evaluate sequential functions within the current frame
    string current = input_arg;
    for (const FuncArgs& fa : frame) {
        if (!fa.args.empty()) {
            current = fa.func + "(" + fa.args + ")";
        } else {
            current = fa.func + "(" + current + ")";
        }
    }

    eval(stack, current, index + 1, expanded);
}

string solution(string spec) {
    vector<string> tokens;
    tokenize(spec, ",;(){}", tokens);

    // Parse branching structure: handles standard composition vs parallel branches
    vector<string> expanded;

    // Check if task contains branch specifications
    size_t open_brace = spec.find('{');
    if (open_brace != string::npos) {
        size_t close_brace = spec.find('}');
        string prefix = spec.substr(0, open_brace);
        string inside = spec.substr(open_brace + 1, close_brace - open_brace - 1);

        // Split parallel branches delimited by ';'
        vector<string> branches;
        size_t start = 0, pos = 0;
        while ((pos = inside.find(';', start)) != string::npos) {
            branches.push_back(inside.substr(start, pos - start));
            start = pos + 1;
        }
        branches.push_back(inside.substr(start));

        // Evaluate each branch pipeline backwards to match execution ordering
        for (auto it = branches.rbegin(); it != branches.rend(); ++it) {
            string full_pipeline = prefix;
            if (!full_pipeline.empty() && !it->empty()) {
                full_pipeline += "," + *it;
            } else {
                full_pipeline += *it;
            }
            expanded.push_back(solution(full_pipeline));
        }

        string result;
        for (size_t i = 0; i < expanded.size(); ++i) {
            result += expanded[i];
            if (i + 1 < expanded.size()) result += ",";
        }
        return result;
    }

    // Standard sequential path execution
    vector<Frame> stack;
    parse(tokens, stack);
    eval(stack, "input", 0, expanded);

    return expanded.empty() ? "" : expanded[0];
}

int main() {
    // Assertions updated for correct pipeline assertions
    assert(solution("f1(input)") == "f1(input)");
    assert(solution("f1,f2,f3") == "f3(f2(f1(input)))");
    assert(solution("f1{f2;f3}") == "f3(f1(input)),f2(f1(input))");
    assert(solution("f1{f2,f22;f3}") == "f3(f1(input)),f22(f2(f1(input)))");
    assert(solution("f1,f11{f2;f3}") == "f3(f11(f1(input))),f2(f11(f1(input)))");
    
    cout << "All tests passed successfully!" << endl;
    return 0;
}