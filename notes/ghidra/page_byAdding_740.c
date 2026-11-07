/* page_byAdding_740 0x1000837d8-0x100083abc ghidra-pseudocode */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void page_byAdding_740(void)

{
  undefined8 uVar1;
  long lVar2;
  undefined4 uVar3;
  long lVar4;
  long *plVar5;
  code *pcVar6;
  code *pcVar7;
  long lVar8;
  code *pcVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  long unaff_x22;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  code *pcVar16;
  
  uVar11 = *(undefined8 *)(unaff_x22 + 0x138);
  lVar8 = *(long *)(unaff_x22 + 0x140);
  uVar12 = *(undefined8 *)(unaff_x22 + 0x130);
  lVar4 = *(long *)(unaff_x22 + 0x118);
  uVar14 = *(undefined8 *)(unaff_x22 + 0x120);
  uVar10 = *(undefined8 *)(unaff_x22 + 0x108);
  uVar1 = *(undefined8 *)(unaff_x22 + 0x110);
  uVar13 = *(undefined8 *)(unaff_x22 + 0xf8);
  lVar2 = *(long *)(unaff_x22 + 0x100);
  uVar15 = *(undefined8 *)(unaff_x22 + 0xf0);
  __s10Foundation8CalendarV7currentACvgZ(uVar14);
  uVar3 = *(undefined4 *)PTR___s10Foundation8CalendarV9ComponentO3dayyA2EmFWC_10056bbb8;
  pcVar6 = *(code **)(lVar2 + 0x68);
  (*pcVar6)(uVar10,uVar3,uVar13);
  __s10Foundation8CalendarV4date8byAdding5value2to18wrappingComponentsAA4DateVSgAC9ComponentO_SiAJSbtF
            (uVar12,uVar10,0xe,uVar15,0);
  pcVar7 = *(code **)(lVar2 + 8);
  (*pcVar7)(uVar10,uVar13);
  pcVar9 = *(code **)(lVar4 + 8);
  (*pcVar9)(uVar14,uVar1);
  pcVar16 = *(code **)(lVar8 + 0x30);
  (*pcVar16)(uVar12,1,uVar11);
  uVar11 = *(undefined8 *)(unaff_x22 + 0x138);
  uVar10 = *(undefined8 *)(unaff_x22 + 0x130);
  if ((int)uVar12 == 1) {
    (**(code **)(*(long *)(unaff_x22 + 0x140) + 0x10))
              (*(undefined8 *)(unaff_x22 + 0x150),*(undefined8 *)(unaff_x22 + 0xf0),uVar11);
    (*pcVar16)(uVar10,1,uVar11);
    if ((int)uVar10 != 1) {
      func_0x00010000a9d0(*(undefined8 *)(unaff_x22 + 0x130),0x1005a82d8,&UNK_10042aa30);
    }
  }
  else {
    (**(code **)(*(long *)(unaff_x22 + 0x140) + 0x20))
              (*(undefined8 *)(unaff_x22 + 0x150),uVar10,uVar11);
  }
  uVar15 = *(undefined8 *)(unaff_x22 + 0x138);
  uVar11 = *(undefined8 *)(unaff_x22 + 0x120);
  uVar14 = *(undefined8 *)(unaff_x22 + 0x128);
  uVar10 = *(undefined8 *)(unaff_x22 + 0x108);
  uVar1 = *(undefined8 *)(unaff_x22 + 0x110);
  uVar13 = *(undefined8 *)(unaff_x22 + 0xf0);
  uVar12 = *(undefined8 *)(unaff_x22 + 0xf8);
  __s10Foundation8CalendarV7currentACvgZ(uVar11);
  (*pcVar6)(uVar10,uVar3,uVar12);
  __s10Foundation8CalendarV4date8byAdding5value2to18wrappingComponentsAA4DateVSgAC9ComponentO_SiAJSbtF
            (uVar14,uVar10,0xffffffffffffffff,uVar13,0);
  (*pcVar7)(uVar10,uVar12);
  (*pcVar9)(uVar11,uVar1);
  (*pcVar16)(uVar14,1,uVar15);
  uVar10 = *(undefined8 *)(unaff_x22 + 0x138);
  uVar11 = *(undefined8 *)(unaff_x22 + 0x128);
  if ((int)uVar14 == 1) {
    (**(code **)(*(long *)(unaff_x22 + 0x140) + 0x10))
              (*(undefined8 *)(unaff_x22 + 0x148),*(undefined8 *)(unaff_x22 + 0xf0));
    (*pcVar16)(uVar11,1,uVar10);
    if ((int)uVar11 != 1) {
      func_0x00010000a9d0(*(undefined8 *)(unaff_x22 + 0x128),0x1005a82d8,&UNK_10042aa30);
    }
  }
  else {
    (**(code **)(*(long *)(unaff_x22 + 0x140) + 0x20))(*(undefined8 *)(unaff_x22 + 0x148),uVar11);
  }
  __s10Foundation8CalendarV7currentACvgZ(*(undefined8 *)(unaff_x22 + 0x120));
  if (lRam00000001005b43b8 != -1) {
    _swift_once(0x1005b43b8,&DAT_1001ce6f4);
  }
  uVar11 = *(undefined8 *)(unaff_x22 + 0x148);
  uVar10 = *(undefined8 *)(unaff_x22 + 0x138);
  lVar8 = *(long *)(unaff_x22 + 0x140);
  uVar13 = *(undefined8 *)(unaff_x22 + 0x120);
  uVar14 = *(undefined8 *)(unaff_x22 + 0x110);
  lVar4 = unaff_x22 + 0x10;
  func_0x0001001cd534(lVar4,uVar11,*(undefined8 *)(unaff_x22 + 0x150),uVar13);
  *(long *)(unaff_x22 + 0x180) = lVar4;
  (*pcVar9)(uVar13,uVar14);
  pcVar6 = *(code **)(lVar8 + 8);
  *(code **)(unaff_x22 + 0x188) = pcVar6;
  (*pcVar6)(uVar11,uVar10);
  plVar5 = (long *)(ulong)_UNK_10042fe24;
  lVar8 = (long)_UNK_10042fe20;
  _swift_task_alloc();
  *(long **)(unaff_x22 + 400) = plVar5;
  *plVar5 = unaff_x22;
  plVar5[1] = (long)&DAT_100083abc;
                    /* WARNING: Could not recover jumptable at 0x000100083aa0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&UNK_10042fe20 + lVar8))(lVar4,unaff_x22 + 0x10,*(undefined8 *)(unaff_x22 + 0xf0));
  return;
}

