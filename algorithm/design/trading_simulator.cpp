// ============================================================
// . Trading Simulator
//    - Maintains a limit order book (bids/asks)
//    - Supports submitting limit and market orders
//    - Matches orders when bid >= ask
// ============================================================
enum class Side { Buy, Sell };

struct Order {
    int id;
    Side side;
    double price;
    int quantity;
    bool operator<(const Order& that){
        return this->price < that.price;
    }
    bool operator>(const Order& that){
        return this->price > that.price;
    }
};

class TradingSimulator {
    int nextOrderId = 1;
    // max-heap for bids (highest price first)
    priority_queue<Order, vector<Order>, less<Order>> bids;
    // min-heap for asks (lowest price first)
    priority_queue<Order, vector<Order>, greater<Order>> asks;

public:
    TradingSimulator()
        : bids(),
          asks() {}

    // Submit a limit order
    void limitOrder(Side side, double price, int quantity) {
        Order order{nextOrderId++, side, price, quantity};

        cout << "  Order #" << order.id << " "
             << (side == Side::Buy ? "BUY" : "SELL")
             << " " << quantity << " @ " << fixed << setprecision(2) << price << endl;

        auto matchAndPlace = [&](auto& matchBook, auto& restBook, auto canMatch) {
            while (order.quantity > 0 && !matchBook.empty() && canMatch(matchBook.top())) {
                Order top = matchBook.top();
                matchBook.pop();
                const auto filled = min(order.quantity, top.quantity);
                cout << "    -> Trade: " << filled << " units @ "
                     << fixed << setprecision(2) << top.price << endl;
                order.quantity -= filled;
                top.quantity -= filled;
                if (top.quantity > 0) matchBook.push(top);
            }
            if (order.quantity > 0) restBook.push(order);
        };

        if (side == Side::Buy)
            matchAndPlace(asks, bids, [&](const Order& o) { return o.price <= order.price; });
        else
            matchAndPlace(bids, asks, [&](const Order& o) { return o.price >= order.price; });
    }

    // Submit a market order (executes at best available price)
    void marketOrder(Side side, int quantity) {
        cout << "  Market " << (side == Side::Buy ? "BUY" : "SELL")
             << " " << quantity << " units" << endl;
        if (side == Side::Buy) {
            while (quantity > 0 && !asks.empty()) {
                Order ask = asks.top();
                asks.pop();
                int filled = min(quantity, ask.quantity);
                cout << "    -> Trade: " << filled << " units @ "
                     << fixed << setprecision(2) << ask.price << endl;
                quantity -= filled;
                ask.quantity -= filled;
                if (ask.quantity > 0) asks.push(ask);
            }
            if (quantity > 0) cout << "    -> " << quantity << " units unfilled (no asks)" << endl;
        } else {
            while (quantity > 0 && !bids.empty()) {
                Order bid = bids.top();
                bids.pop();
                int filled = min(quantity, bid.quantity);
                cout << "    -> Trade: " << filled << " units @ "
                     << fixed << setprecision(2) << bid.price << endl;
                quantity -= filled;
                bid.quantity -= filled;
                if (bid.quantity > 0) bids.push(bid);
            }
            if (quantity > 0) cout << "    -> " << quantity << " units unfilled (no bids)" << endl;
        }
    }

    void printBook() const {
        cout << "  [Order Book] Bids: " << bids.size()
             << ", Asks: " << asks.size() << endl;
    }
};

// ============================================================
// Main — demo all three components
// ============================================================
int main() {

    //  Trading Simulator
    cout << "=== Trading Simulator ===" << endl;
    TradingSimulator sim;
    sim.limitOrder(Side::Buy,  100.00, 50);
    sim.limitOrder(Side::Buy,  101.50, 30);
    sim.limitOrder(Side::Sell, 102.00, 40);
    sim.limitOrder(Side::Sell, 100.50, 20);  // crosses the bid at 101.50
    sim.printBook();
    sim.marketOrder(Side::Buy, 25);          // takes from asks
    sim.printBook();

    return 0;
}
