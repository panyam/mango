
#include <UnitTest++.h>
#include "mangopub.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

class BinTreeTestFixture
{

public:
    BinTreeTestFixture()
    {
    }

    virtual ~BinTreeTestFixture()
    {
    }
};

int int_compare(const void *a, const void *b)
{
    int ia = (int)a;
    int ib = (int)b;
    return ia - ib;
}

/**
 * Tests the creation of an array.
 */
TEST_FIXTURE(BinTreeTestFixture, TestBTCreate)
{
    MangoBinTree *bintree = mango_bintree_new();
    CHECK(bintree != NULL);
    CHECK(bintree->size == 0);
    CHECK(bintree->root == NULL);
    mango_bintree_free(bintree, NULL);
}

/**
 * Tests item insertion when empty.
 */
TEST_FIXTURE(BinTreeTestFixture, TestBTInsertWhenEmpty)
{
    MangoBinTree *bintree = mango_bintree_new();
    mango_bintree_insert(bintree, (void *)1, (CompareFunc)int_compare);
    CHECK(bintree->size == 1);
    CHECK(bintree->root != NULL);
    CHECK_EQUAL(bintree->root->data, (void *)1);
    mango_bintree_free(bintree, NULL);
}

/**
 * Tests item insertion when non empty.
 */
TEST_FIXTURE(BinTreeTestFixture, TestBTInsertWhenNonEmpty)
{
    MangoBinTree *bintree = mango_bintree_new();
    mango_bintree_insert(bintree, (void *)1, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)2, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)3, (CompareFunc)int_compare);
    CHECK(bintree->size == 3);
    CHECK(bintree->root != NULL);
    CHECK_EQUAL(bintree->root->data, (void *)1);
    CHECK_EQUAL(bintree->root->right->data, (void *)2);
    CHECK_EQUAL(bintree->root->right->right->data, (void *)3);
    mango_bintree_free(bintree, NULL);
}


/**
 * Tests item insertion in different order.
 */
TEST_FIXTURE(BinTreeTestFixture, TestBTInsertInBalancedOrder)
{
    MangoBinTree *bintree = mango_bintree_new();
    mango_bintree_insert(bintree, (void *)2, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)1, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)3, (CompareFunc)int_compare);
    CHECK(bintree->size == 3);
    CHECK(bintree->root != NULL);
    CHECK_EQUAL(bintree->root->data, (void *)2);
    CHECK_EQUAL(bintree->root->left->data, (void *)1);
    CHECK_EQUAL(bintree->root->right->data, (void *)3);
    mango_bintree_free(bintree, NULL);
}

/**
 * Tests finding of items
 */
TEST_FIXTURE(BinTreeTestFixture, TestBTFind)
{
    MangoBinTree *bintree = mango_bintree_new();
    mango_bintree_insert(bintree, (void *)2, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)1, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)3, (CompareFunc)int_compare);
    CHECK(bintree->size == 3);
    CHECK(bintree->root != NULL);
    MangoBinTreeNode *btn = mango_bintree_find(bintree, (void *)3, (CompareFunc)int_compare);
    CHECK_EQUAL(bintree->root->right, btn);
    CHECK_EQUAL(bintree->root->right->data, btn->data);
    mango_bintree_free(bintree, NULL);
}

/**
 * Tests tree clearning
 */
TEST_FIXTURE(BinTreeTestFixture, TestBTClearing)
{
    MangoBinTree *bintree = mango_bintree_new();
    mango_bintree_insert(bintree, (void *)2, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)1, (CompareFunc)int_compare);
    mango_bintree_insert(bintree, (void *)3, (CompareFunc)int_compare);
    CHECK(bintree->size == 3);
    mango_bintree_clear(bintree, NULL);
    CHECK(bintree->size == 0);
    CHECK(bintree->root == NULL);
}

