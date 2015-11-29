#ifndef VSX_BITMAP_LOADER_JPG_H
#define VSX_BITMAP_LOADER_JPG_H

#include "vsx_bitmap_loader_base.h"
#include <bitmap/vsx_bitmap_transform.h>

class vsx_bitmap_loader_jpg
    : public vsx_bitmap_loader_base
{
  static void* worker(void *ptr)
  {
    vsx_texture_loader_thread_info* thread_info = ((vsx_texture_loader_thread_info*)ptr);

    CJPEGTest cj;
    vsx_string<> ret;
    cj.LoadJPEG( thread_info->filename, ret, thread_info->filesystem);

    thread_info->bitmap->filename = thread_info->filename;
    thread_info->bitmap->width = cj.GetResX();
    thread_info->bitmap->height = cj.GetResY();
    thread_info->bitmap->data[0] = cj.m_pBuf;
    thread_info->bitmap->channels = 3;

    if (thread_info->hint.flip_vertically)
      vsx_bitmap_transform::get_instance()->flip_vertically(thread_info->bitmap);

    if (thread_info->hint.split_cubemap)
      vsx_bitmap_transform::get_instance()->split_into_cubemap(thread_info->bitmap);

    __sync_fetch_and_add( &(thread_info->bitmap->data_ready), 1 );

//    vsx_bitmap_loader_png::get_instance()->thread_cleanup_queue.produce( (vsx_bitmap_loader_thread*)thread_info->thread );
    delete thread_info;

    return 0;
  }

  void load_internal(vsx_string<> filename, vsxf* filesystem, vsx_bitmap* bitmap, bool thread, vsx_texture_loader_thread_info* thread_info)
  {
    if (!thread)
      return (void)worker((void*)thread_info);

    new vsx_bitmap_loader_thread(worker, thread_info);
  }

public:

  static vsx_bitmap_loader_jpg* get_instance()
  {
    static vsx_bitmap_loader_jpg vtlj;
    return &vtlj;
  }

};

#endif