// Code for trie data structure.
// Time Complexity - O(n) where n is the length of string s.

struct TrieNode
{
    unordered_map<int, TrieNode*> children;
    bool endOfWord;
};

TrieNode* createNode()
{
    TrieNode *node = new TrieNode;
    node->endOfWord = false;
    return node;
}

void insert(TrieNode *root, string s)
{
    TrieNode *cur = root;

    for (int i = 0; i < s.length(); ++i)
    {
        int index = s[i] - 'a';

        if (cur->children[index] == NULL)
            cur->children[index] = createNode();

        cur = cur->children[index];
    }

    cur->endOfWord = true;
}

bool search(TrieNode *root, string s)
{
    TrieNode *cur = root;

    for (int i = 0; i < s.length(); ++i)
    {
        int index = s[i] - 'a';

        if (cur->children[index] == NULL)
            return false;

        cur = cur->children[index];
    }

    return cur->endOfWord;
}

bool isEmpty(TrieNode *root)
{
    for (auto child : root->children)
    {
        if (child.second != NULL)
            return false;
    }

    return true;
}

TrieNode* remove(TrieNode* &root, string& s, int depth)
{
    if (root == NULL)
        return root;

    if (depth == s.length())
    {
        if (root->endOfWord == true)
            root->endOfWord = false;

        if (isEmpty(root))
        {
            delete root;
            root = NULL;
        }

        return root;
    }

    int index = s[depth] - 'a';

    root->children[index] = remove(root->children[index], s, depth + 1);

    if (isEmpty(root) && root->endOfWord == false)
    {
        delete root;
        root = NULL;
    }

    return root;
}
