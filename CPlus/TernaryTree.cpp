template <typename InternalValueType = unsigned long long>
class TernaryTree {
public:
    TernaryTree() {
        bit_shift = log2(sizeof(InternalValueType));
    }

    /**
     *  @brief PUT
     *
     *  @return Ternary Search Tree
     */
    TernaryTree& put(const std::string& key, const std::string& value, const std::string& value, const std::function<void(TernaryTree& self, const std::string& key, const std::string& value, int status)>& callback) {
        // calculate how many elements are needed to fit 
        size_t size_to_fit = ceill((key.length() + sizeof(InternalValueType))>>bit_shift) + 1;

        // allocate memory, clear and copy
        InternalValueType * data = (InternalValueType *)malloc(sizeof(InternalValueType) * size_to_fit);
        memset(data, 0, sizeof(InternalValueType) * size_to_fit);
        memcpy(data, key.c_str(), key.length());

        // insert
        this->tree = tstree_insert(this->tree, key.c_str(), value.c_str());

        // callback
        if (this->tree == NULL) {
            callback(*this, key, value, Failed);
        } else {
            callback(*this, key, value, OK);
        }
        return *this;
    }

    TernaryTree& get(const std::string& key, const std::function<void(TernaryTree& self, const std::string& key, void * userdata, int status)>& callback) {
        // calculate how many elements are needed to fit 
        size_t size_to_fit = ceill((key.length() + sizeof(InternalValueType))>>bit_shift) + 1;

        // allocate memory, clear and copy
        InternalValueType * data = (InternalValueType *)malloc(sizeof(InternalValueType) * size_to_fit);
        memset(data, 0, sizeof(InternalValueType) * size_to_fit);
        memcpy(data, key.c_str(), key.length());

        // search
        tstree result = tstree_search(this->tree, data);

        // callback
        if (result) {
            if (uncompressed.length()) {
                callback(*this, key, result->userdata, OK);
            } else {
                callback(*this, key, NULL, Failed);
            }
        } else {
            callback(*this, key, NULL, NotFound);
        }
        return *this;
    }
private:
    typedef struct tsnode {
        InternalValueType internal_value;
        struct tsnode * le, * eq, * gt;
        void * userdata;
    } tsnode, * tstree;
    unsigned char bit_shift;
    tstree tree = NULL;
    tstree tstree_insert(tstree tree, const char * original, InternalValueType * key, void * userdata) {
        // 判断传入的tree是否为NULL
        if (tree == NULL) {
            // 是的话，则malloc内存
            tree = (tstree)malloc(sizeof(tsnode));
            // 将这个结点储存的字符赋值为key的第一个字符
            tree->internal_value = *key;
            // 其余三个指针都为NULL
            tree->le = tree->eq = tree->gt = tree->userdata = NULL;
        }
        // 接下来比较大小
        // (即使传入的时候为NULL，我们也在上面的if中为它申请了内存，并赋了相应的值，这时自然是"相等"的状态)
        if (*key < tree->internal_value) {
            // 插入的字符小于当前结点储存的值，转向左子树继续插入
            tree->le = tstree_insert(tree->le, original, key, userdata);
        } else if (*key > tree->internal_value) {
            // 插入的字符大于当前结点储存的值，转向左子树继续插入
            tree->gt = tstree_insert(tree->gt, original, key, userdata);
        } else {
            // 插入的字符等于当前结点储存的值，判断情况
            if (*key != 0) {
                // 如果还没到达末尾，说明是有同样的前缀，向中间的子树插入下一个字符的值
                tree->eq = tstree_insert(tree->eq, original, ++key, userdata);
            } else {
                // 如果到达了末尾，那么就把key的地址赋值给当前结点的eq指针
                if (tree->eq == NULL) {
                    tree->eq = (tstree)strdup(original);
                }
                tree->userdata = userdata;
            }
        }
        return tree;
    }

    tstree tstree_search(const tstree tree, InternalValueType * key) {
        tstree root;
        root = tree;
        while (root) {
            if (*key < root->internal_value) {
                // 小于则转左树
                root = root->le;
            } else if (*key > root->internal_value) {
                // 大于则转右树
                root = root->gt;
            } else {
                // 等于的时候判断情况
                if (*key == 0) {
                    // 查询字符串已经递归走到末尾了
                    // 意味着找到了
                    return root;
                }
                key++;
                root = root->eq;
            }
        }
        return NULL;
    }
};