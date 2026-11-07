# shifttrack-inout-analysis

許諾済み IN/OUT IPA（`com.graff.inout` 1.0 build 3）の静的解析。公開しているのは解析に必要な実行ファイルとテキストだけ。署名バイト、プロビジョニングプロファイル、広告ユニット ID、メールアドレスは除いてある。元 IPA 全体は置いていない。

製品リポジトリへの統合はここではしない。回収した初期値と時刻・日付の処理は `recovered/InOutRecovered.swift`。根拠と、まだ関数として取れていない給与計算・丸め・休憩の選択は `notes/FINDINGS.md`。

## バイナリ

`bin/IN-OUT`

- sha256 `11b0cf24cb5beabcc440ab1b54ba8886aee25b9e6caf686009397289d8b3b4a5`
- サイズ 6379760
- 実機用 Mach-O。このリポジトリの macOS runner で Simulator 起動できるとは扱わない

## 確認

```sh
python3 tools/verify_macos.py
```

GitHub Actions の `macos-verify` は hosted の `macos-15` で同じスクリプトを走らせ、`swift-demangle`、iPhoneOS SDK の SwiftUI.framework、`dyld_info` があれば fixup chain も見る。消費する macOS 分数の上限は未確認で、無制限とは扱わない。

Ghidra 11.4 PUBLIC の疑似コードは `notes/ghidra/`。元の Swift ソースではない。
