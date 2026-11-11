# 移植仕様の網羅率

元の Swift ソースではない。画面を見て書いた配置ではない。広告の `BannerAdView` と Intelligence は対象外。画像、フォントファイル、`Assets.car` はこのリポジトリに置いていない。

対象は画面とシート 36。観点は 9。セルは 324。

| 印 | 意味 |
| --- | --- |
| 確 | その画面のアクセサだけを呼ぶ関数、またはその画面の body として既に結んである関数の中にある |
| 部 | その画面を他の画面と一緒に呼ぶ関数、またはアクセサの近くにある。画面の中の位置は未確定 |
| 未 | 命令をその画面へ結べていない |

確定率は 確 ÷ 324。着手率は（確 + 部）÷ 324。半分換算は（確 + 部 × 0.5）÷ 324。積み順を推測で埋めない。

| | 画面数 36 |
| --- | --- |
| 確 | 64（19.8%） |
| 部 | 54（16.7%） |
| 未 | 206（63.6%） |
| 確 + 部 | 118（36.4%） |
| 半分換算 | 28.1% |

観点ごとの数。

| 観点 | 確 | 部 | 未 |
| --- | --- | --- | --- |
| 入口（型と関数） | 35 | 1 | 0 |
| 文言 | 10 | 5 | 21 |
| SF Symbols | 1 | 1 | 34 |
| フォントとサイズ | 1 | 1 | 34 |
| 余白と角丸 | 1 | 1 | 34 |
| 積み順 | 0 | 0 | 36 |
| ジェスチャとアニメーション | 5 | 15 | 16 |
| 遷移 | 7 | 26 | 3 |
| ロジック | 4 | 4 | 28 |

積み順は 36 画面とも未である。`VStack` の直接呼び出しはバイナリ全体で 5。`__swift5_typeref` にも `TupleView` や `ModifiedContent` の特殊化名は無く、opaque 型の要求から子ビューの順は戻らなかった。戻った modifier 順は `opaque.md`。

## 画面ごとの印

列は入口、文言、記号、フォント、余白、積み順、操作、遷移、ロジック。

| 画面 | 印 |
| --- | --- |
| RootView | 確 未 未 未 未 未 部 部 未 |
| InOutTabBar | 確 未 確 未 未 未 部 未 未 |
| LaunchAnimationView | 確 未 未 未 未 未 部 部 未 |
| OnboardingView | 確 部 未 未 部 未 部 部 未 |
| WorkplaceListView | 確 確 部 部 未 未 部 部 確 |
| WorkplaceDirectoryView | 確 確 未 未 未 未 確 部 未 |
| WorkplaceEditorView | 確 確 未 未 未 未 未 確 未 |
| WorkplaceImportView | 確 確 未 未 未 未 未 確 未 |
| WorkplaceThumbnailView | 確 未 未 未 未 未 未 未 未 |
| LocationPickerView | 確 未 未 未 未 未 確 部 未 |
| CalendarTabView | 確 部 未 確 未 未 確 確 確 |
| CalendarDayView | 確 確 未 未 確 未 確 確 確 |
| CalendarAccessView | 確 確 未 未 未 未 未 部 未 |
| IncomeView | 確 未 未 未 未 未 部 部 未 |
| WallEditorView | 確 未 未 未 未 未 未 部 未 |
| SettingsView | 確 確 未 未 未 未 部 部 未 |
| AboutView | 確 未 未 未 未 未 未 部 未 |
| GuideOverlay | 確 未 未 未 未 未 部 部 未 |
| ShiftPartEditorView | 確 未 未 未 未 未 未 部 未 |
| ShiftRepeatEditorView | 確 未 未 未 未 未 未 確 未 |
| ShiftRequestView | 確 確 未 未 未 未 部 部 未 |
| ShiftRequestPlannerView | 確 未 未 未 未 未 部 部 部 |
| RequestHoursStockSheet | 確 未 未 未 未 未 部 部 未 |
| ShiftCheckView | 確 未 未 未 未 未 部 部 未 |
| LateMessageView | 確 部 未 未 未 未 確 確 未 |
| LateTemplateSheet | 確 未 未 未 未 未 未 部 未 |
| LateTemplateEditorView | 確 未 未 未 未 未 未 部 未 |
| PayBreakdownView | 部 未 未 未 未 未 未 未 部 |
| PayPeriodsView | 確 未 未 未 未 未 未 部 未 |
| PayPeriodDetailView | 確 確 未 未 未 未 部 部 部 |
| PayScheduleSettingView | 確 未 未 未 未 未 未 確 未 |
| PayTermsEditorView | 確 部 未 未 未 未 未 部 部 |
| PayScheduleEditorView | 確 未 未 未 未 未 部 部 未 |
| UnconfirmedShiftsView | 確 部 未 未 未 未 部 部 未 |
| ShiftEntryEditor | 確 確 未 未 未 未 未 部 確 |
| TodoEditor | 確 未 未 未 未 未 未 部 未 |

`PayBreakdownView` は、他の画面と分かれた関数が無い。`ShiftEntryEditor` と `TodoEditor` は型名の cstring がある。アクセサはこの表では結んでいない。

画面別の命令は `calendar.md`、`workplace.md`、`pay.md`、`shift.md`、`settings.md`、`root.md`。給与、重なり、`WeekTemplate`、保存先、通知は `logic.md`。opaque 型から読んだ modifier 順は `opaque.md`。
