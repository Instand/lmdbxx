# lmdbxx
Universal C++17 library wrapper of [LMDB](https://github.com/LMDB/lmdb) and [lmdbxx](https://github.com/drycpp/lmdbxx) offering an object-oriented resource interface with RAII semantics. Based on [signals](https://github.com/Instand/signals) library. Has easy and comprehensive API with many template methods.

## Features

- C++17
- Easy to use
- Signals
- Key-Value DB Native performance
- Memory mapping
- Data convertion to base types and containers

## Example

Create and open database
```cpp
#include <lmdb.hpp>

const auto dbPath = "./temppath";

int main() {
    cs::Lmdb db(dbPath);
    cs::Connector::connect(&db.failed, [](const cs::LmdbException& error){
        std::cout << "Data base error occured " << error.what() << std::endl;
    });
    
    db.open();    
    return 0;
}
```
It will create lmdb with helper "./temppath" path (If it does not exist).
You may check path creation with isPathOk method. Lmdb destructor does not remove the path, you should do it manually.
It is better to connect signals before the base opened.

Insert and remove elements
```cpp
#include <array>
#include <vector>

#include <lmdb.hpp>

const auto dbPath = "./temppath";

class Watcher {
public slots:
    void onInserted(const std::string_view data) {
        std::cout << "Key with binary size " << data.size() << " inserted\n";
    }
    
    void onRemoved(const std::string_view data) {
        std::cout << "Key with binary size " << data.size() << " removed\n";
    }
};

int main() {
    cs::Lmdb db(dbPath);
    Watcher watcher;
    
    cs::Connector::connect(&db.commited, &watcher, &Watcher::onInserted);
    cs::Connector::connect(&db.removed, &watcher, &Watcher::onRemoved);
    
    db.open();
    
    db.insert(std::string("Key1"), std::string("Value1"));
    db.insert(std::string_view("Key2"), std::string_view("Value2"));
    
    std::cout << "Is Key1 exists: " << db.isKeyExists("Key1");
    std::cout << "Is Key2 exists: " << db.isKeyExists(std::vector<char>{'K', 'e', 'y', '2'});
    
    db.remove(std::array<char, 4>{'K', 'e', 'y', '1'});
    db.remove("Key2");
    
    return 0;
}
```
Lmdb always checks only binary representation of type.
