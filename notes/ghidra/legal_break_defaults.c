/* legal_break_defaults 0x1000da43c-0x1000da574 ghidra-pseudocode */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void legal_break_defaults(void)

{
  long lVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long extraout_x8;
  ulong uVar6;
  undefined1 *puVar7;
  ulong uVar8;
  long lVar9;
  code *pcVar10;
  long lVar11;
  
  lVar3 = 0;
  __s10Foundation4UUIDVMa();
  lVar9 = *(long *)(lVar3 + -8);
  (*(code *)PTR____chkstk_darwin_10056c088)(*(undefined8 *)(lVar9 + 0x40));
  puVar7 = &stack0xffffffffffffffb0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0);
  lVar4 = 0x1005ae098;
  func_0x00010000921c(0x1005ae098,&UNK_10042d860);
  lVar5 = 0;
  func_0x0001000e9930();
  lVar11 = *(long *)(*(long *)(lVar5 + -8) + 0x48);
  uVar6 = (ulong)*(byte *)(*(long *)(lVar5 + -8) + 0x50);
  uVar8 = uVar6 + 0x20 & (uVar6 ^ 0xffffffffffffffff);
  _swift_allocObject(lVar4,uVar8 + lVar11 * 2,uVar6 | 7);
  uVar2 = _UNK_100427a30;
  *(undefined8 *)(lVar4 + 0x18) = _UNK_100427a38;
  *(undefined8 *)(lVar4 + 0x10) = uVar2;
  lVar1 = lVar4 + uVar8;
  __s10Foundation4UUIDVACycfC(puVar7);
  pcVar10 = *(code **)(lVar9 + 0x20);
  (*pcVar10)(lVar1,puVar7,lVar3);
  *(undefined8 *)(lVar1 + *(int *)(lVar5 + 0x14)) = 0x168;
  *(undefined8 *)(lVar1 + *(int *)(lVar5 + 0x18)) = 0x2d;
  lVar1 = lVar1 + lVar11;
  __s10Foundation4UUIDVACycfC(puVar7);
  (*pcVar10)(lVar1,puVar7,lVar3);
  *(undefined8 *)(lVar1 + *(int *)(lVar5 + 0x14)) = 0x1e0;
  *(undefined8 *)(lVar1 + *(int *)(lVar5 + 0x18)) = 0x3c;
  lRam00000001005d0a40 = lVar4;
  return;
}

