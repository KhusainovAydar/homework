#include <iostream>

struct Node {
    int value;
    Node * next;

    Node(int newValue)
        : value(newValue)
        , next(nullptr)
    {}

    Node(){}
};

class List {
public:
    List()
        : first(nullptr)
        , last(nullptr)
        , num(0)
    {}

    ~List() {
        while (first != nullptr) {
            Node * tmp = first;
            first = first->next;
            delete tmp;
        }
    }

    void set(Node * newFirst, Node * newLast, size_t newNum) {
        first = newFirst;
        last = newLast;
        num = newNum;
    }

    void clear() {
        set(nullptr, nullptr, 0);
    }

    Node * get_first() const {
        return first;
    }

    Node * get_last() const {
        return last;
    }

    size_t size() const {
        return num;
    }

    void add(int value) {
        ++num;
        if (first == nullptr) {
            first = last = new Node(value);
        } else {
            last->next = new Node(value);
            last = last->next;
        }
    }

    void add(Node * node) {
        ++num;
        if (first == nullptr) {
            first = last = node;
        } else {
            last->next = node;
            last = last->next;
        }
    }

private:
    Node * first;
    Node * last;
    size_t num;
};

void merge_sort(List& list) {
    if (list.size() > 1) {
        size_t midSize = list.size() / 2;
        List left, right;

        Node * middle = list.get_first();
        Node * prev_middle = new Node();
        for (size_t i = 0; i != midSize; ++i) {
            prev_middle = middle;
            middle = middle->next;
        }
        prev_middle->next = nullptr;
        left.set(list.get_first(), prev_middle, midSize);
        right.set(middle, list.get_last(), list.size() - midSize);

        merge_sort(left);
        merge_sort(right);

        list.clear();
        Node * first = left.get_first();
        Node * second = right.get_first();

        while (first != nullptr && second != nullptr) {
            if (first->value <= second->value) {
                list.add(first);
                first = first->next;
            } else {
                list.add(second);
                second = second->next;
            }
        }

        while (first != nullptr)  {
            list.add(first);
            first = first->next;
        }

        while (second != nullptr)  {
            list.add(second);
            second = second->next;
        }

        left.clear();
        right.clear();
    }
}

int main() {
    size_t n;
    std::cin >> n;

    List array;
    for (size_t i = 0; i != n; ++i) {
        int x;
        std::cin >> x;
        array.add(x);
    }

    merge_sort(array);

    Node * out = array.get_first();
    while (out) {
        std::cout << out->value << ' ';
        out = out->next;
    }
}
