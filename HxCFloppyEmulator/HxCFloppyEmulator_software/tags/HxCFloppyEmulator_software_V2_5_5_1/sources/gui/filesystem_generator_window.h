// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef filesystem_generator_window_h
#define filesystem_generator_window_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
extern void filesystem_generator_window_bt_injectdir(Fl_Button*, void*);
extern void filesystem_generator_window_bt_close(Fl_Button*, void*);
#include <FL/Fl_Choice.H>
#include <FL/Fl_Tree.H>
extern void filesystem_generator_window_browser_fs(Fl_Tree*, void*);
extern void filesystem_generator_window_bt_delete(Fl_Button*, void*);
extern void filesystem_generator_window_bt_getfiles(Fl_Button*, void*);
#include <FL/Fl_Output.H>
extern void filesystem_generator_window_bt_saveexport(Fl_Button*, void*);
extern void filesystem_generator_window_bt_loadimage(Fl_Button*, void*);
#include <FL/Fl_Counter.H>
extern void filesystem_generator_window_sel_disk(Fl_Counter*, void*);

class filesystem_generator_window {
public:
  filesystem_generator_window();
  Fl_Double_Window *window;
  Fl_Button *bt_injectdir;
  Fl_Button *bt_cancel;
  Fl_Choice *choice_filesystype;
  Fl_Tree *fs_browser;
  Fl_Button *bt_delete;
  Fl_Button *bt_get;
  Fl_Output *txtout_freesize;
  Fl_Output *hlptxt;
  Fl_Button *bt_saveexport;
  Fl_Button *bt_loadimage;
  Fl_Counter *disk_selector;

  int FATAccessInProgress;
};
#endif
