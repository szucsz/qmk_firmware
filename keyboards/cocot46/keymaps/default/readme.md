# The default keymap for cocot46

## CONFIG.JSN

CONFIG.JSNの設定により、動作をカスタマイズできます。

- peripheral

    ```
    "peripheral":{"max_interval":20,"min_interval":10,"slave_latency":7},
    ```
    - 通信間隔の設定です。短くすると入力のラグが減りtrack ballのカクつきを抑えることができますが、電力消費が増加します。

- reserved [3] ---- track ball angle
    ```
    "reserved":[0,0,0,7,3,0,0,0]}}
                      |
    ```
    - track ballを動かした際のカーソルの動作角度をずらします。
    - 0〜120の範囲で設定して下さい。
    - 1大きくすると時計回りに3度ずれます。\
      7を指定すると右に21度、100を指定すると右に300度（=左に60度）回転します。
    - track ballを右手で操作する方は7(右に21度)、左で操作する方は113(右に339度=左に21度)くらいに設定すると自然な動きになります。お好みで調整して下さい。

- reserved [4] ---- track ball speed
    ```
    "reserved":[0,0,0,7,3,0,0,0]}}
                        |
    ```
    - track ballの動作速度を設定します。
    - 0(遅い）〜5(速い)の範囲で設定して下さい。


## ENCODER.JSN

- Remapでキーコード設定をできるようにするため、ENCODER.JSONにダミーのカスタムキーコードを設定しておいてkeymap.cの方でRemapで設定されたキーコードが入力されるようにしています。
- 以下の設定ではLayler1〜3まででエンコーダの操作が有効になります。
```
{"pin":[7,8],"step":1,"action":[["ANY(24000)","ANY(24001)"], ["ANY(24000)","ANY(24001)"], ["ANY(24000)","ANY(24001)"], ["KC_NO","KC_NO"], ["KC_NO","KC_NO"]]}
]}}
```