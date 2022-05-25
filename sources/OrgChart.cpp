#include "OrgChart.hpp"
#include "IterType.hpp"
#include <queue>
#include <stack>

namespace ariel {

    ///////////////////////////////////////////// OrgChart class //////////////////////////////////////////////

    OrgChart::OrgChart() {
        root = nullptr;
    }

    OrgChart &OrgChart::add_root(std::string root_pos) {
        if (root == nullptr) {
            this->root = new Node(root_pos, NULL);
        }
        else{
            root->replacePosition(root_pos);
        }
        return *this;
    }

    OrgChart &OrgChart::add_sub(std::string pos_dad, std::string pos_son) {
        if (root == nullptr){
            throw std::runtime_error("ERROR can't add sub to empty chart.");
        }
        Iterator iter = begin_level_order();
        bool find = false;
        for (Iterator iter = begin_level_order(); iter != end_level_order(); ++iter) {
            if (*iter == pos_dad) {
                Node *son = new Node(pos_son, iter.get_curr());
                iter.get_curr()->addSon(son);
                find = true;
            }
        }
        if (!find){
            throw std::runtime_error("ERROR can't add sub to not exist node.");
        }
        return *this;
    }

    OrgChart::Iterator OrgChart::begin_level_order() { return Iterator(IterType::begin_level_order, root); }

    OrgChart::Iterator OrgChart::end_level_order() { return Iterator(IterType::end_level_order, root); }

    OrgChart::Iterator OrgChart::begin_reverse_order() { return Iterator(IterType::begin_reverse_order, root); }

    OrgChart::Iterator OrgChart::reverse_order() { return Iterator(IterType::end_reverse_order, root); }

    OrgChart::Iterator OrgChart::begin_preorder() { return Iterator(IterType::begin_preorder, root); }

    OrgChart::Iterator OrgChart::end_preorder() { return Iterator(IterType::end_preorder, root); }

    OrgChart::Iterator OrgChart::begin() { return Iterator(IterType::begin_level_order, root); }

    OrgChart::Iterator OrgChart::end() { return Iterator(IterType::end_level_order, root); }

    OrgChart::~OrgChart() {
        std::vector<Node*> to_del;
        std::queue < Node * > queue = std::queue<Node *>();
        queue.push(root);
        while (!queue.empty()) {
            to_del.push_back(queue.front());
            for (Node *node: queue.front()->get_sons()) {
                queue.push(node);
            }
            queue.pop();
        }
        for (Node* node : to_del){
            delete node;
        }
    }

    std::ostream &operator<<(std::ostream &out, const OrgChart &org) { return out; }

    //////////////////////////////////////////// Iterator class ///////////////////////////////////////////

    void OrgChart::Iterator::init_level_order(Node *root) {
        std::queue < Node * > queue = std::queue<Node *>();
        queue.push(root);
        Node *curr;
        while (!queue.empty()) {
            curr = queue.front();
            ordered.push_back(queue.front());
            for (Node *node: curr->get_sons()) {
                queue.push(node);
            }
            queue.pop();
        }
    }

    void OrgChart::Iterator::rec_preorder(Node *pre) {
        ordered.push_back(pre);
        for (size_t i = 0; i < pre->get_sons().size(); ++i) {
            rec_preorder(pre->get_sons()[i]);
        }
    }

    void OrgChart::Iterator::init_preorder(Node *root) {
        rec_preorder(root);
    }

    void OrgChart::Iterator::init_reverse_order(Node *root) {
        std::stack < Node * > stack = std::stack<Node *>();
        std::queue < Node * > queue = std::queue<Node *>();
        queue.push(root);
        Node *temp;
        while (!queue.empty()) {
            temp = queue.front();
            queue.pop();
            stack.push(temp);
            for (int i = (temp->get_sons().size() - 1); i >= 0; --i) {
                queue.push(temp->get_sons()[(size_t) i]);
            }
        }
        while (!stack.empty()) {
            ordered.push_back(stack.top());
            stack.pop();
        }
    }

    OrgChart::Iterator::Iterator(IterType type, Node *root) {
        ordered = std::vector<Node *>();
        if (IterType::begin_level_order == type) {
            init_level_order(root);
            index = 0;
        }
        if (IterType::end_level_order == type) {
            init_level_order(root);
            index = ordered.size();
        }
        if (IterType::begin_preorder == type) {
            init_preorder(root);
            index = 0;
        }
        if (IterType::end_preorder == type) {
            init_preorder(root);
            index = ordered.size();
        }
        if (IterType::begin_reverse_order == type) {
            init_reverse_order(root);
            index = 0;
        }
        if (IterType::end_reverse_order == type) {
            init_reverse_order(root);
            index = ordered.size();
        }
    }

    Node *OrgChart::Iterator::get_curr() const {
        if (index >= ordered.size() || index < 0) {
            return nullptr;
        }
        return ordered[(size_t) index];
    }

    OrgChart::Iterator &OrgChart::Iterator::operator++() {
        ++index;
        return *this;
    }

    OrgChart::Iterator OrgChart::Iterator::operator++(int) { return *this; }

    OrgChart::Iterator &OrgChart::Iterator::operator--() {
        --index;
        return *this;
    }

    OrgChart::Iterator OrgChart::Iterator::operator--(int) { return *this; }

    bool OrgChart::Iterator::operator==(const Iterator &other) const {
        return this->get_curr() == other.get_curr();
    }

    bool OrgChart::Iterator::operator!=(const Iterator &other) const { return !(*this == other); }

    std::string &OrgChart::Iterator::operator*() { return get_curr()->get_pos(); }

    std::string *OrgChart::Iterator::operator->() { return &(get_curr()->get_pos()); }

    OrgChart::Iterator::~Iterator() {}

}
