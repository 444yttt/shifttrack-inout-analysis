/* minute_to_calendar_date 0x100027f04-0x10002829c ghidra-pseudocode */

void minute_to_calendar_date(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  ulong uVar1;
  uint uVar2;
  undefined1 *puVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long lVar8;
  long extraout_x8_03;
  long extraout_x8_04;
  ulong uVar9;
  code *pcVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  undefined1 auStack_f0 [8];
  long lStack_e8;
  long lStack_e0;
  long lStack_d8;
  long lStack_d0;
  long lStack_c8;
  long lStack_c0;
  long lStack_b8;
  undefined1 *puStack_b0;
  long lStack_a8;
  long lStack_a0;
  undefined8 uStack_98;
  long lStack_90;
  long lStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  
  lVar5 = 0;
  uStack_98 = param_1;
  __s10Foundation8CalendarV15SearchDirectionOMa();
  lStack_a0 = *(long *)(lVar5 + -8);
  lStack_a8 = lVar5;
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lStack_a0 + 0x40));
  lVar6 = 0;
  puStack_b0 = auStack_f0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0);
  __s10Foundation8CalendarV18RepeatedTimePolicyOMa();
  lVar12 = *(long *)(lVar6 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar12 + 0x40));
  lVar14 = (long)(auStack_f0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0)) -
           (extraout_x8_00 + 0xfU & 0xfffffffffffffff0);
  lVar7 = 0;
  __s10Foundation8CalendarV14MatchingPolicyOMa();
  lVar15 = *(long *)(lVar7 + -8);
  lStack_e8 = lVar7;
  lStack_e0 = lVar15;
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar15 + 0x40));
  lVar13 = lVar14 - (extraout_x8_01 + 0xfU & 0xfffffffffffffff0);
  lVar5 = 0;
  __s10Foundation4DateVMa();
  lStack_c8 = *(long *)(lVar5 + -8);
  lStack_d0 = lVar5;
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lStack_c8 + 0x40));
  lVar8 = lVar13 - (extraout_x8_02 + 0xfU & 0xfffffffffffffff0);
  lVar5 = 0;
  __s10Foundation8CalendarVMa();
  lStack_c0 = *(long *)(lVar5 + -8);
  lStack_b8 = lVar5;
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lStack_c0 + 0x40));
  lVar11 = lVar8 - (extraout_x8_03 + 0xfU & 0xfffffffffffffff0);
  lVar5 = 0x1005a82d8;
  lStack_d8 = lVar11;
  func_0x00010000921c(0x1005a82d8,&UNK_10042aa30);
  (*(code *)PTR____chkstk_darwin_10056c088)
            (*(long *)(*(long *)(lVar5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lStack_90 = lVar11 - extraout_x8_04;
  uStack_78 = *(undefined8 *)(param_4 + 0x18);
  uStack_80 = *(undefined8 *)(param_4 + 0x10);
  uStack_70 = *(undefined8 *)(param_4 + 0x20);
  func_0x00010000921c(0x1005a8ef8,&UNK_100434370);
  __s7SwiftUI7BindingV12wrappedValuexvg(&lStack_88);
  uVar9 = lStack_88 % 0x5a0;
  uVar1 = (ulong)((int)uVar9 + 0x5a0);
  if (-1 < (long)uVar9) {
    uVar1 = uVar9;
  }
  __s10Foundation8CalendarV7currentACvgZ(lVar11);
  uVar2 = ((uint)uVar1 & 0xffff) / 0x3c;
  __s10Foundation4DateVACycfC(lVar8);
  (**(code **)(lVar15 + 0x68))
            (lVar13,*(undefined4 *)
                     PTR___s10Foundation8CalendarV14MatchingPolicyO8nextTimeyA2EmFWC_10056bb28,lVar7
            );
  (**(code **)(lVar12 + 0x68))
            (lVar14,*(undefined4 *)
                     PTR___s10Foundation8CalendarV18RepeatedTimePolicyO5firstyA2EmFWC_10056bb58,
             lVar6);
  lVar4 = lStack_a0;
  lVar15 = lStack_a8;
  puVar3 = puStack_b0;
  (**(code **)(lStack_a0 + 0x68))
            (puStack_b0,
             *(undefined4 *)
              PTR___s10Foundation8CalendarV15SearchDirectionO7forwardyA2EmFWC_10056bb48,lStack_a8);
  lVar5 = lStack_d8;
  __s10Foundation8CalendarV4date13bySettingHour6minute6second2of14matchingPolicy012repeatedTimeK09directionAA4DateVSgSi_S2iAmC08MatchingK0OAC08RepeatedmK0OAC15SearchDirectionOtF
            (lStack_90,uVar2,(uint)uVar1 + uVar2 * -0x3c & 0xffff,0,lVar8,lVar13,lVar14,puVar3);
  lVar11 = lStack_c8;
  lVar7 = lStack_d0;
  (**(code **)(lVar4 + 8))(puVar3,lVar15);
  (**(code **)(lVar12 + 8))(lVar14,lVar6);
  (**(code **)(lStack_e0 + 8))(lVar13,lStack_e8);
  (**(code **)(lVar11 + 8))(lVar8,lVar7);
  lVar6 = lStack_90;
  (**(code **)(lStack_c0 + 8))(lVar5,lStack_b8);
  pcVar10 = *(code **)(lVar11 + 0x30);
  lVar5 = lVar6;
  (*pcVar10)(lVar6,1,lVar7);
  if ((int)lVar5 == 1) {
    __s10Foundation4DateVACycfC(uStack_98);
    lVar5 = lVar6;
    (*pcVar10)(lVar6,1,lVar7);
    if ((int)lVar5 != 1) {
      func_0x00010000a9d0(lVar6,0x1005a82d8,&UNK_10042aa30);
    }
  }
  else {
    (**(code **)(lVar11 + 0x20))(uStack_98,lVar6,lVar7);
  }
  return;
}

