#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>

using std::cout;
using std::endl;
using std::unordered_map;
using std::list;
using std::pair;

class LRUCache {
public:
    LRUCache(int capacity)
        : capacity_(capacity)
    {}

    int get(int key) {
        auto ret = map_.find(key);
        if (ret != map_.end()) {
            // 将对应元素移动至链表最前端
            lru_list_.splice(lru_list_.begin(), lru_list_, ret->second);
            return ret->second->second;
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        auto ret = map_.find(key);
        // 若元素已经存在,则更新value
        if (ret != map_.end()) {
            map_[key]->second = value;
            // 并将对应元素移动至链表最前端
            lru_list_.splice(lru_list_.begin(), lru_list_, ret->second);
        } else {
            // 元素不存在则执行插入逻辑
            if (capacity_ == lru_list_.size()) { //容量已满
                auto end = --lru_list_.end();
                // 删除map中的该尾结点所对应的元素
                map_.erase(end->first);
                // 删除链表尾结点
                lru_list_.erase(end);
            }
            // 在链表头结点处加入该元素
            lru_list_.push_front({key, value});
            // 在map中添加新元素
            map_.insert({key, lru_list_.begin()});
        }
    }

private:
    int capacity_;
    unordered_map<int, list<pair<int,int>>::iterator> map_;
    list<pair<int,int>> lru_list_;
};

int main(int argc, char* argv[]) {
    LRUCache lRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    int ret = lRUCache.get(1); // 返回 1
    cout << ret << endl;
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    ret = lRUCache.get(2); // 返回 -1 (未找到)
    cout << ret << endl;
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    ret = lRUCache.get(1); // 返回 -1 (未找到)
    cout << ret << endl;
    ret = lRUCache.get(3); // 返回 3
    cout << ret << endl;
    ret = lRUCache.get(4); // 返回 4
    cout << ret << endl;

    return 0;
}

