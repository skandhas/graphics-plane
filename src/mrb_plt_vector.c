#ifndef MRB_PLOTTER_VECTOR_H
#define MRB_PLOTTER_VECTOR_H
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <plotter.h>
#include "./kazmath/vec3.h"

static void
mrb_vector_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

static struct mrb_data_type mrb_vector2_type = { "Vector2", mrb_vector_free };
static struct mrb_data_type mrb_vector3_type = { "Vector3", mrb_vector_free };
static struct mrb_data_type mrb_vector4_type = { "Vector4", mrb_vector_free };

static mrb_value
mrb_vector_wrap(mrb_state *mrb, struct RClass *c, void *ptr, const mrb_data_type * type)
{
  return mrb_obj_value(Data_Wrap_Struct(mrb, c, type, ptr));
}

/* vector3 instance methods */
static mrb_value
mrb_vector3_initialize(mrb_state *mrb, mrb_value self)
{
  kmVec3 * vself;
  mrb_float x, y, z;

  vself = mrb_malloc(mrb, sizeof(kmVec3));
  mrb_get_args(mrb, "fff", &x, &y, &z);

  kmVec3Fill(vself, x, y, z);
  DATA_TYPE(self) = &mrb_vector3_type;
  DATA_PTR(self) = vself;
  return self;
}

static mrb_value
mrb_vector3_length(mrb_state *mrb, mrb_value self)
{
  kmVec3 * vself = DATA_PTR(self);
  kmVec3Length(vself);
  return self;
}

static mrb_value
mrb_vector3_length_square(mrb_state *mrb, mrb_value self)
{
  kmVec3 * vself = DATA_PTR(self);
  kmVec3LengthSq(vself);
  return self;
}

static mrb_value
mrb_vector3_normalize(mrb_state *mrb, mrb_value self)
{
  kmVec3 * vout = mrb_malloc(mrb, sizeof(kmVec3));
  kmVec3 * vself = DATA_PTR(self);
  kmVec3Normalize(vout, vself);
  return mrb_vector_wrap(mrb, mrb_obj_class(mrb, self), vout, &mrb_vector3_type);
}

static mrb_value
mrb_vector3_cross(mrb_state *mrb, mrb_value self)
{
  kmVec3 * v;
  kmVec3 * vout = mrb_malloc(mrb, sizeof(kmVec3));
  kmVec3 * vself = DATA_PTR(self);
  mrb_value o; 

  mrb_get_args(mrb, "o", &o);
  v = mrb_data_get_ptr(mrb, o, &mrb_vector3_type);
  if (!v) return mrb_nil_value();

  kmVec3Cross(vout, vself, v);
  return mrb_vector_wrap(mrb, mrb_obj_class(mrb, self), vout, &mrb_vector3_type);
}

static mrb_value
mrb_vector3_dot(mrb_state *mrb, mrb_value self)
{
  kmVec3 * v;
  kmScalar dot;
  kmVec3 * vself = DATA_PTR(self);
  mrb_value o; 

  mrb_get_args(mrb, "o", &o);
  v = mrb_data_get_ptr(mrb, o, &mrb_vector3_type);
  if (!v) return mrb_nil_value();

  dot = kmVec3Dot(vself, v);
  return mrb_float_value(mrb, dot);
}

static mrb_value
mrb_vector3_add(mrb_state *mrb, mrb_value self)
{
  kmVec3 * v;
  kmVec3 * vout = mrb_malloc(mrb, sizeof(kmVec3));
  kmVec3 * vself = DATA_PTR(self);
  mrb_value o; 

  mrb_get_args(mrb, "o", &o);
  v = mrb_data_get_ptr(mrb, o, &mrb_vector3_type);
  if (!v) return mrb_nil_value();

  kmVec3Add(vout, vself, v);
  return mrb_vector_wrap(mrb, mrb_obj_class(mrb, self), vout, &mrb_vector3_type);
}

static mrb_value
mrb_vector3_zero(mrb_state *mrb, mrb_value self)
{
  kmVec3 * vself = DATA_PTR(self);
  kmVec3Zero(vself);
  return self;
}

void
mrb_plt_vector_init(plt_state * plt)
{
  mrb_state * mrb = plt->mrb;
  struct RClass * plotter_mod = plt->plotter_module;
  struct RClass * object_class = mrb->object_class;
  struct RClass * v3c;
  
  v3c = plt->vector3_class = mrb_define_class_under(mrb, plotter_mod, "Vector3", object_class);
  MRB_SET_INSTANCE_TT(v3c, MRB_TT_DATA);

  mrb_define_method(mrb, v3c, "initialize",    mrb_vector3_initialize,    MRB_ARGS_REQ(3));
  mrb_define_method(mrb, v3c, "length",        mrb_vector3_length,        MRB_ARGS_NONE());
  mrb_define_method(mrb, v3c, "length_square", mrb_vector3_length_square, MRB_ARGS_NONE());
  mrb_define_method(mrb, v3c, "normalize",     mrb_vector3_normalize,     MRB_ARGS_NONE());
  mrb_define_method(mrb, v3c, "cross",         mrb_vector3_cross,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, v3c, "dot",           mrb_vector3_dot,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, v3c, "+",             mrb_vector3_add,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, v3c, "zero",          mrb_vector3_zero,          MRB_ARGS_NONE());
}

#endif

