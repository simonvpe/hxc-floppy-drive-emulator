// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef floppy_infos_window_h
#define floppy_infos_window_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Slider.H>
extern void disk_infos_window_callback(Fl_Value_Slider*, void*);
#include <FL/Fl_Light_Button.H>
extern void disk_infos_window_callback(Fl_Light_Button*, void*);
#include <FL/Fl_Choice.H>
extern void disk_infos_window_callback(Fl_Choice*, void*);
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Slider.H>
extern void disk_infos_window_callback(Fl_Slider*, void*);
#include <FL/Fl_Button.H>
extern void disk_infos_window_bt_edit_callback(Fl_Button*, void*);
extern void floppy_infos_ok(Fl_Button*, void*);

class floppy_infos_window {
public:
  floppy_infos_window();
  Fl_Window *window;
  Fl_Value_Slider *track_number_slide;
  Fl_Value_Slider *side_number_slide;
  Fl_Choice *view_mode;
  Fl_Output *x_pos;
  Fl_Output *y_pos;
  Fl_Output *global_status;
  Fl_Text_Display *object_txt;
  Fl_Group *floppy_map_disp;
  Fl_Value_Slider *y_time;
  Fl_Value_Slider *x_offset;
  Fl_Slider *x_time;
  Fl_Button *bt_edit;
  Fl_Light_Button *iso_mfm_bt;
  Fl_Light_Button *iso_fm_bt;
  Fl_Light_Button *amiga_mfm_bt;
  Fl_Light_Button *membrain_bt;
  Fl_Light_Button *tycom_bt;
  Fl_Light_Button *eemu_bt;
  Fl_Light_Button *apple2_bt;
  Fl_Light_Button *arburg_bt;
  Fl_Light_Button *aed6200p_bt;
  Fl_Light_Button *northstar_bt;
  Fl_Light_Button *heathkit_bt;
  Fl_Light_Button *decrx02_bt;
  Fl_Text_Buffer* buf;
  Fl_Text_Display * txt_displ;
};
#endif
