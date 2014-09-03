#ifndef EFL_GENERATED_SIMPLE_HH
#define EFL_GENERATED_SIMPLE_HH

#include <Eo.h>
#include <Eo.hh>

extern "C"
{
#include "simple.eo.h"
}

#include "interface.eo.hh"
#include "mixin.eo.hh"

/// Simple Class
struct simple
      : efl::eo::base,
      efl::eo::detail::extension_inheritance<interface>::type<simple>,      efl::eo::detail::extension_inheritance<mixin>::type<simple>

{
   /// @brief Eo Constructor.
   ///
   /// Constructs the object from an Eo* pointer stealing its ownership.
   ///
   /// @param eo The Eo object pointer.
   ///
   explicit simple(Eo* eo)
      : efl::eo::base(eo)
   {}

   simple(efl::eo::parent_type _p = (efl::eo::parent = nullptr))
      : simple(_c0(_p))
   {}

   /// @brief Copy Constructor.
   ///
   simple(simple const& other)
      : efl::eo::base(eo_ref(other._eo_ptr()))
   {}

   ~simple() {}

   /// @brief Gets properties X
   ///
   /// @param x X value
   ///
   int x_get() const
   {
      int _tmp_ret;
      eo_do(_eo_ptr(), _tmp_ret = ::simple_x_get());
      return _tmp_ret;
   }

   /// @brief Sets properties X
   ///
   /// @param x X value
   ///
   void x_set(int x) const
   {
      eo_do(_eo_ptr(), ::simple_x_set(x));
   }

   /// @brief Gets properties Y
   ///
   /// @param y Y value
   ///
   int y_get() const
   {
      int _tmp_ret;
      eo_do(_eo_ptr(), _tmp_ret = ::simple_y_get());
      return _tmp_ret;
   }

   /// @brief Sets properties Y
   ///
   /// @param y Y value
   ///
   void y_set(int y) const
   {
      eo_do(_eo_ptr(), ::simple_y_set(y));
   }

   static Eo_Class const* _eo_class()
   {
      return(SIMPLE_CLASS);
   }

private:
   static Eo* _c0(efl::eo::parent_type _p)
   {
      return eo_add_custom(SIMPLE_CLASS, _p._eo_raw, eo_constructor());
   }

};
template <typename T>
int simple_x_get_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self)
{
   return static_cast<T*>(self->this_)->x_get();
}

template <typename T>
void simple_x_set_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self, int x)
{
   static_cast<T*>(self->this_)->x_set(x);
}

template <typename T>
int simple_y_get_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self)
{
   return static_cast<T*>(self->this_)->y_get();
}

template <typename T>
void simple_y_set_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self, int y)
{
   static_cast<T*>(self->this_)->y_set(y);
}

namespace efl { namespace eo { namespace detail {

template<>
struct operations< ::simple >
{
   template <typename T>
   struct type
   {
      virtual int x_get()
      {
         int _tmp_ret = {};
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , _tmp_ret = ::simple_x_get());
         return _tmp_ret;
      }

      virtual void x_set(int x)
      {
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , ::simple_x_set(x));
      }

      virtual int y_get()
      {
         int _tmp_ret = {};
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , _tmp_ret = ::simple_y_get());
         return _tmp_ret;
      }

      virtual void y_set(int y)
      {
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , ::simple_y_set(y));
      }

   };
};


template<>
struct operation_description_class_size< ::simple >
{
   static const int value = 4;
};

template <typename T>
int initialize_operation_description(efl::eo::detail::tag<::simple>
                                 , Eo_Op_Description* ops)
{
   (void)ops;
   ops[0].func = reinterpret_cast<void*>(& ::simple_x_get_wrapper<T>);
   ops[0].api_func = reinterpret_cast<void*>(& ::simple_x_get);
   ops[0].op = EO_OP_OVERRIDE;
   ops[0].op_type = EO_OP_TYPE_REGULAR;
   ops[0].doc = NULL;

   ops[1].func = reinterpret_cast<void*>(& ::simple_x_set_wrapper<T>);
   ops[1].api_func = reinterpret_cast<void*>(& ::simple_x_set);
   ops[1].op = EO_OP_OVERRIDE;
   ops[1].op_type = EO_OP_TYPE_REGULAR;
   ops[1].doc = NULL;

   ops[2].func = reinterpret_cast<void*>(& ::simple_y_get_wrapper<T>);
   ops[2].api_func = reinterpret_cast<void*>(& ::simple_y_get);
   ops[2].op = EO_OP_OVERRIDE;
   ops[2].op_type = EO_OP_TYPE_REGULAR;
   ops[2].doc = NULL;

   ops[3].func = reinterpret_cast<void*>(& ::simple_y_set_wrapper<T>);
   ops[3].api_func = reinterpret_cast<void*>(& ::simple_y_set);
   ops[3].op = EO_OP_OVERRIDE;
   ops[3].op_type = EO_OP_TYPE_REGULAR;
   ops[3].doc = NULL;

   return 0;
}
inline void
call_constructor(tag< ::simple >
               , Eo* eo, Eo_Class const* cls EINA_UNUSED,
               args_class<::simple, ::std::tuple<> > const& args)
{
   (void)args;
   eo_do_super(eo, cls, ::eo_constructor());
}

template<>
struct extension_inheritance< ::simple>
{
   template <typename T>
   struct type
   {
      operator ::simple() const
      {
         return ::simple(eo_ref(static_cast<T const*>(this)->_eo_ptr()));
      }

      int x_get()
      {
         int _tmp_ret = {};
         eo_do(static_cast<T*>(this)->_eo_ptr(), _tmp_ret = ::simple_x_get());
         return _tmp_ret;
      }

      void x_set(int x)
      {
         eo_do(static_cast<T*>(this)->_eo_ptr(), ::simple_x_set(x));
      }

      int y_get()
      {
         int _tmp_ret = {};
         eo_do(static_cast<T*>(this)->_eo_ptr(), _tmp_ret = ::simple_y_get());
         return _tmp_ret;
      }

      void y_set(int y)
      {
         eo_do(static_cast<T*>(this)->_eo_ptr(), ::simple_y_set(y));
      }

   };
};

inline Eo_Class const* get_eo_class(tag<::simple>)
{
   return (SIMPLE_CLASS);
}

} } }
#endif // EFL_GENERATED_SIMPLE_HH

