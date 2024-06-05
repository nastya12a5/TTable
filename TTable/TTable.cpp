
#include "TTable.h"
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<random>
#include<cstdlib>
#include<fstream>
#include"TScanTable.h"
#include"TSortTable.h"
#include"TArrayTable.h"
#include"THashTable.h"
#include "TArrayHash.h"
#include"TListHash.h"
#include "TTreeTable.h"
#include"TBalTreeTable.h"
using namespace std;
int main()
{
    
   TScanTable scan_table;
    TSortTable sort_table;
    TTreeTable tree_table;
    TBalTreeTable btree_table;
    TArrayHash ahash_table;
    TListHash lhash_table;
    
    
    int size = 14;
    for (int i = 0; i < size; ++i) {
        
        TRecord rec(i, i);
        
        sort_table.Insert(rec);
        tree_table.Insert(rec);
        btree_table.Insert(rec);
        ahash_table.Insert(rec);
        lhash_table.Insert(rec);
    }
    cout << tree_table << endl;
    sort_table.ClearEff();
    tree_table.ClearEff();
    btree_table.ClearEff();
    ahash_table.ClearEff();
    lhash_table.ClearEff();
    TRecord rec1(20,20);
    sort_table.Insert(rec1);
    tree_table.Insert(rec1);
    btree_table.Insert(rec1);
    ahash_table.Insert(rec1);
    lhash_table.Insert(rec1);
    cout << "Insert 20:" << endl;
    
    cout << "sort_table: " << sort_table.getEff() << endl;
    cout << "tree_table: " << tree_table.getEff() << endl;
    cout << "btree_table: " << btree_table.getEff() << endl;
    cout << "ahash_table: " << ahash_table.getEff() << endl;
    cout << "lhash_table: " << lhash_table.getEff() << endl;

    
    sort_table.ClearEff();
    tree_table.ClearEff();
    btree_table.ClearEff();
    ahash_table.ClearEff();
    lhash_table.ClearEff();
   
    sort_table.Find(7);
    tree_table.Find(7);
    btree_table.Find(7);
    ahash_table.Find(7);
    lhash_table.Find(7);
    cout << "Find 7: " << endl;
    
    cout << "sort_table: " << sort_table.getEff() << endl;
    cout << "tree_table: " << tree_table.getEff() << endl;
    cout << "btree_table: " << btree_table.getEff() << endl;
    cout << "ahash_table: " << ahash_table.getEff() << endl;
    cout << "lhash_table: " << lhash_table.getEff() << endl;

    
    sort_table.ClearEff();
    tree_table.ClearEff();
    btree_table.ClearEff();
    ahash_table.ClearEff();
    lhash_table.ClearEff();
    
        sort_table.Delete(4);
        tree_table.Delete(4);
        btree_table.Delete(4);
        ahash_table.Delete(4);
        lhash_table.Delete(4);
    
    cout << "Delete 4: " << endl;
    
    cout << "sort_table: " << sort_table.getEff() << endl;
    cout << "tree_table: " << tree_table.getEff() << endl;
    cout << "btree_table: " << btree_table.getEff() << endl;
    cout << "ahash_table: " << ahash_table.getEff() << endl;
    cout << "lhash_table: " << lhash_table.getEff() << endl;

    // Пример использования классов

  // Создание объектов таблиц
    
    TScanTable scanTable;
    TSortTable sortTable;
    TArrayHash arrayHash;
    TListHash listHash;
    TTreeTable treeTable;
    TBalTreeTable balTreeTable;

    // Вставка записей в таблицы
    int isize = 4;
    for (int i = 0; i < isize; ++i) {

        scanTable.Insert(TRecord(i, i));
        sortTable.Insert(TRecord(i, i));
        arrayHash.Insert(TRecord(i, i));
        listHash.Insert(TRecord(i, i));
        treeTable.Insert(TRecord(i, i));
        balTreeTable.Insert(TRecord(i, i));
    }
   
    cout << scanTable << endl;
    // Поиск записей в таблицах
    
    
   
    
    // Проверка эффективности операций для каждой таблицы
   
    scanTable.ClearEff();
    cout << "Efficiency for inserting in back TScanTable(5): ";
    scanTable.Insert(TRecord(5, 5)); // Вставка в конец
    cout << scanTable.getEff() << endl;
    sortTable.ClearEff();
    cout << "Efficiency for deleting in mid TSortTable(2): ";
    sortTable.Delete(2); // Удаление из середины
   cout<< sortTable.getEff()<<endl;
   arrayHash.ClearEff();
    cout << "Efficiency for find 3 in TArrayHash: ";
    arrayHash.Find(3);
    cout<<arrayHash.getEff()<<endl;
    listHash.ClearEff();
    cout << "Efficiency for inserting in TListHash(4): ";
    listHash.Insert(TRecord(4, 4)); // Вставка в конец
    cout<<listHash.getEff()<<endl;
    treeTable.ClearEff();
    cout << "Efficiency for deleting second_el in TTreeTable: ";
    treeTable.Delete(1); // Удаление из начала
    cout<<treeTable.getEff()<<endl;
    balTreeTable.ClearEff();
    cout << "Efficiency for find 2 in TBalTreeTable: ";
    balTreeTable.Find(2);
    cout<<balTreeTable.getEff()<<endl;

    // Вывод всех таблиц на экран
    

    cout << "TScanTable:" << endl;
   // scanTable.Print();
    cout << scanTable << endl;
    cout << "TSortTable:" << endl;
    //sortTable.Print();
    cout << sortTable << endl;
    //cout << "TArrayHash:" << endl;
   // arrayHash.Print();
   // cout << arrayHash << endl;
    cout << "TListHash:" << endl;
    //listHash.Print();
    cout << listHash << endl;
    cout << "TTreeTable:" << endl;
    treeTable.PrintTree(cout);
   // balTreeTable.PrintTree(cout);
    cout << "Check Tree:" << endl;
   treeTable.Insert(TRecord(21, 21));
    treeTable.Insert(TRecord(51, 51));
    treeTable.Insert(TRecord(25, 25));
    treeTable.Insert(TRecord(40, 40));
    treeTable.Insert(TRecord(22, 22));
    treeTable.Insert(TRecord(27, 27));
    treeTable.Insert(TRecord(24, 24));
    treeTable.Insert(TRecord(78, 78));
    treeTable.Insert(TRecord(65, 65));
    treeTable.Insert(TRecord(43, 43));
    treeTable.Insert(TRecord(29, 29));
    treeTable.Insert(TRecord(96, 96));
    cout << treeTable;
    treeTable.PrintTree(cout);
    treeTable.ClearEff();
    treeTable.Find(27);
    cout << "Eff find 27: " << treeTable.getEff() << endl;
    treeTable.ClearEff();
    int a;
    cout << "Insert el,cin key:" << endl;
    cin >> a;
    treeTable.Insert(TRecord(a, a));
    cout << "Eff insert: " << treeTable.getEff() << endl;
    treeTable.ClearEff();
  /* balTreeTable.Insert(TRecord(19, 19));
    balTreeTable.Insert(TRecord(49, 49));
    balTreeTable.Insert(TRecord(25, 25));
    balTreeTable.Insert(TRecord(40, 40));
    balTreeTable.Insert(TRecord(22, 22));
    balTreeTable.Insert(TRecord(27, 27));
    balTreeTable.Insert(TRecord(80, 80));
    balTreeTable.Insert(TRecord(76, 76));
    balTreeTable.Insert(TRecord(7, 7));
    balTreeTable.Insert(TRecord(65, 65));
    balTreeTable.Insert(TRecord(44, 44));
    balTreeTable.Insert(TRecord(28, 28));
    cout << "TBalTreeTable:" << endl;
    cout << balTreeTable << endl;
    balTreeTable.PrintTree(cout);*/
   
    
	TBalTreeTable baltree;

	TRecord rec4(4, 4);
	baltree.Insert(rec4);

	TRecord rec3(3, 3);
	baltree.Insert(rec3);

	TRecord rec2(2, 2);
	baltree.Insert(rec2);

	TRecord rec5(5, 5);
	baltree.Insert(rec5);

	TRecord rec6(6, 6);
	baltree.Insert(rec6);

	TRecord rec7(7, 7);
	baltree.Insert(rec7);
	baltree.Reset();

	TRecord rec8(1, 1);
	baltree.Insert(rec8);
	baltree.Reset();
    cout << baltree;
    cout << "if(tree.Find(7)==true) cout<<yes"<<endl;
        if (baltree.Find(7) == true) cout << "yes" << endl;
   
        cout << "tree.GetKey "<< baltree.GetKey()<< endl;
	
	
	
        cout << "Insert 15,Delete 15:" << endl;
	baltree.Insert(TRecord(15,15));
	baltree.Delete(15);
    baltree.PrintTree(cout);
    baltree.ClearEff();
    baltree.Find(6);
    cout << "eff for find 6 "<<baltree.getEff() << endl;
    baltree.ClearEff();
    TBalTreeTable c;
    for (int i = 0; i < 100; i++)
    {
        int a = rand() % 100;
        c.Insert(TRecord(i, i));
    }
    c.PrintTree(cout);
    c.ClearEff();
    c.Delete(0);
    cout << c.getEff() << endl;
    c.PrintTree_f();
    TArrayHash hash;
    for (int i = 0; i < 100; i++)
    {
       
        hash.Insert(TRecord(50*i+2, i));
    }
    
    hash.Delete(802);
    hash.ClearEff();
    hash.Find(2502);
    cout << hash.getEff() << endl;
    
}
