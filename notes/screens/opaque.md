# opaque 型から起こした modifier 順

`some View` の具体型を `__swift5_typeref` から読む方針を試した。結果は次のとおり。

## 型名は残っていない

`__swift5_typeref`（`0x100440fe0`、0x87b92 バイト）に `TupleView`、`ModifiedContent`、`_ConditionalContent` の綴りは無い。特殊化された `TupleView<(A, B, C)>` のマングル名も無い。`__swift5_types` の 271 型に opaque type（kind 4）は無い。struct 180、enum 72、class 19 だけである。

`swift_getOpaqueTypeMetadata2`（`0x100400094`）は 363 回呼ばれる。引数 `x1` は、アプリ内の body 型ではなく、SwiftUI のメソッドが返す opaque 型（シンボル末尾 `QOMQ`）である。読めた例は `navigationTitle`、`sheet`、`alert`、`presentationCornerRadius`。padding、font、foregroundStyle、`View.cornerRadius` の `QOMQ` は import に無い。この 3 つは specialize されて、実行時の opaque 要求を通らない。

`TupleView` のメタデータ要求は 14、イニシャライザは 7。`ModifiedContent` のメタデータ要求は 39。引数は実行時のメタデータポインタで、子ビューの型名には戻らない。積み順は、この方針でも 36 画面とも未のまま。

72 箇所は `x1` の取り方がこの走査と違い、名前が付いていない。下の列は、名前が付いた呼び出しの順であり、その関数の modifier の全部とは限らない。

## 確定。その画面の関数の中の順

`CalendarDayView` の `0x10003cdd8`。この関数は `ShiftEntryEditor` も呼ぶ。

`presentationBackground`、`presentationCornerRadius`、`presentationDragIndicator`、`onChange`、`sheet`、`sheet`、`alert`

角丸の即値 32 と、ドラッグ距離 30 は、同じ関数の直接呼び出しにある。`presentationBackground` の色と、`presentationDragIndicator` の Visibility は未確定。

`LateMessageView` の `0x1000c551c`。

`navigationTitle`、`navigationBarTitleDisplayMode`、`onChange` が 5。

`TodoEditor` の `0x1001f2b8c`。この関数は `TodoEditor` だけを呼ぶ。

`textFieldStyle`、`submitLabel`、`buttonStyle`。スタイルの具体値は未確定。

`ShiftRepeatEditorView` の `0x1001f8f44` と `WorkplaceImportView` の `0x10023eb54`。

どちらも `navigationTitle`、`navigationBarTitleDisplayMode`、`toolbar`。

## 部分。複数の画面を呼ぶ関数の順

カレンダー body `0x1000541dc` は `CalendarTabView` と日ビュー、パターン編集、繰り返し、依頼プランナーを呼ぶ。

`scrollIndicators`、`onChange`、`onChange`、`sheet`、`fullScreenCover`、`sheet`、`sheet`、`alert`、`alert`

一覧ハブ `0x100255ab0`。

`sheet` が 3、`alert`、`sheet` が 4。

オンボーディングと取り込みを呼ぶ `0x100104588`。

`presentationBackground`、`presentationCornerRadius`、`presentationDragIndicator`、`interactiveDismissDisabled`、`alert`、`photosPicker`、`fullScreenCover`、`onChange`、`sheet`、`alert`

勤務先エディタと取り込みを呼ぶ `0x10022e0d0`。

`navigationTitle`、`navigationBarTitleDisplayMode`、`fullScreenCover`、`onChange`、`sheet`

`0x10020ad88` は画面アクセサを呼ばない。`presentationDetents`、`presentationBackground`、`presentationCornerRadius`。角丸 32 と large / medium は同じ関数の直接呼び出しにある。シートの所属は未確定。

## 専用関数

`ShiftEntryEditor`。descriptor `0x100440570`、アクセサ `0x1001b8554`。このアクセサだけを呼ぶ最大の関数は `0x1001bdcfc`（4244 バイト）。「追加して次へ」「シフトパターンに追加」「勤務先に戻す」「行き先の名前」を読む。`0x1001ba1b4` もこのアクセサだけを呼び、「このまま保存」「この日のシフトを外す」を読む。分数の正規化 `0x1001b8770` もこのアクセサだけを呼ぶ。`CalendarDayView` の `0x10003cdd8` と一覧ハブが、このアクセサを呼ぶ。

`TodoEditor`。descriptor `0x1004408c8`、アクセサ `0x1001f641c`。このアクセサだけを呼ぶ最大の関数は `0x1001f3d30`（3492 バイト）。`ShiftPartEditorView` の `0x1001f0144` が、このアクセサを呼ぶ。

`PayBreakdownView`。descriptor `0x10043fa30`、アクセサ `0x1001165c0`。テキスト内の `bl` も、このアクセサへの `adrp` + `add` も無い。専用関数は結べていない。
