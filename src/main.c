#include <stdint.h>
#include <app_error.h>
#include <app_timer.h>
#include <nrf_log_ctrl.h>
#include <nrf_pwr_mgmt.h>
#include <nrf_log_default_backends.h>

static void
power_management_init(void){
  ret_code_t err_code;
  err_code = nrf_pwr_mgmt_init();
  APP_ERROR_CHECK(err_code);
}

static void
clock_initialization(void){
  /* Start 16 MHz crystal oscillator */
  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_HFCLKSTART = 1;

  /* Wait for the external oscillator to start up */
  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) {
    // Do nothing.
  }

  /* Start low frequency crystal oscillator for app_timer(used by bsp)*/
  // NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal <<
  // CLOCK_LFCLKSRC_SRC_Pos);
  NRF_CLOCK->LFCLKSRC = (CLOCK_LFCLKSRC_SRC_Synth << CLOCK_LFCLKSRC_SRC_Pos);
  NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_LFCLKSTART = 1;

  while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0) {
    // Do nothing.
  }
}

static void
log_init(void){
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

int main(void){
  clock_initialization();
  ret_code_t err_code = app_timer_init();
  APP_ERROR_CHECK(err_code);
  power_management_init();
  log_init();
  return EXIT_FAILURE;
}
