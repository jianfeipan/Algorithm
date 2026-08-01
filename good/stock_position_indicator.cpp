/*
function: apply_strategy


Input:
   prices [48 27 56 56 58 64 63 78]
   buy_indicator [1, 1]: when price go down twice, buy 1 amount
   sell_indicator [-1, -1, 1]
output:
   pos [0 0 0 1 1 2 1 1 1]
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>


std::vector<int> apply_strategy(
   const std::vector<int>& prices,
   const std::vector<int>& buy_indicator,
   const std::vector<int>& sell_indicator) {


   size_t n = prices.size();
   if (n == 0) return {};


   std::vector<int> pos(n, 0);
   std::vector<int> window;
   window.reserve(n);


   auto trigger = [&window](const std::vector<int>& indicator) {
       if (indicator.empty() || window.size() < indicator.size()) return false;
       return std::equal(indicator.rbegin(), indicator.rend(), window.rbegin());
   };


   int current_pos = 0;
   for (size_t i = 1; i < n; ++i) {
       int diff = prices[i] - prices[i - 1];
       if (diff != 0) {
           // -1 = down move, +1 = up move
           window.emplace_back(diff > 0 ? 1 : -1);


           if (trigger(buy_indicator)) ++current_pos;
           if (trigger(sell_indicator)) --current_pos;
       } // ignore diff == 0


       pos[i] = current_pos;
   }


   return pos; // Added missing return
}


// Helper function to pretty print test cases
void run_test(const std::string& name,
             const std::vector<int>& prices,
             const std::vector<int>& buy_ind,
             const std::vector<int>& sell_ind) {


   std::cout << "========================================\n";
   std::cout << "Test: " << name << "\n";


   auto pos = apply_strategy(prices, buy_ind, sell_ind);


   std::cout << "Prices: [ ";
   for (int p : prices) std::cout << p << " ";
   std::cout << "]\nPos:    [ ";
   for (int p : pos) std::cout << p << " ";
   std::cout << "]\n\n";
}


int main() {
   // Test 1: Given example (Buy on 2 price drops: {-1, -1}, Sell on 2 drops then 1 rise: {-1, -1, 1})
   run_test("Standard Buy/Sell Patterns",
            {48, 27, 56, 56, 58, 64, 63, 62, 65},
            {-1, -1},       // Buy on 2 drops
            {-1, -1, 1});   // Sell on 2 drops then 1 rise


   // Test 2: Flat prices (diff == 0 handling)
   run_test("Flat Price Intervals",
            {10, 10, 8, 10, 8, 8, 6},
            {-1, -1},
            {1, 1});


   // Test 3: Multiple consecutive triggers
   run_test("Consecutive Triggers (Streak)",
            {10, 9, 8, 7, 6, 5},
            {-1, -1},       // Should trigger at index 2, 3, 4, 5
            {});


   // Test 4: Empty / Single element input
   run_test("Single Price Element",
            {100},
            {-1}, {1});


   // Test 5: Simultaneous Buy & Sell Trigger on same step
   run_test("Simultaneous Buy & Sell Trigger",
            {10, 8, 6, 8},
            {-1, -1},       // Triggers +1 at step 3
            {-1, -1});      // Triggers -1 at step 3 -> Net pos change = 0


   return 0;
}