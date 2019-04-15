

//#####################################################
//#WriteBy: ESMT
//#Product: AD82584F_GUI_v1.5
//#Date:2018/09/06
//#####################################################

//###################Register_Table {Register Address, Register Data}####################
const uint8_t m_reg_tab[][2]= {
                     {0x00, 0x04},//##State_Control_1
                     {0x01, 0x81},//##State_Control_2
                     {0x02, 0x00},//##State_Control_3
                     {0x03, 0x0F},//##Master_volume_control
                     {0x04, 0x00},//##Channel_1_volume_control
                     {0x05, 0x00},//##Channel_2_volume_control
                     {0x06, 0x18},//##Channel_3_volume_control
                     {0x07, 0x18},//##Channel_4_volume_control
                     {0x08, 0x18},//##Channel_5_volume_control
                     {0x09, 0x18},//##Channel_6_volume_control
                     {0x0a, 0x10},//##Bass_Tone_Boost_and_Cut
                     {0x0b, 0x10},//##treble_Tone_Boost_and_Cut
                     {0x0c, 0x98},//##State_Control_4
                     {0x0d, 0x00},//##Channel_1_configuration_registers
                     {0x0e, 0x00},//##Channel_2_configuration_registers
                     {0x0f, 0x00},//##Channel_3_configuration_registers
                     {0x10, 0x00},//##Channel_4_configuration_registers
                     {0x11, 0x00},//##Channel_5_configuration_registers
                     {0x12, 0x00},//##Channel_6_configuration_registers
                     {0x13, 0x00},//##Channel_7_configuration_registers
                     {0x14, 0x00},//##Channel_8_configuration_registers
                     {0x15, 0x69},//##DRC1_limiter_attack/release_rate
                     {0x16, 0x6a},//##DRC2_limiter_attack/release_rate
                     {0x17, 0x6a},//##DRC3_limiter_attack/release_rate
                     {0x18, 0x6a},//##DRC4_limiter_attack/release_rate
                     {0x19, 0x06},//##Error_Delay
                     {0x1a, 0x72},//##State_Control_5
                     {0x1b, 0x01},//##HVUV_selection
                     {0x1c, 0x00},//##State_Control_6
                     {0x1d, 0x7f},//##Coefficient_RAM_Base_Address
                     {0x1e, 0x00},//##Top_8-bits_of_coefficients_A1
                     {0x1f, 0x00},//##Middle_8-bits_of_coefficients_A1
                     {0x20, 0x00},//##Bottom_8-bits_of_coefficients_A1
                     {0x21, 0x00},//##Top_8-bits_of_coefficients_A2
                     {0x22, 0x00},//##Middle_8-bits_of_coefficients_A2
                     {0x23, 0x00},//##Bottom_8-bits_of_coefficients_A2
                     {0x24, 0x00},//##Top_8-bits_of_coefficients_B1
                     {0x25, 0x00},//##Middle_8-bits_of_coefficients_B1
                     {0x26, 0x00},//##Bottom_8-bits_of_coefficients_B1
                     {0x27, 0x00},//##Top_8-bits_of_coefficients_B2
                     {0x28, 0x00},//##Middle_8-bits_of_coefficients_B2
                     {0x29, 0x00},//##Bottom_8-bits_of_coefficients_B2
                     {0x2a, 0x20},//##Top_8-bits_of_coefficients_A0
                     {0x2b, 0x00},//##Middle_8-bits_of_coefficients_A0
                     {0x2c, 0x00},//##Bottom_8-bits_of_coefficients_A0
                     {0x2d, 0x40},//##Coefficient_R/W_control
                     {0x2e, 0x00},//##Protection_Enable/Disable
                     {0x2f, 0x00},//##Memory_BIST_status
                     {0x30, 0x00},//##Power_Stage_Status(Read_only)
                     {0x31, 0x00},//##PWM_Output_Control
                     {0x32, 0x00},//##Test_Mode_Control_Reg.
                     {0x33, 0x6d},//##Qua-Ternary/Ternary_Switch_Level
                     {0x34, 0x00},//##Volume_Fine_tune
                     {0x35, 0x00},//##Volume_Fine_tune
                     {0x36, 0x60},//##OC_bypass_&_GVDD_selection
                     {0x37, 0x52},//##Device_ID_register
                     {0x38, 0x00},//##RAM1_test_register_address
                     {0x39, 0x00},//##Top_8-bits_of_RAM1_Data
                     {0x3a, 0x00},//##Middle_8-bits_of_RAM1_Data
                     {0x3b, 0x00},//##Bottom_8-bits_of_RAM1_Data
                     {0x3c, 0x00},//##RAM1_test_r/w_control
                     {0x3d, 0x00},//##RAM2_test_register_address
                     {0x3e, 0x00},//##Top_8-bits_of_RAM2_Data
                     {0x3f, 0x00},//##Middle_8-bits_of_RAM2_Data
                     {0x40, 0x00},//##Bottom_8-bits_of_RAM2_Data
                     {0x41, 0x00},//##RAM2_test_r/w_control
                     {0x42, 0x00},//##Level_Meter_Clear
                     {0x43, 0x00},//##Power_Meter_Clear
                     {0x44, 0x7f},//##TOP_of_C1_Level_Meter
                     {0x45, 0xff},//##Middle_of_C1_Level_Meter
                     {0x46, 0xff},//##Bottom_of_C1_Level_Meter
                     {0x47, 0x7f},//##TOP_of_C2_Level_Meter
                     {0x48, 0xff},//##Middle_of_C2_Level_Meter
                     {0x49, 0xff},//##Bottom_of_C2_Level_Meter
                     {0x4a, 0x00},//##TOP_of_C3_Level_Meter
                     {0x4b, 0x00},//##Middle_of_C3_Level_Meter
                     {0x4c, 0x00},//##Bottom_of_C3_Level_Meter
                     {0x4d, 0x00},//##TOP_of_C4_Level_Meter
                     {0x4e, 0x00},//##Middle_of_C4_Level_Meter
                     {0x4f, 0x00},//##Bottom_of_C4_Level_Meter
                     {0x50, 0x00},//##TOP_of_C5_Level_Meter
                     {0x51, 0x00},//##Middle_of_C5_Level_Meter
                     {0x52, 0x00},//##Bottom_of_C5_Level_Meter
                     {0x53, 0x00},//##TOP_of_C6_Level_Meter
                     {0x54, 0x00},//##Middle_of_C6_Level_Meter
                     {0x55, 0x00},//##Bottom_of_C6_Level_Meter
                     {0x56, 0x00},//##TOP_of_C7_Level_Meter
                     {0x57, 0x00},//##Middle_of_C7_Level_Meter
                     {0x58, 0x00},//##Bottom_of_C7_Level_Meter
                     {0x59, 0x00},//##TOP_of_C8_Level_Meter
                     {0x5a, 0x00},//##Middle_of_C8_Level_Meter
                     {0x5b, 0x00},//##Bottom_of_C8_Level_Meter
                     {0x5c, 0x06},//##I2S_Data_Output_Selection_Register
                     {0x5d, 0x00},//##Reserve
                     {0x5e, 0x00},//##Reserve
                     {0x5f, 0x00},//##Reserve
                     {0x60, 0x00},//##Reserve
                     {0x61, 0x00},//##Reserve
                     {0x62, 0x00},//##Reserve
                     {0x63, 0x00},//##Reserve
                     {0x64, 0x00},//##Reserve
                     {0x65, 0x00},//##Reserve
                     {0x66, 0x00},//##Reserve
                     {0x67, 0x00},//##Reserve
                     {0x68, 0x00},//##Reserve
                     {0x69, 0x00},//##Reserve
                     {0x6a, 0x00},//##Reserve
                     {0x6b, 0x00},//##Reserve
                     {0x6c, 0x00},//##Reserve
                     {0x6d, 0x00},//##Reserve
                     {0x6e, 0x00},//##Reserve
                     {0x6f, 0x00},//##Reserve
                     {0x70, 0x00},//##Reserve
                     {0x71, 0x00},//##Reserve
                     {0x72, 0x00},//##Reserve
                     {0x73, 0x00},//##Reserve
                     {0x74, 0x30},//##Mono_Key_High_Byte
                     {0x75, 0x06},//##Mono_Key_Low_Byte
                     {0x76, 0x00},//##Boost_Control
                     {0x77, 0x07},//##Hi-res_Item
                     {0x78, 0x40},//##Test_Mode_register
                     {0x79, 0x62},//##Boost_Strap_OV/UV_Selection
                     {0x7a, 0x88},//##OC_Selection_2
                     {0x7b, 0x55},//##MBIST_User_Program_Top_Byte_Even
                     {0x7c, 0x55},//##MBIST_User_Program_Middle_Byte_Even
                     {0x7d, 0x55},//##MBIST_User_Program_Bottom_Byte_Even
                     {0x7e, 0x55},//##MBIST_User_Program_Top_Byte_Odd
                     {0x7f, 0x55},//##MBIST_User_Program_Middle_Byte_Odd
                     {0x80, 0x55},//##MBIST_User_Program_Bottom_Byte_Odd
                     {0x81, 0x00},//##ERROR_clear_register
                     {0x82, 0x0c},//##Minimum_duty_test
                     {0x83, 0x06},//##Reserve
                     {0x84, 0xfe},//##Reserve
                     {0x85, 0x4a},//##Reserve
                     };

//###################RAM1_Table {RAM1 Address, Top Byte Of RAM1 Data , Middle Byte Of RAM1 Data , Botton Byte Of RAM1 Data }####################
const uint8_t  m_ram1_tab[][4]= {
                     {0x00, 0xc0, 0x26, 0x41},//##Channel_1_EQ1_A1 
                     {0x01, 0x1f, 0xec, 0xdf},//##Channel_1_EQ1_A2 
                     {0x02, 0x3f, 0xd9, 0xb4},//##Channel_1_EQ1_B1 
                     {0x03, 0xe0, 0x26, 0x35},//##Channel_1_EQ1_B2 
                     {0x04, 0x1f, 0xec, 0xdf},//##Channel_1_EQ1_A0 
                     {0x05, 0xc0, 0x18, 0xfb},//##Channel_1_EQ2_A1 
                     {0x06, 0x1f, 0xdf, 0xf0},//##Channel_1_EQ2_A2 
                     {0x07, 0x3f, 0xe7, 0x05},//##Channel_1_EQ2_B1 
                     {0x08, 0xe0, 0x18, 0xcf},//##Channel_1_EQ2_B2 
                     {0x09, 0x20, 0x07, 0x41},//##Channel_1_EQ2_A0 
                     {0x0a, 0xc4, 0x22, 0x6d},//##Channel_1_EQ3_A1 
                     {0x0b, 0x1c, 0xf8, 0x1b},//##Channel_1_EQ3_A2 
                     {0x0c, 0x3b, 0xdd, 0x93},//##Channel_1_EQ3_B1 
                     {0x0d, 0xe3, 0xb7, 0x76},//##Channel_1_EQ3_B2 
                     {0x0e, 0x1f, 0x50, 0x6f},//##Channel_1_EQ3_A0 
                     {0x0f, 0xd1, 0x2f, 0x78},//##Channel_1_EQ4_A1 
                     {0x10, 0x15, 0x3c, 0x71},//##Channel_1_EQ4_A2 
                     {0x11, 0x2e, 0xd0, 0x88},//##Channel_1_EQ4_B1 
                     {0x12, 0xec, 0x9a, 0xc0},//##Channel_1_EQ4_B2 
                     {0x13, 0x1e, 0x28, 0xce},//##Channel_1_EQ4_A0 
                     {0x14, 0xd3, 0x4a, 0x01},//##Channel_1_EQ5_A1 
                     {0x15, 0x17, 0x5d, 0xd0},//##Channel_1_EQ5_A2 
                     {0x16, 0x2c, 0xb5, 0xff},//##Channel_1_EQ5_B1 
                     {0x17, 0xe7, 0xa4, 0xd9},//##Channel_1_EQ5_B2 
                     {0x18, 0x20, 0xfd, 0x56},//##Channel_1_EQ5_A0 
                     {0x19, 0xe1, 0x78, 0x5c},//##Channel_1_EQ6_A1 
                     {0x1a, 0x18, 0x45, 0x7e},//##Channel_1_EQ6_A2 
                     {0x1b, 0x1e, 0x87, 0xa4},//##Channel_1_EQ6_B1 
                     {0x1c, 0xe9, 0x0c, 0xd4},//##Channel_1_EQ6_B2 
                     {0x1d, 0x1e, 0xad, 0xae},//##Channel_1_EQ6_A0 
                     {0x1e, 0x00, 0x00, 0x00},//##Channel_1_EQ7_A1 
                     {0x1f, 0x00, 0x00, 0x00},//##Channel_1_EQ7_A2 
                     {0x20, 0x00, 0x00, 0x00},//##Channel_1_EQ7_B1 
                     {0x21, 0x00, 0x00, 0x00},//##Channel_1_EQ7_B2 
                     {0x22, 0x20, 0x00, 0x00},//##Channel_1_EQ7_A0 
                     {0x23, 0x00, 0x00, 0x00},//##Channel_1_EQ8_A1 
                     {0x24, 0x00, 0x00, 0x00},//##Channel_1_EQ8_A2 
                     {0x25, 0x00, 0x00, 0x00},//##Channel_1_EQ8_B1 
                     {0x26, 0x00, 0x00, 0x00},//##Channel_1_EQ8_B2 
                     {0x27, 0x20, 0x00, 0x00},//##Channel_1_EQ8_A0 
                     {0x28, 0x00, 0x00, 0x00},//##Channel_1_EQ9_A1 
                     {0x29, 0x00, 0x00, 0x00},//##Channel_1_EQ9_A2 
                     {0x2a, 0x00, 0x00, 0x00},//##Channel_1_EQ9_B1 
                     {0x2b, 0x00, 0x00, 0x00},//##Channel_1_EQ9_B2 
                     {0x2c, 0x20, 0x00, 0x00},//##Channel_1_EQ9_A0 
                     {0x2d, 0x00, 0x00, 0x00},//##Channel_1_EQ10_A1 
                     {0x2e, 0x00, 0x00, 0x00},//##Channel_1_EQ10_A2 
                     {0x2f, 0x00, 0x00, 0x00},//##Channel_1_EQ10_B1 
                     {0x30, 0x00, 0x00, 0x00},//##Channel_1_EQ10_B2 
                     {0x31, 0x20, 0x00, 0x00},//##Channel_1_EQ10_A0 
                     {0x32, 0x00, 0x00, 0x00},//##Channel_1_EQ11_A1 
                     {0x33, 0x00, 0x00, 0x00},//##Channel_1_EQ11_A2 
                     {0x34, 0x00, 0x00, 0x00},//##Channel_1_EQ11_B1 
                     {0x35, 0x00, 0x00, 0x00},//##Channel_1_EQ11_B2 
                     {0x36, 0x20, 0x00, 0x00},//##Channel_1_EQ11_A0 
                     {0x37, 0x00, 0x00, 0x00},//##Channel_1_EQ12_A1 
                     {0x38, 0x00, 0x00, 0x00},//##Channel_1_EQ12_A2 
                     {0x39, 0x00, 0x00, 0x00},//##Channel_1_EQ12_B1 
                     {0x3a, 0x00, 0x00, 0x00},//##Channel_1_EQ12_B2 
                     {0x3b, 0x20, 0x00, 0x00},//##Channel_1_EQ12_A0 
                     {0x3c, 0x00, 0x00, 0x00},//##Channel_1_EQ13_A1 
                     {0x3d, 0x00, 0x00, 0x00},//##Channel_1_EQ13_A2 
                     {0x3e, 0x00, 0x00, 0x00},//##Channel_1_EQ13_B1 
                     {0x3f, 0x00, 0x00, 0x00},//##Channel_1_EQ13_B2 
                     {0x40, 0x20, 0x00, 0x00},//##Channel_1_EQ13_A0 
                     {0x41, 0x00, 0x00, 0x00},//##Channel_1_EQ14_A1 
                     {0x42, 0x00, 0x00, 0x00},//##Channel_1_EQ14_A2 
                     {0x43, 0x00, 0x00, 0x00},//##Channel_1_EQ14_B1 
                     {0x44, 0x00, 0x00, 0x00},//##Channel_1_EQ14_B2 
                     {0x45, 0x20, 0x00, 0x00},//##Channel_1_EQ14_A0 
                     {0x46, 0x00, 0x00, 0x00},//##Channel_1_EQ15_A1 
                     {0x47, 0x00, 0x00, 0x00},//##Channel_1_EQ15_A2 
                     {0x48, 0x00, 0x00, 0x00},//##Channel_1_EQ15_B1 
                     {0x49, 0x00, 0x00, 0x00},//##Channel_1_EQ15_B2 
                     {0x4a, 0x20, 0x00, 0x00},//##Channel_1_EQ15_A0 
                     {0x4b, 0x40, 0x00, 0x00},//##Channel_1_Mixer1 
                     {0x4c, 0x40, 0x00, 0x00},//##Channel_1_Mixer2 
                     {0x4d, 0x74, 0x00, 0x00},//##Channel_1_Prescale 
                     {0x4e, 0x7f, 0xff, 0xff},//##Channel_1_Postscale 
                     {0x4f, 0xc7, 0xb6, 0x91},//##A0_of_L_channel_SRS_HPF 
                     {0x50, 0x38, 0x49, 0x6e},//##A1_of_L_channel_SRS_HPF 
                     {0x51, 0x0c, 0x46, 0xf8},//##B1_of_L_channel_SRS_HPF 
                     {0x52, 0x0e, 0x81, 0xb9},//##A0_of_L_channel_SRS_LPF 
                     {0x53, 0xf2, 0x2c, 0x12},//##A1_of_L_channel_SRS_LPF 
                     {0x54, 0x0f, 0xca, 0xbb},//##B1_of_L_channel_SRS_LPF 
                     {0x55, 0x20, 0x00, 0x00},//##CH1.2_Power_Clipping 
                     {0x56, 0x0c, 0x06, 0xdc},//##CCH1.2_DRC1_Attack_threshold 
                     {0x57, 0x0b, 0x5a, 0xa1},//##CH1.2_DRC1_Release_threshold 
                     {0x58, 0x20, 0x00, 0x00},//##CH3.4_DRC2_Attack_threshold 
                     {0x59, 0x08, 0x00, 0x00},//##CH3.4_DRC2_Release_threshold 
                     {0x5a, 0x20, 0x00, 0x00},//##CH5.6_DRC3_Attack_threshold 
                     {0x5b, 0x08, 0x00, 0x00},//##CH5.6_DRC3_Release_threshold 
                     {0x5c, 0x20, 0x00, 0x00},//##CH7.8_DRC4_Attack_threshold 
                     {0x5d, 0x08, 0x00, 0x00},//##CH7.8_DRC4_Release_threshold 
                     {0x5e, 0x00, 0x00, 0x1a},//##Noise_Gate_Attack_Level 
                     {0x5f, 0x00, 0x00, 0x53},//##Noise_Gate_Release_Level 
                     {0x60, 0x00, 0x80, 0x00},//##DRC1_Energy_Coefficient 
                     {0x61, 0x00, 0x20, 0x00},//##DRC2_Energy_Coefficient 
                     {0x62, 0x00, 0x80, 0x00},//##DRC3_Energy_Coefficient 
                     {0x63, 0x00, 0x80, 0x00},//##DRC4_Energy_Coefficient 
                     {0x64, 0x0b, 0x7e, 0x5e},//DRC1_Power_Meter
                     {0x65, 0x00, 0x00, 0x00},//DRC3_Power_Mete
                     {0x66, 0x00, 0x00, 0x00},//DRC5_Power_Meter
                     {0x67, 0x00, 0x00, 0x00},//DRC7_Power_Meter
                     {0x68, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_A1 
                     {0x69, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_A2
                     {0x6a, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_B1
                     {0x6b, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_B2 
                     {0x6c, 0x20, 0x00, 0x00},//##Channel_1_DEQ1_A0
                     {0x6d, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_A1 
                     {0x6e, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_A2 
                     {0x6f, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_B1 
                     {0x70, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_B2 
                     {0x71, 0x20, 0x00, 0x00},//##Channel_1_DEQ2_A0 
                     {0x72, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_A1 
                     {0x73, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_A2 
                     {0x74, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_B1 
                     {0x75, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_B2 
                     {0x76, 0x20, 0x00, 0x00},//##Channel_1_DEQ3_A0 
                     {0x77, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_A1 
                     {0x78, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_A2 
                     {0x79, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_B1 
                     {0x7a, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_B2 
                     {0x7b, 0x20, 0x00, 0x00},//##Channel_1_DEQ4_A0 
                     {0x7c, 0x00, 0x00, 0x00},//##Reserve
                     {0x7d, 0x00, 0x00, 0x00},//##Reserve
                     {0x7e, 0x00, 0x00, 0x00},//##Reserve
                     {0x7f, 0x00, 0x00, 0x00},//##Reserve
                     };

//###################RAM2_Table {RAM2 Address, Top Byte Of RAM2 Data , Middle Byte Of RAM2 Data , Botton Byte Of RAM2 Data }####################
const uint8_t m_ram2_tab[][4]= {
                     {0x00, 0x00, 0x00, 0x00},//##Channel_2_EQ1_A1 
                     {0x01, 0x00, 0x00, 0x00},//##Channel_2_EQ1_A2 
                     {0x02, 0x00, 0x00, 0x00},//##Channel_2_EQ1_B1 
                     {0x03, 0x00, 0x00, 0x00},//##Channel_2_EQ1_B2 
                     {0x04, 0x20, 0x00, 0x00},//##Channel_2_EQ1_A0 
                     {0x05, 0x00, 0x00, 0x00},//##Channel_2_EQ2_A1 
                     {0x06, 0x00, 0x00, 0x00},//##Channel_2_EQ2_A2 
                     {0x07, 0x00, 0x00, 0x00},//##Channel_2_EQ2_B1 
                     {0x08, 0x00, 0x00, 0x00},//##Channel_2_EQ2_B2 
                     {0x09, 0x20, 0x00, 0x00},//##Channel_2_EQ2_A0 
                     {0x0a, 0x00, 0x00, 0x00},//##Channel_2_EQ3_A1 
                     {0x0b, 0x00, 0x00, 0x00},//##Channel_2_EQ3_A2 
                     {0x0c, 0x00, 0x00, 0x00},//##Channel_2_EQ3_B1 
                     {0x0d, 0x00, 0x00, 0x00},//##Channel_2_EQ3_B2 
                     {0x0e, 0x20, 0x00, 0x00},//##Channel_2_EQ3_A0 
                     {0x0f, 0x00, 0x00, 0x00},//##Channel_2_EQ4_A1 
                     {0x10, 0x00, 0x00, 0x00},//##Channel_2_EQ4_A2 
                     {0x11, 0x00, 0x00, 0x00},//##Channel_2_EQ4_B1 
                     {0x12, 0x00, 0x00, 0x00},//##Channel_2_EQ4_B2 
                     {0x13, 0x20, 0x00, 0x00},//##Channel_2_EQ4_A0 
                     {0x14, 0x00, 0x00, 0x00},//##Channel_2_EQ5_A1 
                     {0x15, 0x00, 0x00, 0x00},//##Channel_2_EQ5_A2 
                     {0x16, 0x00, 0x00, 0x00},//##Channel_2_EQ5_B1 
                     {0x17, 0x00, 0x00, 0x00},//##Channel_2_EQ5_B2 
                     {0x18, 0x20, 0x00, 0x00},//##Channel_2_EQ5_A0 
                     {0x19, 0x00, 0x00, 0x00},//##Channel_2_EQ6_A1 
                     {0x1a, 0x00, 0x00, 0x00},//##Channel_2_EQ6_A2 
                     {0x1b, 0x00, 0x00, 0x00},//##Channel_2_EQ6_B1 
                     {0x1c, 0x00, 0x00, 0x00},//##Channel_2_EQ6_B2 
                     {0x1d, 0x20, 0x00, 0x00},//##Channel_2_EQ6_A0 
                     {0x1e, 0x00, 0x00, 0x00},//##Channel_2_EQ7_A1 
                     {0x1f, 0x00, 0x00, 0x00},//##Channel_2_EQ7_A2 
                     {0x20, 0x00, 0x00, 0x00},//##Channel_2_EQ7_B1 
                     {0x21, 0x00, 0x00, 0x00},//##Channel_2_EQ7_B2 
                     {0x22, 0x20, 0x00, 0x00},//##Channel_2_EQ7_A0 
                     {0x23, 0x00, 0x00, 0x00},//##Channel_2_EQ8_A1 
                     {0x24, 0x00, 0x00, 0x00},//##Channel_2_EQ8_A2 
                     {0x25, 0x00, 0x00, 0x00},//##Channel_2_EQ8_B1 
                     {0x26, 0x00, 0x00, 0x00},//##Channel_2_EQ8_B2 
                     {0x27, 0x20, 0x00, 0x00},//##Channel_2_EQ8_A0 
                     {0x28, 0x00, 0x00, 0x00},//##Channel_2_EQ9_A1 
                     {0x29, 0x00, 0x00, 0x00},//##Channel_2_EQ9_A2 
                     {0x2a, 0x00, 0x00, 0x00},//##Channel_2_EQ9_B1 
                     {0x2b, 0x00, 0x00, 0x00},//##Channel_2_EQ9_B2 
                     {0x2c, 0x20, 0x00, 0x00},//##Channel_2_EQ9_A0 
                     {0x2d, 0x00, 0x00, 0x00},//##Channel_2_EQ10_A1 
                     {0x2e, 0x00, 0x00, 0x00},//##Channel_2_EQ10_A2 
                     {0x2f, 0x00, 0x00, 0x00},//##Channel_2_EQ10_B1 
                     {0x30, 0x00, 0x00, 0x00},//##Channel_2_EQ10_B2 
                     {0x31, 0x20, 0x00, 0x00},//##Channel_2_EQ10_A0 
                     {0x32, 0x00, 0x00, 0x00},//##Channel_2_EQ11_A1 
                     {0x33, 0x00, 0x00, 0x00},//##Channel_2_EQ11_A2 
                     {0x34, 0x00, 0x00, 0x00},//##Channel_2_EQ11_B1 
                     {0x35, 0x00, 0x00, 0x00},//##Channel_2_EQ11_B2 
                     {0x36, 0x20, 0x00, 0x00},//##Channel_2_EQ11_A0 
                     {0x37, 0x00, 0x00, 0x00},//##Channel_2_EQ12_A1 
                     {0x38, 0x00, 0x00, 0x00},//##Channel_2_EQ12_A2 
                     {0x39, 0x00, 0x00, 0x00},//##Channel_2_EQ12_B1 
                     {0x3a, 0x00, 0x00, 0x00},//##Channel_2_EQ12_B2 
                     {0x3b, 0x20, 0x00, 0x00},//##Channel_2_EQ12_A0 
                     {0x3c, 0x00, 0x00, 0x00},//##Channel_2_EQ13_A1 
                     {0x3d, 0x00, 0x00, 0x00},//##Channel_2_EQ13_A2 
                     {0x3e, 0x00, 0x00, 0x00},//##Channel_2_EQ13_B1 
                     {0x3f, 0x00, 0x00, 0x00},//##Channel_2_EQ13_B2 
                     {0x40, 0x20, 0x00, 0x00},//##Channel_2_EQ13_A0 
                     {0x41, 0x00, 0x00, 0x00},//##Channel_2_EQ14_A1 
                     {0x42, 0x00, 0x00, 0x00},//##Channel_2_EQ14_A2 
                     {0x43, 0x00, 0x00, 0x00},//##Channel_2_EQ14_B1 
                     {0x44, 0x00, 0x00, 0x00},//##Channel_2_EQ14_B2 
                     {0x45, 0x20, 0x00, 0x00},//##Channel_2_EQ14_A0 
                     {0x46, 0x00, 0x00, 0x00},//##Channel_2_EQ15_A1 
                     {0x47, 0x00, 0x00, 0x00},//##Channel_2_EQ15_A2 
                     {0x48, 0x00, 0x00, 0x00},//##Channel_2_EQ15_B1 
                     {0x49, 0x00, 0x00, 0x00},//##Channel_2_EQ15_B2 
                     {0x4a, 0x20, 0x00, 0x00},//##Channel_2_EQ15_A0 
                     {0x4b, 0x00, 0x00, 0x00},//##Channel_2_Mixer1 
                     {0x4c, 0x7f, 0xff, 0xff},//##Channel_2_Mixer2 
                     {0x4d, 0x74, 0x00, 0x00},//##Channel_2_Prescale 
                     {0x4e, 0x7f, 0xff, 0xff},//##Channel_2_Postscale 
                     {0x4f, 0xc7, 0xb6, 0x91},//##A0_of_R_channel_SRS_HPF 
                     {0x50, 0x38, 0x49, 0x6e},//##A1_of_R_channel_SRS_HPF 
                     {0x51, 0x0c, 0x46, 0xf8},//##B1_of_R_channel_SRS_HPF 
                     {0x52, 0x0e, 0x81, 0xb9},//##A0_of_R_channel_SRS_LPF 
                     {0x53, 0xf2, 0x2c, 0x12},//##A1_of_R_channel_SRS_LPF 
                     {0x54, 0x0f, 0xca, 0xbb},//##B1_of_R_channel_SRS_LPF 
                     {0x55, 0x00, 0x00, 0x00},//##Reserve
                     {0x56, 0x00, 0x00, 0x00},//##Reserve
                     {0x57, 0x00, 0x00, 0x00},//##Reserve
                     {0x58, 0x00, 0x00, 0x00},//##Reserve
                     {0x59, 0x00, 0x00, 0x00},//##Reserve
                     {0x5a, 0x00, 0x00, 0x00},//##Reserve
                     {0x5b, 0x00, 0x00, 0x00},//##Reserve
                     {0x5c, 0x00, 0x00, 0x00},//##Reserve
                     {0x5d, 0x00, 0x00, 0x00},//##Reserve
                     {0x5e, 0x00, 0x00, 0x00},//##Reserve
                     {0x5f, 0x00, 0x00, 0x00},//##Reserve
                     {0x60, 0x00, 0x00, 0x00},//##Reserve
                     {0x61, 0x00, 0x00, 0x00},//##Reserve
                     {0x62, 0x00, 0x00, 0x00},//##Reserve
                     {0x63, 0x00, 0x00, 0x00},//##Reserve
                     {0x64, 0x0b, 0x8d, 0xe2},//DRC2_Power_Meter
                     {0x65, 0x00, 0x00, 0x00},//DRC4_Power_Mete
                     {0x66, 0x00, 0x00, 0x00},//DRC6_Power_Meter
                     {0x67, 0x00, 0x00, 0x00},//DRC8_Power_Meter
                     {0x68, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_A1 
                     {0x69, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_A2
                     {0x6a, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_B1
                     {0x6b, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_B2 
                     {0x6c, 0x20, 0x00, 0x00},//##Channel_2_DEQ1_A0
                     {0x6d, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_A1 
                     {0x6e, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_A2 
                     {0x6f, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_B1 
                     {0x70, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_B2 
                     {0x71, 0x20, 0x00, 0x00},//##Channel_2_DEQ2_A0 
                     {0x72, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_A1 
                     {0x73, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_A2 
                     {0x74, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_B1 
                     {0x75, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_B2 
                     {0x76, 0x20, 0x00, 0x00},//##Channel_2_DEQ3_A0 
                     {0x77, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_A1 
                     {0x78, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_A2 
                     {0x79, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_B1 
                     {0x7a, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_B2 
                     {0x7b, 0x20, 0x00, 0x00},//##Channel_2_DEQ4_A0 
                     {0x7c, 0x00, 0x00, 0x00},//##Reserve
                     {0x7d, 0x00, 0x00, 0x00},//##Reserve
                     {0x7e, 0x00, 0x00, 0x00},//##Reserve
                     {0x7f, 0x00, 0x00, 0x00},//##Reserve
                     };
