/*! @file
  @brief
  mruby/c String object

  <pre>
  Copyright (C) 2015-2018 Kyushu Institute of Technology.
  Copyright (C) 2015-2018 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.

  </pre>
*/

#ifndef MRBC_SRC_C_STRING_H_
#define MRBC_SRC_C_STRING_H_

//#include <stdint.h>
#include "string_mini.h"
#include "value.h"

//================================================================
/*!@brief
  Define String handle.
*/
typedef struct RString {
  MRBC_OBJECT_HEADER;

  uint16_t size;	//!< string length.
  uint8_t *data;	//!< pointer to allocated buffer.

} mrb_string;


struct VM;

mrb_value mrbc_string_new(const void *src, int len);
mrb_value mrbc_string_new_cstr(const char *src);
mrb_value mrbc_string_new_alloc(void *buf, int len);
void mrbc_string_delete(mrb_value *str);
void mrbc_string_clear_vm_id(mrb_value *str);
mrb_value mrbc_string_dup(mrb_value *s1);
mrb_value mrbc_string_add(mrb_value *s1, mrb_value *s2);
int mrbc_string_append(mrb_value *s1, mrb_value *s2);
int mrbc_string_index(mrb_value *src, mrb_value *pattern, int offset);
int mrbc_string_strip(mrb_value *src, int mode);
int mrbc_string_chomp(mrb_value *src);
void mrbc_init_class_string();

//C functions for static proc table
void c_string_add(mrb_mvm *vm, mrb_value v[], int argc);
void c_string_eql(mrb_mvm *vm, mrb_value v[], int argc);
void c_string_size(mrb_mvm *vm, mrb_value v[], int argc);


//================================================================
/*! compare
*/
static inline int mrbc_string_compare(const mrb_value *v1, const mrb_value *v2)
{
  int len = (v1->string->size < v2->string->size) ?
    v1->string->size : v2->string->size;

  int res = memcmp(v1->string->data, v2->string->data, len);
  if( res != 0 ) return res;

  return v1->string->size - v2->string->size;
}

//================================================================
/*! get size
*/
static inline int mrbc_string_size(const mrb_value *str)
{
  return str->string->size;
}

//================================================================
/*! get c-language string (char *)
*/
static inline char * mrbc_string_cstr(const mrb_value *v)
{
  return (char*)v->string->data;
}


#endif

