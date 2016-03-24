/**
* Project: VSXu: Realtime modular visual programming language, music/audio visualizer.
*
* This file is part of Vovoid VSXu.
*
* @author Jonatan Wallmander, Robert Wenzel, Vovoid Media Technologies AB Copyright (C) 2003-2013
* @see The GNU Public License (GPL)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef VSX_WIDGET_SEQUENCE_H
#define VSX_WIDGET_SEQUENCE_H

#include <vsx_widget.h>
#include "vsx_widget_sequence_clipboard.h"

class vsx_widget_sequence_editor : public vsx_widget
{
  vsx_widget *server;

  vsx_vector3<> parentpos;
  vsx_widget* but_rew;
  vsx_widget* but_play;
  vsx_widget* but_stop;
  vsx_widget* but_add_master_channel;
  vsx_widget* but_remove_master_channel;
  vsx_widget* but_set_loop_point;
  vsx_widget* but_set_speed;
  vsx_widget* but_open_at_time;
  vsx_widget* but_copy;
  vsx_widget* but_paste;


  std::vector<vsx_widget*> channels;
  std::map<vsx_string<>,vsx_widget*> channels_map;
  float channels_visible;
  int channels_start;
  vsx_widget* sequence_list;
  void update_list();

  vsx_widget_sequence_clipboard clipboard;

  // dialogs
  vsx_widget* name_dialog;
  vsx_widget* loop_point_dialog;
  vsx_widget* speed_dialog;


public:

  // timeline
  vsx_widget* timeline;

  bool disable_master_channel;

  void check_timeline();
  void set_timeline_show_wave_data(bool value);
  virtual void load_sequence_list();
  bool update_time_from_engine;
  int engine_status;
  float tstart;
  float tend;
  float curtime;

  virtual void init();
  void i_draw();
  void toggle_channel_visible(vsx_string<>name);
  void close_open_channels();
  void channels_open_at_time();

  void action_copy();
  void action_paste();



  // removes all sequence channels, used when switching seqpool etc.
  void clear_sequencer();
  virtual void command_process_back_queue(vsx_command_s *t);
  virtual bool event_key_down(signed long key);
  virtual void interpolate_size();
  void set_server(vsx_widget* new_server);
  vsx_widget* get_server();
  void remove_master_channel_items_with_name(vsx_string<>name);
  vsx_widget_sequence_editor() {
    disable_master_channel = false;
    but_add_master_channel = 0;
  }
};

#endif
