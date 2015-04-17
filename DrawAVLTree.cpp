#include <gtkmm.h>
#include "AVLTree.h"
#include "DrawPanel.h"
#include "CD.h"
using CSC2110::CD;
#include "Text.h"
using CSC2110::String;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   ListArrayIterator<CD>* iter = cds->iterator();
   AVLTree<CD>* avl = new AVLTree<CD>(&CD::compare_items, &CD::compare_keys);
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      avl->insert(cd);
   }
   delete iter;
   delete cds;

   Gtk::Main kit(argc, argv);

   Gtk::Window win;
   win.set_title("AVLTree!");
   win.set_position(Gtk::WIN_POS_CENTER);

   //the size of the window
   int width = 1000;
   int height = 500;

   win.set_size_request(width, height);
   win.set_resizable(false);  

   DrawPanel pnl(width, height, avl);  //needs to know its own dimensions

   win.add(pnl);

   win.show_all_children();
   Gtk::Main::run(win);

   return 0;
}
