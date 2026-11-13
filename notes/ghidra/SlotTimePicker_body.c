/* SlotTimePicker_body 0x100027b88-0x100027f04 ghidra-pseudocode */

void SlotTimePicker_body(long param_1)

{
  undefined1 *puVar1;
  long lVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined8 uVar7;
  undefined *puVar8;
  undefined8 *puVar9;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  undefined8 *unaff_x20;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined1 auStack_d0 [8];
  undefined1 *puStack_c8;
  long lStack_c0;
  long lStack_b8;
  long lStack_b0;
  long lStack_a8;
  undefined1 auStack_a0 [16];
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  lVar2 = 0;
  lStack_a8 = param_1;
  __s7SwiftUI20DatePickerComponentsVMa();
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(*(long *)(lVar2 + -8) + 0x40));
  lVar2 = 0x1005a9040;
  puStack_c8 = auStack_d0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0);
  func_0x00010000921c(0x1005a9040,&UNK_1004285a0);
  (*(code *)PTR____chkstk_darwin_10056c088)
            (*(long *)(*(long *)(lVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar10 = (long)(auStack_d0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0)) - extraout_x8_00;
  lVar2 = 0x1005a9048;
  func_0x00010000921c(0x1005a9048,&UNK_1004285a8);
  lStack_c0 = *(long *)(lVar2 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(long *)(lStack_c0 + 0x40) + 0xfU & 0xfffffffffffffff0)
  ;
  lVar11 = lVar10 - extraout_x8_01;
  lVar3 = 0x1005a9050;
  func_0x00010000921c(0x1005a9050,&UNK_1004285b0);
  lStack_b8 = *(long *)(lVar3 + -8);
  lStack_b0 = lVar3;
  (*(code *)PTR____chkstk_darwin_10056c088)(*(long *)(lStack_b8 + 0x40) + 0xfU & 0xfffffffffffffff0)
  ;
  uStack_68 = unaff_x20[1];
  uStack_70 = *unaff_x20;
  uStack_88 = unaff_x20[1];
  uStack_90 = *unaff_x20;
  uStack_78 = unaff_x20[2];
  __sScMMa(0);
  puVar5 = PTR___sScMMa_10056f1e8;
  func_0x00010000a3c4(&uStack_70,auStack_a0);
  func_0x00010000a3c4(&uStack_70,auStack_a0);
  puVar4 = &uStack_78;
  func_0x000100032958(puVar4,auStack_a0);
  _swift_retain_x22();
  __sScM6sharedScMvgZ();
  uVar7 = 0x1005a82d0;
  func_0x000100008b94(0x1005a82d0,puVar5,PTR___sScMScAsMc_10056f1f0);
  puVar5 = &UNK_10053d850;
  _swift_allocObject(&UNK_10053d850,0x48,7);
  *(undefined8 **)(puVar5 + 0x10) = puVar4;
  *(undefined8 *)(puVar5 + 0x18) = uVar7;
  uVar12 = *unaff_x20;
  uVar14 = unaff_x20[3];
  uVar13 = unaff_x20[2];
  *(undefined8 *)(puVar5 + 0x28) = unaff_x20[1];
  *(undefined8 *)(puVar5 + 0x20) = uVar12;
  *(undefined8 *)(puVar5 + 0x38) = uVar14;
  *(undefined8 *)(puVar5 + 0x30) = uVar13;
  *(undefined8 *)(puVar5 + 0x40) = unaff_x20[4];
  func_0x00010000a3c4(&uStack_70,auStack_a0);
  puVar4 = &uStack_78;
  func_0x000100032958(puVar4,auStack_a0);
  _swift_retain_x22();
  __sScM6sharedScMvgZ();
  puVar6 = &UNK_10053d878;
  _swift_allocObject(&UNK_10053d878,0x48,7);
  *(undefined8 **)(puVar6 + 0x10) = puVar4;
  *(undefined8 *)(puVar6 + 0x18) = uVar7;
  uVar7 = *unaff_x20;
  uVar13 = unaff_x20[3];
  uVar12 = unaff_x20[2];
  *(undefined8 *)(puVar6 + 0x28) = unaff_x20[1];
  *(undefined8 *)(puVar6 + 0x20) = uVar7;
  *(undefined8 *)(puVar6 + 0x38) = uVar13;
  *(undefined8 *)(puVar6 + 0x30) = uVar12;
  *(undefined8 *)(puVar6 + 0x40) = unaff_x20[4];
  uVar7 = 0;
  __s10Foundation4DateVMa(0);
  puVar8 = &DAT_100032998;
  __s7SwiftUI7BindingV3get3setACyxGxyc_yxctcfC
            (lVar10,&DAT_100032998,puVar5,&DAT_1000329e0,puVar6,uVar7);
  puVar1 = puStack_c8;
  __s7SwiftUI20DatePickerComponentsV13hourAndMinuteACvgZ(puStack_c8);
  func_0x00010000a400();
  __s7SwiftUI10DatePickerVA2A4TextVRszrlE_9selection19displayedComponentsACyAEGqd___AA7BindingVy10Foundation0C0VGAA0cdH0VtcSyRd__lufC
            (lVar11,&uStack_90,lVar10,puVar1,PTR___sSSN_10056e7f0,puVar8);
  uVar7 = 0x1005a9058;
  func_0x00010000ab60(0x1005a9058,0x1005a9048,&UNK_1004285a8,
                      PTR___s7SwiftUI10DatePickerVyxGAA4ViewAAMc_10056ca08);
  __s7SwiftUI4ViewPAAE12labelsHiddenQryF(lVar11 - extraout_x8_02,lVar2,uVar7);
  (**(code **)(lStack_c0 + 8))(lVar11,lVar2);
  if (lRam00000001005acd50 != -1) {
    _swift_once(0x1005acd50,&DAT_1000ac6dc);
  }
  uVar7 = uRam00000001005d09e0;
  puVar5 = &UNK_1004285b8;
  _swift_getKeyPath();
  uStack_90 = uVar7;
  puVar6 = puVar5;
  func_0x000100032254();
  _swift_retain_x21();
  puVar9 = &uStack_90;
  __s7SwiftUI13AnyShapeStyleVyACxcAA0dE0RzlufC(puVar9,PTR___s7SwiftUI5ColorVN_10056de50,puVar6);
  lVar3 = lStack_a8;
  (**(code **)(lStack_b8 + 0x20))(lStack_a8,lVar11 - extraout_x8_02,lStack_b0);
  lVar2 = 0x1005a9060;
  func_0x00010000921c(0x1005a9060,&UNK_1004285e8);
  puVar4 = (undefined8 *)(lVar3 + *(int *)(lVar2 + 0x24));
  *puVar4 = puVar5;
  puVar4[1] = puVar9;
  return;
}

