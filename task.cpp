#include <iostream>

template<typename T>
struct Node {
    T value;
    bool isRoot;
    Node * next;

    Node(T newValue)
        : value(newValue)
        , next(nullptr)
        , isRoot(false)
    {}

    Node()
        : isRoot(true)
    {}
};

template<typename T>
class List {
public:
    List()
        : first(new Node<T>())
        , last(first)
        , num(0)
    {}

    ~List() {
        while (first != nullptr) {
            Node<T> * tmp = first;
            first = first->next;
            delete tmp;
        }
    }

    void set(Node<T> * newFirst, Node<T> * newLast, size_t newNum) {
        first = new Node<T>();
        first->next = newFirst;
        last = newLast;
        num = newNum;
    }

    void clear() {
        set(nullptr, nullptr, 0);
    }

    Node<T> * get_first() const {
        return first;
    }

    Node<T> * get_last() const {
        return last;
    }

    size_t size() const {
        return num;
    }

    void insertNode(Node<T> * node, T value) {
        if (node == last) {
            addValue(value);
        } else {
            Node<T> * copy = new Node<T>(value);
            copy->next = node->next;
            node->next = copy;
            ++num;
        }
    }

    void addValue(T value) {
        ++num;
        if (first == last) {
            first->next = new Node<T>(value);
            last = first->next;
        } else {
            last->next = new Node<T>(value);
            last = last->next;
        }
    }

private:
    Node<T> * first;
    Node<T> * last;
    size_t num;
};

void merge(List<int>& left, List<int>& right) {
    Node<int> * first = left.get_first();
    Node<int> * second = right.get_first();
    size_t numFirst = 0, numSecond = 0;
    size_t leftSize = left.size(), rightSize = right.size();

    while (numFirst < leftSize && numSecond < rightSize) {
        int valFirst = first->next->value,
                valSecond = second->next->value;

        if (valFirst <= valSecond) {
            first = first->next;
            ++numFirst;
        } else {
            left.insertNode(first, valSecond);
            first = first->next;
            second = second->next;
            ++numSecond;
        }
    }

    while (numSecond < rightSize) {
        int valSecond = second->next->value;
        left.addValue(valSecond);
        second = second->next;
        ++numSecond;
    }
}

void split(List<int>& list, size_t midSize, List<int>& left, List<int>& right) {
    Node<int> * middle = list.get_first();
    Node<int> * prevMiddle = new Node<int>();
    middle = middle->next;

    for (size_t i = 0; i != midSize; ++i) {
        prevMiddle = middle;
        middle = middle->next;
    }
    prevMiddle->next = nullptr;

    left.set(list.get_first()->next, prevMiddle, midSize);
    right.set(middle, list.get_last(), list.size() - midSize);
}

void merge_sort(List<int>& list) {
    if (list.size() > 1) {
        size_t midSize = list.size() / 2;
        List<int> left, right;

        split(list, midSize, left, right);
        merge_sort(left);
        merge_sort(right);
        merge(left, right);

        list = left;
        left.clear();
        right.clear();
    }
}

int main() {
    size_t n;
    std::cin >> n;

    List<int> array;
    for (size_t i = 0; i != n; ++i) {
        int x;
        std::cin >> x;
        array.addValue(x);
    }

    merge_sort(array);

    Node<int> * out = array.get_first();
    while (out) {
        if (out->isRoot) {
            out = out->next;
            continue;
        }
        std::cout << out->value << ' ';
        out = out->next;
    }
}
