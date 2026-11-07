/* workplace_defaults 0x1000defb8-0x1000e021c ghidra-pseudocode */

/* WARNING: Removing unreachable block (ram,0x0001000dfbf4) */
/* WARNING: Removing unreachable block (ram,0x0001000df668) */
/* WARNING: Removing unreachable block (ram,0x0001000df890) */
/* WARNING: Removing unreachable block (ram,0x0001000dfa44) */
/* WARNING: Removing unreachable block (ram,0x0001000df710) */
/* WARNING: Removing unreachable block (ram,0x0001000df71c) */
/* WARNING: Removing unreachable block (ram,0x0001000df850) */
/* WARNING: Removing unreachable block (ram,0x0001000dfb60) */
/* WARNING: Removing unreachable block (ram,0x0001000df674) */
/* WARNING: Removing unreachable block (ram,0x0001000df684) */
/* WARNING: Removing unreachable block (ram,0x0001000dff68) */
/* WARNING: Removing unreachable block (ram,0x0001000dfecc) */
/* WARNING: Removing unreachable block (ram,0x0001000dfeec) */
/* WARNING: Removing unreachable block (ram,0x0001000df600) */
/* WARNING: Removing unreachable block (ram,0x0001000df738) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void workplace_defaults(undefined8 param_1,long param_2)

{
  undefined8 *puVar1;
  long *plVar2;
  byte *pbVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined1 *puVar6;
  byte *pbVar7;
  undefined8 uVar8;
  undefined1 uVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  undefined *puVar17;
  undefined *puVar18;
  undefined8 uVar19;
  uint *puVar20;
  ulong uVar21;
  long extraout_x8;
  long extraout_x8_00;
  long lVar22;
  long lVar23;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  long lVar24;
  long lVar25;
  undefined8 uVar26;
  long extraout_x12;
  long extraout_x12_00;
  long lVar27;
  undefined8 uVar28;
  long unaff_x21;
  long lVar29;
  byte bVar30;
  ulong uVar31;
  undefined1 *puStack_220;
  undefined8 *puStack_218;
  undefined8 *puStack_210;
  long lStack_208;
  undefined8 *apuStack_200 [2];
  long lStack_1f0;
  undefined8 uStack_1e8;
  undefined8 *puStack_1e0;
  undefined8 *puStack_1d8;
  undefined8 *puStack_1d0;
  undefined8 *puStack_1c8;
  long lStack_1c0;
  long lStack_1b8;
  long lStack_1b0;
  long lStack_1a8;
  long lStack_1a0;
  byte *pbStack_198;
  byte *pbStack_190;
  code *pcStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  ulong uStack_168;
  long lStack_160;
  ulong uStack_158;
  long lStack_150;
  long lStack_148;
  long lStack_140;
  byte *pbStack_138;
  long lStack_130;
  long lStack_128;
  long lStack_120;
  undefined8 *puStack_118;
  long lStack_110;
  long lStack_108;
  long lStack_100;
  long lStack_f8;
  long lStack_f0;
  long lStack_e8;
  undefined8 uStack_b8;
  long lStack_a8;
  uint uStack_a0;
  undefined4 uStack_9c;
  long lStack_98;
  long lStack_90;
  undefined1 uStack_88;
  undefined7 uStack_87;
  undefined8 uStack_80;
  undefined1 uStack_78;
  undefined7 uStack_77;
  undefined1 uStack_51;
  
  lVar13 = 0x1005ae7c8;
  uStack_1e8 = param_1;
  func_0x00010000921c(0x1005ae7c8,&UNK_10042e500);
  lStack_130 = *(long *)(lVar13 + -8);
  lStack_108 = lVar13;
  (*(code *)PTR____chkstk_darwin_10056c088)
            (*(long *)(lStack_130 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar13 = 0x1005ae7d0;
  lStack_110 = (long)&puStack_220 - extraout_x8;
  func_0x00010000921c(0x1005ae7d0,&UNK_10042e508);
  lStack_100 = *(long *)(lVar13 + -8);
  lStack_f0 = lVar13;
  (*(code *)PTR____chkstk_darwin_10056c088)
            (*(long *)(lStack_100 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar22 = ((long)&puStack_220 - extraout_x8) - extraout_x8_00;
  lVar12 = 0;
  __s10Foundation4UUIDVMa();
  lVar23 = *(long *)(lVar12 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar23 + 0x40));
  lVar24 = lVar22 - (extraout_x8_01 + 0xfU & 0xfffffffffffffff0);
  lStack_f8 = lVar24;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar24 = lVar24 - extraout_x12;
  lVar13 = 0;
  __s10Foundation8CalendarVMa();
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(*(long *)(lVar13 + -8) + 0x40));
  lVar27 = lVar24 - (extraout_x8_02 + 0xfU & 0xfffffffffffffff0);
  lVar13 = 0;
  __s10Foundation4DateVMa();
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(*(long *)(lVar13 + -8) + 0x40));
  lVar29 = lVar27 - (extraout_x8_03 + 0xfU & 0xfffffffffffffff0);
  lVar14 = 0;
  func_0x0001000e3704();
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(*(long *)(lVar14 + -8) + 0x40));
  lVar25 = lVar29 - (extraout_x8_04 + 0xfU & 0xfffffffffffffff0);
  lStack_e8 = lVar25;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar25 = lVar25 - extraout_x12_00;
  __s10Foundation4UUIDVACycfC(lVar25);
  puVar1 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x14));
  *puVar1 = 0;
  puVar1[1] = 0xe000000000000000;
  iVar10 = *(int *)(lVar14 + 0x18);
  lVar13 = 0x1005ae690;
  puStack_118 = puVar1;
  func_0x00010000921c(0x1005ae690,&UNK_10042e4e0);
  lVar15 = 0;
  func_0x0001000e996c();
  lStack_160 = *(long *)(*(long *)(lVar15 + -8) + 0x48);
  uStack_168 = (ulong)*(byte *)(*(long *)(lVar15 + -8) + 0x50);
  uVar31 = uStack_168 + 0x20 & (uStack_168 ^ 0xffffffffffffffff);
  uVar21 = uStack_168 | 7;
  lStack_150 = lVar13;
  _swift_allocObject(lVar13,uVar31 + lStack_160);
  uVar26 = _UNK_100426320;
  uStack_178 = _UNK_100426328;
  uStack_180 = _UNK_100426320;
  *(undefined8 *)(lVar13 + 0x18) = _UNK_100426328;
  *(undefined8 *)(lVar13 + 0x10) = uVar26;
  lVar16 = lVar13 + uVar31;
  uStack_158 = uVar31;
  __s10Foundation4DateVACycfC(lVar29);
  __s10Foundation8CalendarV7currentACvgZ(lVar27);
  func_0x0001000e9470();
  __s10Foundation4UUIDVACycfC(lVar24);
  pcStack_188 = *(code **)(lVar23 + 0x20);
  lStack_140 = lVar24;
  (*pcStack_188)(lVar16,lVar24,lVar12);
  plVar2 = (long *)(lVar16 + *(int *)(lVar15 + 0x14));
  *plVar2 = lVar29;
  plVar2[1] = lVar27;
  plVar2[2] = uVar21;
  *(undefined8 *)(lVar16 + *(int *)(lVar15 + 0x18)) = 0;
  lStack_148 = lVar15;
  lStack_128 = lVar13;
  *(long *)(lVar25 + iVar10) = lVar13;
  pbVar3 = (byte *)(lVar25 + *(int *)(lVar14 + 0x1c));
  *pbVar3 = 1;
  *(undefined8 *)(pbVar3 + 0x10) = _UNK_10042d688;
  *(undefined8 *)(pbVar3 + 8) = _UNK_10042d680;
  pbStack_138 = pbVar3;
  pbVar3[0x18] = 0x19;
  pbVar3[0x19] = 0;
  pbVar3[0x1a] = 0;
  pbVar3[0x1b] = 0;
  pbVar3[0x1c] = 0;
  pbVar3[0x1d] = 0;
  pbVar3[0x1e] = 0;
  pbVar3[0x1f] = 0;
  pbVar3 = (byte *)(lVar25 + *(int *)(lVar14 + 0x20));
  *pbVar3 = 1;
  pbStack_190 = pbVar3;
  *(undefined8 *)(pbVar3 + 0x10) = _UNK_10042d698;
  *(undefined8 *)(pbVar3 + 8) = _UNK_10042d690;
  pbVar3 = (byte *)(lVar25 + *(int *)(lVar14 + 0x24));
  lVar13 = 7;
  __sSa28_allocateBufferUninitialized15minimumCapacitys06_ArrayB0VyxGSi_tFZ(7,PTR___sSiN_10056e918);
  *(undefined8 *)(lVar13 + 0x10) = 7;
  *(undefined8 *)(lVar13 + 0x28) = 0;
  *(undefined8 *)(lVar13 + 0x20) = 0;
  *(undefined8 *)(lVar13 + 0x38) = 0;
  *(undefined8 *)(lVar13 + 0x30) = 0;
  *(undefined8 *)(lVar13 + 0x48) = 0;
  *(undefined8 *)(lVar13 + 0x40) = 0;
  *(undefined8 *)(lVar13 + 0x50) = 0;
  *pbVar3 = 0;
  lStack_1a0 = lVar13;
  pbStack_198 = pbVar3;
  *(long *)(pbVar3 + 8) = lVar13;
  lStack_1a8 = (long)*(int *)(lVar14 + 0x28);
  *(undefined1 *)(lVar25 + lStack_1a8) = 0;
  iVar11 = *(int *)(lVar14 + 0x2c);
  if (lRam00000001005ae200 != -1) {
    _swift_once(0x1005ae200,legal_break_defaults);
  }
  uVar19 = uRam00000001005d0a40;
  *(undefined8 *)(lVar25 + iVar11) = uRam00000001005d0a40;
  puVar1 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x30));
  puVar1[1] = 0;
  puVar1[2] = 0;
  *puVar1 = 0;
  *(undefined1 *)(puVar1 + 3) = 1;
  lStack_1b8 = (long)*(int *)(lVar14 + 0x34);
  *(undefined8 *)(lVar25 + lStack_1b8) = 0;
  lStack_1c0 = (long)*(int *)(lVar14 + 0x38);
  *(undefined1 *)(lVar25 + lStack_1c0) = 0;
  puVar4 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x3c));
  puStack_1c8 = puVar4;
  *puVar4 = 0;
  puVar4[1] = 0xe000000000000000;
  puVar4 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x40));
  *puVar4 = 0;
  puVar4[1] = 0xe000000000000000;
  puVar5 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x44));
  puStack_1d0 = puVar4;
  *puVar5 = 0;
  puVar5[1] = 0xe000000000000000;
  puVar4 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x48));
  puStack_1d8 = puVar5;
  *puVar4 = 0x100000000000007d;
  puVar4[1] = 0x80000001004fd070;
  puVar5 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x4c));
  puStack_1e0 = puVar4;
  *puVar5 = 0x100000000000006b;
  puVar5[1] = 0x80000001004fd0f0;
  puVar4 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x50));
  apuStack_200[0] = puVar5;
  *puVar4 = 0x10000000000000bf;
  puVar4[1] = 0x80000001004fd1c0;
  puVar6 = (undefined1 *)(lVar25 + *(int *)(lVar14 + 0x54));
  apuStack_200[1] = puVar4;
  *puVar6 = 0;
  *(undefined8 *)(puVar6 + 8) = 0xd000000000000013;
  *(undefined8 *)(puVar6 + 0x10) = 0x80000001004fd280;
  *(undefined8 *)(puVar6 + 0x18) = 0;
  *(undefined8 *)(puVar6 + 0x20) = 0;
  *(undefined8 *)(puVar6 + 0x28) = 0xf000000000000000;
  puVar4 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x58));
  lStack_1b0 = (long)iVar11;
  *puVar4 = 0;
  puVar4[1] = 0;
  lStack_1f0 = (long)*(int *)(lVar14 + 0x5c);
  *(undefined **)(lVar25 + lStack_1f0) = PTR___swiftEmptyArrayStorage_10056ed48;
  puVar5 = (undefined8 *)(lVar25 + *(int *)(lVar14 + 0x60));
  *puVar5 = 3;
  puVar5[2] = 0;
  puVar5[1] = 0;
  puVar5[4] = 0;
  puVar5[3] = 0;
  *(undefined1 *)(puVar5 + 5) = 0;
  iVar11 = *(int *)(lVar14 + 100);
  *(undefined **)(lVar25 + iVar11) = PTR___swiftEmptyArrayStorage_10056ed48;
  uVar26 = *(undefined8 *)(param_2 + 0x18);
  uVar28 = *(undefined8 *)(param_2 + 0x20);
  lVar13 = param_2;
  func_0x00010000e7b8(param_2,uVar26);
  lStack_120 = lVar14;
  func_0x0001000f03c0();
  _swift_bridgeObjectRetain(uVar19);
  __ss7DecoderP9container7keyedBys22KeyedDecodingContainerVyqd__Gqd__m_tKs9CodingKeyRd__lFTj
            (lVar22,&UNK_100541720,&UNK_100541720,lVar13,uVar26,uVar28);
  lVar13 = lStack_e8;
  if (unaff_x21 != 0) {
    func_0x00010000e7dc(param_2);
    goto LAB_1000df750;
  }
  puStack_220 = puVar6;
  puStack_218 = puVar4;
  puStack_210 = puVar5;
  lStack_208 = (long)iVar11;
  func_0x0001000de06c(lStack_e8,0,0xe000000000000000);
  uStack_a0 = uStack_a0 & 0xffffff00;
  uVar26 = 0x1005ae7e0;
  func_0x000100008b94(0x1005ae7e0,PTR___s10Foundation4UUIDVMa_10056ba98,
                      PTR___s10Foundation4UUIDVSeAAMc_10056bac0);
  lVar14 = lStack_f0;
  lVar16 = lStack_f8;
  __ss22KeyedDecodingContainerV6decode_6forKeyqd__qd__m_xtKSeRd__lF
            (lStack_f8,lVar12,&uStack_a0,lStack_f0,lVar12,uVar26);
  (**(code **)(lVar23 + 0x28))(lVar25,lVar16,lVar12);
  uStack_a0 = CONCAT31(uStack_a0._1_3_,1);
  puVar20 = &uStack_a0;
  lVar16 = lVar14;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  if (lVar16 == 0) {
    puVar4 = (undefined8 *)(lVar13 + *(int *)(lStack_120 + 0x14));
    puVar20 = (uint *)*puVar4;
    lVar16 = puVar4[1];
    _swift_bridgeObjectRetain();
  }
  lVar29 = lStack_108;
  lVar15 = lStack_110;
  puVar4 = puStack_118;
  *puStack_118 = puVar20;
  puVar4[1] = lVar16;
  lVar13 = 0x1005ae7e8;
  func_0x00010000921c(0x1005ae7e8,&UNK_10042e510);
  uStack_51 = 2;
  lVar16 = lVar13;
  func_0x0001000f0400();
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,lVar13,&uStack_51,lVar14,lVar13,lVar16);
  lVar16 = CONCAT44(uStack_9c,uStack_a0);
  if (lVar16 == 0) {
LAB_1000df80c:
    uVar26 = *(undefined8 *)(param_2 + 0x18);
    uVar28 = *(undefined8 *)(param_2 + 0x20);
    lVar13 = param_2;
    func_0x00010000e7b8(param_2,uVar26);
    func_0x0001000f0488();
    puVar17 = &UNK_1005417b0;
    __ss7DecoderP9container7keyedBys22KeyedDecodingContainerVyqd__Gqd__m_tKs9CodingKeyRd__lFTj
              (lVar15,&UNK_1005417b0,&UNK_1005417b0,lVar13,uVar26,uVar28);
    lVar13 = lVar29;
    __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySiSgSim_xtKF();
    uVar21 = uStack_158;
    puVar18 = (undefined *)0x0;
    if (((uint)lVar13 & 0xff) != 1) {
      puVar18 = puVar17;
    }
    lVar16 = lStack_150;
    _swift_allocObject(lStack_150,uStack_158 + lStack_160,uStack_168 | 7);
    lVar27 = lStack_140;
    *(undefined8 *)(lVar16 + 0x18) = uStack_178;
    *(undefined8 *)(lVar16 + 0x10) = uStack_180;
    lVar14 = lVar16 + uVar21;
    __s10Foundation4UUIDVACycfC(lStack_140);
    (**(code **)(lStack_130 + 8))(lVar15,lVar29);
    lVar13 = lVar14;
    (*pcStack_188)(lVar14,lVar27,lVar12);
    uVar26 = _UNK_10042d6a0;
    puVar4 = (undefined8 *)(lVar14 + *(int *)(lStack_148 + 0x14));
    puVar4[1] = _UNK_10042d6a8;
    *puVar4 = uVar26;
    puVar4[2] = 1;
    *(undefined **)(lVar14 + *(int *)(lStack_148 + 0x18)) = puVar18;
    lVar14 = lStack_f0;
  }
  else if (*(long *)(lVar16 + 0x10) == 0) {
    _swift_bridgeObjectRelease(lVar16);
    goto LAB_1000df80c;
  }
  lVar12 = lStack_e8;
  _swift_release_x8(lStack_128);
  *(long *)(lVar25 + iVar10) = lVar16;
  uStack_51 = 3;
  func_0x0001000f04c8();
  puVar17 = &UNK_100541be8;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,&UNK_100541be8,&uStack_51,lVar14,&UNK_100541be8,lVar13);
  pbVar3 = pbStack_138;
  if ((byte)uStack_a0 == 2) {
    pbVar7 = (byte *)(lVar12 + *(int *)(lStack_120 + 0x1c));
    uVar26 = *(undefined8 *)(pbVar7 + 0x18);
    lVar13 = *(long *)(pbVar7 + 8);
    lVar16 = *(long *)(pbVar7 + 0x10);
    bVar30 = *pbVar7;
  }
  else {
    uVar26 = CONCAT71(uStack_87,uStack_88);
    lVar13 = lStack_98;
    lVar16 = lStack_90;
    bVar30 = (byte)uStack_a0;
  }
  *pbStack_138 = bVar30 & 1;
  *(long *)(pbVar3 + 0x10) = lVar16;
  *(long *)(pbVar3 + 8) = lVar13;
  *(undefined8 *)(pbVar3 + 0x18) = uVar26;
  uStack_51 = 4;
  func_0x0001000f0508();
  puVar18 = &UNK_100541b60;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,&UNK_100541b60,&uStack_51,lVar14,&UNK_100541b60,puVar17);
  pbVar3 = pbStack_190;
  lVar13 = lStack_98;
  lVar16 = lStack_90;
  bVar30 = (byte)uStack_a0;
  if ((byte)uStack_a0 == 2) {
    pbVar7 = (byte *)(lVar12 + *(int *)(lStack_120 + 0x20));
    lVar13 = *(long *)(pbVar7 + 8);
    lVar16 = *(long *)(pbVar7 + 0x10);
    bVar30 = *pbVar7;
  }
  *pbStack_190 = bVar30 & 1;
  *(long *)(pbVar3 + 0x10) = lVar16;
  *(long *)(pbVar3 + 8) = lVar13;
  uStack_51 = 5;
  func_0x0001000f0548();
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,&UNK_100541ae0,&uStack_51,lVar14,&UNK_100541ae0,puVar18);
  if (lStack_98 == 0) {
    pbVar3 = (byte *)(lStack_e8 + *(int *)(lStack_120 + 0x24));
    bVar30 = *pbVar3;
    lVar13 = *(long *)(pbVar3 + 8);
    _swift_bridgeObjectRetain(lVar13);
  }
  else {
    bVar30 = (byte)uStack_a0;
    lVar13 = lStack_98;
  }
  _swift_bridgeObjectRelease(lStack_1a0);
  pbVar3 = pbStack_198;
  *pbStack_198 = bVar30 & 1;
  *(long *)(pbVar3 + 8) = lVar13;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,6);
  puVar20 = &uStack_a0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySbSgSbm_xtKF(puVar20,lVar14);
  bVar30 = (byte)puVar20;
  if (((uint)puVar20 & 0xff) == 2) {
    bVar30 = *(byte *)(lStack_e8 + *(int *)(lStack_120 + 0x28));
  }
  *(byte *)(lVar25 + lStack_1a8) = bVar30 & 1;
  uVar26 = 0x1005ae820;
  func_0x00010000921c(0x1005ae820,&UNK_10042e518);
  uStack_51 = 7;
  uVar28 = uVar26;
  func_0x0001000f0588();
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,uVar26,&uStack_51,lVar14,uVar26,uVar28);
  lVar13 = CONCAT44(uStack_9c,uStack_a0);
  if (lVar13 == 0) {
    lVar13 = *(long *)(lStack_e8 + *(int *)(lStack_120 + 0x2c));
    _swift_bridgeObjectRetain(lVar13);
  }
  _swift_bridgeObjectRelease(uVar19);
  *(long *)(lVar25 + lStack_1b0) = lVar13;
  uStack_51 = 8;
  func_0x0001000f0610();
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,&UNK_100541320,&uStack_51,lStack_f0,&UNK_100541320,uVar19);
  uVar9 = uStack_88;
  lVar16 = lStack_90;
  uVar26 = CONCAT44(uStack_9c,uStack_a0);
  puVar1[1] = lStack_98;
  *puVar1 = uVar26;
  puVar1[2] = lVar16;
  *(undefined1 *)(puVar1 + 3) = uVar9;
  uStack_a0._0_1_ = '\t';
  puVar20 = &uStack_a0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySiSgSim_xtKF();
  if (((uint)lVar13 & 0xff) == 1) {
    puVar20 = *(uint **)(lStack_e8 + *(int *)(lStack_120 + 0x34));
  }
  *(uint **)(lVar25 + lStack_1b8) = puVar20;
  uStack_51 = 10;
  func_0x0001000f0650();
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,&UNK_1005412a8,&uStack_51,lStack_f0,&UNK_1005412a8,puVar20);
  if ((byte)uStack_a0 == '\x03') {
    uStack_a0._0_1_ = *(char *)(lStack_e8 + *(int *)(lStack_120 + 0x38));
  }
  *(byte *)(lVar25 + lStack_1c0) = (byte)uStack_a0;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,0xb);
  puVar20 = &uStack_a0;
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  if (lVar13 == 0) {
    puVar1 = (undefined8 *)(lStack_e8 + *(int *)(lStack_120 + 0x3c));
    puVar20 = (uint *)*puVar1;
    lVar13 = puVar1[1];
    _swift_bridgeObjectRetain();
  }
  puVar1 = puStack_1c8;
  *puStack_1c8 = puVar20;
  puVar1[1] = lVar13;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,0xc);
  puVar20 = &uStack_a0;
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  if (lVar13 == 0) {
    puVar1 = (undefined8 *)(lStack_e8 + *(int *)(lStack_120 + 0x40));
    puVar20 = (uint *)*puVar1;
    lVar13 = puVar1[1];
    _swift_bridgeObjectRetain();
  }
  puVar1 = puStack_1d0;
  *puStack_1d0 = puVar20;
  puVar1[1] = lVar13;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,0xd);
  puVar20 = &uStack_a0;
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  if (lVar13 == 0) {
    puVar1 = (undefined8 *)(lStack_e8 + *(int *)(lStack_120 + 0x44));
    puVar20 = (uint *)*puVar1;
    lVar13 = puVar1[1];
    _swift_bridgeObjectRetain();
  }
  puVar1 = puStack_1d8;
  *puStack_1d8 = puVar20;
  puVar1[1] = lVar13;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,0xe);
  puVar20 = &uStack_a0;
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  if (lVar13 == 0) {
    puVar1 = (undefined8 *)(lStack_e8 + *(int *)(lStack_120 + 0x48));
    puVar20 = (uint *)*puVar1;
    lVar13 = puVar1[1];
    _swift_bridgeObjectRetain();
  }
  puVar1 = puStack_1e0;
  *puStack_1e0 = puVar20;
  puVar1[1] = lVar13;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,0xf);
  puVar20 = &uStack_a0;
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  if (lVar13 == 0) {
    puVar1 = (undefined8 *)(lStack_e8 + *(int *)(lStack_120 + 0x4c));
    puVar20 = (uint *)*puVar1;
    lVar13 = puVar1[1];
    _swift_bridgeObjectRetain();
  }
  puVar1 = apuStack_200[0];
  *apuStack_200[0] = puVar20;
  puVar1[1] = lVar13;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,0x10);
  puVar20 = &uStack_a0;
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  if (lVar13 == 0) {
    puVar1 = (undefined8 *)(lStack_e8 + *(int *)(lStack_120 + 0x50));
    puVar20 = (uint *)*puVar1;
    lVar13 = puVar1[1];
    _swift_bridgeObjectRetain();
  }
  puVar1 = apuStack_200[1];
  *apuStack_200[1] = puVar20;
  puVar1[1] = lVar13;
  uStack_51 = 0x11;
  func_0x0001000f0690();
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,&UNK_100541a58,&uStack_51,lStack_f0,&UNK_100541a58,lVar13);
  if (lStack_90 == 0) {
    puVar6 = (undefined1 *)(lStack_e8 + *(int *)(lStack_120 + 0x54));
    uVar9 = *puVar6;
    lStack_a8 = *(long *)(puVar6 + 8);
    lVar13 = *(long *)(puVar6 + 0x10);
    uStack_b8 = *(undefined8 *)(puVar6 + 0x18);
    uVar26 = *(undefined8 *)(puVar6 + 0x20);
    uVar28 = *(undefined8 *)(puVar6 + 0x28);
    _swift_bridgeObjectRetain(lVar13);
    func_0x0001000f06d0(uVar26,uVar28);
  }
  else {
    uVar28 = CONCAT71(uStack_77,uStack_78);
    uStack_b8 = CONCAT71(uStack_87,uStack_88);
    lStack_a8 = lStack_98;
    uVar9 = (undefined1)uStack_a0;
    lVar13 = lStack_90;
    uVar26 = uStack_80;
  }
  puVar6 = puStack_220;
  uVar19 = *(undefined8 *)(puStack_220 + 0x20);
  uVar8 = *(undefined8 *)(puStack_220 + 0x28);
  _swift_bridgeObjectRelease(*(undefined8 *)(puStack_220 + 0x10));
  func_0x0001000936c0(uVar19,uVar8);
  *puVar6 = uVar9;
  *(long *)(puVar6 + 8) = lStack_a8;
  *(long *)(puVar6 + 0x10) = lVar13;
  *(undefined8 *)(puVar6 + 0x18) = uStack_b8;
  *(undefined8 *)(puVar6 + 0x20) = uVar26;
  *(undefined8 *)(puVar6 + 0x28) = uVar28;
  uStack_a0 = CONCAT31(uStack_a0._1_3_,0x12);
  puVar20 = &uStack_a0;
  lVar13 = lStack_f0;
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeySSSgSSm_xtKF();
  puVar1 = puStack_218;
  *puStack_218 = puVar20;
  puVar1[1] = lVar13;
  uVar26 = 0x1005ae850;
  func_0x00010000921c(0x1005ae850,&UNK_10042e520);
  uStack_51 = 0x13;
  uVar28 = uVar26;
  func_0x0001000f06e4();
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,uVar26,&uStack_51,lStack_f0,uVar26,uVar28);
  puVar17 = PTR___swiftEmptyArrayStorage_10056ed48;
  if ((undefined *)CONCAT44(uStack_9c,uStack_a0) != (undefined *)0x0) {
    puVar17 = (undefined *)CONCAT44(uStack_9c,uStack_a0);
  }
  *(undefined **)(lVar25 + lStack_1f0) = puVar17;
  uStack_51 = 0x14;
  func_0x0001000f076c();
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,&UNK_100543520,&uStack_51,lStack_f0,&UNK_100543520,uVar26);
  puVar1 = puStack_210;
  uVar26 = CONCAT44(uStack_9c,uStack_a0);
  puStack_210[1] = lStack_98;
  *puVar1 = uVar26;
  puVar1[3] = CONCAT71(uStack_87,uStack_88);
  puVar1[2] = lStack_90;
  puVar1[4] = uStack_80;
  *(undefined1 *)(puVar1 + 5) = uStack_78;
  uVar26 = 0x1005ae870;
  func_0x00010000921c(0x1005ae870,&UNK_10042e528);
  uStack_51 = 0x15;
  uVar28 = 0x1005ae878;
  func_0x0001000f0d04(0x1005ae878,&DAT_1000f07ac,PTR___sSayxGSesSeRzlMc_10056e8a8);
  __ss22KeyedDecodingContainerV15decodeIfPresent_6forKeyqd__Sgqd__m_xtKSeRd__lF
            (&uStack_a0,uVar26,&uStack_51,lStack_f0,uVar26,uVar28);
  puVar17 = PTR___swiftEmptyArrayStorage_10056ed48;
  if ((undefined *)CONCAT44(uStack_9c,uStack_a0) != (undefined *)0x0) {
    puVar17 = (undefined *)CONCAT44(uStack_9c,uStack_a0);
  }
  func_0x00010001dc80(lStack_e8,&SUB_1000e3704);
  (**(code **)(lStack_100 + 8))(lVar22,lStack_f0);
  *(undefined **)(lVar25 + lStack_208) = puVar17;
  func_0x00010001dc3c(lVar25,uStack_1e8,&SUB_1000e3704);
  func_0x00010000e7dc(param_2);
LAB_1000df750:
  func_0x00010001dc80(lVar25,&SUB_1000e3704);
  return;
}

