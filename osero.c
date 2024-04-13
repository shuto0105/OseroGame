/*
オセロ
先行が自分でエンターキー2回押すと進む
工夫 COMが一番ひっくり返せるマスに置いてくる
不具合 ゲームを進めていくと最後の方バグる
*/

#include <handy.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, k, l, opp, me, swich, turnnum, keep, preseti, presetj;
    int xmax, ymax, xymax, yxmax, count, counti, countj;
    int seti, setj;

    // startset
    int board[8][8] = {};
    board[3][3] = 1;
    board[4][4] = 1;
    board[3][4] = 2;
    board[4][3] = 2;

    /////////////////////////////////set
    HgOpen(800, 800);
    for (i = 0; i < 8; i++) {
        HgLine(100 * i, 0, 100 * i, 800);
    }
    for (i = 0; i < 8; i++) {
        HgLine(0, 100 * i, 800, 100 * i);
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] == 1 || board[i][j] == 2) {
                if (board[i][j] == 1) {
                    HgSetFillColor(HG_WHITE);
                } else if (board[i][j] == 2) {
                    HgSetFillColor(HG_BLACK);
                }
                HgCircleFill(50 + 100 * j, 50 + 100 * i, 40, 1);
            }
        }
    }

    ///////////////////////////////////////// if your turn
    int clicki, clickj;

    hgevent *event;      // HandyGraphicのイベントを扱うための変数
    int clickx, clicky;  // クリックされた座標

    HgSetEventMask(HG_MOUSE_DOWN);  // マウスクリックのみを検出するように設定

    for (;;) {


        for (turnnum = 0; turnnum <= 0;) { ///////click judgeloop

        HgSetEventMask(HG_MOUSE_DOWN);  // マウスクリックのみを検出するように設定
        event =
            HgEvent();  // マウスダウンを待つ。イベント情報はeventに格納される。
        clickx = event->x;  // クリックされたx座標を取り出す
        clicky = event->y;  // クリックされたy座標を取り出す
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (100 * i < clicky && clicky < 100 * (i + 1)) {
                    if (100 * j < clickx && clickx < 100 * (j + 1)) {
                        clicki = i;
                        clickj = j;
                    }
                }
            }
        }

        keep = board[clicki][clickj];
        board[clicki][clickj] = 1;

        //////////////////////////////turn over
        opp = 2;
        me = 1;
        swich = 0;

        /// ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        for (i = clicki + 1, swich = 0;; i++) {
            if (board[i][clickj] == opp && i <= 7) {
                if (swich == 1) {
                    board[i][clickj] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][clickj] == me && i <= 7) {
                if (i == clicki + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    i--;
                }

            } else if (swich == 1 && board[i][clickj] == me && i <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎
        for (i = clicki + 1, j = clickj + 1, swich = 0;; i++, j++) {
            if (board[i][j] == opp && i <= 7 && j <= 7) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i <= 7 && j <= 7) {
                if (i == clicki + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    j = clickj + 1;
                    i--;
                    j--;
                }

            } else if (swich == 1 && board[i][j] == me && i <= 7 && j <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////→→→→→→→→→→→→→→→→→→→→
        for (j = clickj + 1, swich = 0;; j++) {
            if (board[clicki][j] == opp && j <= 7) {
                if (swich == 1) {
                    board[clicki][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[clicki][j] == me && j <= 7) {
                if (j == clickj + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    j = clickj + 1;
                    j--;
                }

            } else if (swich == 1 && board[clicki][j] == me && j <= 7) {
                break;
            } else {
                break;
            }
        }
        //////////////↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎
        for (i = clicki - 1, j = clickj + 1, swich = 0;; i--, j++) {
            if (board[i][j] == opp && i >= 0 && j <= 7) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i >= 0 && j <= 7) {
                if (j == clickj + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    j = clickj + 1;
                    i++;
                    j--;
                }

            } else if (swich == 1 && board[i][j] == me && i >= 0 && j <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
        for (i = clicki - 1, swich = 0;; i--) {
            if (board[i][clickj] == opp && i >= 0) {
                if (swich == 1) {
                    board[i][clickj] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][clickj] == me && i >= 0) {
                if (i == clicki - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    i++;
                }

            } else if (swich == 1 && board[i][clickj] == me && i >= 0) {
                break;
            } else {
                break;
            }
        }
        ////////////↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎
        for (i = clicki - 1, j = clickj - 1, swich = 0;; i--, j--) {
            if (board[i][j] == opp && i >= 0 && j >= 0) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i >= 0 && j >= 0) {
                if (i == clicki - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    j = clickj - 1;
                    i++;
                    j++;
                }

            } else if (swich == 1 && board[i][j] == me && i >= 0 && j >= 0) {
                break;
            } else {
                break;
            }
        }
        ////////////←←←←←←←←←←←←←←←←←←←←←←←←←←←←
        for (j = clickj - 1, swich = 0;; j--) {
            if (board[clicki][j] == opp && j >= 0) {
                if (swich == 1) {
                    board[clicki][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[clicki][j] == me && j >= 0) {
                if (j == clickj - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    j = clickj - 1;
                    j++;
                }

            } else if (swich == 1 && board[clicki][j] == me && j >= 0) {
                break;
            } else {
                break;
            }
        }
        /////////////↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎
        for (i = clicki + 1, j = clickj - 1, swich = 0;; i++, j--) {
            if (board[i][j] == opp && i <= 7 && j >= 0) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i <= 7 && j >= 0) {
                if (j == clickj - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    j = clickj - 1;
                    i--;
                    j++;
                }

            } else if (swich == 1 && board[i][j] == me && i <= 7 && j >= 0) {
                break;
            } else {
                break;
            }
        }

            if (turnnum == 0) {

            board[clicki][clickj] = keep;
            }

        }

        /////////////////////////////set
        HgClear();
        for (i = 0; i < 8; i++) {
            HgLine(100 * i, 0, 100 * i, 800);
        }
        for (i = 0; i < 8; i++) {
            HgLine(0, 100 * i, 800, 100 * i);
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (board[i][j] == 1 || board[i][j] == 2) {
                    if (board[i][j] == 1) {
                        HgSetFillColor(HG_WHITE);
                    } else if (board[i][j] == 2) {
                        HgSetFillColor(HG_BLACK);
                    }
                    HgCircleFill(50 + 100 * j, 50 + 100 * i, 40, 1);
                }
            }
        }

        HgGetChar();

        ///////////////////////// (change turn) count of max
        xmax = 0;
        ymax = 0;
        xymax = 0;
        yxmax = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (board[i][j] == 1) {
                    count = 1;

                    // xcount
                    for (countj = j + 1, count = 1;; countj++) {

                        if (j - 1 < 0 || countj > 7) {

                            break;
                        }

                        if (board[i][countj] == 1) {

                            count++;
                        } else if (board[i][j - 1] == 0 && board[i][countj] == 2) {

                            if (count > xmax) {
                                printf ("02board %d %d %d %d\n", i, j-1, i, countj);
                                xmax = count;
                                break;
                            }

                        } else if (board[i][j - 1] == 2 && board[i][countj] == 0) {

                            if (count > xmax) {
                                printf ("02board %d %d %d %d\n", i, j-1, i, countj);
                                xmax = count;
                                break;
                            }

                        } else {
                            break;
                        }
                    }

                    // ycount
                    for (counti = i + 1, count = 1;; counti++) {

                        if (i - 1 < 0 || counti > 7) {

                            break;
                        }

                        if (board[counti][j] == 1) {

                            count++;
                        } else if (board[i - 1][j] == 0 && board[counti][j] == 2) {

                            if (count > ymax) {
                                ymax = count;
                                break;
                            }

                        } else if (board[i - 1][j] == 2 && board[counti][j] == 0) {

                            if (count > ymax) {
                                ymax = count;
                                break;
                            }

                        } else {
                            break;
                        }
                    }

                    //   xy/count
                    for (counti = i + 1, countj = j + 1, count = 1;;counti++, countj++) {
                        
                        if (i - 1 < 0 || j - 1 < 0 || counti > 7 || countj > 7) {

                            break;
                        }

                        if (board[counti][countj] == 1) {

                            count++;
                        } else if (board[i - 1][j - 1] == 0 && board[counti][countj] == 2) {

                            if (count > xymax) {

                                xymax = count;
                                break;
                            }

                        } else if (board[i - 1][j - 1] == 2 && board[counti][countj] == 0) {

                            if (count > xymax) {

                                xymax = count;
                                break;
                            }

                        } else {       
                            break;
                        }
                    }
                    ////////////  yx\count
                    for (counti = i + 1, countj = j - 1, count = 1;;
                         counti++, countj--) {
                        if (i - 1 < 0 || j + 1 > 7 || counti > 7 ||
                            countj < 0) {
                            break;
                        }

                        if (board[counti][countj] == 1) {
                            count++;
                        } else if (board[i - 1][j + 1] == 0 &&
                                   board[counti][countj] == 2) {
                            if (count > yxmax) {
                                yxmax = count;
                                break;
                            }
                        } else if (board[i - 1][j + 1] == 2 &&
                                   board[counti][countj] == 0) {
                            if (count > yxmax) {
                                yxmax = count;
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                }
            }
        }

        printf("%d %d %d %d\n", xmax, ymax, xymax, yxmax);
        HgGetChar();

        ////////////////////////////////find seti, setj
        counti = 0;
        countj = 0;
        if (xmax >= ymax && xmax >= xymax && xmax >= yxmax) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (board[i][j] == 0 && board[i][j + xmax + 1] == 2 &&
                        j + xmax + 1 <= 7) {
                        for (countj = j + 1; countj <= j + xmax; countj++) {
                            if (board[i][countj] == 1) {
                                if (countj == j + xmax) {
                                    seti = i;
                                    setj = j;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    } else if (board[i][j] == 2 &&
                               board[i][j + xmax + 1] == 0 &&
                               j + xmax + 1 <= 7) {
                        for (countj = j + 1; countj <= j + xmax; countj++) {
                            if (board[i][countj] == 1) {
                                if (countj == j + xmax) {
                                    seti = i;
                                    setj = j + xmax + 1;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
        } else if (ymax >= xmax && ymax >= xymax && ymax >= yxmax) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (board[i][j] == 0 && board[i + ymax + 1][j] == 2 &&
                        i + ymax + 1 <= 7) {
                        for (counti = i + 1; counti <= i + ymax; counti++) {
                            if (board[counti][j] == 1) {
                                if (counti == i + ymax) {
                                    seti = i;
                                    setj = j;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    } else if (board[i][j] == 2 &&
                               board[i + ymax + 1][j] == 0 &&
                               i + ymax + 1 <= 7) {
                        for (counti = i + 1; counti <= i + ymax; counti++) {
                            if (board[counti][j] == 1) {
                                if (counti == i + ymax) {
                                    seti = i + ymax + 1;
                                    setj = j;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
        } else if (xymax >= xmax && xymax >= ymax && xymax >= yxmax) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (board[i][j] == 0 &&
                        board[i + xymax + 1][j + xymax + 1] == 2 &&
                        i + xymax + 1 <= 7 && j + xymax + 1 <= 7) {
                        for (counti = i + 1, countj = j + 1;
                             counti <= i + xymax; counti++, countj++) {
                            if (board[counti][countj] == 1) {
                                if (counti == i + xymax) {
                                    seti = i;
                                    setj = j;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    } else if (board[i][j] == 2 &&
                               board[i + xymax + 1][j + xymax + 1] == 0 &&
                               i + xymax + 1 <= 7 && j + xymax + 1 <= 7) {
                        for (counti = i + 1, countj = j + 1;
                             counti <= i + xymax; counti++, countj++) {
                            if (board[counti][countj] == 1) {
                                if (counti == i + xymax) {
                                    seti = i + xymax + 1;
                                    setj = j + xymax + 1;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
        } else if (yxmax >= xmax && yxmax >= ymax && yxmax >= xymax) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (board[i][j] == 0 &&
                        board[i + yxmax + 1][j - yxmax - 1] == 2 &&
                        i + yxmax + 1 <= 7 && j - yxmax - 1 >= 0) {
                        for (counti = i + 1, countj = j - 1;
                             counti <= i + yxmax; counti++, countj--) {
                            if (board[counti][countj] == 1) {
                                if (counti == i + yxmax &&
                                    countj == j - yxmax) {
                                    seti = i;
                                    setj = j;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    } else if (board[i][j] == 2 &&
                               board[i + yxmax + 1][j - yxmax - 1] == 0 &&
                               i + yxmax + 1 <= 7 && j - yxmax - 1 >= 0) {
                        for (counti = i + 1, countj = j - 1;
                             counti <= i + yxmax; counti++, countj--) {
                            if (board[counti][countj] == 1) {
                                if (counti == i + yxmax &&
                                    countj == j - yxmax) {
                                    seti = i + yxmax + 1;
                                    setj = j - yxmax - 1;
                                    break;
                                }
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
        }

        ///////////////////////////////////////////バグった時
        if (preseti == seti && presetj == setj) {
        for (i = 0; i < 8; i++) {
            for (j = 0, turnnum = 0; j < 8; j++) {

        ////////////↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        for (i = clicki + 1, swich = 0;; i++) {
            if (board[i][clickj] == opp && i <= 7) {
                if (swich == 1) {
                    board[i][clickj] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][clickj] == me && i <= 7) {
                if (i == clicki + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    i--;
                }

            } else if (swich == 1 && board[i][clickj] == me && i <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎
        for (i = clicki + 1, j = clickj + 1, swich = 0;; i++, j++) {
            if (board[i][j] == opp && i <= 7 && j <= 7) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i <= 7 && j <= 7) {
                if (i == clicki + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    j = clickj + 1;
                    i--;
                    j--;
                }

            } else if (swich == 1 && board[i][j] == me && i <= 7 && j <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////→→→→→→→→→→→→→→→→→→→→
        for (j = clickj + 1, swich = 0;; j++) {
            if (board[clicki][j] == opp && j <= 7) {
                if (swich == 1) {
                    board[clicki][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[clicki][j] == me && j <= 7) {
                if (j == clickj + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    j = clickj + 1;
                    j--;
                }

            } else if (swich == 1 && board[clicki][j] == me && j <= 7) {
                break;
            } else {
                break;
            }
        }
        //////////////↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎
        for (i = clicki - 1, j = clickj + 1, swich = 0;; i--, j++) {
            if (board[i][j] == opp && i >= 0 && j <= 7) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i >= 0 && j <= 7) {
                if (j == clickj + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    j = clickj + 1;
                    i++;
                    j--;
                }

            } else if (swich == 1 && board[i][j] == me && i >= 0 && j <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
        for (i = clicki - 1, swich = 0;; i--) {
            if (board[i][clickj] == opp && i >= 0) {
                if (swich == 1) {
                    board[i][clickj] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][clickj] == me && i >= 0) {
                if (i == clicki - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    i++;
                }

            } else if (swich == 1 && board[i][clickj] == me && i >= 0) {
                break;
            } else {
                break;
            }
        }
        ////////////↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎
        for (i = clicki - 1, j = clickj - 1, swich = 0;; i--, j--) {
            if (board[i][j] == opp && i >= 0 && j >= 0) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i >= 0 && j >= 0) {
                if (i == clicki - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    j = clickj - 1;
                    i++;
                    j++;
                }

            } else if (swich == 1 && board[i][j] == me && i >= 0 && j >= 0) {
                break;
            } else {
                break;
            }
        }
        ////////////←←←←←←←←←←←←←←←←←←←←←←←←←←←←
        for (j = clickj - 1, swich = 0;; j--) {
            if (board[clicki][j] == opp && j >= 0) {
                if (swich == 1) {
                    board[clicki][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[clicki][j] == me && j >= 0) {
                if (j == clickj - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    j = clickj - 1;
                    j++;
                }

            } else if (swich == 1 && board[clicki][j] == me && j >= 0) {
                break;
            } else {
                break;
            }
        }
        /////////////↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎
        for (i = clicki + 1, j = clickj - 1, swich = 0;; i++, j--) {
            if (board[i][j] == opp && i <= 7 && j >= 0) {
                if (swich == 1) {
                    board[i][j] = me;
                    turnnum++;
                }

            } else if (swich == 0 && board[i][j] == me && i <= 7 && j >= 0) {
                if (j == clickj - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    j = clickj - 1;
                    i--;
                    j++;
                }

            } else if (swich == 1 && board[i][j] == me && i <= 7 && j >= 0) {
                break;
            } else {
                break;
            }
        }

        if (turnnum > 0) {

            seti = i;
            setj = j;
        }

            }
        }
        }

        preseti = seti;
        presetj = setj;


        //////////////////////////////turn over
        opp = 1;
        me = 2;
        clicki = seti;
        clickj = setj;
        board[clicki][clickj] = me;
        swich = 0;
        /// ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        for (i = clicki + 1, swich = 0;; i++) {
            if (board[i][clickj] == opp && i <= 7) {
                if (swich == 1) {
                    board[i][clickj] = me;
                }

            } else if (swich == 0 && board[i][clickj] == me && i <= 7) {
                if (i == clicki + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    i--;
                }

            } else if (swich == 1 && board[i][clickj] == me && i <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎↗︎
        for (i = clicki + 1, j = clickj + 1, swich = 0;; i++, j++) {
            if (board[i][j] == opp && i <= 7 && j <= 7) {
                if (swich == 1) {
                    board[i][j] = me;
                }

            } else if (swich == 0 && board[i][j] == me && i <= 7 && j <= 7) {
                if (i == clicki + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    j = clickj + 1;
                    i--;
                    j--;
                }

            } else if (swich == 1 && board[i][j] == me && i <= 7 && j <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////→→→→→→→→→→→→→→→→→→→→
        for (j = clickj + 1, swich = 0;; j++) {
            if (board[clicki][j] == opp && j <= 7) {
                if (swich == 1) {
                    board[clicki][j] = me;
                }

            } else if (swich == 0 && board[clicki][j] == me && j <= 7) {
                if (j == clickj + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    j = clickj + 1;
                    j--;
                }

            } else if (swich == 1 && board[clicki][j] == me && j <= 7) {
                break;
            } else {
                break;
            }
        }
        //////////////↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎↘︎
        for (i = clicki - 1, j = clickj + 1, swich = 0;; i--, j++) {
            if (board[i][j] == opp && i >= 0 && j <= 7) {
                if (swich == 1) {
                    board[i][j] = me;
                }

            } else if (swich == 0 && board[i][j] == me && i >= 0 && j <= 7) {
                if (j == clickj + 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    j = clickj + 1;
                    i++;
                    j--;
                }

            } else if (swich == 1 && board[i][j] == me && i >= 0 && j <= 7) {
                break;
            } else {
                break;
            }
        }
        ///////////↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
        for (i = clicki - 1, swich = 0;; i--) {
            if (board[i][clickj] == opp && i >= 0) {
                if (swich == 1) {
                    board[i][clickj] = me;
                }

            } else if (swich == 0 && board[i][clickj] == me && i >= 0) {
                if (i == clicki - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    i++;
                }

            } else if (swich == 1 && board[i][clickj] == me && i >= 0) {
                break;
            } else {
                break;
            }
        }
        ////////////↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎↙︎
        for (i = clicki - 1, j = clickj - 1, swich = 0;; i--, j--) {
            if (board[i][j] == opp && i >= 0 && j >= 0) {
                if (swich == 1) {
                    board[i][j] = me;
                }

            } else if (swich == 0 && board[i][j] == me && i >= 0 && j >= 0) {
                if (i == clicki - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki - 1;
                    j = clickj - 1;
                    i++;
                    j++;
                }

            } else if (swich == 1 && board[i][j] == me && i >= 0 && j >= 0) {
                break;
            } else {
                break;
            }
        }
        ////////////←←←←←←←←←←←←←←←←←←←←←←←←←←←←
        for (j = clickj - 1, swich = 0;; j--) {
            if (board[clicki][j] == opp && j >= 0) {
                if (swich == 1) {
                    board[clicki][j] = me;
                }

            } else if (swich == 0 && board[clicki][j] == me && j >= 0) {
                if (j == clickj - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    j = clickj - 1;
                    j++;
                }

            } else if (swich == 1 && board[clicki][j] == me && j >= 0) {
                break;
            } else {
                break;
            }
        }
        /////////////↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎↖︎
        for (i = clicki + 1, j = clickj - 1, swich = 0;; i++, j--) {
            if (board[i][j] == opp && i <= 7 && j >= 0) {
                if (swich == 1) {
                    board[i][j] = me;
                }

            } else if (swich == 0 && board[i][j] == me && i <= 7 && j >= 0) {
                if (j == clickj - 1) {
                    break;
                }

                if (swich == 0) {
                    swich = 1;
                    i = clicki + 1;
                    j = clickj - 1;
                    i--;
                    j++;
                }

            } else if (swich == 1 && board[i][j] == me && i <= 7 && j >= 0) {
                break;
            } else {
                break;
            }
        }

        HgClear();
        for (i = 0; i < 8; i++) {
            HgLine(100 * i, 0, 100 * i, 800);
        }
        for (i = 0; i < 8; i++) {
            HgLine(0, 100 * i, 800, 100 * i);
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (board[i][j] == 1 || board[i][j] == 2) {
                    if (board[i][j] == 1) {
                        HgSetFillColor(HG_WHITE);
                    } else if (board[i][j] == 2) {
                        HgSetFillColor(HG_BLACK);
                    }
                    HgCircleFill(50 + 100 * j, 50 + 100 * i, 40, 1);
                }
            }
        }
        printf("set %d %d\n", seti, setj);
    }

    return 0;
}
