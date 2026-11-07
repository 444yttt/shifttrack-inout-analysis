/* page_byAdding_3184 0x10006028c-0x100060efc ghidra-pseudocode */

undefined ** page_byAdding_3184(undefined8 param_1)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  undefined *puVar7;
  undefined **ppuVar8;
  undefined **ppuVar9;
  undefined **ppuVar10;
  ulong uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  long extraout_x8;
  long extraout_x8_00;
  long lVar14;
  long extraout_x8_01;
  long lVar15;
  long extraout_x8_02;
  long lVar16;
  long extraout_x8_03;
  long lVar17;
  long extraout_x8_04;
  long extraout_x8_05;
  long extraout_x8_06;
  code *pcVar18;
  undefined *puVar19;
  undefined8 *puVar20;
  undefined8 uVar21;
  ulong uVar22;
  ulong uVar23;
  long extraout_x12;
  long extraout_x12_00;
  long extraout_x12_01;
  long extraout_x12_02;
  long lVar24;
  long *unaff_x20;
  ulong uVar25;
  ulong uVar26;
  long lVar27;
  code *pcVar28;
  long lVar29;
  code *pcVar30;
  ulong uVar31;
  long lVar32;
  long lVar33;
  code *pcStack_220;
  code *pcStack_218;
  long lStack_210;
  undefined4 uStack_204;
  code *pcStack_200;
  code *pcStack_1f8;
  undefined **ppuStack_1f0;
  long lStack_1e8;
  code *pcStack_1e0;
  long lStack_1d8;
  long lStack_1d0;
  undefined **ppuStack_1c8;
  undefined **ppuStack_1c0;
  undefined **ppuStack_1b8;
  long lStack_1b0;
  long lStack_1a8;
  ulong uStack_1a0;
  ulong uStack_198;
  undefined *puStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_ee;
  undefined *puStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_7e;
  
  lVar2 = 0x1005a86d0;
  func_0x00010000921c(0x1005a86d0,&UNK_10042d050);
  (*(code *)PTR____chkstk_darwin_10056c088)
            (*(long *)(*(long *)(lVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0;
  ppuStack_1b8 = (undefined **)((long)&pcStack_220 - extraout_x8);
  __s10Foundation4UUIDVMa();
  lStack_1b0 = *(long *)(lVar2 + -8);
  lStack_1a8 = lVar2;
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lStack_1b0 + 0x40));
  lVar14 = ((long)&pcStack_220 - extraout_x8) - (extraout_x8_00 + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0;
  __s10Foundation8CalendarVMa();
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(*(long *)(lVar2 + -8) + 0x40));
  lVar15 = lVar14 - (extraout_x8_01 + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0x1005a82d8;
  lStack_1d0 = lVar15;
  func_0x00010000921c(0x1005a82d8,&UNK_10042aa30);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(*(long *)(lVar2 + -8) + 0x40));
  lVar15 = lVar15 - (extraout_x8_02 + 0xfU & 0xfffffffffffffff0);
  ppuStack_1c8 = (undefined **)lVar15;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar15 = lVar15 - extraout_x12;
  lVar3 = 0;
  uStack_198 = lVar15;
  __s10Foundation4DateVMa();
  lVar16 = *(long *)(lVar3 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar16 + 0x40));
  lVar15 = lVar15 - (extraout_x8_03 + 0xfU & 0xfffffffffffffff0);
  ppuStack_1c0 = (undefined **)lVar15;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar15 = lVar15 - extraout_x12_00;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  uStack_1a0 = lVar15 - extraout_x12_01;
  (*(code *)PTR____chkstk_darwin_10056c088)();
  lVar17 = (lVar15 - extraout_x12_01) - extraout_x12_02;
  lVar4 = 0;
  __s10Foundation8CalendarV9ComponentOMa();
  lVar27 = *(long *)(lVar4 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar27 + 0x40));
  lVar24 = lVar17 - (extraout_x8_04 + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0x1005a86c0;
  func_0x00010000921c(0x1005a86c0,&UNK_100429910);
  (*(code *)PTR____chkstk_darwin_10056c088)
            (*(long *)(*(long *)(lVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  uVar25 = lVar24 - extraout_x8_05;
  lVar5 = 0;
  __s10Foundation12DateIntervalVMa();
  lVar32 = *(long *)(lVar5 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar32 + 0x40));
  lVar33 = uVar25 - (extraout_x8_06 + 0xfU & 0xfffffffffffffff0);
  lVar2 = 0;
  func_0x000100071b0c();
  lVar29 = (long)*(int *)(lVar2 + 0x4c);
  pcVar30 = *(code **)(lVar27 + 0x68);
  (*pcVar30)(lVar24,*(undefined4 *)PTR___s10Foundation8CalendarV9ComponentO5monthyA2EmFWC_10056bbd0,
             lVar4);
  __s10Foundation8CalendarV12dateInterval2of3forAA04DateD0VSgAC9ComponentO_AA0G0VtF
            (uVar25,lVar24,param_1);
  pcVar28 = *(code **)(lVar27 + 8);
  (*pcVar28)(lVar24,lVar4);
  lVar2 = uVar25;
  (**(code **)(lVar32 + 0x30))(uVar25,1,lVar5);
  if ((int)lVar2 == 1) {
    uVar13 = 0x1005a86c0;
    puVar19 = &UNK_100429910;
  }
  else {
    (**(code **)(lVar32 + 0x20))(lVar33,uVar25,lVar5);
    uStack_204 = *(undefined4 *)PTR___s10Foundation8CalendarV9ComponentO3dayyA2EmFWC_10056bbb8;
    pcStack_200 = pcVar30;
    (*pcVar30)(lVar24,uStack_204,lVar4);
    uVar22 = uStack_1a0;
    lStack_1d8 = lVar32;
    __s10Foundation12DateIntervalV3endAA0B0Vvg(uStack_1a0);
    uVar25 = uStack_198;
    __s10Foundation8CalendarV4date8byAdding5value2to18wrappingComponentsAA4DateVSgAC9ComponentO_SiAJSbtF
              (uStack_198,lVar24,0xffffffffffffffff,uVar22,0);
    pcStack_1e0 = *(code **)(lVar16 + 8);
    (*pcStack_1e0)(uVar22,lVar3);
    pcStack_1f8 = pcVar28;
    ppuStack_1f0 = (undefined **)lVar4;
    (*pcVar28)(lVar24,lVar4);
    pcVar28 = *(code **)(lVar16 + 0x30);
    uVar6 = uVar25;
    (*pcVar28)(uVar25,1,lVar3);
    if ((int)uVar6 != 1) {
      pcStack_220 = *(code **)(lVar16 + 0x20);
      pcStack_218 = pcVar28;
      lStack_210 = lVar5;
      lStack_1e8 = lVar33;
      (*pcStack_220)(lVar17,uVar25,lVar3);
      lVar2 = *unaff_x20;
      if (lVar2 == 0) {
        lVar2 = unaff_x20[1];
        uVar12 = 0;
        func_0x00010001c974(0);
        uVar13 = 0x1005a8680;
        func_0x000100008b94(0x1005a8680,&SUB_10001c974,&UNK_1004276a8);
        __s7SwiftUI17EnvironmentObjectV5errors5NeverOyF(0,lVar2,uVar12,uVar13);
                    /* WARNING: Does not return */
        pcVar28 = (code *)SoftwareBreakpoint(1,0x100060efc);
        (*pcVar28)();
      }
      puVar19 = &UNK_100429860;
      _swift_getKeyPath(&UNK_100429860);
      puVar7 = &UNK_100429888;
      _swift_getKeyPath(&UNK_100429888);
      _swift_retain_x20();
      __s7Combine9PublishedV18_enclosingInstance7wrapped7storagexqd___s24ReferenceWritableKeyPathCyqd__xGAHyqd__ACyxGGtcRld__CluigZ
                (&puStack_150,lVar2,puVar19,puVar7);
      _swift_release_x21();
      _swift_release_x24();
      _swift_release_x20();
      uStack_a8 = uStack_118;
      uStack_b0 = uStack_120;
      uStack_98 = uStack_108;
      uStack_a0 = uStack_110;
      uStack_90 = uStack_100;
      uStack_7e = uStack_ee;
      uStack_d8 = uStack_148;
      puStack_e0 = puStack_150;
      uStack_c8 = uStack_138;
      uStack_d0 = uStack_140;
      uStack_b8 = uStack_128;
      uStack_c0 = uStack_130;
      __s10Foundation12DateIntervalV5startAA0B0Vvg(uVar22);
      lVar2 = lStack_1d0;
      __s10Foundation8CalendarV7currentACvgZ(lStack_1d0);
      uVar25 = uVar22;
      lVar4 = lVar2;
      func_0x0001000e9470(uVar22,lVar2);
      pcVar18 = *(code **)(lVar16 + 0x10);
      lVar5 = lVar3;
      uStack_198 = uVar25;
      (*pcVar18)(uVar22,lVar17,lVar3);
      __s10Foundation8CalendarV7currentACvgZ(lVar2);
      uVar25 = uVar22;
      func_0x0001000e9470(uVar22,lVar2);
      func_0x0001000da0a8(lVar15,(long)unaff_x20 + lVar29,uStack_198,lVar4,puVar7);
      ppuVar10 = ppuStack_1f0;
      (*pcStack_200)(lVar24,uStack_204,ppuStack_1f0);
      func_0x0001000da0a8(uVar22,(long)unaff_x20 + lVar29,uVar25,lVar2,lVar5);
      ppuVar9 = ppuStack_1c8;
      __s10Foundation8CalendarV4date8byAdding5value2to18wrappingComponentsAA4DateVSgAC9ComponentO_SiAJSbtF
                (ppuStack_1c8,lVar24,1,uVar22,0);
      pcVar30 = pcStack_1e0;
      (*pcStack_1e0)(uVar22,lVar3);
      (*pcStack_1f8)(lVar24,ppuVar10);
      pcVar28 = pcStack_218;
      ppuVar8 = ppuVar9;
      (*pcStack_218)(ppuVar9,1,lVar3);
      ppuVar10 = ppuStack_1c0;
      if ((int)ppuVar8 == 1) {
        (*pcVar18)(ppuStack_1c0,lVar15,lVar3);
        ppuVar8 = ppuVar9;
        (*pcVar28)(ppuVar9,1,lVar3);
        lVar2 = lStack_1a8;
        if ((int)ppuVar8 != 1) {
          func_0x00010000a9d0(ppuVar9,0x1005a82d8,&UNK_10042aa30);
        }
      }
      else {
        (*pcStack_220)(ppuStack_1c0,ppuVar9,lVar3);
        lVar2 = lStack_1a8;
      }
      if (lRam00000001005b43b8 != -1) {
        _swift_once(0x1005b43b8,&DAT_1001ce6f4);
      }
      ppuVar8 = &puStack_e0;
      func_0x0001001cd534(ppuVar8,lVar15,ppuVar10,(long)unaff_x20 + lVar29);
      ppuVar9 = ppuVar8;
      func_0x00010007a124();
      lStack_1d0 = 0;
      _swift_bridgeObjectRelease(ppuVar8);
      func_0x00010001d8b0(&puStack_e0);
      (*pcVar30)(ppuVar10,lVar3);
      (*pcVar30)(lVar15,lVar3);
      ppuVar10 = ppuStack_1b8;
      func_0x0001000523d8(ppuStack_1b8);
      lVar4 = lStack_1b0;
      ppuVar8 = ppuVar10;
      (**(code **)(lStack_1b0 + 0x30))(ppuVar10,1,lVar2);
      if ((int)ppuVar8 == 1) {
        (*pcVar30)(lVar17,lVar3);
        (**(code **)(lStack_1d8 + 8))(lStack_1e8,lStack_210);
        func_0x00010000a9d0(ppuVar10,0x1005a86d0,&UNK_10042d050);
        return ppuVar9;
      }
      (**(code **)(lVar4 + 0x20))(lVar14,ppuVar10,lVar2);
      func_0x00010000921c(0x1005aa940,&UNK_100429e58);
      ppuVar10 = ppuVar9;
      __ss18_DictionaryStorageC4copy8originalAByxq_Gs05__RawaB0C_tFZ();
      lVar2 = 0;
      ppuStack_1f0 = ppuVar9 + 8;
      uVar22 = 1L << ((ulong)*(byte *)(ppuVar9 + 4) & 0x3f);
      uVar25 = 0xffffffffffffffff;
      if ((*(byte *)(ppuVar9 + 4) & 0x3f) < 6) {
        uVar25 = ~(-1L << (uVar22 & 0x3f));
      }
      pcStack_1f8 = (code *)(uVar22 + 0x3f >> 6);
      ppuStack_1c0 = ppuVar10 + 8;
      uVar22 = uVar25 & (ulong)*ppuStack_1f0;
      ppuStack_1c8 = ppuVar9;
      ppuStack_1b8 = ppuVar10;
      if ((uVar25 & (ulong)*ppuStack_1f0) == 0) goto joined_r0x000100060bd8;
LAB_100060b8c:
      uVar25 = (uVar22 & 0xaaaaaaaaaaaaaaaa) >> 1 | (uVar22 & 0x5555555555555555) << 1;
      uVar25 = (uVar25 & 0xcccccccccccccccc) >> 2 | (uVar25 & 0x3333333333333333) << 2;
      uVar25 = (uVar25 & 0xf0f0f0f0f0f0f0f0) >> 4 | (uVar25 & 0xf0f0f0f0f0f0f0f) << 4;
      uVar25 = (uVar25 & 0xff00ff00ff00ff00) >> 8 | (uVar25 & 0xff00ff00ff00ff) << 8;
      uVar25 = (uVar25 & 0xffff0000ffff0000) >> 0x10 | (uVar25 & 0xffff0000ffff) << 0x10;
      uStack_198 = uVar22 - 1 & uVar22;
      uVar25 = LZCOUNT(uVar25 >> 0x20 | uVar25 << 0x20) | lVar2 << 6;
      do {
        puVar20 = (undefined8 *)(ppuStack_1c8[6] + uVar25 * 0x18);
        lVar4 = *(long *)(ppuStack_1c8[7] + uVar25 * 8);
        uVar13 = *puVar20;
        uVar12 = puVar20[1];
        uVar21 = puVar20[2];
        uVar22 = *(ulong *)(lVar4 + 0x10);
        _swift_bridgeObjectRetain(lVar4);
        puVar19 = PTR___swiftEmptyArrayStorage_10056ed48;
        if (uVar22 != 0) {
          uStack_1a0 = uVar22 - 1;
          uVar31 = 0;
          uVar6 = uVar22;
          do {
            while( true ) {
              if (uVar6 == uVar31) {
                    /* WARNING: Does not return */
                pcVar28 = (code *)SoftwareBreakpoint(1,0x100060e98);
                (*pcVar28)();
              }
              lVar5 = 0;
              func_0x000100118388();
              uVar23 = (ulong)*(byte *)(*(long *)(lVar5 + -8) + 0x50);
              uVar26 = uVar23 + 0x20 & (uVar23 ^ 0xffffffffffffffff);
              lVar16 = *(long *)(*(long *)(lVar5 + -8) + 0x48);
              lVar15 = lVar4 + uVar26 + lVar16 * uVar31;
              uVar23 = uVar31 + 1;
              uVar11 = lVar15 + *(int *)(lVar5 + 0x24);
              __s10Foundation4UUIDV2eeoiySbAC_ACtFZ(uVar11,lVar14);
              if ((uVar11 & 1) != 0) break;
              uVar31 = uVar23;
              if (uVar22 == uVar23) goto LAB_100060d88;
            }
            puVar7 = puVar19;
            _swift_isUniquelyReferenced_nonNull_native();
            puStack_150 = puVar19;
            if (((ulong)puVar7 & 1) == 0) {
              func_0x0001000fab1c(0,*(long *)(puVar19 + 0x10) + 1,1);
            }
            uVar6 = *(ulong *)(puStack_150 + 0x10);
            pcVar28 = (code *)(uVar6 + 1);
            if (*(ulong *)(puStack_150 + 0x18) >> 1 <= uVar6) {
              pcStack_200 = pcVar28;
              func_0x0001000fab1c(1 < *(ulong *)(puStack_150 + 0x18),pcVar28,1);
              pcVar28 = pcStack_200;
            }
            puVar19 = puStack_150;
            *(code **)(puStack_150 + 0x10) = pcVar28;
            func_0x00010001dc3c(lVar15,puStack_150 + uVar6 * lVar16 + uVar26,&SUB_100118388);
            uVar6 = uVar23;
            if (uVar23 <= uVar22) {
              uVar6 = uVar22;
            }
            bVar1 = uStack_1a0 != uVar31;
            uVar31 = uVar23;
          } while (bVar1);
        }
LAB_100060d88:
        _swift_bridgeObjectRelease(lVar4);
        uVar22 = uVar25 >> 3 & 0x1ffffffffffffff8;
        *(ulong *)((long)ppuStack_1c0 + uVar22) =
             *(ulong *)((long)ppuStack_1c0 + uVar22) | 1L << (uVar25 & 0x3f);
        puVar20 = (undefined8 *)(ppuStack_1b8[6] + uVar25 * 0x18);
        *puVar20 = uVar13;
        puVar20[1] = uVar12;
        puVar20[2] = uVar21;
        *(undefined **)(ppuStack_1b8[7] + uVar25 * 8) = puVar19;
        if (SCARRY8((long)ppuStack_1b8[2],1)) {
                    /* WARNING: Does not return */
          pcVar28 = (code *)SoftwareBreakpoint(1,0x100060ea0);
          (*pcVar28)();
        }
        ppuStack_1b8[2] = ppuStack_1b8[2] + 1;
        uVar22 = uStack_198;
        if (uStack_198 != 0) goto LAB_100060b8c;
joined_r0x000100060bd8:
        do {
          ppuVar10 = ppuStack_1b8;
          lVar5 = lStack_1e8;
          lVar4 = lStack_210;
          if (SCARRY8(lVar2,1)) {
                    /* WARNING: Does not return */
            pcVar28 = (code *)SoftwareBreakpoint(1,0x100060e9c);
            (*pcVar28)();
          }
          lVar2 = lVar2 + 1;
          if ((long)pcStack_1f8 <= lVar2) {
            _swift_bridgeObjectRelease(ppuStack_1c8);
            func_0x000100078210(ppuVar10);
            _swift_release_x24();
            (**(code **)(lStack_1b0 + 8))(lVar14,lStack_1a8);
            (*pcStack_1e0)(lVar17,lVar3);
            (**(code **)(lStack_1d8 + 8))(lVar5,lVar4);
            return ppuVar10;
          }
          puVar19 = ppuStack_1f0[lVar2];
        } while (puVar19 == (undefined *)0x0);
        uVar25 = ((ulong)puVar19 & 0xaaaaaaaaaaaaaaaa) >> 1 |
                 ((ulong)puVar19 & 0x5555555555555555) << 1;
        uVar25 = (uVar25 & 0xcccccccccccccccc) >> 2 | (uVar25 & 0x3333333333333333) << 2;
        uVar25 = (uVar25 & 0xf0f0f0f0f0f0f0f0) >> 4 | (uVar25 & 0xf0f0f0f0f0f0f0f) << 4;
        uVar25 = (uVar25 & 0xff00ff00ff00ff00) >> 8 | (uVar25 & 0xff00ff00ff00ff) << 8;
        uVar25 = (uVar25 & 0xffff0000ffff0000) >> 0x10 | (uVar25 & 0xffff0000ffff) << 0x10;
        uStack_198 = (ulong)(puVar19 + -1) & (ulong)puVar19;
        uVar25 = LZCOUNT(uVar25 >> 0x20 | uVar25 << 0x20) | lVar2 * 0x40;
      } while( true );
    }
    (**(code **)(lStack_1d8 + 8))(lVar33,lVar5);
    uVar13 = 0x1005a82d8;
    puVar19 = &UNK_10042aa30;
  }
  func_0x00010000a9d0(uVar25,uVar13,puVar19);
  ppuVar10 = (undefined **)PTR___swiftEmptyArrayStorage_10056ed48;
  func_0x0001000adfb8(PTR___swiftEmptyArrayStorage_10056ed48);
  return ppuVar10;
}

