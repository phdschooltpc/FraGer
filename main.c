#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <interpow/interpow.h>

#include "fann.h"
#include "thyroid_test.h"
#include "profiler.h"
/*Intermittent Tester*/
#include <tester.h>
#include <noise.h>

/* Debug variable. */
fann_type *calc_out;
//static char string[] = "Hello! Hello! Hello! Hello! Hello! Hello! Hello! Hello! \n";

//=============================================================================//

#pragma PERSISTENT(ann)
    struct fann ann; //= malloc(sizeof(struct fann));
#pragma PERSISTENT(iteration)
    uint16_t iteration = 0;
#pragma PERSISTENT(ended)
    uint8_t ended = 0;

//=============================================================================//

void task_init_fann(void);
void task_iterate(void);
void task_end_program(void);

//=============================================================================//

#pragma PERSISTENT(TASK_INIT_FANN)
NewTask(TASK_INIT_FANN, task_init_fann, 0) // with self-field

#pragma PERSISTENT(TASK_ITERATE)
NewTask(TASK_ITERATE, task_iterate, 0) // with self-field

#pragma PERSISTENT(TASK_END_PROGRAM)
NewTask(TASK_END_PROGRAM, task_end_program, 0) // with self-field

#pragma PERSISTENT(PerState)
InitialTask(TASK_INIT_FANN)

//=============================================================================//

//=============================================================================//

void task_init_fann() {

    P1OUT |= BIT0;

#ifdef PROFILE
    /* Start counting clock cycles. */
    profiler_start();
#endif // PROFILE

    /* Create network and read training data.*/
#pragma SET_DATA_SECTION(".fram_data")
        struct fann *tmp;
        tmp = fann_create_from_header();
        ann = *tmp;
#pragma SET_DATA_SECTION()

        uint32_t clk_cycles = 0;
    #ifdef PROFILE
        /* Stop counting clock cycles. */
        clk_cycles = profiler_stop();

        /* Print profiling. */
        printf("ANN initialisation:\n"
               "-> execution cycles = %lu\n"
               "-> execution time = %.3f ms\n\n",
               clk_cycles, (float) clk_cycles / 8000);
    #endif // PROFILE
        fann_reset_MSE(&ann);
        P1OUT &= ~BIT0;
        StartTask(TASK_ITERATE);
}

void task_iterate() {
    P1OUT |= BIT1;
#ifdef PROFILE
    /* Start counting clock cycles. */
    profiler_start();
    uint32_t clk_cycles = 0;
#endif // PROFILE
    int i;
    for (i = iteration; i < num_data; i++) {
        calc_out = fann_test(&ann, input[i], output[i]);
#ifdef DEBUG
        /* Print results and errors (very expensive operations). */
        printf("Test %u:\n"
               "  result = (%f, %f, %f)\n"
               "expected = (%f, %f, %f)\n"
               "   delta = (%f, %f, %f)\n\n",
               i + 1,
               calc_out[0], calc_out[1], calc_out[2],
               output[i][0], output[i][1], output[i][2],
               (float) fann_abs(calc_out[0] - output[i][0]),
               (float) fann_abs(calc_out[1] - output[i][1]),
               (float) fann_abs(calc_out[2] - output[i][2]));
#else
        /* Breakpoint here and check the difference between calc_out[k] and
         * output[i][k], with k = 0, 1, 2. */
        __no_operation();
#endif // DEBUG
    iteration = iteration+1;
    }

#ifdef PROFILE
    /* Stop counting clock cycles. */
    clk_cycles = profiler_stop();

    /* Print profiling. */
    printf("Run %u tests:\n"
           "-> execution cycles = %lu (%lu per test)\n"
           "-> execution time = %.3f ms (%.3f ms per test)\n\n",
           i,
           clk_cycles, clk_cycles / i,
           (float) clk_cycles / 8000, (float) clk_cycles / 8000 / i);
#endif // PROFILE
    P1OUT &= ~BIT1;
    StartTask(TASK_END_PROGRAM);
}

void task_end_program() {

    float error = fann_get_MSE(&ann);
    printf("MSE error on %d test data: %f\n\n", num_data, error);


        /*Report results*/
        /* You need to include that statement at the termination of your intermittent program*/
        //tester_send_data(0, string, 57);

        /* Turn on LED: Use for debugging */

        //P1OUT |= BIT0;
        // we finished
        P1OUT |=BIT0;
        if (error < 0.02)
            P1OUT |= BIT1;

        /* Clean-up. */
                fann_destroy(&ann);

                __no_operation();

        ended = 1;
}

/**
 * main.c
 */
int main(void)
{
    /* Stop watchdog timer. */
    WDTCTL = WDTPW | WDTHOLD;

    /* Prepare LED. */
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
                          // to activate previously configured port settings
    P1DIR |= BIT0;
    //P1OUT &= ~BIT0;
    P1DIR |= BIT1;
    P1OUT &= ~BIT0;
    P1OUT &= ~BIT1;

    /* Set master clock frequency to 8 MHz. */
//    CSCTL0 = CSKEY;
//    CSCTL1 &= ~DCOFSEL;
//    CSCTL1 |= DCOFSEL_6;
//    CSCTL3 &= ~(DIVS | DIVM);
//    CSCTL4 &= ~SMCLKOFF;

    /*Power load simulation*/
    /* You need to use these statements in the beginning your intermittent program*/
    //tester_autoreset(0, noise_3, 0);
    tester_notify_start();





    while(1) {
        if (ended)
            return 0;
        Resume();
    }

}
