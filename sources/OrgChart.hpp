#ifndef ORGCHART_A_ORGCHART_H
#define ORGCHART_A_ORGCHART_H

#include <string>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include "IterType.hpp"

namespace ariel {

    class OrgChart {

    private:
        Node *root;

    public:
        class Iterator; // for the OrgChart class to be able to see Iterator class

        OrgChart();
        OrgChart(OrgChart& orgChart) = default;
        OrgChart(OrgChart&& orgChart) = default;

        OrgChart &add_root(std::string root_pos);

        OrgChart &add_sub(std::string pos_dad, std::string pos_son);

        Iterator begin_level_order();

        Iterator end_level_order();

        Iterator begin_reverse_order();

        Iterator reverse_order();

        Iterator begin_preorder();

        Iterator end_preorder();

        OrgChart::Iterator begin();

        OrgChart::Iterator end();

        ~OrgChart();

        OrgChart& operator=(OrgChart const &orgchart) = default;
        OrgChart& operator=(OrgChart &&orgchart) = default;

        friend std::ostream &operator<<(std::ostream &out, const OrgChart &org);

        class Iterator {
        private:
            std::vector<Node *> ordered;
            int index;

            void init_level_order(Node *root);

            void rec_preorder(Node *pre);

            void init_preorder(Node *root);

            void init_reverse_order(Node *root);

        public:

            Iterator(IterType type, Node *root);

            Node *get_curr() const;

            bool operator==(const Iterator &other) const;

            bool operator!=(const Iterator &other) const;

            Iterator &operator++(); // prefix adding

            Iterator operator++(int); // postfix adding

            Iterator &operator--(); // prefix sub

            Iterator operator--(int); // postfix sub

            std::string &operator*();

            std::string *operator->();

            ~Iterator();

        };

    };

}
#endif //ORGCHART_A_ORGCHART_H
