# 移植仕様の網羅率

元の Swift ソースではない。広告の `BannerAdView` と Intelligence は対象外。画像、フォントファイル、`Assets.car`、実機スクショはこのリポジトリに置いていない。スクショから読んだ配置は印 `観` で、命令の `確` とは別である。

対象は画面とシート 36。観点は 9。セルは 324。

| 印 | 意味 |
| --- | --- |
| 確 | その画面のアクセサだけを呼ぶ関数、またはその画面の body として既に結んである関数の中にある |
| 部 | その画面を他の画面と一緒に呼ぶ関数、またはアクセサの近くにある。画面の中の位置は未確定 |
| 観 | 実機スクショで見える。命令の証明ではない。個人の金額、勤務先名、住所は書いていない |
| 未 | 命令にもスクショにも、その観点が無い |

確定率は 確 ÷ 324。着手率は（確 + 部）÷ 324。半分換算は（確 + 部 × 0.5）÷ 324。積み順を推測で埋めない。

| | 画面数 36 |
| --- | --- |
| 確 | 149（46.0%） |
| 部 | 44（13.6%） |
| 観 | 33（10.2%） |
| 未 | 98（30.2%） |
| 確 + 部 + 観 | 226（69.8%） |

観点ごとの数。

| 観点 | 確 | 部 | 観 | 未 |
| --- | --- | --- | --- | --- |
| 入口（型と関数） | 35 | 1 | 0 | 0 |
| 文言 | 25 | 0 | 4 | 7 |
| SF Symbols | 12 | 0 | 8 | 16 |
| フォントとサイズ | 26 | 0 | 3 | 7 |
| 余白と角丸 | 20 | 2 | 1 | 13 |
| 積み順 | 0 | 0 | 17 | 19 |
| ジェスチャとアニメーション | 13 | 9 | 0 | 14 |
| 遷移 | 7 | 26 | 0 | 3 |
| ロジック | 11 | 6 | 0 | 19 |

積み順の `確` は 0 のままである。スクショで上から下の順が見えた画面だけ `観` にした。命令の `VStack` はバイナリ全体で 5 のまま、その 5 関数は一つの画面へ届かない。`Section` を呼ぶ関数が文字列を読む順は、子ビューの順としては置いていない。詳細は `observed.md`。

## 画面ごとの印

列は入口、文言、記号、フォント、余白、積み順、操作、遷移、ロジック。

| 画面 | 印 |
| --- | --- |
| RootView | 確 確 未 確 確 未 確 部 未 |
| InOutTabBar | 確 観 確 観 確 観 確 未 未 |
| LaunchAnimationView | 確 未 未 未 未 未 確 部 未 |
| OnboardingView | 確 確 観 確 確 観 確 部 確 |
| WorkplaceListView | 確 確 確 確 確 観 確 部 確 |
| WorkplaceDirectoryView | 確 確 確 確 確 観 確 部 未 |
| WorkplaceEditorView | 確 確 未 未 未 未 未 確 確 |
| WorkplaceImportView | 確 確 未 確 部 未 未 確 確 |
| WorkplaceThumbnailView | 確 未 未 未 未 未 未 未 未 |
| LocationPickerView | 確 確 未 確 確 未 確 部 確 |
| CalendarTabView | 確 確 確 確 確 観 確 確 確 |
| CalendarDayView | 確 確 確 確 確 観 確 確 確 |
| CalendarAccessView | 確 確 未 確 確 未 部 部 部 |
| IncomeView | 確 確 確 確 確 観 部 部 未 |
| WallEditorView | 確 確 観 確 確 観 未 部 未 |
| SettingsView | 確 確 確 確 確 観 部 部 確 |
| AboutView | 確 未 確 未 未 未 未 部 未 |
| GuideOverlay | 確 観 観 確 確 観 確 部 未 |
| ShiftPartEditorView | 確 観 観 確 確 観 未 部 未 |
| ShiftRepeatEditorView | 確 確 観 観 観 観 未 確 確 |
| ShiftRequestView | 確 確 観 確 確 観 部 部 確 |
| ShiftRequestPlannerView | 確 確 確 確 確 未 確 部 部 |
| RequestHoursStockSheet | 確 確 確 確 部 未 部 部 未 |
| ShiftCheckView | 確 確 確 確 確 観 確 部 未 |
| LateMessageView | 確 確 未 確 未 未 確 確 部 |
| LateTemplateSheet | 確 確 未 確 確 未 未 部 未 |
| LateTemplateEditorView | 確 未 未 確 未 未 未 部 未 |
| PayBreakdownView | 部 未 未 未 未 未 未 未 部 |
| PayPeriodsView | 確 観 未 確 未 観 未 部 未 |
| PayPeriodDetailView | 確 確 未 観 未 観 部 部 部 |
| PayScheduleSettingView | 確 未 未 未 未 未 未 確 未 |
| PayTermsEditorView | 確 確 未 確 未 未 未 部 部 |
| PayScheduleEditorView | 確 確 未 未 未 未 部 部 未 |
| UnconfirmedShiftsView | 確 確 観 確 未 観 部 部 未 |
| ShiftEntryEditor | 確 確 観 確 確 未 部 部 確 |
| TodoEditor | 確 未 確 確 確 未 未 部 未 |

`PayBreakdownView` は、アクセサ `0x1001165c0` への `bl` も `adrp` + `add` も無い。積み順の `確` は 0 のまま。記号で `確` にした名前は、`Image(systemName:)` の関数から画面アクセサまで、呼び出し元が一つずつしか無い経路で届くもの。画面の中の位置は見ていない。

余白の `確` は、`EdgeInsets.init(_all:)` の直前が `fmov d0, #即値` で、その関数が画面アクセサだけに届くもの。幅と高さの `_FrameLayout` は余白にしていない。繰り返しの余白はスクショの `観` のまま。時間のストックと取り込みは、複数画面を呼ぶ関数にあるので `部`。

画面別の命令は `calendar.md`、`workplace.md`、`pay.md`、`shift.md`、`settings.md`、`root.md`。スクショとの突き合わせは `observed.md`。給与、重なり、`WeekTemplate`、保存先、通知は `logic.md`。opaque 型から読んだ modifier 順は `opaque.md`。
