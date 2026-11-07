# 統合担当への引き渡し

このリポジトリは公開解析用。private の ShiftTrack は変更していない（この token では 404）。

使うファイル:

- `recovered/InOutRecovered.swift` — 命令と Ghidra 疑似コードに対応が付いた再構成。広告なし。給与の計算式は含まない
- `notes/FINDINGS.md` — アドレスと、回収 / 未回収の区分
- `notes/ghidra/*.c` — 疑似コード。元ソースとして取り込まない
- `bin/IN-OUT` — 署名と広告 ID・メールを除いた実行ファイル
- `symbols/swiftui-view.txt` — View body の thunk

未回収のまま製品へ推測で移植しないもの: 休憩規則の選択、丸め式、時給から金額への式、年収の壁の閾値比較、`weekOfYear` の週送り。
