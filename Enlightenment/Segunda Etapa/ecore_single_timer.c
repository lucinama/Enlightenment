#include <Ecore.h>
#include <unistd.h>
#include <stdio.h>
#define TIMEOUT_1 2.0
#define TIMEOUT_2 6.0
#define DELAY_1 15.0
static double _initial_time = 0;
struct context
{
  Ecore_Timer *timer1;
  Ecore_Timer *timer2;
  double x;
};
static double
_get_current_time(void)
{
  x = ecore_time_get() - _initial_time;
  return x;
}
static Eina_Bool
_timer1_cb(void *data EINA_UNUSED)
{
  printf("Timer1 expired after %0.3f seconds.\n", _get_current_time());
  return ECORE_CALLBACK_RENEW;
}
static Eina_Bool
_timer2_cb(void *data)
{
  struct context *ctxt = data;
  printf("Timer2 expired after %0.3f seconds. "
	 "Adding delay of %0.3f seconds to timer1.\n",
	 _get_current_time(), DELAY_1);
  ecore_timer_delay(ctxt->timer1, DELAY_1);
  ctxt->timer2 = NULL;
  return ECORE_CALLBACK_CANCEL;
}
int
main(void)
{
  struct context ctxt = {0};
  if (!ecore_init())
    {
      printf("ERROR: Cannot init Ecore!\n");
      return -1;
    }
  _initial_time = ecore_time_get();
  ctxt.timer1 = ecore_timer_add(TIMEOUT_1, _timer1_cb, &ctxt);
  ctxt.timer2 = ecore_timer_add(TIMEOUT_2, _timer2_cb, &ctxt);
  printf("start the main loop.\n");
  do {
  ecore_main_loop_begin();
  if (ctxt.timer1)
    ecore_timer_del(ctxt.timer1);
  if (ctxt.timer2)
    ecore_timer_del(ctxt.timer2);
  {
    while (x < 30.0);
    ecore_shutdown();
    return 0;

}
