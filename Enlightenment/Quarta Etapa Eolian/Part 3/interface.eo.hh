#ifndef EFL_GENERATED_INTERFACE_HH
#define EFL_GENERATED_INTERFACE_HH

#include <Eo.h>
#include <Eo.hh>

extern "C"
{
#include "interface.eo.h"
}


/// Interface Class
struct interface
      : efl::eo::base
{
   /// @brief Eo Constructor.
   ///
   /// Constructs the object from an Eo* pointer stealing its ownership.
   ///
   /// @param eo The Eo object pointer.
   ///
   explicit interface(Eo* eo)
      : efl::eo::base(eo)
   {}

   /// @brief Copy Constructor.
   ///
   interface(interface const& other)
      : efl::eo::base(eo_ref(other._eo_ptr()))
   {}

   ~interface() {}

   /// @brief Gets property MXY = X*Y
   ///
   /// @param mxy MXY value
   ///
   int mxy_get() const
   {
      int _tmp_ret;
      eo_do(_eo_ptr(), _tmp_ret = ::interface_mxy_get());
      return _tmp_ret;
   }

   static Eo_Class const* _eo_class()
   {
      return(INTERFACE_CLASS);
   }

private:
};
template <typename T>
int interface_mxy_get_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self)
{
   return static_cast<T*>(self->this_)->mxy_get();
}

namespace efl { namespace eo { namespace detail {

template<>
struct operations< ::interface >
{
   template <typename T>
   struct type
   {
      virtual int mxy_get()
      {
         int _tmp_ret = {};
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , _tmp_ret = ::interface_mxy_get());
         return _tmp_ret;
      }

   };
};


template<>
struct operation_description_class_size< ::interface >
{
   static const int value = 1;
};

template <typename T>
int initialize_operation_description(efl::eo::detail::tag<::interface>
                                 , Eo_Op_Description* ops)
{
   (void)ops;
   ops[0].func = reinterpret_cast<void*>(& ::interface_mxy_get_wrapper<T>);
   ops[0].api_func = reinterpret_cast<void*>(& ::interface_mxy_get);
   ops[0].op = EO_OP_OVERRIDE;
   ops[0].op_type = EO_OP_TYPE_REGULAR;
   ops[0].doc = NULL;

   return 0;
}
template<>
struct extension_inheritance< ::interface>
{
   template <typename T>
   struct type
   {
      operator ::interface() const
      {
         return ::interface(eo_ref(static_cast<T const*>(this)->_eo_ptr()));
      }

      int mxy_get()
      {
         int _tmp_ret = {};
         eo_do(static_cast<T*>(this)->_eo_ptr(), _tmp_ret = ::interface_mxy_get());
         return _tmp_ret;
      }

   };
};

inline Eo_Class const* get_eo_class(tag<::interface>)
{
   return (INTERFACE_CLASS);
}

} } }
#endif // EFL_GENERATED_INTERFACE_HH

