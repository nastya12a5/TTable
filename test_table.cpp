#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "TTable/TTreeTable.h"
#include "TTable/TBalTreeTable.h"
#include "gtest.h"
#include "TTable/TListHash.h"
#include "TTable/TArrayHash.h"
#include "TTable/TScanTable.h"
#include "TTable/TSortTable.h"
TEST(TScanTable, can_create)
{
    ASSERT_NO_THROW(TScanTable tab(4));
}

TEST(TScanTable, can_use_is_full)
{
    TScanTable tab;
    EXPECT_EQ(0, tab.IsFull());
}

TEST(TScanTable, can_use_is_empty)
{
    TScanTable tab(4);
    EXPECT_EQ(1, tab.empty());
}

TEST(TScanTable, can_get_efficienty)
{
    TScanTable tab(6);
    EXPECT_EQ(0, tab.getEff());
}



TEST(TScanTable, can_insert)
{
    TScanTable tab(4);
    TRecord rec5(5, 5);
    ASSERT_NO_THROW(tab.Insert(rec5));
}

TEST(TScanTable, can_find)
{
    TScanTable a(4);
    TRecord rec5(5, 5);
    a.Insert(rec5);
    EXPECT_NE(NULL, a.Find(5));
}

TEST(TScanTable, can_delete)
{
    TScanTable a(6);
    TRecord rec5(5, 5);
    TRecord rec4(4, 4);
    a.Insert(rec5);
    a.Insert(rec4);
    a.Delete(5);
    EXPECT_EQ(4,a.GetKey());
}



TEST(TScanTable, can_get_key)
{
    TScanTable a(6);
    TRecord rec5(5, 5);
    a.Insert(rec5);
    EXPECT_EQ(5, a.GetKey());
}

TEST(TScanTable, can_get_tab_size)
{
    TScanTable a(8);
    EXPECT_EQ(8, a.GetTabSize());
}

TEST(TScanTable, cant_add_in_full_tab)
{
    TScanTable b(3);
    
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    TRecord rec3(3, 3);
    b.Insert(rec2);
    b.Insert(rec4);
    b.Insert(rec5);
    ASSERT_ANY_THROW(b.Insert(rec3));
}

TEST(TScanTable, can_reset)
{
    TScanTable a(5);
    
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    a.Insert(rec5);
    a.Insert(rec4);

    
    a.GoNext();
    a.Reset();
    EXPECT_EQ(5, a.GetKey());
}

TEST(TScanTable, can_check_if_tab_ended)
{
    TScanTable a(4);
    EXPECT_EQ(1, a.IsEnd());
}

TEST(TScanTable, can_go_next)
{
    TScanTable a(6);
    
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    

    a.Insert(rec4);
    a.Insert(rec5);
    a.Reset();
    a.GoNext();
    EXPECT_EQ(5, a.GetKey());
}

TEST(TSortTable, can_create)
{
    ASSERT_NO_THROW(TSortTable t(2));
}
TEST(TSortTable, cant_create_TSortTable_with_size_more_max_size)
{
    ASSERT_ANY_THROW(TSortTable table(1000000));


}

TEST(TSortTable, new_TSortTable_is_empty)
{
    TSortTable table(10);
   int a = table.getDataCount();
   EXPECT_TRUE(a == 0);

}

TEST(TSortTable, TSortTable_is_sorted)
{
    TSortTable table(10);
  
 
    for (int i = 9; i > 0; i--)
   {
        TRecord tmp(i, i);
       table.Insert(tmp);
    }
   TKey j = 1;
    for (table.Reset(); !table.IsEnd(); table.GoNext())
   {
        EXPECT_EQ(table.GetKey(), j);

        j++;
    }



}

TEST(TSortTable, can_insert_new_Record_in_empty_TSortTable)
{
    TSortTable table(10);
    
    TRecord a(1, 1);
    ASSERT_NO_THROW(table.Insert(a));
    table.Find(1);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
}
TEST(TSortTable, can_insert_in_first_pos)
{
  TSortTable table(10);
    
    TRecord a(2, 2);
    ASSERT_NO_THROW(table.Insert(a));
    table.Find(1);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
    TRecord b(1, 1);
    ASSERT_NO_THROW(table.Insert(b));
    table.Reset();
    EXPECT_TRUE(table.GetKey() == b.key);
    EXPECT_TRUE(table.GetValue() == b.val);

}

TEST(TSortTable, can_insert_in_last_empty_pos)
{
    TSortTable table(10);
    

    for (int i = 9; i > 0; i--)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }
    int count = table.getDataCount();
    EXPECT_TRUE(count == 9);
    TRecord a(10, 10);
    ASSERT_NO_THROW(table.Insert(a));
    table.Find(10);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
    EXPECT_TRUE( table.GetCurrentPos() == 9);


}

TEST(TSortTable, can_insert_new_Record_in_mid_pos_in_TSortTable)
{
    TSortTable table(10);
    

    for (int i = 10; i > 0; i-=2)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }
    int count = table.getDataCount();
    EXPECT_TRUE(count == 5);
    TRecord a(5, 5);
    ASSERT_NO_THROW(table.Insert(a));
    table.Find(5);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue ());
   EXPECT_TRUE(table.GetCurrentPos() == 2);
}


TEST(TSortTable, can_delete_first_Record)
{
    TSortTable table(10);
    
    TRecord a(1, 1);
    table.Insert(a);
    table.Find(1);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.key == table.GetKey());
    
    ASSERT_NO_THROW(table.Delete(1));
   
    EXPECT_TRUE(table.getDataCount() == 0);



}

TEST(TSortTable, cant_delete_Record_in_empty_TSortTable)
{
    TSortTable table(10);
    
    ASSERT_ANY_THROW( table.Delete(1));
   
    EXPECT_TRUE(table.getDataCount() == 0);



}
TEST(TSortTable, can_delete_last_Record)
{
    TSortTable table(10);
    
    for(int i = 10; i > 0; i--)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }
    int count = table.getDataCount();
    EXPECT_TRUE(count == 10);
    EXPECT_TRUE(table.IsFull());

     table.Delete(10);
    bool val = table.Find(10);
    EXPECT_TRUE(val == false);
    
    count = table.getDataCount();
    EXPECT_TRUE(count == 9);
    EXPECT_FALSE(table.IsFull());


}

TEST(TSortTable, can_delete_Record_in_mid_pos)
{
    TSortTable table(10);
    
 
    for (int i = 10; i > 0; i--)
    {
        TRecord tmp(i, i);

       table.Insert(tmp);
    }
    int count = table.getDataCount();
   EXPECT_TRUE(count == 10);

    EXPECT_TRUE(table.IsFull());

    table.Delete(4);
    bool v = table.Find(4);
    EXPECT_TRUE(v == false);
 

}

TEST(TSortTable, can_get_size_in_TSortTable)
{
    TSortTable table(10);
    int size = table.GetTabSize();

    EXPECT_TRUE(size == 10);

}


TEST(TSortTable, can_find_value)
{
    TSortTable b(2);
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    b.Insert(rec2);
    b.Insert(rec4);

    EXPECT_NE(NULL, b.Find(4));
}

TEST(TSortTable, cant_find_if_it_is_not_exist)
{
    TSortTable b(2);
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    b.Insert(rec2);
    b.Insert(rec4);

    EXPECT_EQ(NULL, b.Find(6));
}

TEST(TSortTable, can_insert)
{
    TSortTable b(2);
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    b.Insert(rec2);
    b.Insert(rec4);

    
    EXPECT_EQ(true, b.Find(4));
}

TEST(TSortTable, cant_insert_if_full)
{
    TSortTable b(2);
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    b.Insert(rec2);
    b.Insert(rec4);

    ASSERT_ANY_THROW(b.Insert(rec5));
}

TEST(TSortTable, can_delete)
{
    
    TSortTable b(2);
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    b.Insert(rec2);
    b.Insert(rec4);
    
    b.Delete(2);
    EXPECT_EQ(NULL, b.Find(2));
}

TEST(TTreeTable, can_create_object)
{
    ASSERT_NO_THROW(TTreeTable a);
}
TEST(TTreeTable, new_tree_table_is_empty)
{
    TTreeTable tree;
    EXPECT_EQ(true, tree.empty());
}


TEST(TTreeTable, can_insert_record)
{
    TTreeTable a;
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
   
    ASSERT_NO_THROW(a.Insert(rec4));
    EXPECT_EQ(a.Find(4), true);
}

TEST(TTreeTable, can_find_record)
{
    TTreeTable a;
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    a.Insert(rec2);
    a.Insert(rec4);
    EXPECT_EQ(a.Find(2),true);
}

TEST(TTreeTable, can_delete_record)
{
    TTreeTable a;
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    a.Insert(rec2);
    a.Insert(rec4);
    a.Insert(rec5);
    a.Delete(2);
    EXPECT_NE(NULL, a.Find(5));
    EXPECT_NE(NULL, a.Find(4));
    EXPECT_EQ(NULL, a.Find(2));
}

TEST(TTreeTable, can_reset)
{
    TTreeTable tree;

    TRecord rec4(4, 4);
    tree.Insert(rec4);

   

    ASSERT_NO_THROW(tree.Reset());
    
}

TEST(TTreeTable, can_go_next)
{
    TTreeTable a;
    TRecord rec2(2, 2);
    TRecord rec4(4, 4);
    TRecord rec5(5, 5);
    a.Insert(rec2);
    a.Insert(rec4);
    a.Insert(rec5);
    a.Delete(4);
    a.Reset();
    
    ASSERT_NO_THROW(a.GoNext());
    
}
TEST(TTreeTable, big_tree_test)
{
    TTreeTable a;
   
    for (int i = 0; i < 100; i++)
    {
        a.Insert(TRecord(i,i));
    }
    for (int i = 100; i > 80; i--)
    {
        a. Delete(i);
    }
    a.Insert(TRecord(101, 101));
    a.ClearEff();
    a.Find(101);
    EXPECT_EQ(a.getEff(), 82);
    a.Delete(0);
    a.ClearEff();
    a.Find(1);
    EXPECT_EQ(a.getEff(), 1);
    EXPECT_EQ(a.GetKey(), 1);
}
TEST(TBalTreeTable, can_insert)
{
    TBalTreeTable a;
    TRecord rec4(4, 4);
    ASSERT_NO_THROW(a.Insert(rec4));
}

TEST(TBalTreeTable, can_find)
{
    TBalTreeTable a;
    TRecord rec4(4, 4);
    a.Insert(rec4);
    EXPECT_NE(4, a.Find(4));
}

TEST(TBalTreeTable, can_delete)
{
    TBalTreeTable a;
    TRecord rec4(4, 4);
    a.Insert(rec4);
    a.Delete(4);
    EXPECT_EQ(false, a.Find(4));
}
TEST(TArrayHash, can_create_TArrayHash_table)
{
   ASSERT_NO_THROW(TArrayHash table(10,3));
}

TEST(TArrayHash, cant_create_TArrayHash_table_with_size_more_then_max_size)
{
    ASSERT_ANY_THROW(TArrayHash table(100000000,3));
}

TEST(TArrayHash, can_get_size_from_TArrayHash_table)
{
    TArrayHash table(10);
    int size = table.GetSize();
    EXPECT_TRUE(size == 10);
}

TEST(TArrayHash, can_get_current)
{
   TArrayHash table(10);
   
    
    for (int i = 0; i < 10; i++)
    {
        TRecord tmp(i,i);

        table.Insert(tmp);
    }

    table.Reset();
    table.GoNext();
    
    EXPECT_EQ(table.GetKey(),1);
    EXPECT_EQ(table.GetValue(), 1);
   
    
}

TEST(TArrayHash, new_TArrayHash_table_is_empty)
{
    TArrayHash table(10);
    EXPECT_EQ(true, table.empty());
}
TEST(TArrayHash, can_insert)
{
    TArrayHash a(7, 3);
    TRecord rec4(4, 4);
    ASSERT_NO_THROW(a.Insert(rec4));
}

TEST(TArrayHash, can_find)
{
    TArrayHash a(7, 3);
    TRecord rec4(4, 4);
    a.Insert(rec4);
    EXPECT_NE(3, a.Find(2));
}

TEST(TArrayHash, can_delete)
{
    TArrayHash a(7, 3);
    TRecord rec4(4, 4);
    a.Insert(rec4);
    a.Delete(4);
    EXPECT_EQ(NULL, a.Find(4));
}
TEST(TArrayHash, can_insert_in_last_empty_pos)
{
    TArrayHash table(10);
    
    for (int i = 0; i < 9; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    int count = table.getDataCount();
    EXPECT_TRUE(count == 9);
    TRecord a(10, 10);
   ASSERT_NO_THROW(table.Insert(a));
    table.Find(10);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
}

TEST(TArrayHash, can_insert_in_mid_pos)
{
    TArrayHash table(10);
    

    for (int i = 0; i < 5; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    int count = table.getDataCount();
    EXPECT_TRUE(count == 5);
    TRecord a(6, 6);
    ASSERT_NO_THROW(table.Insert(a));

    for (int i = 7; i < 10; i++)
   {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    table.Find(6);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
}

TEST(TArrayHash, can_insert_in_one_pos)
{
    TArrayHash table;

    table.Insert(TRecord(26, 26));
    table.Insert(TRecord(51, 21));
    table.Insert(TRecord(76, 31));
    table.Insert(TRecord(101, 41));
    table.Insert(TRecord(126, 31));
    table.Insert(TRecord(151, 41));
    
    table.Delete(76);
    EXPECT_EQ(table.Find(76), false);
    EXPECT_EQ(table.Find(151), true);
    table.ClearEff();
    
    table.Find(101);
   EXPECT_EQ(table.getEff(),3 );
   table.ClearEff();

   
}
TEST(TArrayHash, cant_insert_in_Full_TArrayHash_table)
{
    TArrayHash table(10);
    

    for (int i = 0; i < 10; i++)
   {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

   int count = table.getDataCount();
    EXPECT_TRUE(count == 10);
    EXPECT_TRUE(table.IsFull());

    TRecord a(10, 10);
    ASSERT_ANY_THROW(table.Insert(a));
}
TEST(TArrayHash, can_delete_first_Record)
{
    TArrayHash table(10);
    

    TRecord a(1, 1);
    table.Insert(a);
    table.Find(1);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
    ASSERT_NO_THROW(table.Delete(1));
    EXPECT_TRUE(table.getDataCount() == 0);
}

TEST(TArrayHash, cant_delete_Record_from_empty_table)
{
    TArrayHash table(10);
    ASSERT_ANY_THROW(table.Delete(1));
}


TEST(TArrayHash, can_delete_last_Record)
{
    TArrayHash table(10);
    

    for (int i = 0; i < 10; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    int count = table.getDataCount();
    EXPECT_TRUE(count == 10);
    EXPECT_TRUE(table.IsFull());

    table.Delete(9);
    bool val = table.Find(9);
    EXPECT_TRUE(val == false);
    
    count = table.getDataCount();
    EXPECT_TRUE(count == 9);
    EXPECT_FALSE(table.IsFull());
}

TEST(TArrayHash, can_delete_from_mid_pos)
{
    TArrayHash table(10);
    
    TRecord a(1, 1);
    for (int i = 0; i < 10; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    int count = table.getDataCount();
    EXPECT_TRUE(count == 10);

    table.Delete(4);
    bool val = table.Find(4);
    EXPECT_TRUE(val == false);
    EXPECT_TRUE(table.getDataCount() == 9);
}
TEST(TListHash, can_create_TListHash_table)
{
    ASSERT_NO_THROW(TListHash table(10));
}

TEST(TListHash, cant_create_table_with_size_more_then_max_size)
{
    ASSERT_ANY_THROW(TListHash table(100000000));
}

TEST(TListHash, can_get_size)
{
    TListHash table(10);
    int size = table.GetSize();
    EXPECT_TRUE(size == 10);
}

TEST(TListHash, new_TListHash_table_is_empty)
{
    TListHash table(10);
    EXPECT_EQ(true, table.empty());
}

TEST(TListHash, can_insert_in_one_pos)
{
    TListHash table;

    table.Insert(TRecord(26, 11));
    table.Insert(TRecord(51, 21));
    table.Insert(TRecord(76, 31));
    table.Insert(TRecord(101, 41));
    table.Delete(51);
    table.ClearEff();

   // table.Find(101);
    EXPECT_EQ(table.Find(101), true);
    EXPECT_EQ(table.getEff(), 1);
}

TEST(TListHash, can_insert_in_last_empty_pos)
{
    TListHash table(10);
    

    for (int i = 0; i < 9; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    int count = table.getDataCount();
    EXPECT_TRUE(count == 9);
    TRecord a(10, 10);
    ASSERT_NO_THROW(table.Insert(a));
    table.Find(10);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
}

TEST(TListHash, can_insert_in_mid_pos)
{
    TListHash table(10);

    for (int i = 0; i < 5; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    int count = table.getDataCount();
    EXPECT_TRUE(count == 5);
    TRecord a(6, 6);
   ASSERT_NO_THROW(table.Insert(a));

    for (int i = 7; i < 10; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    table.Find(6);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
}



TEST(TListHash, can_delete_first_Record)
{
    TListHash table(10);
   

    TRecord a(1, 1);
   table.Insert(a);
   table.Find(1);
    EXPECT_TRUE(a.key == table.GetKey());
    EXPECT_TRUE(a.val == table.GetValue());
    ASSERT_NO_THROW(table.Delete(1));
EXPECT_TRUE(table.getDataCount() == 0);
}

TEST(TListHash, cant_delete_Record_from_empty_table)
{
    TListHash table(10);
    ASSERT_ANY_THROW(table.Delete(1));
}

TEST(TListHash, return_throw_when_delete_another_Record)
{
    TListHash table(10);
    

    for (int i = 0; i < 9; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    
    ASSERT_ANY_THROW( table.Delete(11));
    
}

TEST(TListHash, can_delete_Record_from_mid_pos)
{
    TListHash table(10);
    
   TRecord a(1, 1);
    for (int i = 0; i < 10; i++)
    {
        TRecord tmp(i, i);
        table.Insert(tmp);
    }

    int count = table.getDataCount();
    EXPECT_TRUE(count == 10);

    table.Delete(4);
    bool val = table.Find(4);
    EXPECT_TRUE(val == false);
    EXPECT_TRUE(table.getDataCount() == 9);
}
TEST(TListHash, can_insert)
{
    TListHash a(5);
    TRecord rec4(4, 4);
    ASSERT_NO_THROW(a.Insert(rec4));
}

TEST(TListHash, can_find)
{
    TListHash a(5);
    TRecord rec4(4, 4);
    a.Insert(rec4);
    EXPECT_NE(NULL, a.Find(4));

}

TEST(TListHash, can_delete)
{
    TListHash a(5);
    TRecord rec4(4, 4);
    a.Insert(rec4);
    a.Delete(4);
    EXPECT_EQ(NULL, a.Find(4));
}