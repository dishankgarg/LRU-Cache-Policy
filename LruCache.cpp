#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    class node {
    public:
        int key;
        int val;
        node* next;
        node* prev;
        node(int _key, int _val) {
            key = _key;
            val = _val;
            next = nullptr;
            prev = nullptr;
        }
    };

    node* head = new node(-1, -1);
    node* tail = new node(-1, -1);

    int cap;
    unordered_map<int, node*> m;

    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        node* current = head;
        while (current) {
            node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void addnode(node* newnode) {
        node* temp = head->next;
        newnode->next = temp;
        newnode->prev = head;
        head->next = newnode;
        temp->prev = newnode;
    }

    void deletenode(node* delnode) {
        node* delprev = delnode->prev;
        node* delnext = delnode->next;
        delprev->next = delnext;
        delnext->prev = delprev;
        delete delnode;
    }

    int get(int key_) {
        if (m.find(key_) != m.end()) {
            node* resnode = m[key_];
            int res = resnode->val;
            m.erase(key_);
            deletenode(resnode);
            addnode(new node(key_, res));
            m[key_] = head->next;
            return res;
        }
        return -1;
    }

    void put(int key_, int value) {
        if (m.find(key_) != m.end()) {
            node* existingnode = m[key_];
            m.erase(key_);
            deletenode(existingnode);
        }
        if (m.size() == cap) {
            m.erase(tail->prev->key);
            deletenode(tail->prev);
        }

        addnode(new node(key_, value));
        m[key_] = head->next;
    }
};

int main() {
    int capacity;
    cout << "Enter the capacity of the LRU Cache: ";
    cin >> capacity;
    
    LRUCache* cache = new LRUCache(capacity);

    while (true) {
        cout << "\nChoose an operation:\n";
        cout << "1. Put (Insert/Update key-value)\n";
        cout << "2. Get (Retrieve value by key)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1/2/3): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int key, value;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            cache->put(key, value);
            cout << "Inserted/Updated key " << key << " with value " << value << ".\n";
        } else if (choice == 2) {
            int key;
            cout << "Enter key to retrieve: ";
            cin >> key;
            int result = cache->get(key);
            if (result != -1) {
                cout << "Value for key " << key << " is: " << result << "\n";
            } else {
                cout << "Key " << key << " not found in cache.\n";
            }
        } else if (choice == 3) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    delete cache;
    return 0;
}
