/* page_byAdding_884 0x1001b4a94-0x1001b4e08 ghidra-pseudocode */

undefined8 page_byAdding_884(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined4 uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long lVar6;
  long lVar7;
  long extraout_x12;
  long extraout_x12_00;
  long extraout_x12_01;
  long lVar8;
  code *pcVar9;
  long lVar10;
  long lVar11;
  undefined1 *puVar12;
  undefined1 auStack_a0 [8];
  code *pcStack_98;
  code *pcStack_90;
  long lStack_88;
  long lStack_80;
  long lStack_78;
  long lStack_70;
  undefined8 uStack_68;
  
  lVar2 = 0;
  uStack_68 = param_2;
  __s10Foundation8CalendarV9ComponentOMa();
  lVar8 = *(long *)(lVar2 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar8 + 0x40));
  puVar12 = auStack_a0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0);
  lVar3 = 0x1005a82d8;
  func_0x00010000921c(0x1005a82d8,&UNK_10042aa30);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(*(long *)(lVar3 + -8) + 0x40));
  lVar6 = (long)puVar12 - (extraout_x8_00 + 0xfU & 0xfffffffffffffff0);
  lStack_88 = lVar6;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar6 = lVar6 - extraout_x12;
  lVar4 = 0;
  __s10Foundation4DateVMa();
  lVar11 = *(long *)(lVar4 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar11 + 0x40));
  lVar7 = lVar6 - (extraout_x8_01 + 0xfU & 0xfffffffffffffff0);
  lStack_78 = lVar7;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar7 = lVar7 - extraout_x12_00;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar10 = lVar7 - extraout_x12_01;
  __s10Foundation8CalendarV10startOfDay3forAA4DateVAG_tF(lVar10,param_1);
  uVar1 = *(undefined4 *)PTR___s10Foundation8CalendarV9ComponentO3dayyA2EmFWC_10056bbb8;
  pcStack_90 = *(code **)(lVar8 + 0x68);
  (*pcStack_90)(puVar12,uVar1,lVar2);
  __s10Foundation8CalendarV4date8byAdding5value2to18wrappingComponentsAA4DateVSgAC9ComponentO_SiAJSbtF
            (lVar6,puVar12,0xffffffffffffffff,lVar10,0);
  pcStack_98 = *(code **)(lVar8 + 8);
  (*pcStack_98)(puVar12,lVar2);
  pcVar9 = *(code **)(lVar11 + 0x30);
  lVar3 = lVar6;
  (*pcVar9)(lVar6,1,lVar4);
  lStack_80 = lVar7;
  lStack_70 = lVar11;
  if ((int)lVar3 == 1) {
    (**(code **)(lVar11 + 0x10))(lVar7,lVar10,lVar4);
    lVar3 = lVar6;
    (*pcVar9)(lVar6,1,lVar4);
    if ((int)lVar3 != 1) {
      func_0x00010000a9d0(lVar6,0x1005a82d8,&UNK_10042aa30);
    }
  }
  else {
    (**(code **)(lVar11 + 0x20))(lVar7,lVar6,lVar4);
  }
  (*pcStack_90)(puVar12,uVar1,lVar2);
  lVar3 = lStack_88;
  __s10Foundation8CalendarV4date8byAdding5value2to18wrappingComponentsAA4DateVSgAC9ComponentO_SiAJSbtF
            (lStack_88,puVar12,2,lVar10,0);
  (*pcStack_98)(puVar12,lVar2);
  lVar7 = lVar3;
  (*pcVar9)(lVar3,1,lVar4);
  lVar6 = lStack_70;
  lVar2 = lStack_78;
  if ((int)lVar7 == 1) {
    (**(code **)(lStack_70 + 0x10))(lStack_78,lVar10,lVar4);
    lVar8 = lVar3;
    (*pcVar9)(lVar3,1,lVar4);
    lVar7 = lStack_80;
    if ((int)lVar8 != 1) {
      func_0x00010000a9d0(lVar3,0x1005a82d8,&UNK_10042aa30);
    }
  }
  else {
    (**(code **)(lStack_70 + 0x20))(lStack_78,lVar3,lVar4);
    lVar7 = lStack_80;
  }
  if (lRam00000001005b43b8 != -1) {
    _swift_once(0x1005b43b8,&DAT_1001ce6f4);
  }
  uVar5 = uStack_68;
  func_0x0001001cd534(uRam00000001005d0a58,uStack_68,lVar7,lVar2,param_3);
  pcVar9 = *(code **)(lVar6 + 8);
  (*pcVar9)(lVar2,lVar4);
  (*pcVar9)(lVar7,lVar4);
  (*pcVar9)(lVar10,lVar4);
  return uVar5;
}

