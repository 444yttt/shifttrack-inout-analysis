/* format_minute_of_day 0x1000968c4-0x100096a00 ghidra-pseudocode */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16] format_minute_of_day(long param_1)

{
  ulong uVar1;
  undefined1 auVar2 [16];
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  long lVar6;
  undefined8 uVar7;
  undefined *puVar8;
  undefined8 uVar9;
  ulong uVar10;
  
  puVar3 = PTR___sSiN_10056e918;
  uVar10 = param_1 % 0x5a0;
  uVar1 = (ulong)((int)uVar10 + 0x5a0);
  if (-1 < (long)uVar10) {
    uVar1 = uVar10;
  }
  puVar5 = PTR___sSiN_10056e918;
  puVar8 = PTR___sSis23CustomStringConvertiblesWP_10056e950;
  __ss23CustomStringConvertibleP11descriptionSSvgTj();
  __sSS6appendyySSF(0x3a,0xe100000000000000);
  lVar6 = 0x1005a9038;
  func_0x00010000921c(0x1005a9038,&UNK_10042a0f0);
  _swift_allocObject();
  uVar7 = _UNK_100426320;
  *(undefined8 *)(lVar6 + 0x18) = _UNK_100426328;
  *(undefined8 *)(lVar6 + 0x10) = uVar7;
  puVar4 = PTR___sSis7CVarArgsWP_10056e958;
  *(undefined **)(lVar6 + 0x38) = puVar3;
  *(undefined **)(lVar6 + 0x40) = puVar4;
  *(ulong *)(lVar6 + 0x20) = (ulong)((uint)uVar1 + (((uint)uVar1 & 0xffff) / 0x3c) * -0x3c) & 0xffff
  ;
  uVar7 = 0x64323025;
  uVar9 = 0xe400000000000000;
  __sSS10FoundationE6format_S2Sh_s7CVarArg_pdtcfC(0x64323025,0xe400000000000000,lVar6);
  _swift_bridgeObjectRetain(puVar8);
  __sSS6appendyySSF(uVar7,uVar9);
  _swift_bridgeObjectRelease(puVar8);
  _swift_bridgeObjectRelease(uVar9);
  auVar2._8_8_ = puVar8;
  auVar2._0_8_ = puVar5;
  return auVar2;
}

