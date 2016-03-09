  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 3;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (ARDroneWPTracking_P)
    ;%
      section.nData     = 31;
      section.data(31)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_P.PacketOutput_MaxMissedTicks
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_P.PacketOutput_YieldWhenWaiting
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ARDroneWPTracking_P.PacketOutput1_MaxMissedTicks
	  section.data(3).logicalSrcIdx = 4;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ARDroneWPTracking_P.PacketOutput1_YieldWhenWaiting
	  section.data(4).logicalSrcIdx = 5;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ARDroneWPTracking_P.PacketInput_MaxMissedTicks
	  section.data(5).logicalSrcIdx = 8;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ARDroneWPTracking_P.PacketInput_YieldWhenWaiting
	  section.data(6).logicalSrcIdx = 9;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ARDroneWPTracking_P.land_Value
	  section.data(7).logicalSrcIdx = 10;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ARDroneWPTracking_P.takeoff_Value
	  section.data(8).logicalSrcIdx = 11;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ARDroneWPTracking_P.Constant1_Value
	  section.data(9).logicalSrcIdx = 12;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ARDroneWPTracking_P.Constant5_Value
	  section.data(10).logicalSrcIdx = 13;
	  section.data(10).dtTransOffset = 10;
	
	  ;% ARDroneWPTracking_P.UnitDelaytoavoidalgebraicloop_InitialCondition
	  section.data(11).logicalSrcIdx = 14;
	  section.data(11).dtTransOffset = 260;
	
	  ;% ARDroneWPTracking_P.commandsdisabled_Value
	  section.data(12).logicalSrcIdx = 15;
	  section.data(12).dtTransOffset = 261;
	
	  ;% ARDroneWPTracking_P.commandsenabled_Value
	  section.data(13).logicalSrcIdx = 16;
	  section.data(13).dtTransOffset = 262;
	
	  ;% ARDroneWPTracking_P.deg2rad_Gain
	  section.data(14).logicalSrcIdx = 17;
	  section.data(14).dtTransOffset = 263;
	
	  ;% ARDroneWPTracking_P.Gain3_Gain
	  section.data(15).logicalSrcIdx = 18;
	  section.data(15).dtTransOffset = 264;
	
	  ;% ARDroneWPTracking_P.Gain1_Gain
	  section.data(16).logicalSrcIdx = 19;
	  section.data(16).dtTransOffset = 265;
	
	  ;% ARDroneWPTracking_P.Saturation1_UpperSat
	  section.data(17).logicalSrcIdx = 20;
	  section.data(17).dtTransOffset = 266;
	
	  ;% ARDroneWPTracking_P.Saturation1_LowerSat
	  section.data(18).logicalSrcIdx = 21;
	  section.data(18).dtTransOffset = 267;
	
	  ;% ARDroneWPTracking_P.Gain2_Gain
	  section.data(19).logicalSrcIdx = 22;
	  section.data(19).dtTransOffset = 268;
	
	  ;% ARDroneWPTracking_P.Gain_Gain
	  section.data(20).logicalSrcIdx = 23;
	  section.data(20).dtTransOffset = 269;
	
	  ;% ARDroneWPTracking_P.Saturation2_UpperSat
	  section.data(21).logicalSrcIdx = 24;
	  section.data(21).dtTransOffset = 270;
	
	  ;% ARDroneWPTracking_P.Saturation2_LowerSat
	  section.data(22).logicalSrcIdx = 25;
	  section.data(22).dtTransOffset = 271;
	
	  ;% ARDroneWPTracking_P.proportionalcontrolgainyaw_Gain
	  section.data(23).logicalSrcIdx = 26;
	  section.data(23).dtTransOffset = 272;
	
	  ;% ARDroneWPTracking_P.Saturation3_UpperSat
	  section.data(24).logicalSrcIdx = 27;
	  section.data(24).dtTransOffset = 273;
	
	  ;% ARDroneWPTracking_P.Saturation3_LowerSat
	  section.data(25).logicalSrcIdx = 28;
	  section.data(25).dtTransOffset = 274;
	
	  ;% ARDroneWPTracking_P.proportionalcontrolgain_Gain
	  section.data(26).logicalSrcIdx = 29;
	  section.data(26).dtTransOffset = 275;
	
	  ;% ARDroneWPTracking_P.Saturation4_UpperSat
	  section.data(27).logicalSrcIdx = 30;
	  section.data(27).dtTransOffset = 276;
	
	  ;% ARDroneWPTracking_P.Saturation4_LowerSat
	  section.data(28).logicalSrcIdx = 31;
	  section.data(28).dtTransOffset = 277;
	
	  ;% ARDroneWPTracking_P._Value
	  section.data(29).logicalSrcIdx = 32;
	  section.data(29).dtTransOffset = 278;
	
	  ;% ARDroneWPTracking_P.stop_Value
	  section.data(30).logicalSrcIdx = 33;
	  section.data(30).dtTransOffset = 279;
	
	  ;% ARDroneWPTracking_P.deg2rad1_Gain
	  section.data(31).logicalSrcIdx = 34;
	  section.data(31).dtTransOffset = 280;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_P.PacketOutput_PacketID
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_P.PacketOutput1_PacketID
	  section.data(2).logicalSrcIdx = 36;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ARDroneWPTracking_P.PacketInput_PacketID
	  section.data(3).logicalSrcIdx = 37;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_P.Constant_Value
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_P.ManualSwitch1_CurrentSetting
	  section.data(2).logicalSrcIdx = 39;
	  section.data(2).dtTransOffset = 2;
	
	  ;% ARDroneWPTracking_P.ManualSwitch2_CurrentSetting
	  section.data(3).logicalSrcIdx = 40;
	  section.data(3).dtTransOffset = 3;
	
	  ;% ARDroneWPTracking_P.ManualSwitch_CurrentSetting
	  section.data(4).logicalSrcIdx = 41;
	  section.data(4).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 3;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (ARDroneWPTracking_B)
    ;%
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_B.ManualSwitch1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_B.TypeConversion6
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ARDroneWPTracking_B.Constant1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ARDroneWPTracking_B.Integrator
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% ARDroneWPTracking_B.Constant5
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% ARDroneWPTracking_B.TypeConversion1
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 256;
	
	  ;% ARDroneWPTracking_B.TypeConversion2
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 257;
	
	  ;% ARDroneWPTracking_B.ManualSwitch2
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 258;
	
	  ;% ARDroneWPTracking_B.deg2rad
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 259;
	
	  ;% ARDroneWPTracking_B.TypeConversion4
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 262;
	
	  ;% ARDroneWPTracking_B.Clock1
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 263;
	
	  ;% ARDroneWPTracking_B.TypeConversion5
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 264;
	
	  ;% ARDroneWPTracking_B.ManualSwitch
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 265;
	
	  ;% ARDroneWPTracking_B.TypeConversion
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 266;
	
	  ;% ARDroneWPTracking_B.TypeConversion7
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 267;
	
	  ;% ARDroneWPTracking_B.TmpSignalConversionAtToWorkspaceInport1
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 268;
	
	  ;% ARDroneWPTracking_B.deg2rad1
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 277;
	
	  ;% ARDroneWPTracking_B.Vel_xy
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 278;
	
	  ;% ARDroneWPTracking_B.yawOut
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 280;
	
	  ;% ARDroneWPTracking_B.isFlying
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 281;
	
	  ;% ARDroneWPTracking_B.status
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 282;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_B.PacketInput_o1
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_B.dataControl
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 500;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_B.PacketInput_o2
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 3;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (ARDroneWPTracking_DW)
    ;%
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_DW.UnitDelaytoavoidalgebraicloop_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_DW.wpointer
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% ARDroneWPTracking_DW.t0
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% ARDroneWPTracking_DW.yaw0
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% ARDroneWPTracking_DW.mode
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% ARDroneWPTracking_DW.SequenceNumber
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% ARDroneWPTracking_DW.count
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% ARDroneWPTracking_DW.countHeader
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% ARDroneWPTracking_DW.countBuffer
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% ARDroneWPTracking_DW.hPrev
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_DW.PacketOutput_PWORK
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_DW.PacketOutput1_PWORK
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 2;
	
	  ;% ARDroneWPTracking_DW.PacketInput_PWORK
	  section.data(3).logicalSrcIdx = 12;
	  section.data(3).dtTransOffset = 4;
	
	  ;% ARDroneWPTracking_DW.Euleranglesdeg_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 13;
	  section.data(4).dtTransOffset = 5;
	
	  ;% ARDroneWPTracking_DW.ToWorkspace6_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 14;
	  section.data(5).dtTransOffset = 6;
	
	  ;% ARDroneWPTracking_DW.Heightm_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 15;
	  section.data(6).dtTransOffset = 7;
	
	  ;% ARDroneWPTracking_DW.InertialpotitionalongXem_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 16;
	  section.data(7).dtTransOffset = 8;
	
	  ;% ARDroneWPTracking_DW.InertialpotitionalongYem_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 17;
	  section.data(8).dtTransOffset = 9;
	
	  ;% ARDroneWPTracking_DW.ToWorkspace_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 18;
	  section.data(9).dtTransOffset = 10;
	
	  ;% ARDroneWPTracking_DW.headingdeg_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 19;
	  section.data(10).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_DW.Integrator_IWORK.IcNeedsLoading
	  section.data(1).logicalSrcIdx = 20;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% ARDroneWPTracking_DW.frame
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% ARDroneWPTracking_DW.lastFrame
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 496;
	
	  ;% ARDroneWPTracking_DW.buffer
	  section.data(3).logicalSrcIdx = 23;
	  section.data(3).dtTransOffset = 992;
	
	  ;% ARDroneWPTracking_DW.dataPrev
	  section.data(4).logicalSrcIdx = 24;
	  section.data(4).dtTransOffset = 2016;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 3081800862;
  targMap.checksum1 = 1628248587;
  targMap.checksum2 = 288507846;
  targMap.checksum3 = 1011084738;

