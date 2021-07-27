#pragma once
// 半用関数ヘッダー

// ラップアラウンド関数
// valueが上限値に達したら下限値に戻し、
// 下限値に達していたら上限値に戻す。
// 戻り値は下限値にはなるが上限値にはならない
// 例1：wrap( 5, 0,5)->  0
// 例2：wrap(-5,-5,5)-> -5
// 例3：wrap(-6,-5,5)->  4 (5 - 1)
int Wrap(int value, int low, int high);

// 度数法の角度を弧度法に変換
float ConvertToRadians(float deg);

// 弧度法の角度を度数法に変換
float ConvertToDegrees(float rad);