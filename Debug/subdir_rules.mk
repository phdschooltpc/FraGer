################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
libtester.obj: ../libtester.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/Applications/ti/ccsv7/ccs_base/msp430/include" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid/database" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid/fann/inc" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid/utils" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/include" --advice:power="all" --advice:hw_config=all --define=__MSP430FR5994__ --define=PROFILE --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="libtester.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/Applications/ti/ccsv7/ccs_base/msp430/include" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid/database" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid/fann/inc" --include_path="/Users/valentin/dev/tpcschool/msp430-thyroid/utils" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/include" --advice:power="all" --advice:hw_config=all --define=__MSP430FR5994__ --define=PROFILE --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


