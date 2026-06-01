#pragma once
#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <cstdint>

class EnterpriseTrie {
public:
    using NodeId = uint32_t;
    static constexpr NodeId kNullId = 0;
    static constexpr NodeId kRootId = 1;

private:
    // 紧凑的子节点边（Edge）结构，仅占 8 字节
    struct Edge {
        char label;
        NodeId child_id;

        // 按字符排序，便于二分查找
        bool operator<(const Edge& other) const { return label < other.label; }
        bool operator<(char c) const { return label < c; }
    };

    // 节点结构：通过消除指针，极大提高了 CPU 缓存友好度
    struct Node {
        std::vector<Edge> edges; // 工业级中常用可变长数组，或更高级的短数组优化(Inline/SOO)
        bool is_terminal = false;
    };

    // 内存池：所有节点在连续的内存中
    std::vector<Node> nodes_;

    // 分配新节点的内部方法
    NodeId alloc_node() {
        nodes_.emplace_back();
        return static_cast<NodeId>(nodes_.size() - 1);
    }

public:
    EnterpriseTrie() {
        // 占位第 0 号无用 ID（kNullId），让 kRootId=1 成为根节点
        nodes_.emplace_back(); 
        alloc_node(); 
    }

    // 插入优化：使用 string_view 避免拷贝
    void insert(std::string_view key) {
        if (key.empty()) return;

        NodeId curr_id = kRootId;
        for (char c : key) {
            auto& edges = nodes_[curr_id].edges;
            // 工业级压榨：子节点少时二分查找比 hash 快，且省内存
            auto it = std::lower_bound(edges.begin(), edges.end(), c);
            
            if (it == edges.end() || it->label != c) {
                // 没找到，创建新节点
                NodeId next_id = alloc_node();
                // 插入并保持有序
                edges.insert(it, Edge{c, next_id});
                curr_id = next_id;
            } else {
                // 找到了，直接复用
                curr_id = it->child_id;
            }
        }
        nodes_[curr_id].is_terminal = true;
    }

    // 查找前缀是否存在
    bool starts_with(std::string_view prefix) const {
        return find_node(prefix) != kNullId;
    }

    // 精确查找单词是否存在
    bool search(std::string_view key) const {
        NodeId id = find_node(key);
        return id != kNullId && nodes_[id].is_terminal;
    }

    // 显式释放内存（或重置）
    void clear() {
        nodes_.clear();
        nodes_.emplace_back();
        alloc_node();
    }

    // 估算当前占用的物理内存 (Byte)
    size_t memory_usage() const {
        size_t total = nodes_.capacity() * sizeof(Node);
        for (const auto& node : nodes_) {
            total += node.edges.capacity() * sizeof(Edge);
        }
        return total;
    }

private:
    // 核心辅助函数：沿前缀向下探测
    NodeId find_node(std::string_view sub_str) const {
        NodeId curr_id = kRootId;
        for (char c : sub_str) {
            const auto& edges = nodes_[curr_id].edges;
            auto it = std::lower_bound(edges.begin(), edges.end(), c);
            if (it == edges.end() || it->label != c) {
                return kNullId;
            }
            curr_id = it->child_id;
        }
        return curr_id;
    }
};
