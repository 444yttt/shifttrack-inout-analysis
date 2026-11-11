# 起動、タブ、ガイド

元の Swift ソースではない。広告は書かない。

## RootView

descriptor `0x1004403f8`、アクセサ `0x10017876c`。専用関数 `0x10017fc6c`（3620 バイト）。

確定。`0x10017ba24` はこのアクセサだけを呼び、`easeOut(duration:)` に 0.35 を渡してから `withAnimation` を呼ぶ。0.35 は `0x10017ba84` のビットパターン `0x3FD6666666666666`。

部分。`0x10017ac70` は `RootView` と一緒に `LaunchAnimationView`、`GuideOverlay`、`CalendarAccessView` を呼ぶ。`0x100179048` は `RootView` と一緒に `OnboardingView`、`LateMessageView`、`ShiftCheckView` を呼び、`fullScreenCover(isPresented:)`、`sheet(item:)` が 2、`alert`、`onChange`、`sensoryFeedback` がある。どのシートがどの画面かは未確定。

未確定。文言、記号、フォント、余白、角丸、積み順、ルート自身のロジック。

## InOutTabBar

descriptor `0x10043dcc0`、アクセサ `0x10002f47c`。専用関数 `0x100025004`。

確定。`0x1000253f0` の `Image(systemName:)` は `w21` で次を渡す。

| `w21` | 文字列 |
| --- | --- |
| 0 | `slider.horizontal`（17 バイト。cstring の `.3` はカウントの外） |
| 1 | `calendar` |
| 2 | `building.2` |
| 3 | `yensign` |

部分。`0x100025908` と `0x100025b48` は `withAnimation` を呼ぶ。タブの専用関数の中ではない。

確定に近いが、対応は未確定。`0x100180b74` は `SettingsView`、`IncomeView`、`WorkplaceDirectoryView`、`CalendarTabView`、`WorkplaceListView` のアクセサをこの順で呼ぶ。比較で 1 つを選んではいない。呼び出し順は構築順であり、タブの並びではない。`w21` の値と、この 5 画面の対応は未確定。

未確定。タブの文言、フォント、余白、角丸、積み順。

## LaunchAnimationView

descriptor `0x10043f40c`、アクセサ `0x1000d6708`。専用関数 `0x1000d67ec`。

部分。`0x1000d732c` はこのアクセサを呼び、`withAnimation` がある。`0x1000d76b8` は `spring` を呼ぶ。`d0` は実行時の値、`d1` は 0.82（`0x10042d408`）、`d2` は 0。この spring が起動画面のアニメーションであることは、呼び出し元まで辿れていない。

未確定。文言、記号、フォント、余白、角丸、積み順、ロゴの出し方。`LaunchBackground` の色 `195, 255, 119, 255` はカタログにある。命令がこの画面で塗ることは未確定。

## GuideOverlay

descriptor `0x10043edd0`、アクセサ `0x1000a4f84`。専用関数 `0x1000a19b4`。

部分。アクセサの近く `0x1000a0d80` は `easeInOut` に 0.3（`0x3FD3333333333333`）を渡す。`0x1000a6d34` からの 4 つの関数は `spring(response:dampingFraction:blendDuration:)` を作り、グローバルへ保存する。blend はいずれも 0。

| 保存先 | response | damping |
| --- | --- | --- |
| `0x1005d09d0` | 0.28 | 0.88 |
| `0x1005d09c8` | 0.24 | 0.85 |
| `0x1005d09b8` | 0.55 | 0.68 |
| `0x1005d09d8` | 0.45 | 0.50 |

どの画面がどの spring を再生するかは未確定。ガイドの専用関数がこれらを呼ぶことは、この走査では見ていない。

## OnboardingView

descriptor `0x10043f998`、アクセサ `0x10010423c`。専用関数 `0x10010ea20`。

部分。`0x100107ec0` は「勤務先を登録」「いつものシフト」「お給料の決まり」を読む。専用関数ではない。`0x100104588` は `OnboardingView` と `WorkplaceImportView` を呼び、`alert` が 2、`onAppear` が 1、`presentationCornerRadius` の即値 32 がある。どちらの画面の角丸かは未確定。

未確定。記号、フォント、積み順、オンボーディングのページ順。
