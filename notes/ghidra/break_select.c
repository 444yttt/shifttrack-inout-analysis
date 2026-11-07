/* break_select 0x1000e967c-0x1000e9930 ghidra-pseudocode */

undefined8 break_select(long param_1,long param_2)

{
  ulong uVar1;
  code *pcVar2;
  bool bVar3;
  long lVar4;
  undefined *puVar5;
  long extraout_x8;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long extraout_x12;
  long extraout_x12_00;
  ulong uVar9;
  undefined8 uVar10;
  undefined *puVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  long lVar15;
  long lVar16;
  ulong uStack_a0;
  long lStack_98;
  ulong uStack_90;
  long lStack_88;
  long lStack_80;
  long lStack_78;
  long lStack_70;
  undefined *puStack_68;
  
  lVar4 = 0;
  lStack_70 = param_1;
  func_0x0001000e9930();
  lVar15 = *(long *)(lVar4 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar15 + 0x40));
  lVar6 = (long)&uStack_a0 - (extraout_x8 + 0xfU & 0xfffffffffffffff0);
  lStack_88 = lVar6;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar6 = lVar6 - extraout_x12;
  lStack_80 = lVar6;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lStack_78 = lVar6 - extraout_x12_00;
  uVar12 = *(ulong *)(param_2 + 0x10);
  puVar11 = PTR___swiftEmptyArrayStorage_10056ed48;
  if (uVar12 != 0) {
    uVar14 = 0;
    uVar9 = uVar12 - 1;
    uVar7 = uVar12;
    do {
      while( true ) {
        if (uVar7 == uVar14) {
                    /* WARNING: Does not return */
          pcVar2 = (code *)SoftwareBreakpoint(1,0x1000e9930);
          (*pcVar2)();
        }
        uVar13 = (ulong)*(byte *)(lVar15 + 0x50) + 0x20 &
                 ((ulong)*(byte *)(lVar15 + 0x50) ^ 0xffffffffffffffff);
        lVar6 = *(long *)(lVar15 + 0x48);
        lVar16 = param_2 + uVar13 + lVar6 * uVar14;
        uVar1 = uVar14 + 1;
        if (*(long *)(lVar16 + *(int *)(lVar4 + 0x14)) < lStack_70) break;
        uVar14 = uVar1;
        if (uVar12 == uVar1) goto LAB_1000e982c;
      }
      puVar5 = puVar11;
      uStack_90 = uVar9;
      _swift_isUniquelyReferenced_nonNull_native();
      puStack_68 = puVar11;
      if (((ulong)puVar5 & 1) == 0) {
        func_0x0001000fae9c(0,*(long *)(puVar11 + 0x10) + 1,1);
      }
      uVar7 = *(ulong *)(puStack_68 + 0x10);
      lVar8 = uVar7 + 1;
      if (*(ulong *)(puStack_68 + 0x18) >> 1 <= uVar7) {
        uStack_a0 = uVar7;
        lStack_98 = lVar8;
        func_0x0001000fae9c(1 < *(ulong *)(puStack_68 + 0x18),lVar8,1);
        uVar7 = uStack_a0;
        lVar8 = lStack_98;
      }
      puVar11 = puStack_68;
      *(long *)(puStack_68 + 0x10) = lVar8;
      func_0x00010001dc3c(lVar16,puStack_68 + uVar7 * lVar6 + uVar13,&SUB_1000e9930);
      uVar7 = uVar1;
      if (uVar1 <= uVar12) {
        uVar7 = uVar12;
      }
      bVar3 = uStack_90 != uVar14;
      uVar14 = uVar1;
      uVar9 = uStack_90;
    } while (bVar3);
  }
LAB_1000e982c:
  lVar16 = lStack_88;
  lVar6 = *(long *)(puVar11 + 0x10);
  if (lVar6 == 0) {
    _swift_release_x20();
    uVar10 = 0;
  }
  else {
    uVar12 = (ulong)*(byte *)(lVar15 + 0x50) + 0x20 &
             ((ulong)*(byte *)(lVar15 + 0x50) ^ 0xffffffffffffffff);
    func_0x00010001dc3c(puVar11 + uVar12,lStack_88,&SUB_1000e9930);
    lVar8 = lStack_80;
    func_0x00010001db70(lVar16,lStack_80,&SUB_1000e9930);
    lVar6 = lVar6 + -1;
    if (lVar6 != 0) {
      lVar15 = *(long *)(lVar15 + 0x48);
      puVar11 = puVar11 + uVar12 + lVar15;
      do {
        if (*(long *)(lVar8 + *(int *)(lVar4 + 0x14)) < *(long *)(puVar11 + *(int *)(lVar4 + 0x14)))
        {
          func_0x00010001dc80(lVar8,&SUB_1000e9930);
          func_0x00010001dc3c(puVar11,lVar8,&SUB_1000e9930);
        }
        puVar11 = puVar11 + lVar15;
        lVar6 = lVar6 + -1;
      } while (lVar6 != 0);
    }
    _swift_release_x20();
    lVar6 = lStack_78;
    func_0x00010001db70(lVar8,lStack_78,&SUB_1000e9930);
    uVar10 = *(undefined8 *)(lVar6 + *(int *)(lVar4 + 0x18));
    func_0x00010001dc80(lVar6,&SUB_1000e9930);
  }
  return uVar10;
}

