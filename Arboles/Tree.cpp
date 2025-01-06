
struct tree {
    elem data;
    struct tree* left;
    struct tree* right;
};
typedef struct tree* tree;
bool is_ordtree(tree T);

/* height(T) returns the precomputed height of T in O(1) */
int height(tree T) {
    return T == NULL ? 0 : T->height;
}
/* A tree is an AVL tree if it is both ordered (as defined and implementation in the last lecture) and balanced.*/
bool is_avl(tree T) {
    return is_ordtree(T) && is_balanced(T);
}

bool is_balanced(tree T) {
    if (T == NULL) return true;
    int h = T->height;
    int hl = height(T->left);
    int hr = height(T->right);
    if (!(h == (hl > hr ? hl+1 : hr+1))) return false;
    if (hl > hr+1 || hr > hl+1) return false;
    return is_balanced(T->left) && is_balanced(T->right);
}


tree tree_insert(tree T, elem e)
//@requires is_avl(T);
//@ensures is_avl(\result);
{
    assert(e != NULL); /* cannot insert NULL element */
    if (T == NULL) {
        T = leaf(e); /* create new leaf with data e */
    } else {
    int r = compare(elem_key(e), elem_key(T->data));
        if (r < 0) {
            T->left = tree_insert(T->left, e);
            T = rebalance_left(T); /* also fixes height */
        } else if (r == 0) {
            T->data = e;
        } else { //@assert r > 0;
            T->right = tree_insert(T->right, e);
            T = rebalance_right(T); /* also fixes height */
        }
    }
    return T;
}

tree rebalance_right(tree T)
//@requires T != NULL;
//@requires is_avl(T->left) && is_avl(T->right);
/* also requires that T->right is result of insert into T */
//@ensures is_avl(\result);
{
    tree l = T->left;
    tree r = T->right;
    int hl = height(l);
    int hr = height(r);
    if (hr > hl+1) {
        //@assert hr == hl+2;
        if (height(r->right) > height(r->left)) {
        //@assert height(r->right) == hl+1;
        T = rotate_left(T);
        //@assert height(T) == hl+2;
        return T;
        } else {
            //@assert height(r->left) == hl+1;
            /* double rotate left */
            T->right = rotate_right(T->right);
            T = rotate_left(T);
            //@assert height(T) == hl+2;
            return T;
        }
    } else { //@assert !(hr > hl+1);
        fix_height(T);
        return T;
    }
}

tree rotate_right(tree T)
//@requires is_ordtree(T);
//@requires T != NULL && T->left != NULL;
//@ensures is_ordtree(\result);
//@ensures \result != NULL && \result->right != NULL;
{
    tree root = T->left;
    T->left = root->right;
    root->right = T;
    return root;
}