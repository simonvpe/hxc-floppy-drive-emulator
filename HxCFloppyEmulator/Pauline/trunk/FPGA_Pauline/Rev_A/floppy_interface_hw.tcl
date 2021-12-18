# TCL File Generated by Component Editor 19.1
# Sat Dec 18 08:49:00 CET 2021
# DO NOT MODIFY


# 
# floppy_interface "floppy_interface" v1.0
#  2021.12.18.08:49:00
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module floppy_interface
# 
set_module_property DESCRIPTION ""
set_module_property NAME floppy_interface
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME floppy_interface
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL floppy_interface
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file floppy_interface.vhd VHDL PATH ip/pauline_core/floppy_interface.vhd TOP_LEVEL_FILE
add_fileset_file floppy_signal_filter.vhd VHDL PATH ip/pauline_core/floppy_signal_filter.vhd
add_fileset_file floppy_drive.vhd VHDL PATH ip/pauline_core/floppy_drive.vhd
add_fileset_file trackcore.vhd VHDL PATH ip/pauline_core/trackcore.vhd
add_fileset_file floppy_index_generator.vhd VHDL PATH ip/pauline_core/floppy_index_generator.vhd
add_fileset_file floppy_status_signal.vhd VHDL PATH ip/pauline_core/floppy_status_signal.vhd
add_fileset_file floppy_tick_generator.vhd VHDL PATH ip/pauline_core/floppy_tick_generator.vhd
add_fileset_file floppy_sound.vhd VHDL PATH ip/pauline_core/floppy_sound.vhd
add_fileset_file floppy_select_mux.vhd VHDL PATH ip/pauline_core/floppy_select_mux.vhd
add_fileset_file floppy_qd_logic.vhd VHDL PATH ip/pauline_core/floppy_qd_logic.vhd
add_fileset_file floppy_ctrl_stepper.vhd VHDL PATH ip/pauline_core/floppy_ctrl_stepper.vhd
add_fileset_file floppy_dumper.vhd VHDL PATH ip/pauline_core/floppy_dumper.vhd
add_fileset_file floppy_lib_package.vhd VHDL PATH ip/pauline_core/floppy_lib_package.vhd
add_fileset_file floppy_dma_master.vhd VHDL PATH ip/pauline_core/floppy_dma_master.vhd
add_fileset_file floppy_trigger.vhd VHDL PATH ip/pauline_core/floppy_trigger.vhd
add_fileset_file gen_mux.vhd VHDL PATH ip/pauline_core/gen_mux.vhd
add_fileset_file noise_generator.vhd VHDL PATH ip/pauline_core/noise_generator.vhd
add_fileset_file floppy_fm_data_separator.vhd VHDL PATH ip/pauline_core/floppy_fm_data_separator.vhd


# 
# parameters
# 


# 
# display items
# 


# 
# connection point ci
# 
add_interface ci clock end
set_interface_property ci clockRate 0
set_interface_property ci ENABLED true
set_interface_property ci EXPORT_OF ""
set_interface_property ci PORT_NAME_MAP ""
set_interface_property ci CMSIS_SVD_VARIABLES ""
set_interface_property ci SVD_ADDRESS_GROUP ""

add_interface_port ci csi_ci_Clk clk Input 1


# 
# connection point ci_reset
# 
add_interface ci_reset reset end
set_interface_property ci_reset associatedClock ci
set_interface_property ci_reset synchronousEdges DEASSERT
set_interface_property ci_reset ENABLED true
set_interface_property ci_reset EXPORT_OF ""
set_interface_property ci_reset PORT_NAME_MAP ""
set_interface_property ci_reset CMSIS_SVD_VARIABLES ""
set_interface_property ci_reset SVD_ADDRESS_GROUP ""

add_interface_port ci_reset csi_ci_Reset_n reset_n Input 1


# 
# connection point s1
# 
add_interface s1 avalon end
set_interface_property s1 addressUnits WORDS
set_interface_property s1 associatedClock ci
set_interface_property s1 associatedReset ci_reset
set_interface_property s1 bitsPerSymbol 8
set_interface_property s1 burstOnBurstBoundariesOnly false
set_interface_property s1 burstcountUnits WORDS
set_interface_property s1 explicitAddressSpan 0
set_interface_property s1 holdTime 0
set_interface_property s1 linewrapBursts false
set_interface_property s1 maximumPendingReadTransactions 0
set_interface_property s1 maximumPendingWriteTransactions 0
set_interface_property s1 readLatency 0
set_interface_property s1 readWaitTime 1
set_interface_property s1 setupTime 0
set_interface_property s1 timingUnits Cycles
set_interface_property s1 writeWaitTime 0
set_interface_property s1 ENABLED true
set_interface_property s1 EXPORT_OF ""
set_interface_property s1 PORT_NAME_MAP ""
set_interface_property s1 CMSIS_SVD_VARIABLES ""
set_interface_property s1 SVD_ADDRESS_GROUP ""

add_interface_port s1 avs_s1_write write Input 1
add_interface_port s1 avs_s1_read read Input 1
add_interface_port s1 avs_s1_byteenable byteenable Input 4
add_interface_port s1 avs_s1_address address Input 7
add_interface_port s1 avs_s1_writedata writedata Input 32
add_interface_port s1 avs_s1_waitrequest waitrequest Output 1
add_interface_port s1 avs_s1_readdata readdata Output 32
set_interface_assignment s1 embeddedsw.configuration.isFlash 0
set_interface_assignment s1 embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment s1 embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment s1 embeddedsw.configuration.isPrintableDevice 0


# 
# connection point m1
# 
add_interface m1 avalon start
set_interface_property m1 addressUnits SYMBOLS
set_interface_property m1 associatedClock ci
set_interface_property m1 associatedReset ci_reset
set_interface_property m1 bitsPerSymbol 8
set_interface_property m1 burstOnBurstBoundariesOnly false
set_interface_property m1 burstcountUnits WORDS
set_interface_property m1 doStreamReads false
set_interface_property m1 doStreamWrites false
set_interface_property m1 holdTime 0
set_interface_property m1 linewrapBursts false
set_interface_property m1 maximumPendingReadTransactions 0
set_interface_property m1 maximumPendingWriteTransactions 0
set_interface_property m1 readLatency 0
set_interface_property m1 readWaitTime 1
set_interface_property m1 setupTime 0
set_interface_property m1 timingUnits Cycles
set_interface_property m1 writeWaitTime 0
set_interface_property m1 ENABLED true
set_interface_property m1 EXPORT_OF ""
set_interface_property m1 PORT_NAME_MAP ""
set_interface_property m1 CMSIS_SVD_VARIABLES ""
set_interface_property m1 SVD_ADDRESS_GROUP ""

add_interface_port m1 avm_m1_address address Output 32
add_interface_port m1 avm_m1_readdata readdata Input 32
add_interface_port m1 avm_m1_read read Output 1
add_interface_port m1 avm_m1_write write Output 1
add_interface_port m1 avm_m1_writedata writedata Output 32
add_interface_port m1 avm_m1_waitrequest waitrequest Input 1
add_interface_port m1 avm_m1_readdatavalid readdatavalid Input 1
add_interface_port m1 avm_m1_byteenable byteenable Output 4
add_interface_port m1 avm_m1_burstcount burstcount Output 8


# 
# connection point conduit_end
# 
add_interface conduit_end conduit end
set_interface_property conduit_end associatedClock ci
set_interface_property conduit_end associatedReset ""
set_interface_property conduit_end ENABLED true
set_interface_property conduit_end EXPORT_OF ""
set_interface_property conduit_end PORT_NAME_MAP ""
set_interface_property conduit_end CMSIS_SVD_VARIABLES ""
set_interface_property conduit_end SVD_ADDRESS_GROUP ""

add_interface_port conduit_end coe_c1_led1_out coe_c1_led1_out Output 4
add_interface_port conduit_end coe_c1_led2_out coe_c1_led2_out Output 4
add_interface_port conduit_end coe_c1_host_i_step coe_c1_host_i_step Input 1
add_interface_port conduit_end coe_c1_host_i_dir coe_c1_host_i_dir Input 1
add_interface_port conduit_end coe_c1_host_i_motor coe_c1_host_i_motor Input 1
add_interface_port conduit_end coe_c1_host_i_sel coe_c1_host_i_sel Input 4
add_interface_port conduit_end coe_c1_host_i_write_gate coe_c1_host_i_write_gate Input 1
add_interface_port conduit_end coe_c1_host_i_write_data coe_c1_host_i_write_data Input 1
add_interface_port conduit_end coe_c1_host_i_side1 coe_c1_host_i_side1 Input 1
add_interface_port conduit_end coe_c1_host_i_x68000_sel coe_c1_host_i_x68000_sel Input 4
add_interface_port conduit_end coe_c1_host_i_x68000_eject coe_c1_host_i_x68000_eject Input 1
add_interface_port conduit_end coe_c1_host_i_x68000_lock coe_c1_host_i_x68000_lock Input 1
add_interface_port conduit_end coe_c1_host_i_x68000_ledblink coe_c1_host_i_x68000_ledblink Input 1
add_interface_port conduit_end coe_c1_host_o_x68000_diskindrive coe_c1_host_o_x68000_diskindrive Output 1
add_interface_port conduit_end coe_c1_host_o_x68000_insertfault coe_c1_host_o_x68000_insertfault Output 1
add_interface_port conduit_end coe_c1_host_o_x68000_int coe_c1_host_o_x68000_int Output 1
add_interface_port conduit_end coe_c1_host_o_trk00 coe_c1_host_o_trk00 Output 1
add_interface_port conduit_end coe_c1_host_o_data coe_c1_host_o_data Output 1
add_interface_port conduit_end coe_c1_host_o_wpt coe_c1_host_o_wpt Output 1
add_interface_port conduit_end coe_c1_host_o_index coe_c1_host_o_index Output 1
add_interface_port conduit_end coe_c1_host_o_pin02 coe_c1_host_o_pin02 Output 1
add_interface_port conduit_end coe_c1_host_o_pin03 coe_c1_host_o_pin03 Output 1
add_interface_port conduit_end coe_c1_host_o_pin34 coe_c1_host_o_pin34 Output 1
add_interface_port conduit_end coe_c1_host_i_pin02 coe_c1_host_i_pin02 Input 1
add_interface_port conduit_end coe_c1_host_i_pin04 coe_c1_host_i_pin04 Input 1
add_interface_port conduit_end coe_c1_floppy_o_step coe_c1_floppy_o_step Output 1
add_interface_port conduit_end coe_c1_floppy_o_dir coe_c1_floppy_o_dir Output 1
add_interface_port conduit_end coe_c1_floppy_o_motor coe_c1_floppy_o_motor Output 1
add_interface_port conduit_end coe_c1_floppy_o_sel coe_c1_floppy_o_sel Output 4
add_interface_port conduit_end coe_c1_floppy_o_write_gate coe_c1_floppy_o_write_gate Output 1
add_interface_port conduit_end coe_c1_floppy_o_write_data coe_c1_floppy_o_write_data Output 1
add_interface_port conduit_end coe_c1_floppy_o_side1 coe_c1_floppy_o_side1 Output 1
add_interface_port conduit_end coe_c1_floppy_i_trk00 coe_c1_floppy_i_trk00 Input 1
add_interface_port conduit_end coe_c1_floppy_i_data coe_c1_floppy_i_data Input 1
add_interface_port conduit_end coe_c1_floppy_i_wpt coe_c1_floppy_i_wpt Input 1
add_interface_port conduit_end coe_c1_floppy_i_index coe_c1_floppy_i_index Input 1
add_interface_port conduit_end coe_c1_floppy_i_pin02 coe_c1_floppy_i_pin02 Input 1
add_interface_port conduit_end coe_c1_floppy_i_pin34 coe_c1_floppy_i_pin34 Input 1
add_interface_port conduit_end coe_c1_floppy_o_pin04 coe_c1_floppy_o_pin04 Output 1
add_interface_port conduit_end coe_c1_floppy_o_x68000_sel coe_c1_floppy_o_x68000_sel Output 4
add_interface_port conduit_end coe_c1_floppy_o_x68000_ledblink coe_c1_floppy_o_x68000_ledblink Output 1
add_interface_port conduit_end coe_c1_floppy_o_x68000_lock coe_c1_floppy_o_x68000_lock Output 1
add_interface_port conduit_end coe_c1_floppy_i_x68000_diskindrive coe_c1_floppy_i_x68000_diskindrive Input 1
add_interface_port conduit_end coe_c1_floppy_i_x68000_insertfault coe_c1_floppy_i_x68000_insertfault Input 1
add_interface_port conduit_end coe_c1_floppy_i_x68000_int coe_c1_floppy_i_x68000_int Input 1
add_interface_port conduit_end coe_c1_floppy_o_x68000_eject coe_c1_floppy_o_x68000_eject Output 1
add_interface_port conduit_end coe_c1_floppy_o_pin02 coe_c1_floppy_o_pin02 Output 1
add_interface_port conduit_end coe_c1_floppy_i_pin03 coe_c1_floppy_i_pin03 Input 1
add_interface_port conduit_end coe_c1_buzzer coe_c1_buzzer Output 1
add_interface_port conduit_end coe_c1_tris_io0_dout coe_c1_tris_io0_dout Output 1
add_interface_port conduit_end coe_c1_tris_io0_din coe_c1_tris_io0_din Input 1
add_interface_port conduit_end coe_c1_tris_io0_oe coe_c1_tris_io0_oe Output 1
add_interface_port conduit_end coe_c1_tris_io1_dout coe_c1_tris_io1_dout Output 1
add_interface_port conduit_end coe_c1_tris_io1_din coe_c1_tris_io1_din Input 1
add_interface_port conduit_end coe_c1_tris_io1_oe coe_c1_tris_io1_oe Output 1
add_interface_port conduit_end coe_c1_tris_io2_dout coe_c1_tris_io2_dout Output 1
add_interface_port conduit_end coe_c1_tris_io2_din coe_c1_tris_io2_din Input 1
add_interface_port conduit_end coe_c1_tris_io2_oe coe_c1_tris_io2_oe Output 1
add_interface_port conduit_end coe_c1_tris_io3_dout coe_c1_tris_io3_dout Output 1
add_interface_port conduit_end coe_c1_tris_io3_din coe_c1_tris_io3_din Input 1
add_interface_port conduit_end coe_c1_tris_io3_oe coe_c1_tris_io3_oe Output 1
add_interface_port conduit_end coe_c1_ext_io_dout coe_c1_ext_io_dout Output 1
add_interface_port conduit_end coe_c1_ext_io_din coe_c1_ext_io_din Input 1
add_interface_port conduit_end coe_c1_external_int coe_c1_external_int Input 1
add_interface_port conduit_end coe_c1_pushbutton0 coe_c1_pushbutton0 Input 1
add_interface_port conduit_end coe_c1_pushbutton1 coe_c1_pushbutton1 Input 1
add_interface_port conduit_end coe_c1_pushbutton2 coe_c1_pushbutton2 Input 1
add_interface_port conduit_end coe_c1_led1 coe_c1_led1 Output 1
add_interface_port conduit_end coe_c1_led2 coe_c1_led2 Output 1


# 
# connection point irq_s1
# 
add_interface irq_s1 interrupt end
set_interface_property irq_s1 associatedAddressablePoint s1
set_interface_property irq_s1 associatedClock ci
set_interface_property irq_s1 associatedReset ci_reset
set_interface_property irq_s1 bridgedReceiverOffset ""
set_interface_property irq_s1 bridgesToReceiver ""
set_interface_property irq_s1 ENABLED true
set_interface_property irq_s1 EXPORT_OF ""
set_interface_property irq_s1 PORT_NAME_MAP ""
set_interface_property irq_s1 CMSIS_SVD_VARIABLES ""
set_interface_property irq_s1 SVD_ADDRESS_GROUP ""

add_interface_port irq_s1 avs_s1_irq irq Output 1

