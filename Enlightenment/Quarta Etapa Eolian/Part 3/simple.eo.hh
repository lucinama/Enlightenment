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

   /// @brief Gets properties X and Y
   ///
   /// @param x X value
   /// @param y Y value
   ///
   void xy_get(int* x, int* y) const
   {
      eo_do(_eo_ptr(), ::simple_xy_get(x, y));
   }

   /// @brief Sets properties X and Y
   ///
   /// @param x X value
   /// @param y Y value
   ///
   void xy_set(int x, int y) const
   {
      eo_do(_eo_ptr(), ::simple_xy_set(x, y));
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
void simple_xy_get_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self, int* x, int* y)
{
   static_cast<T*>(self->this_)->xy_get(x, y);
}

template <typename T>
void simple_xy_set_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self, int x, int y)
{
   static_cast<T*>(self->this_)->xy_set(x, y);
}

namespace efl { namespace eo { namespace detail {

template<>
struct operations< ::simple >
{
   template <typename T>
   struct type
   {
      virtual void xy_get(int* x, int* y)
      {
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , ::simple_xy_get(x, y));
      }

      virtual void xy_set(int x, int y)
      {
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , ::simple_xy_set(x, y));
      }

   };
};


template<>
struct operation_description_class_size< ::simple >
{
   static const int value = 2;
};

template <typename T>
int initialize_operation_description(efl::eo::detail::tag<::simple>
                                 , Eo_Op_Description* ops)
{
   (void)ops;
   ops[0].func = reinterpret_cast<void*>(& ::simple_xy_get_wrapper<T>);
   ops[0].api_func = reinterpret_cast<void*>(& ::simple_xy_get);
   ops[0].op = EO_OP_OVERRIDE;
   ops[0].op_type = EO_OP_TYPE_REGULAR;
   ops[0].doc = NULL;

   ops[1].func = reinterpret_cast<void*>(& ::simple_xy_set_wrapper<T>);
   ops[1].api_func = reinterpret_cast<void*>(& ::simple_xy_set);
   ops[1].op = EO_OP_OVERRIDE;
   ops[1].op_type = EO_OP_TYPE_REGULAR;
   ops[1].doc = NULL;

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

      void xy_get(int* x, int* y)
      {
         eo_do(static_cast<T*>(this)->_eo_ptr(), ::simple_xy_get(x, y));
      }

      void xy_set(int x, int y)
      {
         eo_do(static_cast<T*>(this)->_eo_ptr(), ::simple_xy_set(x, y));
      }

   };
};

inline Eo_Class const* get_eo_class(tag<::simple>)
{
   return (SIMPLE_CLASS);
}

} } }
#endif // EFL_GENERATED_SIMPLE_HH

