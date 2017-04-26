################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/inc" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/grlib" --include_path="C:/Users/WadeJensen/Dropbox/01_EN40/YEAR_4_SEM_1/EGH456/Repos/code_composer/synth_c1" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/examples/boards/dk-tm4c129x" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C129XNCZAD --define=TARGET_IS_TM4C129_RA0 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="startup_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

synth.obj: ../synth.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/inc" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/grlib" --include_path="C:/Users/WadeJensen/Dropbox/01_EN40/YEAR_4_SEM_1/EGH456/Repos/code_composer/synth_c1" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156/examples/boards/dk-tm4c129x" --include_path="H:/ti_workspace/TivaWare_C_Series-2.1.3.156" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C129XNCZAD --define=TARGET_IS_TM4C129_RA0 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="synth.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


