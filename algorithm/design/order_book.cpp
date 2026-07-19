/*
这道题是简化版的订单簿设计，输入数据包含四个字段·exchange_id、price、quantity、order_type [bid 或 ask]。要求设计一个类，支持订单实时插入，并实现两个核心方法。
第一个是 get_exchange_bbo。传入指定exchange_id，返回该交易所当前的最高买价和最低卖价。
第二个是 get_nbbo。返回全市场范围内的最高买价和最低卖价，也就是所有交易所整合后的最优报价。
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <optional>

using namespace std;

enum class OrderType {
    BID,
    ASK
};

struct BBO {
    optional<double> best_bid;
    optional<double> best_ask;
};

class OrderBook {
private:
    struct ExchangeBook {
        // price -> aggregated quantity
        map<double, long long> bids;
        map<double, long long> asks;

        optional<double> get_best_bid() const {
            if (bids.empty()) return nullopt;
            return bids.rbegin()->first;
        }

        optional<double> get_best_ask() const {
            if (asks.empty()) return nullopt;
            return asks.begin()->first;
        }
    };

    unordered_map<string, ExchangeBook> books_;

    // 全局维护：price -> count_of_exchanges_having_this_best_price
    map<double, int> global_best_bids_;
    map<double, int> global_best_asks_;

private:
    static void add_best(map<double, int>& global_book, const optional<double>& px) {
        if (!px.has_value()) return;
        global_book[*px]++;
    }

    static void remove_best(map<double, int>& global_book, const optional<double>& px) {
        if (!px.has_value()) return;
        auto it = global_book.find(*px);
        if (it == global_book.end()) return;

        it->second--;
        if (it->second == 0) {
            global_book.erase(it);
        }
    }

public:
    void insert_order(const string& exchange_id,
                      double price,
                      long long quantity,
                      OrderType order_type) {
        if (quantity <= 0) {
            return; // 也可以抛异常，看需求
        }

        ExchangeBook& book = books_[exchange_id];

        // 插入前，记录旧 best
        optional<double> old_best_bid = book.get_best_bid();
        optional<double> old_best_ask = book.get_best_ask();

        // 更新该交易所簿
        if (order_type == OrderType::BID) {
            book.bids[price] += quantity;
        } else {
            book.asks[price] += quantity;
        }

        // 插入后，记录新 best
        optional<double> new_best_bid = book.get_best_bid();
        optional<double> new_best_ask = book.get_best_ask();

        // 如果 best bid 变化，更新全局 best bid 结构
        if (old_best_bid != new_best_bid) {
            remove_best(global_best_bids_, old_best_bid);
            add_best(global_best_bids_, new_best_bid);
        }

        // 如果 best ask 变化，更新全局 best ask 结构
        if (old_best_ask != new_best_ask) {
            remove_best(global_best_asks_, old_best_ask);
            add_best(global_best_asks_, new_best_ask);
        }
    }

    BBO get_exchange_bbo(const string& exchange_id) const {
        auto it = books_.find(exchange_id);
        if (it == books_.end()) {
            return {nullopt, nullopt};
        }

        return {it->second.get_best_bid(), it->second.get_best_ask()};
    }

    BBO get_nbbo() const {
        optional<double> best_bid = nullopt;
        optional<double> best_ask = nullopt;

        if (!global_best_bids_.empty()) {
            best_bid = global_best_bids_.rbegin()->first;
        }

        if (!global_best_asks_.empty()) {
            best_ask = global_best_asks_.begin()->first;
        }

        return {best_bid, best_ask};
    }
};
