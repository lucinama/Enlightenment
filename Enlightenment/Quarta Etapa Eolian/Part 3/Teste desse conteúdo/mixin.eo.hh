#ifndef EFL_GENERATED_MIXIN_HH
#define EFL_GENERATED_MIXIN_HH

#include <Eo.h>
#include <Eo.hh>

extern "C"
{
#include "mixin.eo.h"
}


/// Mixin Class
struct mixin
      : efl::eo::base
{
   /// @brief Eo Constructor.
   ///
   /// Constructs the object from an Eo* pointer stealing its ownership.
   ///
   /// @param eo The Eo object pointer.
   ///
   explicit mixin(Eo* eo)
      : efl::eo::base(eo)
   {}

   /// @brief Copy Constructor.
   ///
   mixin(mixin const& other)
      : efl::eo::base(eo_ref(other._eo_ptr()))
   {}

   ~mixin() {}

   /// @brief Gets property DXY = X/Y
   ///
   /// @param dxy DXY value
   ///
   int dxy_get() const
   {
      int _tmp_ret;
      eo_do(_eo_ptr(), _tmp_ret = ::mixin_dxy_get());
      return _tmp_ret;
   }

   static Eo_Class const* _eo_class()
   {
      return(MIXIN_CLASS);
   }

private:
};
template <typename T>
int mixin_dxy_get_wrapper(Eo* objid EINA_UNUSED, efl::eo::detail::Inherit_Private_Data* self)
{
   return static_cast<T*>(self->this_)->dxy_get();
}

namespace efl { namespace eo { namespace detail {

template<>
struct operations< ::mixin >
{
   template <typename T>
   struct type
   {
      virtual int dxy_get()
      {
         int _tmp_ret = {};
         eo_do_super(static_cast<T*>(this)->_eo_ptr()
            , static_cast<T*>(this)->_eo_class()
            , _tmp_ret = ::mixin_dxy_get());
         return _tmp_ret;
      }

   };
};


template<>
struct operation_description_class_size< ::mixin >
{
   static const int value = 1;
};

template <typename T>
int initialize_operation_description(efl::eo::detail::tag<::mixin>
                                 , Eo_Op_Description* ops)
{
   (void)ops;
   ops[0].func = reinterpret_cast<void*>(& ::mixin_dxy_get_wrapper<T>);
   ops[0].api_func = reinterpret_cast<void*>(& ::mixin_dxy_get);
   ops[0].op = EO_OP_OVERRIDE;
   ops[0].op_type = EO_OP_TYPE_REGULAR;
   ops[0].doc = NULL;

   return 0;
}
template<>
struct extension_inheritance< ::mixin>
{
   template <typename T>
   struct type
   {
      operator ::mixin() const
      {
         return ::mixin(eo_ref(static_cast<T const*>(this)->_eo_ptr()));
      }

      int dxy_get()
      {
         int _tmp_ret = {};
         eo_do(static_cast<T*>(this)->_eo_ptr(), _tmp_ret = ::mixin_dxy_get());
         return _tmp_ret;
      }

   };
};

inline Eo_Class const* get_eo_class(tag<::mixin>)
{
   return (MIXIN_CLASS);
}

} } }
#endif // EFL_GENERATED_MIXIN_HH

