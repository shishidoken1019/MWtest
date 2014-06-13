<?php

/**
 * トークナイザー
 *
 * ユニークなトークンを生成する
 * XXX まず大抵の状況でユニークになると思います
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 */
require_once('code_util.inc');

class tokenizer 
{

/**
 * _get
 * メインロジック
 *
 */
static public function _get($delimiter, $flg_ran, $flg_pid, $flg_ip)
{
$tokens = array();
  // 秒＆マイクロ秒を取得
  // XXX …関数の復帰値が空白デリミタ。…正気か？
  list($usec, $sec) = explode(" ", microtime());
  
  // ここはデフォルト
  // エポック秒：まぁ全部はいらんのでちょっと小さめに
  $tokens[] = $sec - 1079340000;
  // マイクロ秒
  $tokens[] = (int)($usec * 1000 * 1000);

  // 乱数
  if ($flg_ran) {
    $tokens[] = mt_rand();
  }

  // プロセスID
  if ($flg_pid) {
    $tokens[] = getmypid();
  }

  // XXX thread ID …PHPだと取れない ；；

  // IPアドレス
  if ($flg_ip) {
    $tokens[] = str_replace(".", "", $_SERVER['REMOTE_ADDR']);
  }

  // で、作成
  $ret = array();
  foreach($tokens as $token) {
    $ret[] = code_util::to62($token);
  }
  return implode($delimiter, $ret);
}


/**
 * get
 * とりあえずデフォルトってことで
 *
 */
static function get($delimiter = "-")
{
  // とりあえず乱数＋プロセスID
  // XXX ま、問題なかろうて
  return tokenizer::_get($delimiter, true, true, false);
}


} // end of class

