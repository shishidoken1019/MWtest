<?php

/**
 * mail用ユーティリティクラス
 *
 * mail用のユーティリティクラス
 * ユーティリティ系クラスなので、全て
 * mail_util::メソッド
 * の形式でのcallを想定している
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class mail_util {


/**
 * メールアドレスの抜き出し
 *
 * 名前 <メールアドレス> の形式から、メールアドレスだけを抜き出す
 *
 * @access public
 * @param string $s メールアドレス
 * @return string 抜き出したアドレス部分。エラーは空文字復帰
 */
static public function carve_address($s)
{
  if (1 === preg_match('/[<](.*?)[>]/', $s, $mt)) {
    return $mt[1];
  }
  // else
  return trim($s);
}

/**
 * 可変エンベロープリターンパス (VERP : variable envelope return path) 作成
 *
 * エラーメールを取得する用のごにょり
 * 例)
 * mail_util::make_verp('error@test.com', 'm.furusho@gmail.com');
 * を
 * error+m.furusho=gmail.com@test.com
 * にする。
 *
 * @access public
 * @param string $e エラー到達用メールアドレス
 * @param string $t toメールアドレス(中に埋め込む
 * @param string $d メールアドレスのデリミタ : とりあえずPostfixのデフォ＋を
 * @return string return-pathに設定すべきメールアドレス
 */
static public function make_verp($e, $t, $d = '+')
{
  // まず分解
  $wk = explode('@', $e);

  // toアドレスの＠を置換
  $t = strtr($t, '@', '=');

  // 足し込んで復帰
  $s = $wk[0] . $d . $t . '@' . $wk[1];
  return $s;
}

} // end of class

