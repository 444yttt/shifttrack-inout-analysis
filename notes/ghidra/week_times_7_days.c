/* week_times_7_days 0x10020499c-0x100204ee8 ghidra-pseudocode */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void week_times_7_days(long param_1)

{
  undefined8 *puVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  undefined1 uVar8;
  long extraout_x8;
  long extraout_x8_00;
  ulong uVar9;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long lVar10;
  long extraout_x12;
  long extraout_x12_00;
  long lVar11;
  undefined8 uVar12;
  long unaff_x20;
  code *pcVar13;
  long lVar14;
  code *pcVar15;
  long lVar16;
  long lVar17;
  undefined8 uStack_140;
  long lStack_138;
  long lStack_130;
  long lStack_128;
  undefined4 uStack_11c;
  code *pcStack_118;
  long lStack_110;
  long lStack_108;
  long lStack_100;
  long lStack_f8;
  ulong uStack_f0;
  long lStack_e8;
  long lStack_e0;
  long lStack_d8;
  long lStack_d0;
  long lStack_c8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  long lStack_98;
  long lStack_90;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  
  lVar3 = 0;
  __s10Foundation8CalendarVMa();
  lStack_100 = *(long *)(lVar3 + -8);
  lStack_f8 = lVar3;
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lStack_100 + 0x40));
  lVar3 = (long)&uStack_140 - (extraout_x8 + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0;
  lStack_108 = lVar3;
  __s10Foundation14DateComponentsVMa();
  lStack_e8 = *(long *)(lVar4 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lStack_e8 + 0x40));
  uVar9 = lVar3 - (extraout_x8_00 + 0xfU & 0xfffffffffffffff0);
  lVar5 = 0;
  uStack_f0 = uVar9;
  __s10Foundation8CalendarV9ComponentOMa();
  lVar16 = *(long *)(lVar5 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar16 + 0x40));
  lVar11 = uVar9 - (extraout_x8_01 + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0x1005a82d8;
  func_0x00010000921c(0x1005a82d8,&UNK_10042aa30);
  (*(code *)PTR____chkstk_darwin_10056c088)
            (*(long *)(*(long *)(lVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar17 = lVar11 - extraout_x8_02;
  lVar3 = 0;
  __s10Foundation4DateVMa();
  lVar14 = *(long *)(lVar3 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar14 + 0x40));
  lVar10 = lVar17 - (extraout_x8_03 + 0xfU & 0xfffffffffffffff0);
  lStack_110 = lVar10;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar10 = lVar10 - extraout_x12;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lStack_e0 = lVar10 - extraout_x12_00;
  lVar6 = 0;
  func_0x0001001fecf4();
  lStack_c8 = (long)*(int *)(lVar6 + 0x38);
  uStack_11c = *(undefined4 *)PTR___s10Foundation8CalendarV9ComponentO3dayyA2EmFWC_10056bbb8;
  pcStack_118 = *(code **)(lVar16 + 0x68);
  lStack_d0 = lVar6;
  (*pcStack_118)(lVar11,uStack_11c,lVar5);
  if (SUB168(SEXT816(param_1) * SEXT816(7),8) == param_1 * 7 >> 0x3f) {
    iVar2 = *(int *)(lStack_d0 + 0x24);
    uVar12 = 0x1005af5f8;
    lStack_138 = param_1;
    lStack_128 = lVar4;
    func_0x00010000921c(0x1005af5f8,&UNK_100437f40);
    uStack_140 = uVar12;
    lStack_130 = (long)iVar2;
    lStack_d8 = lVar3;
    __s7SwiftUI5StateV12wrappedValuexvg(lVar10);
    lVar3 = lStack_d8;
    __s10Foundation8CalendarV4date8byAdding5value2to18wrappingComponentsAA4DateVSgAC9ComponentO_SiAJSbtF
              (lVar17,lVar11,param_1 * 7,lVar10,0);
    pcVar13 = *(code **)(lVar14 + 8);
    (*pcVar13)(lVar10,lVar3);
    pcVar15 = *(code **)(lVar16 + 8);
    (*pcVar15)(lVar11,lVar5);
    lVar4 = lVar17;
    (**(code **)(lVar14 + 0x30))(lVar17,1,lVar3);
    if ((int)lVar4 == 1) {
      func_0x00010000a9d0(lVar17,0x1005a82d8,&UNK_10042aa30);
    }
    else {
      (**(code **)(lVar14 + 0x20))(lStack_e0,lVar17,lVar3);
      lVar3 = lStack_d0;
      uVar8 = 3;
      if (lStack_138 < 1) {
        uVar8 = 1;
      }
      uStack_b0 = CONCAT71(uStack_b0._1_7_,uVar8);
      uVar12 = 0x1005aa138;
      func_0x00010000921c(0x1005aa138,&UNK_1004295d0);
      __s7SwiftUI9LazyStateV12wrappedValuexvs(&uStack_b0,uVar12);
      lVar4 = 0x1005a86f8;
      func_0x00010000921c(0x1005a86f8,&UNK_1004285f0);
      uVar9 = (ulong)*(byte *)(lVar16 + 0x50) + 0x20 &
              ((ulong)*(byte *)(lVar16 + 0x50) ^ 0xffffffffffffffff);
      _swift_allocObject();
      uVar12 = _UNK_100426320;
      *(undefined8 *)(lVar4 + 0x18) = _UNK_100426328;
      *(undefined8 *)(lVar4 + 0x10) = uVar12;
      (*pcStack_118)(lVar4 + uVar9,uStack_11c,lVar5);
      lVar6 = lVar4;
      func_0x0001000fc060(lVar4);
      _swift_setDeallocating(lVar4);
      (*pcVar15)(lVar4 + uVar9,lVar5);
      _swift_deallocClassInstance(lVar4,0x20,7);
      __s7SwiftUI5StateV12wrappedValuexvg(lVar10,uStack_140);
      puVar1 = (undefined8 *)(unaff_x20 + *(int *)(lVar3 + 0x20));
      uStack_a8 = puVar1[1];
      uStack_b0 = *puVar1;
      lStack_98 = puVar1[3];
      uStack_a0 = puVar1[2];
      func_0x00010000921c(0x1005a9a68,&UNK_100438360);
      __s7SwiftUI5StateV12wrappedValuexvg(&uStack_80);
      lVar4 = lStack_108;
      __s10Foundation8CalendarV7currentACvgZ(lStack_108);
      lVar5 = lStack_d8;
      lVar3 = lStack_110;
      func_0x0001000da0a8(lStack_110,lVar4,uStack_80,uStack_78,uStack_70);
      (**(code **)(lStack_100 + 8))(lVar4,lStack_f8);
      uVar9 = uStack_f0;
      __s10Foundation8CalendarV14dateComponents_4from2toAA04DateD0VShyAC9ComponentOG_AA0G0VAMtF
                (uStack_f0,lVar6,lVar10,lVar3);
      _swift_bridgeObjectRelease(lVar6);
      (*pcVar13)(lVar3,lVar5);
      lVar3 = lVar5;
      (*pcVar13)();
      uVar7 = (uint)lVar3;
      __s10Foundation14DateComponentsV3daySiSgvg();
      (**(code **)(lStack_e8 + 8))(uVar9,lStack_128);
      lVar3 = 0;
      if ((uVar7 & 0xff) != 1) {
        lVar3 = lVar10;
      }
      if (lRam00000001005ac8d8 != -1) {
        uVar9 = 0;
        _swift_once(0x1005ac8d8,&DAT_1000a6d34);
      }
      uVar12 = uRam00000001005d09d0;
      _UIAccessibilityIsReduceMotionEnabled();
      if ((uVar9 & 1) == 0) {
        _swift_retain_x19();
      }
      else {
        uVar12 = 0;
      }
      lVar4 = lStack_e0;
      lStack_98 = lStack_e0;
      lStack_90 = lVar3;
      __s7SwiftUI13withAnimationyxAA0D0VSg_xyKXEtKlF
                (uVar12,&DAT_100210bbc,&uStack_b0,PTR___sytN_10056ed38 + 8);
      _swift_release_x19();
      (*pcVar13)(lVar4,lVar5);
    }
    return;
  }
                    /* WARNING: Does not return */
  pcVar13 = (code *)SoftwareBreakpoint(1,0x100204ed0);
  (*pcVar13)();
}

