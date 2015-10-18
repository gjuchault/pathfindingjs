#ifndef _NODEH_
#define _NODEH_

class Node {
    public:
        int x = 0;
        int y = 0;
        bool walkable = false;

        float f = 0;
        float g = 0;
        float h = 0;
        bool closed = false;
        bool opened = false;

        Node* parent = nullptr;

        Node (int x_, int y_, bool walkable_ = true) : x(x_), y(y_), walkable(walkable_) {};
};

#endif
